#ifndef __DRV_MAC_H__
#define __DRV_MAC_H__
#include "system.h"

typedef struct {
    uint32_t    rx_count;
    int32_t     rx_avg_snr;
    int32_t     rx_avg_rssi;
    uint32_t    rx_avg_mcs;
    uint32_t    rx_dma_total_received_byte;
    uint32_t    tx_scheduled_count;
    uint32_t    tx_scheduled_success;
    uint32_t    tx_scheduled_fail;
    uint32_t    tx_scheduled_byte;
    uint32_t    tx_done_total_byte;
    uint8_t     max_hw_received_desc_count;
} mac_stats_t;

typedef enum {
    DRV_MAC_SEND_RESULT_SUCCESS, // SYNC : Received ACK , ASYNC : Buffered
    DRV_MAC_SEND_RESULT_FAIL, // SYNC Fail
    DRV_MAC_SEND_RESULT_BUSY, // ASYNC Fail
    DRV_MAC_SEND_RESULT_NOBUFFER // ASYNC Fail
} send_result_t;

typedef void (*tbtt_handler_cb_t)(void);

enum {
	SEGMENT_SINGLE = 0,
	SEGMENT_LAST,
	SEGMENT_FIRST,
	SEGMENT_MID,
};

enum {
	MAX_KEY_ID              = 4,
	MAX_KEY_LEN             = 4,
	WEP_IV_LEN              = 4,
	CIPHER_HEADER_LEN       = 8,
	CIPHER_HEADER_LEN_WEP   = 4,
	CIPHER_HEADER_LEN_WAPI  = 18,
	MIC_LEN                 =  8,
	MIC_LEN_WAPI            = 16,
	ICV_LEN	                = 4,
	FCS_SIZE                = 4,
	DELIMITER_SIZE          = 4,
	MGMT_HEADER_SIZE        = 24,
	CFO_WINDOW_SIZE         = 16,
};

enum {
	CIP_WEP40 = 0,
	CIP_WEP104 = 1,
	CIP_TKIP = 2,
	CIP_CCMP = 3,
	CIP_WAPI = 4,
	CIP_MAX = 5,
	CIP_NONE = CIP_MAX,
};

typedef enum {
    OWNER_SW = 0,
    OWNER_HW = 1
} owner_t;

typedef enum {
    S1G,
    S1G_DUP_1M,
    S1G_DUP_2M
} s1g_format_t;

typedef enum {
    S1G_SHORT,
    S1G_LONG
} s1g_preamble_t;

typedef enum {
    RID_NO_RESPONSE = 0,
    RID_NDP_RESPONSE,
    RID_NORMAL_RESPONSE,
    RID_LONG_RESPONSE
} rid_t;

typedef enum {
    CODING_BCC = 2,
    CODING_LDPC = 3
} coding_t;

typedef enum {
    ACK_POLICY_ACK,
    ACK_POLICY_NOACK,
} ackpolicy_t;

typedef enum {
    GI_LONG,
    GI_SHORT
} gi_t;


typedef struct _SigS1G1M {
    /* sig bit pattern LSB -> MSB */
    uint32_t nsts               : 2;        /* 0=1 space time stream, 1=2 space time stream, etc. */
    uint32_t short_gi           : 1;        /* 0 for no use of short guard interval, otherwise 1 */
    uint32_t coding             : 2;        /* x0=BCC, x1=LDPC */
    uint32_t stbc               : 1;        /* 0=no spatial streams has STBC, 1=all spatial streams has STBC */
    uint32_t reserved2          : 1;
    uint32_t mcs                : 4;
    uint32_t aggregation        : 1;        /* 1 for aggregation */
    uint32_t length             : 9;        /* PPDU length in symbols in case of aggregation, otherwise, byte length */
    uint32_t response_ind       : 2;        /* 0=no rsp, 1=NDP rsp, 2=normal rsp, 3=long rsp */
    uint32_t smoothing          : 1;        /* 1 for recommending channel smoothing */
    uint32_t doppler            : 1;        /* 0=regular pilot tone, 1=traveling pilots */
    uint32_t ndp_ind            : 1;        /* 1 for NDP */
    uint32_t crc                : 4;        /* for TX use (CRC calulation for S1G SIGA fields) */
    uint32_t reserved1          : 2;

    uint32_t magic_code_3       : 8;
    uint32_t magic_code_2       : 8;
    uint32_t magic_code_1       : 8;
    uint32_t magic_code_0       : 8;
} SigS1G1M;

/* SIG for S1G SHORT */
typedef struct _SigS1GShort {
    /* sig bit pattern LSB -> MSB */
    uint32_t reserved2          : 1;
    uint32_t stbc               : 1;
    uint32_t uplink_ind         : 1;    /* set to the value of TXVECTOR parameter UPLINK_INDICATION */
    uint32_t bandwidth          : 2;    /* 0:2M, 1:4M, 2:8M, 3:16M */
    uint32_t nsts               : 2;
    uint32_t id                 : 9;
    uint32_t short_gi           : 1;
    uint32_t coding             : 2;
    uint32_t mcs                : 4;
    uint32_t smoothing          : 1;
    uint32_t reserved1          : 8;

    uint32_t aggregation        : 1;
    uint32_t length             : 9;
    uint32_t response_ind       : 2;
    uint32_t doppler            : 1;
    uint32_t ndp_ind            : 1;
    uint32_t crc                : 4;    /* for TX use */
    uint32_t reserved3          : 14;

} SigS1GShort;

/* SIG for S1G LONG */
typedef struct _SigS1GLong {

    /* sig bit pattern LSB -> MSB */
    uint32_t mu_su              : 1;
    uint32_t stbc               : 1;
    uint32_t uplink_ind         : 1;
    uint32_t bandwidth          : 2;    /* 0:2M, 1:4M, 2:8M, 3:16M */
    uint32_t nsts               : 2;
    uint32_t id                 : 9;
    uint32_t short_gi           : 1;
    uint32_t coding             : 2;
    uint32_t mcs                : 4;
    uint32_t smoothing          : 1;
    uint32_t reserved1          : 8;

    uint32_t aggregation        : 1;
    uint32_t length             : 9;
    uint32_t response_ind       : 2;
    uint32_t reserved3          : 1;
    uint32_t doppler            : 1;
    uint32_t crc                : 4;    /* for TX use */
    uint32_t reserved2          : 14;
} SigS1GLong;



typedef union {
    SigS1G1M     s1g_1m;
    SigS1GShort  s1g_short;
    SigS1GLong   s1g_long;
    uint32_t w[2];
} SIG_U;

typedef struct {
    // RXVECTOR #0
    uint32_t format         : 2;
    uint32_t preamble_type  : 1;
    uint32_t reserved1      : 1;
    uint32_t bandwidth      : 2;
    uint32_t reserved2      : 1;
    uint32_t obss_indication: 1;
    uint32_t length    : 20;
    uint32_t reserved3      : 4;

    // RXVECTOR #1
    uint32_t scrambler_or_crc   : 7;
    uint32_t reserved4     		: 9;
    uint32_t snr                : 6;
    uint32_t reserved5          : 10;

    // RXVECTOR #2
    uint32_t rcpi           : 8;
    uint32_t rssi           : 8;
    uint32_t cfo_estimate   : 13;
    uint32_t reserved6      : 3;
} RXVECTOR;

typedef union {
    RXVECTOR b;
    uint32_t w[3];
} RXVECTOR_U;

typedef struct {
    // RXINFO #0
    uint32_t mpdu_length    	: 14;
    uint32_t reserved0      	: 10;
    uint32_t counter_mpdu   	: 8;
    // RXINFO #1
    uint32_t tid                : 4;
    uint32_t reserved1          : 9;
    uint32_t rxfull             : 1;
    uint32_t rid_ind            : 2;
    uint32_t ack_policy         : 1;
    uint32_t nav_check          : 1;
    uint32_t error_all_delim    : 1;
    uint32_t eof_ind            : 1;
    uint32_t obss_frame         : 1;
    uint32_t ndp_ind            : 1;
    uint32_t long_2m_ind        : 1;
    uint32_t aggregation        : 1;
    uint32_t error_mic          : 1;
    uint32_t error_key          : 1;
    uint32_t protection         : 1;
    uint32_t error_length       : 1;
    uint32_t error_match        : 1;
    uint32_t error_crc          : 1;
    uint32_t okay               : 1;
    uint32_t error_seq          : 1;
    // RXINFO #2
    uint32_t timestamp;
    // RXINFO #3
    uint32_t fcs;
} RXINFO;

typedef union {
    RXINFO b;
    uint32_t w[4];
} RXINFO_U;

typedef struct {
    // Word 0/1
    uint32_t    reserved0[2];
    // Word 2
	void        *next_mpdu;
	// Word 3
	void        *next_link;

    // Word 4 : BD info 0
    uint32_t    legacy_tsf_sym_ptr           : 6; 		 //number of data symbol right before the symbol containing first bit of TSF subfield
    uint32_t    ack_policy                   : 2;        // 00: Normal Ack, 01: No Ack
    uint32_t    cipher_type                  : 3;        // 0:wep40, 1:wep128, 2:tkip, 3:ccmp, 4:wapi
    uint32_t    rts_request                  : 1;
    uint32_t    cts_self_request             : 1;
    uint32_t    cf_end_request               : 1;
    uint32_t    reserved1	                 : 4;        // security key location
    uint32_t    timestamp_update             : 1;        // flag for updating timestamp in the frame
    uint32_t    timestamp_position           : 6;        // in byte, timestamp position in frame , in bit (when used in SBR TSF Update)
    uint32_t	bssid_idx                    : 2;
#if 0
    uint32_t	mac_idx                      : 2;
#else
	uint32_t	reserved2 					 : 2;
#endif
    uint32_t	sbr_tsf_update				 : 1;
    uint32_t 	sbr_segment					 : 2;

    // Word 5 : BD info 1
    uint32_t    rts_duration                 : 16;
#if 0
    uint32_t	key_location				 : 10;
#else
	uint32_t	reserved3					 : 10;
#endif
    uint32_t	key_search_en				 : 1;
    uint32_t	sbr_tsf_bit_ptr				 : 5;

    // Word 6 : BD info 2
    uint32_t    psdu_length                  : 20;       /////
    uint32_t    bcn_compatible_pos           : 6;
    uint32_t    bcn_compatible_update        : 1;
    uint32_t    tetra_partial_tsf_update     : 1;
    uint32_t    penta_partial_tsf_update     : 1;

    uint32_t	sbr_start					 : 1; //
    uint32_t	sbr_embedded_bssid_en		 : 1; //
    uint32_t	reserved4					 : 1;

    // Word 7 : BD info 3
    uint32_t    mpdu_length                 : 14;
    uint32_t    ampdu_segment               : 2;        // 00:single, 10:first, 11:middle, 01:last
    uint32_t    mac_header_length           : 11;
#if 0
    uint32_t    ampdu_spacing               : 5;
#else
	uint32_t	reserved5					: 5;
#endif

    // Word 8 : BD info 4
    uint32_t    rate_index	                : 8;    // LMAC FW use only, Used for Rate Control
    uint32_t    data_length                 : 11;   // data length
    uint32_t    segment                     : 2;    // MPDU segmentation
    uint32_t    qos_null_pm1_ack            : 2;	// ack for qos_null frame with pm1 bit. (0: wait, 1: success, 2: fail)
    uint32_t    reserved6                   : 1;
    uint32_t    ac                          : 4;// LMAC FW use only, Assigned Queue Manager ID
    uint32_t    tx_count                    : 4;    // LMAC FW use only, check whether it exceeds retry limit

} TXBD;

typedef struct _TXVECTOR{
	// Exist only at first fragment (segment == 2'b01)
	// Vector
	uint32_t format         : 2;        // 0=S1G, 1=S1G_DUP_1M, 2=S1G_DUP_2M
	uint32_t bandwidth      : 2;        // 0=1M, 1=2M, 2=4M, 3=8M
	uint32_t preamble       : 1;        // 0=S1G_SHORT, 1=S1G_LONG
	uint32_t scrambler      : 7;
	uint32_t scrambler_exist: 1;
	uint32_t tx_pwr_level   : 8;
	uint32_t service_rsvd	: 1;
	uint32_t sbr_mode		: 1; // 0: 11ah Legacy PPDU , 1: SBR PPDU
	uint32_t sbr_rate		: 1; // 0 :LDR , 1 : HDR
	uint32_t sbr_byte_length : 7; // Number of data byte exepct SYNC bits
	uint32_t ndp_page_en	: 1; // MAC H/W Internal use
} TXVECTOR;

typedef struct {
    TXBD        bd;
    TXVECTOR    vector;
    SIG_U       sig;
    uint8_t     mpdu[0];
} MACHW_TX_BUFFER;

typedef enum {
    TX_INDIR_STATUS_START   =   0,
    TX_PSDU_COUNT           =   0,
    TX_MPDU_COUNT           =   1,
    TX_LENGTH_MISMATCH_COUNT =  2,
    TX_SBR_COUNT_CTS_COUNT  = 12,
    TX_CCA_SAMPLE           =   61,
    TX_CCA_1M               =   63,
    TX_CCA_2M               =   64,
    TX_CCA_2M_SEC           =   65,
    TX_INDIR_STATUS_END     =   100,
    RX_INDIR_STATUS_START,
    RX_RDI_NORMAL           =   1       + RX_INDIR_STATUS_START,
    RX_PSDU_RECEIVE         =   2       + RX_INDIR_STATUS_START,
    RX_MPDU_RECEIVE         =   3       + RX_INDIR_STATUS_START,
    RX_MPDU_SUCCESS         =   4       + RX_INDIR_STATUS_START,
    RX_MPDU_CRC_ERROR       =   5       + RX_INDIR_STATUS_START,
    RX_ABORT                =   9       + RX_INDIR_STATUS_START,
    RX_BUFFER_SHORTAGE      =   16      + RX_INDIR_STATUS_START,
    RX_DELIMETER_CRC_ERROR  =   41      + RX_INDIR_STATUS_START,
    RX_INDIR_STATUS_END     =   100     + RX_INDIR_STATUS_START
} drv_mac_status_t;

uint32_t drv_mac_get_status( drv_mac_status_t item);

#define MAC_STATUS( n , r )\
    static uint32_t n , n##_old;\
    n = r - n##_old;\
    n##_old = r;

#define MAC_STATUS16( n , r )\
    static uint16_t n , n##_old;\
    n = r - n##_old;\
    n##_old = r;

#define MAC_STATUS_ONE( n , r , f)\
    static uint32_t n;\
    reg = READ_REG( r );\
    n   = GET_FIELD( r , f , reg );\

#define MAC_STATUS_INDIR( n , a ) \
    static uint32_t __attribute__((__unused__)) n , n##_old;\
    {uint32_t reg = drv_mac_get_status(a); \
    n = reg - n##_old;\
    n##_old = reg; }


typedef struct {
    bw_t            mac_packet_bw;
    s1g_format_t    mac_packet_format;
    s1g_preamble_t  mac_packet_preamble;
    uint8_t         mac_packet_txpwr_index;
    uint8_t         mac_packet_scrambler;
    rid_t           mac_packet_rid;
    uint8_t         mac_packet_uplink_ind;
    uint8_t         mac_packet_color_id;
    bool            mac_packet_doppler;
    gi_t            mac_packet_gi;
    uint8_t         mac_packet_mcs;
    uint16_t        mac_packet_length;
    bool            mac_packet_ignore_sec2m;
} packet_config_t;


void drv_mac_print_rx_sig_vector(SIG_U *s , RXVECTOR_U *v);
void drv_mac_print_rxinfo(RXINFO_U *v);
void drv_mac_print_rxmpdu(uint32_t *p);

#define SBR_TYPE_BEACON 0
#define SBR_TYPE_WAKEUP 1
#define SBR_TYPE_SHORT_WAKEUP 2
#define SBR_TYPE_DATA_WAKEUP 3

#define SBR_SUBTYPE_CONTROL_DUTY 0
#define SBR_SUBTYPE_CONTROL_TBTT 1
#define SBR_SUBTYPE_CONTROL_THRESHOLD 2
#define SBR_SUBTYPE_GENERAL 7

typedef struct _SBR_Beacon{
	uint32_t	id 			: 18;
	uint32_t	type		: 2;
	uint32_t	cont		: 1;
	uint32_t	tsf			: 11;
} SBR_Beacon;

typedef struct _SBR_Wakeup {
	uint32_t	id 			: 18;
	uint32_t	type		: 2;
	uint32_t	cont		: 1;
	uint32_t	body_present: 1;
	uint32_t	length      : 7;
	uint32_t	reserved    : 3;
} SBR_Wakeup;

typedef struct _SBR_Short_Wakeup {
	uint32_t	id 			: 18;
	uint32_t	type		: 2;
	uint32_t	cont		: 1;
	uint32_t	reserved    : 3;
} SBR_Short_Wakeup;

typedef struct _SBR_Data_Wakeup {
	uint32_t	id 			: 18;
	uint32_t	type		: 2;
	uint32_t	cont		: 1;
	uint32_t	body_present: 1;
	uint32_t	length      : 7;
	uint32_t	subtype     : 3;
    uint8_t     body [127];
} SBR_Data_Wakeup;

#if defined(SBR_TX)
typedef struct _BUF_SBR_Beacon {
	MACHW_TX_BUFFER hdr; // 4 word + TX BD 5 word + Vector 1 word + SIG 2 word.
	SBR_Beacon data;
} BUF_SBR_Beacon;
typedef struct _BUF_SBR_Wakeup {
	MACHW_TX_BUFFER hdr; // 4 word + TX BD 5 word + Vector 1 word + SIG 2 word.
	SBR_Wakeup data;
} BUF_SBR_Wakeup;
typedef struct _BUF_SBR_Short_Wakeup {
	MACHW_TX_BUFFER hdr; // 4 word + TX BD 5 word + Vector 1 word + SIG 2 word.
	SBR_Short_Wakeup data;
} BUF_SBR_Short_Wakeup;
typedef struct _BUF_SBR_Data_Wakeup {
	MACHW_TX_BUFFER hdr; // 4 word + TX BD 5 word + Vector 1 word + SIG 2 word.
	SBR_Data_Wakeup data;
} BUF_SBR_Data_Wakeup;
#endif

#if defined(SBR_RX) || defined(SBR_TX)
typedef struct {
    uint32_t    wkup_mode;
    uint32_t    soc_wkup_count;
    uint32_t    id_match_count;
    uint32_t    id_mismatch_count;
    uint32_t    type_0_count;
    uint32_t    type_1_count;
    uint32_t    type_2_count;
    uint32_t    type_3_count;
    uint32_t    fcs_okay_count;
    uint32_t    fcs_err_count;
    uint32_t    sbr_wkup_count;
    uint32_t    ldr_sync_count;
    uint32_t    hdr_sync_count;
} sbr_mac_stats_t;
typedef struct {
    uint16_t        tsf_offset;
    int16_t         sbr_en_offset;
    uint16_t        sbr_interval;
    uint16_t        wakeup_reason;
    uint16_t        fail_wakeup_count;
    uint16_t        rtc_wakeup_count;
    uint32_t        wkup_margin_in_us;
    uint32_t        svc_period_in_us;

    sbr_mac_stats_t sbr_mac_stats;
} sbr_mac_info_t;
#endif


typedef struct {
    uint32_t tx_cs_time;            // us unit
    uint32_t tx_pause_time;         // us unit
    uint32_t tx_continous_time;     // us unit
    bool     valid;
} lbt_param_t;

typedef struct {

} duty_param_t;

typedef struct {
    lbt_param_t     lbt_param;
    uint16_t        aifsn_lower;
    uint16_t        aifsn_upper;
    uint16_t        tx_count_after_cs;
} lbt_info_t;
typedef struct {
    duty_param_t    duty_param;
} duty_info_t;
typedef struct {
#if defined(SBR_RX) || defined(SBR_TX)
    sbr_mac_info_t sbr_mac_info;
#endif
    lbt_info_t  lbt_info;
    duty_info_t duty_info;
} drv_mac_info_t;

extern drv_mac_info_t *drv_mac_info;

void            drv_mac_init();
void            drv_mac_stop();
void            drv_mac_show(uint8_t mode , bool rst);
void            drv_mac_save_now();
void            drv_mac_load_now();
void            drv_mac_set_tsf(uint32_t h , uint32_t l);
void            drv_mac_set_rx_debug_flag(uint8_t flag);
send_result_t   drv_mac_send_mpdu(uint8_t* mpdu, uint32_t mpdu_len, ac_t ac , bool sync_flag);

#if defined(SBR_TX)
send_result_t   drv_mac_send_sbr_frame(uint8_t* mpdu , uint32_t mpdu_len , ac_t ac , bool sync_flag , MACHW_TX_BUFFER* sbr_frame , uint32_t sbr_byte_length);
#endif

void            drv_mac_set_bcn_interval(uint32_t bcn_interval);
void            drv_mac_set_tbtt_handler_cb( tbtt_handler_cb_t cb);
int32_t         drv_mac_get_tsf_offset();
void            drv_mac_set_tsf_offset(int32_t offset);

void            drv_mac_delay_us(uint32_t us);

mac_stats_t*    drv_mac_get_stats();
packet_config_t*    drv_mac_get_packet_config();

void            WIFI0_Handler();


void            drv_mac_lbt_config(bool valid , uint32_t cs_time , uint32_t pause_time , uint32_t tx_time );


#endif
