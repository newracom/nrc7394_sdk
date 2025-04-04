/* lwIP includes. */
#include <string.h>
#include "lwip/opt.h"
#include "lwip/def.h"
#include "lwip/mem.h"
#include "lwip/pbuf.h"
#include "lwip/sys.h"
#include "lwip/timeouts.h"
#include "lwip/stats.h"
#include "lwip/snmp.h"
#include "netif/etharp.h"
#include "driver_nrc.h"
#include "driver_nrc_tx.h"
#include "nrc_lwip.h"
#if LWIP_IPV6
#include "lwip/ethip6.h"
#endif
#if defined(SUPPORT_ETHERNET_ACCESSPOINT)
#include "nrc_eth_if.h"
#endif

/* FreeRTOS includes. */
#include "FreeRTOS.h"

#define netifMTU                            ( 1500 )
#define netifINTERFACE_TASK_STACK_SIZE      ( 350 )
#define netifINTERFACE_TASK_PRIORITY        ( configMAX_PRIORITIES - 2 )
#define netifGUARD_BLOCK_TIME               ( 250 )

/* descriptive abbreviation */
#define IFNAME0 'w'
#define IFNAME1 'l'

/* The time to block waiting for input. */
#define BLOCK_TIME_WAITING_FOR_INPUT    ( ( TickType_t ) 100 )

extern struct netif* nrc_netif[MAX_IF];
extern struct netif eth_netif;
#if LWIP_BRIDGE
extern struct netif br_netif;
#endif /* LWIP_BRIDGE */
/**
 * In this function, the hardware should be initialized.
 * Called from wlif_init().
 *
 * @param netif the already initialized lwip network interface structure
 *        for this ethernetif
 */
err_t low_level_init(struct netif *netif)
{
	unsigned portBASE_TYPE uxPriority;

	/* set MAC hardware address length */
	netif->hwaddr_len = NETIF_MAX_HWADDR_LEN;

	/* maximum transfer unit */
	netif->mtu = netifMTU;

	/* broadcast capability */
	netif->flags = NETIF_FLAG_BROADCAST | NETIF_FLAG_ETHARP | NETIF_FLAG_IGMP |NETIF_FLAG_LINK_UP;
#if LWIP_IPV6 && LWIP_IPV6_MLD
	netif->flags |= NETIF_FLAG_MLD6;
#endif /* LWIP_IPV6 && LWIP_IPV6_MLD */

	return ERR_OK;
}
/*-----------------------------------------------------------*/

/*
 * low_level_output(): Should do the actual transmission of the packet. The
 * packet is contained in the pbuf that is passed to the function. This pbuf
 * might be chained.
 */

static err_t low_level_output( struct netif *netif, struct pbuf *p )
{
	struct pbuf *q;
	err_t xReturn = ERR_OK;
	const int MAX_FRAME_NUM = 10;
	uint8_t *frames[MAX_FRAME_NUM];
	uint16_t frame_len[MAX_FRAME_NUM];
	int i = 0;

	for( q = p; q != NULL; q = q->next ) {
		frames[i] = q->payload;
		frame_len[i] = q->len;
		i++;
	}
	V(TT_NET, "[%s] netif->num = %d, output frames = %d, frame_len = %d...\n", __func__, netif->num, i, frame_len[0]);
	xReturn = nrc_transmit_from_8023_mb(netif->num, frames, frame_len, i);
	LINK_STATS_INC(link.xmit);

	return  xReturn;
}

#if 0 // not referenced
void lwif_input_from_net80211_pbuf(struct pbuf* p)
{
	struct eth_hdr      *ethhdr;
	struct netif *netif = nrc_netif[0];
	if (p != NULL) {
		LINK_STATS_INC(link.recv);
	} else {
		LINK_STATS_INC(link.memerr);
		LINK_STATS_INC(link.drop);
		return;
	}

	/* points to packet payload, which starts with an Ethernet header */
	ethhdr = p->payload;

	switch (htons(ethhdr->type)) {
		/* IP or ARP packet? */
		case ETHTYPE_IP:
		case ETHTYPE_ARP:
#if PPPOE_SUPPORT
		/* PPPoE packet? */
		case ETHTYPE_PPPOEDISC:
		case ETHTYPE_PPPOE:
#endif /* PPPOE_SUPPORT */
		/* full packet send to tcpip_thread to process */
			V(TT_NET, "[%s] send packet to tcpip thread to process...\n", __func__);
			if (netif->input(p, netif)!=ERR_OK) {
				LWIP_DEBUGF(NETIF_DEBUG, ("ethernetif_input: IP input error\n"));
				pbuf_free(p);
				p = NULL;
			}
			break;

		default:
			pbuf_free(p);
			p = NULL;
			break;
	}
}
#endif

#if STATIC_ARP_ENTRY_DHCP_SERVER
#include "lwip/prot/dhcp.h"
static uint8_t saved_dhcp_server_mac[6];
static ip4_addr_t saved_dhcp_server_ip;
#define DPHC_SERVER_ARP_ENTRY_DELAY_MS 2000

static void add_dhcp_server_arp_entry(void *arg)
{
	err_t res = etharp_add_static_entry(&saved_dhcp_server_ip, (struct eth_addr *)saved_dhcp_server_mac);
	if (res == ERR_OK) {
		LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE,
			("add_dhcp_server_arp_entry(): Static ARP entry for DHCP server added successfully.\n"));
	} else {
		LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE,
			("add_dhcp_server_arp_entry(): Failed to add static ARP entry for DHCP server. Error code: %d\n", res));
	}
}

void process_dhcp_ack(struct pbuf *p)
{
	if (!p) {
		return;
	}

	struct eth_hdr *eth = (struct eth_hdr *)p->payload;
	struct ip_hdr *iph = (struct ip_hdr *)((uint8_t *)eth + sizeof(struct eth_hdr));
	struct udp_hdr *udph = (struct udp_hdr *)((uint8_t *)iph + (IPH_HL(iph) * 4));
	struct dhcp_msg *dhcp = (struct dhcp_msg *)((uint8_t *)udph + sizeof(struct udp_hdr));

	if (IPH_PROTO(iph) != IP_PROTO_UDP) {
		return;
	}

	if (ntohl(dhcp->cookie) != DHCP_MAGIC_COOKIE) {
		return;
	}

	uint8_t *options = dhcp->options;
	int option_len = p->len - ((uint8_t *)options - (uint8_t *)p->payload);
	uint8_t dhcp_message_type = 0;

	for (int i = 0; i < option_len - 2; i++) {
		if (options[i] == DHCP_OPTION_MESSAGE_TYPE && options[i + 1] == 1) {
			dhcp_message_type = options[i + 2];
			break;
		}
	}

	if (dhcp_message_type != DHCP_ACK) {
		LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE,
				("process_dhcp_ack(): Not a DHCP ACK packet (Message Type: %d)\n", dhcp_message_type));
		return;
	}

	uint8_t dhcp_server_mac[6];
	memcpy(dhcp_server_mac, eth->src.addr, 6);

	uint32_t dhcp_server_ip_addr = 0;
	for (int i = 0; i < option_len - 2; i++) {
		if (options[i] == DHCP_OPTION_SERVER_ID && options[i + 1] == 4) {
			memcpy(&dhcp_server_ip_addr, &options[i + 2], 4);
			break;
		}
	}

	if (dhcp_server_ip_addr == 0) {
		LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE, ("process_dhcp_ack(): Failed to extract DHCP server IP address\n"));
		return;
	}

	memcpy(saved_dhcp_server_mac, dhcp_server_mac, sizeof(saved_dhcp_server_mac));
	saved_dhcp_server_ip.addr = dhcp_server_ip_addr;


	LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE, ("process_dhcp_ack(): DHCP ACK received\n"));
	LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE, ("process_dhcp_ack(): DHCP Server MAC: %02X:%02X:%02X:%02X:%02X:%02X\n",
			dhcp_server_mac[0], dhcp_server_mac[1], dhcp_server_mac[2],
			dhcp_server_mac[3], dhcp_server_mac[4], dhcp_server_mac[5]));
	LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE, ("process_dhcp_ack(): DHCP Server IP: "));
	ip4_addr_debug_print(DHCP_DEBUG | LWIP_DBG_TRACE, &saved_dhcp_server_ip);
	LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE, ("\n"));

	sys_timeout(DPHC_SERVER_ARP_ENTRY_DELAY_MS, add_dhcp_server_arp_entry, NULL);
}
#endif /* STATIC_ARP_ENTRY_DHCP_SERVER */

void lwif_input(struct nrc_wpa_if* intf, void *buffer, int data_len)
{
	struct eth_hdr *ethhdr;
	struct netif *netif = nrc_netif[intf->vif_id];
	struct pbuf *p = NULL, *q;
	int remain = data_len;
	int offset = 0;
	int len = data_len;
	struct etharp_hdr *arp_hdr;
	struct ip_hdr *ip_hdr;

	V(TT_NET, "[%s] input length = %d...\n", __func__, data_len);
	p = pbuf_alloc( PBUF_RAW, len, PBUF_POOL );

	if( p != NULL )
	{
		for( q = p; q != NULL; (q = q->next)&&remain )
		{
			/* Read enough bytes to fill this pbuf in the chain. The
			   available data in the pbuf is given by the q->len variable. */
			memcpy(q->payload, (uint8_t*)buffer + offset, q->len);
			remain -= q->len;
			offset += q->len;
		}
		LINK_STATS_INC(link.recv);
	}
	else
	{
		E(TT_NET, "[%s] pbuf_alloc failed\n", __func__);
		LINK_STATS_INC(link.memerr);
		LINK_STATS_INC(link.drop);
		return;
	}

	/* points to packet payload, which starts with an Ethernet header */
	ethhdr = p->payload;

	switch (htons(ethhdr->type)) {
		/* IP or ARP packet? */
		case ETHTYPE_ARP:
#if defined(SUPPORT_ETHERNET_ACCESSPOINT)
			if (!nrc_get_use_4address() &&
			    (nrc_eth_get_network_mode() == NRC_NETWORK_MODE_BRIDGE)) {
				arp_hdr = (struct etharp_hdr *)(p->payload + SIZEOF_ETH_HDR);
				V(TT_NET, "[ARP][%s] ", htons(arp_hdr->opcode) == 1 ? "REQ" : "REP");
				V(TT_NET, "dst("MACSTR"), src("MACSTR")\n", MAC2STR(ethhdr->dest.addr), MAC2STR(ethhdr->src.addr));
				#if LWIP_BRIDGE
				u32 target_ip_addr = (arp_hdr->dipaddr.addrw[1] << 16) | arp_hdr->dipaddr.addrw[0];
				#endif /* LWIP_BRIDGE */
				if (!intf->is_ap) { // br0 mac == wlan0 mac
					if (htons(arp_hdr->opcode) == 1) { // ARP Request
						if (!os_memcmp(arp_hdr->shwaddr.addr, netif->hwaddr, 6)) {
							goto pbuf_free;
						} else {
							if (!(ethhdr->dest.addr[0] & 1)
							#if LWIP_BRIDGE
								&& target_ip_addr != br_netif.ip_addr.addr
							#endif /* LWIP_BRIDGE */
								) {
								memcpy(ethhdr->dest.addr, get_peer_mac()->addr, 6);
							}
						}
					} else { // ARP Reply
						if (!os_memcmp(arp_hdr->dhwaddr.addr, netif->hwaddr, 6)
							#if LWIP_BRIDGE
							&& target_ip_addr != br_netif.ip_addr.addr
							#endif /* LWIP_BRIDGE */
							) {
							memcpy(ethhdr->dest.addr, get_peer_mac()->addr, 6);
							memcpy(arp_hdr->dhwaddr.addr, get_peer_mac()->addr, 6);
						}
					}
				}
				goto next;
			}
#endif
#if PPPOE_SUPPORT
		/* PPPoE packet? */
		case ETHTYPE_PPPOEDISC:
		case ETHTYPE_PPPOE:
#endif /* PPPOE_SUPPORT */
		case ETHTYPE_IP:
#if LWIP_IPV6
		case ETHTYPE_IPV6:
#endif	//LWIP_IPV6
#if defined(SUPPORT_ETHERNET_ACCESSPOINT)
			if (!nrc_get_use_4address() &&
			    (nrc_eth_get_network_mode() == NRC_NETWORK_MODE_BRIDGE)) {
				ip_hdr = (struct ip_hdr *)(p->payload + SIZEOF_ETH_HDR);
				if (!intf->is_ap) { // br0 mac == wlan0 mac
					if (ip_hdr->dest.addr != 0 && ip_hdr->dest.addr != 0xffffffff
					#if LWIP_BRIDGE
						&& ip_hdr->dest.addr != br_netif.ip_addr.addr
					#endif /* LWIP_BRIDGE */
						) {
						memcpy(ethhdr->dest.addr, get_peer_mac()->addr, 6);
						}
				}
			}
	next:
#endif

#if STATIC_ARP_ENTRY_DHCP_SERVER
			{
				struct netif *dhcp_netif;
				dhcp_netif = nrc_netif_get_by_idx((intf->vif_id == 0) ? WLAN0_INTERFACE : BRIDGE_INTERFACE);
				if (dhcp_get_state(dhcp_netif) == DHCP_STATE_REQUESTING) {
					LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE, ("DHCP_STATE_REQUESTING %d\n", dhcp_get_state(dhcp_netif)));
					process_dhcp_ack(p);
				}
			}
#endif /* STATIC_ARP_ENTRY_DHCP_SERVER */

			/* full packet send to tcpip_thread to process */
			if (netif->input(p, netif)!=ERR_OK) {
				LWIP_DEBUGF(NETIF_DEBUG, ("ethernetif_input: IP input error\n"));
				goto pbuf_free;
			}
			break;

		default:
pbuf_free:
			pbuf_free(p);
			p = NULL;
			break;
	}
}
#include "standalone.h"

err_t wlif_init( struct netif *netif )
{
	LWIP_DEBUGF(NETIF_DEBUG, ("wlif_init\r\n"));

	LWIP_ASSERT("netif != NULL", (netif != NULL));

	#if LWIP_NETIF_HOSTNAME
	/* Initialize interface hostname */
	netif->hostname = "lwip";
	#endif /* LWIP_NETIF_HOSTNAME */

	/*
	* Initialize the snmp variables and counters inside the struct netif.
	* The last argument should be replaced with your link speed, in units
	* of bits per second.
	*/
	NETIF_INIT_SNMP(netif, snmp_ifType_ethernet_csmacd, 100);

	netif->name[0] = IFNAME0;
	netif->name[1] = IFNAME1;
	/* We directly use etharp_output() here to save a function call.
	* You can instead declare your own function an call etharp_output()
	* from it if you have to do some checks before sending (e.g. if link
	* is available...)
	*/
	#if LWIP_IPV4
	netif->output = etharp_output;
	#endif /* LWIP_IPV4 */
	#if LWIP_IPV6
	netif->output_ip6 = ethip6_output;
	#endif /* LWIP_IPV6 */
	netif->linkoutput = low_level_output;

	/* set MAC hardware address length to be used by lwIP */
	netif->hwaddr_len = 6;

	/* initialize the hardware */
	low_level_init(netif);

	return ERR_OK;
}
