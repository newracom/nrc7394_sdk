#ifndef WIFI_REGS_H
#define WIFI_REGS_H
#define MAC_REG_VER 1
#define MAC_REG_SIZE 4
/*------------------------------------------------------------------------------------------------------------------------------------
=================================================================================
Module Name  : mac_register_bank
File Name    : mac_reg_bank.v
Register Num : 397
=================================================================================
---------------------------------------------------------------------------------
    Address  : 0x40080000
    Name     : RST_SW
    Bit      : 1
    R/W      : R/W
---------------------------------------------------------------------------------
   [    0]    RST_SW                        R/W  default = 1
               -Write 0 and Write 1 will reset MAC state


---------------------------------------------------------------------------------
    Address  : 0x40080004
    Name     : CONFIG
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   + separate
---------------------------------------------------------------------------------
   [   31]    IRQ_CLEAR_MODE                R/W  default = 0

   [   30]    PV1_PAYLOAD_SHIFT_RX          R/W  default = 0

   [   29]    BITMAP_PROTECT_EN             R/W  default = 1
               -Enables a NDP BA Bitmap protection

   [   26]    RX_BUFFER_LOOKUP_IRQ_EN       R/W  default = 0
               -Valid only if LOOKUP_EN bit of CONFIG register is enabled
                 0 : IRQ OFF
                 1 : IRQ ON

   [   25]    RX_BUFFER_LOOKUP_MODE_TYPE    R/W  default = 1
                 0 : When hardware detects Rx buffer shortage, it attempts to transfer receiving MPDU to RX DMA even though there's not enough buffer(doesn't generate ACK)
                 1 : When a hardware detects RX buffer shortage, it discards received one(doesn't generate ACK)

   [   24]    RX_BUFFER_LOOKUP_EN           R/W  default = 1

   [23:16]    US_CLOCK                      R/W  default = 8

   [   13]    ENCR_MIC_SELECTED             R/W  default = 0

   [   12]    RECV_MIC_REMAIN               R/W  default = 0

   [11: 8]    AIFSN_UPPER                   R/W  default = 0

   [ 7: 6]    TX_PD_CONFIG                  R/W  default = 0
               -Tx power down config

   [    5]    PD_MAC_RX_TOP                 R/W  default = 0

   [    4]    PD_MAC_LOOPBACK               R/W  default = 0

   [    2]    RX_DMA_PROMISCUOUS_MODE       R/W  default = 0
                 0 : OFF: MPDU with Rx CRC error cannot be transferred to Memory
                 1 : ON : MPDU with Rx CRC error can be transferred to Memory. This mode is used for Monitor & debugging

   [    1]    CCA_IGNORE                    R/W  default = 0
               -Transmit without carrier sensing

   [    0]    MAC_LOOPBACK                  R/W  default = 0


---------------------------------------------------------------------------------
    Address  : 0x40080008
    Name     : SIFS_DURATION
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    SIFS_DURATION                 R/W  default = 95
               -SIFS Duration with usec unit


---------------------------------------------------------------------------------
    Address  : 0x4008000c
    Name     : SLOT_DURATION
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    SLOT_DURATION                 R/W  default = 52
               -Slot Duration with usec unit


---------------------------------------------------------------------------------
    Address  : 0x40080010
    Name     : TXPWR_POST_DELAY_CLOCK
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    TXPWR_POST_DELAY_CLOCK        R/W  default = 0


---------------------------------------------------------------------------------
    Address  : 0x40080014
    Name     : CRASH
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    CRASH                         R/W  default = 0


---------------------------------------------------------------------------------
    Address  : 0x40080018
    Name     : TX_RESPONSE_CONTROL
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    TX_RESPONSE_CONTROL           R/W  default = 0


---------------------------------------------------------------------------------
    Address  : 0x4008001c
    Name     : OPERATION_BAND
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    OPERATION_BAND                R/W  default = 0
               -Reserved


---------------------------------------------------------------------------------
    Address  : 0x40080020
    Name     : TXPPDU_DELAY_CLOCK
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [29:20]    FILTER_DELAY2                 R/W  default = 425

   [19:10]    FILTER_DELAY1                 R/W  default = 351

   [ 9: 0]    FILTER_DELAY0                 R/W  default = 275
               -TXPPDU post delay clock. Delay to align from the end of TXPPDU to the end of CCA (128clock = 3.2usec)


---------------------------------------------------------------------------------
    Address  : 0x40080024
    Name     : READY_BEFORE_TXPPDU_CLOCK
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    READY_BEFORE_TXPPDU_CLOCK     R/W  default = 200
               -Preparation time prior to actual transmit time.
               -Setting 160(4usec) means that transmit decision is made 4usec before last backoff slot time.
               -Within this time, H/W read transmits information and passes Tx vector to PHY


---------------------------------------------------------------------------------
    Address  : 0x40080028
    Name     : READY_TO_TXPOWER_CLOCK
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [29:20]    READY_TO_TXPOWER_CLOCK_1M     R/W  default = 141
               -Time gap between transmit decision time and Tx power time (64clock = 1.6usec)

   [19:10]    READY_TO_TXPOWER_CLOCK_2M     R/W  default = 104
               -Time gap between transmit decision time and Tx power time (64clock = 1.6usec)

   [ 9: 0]    READY_TO_TXPOWER_CLOCK_4M     R/W  default = 65
               -Time gap between transmit decision time and Tx power time (64clock = 1.6usec)


---------------------------------------------------------------------------------
    Address  : 0x4008002c
    Name     : TXPOWER_TO_TXREQUEST_CLOCK
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    TXPOWER_TO_TXREQUEST_CLOCK    R/W  default = 16
               -Time gap between Tx power time and Tx request time


---------------------------------------------------------------------------------
    Address  : 0x40080030
    Name     : RESPONSE_TIMEOUT_US
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    RESPONSE_TIMEOUT_US           R/W  default = 840
               -Response timeout duration after transmitting packet except 11b
               -SIFS + SLOT + RXPhyStartDelay(25us at OFDM)


---------------------------------------------------------------------------------
    Address  : 0x40080034
    Name     : CONFIG_EXT
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   + separate
---------------------------------------------------------------------------------
   [21:16]    SEARCH_FIELD_TIMEOUT          R/W  default = 6

   [   14]    BACKOFF_FINE_TUNE             R/W  default = 1

   [   13]    MPDU_FCS                      R/W  default = 0

   [   12]    SIFS_TIMEOUT_EN               R/W  default = 0
               -Enable SIFS timeout mode for RAW

   [11: 8]    RESP_MOREDATA_MODE            R/W  default = 15
               -Each bit represents availability of moredata flag setting when it responds with below frames
               -[3]: ACK/BA
               -[2]: TACK/STACK/BAT
               -[1]: NDP ACK
               -[0]: NDP PSPOLL ACK

   [ 7: 6]    SNR_FEEDBACK_EN               R/W  default = 0
               -[1]: Enable SNR Feedback for interface 1
               -[0]: Enable SNR Feedback for interface 0

   [    5]    NDP_PAGING_WAKEUP             R/W  default = 0
               -IRQ Generated if it receives my NDP Paging

   [    4]    TWT_RESPONDER_EN              R/W  default = 0
                 1 : Operates as a TWT Responder

   [ 3: 0]    RX_REG_INTF_CTRL              R/W  default = 0
                 4 : Generates additional interrupt when it receives every packets


---------------------------------------------------------------------------------
    Address  : 0x40080038
    Name     : STA_FILTER_MODE
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   - Add additional filtering rule to default principle.
   - Each bit represents detailed rule. It is a kind of amendment applied to current rule of standard
   [   12]    RX_MY_NDP_PAGING              R/W  default = 0

   [   11]    RX_NDP_PROBE_REQ              R/W  default = 0

   [   10]    RX_ALL                        R/W  default = 0
               -All of received frames

   [    9]    RX_PV1_FRAME                  R/W  default = 0
               -All of received PV1 frames

   [    8]    RX_CONTROL_FRAME              R/W  default = 0
               -All of control frames

   [    7]    RX_MANAGEMENT_FRAME           R/W  default = 0
               -All of management frames

   [    6]    RX_GROUP_ADDRESSED            R/W  default = 0
               -Group addressed frames

   [    5]    RX_ALL_NDP_FRAME              R/W  default = 0
               -All of NDP frames

   [    4]    RX_MY_CONTROL_FRAME           R/W  default = 0

   [    3]    RX_MY_NDP_FRAME               R/W  default = 0

   [    2]    RX_MY_ACK_FRAME               R/W  default = 0
               -Address matched Ack realted frames

   [    1]    RX_MY_IDLE_INDICATION         R/W  default = 0

   [    0]    RX_MY_PM_BIT_FRAME            R/W  default = 0
               -Address matched and power management enabled frames
                 0 : Disalbe
                 1 : Enable


---------------------------------------------------------------------------------
    Address  : 0x4008003c
    Name     : INTF_CFG_ACTIVE_BITMAP
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   + separate
---------------------------------------------------------------------------------
   [27:24]    AID_INTF_CFG                  R/W  default = 0
               -Each bit represents interface ID of AID set

   [23:20]    MACADDR_INTF_CFG              R/W  default = 0
               -Each bit represents interface ID of MAC Address

   [19:16]    BSS_INTF_CFG                  R/W  default = 0
               -Each bit represents interface ID of BSS

   [11: 8]    BSSID_MODE                    R/W  default = 0
               -Each bit represents operating mode of device in designated BSS
               -[3]: Station mode of BSS3
               -[2]: Station mode of BSS2
               -[1]: Station mode of BSS1
               -[0]: Station mode of BSS0
                 0 : STA
                 1 : AP

   [ 7: 4]    MACADDR_ENABLE                R/W  default = 1
               -Each bit represents activeness of MAC Address
               -Firmware shall activate for using MAC Address
               -[3]: Active state of MAC Address3
               -[2]: Active state of MAC Address2
               -[1]: Active state of MAC Address1
               -[0]: Active state of MAC Address0
                 0 : Inactive
                 1 : Active

   [ 3: 0]    BSS_ENABLE                    R/W  default = 0
               -Each bit represents activeness of BSS
               -Firmware shall make it active when it accomplishes its association with counterpart
               -[3]: Active state of BSS3
               -[2]: Active state of BSS2
               -[1]: Active state of BSS1
               -[0]: Active state of BSS0
                 0 : Inactive
                 1 : Active


---------------------------------------------------------------------------------
    Address  : 0x40080040
    Name     : SIFS_TIMEOUT
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   + separate
---------------------------------------------------------------------------------
   [15: 0]    SIFS_TIMEOUT_US               R/W  default = 160
               -Represents timeout value of SIFS transmit
               -Valid only if SIFS_TIMEOUT_CONFIG is enabled


---------------------------------------------------------------------------------
    Address  : 0x40080044
    Name     : STA_BSSID0_LOWER
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    STA_BSSID0_LOWER              R/W  default = 0
               -Lower 32bit width BSSID of the BSS0 where the device is associated with


---------------------------------------------------------------------------------
    Address  : 0x40080048
    Name     : STA_BSSID0_UPPER
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    STA_BSSID0_UPPER              R/W  default = 0
               -Upper 16bit width BSSID of the BSS0 where the device is associated with


---------------------------------------------------------------------------------
    Address  : 0x4008004c
    Name     : STA_BSSID1_LOWER
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    STA_BSSID1_LOWER              R/W  default = 0
               -Lower 32bit width BSSID of the BSS1 where the device is associated with


---------------------------------------------------------------------------------
    Address  : 0x40080050
    Name     : STA_BSSID1_UPPER
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    STA_BSSID1_UPPER              R/W  default = 0
               -Upper 16bit width BSSID of the BSS1 where the device is associated with


---------------------------------------------------------------------------------
    Address  : 0x40080054
    Name     : STA_BSSID2_LOWER
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    STA_BSSID2_LOWER              R/W  default = 0
               -Lower 32bit width BSSID of the BSS2 where the device is associated with


---------------------------------------------------------------------------------
    Address  : 0x40080058
    Name     : STA_BSSID2_UPPER
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    STA_BSSID2_UPPER              R/W  default = 0
               -Upper 16bit width BSSID of the BSS2 where the device is associated with


---------------------------------------------------------------------------------
    Address  : 0x4008005c
    Name     : STA_BSSID3_LOWER
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    STA_BSSID3_LOWER              R/W  default = 0
               -Lower 32bit width BSSID of the BSS3 where the device is associated with


---------------------------------------------------------------------------------
    Address  : 0x40080060
    Name     : STA_BSSID3_UPPER
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    STA_BSSID3_UPPER              R/W  default = 0
               -Upper 16bit width BSSID of the BSS3 where the device is associated with


---------------------------------------------------------------------------------
    Address  : 0x40080064
    Name     : MAC_ADDRESS0_LOWER
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    MAC_ADDRESS0_LOWER            R/W  default = 0
               -Lower 32bit width MAC Address0


---------------------------------------------------------------------------------
    Address  : 0x40080068
    Name     : MAC_ADDRESS0_UPPER
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    MAC_ADDRESS0_UPPER            R/W  default = 0
               -Upper 16bit width MAC Address0


---------------------------------------------------------------------------------
    Address  : 0x4008006c
    Name     : MAC_ADDRESS1_LOWER
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    MAC_ADDRESS1_LOWER            R/W  default = 0
               -Lower 32bit width MAC Address1


---------------------------------------------------------------------------------
    Address  : 0x40080070
    Name     : MAC_ADDRESS1_UPPER
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    MAC_ADDRESS1_UPPER            R/W  default = 0
               -Upper 16bit width MAC Address1


---------------------------------------------------------------------------------
    Address  : 0x40080074
    Name     : MAC_ADDRESS2_LOWER
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    MAC_ADDRESS2_LOWER            R/W  default = 0
               -Lower 32bit width MAC Address2


---------------------------------------------------------------------------------
    Address  : 0x40080078
    Name     : MAC_ADDRESS2_UPPER
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    MAC_ADDRESS2_UPPER            R/W  default = 0
               -Upper 16bit width MAC Address2


---------------------------------------------------------------------------------
    Address  : 0x4008007c
    Name     : MAC_ADDRESS3_LOWER
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    MAC_ADDRESS3_LOWER            R/W  default = 0
               -Lower 32bit width MAC Address3


---------------------------------------------------------------------------------
    Address  : 0x40080080
    Name     : MAC_ADDRESS3_UPPER
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    MAC_ADDRESS3_UPPER            R/W  default = 0
               -Upper 16bit width MAC Address3


---------------------------------------------------------------------------------
    Address  : 0x40080084
    Name     : STA_AID0_0
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    STA_AID0_0                    R/W  default = 0
               -Granted AID0 by the AP which has identical address stated in BSSID0 register of device


---------------------------------------------------------------------------------
    Address  : 0x40080088
    Name     : STA_AID0_1
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    STA_AID0_1                    R/W  default = 0
               -Granted AID1 by the AP which has identical address stated in BSSID0 register of device


---------------------------------------------------------------------------------
    Address  : 0x4008008c
    Name     : STA_AID0_2
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    STA_AID0_2                    R/W  default = 0
               -Granted AID2 by the AP which has identical address stated in BSSID0 register of device


---------------------------------------------------------------------------------
    Address  : 0x40080090
    Name     : STA_AID1_0
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    STA_AID1_0                    R/W  default = 0
               -Granted AID0 by the AP which has identical address stated in BSSID1 register of device


---------------------------------------------------------------------------------
    Address  : 0x40080094
    Name     : STA_AID1_1
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    STA_AID1_1                    R/W  default = 0
               -Granted AID1 by the AP which has identical address stated in BSSID1 register of device


---------------------------------------------------------------------------------
    Address  : 0x40080098
    Name     : STA_AID1_2
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    STA_AID1_2                    R/W  default = 0
               -Granted AID2 by the AP which has identical address stated in BSSID1 register of device


---------------------------------------------------------------------------------
    Address  : 0x4008009c
    Name     : STA_AID2_0
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    STA_AID2_0                    R/W  default = 0
               -Granted AID0 by the AP which has identical address stated in BSSID2 register of device


---------------------------------------------------------------------------------
    Address  : 0x400800a0
    Name     : STA_AID2_1
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    STA_AID2_1                    R/W  default = 0
               -Granted AID1 by the AP which has identical address stated in BSSID2 register of device


---------------------------------------------------------------------------------
    Address  : 0x400800a4
    Name     : STA_AID2_2
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    STA_AID2_2                    R/W  default = 0
               -Granted AID2 by the AP which has identical address stated in BSSID2 register of device


---------------------------------------------------------------------------------
    Address  : 0x400800a8
    Name     : STA_AID3_0
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    STA_AID3_0                    R/W  default = 0
               -Granted AID0 by the AP which has identical address stated in BSSID3 register of device


---------------------------------------------------------------------------------
    Address  : 0x400800ac
    Name     : STA_AID3_1
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    STA_AID3_1                    R/W  default = 0
               -Granted AID1 by the AP which has identical address stated in BSSID3 register of device


---------------------------------------------------------------------------------
    Address  : 0x400800b0
    Name     : STA_AID3_2
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    STA_AID3_2                    R/W  default = 0
               -Granted AID2 by the AP which has identical address stated in BSSID3 register of device


---------------------------------------------------------------------------------
    Address  : 0x400800b4
    Name     : DMA_BURST
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [11: 6]    DMA_BURST_MAX                 R/W  default = 16
               -Set the maximum beat of DMA Burst

   [ 5: 0]    DMA_BURST_MIN                 R/W  default = 1
               -Set the minimum beat of DMA Burst


---------------------------------------------------------------------------------
    Address  : 0x400800b8
    Name     : DMA_READ_FIFO_ADJUST
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [   31]    DMA_READ_FIFO_REFRESH_SWITCH  R/W  default = 0

   [27:20]    DMA_READ_FIFO_REFRESH_SIZE    R/W  default = 64
               -The number of slot to set the size of read fifo in dma module after every read operation

   [ 7: 0]    DMA_READ_FIFO_FULL_ADJUST     R/W  default = 0
               -The number of slot to reduce the size of read fifo in dma module


---------------------------------------------------------------------------------
    Address  : 0x400800bc
    Name     : CONCURRENT_CONFIG_BITMAP
    Bit      : 11
    R/W      : R/W
---------------------------------------------------------------------------------
   [10: 0]    CONCURRENT_CONFIG_BITMAP      R/W  default = 1984
               -Configuration bitmap for concurrent queues


---------------------------------------------------------------------------------
    Address  : 0x400800c0
    Name     : TX_CONTROL_PARAMETER
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31:30]    RX_RESPONSE_CONTROL           R/W  default = 0
                 0 : Accept received frame as correct response frame only if Address matched and CRC succeed
                 1 : Accept received frame as correct response frame for any frame which CRC was succeed
                 2 : Accept received frame as correct response frame for any frame received during response timeout period

   [   29]    TX_ERROR_RECOVERY             R/W  default = 1
               -TX Control runs recovery process if PHY TX has been ended (TXPPDU signal goes down) while TX Control state is still processing

   [   28]    CCA_LATE_DETECTION            R/W  default = 1
               -TX Control runs recovery process after TX Ready when CCA has been detected before RF TX Power ON

   [27:20]    VECTOR_TIMEOUT                R/W  default = 64
               -16clock unit, default = 64x16 = 1024clock

   [19:16]    VECTOR_WAIT_TIME              R/W  default = 3
               -8clock unit, default = 3x8 = 24clock

   [15:12]    OTHER_FRAG_DATA_WORD_OFFSET   R/W  default = 0
               -Other Fragment Data word offset after 36byte(buffer header)

   [11: 8]    FIRST_FRAG_DATA_WORD_OFFSET   R/W  default = 7
               -First  Fragment Data word offset after 48byte(buffer header + vector)

   [ 7: 0]    RESPONSE_WAIT_TIME_US         R/W  default = 40
               -S/W Response wait timeout in us in 11ah


---------------------------------------------------------------------------------
    Address  : 0x400800c4
    Name     : RSP0
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   - This register describes which control frame to send as a response frame when frame is received
   - Received Not OK Frame : Send Nothing
   [   31]    RSP0_VALID                    R/W  default = 0

   [30:26]    RSP0_CASE                     R/W  default = 0

   [   25]    RSP0_MASK_RX_INFO_OK          R/W  default = 1

   [   24]    RSP0_MASK_RX_INFO_NDP         R/W  default = 0

   [   23]    RSP0_MASK_RX_NDP_PSPOLL       R/W  default = 0

   [22:21]    RSP0_MASK_RX_PV0_TYPE         R/W  default = 0

   [20:17]    RSP0_MASK_RX_PV0_SUBTYPE      R/W  default = 0

   [   16]    RSP0_MASK_RX_PV               R/W  default = 0

   [   15]    RSP0_MASK_GROUP_ADDRESS       R/W  default = 0

   [   14]    RSP0_MASK_OPERATION           R/W  default = 0

   [   13]    RSP0_MASK_RX_INFO_AGG         R/W  default = 0

   [   12]    RSP0_RX_INFO_OK               R/W  default = 0

   [   11]    RSP0_RX_INFO_NDP              R/W  default = 0

   [   10]    RSP0_RX_NDP_PSPOLL            R/W  default = 0

   [ 9: 8]    RSP0_RX_PV0_TYPE              R/W  default = 0
                 0 : MANAGEMENT
                 1 : CONTROL
                 2 : DATA

   [ 7: 4]    RSP0_RX_PV0_SUBTYPE           R/W  default = 0

   [    3]    RSP0_RX_PV                    R/W  default = 0

   [    2]    RSP0_GROUP_ADDRESS            R/W  default = 0

   [    1]    RSP0_OPERATION                R/W  default = 0
                 0 : STA
                 1 : AP

   [    0]    RSP0_RX_INFO_AGG              R/W  default = 0


---------------------------------------------------------------------------------
    Address  : 0x400800c8
    Name     : RSP1
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   - This register describes which control frame to send as a response frame when frame is received
   - Received NDP PS-POLL Frame : Send NDP_PSPOLL_ACK
   [   31]    RSP1_VALID                    R/W  default = 1

   [30:26]    RSP1_CASE                     R/W  default = 6

   [   25]    RSP1_MASK_RX_INFO_OK          R/W  default = 1

   [   24]    RSP1_MASK_RX_INFO_NDP         R/W  default = 1

   [   23]    RSP1_MASK_RX_NDP_PSPOLL       R/W  default = 1

   [22:21]    RSP1_MASK_RX_PV0_TYPE         R/W  default = 0

   [20:17]    RSP1_MASK_RX_PV0_SUBTYPE      R/W  default = 0

   [   16]    RSP1_MASK_RX_PV               R/W  default = 0

   [   15]    RSP1_MASK_GROUP_ADDRESS       R/W  default = 0

   [   14]    RSP1_MASK_OPERATION           R/W  default = 0

   [   13]    RSP1_MASK_RX_INFO_AGG         R/W  default = 0

   [   12]    RSP1_RX_INFO_OK               R/W  default = 1

   [   11]    RSP1_RX_INFO_NDP              R/W  default = 1

   [   10]    RSP1_RX_NDP_PSPOLL            R/W  default = 1

   [ 9: 8]    RSP1_RX_PV0_TYPE              R/W  default = 0
                 0 : MANAGEMENT
                 1 : CONTROL
                 2 : DATA

   [ 7: 4]    RSP1_RX_PV0_SUBTYPE           R/W  default = 0

   [    3]    RSP1_RX_PV                    R/W  default = 0

   [    2]    RSP1_GROUP_ADDRESS            R/W  default = 0

   [    1]    RSP1_OPERATION                R/W  default = 0
                 0 : STA
                 1 : AP

   [    0]    RSP1_RX_INFO_AGG              R/W  default = 0


---------------------------------------------------------------------------------
    Address  : 0x400800cc
    Name     : RSP2
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   - This register describes which control frame to send as a response frame when frame is received
   - Received Beacon Frame : Send Nothing
   [   31]    RSP2_VALID                    R/W  default = 1

   [30:26]    RSP2_CASE                     R/W  default = 0

   [   25]    RSP2_MASK_RX_INFO_OK          R/W  default = 1

   [   24]    RSP2_MASK_RX_INFO_NDP         R/W  default = 1

   [   23]    RSP2_MASK_RX_NDP_PSPOLL       R/W  default = 0

   [22:21]    RSP2_MASK_RX_PV0_TYPE         R/W  default = 3

   [20:17]    RSP2_MASK_RX_PV0_SUBTYPE      R/W  default = 15

   [   16]    RSP2_MASK_RX_PV               R/W  default = 1

   [   15]    RSP2_MASK_GROUP_ADDRESS       R/W  default = 0

   [   14]    RSP2_MASK_OPERATION           R/W  default = 0

   [   13]    RSP2_MASK_RX_INFO_AGG         R/W  default = 0

   [   12]    RSP2_RX_INFO_OK               R/W  default = 1

   [   11]    RSP2_RX_INFO_NDP              R/W  default = 0

   [   10]    RSP2_RX_NDP_PSPOLL            R/W  default = 0

   [ 9: 8]    RSP2_RX_PV0_TYPE              R/W  default = 0
                 0 : MANAGEMENT
                 1 : CONTROL
                 2 : DATA

   [ 7: 4]    RSP2_RX_PV0_SUBTYPE           R/W  default = 8

   [    3]    RSP2_RX_PV                    R/W  default = 0

   [    2]    RSP2_GROUP_ADDRESS            R/W  default = 0

   [    1]    RSP2_OPERATION                R/W  default = 0
                 0 : STA
                 1 : AP

   [    0]    RSP2_RX_INFO_AGG              R/W  default = 0


---------------------------------------------------------------------------------
    Address  : 0x400800d0
    Name     : RSP3
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   - This register describes which control frame to send as a response frame when frame is received
   - Received Action NoACK Frame : Send Nothing
   [   31]    RSP3_VALID                    R/W  default = 1

   [30:26]    RSP3_CASE                     R/W  default = 0

   [   25]    RSP3_MASK_RX_INFO_OK          R/W  default = 1

   [   24]    RSP3_MASK_RX_INFO_NDP         R/W  default = 1

   [   23]    RSP3_MASK_RX_NDP_PSPOLL       R/W  default = 0

   [22:21]    RSP3_MASK_RX_PV0_TYPE         R/W  default = 3

   [20:17]    RSP3_MASK_RX_PV0_SUBTYPE      R/W  default = 15

   [   16]    RSP3_MASK_RX_PV               R/W  default = 1

   [   15]    RSP3_MASK_GROUP_ADDRESS       R/W  default = 0

   [   14]    RSP3_MASK_OPERATION           R/W  default = 0

   [   13]    RSP3_MASK_RX_INFO_AGG         R/W  default = 0

   [   12]    RSP3_RX_INFO_OK               R/W  default = 1

   [   11]    RSP3_RX_INFO_NDP              R/W  default = 0

   [   10]    RSP3_RX_NDP_PSPOLL            R/W  default = 0

   [ 9: 8]    RSP3_RX_PV0_TYPE              R/W  default = 0
                 0 : MANAGEMENT
                 1 : CONTROL
                 2 : DATA

   [ 7: 4]    RSP3_RX_PV0_SUBTYPE           R/W  default = 14

   [    3]    RSP3_RX_PV                    R/W  default = 0

   [    2]    RSP3_GROUP_ADDRESS            R/W  default = 0

   [    1]    RSP3_OPERATION                R/W  default = 0
                 0 : STA
                 1 : AP

   [    0]    RSP3_RX_INFO_AGG              R/W  default = 0


---------------------------------------------------------------------------------
    Address  : 0x400800d4
    Name     : RSP4
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   - This register describes which control frame to send as a response frame when frame is received
   - Received Group Addressed Management  Frame : Send Nothing
   [   31]    RSP4_VALID                    R/W  default = 1

   [30:26]    RSP4_CASE                     R/W  default = 0

   [   25]    RSP4_MASK_RX_INFO_OK          R/W  default = 1

   [   24]    RSP4_MASK_RX_INFO_NDP         R/W  default = 1

   [   23]    RSP4_MASK_RX_NDP_PSPOLL       R/W  default = 0

   [22:21]    RSP4_MASK_RX_PV0_TYPE         R/W  default = 3

   [20:17]    RSP4_MASK_RX_PV0_SUBTYPE      R/W  default = 0

   [   16]    RSP4_MASK_RX_PV               R/W  default = 1

   [   15]    RSP4_MASK_GROUP_ADDRESS       R/W  default = 1

   [   14]    RSP4_MASK_OPERATION           R/W  default = 0

   [   13]    RSP4_MASK_RX_INFO_AGG         R/W  default = 0

   [   12]    RSP4_RX_INFO_OK               R/W  default = 1

   [   11]    RSP4_RX_INFO_NDP              R/W  default = 0

   [   10]    RSP4_RX_NDP_PSPOLL            R/W  default = 0

   [ 9: 8]    RSP4_RX_PV0_TYPE              R/W  default = 0
                 0 : MANAGEMENT
                 1 : CONTROL
                 2 : DATA

   [ 7: 4]    RSP4_RX_PV0_SUBTYPE           R/W  default = 0

   [    3]    RSP4_RX_PV                    R/W  default = 0

   [    2]    RSP4_GROUP_ADDRESS            R/W  default = 1

   [    1]    RSP4_OPERATION                R/W  default = 0
                 0 : STA
                 1 : AP

   [    0]    RSP4_RX_INFO_AGG              R/W  default = 0


---------------------------------------------------------------------------------
    Address  : 0x400800d8
    Name     : RSP5
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   - This register describes which control frame to send as a response frame when frame is received
   - Received Management  Frame : Send ACK
   [   31]    RSP5_VALID                    R/W  default = 1

   [30:26]    RSP5_CASE                     R/W  default = 1

   [   25]    RSP5_MASK_RX_INFO_OK          R/W  default = 1

   [   24]    RSP5_MASK_RX_INFO_NDP         R/W  default = 1

   [   23]    RSP5_MASK_RX_NDP_PSPOLL       R/W  default = 0

   [22:21]    RSP5_MASK_RX_PV0_TYPE         R/W  default = 3

   [20:17]    RSP5_MASK_RX_PV0_SUBTYPE      R/W  default = 0

   [   16]    RSP5_MASK_RX_PV               R/W  default = 1

   [   15]    RSP5_MASK_GROUP_ADDRESS       R/W  default = 0

   [   14]    RSP5_MASK_OPERATION           R/W  default = 0

   [   13]    RSP5_MASK_RX_INFO_AGG         R/W  default = 0

   [   12]    RSP5_RX_INFO_OK               R/W  default = 1

   [   11]    RSP5_RX_INFO_NDP              R/W  default = 0

   [   10]    RSP5_RX_NDP_PSPOLL            R/W  default = 0

   [ 9: 8]    RSP5_RX_PV0_TYPE              R/W  default = 0
                 0 : MANAGEMENT
                 1 : CONTROL
                 2 : DATA

   [ 7: 4]    RSP5_RX_PV0_SUBTYPE           R/W  default = 0

   [    3]    RSP5_RX_PV                    R/W  default = 0

   [    2]    RSP5_GROUP_ADDRESS            R/W  default = 0

   [    1]    RSP5_OPERATION                R/W  default = 0
                 0 : STA
                 1 : AP

   [    0]    RSP5_RX_INFO_AGG              R/W  default = 0


---------------------------------------------------------------------------------
    Address  : 0x400800dc
    Name     : RSP6
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   - This register describes which control frame to send as a response frame when frame is received
   - Received RTS Frame in STA Mode: Send CTS
   [   31]    RSP6_VALID                    R/W  default = 1

   [30:26]    RSP6_CASE                     R/W  default = 3

   [   25]    RSP6_MASK_RX_INFO_OK          R/W  default = 1

   [   24]    RSP6_MASK_RX_INFO_NDP         R/W  default = 1

   [   23]    RSP6_MASK_RX_NDP_PSPOLL       R/W  default = 0

   [22:21]    RSP6_MASK_RX_PV0_TYPE         R/W  default = 3

   [20:17]    RSP6_MASK_RX_PV0_SUBTYPE      R/W  default = 15

   [   16]    RSP6_MASK_RX_PV               R/W  default = 1

   [   15]    RSP6_MASK_GROUP_ADDRESS       R/W  default = 0

   [   14]    RSP6_MASK_OPERATION           R/W  default = 1

   [   13]    RSP6_MASK_RX_INFO_AGG         R/W  default = 0

   [   12]    RSP6_RX_INFO_OK               R/W  default = 1

   [   11]    RSP6_RX_INFO_NDP              R/W  default = 0

   [   10]    RSP6_RX_NDP_PSPOLL            R/W  default = 0

   [ 9: 8]    RSP6_RX_PV0_TYPE              R/W  default = 1
                 0 : MANAGEMENT
                 1 : CONTROL
                 2 : DATA

   [ 7: 4]    RSP6_RX_PV0_SUBTYPE           R/W  default = 11

   [    3]    RSP6_RX_PV                    R/W  default = 0

   [    2]    RSP6_GROUP_ADDRESS            R/W  default = 0

   [    1]    RSP6_OPERATION                R/W  default = 0
                 0 : STA
                 1 : AP

   [    0]    RSP6_RX_INFO_AGG              R/W  default = 0


---------------------------------------------------------------------------------
    Address  : 0x400800e0
    Name     : RSP7
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   - This register describes which control frame to send as a response frame when frame is received
   - Received RTS Frame in AP Mode: Send CTS
   [   31]    RSP7_VALID                    R/W  default = 1

   [30:26]    RSP7_CASE                     R/W  default = 4

   [   25]    RSP7_MASK_RX_INFO_OK          R/W  default = 1

   [   24]    RSP7_MASK_RX_INFO_NDP         R/W  default = 1

   [   23]    RSP7_MASK_RX_NDP_PSPOLL       R/W  default = 0

   [22:21]    RSP7_MASK_RX_PV0_TYPE         R/W  default = 3

   [20:17]    RSP7_MASK_RX_PV0_SUBTYPE      R/W  default = 15

   [   16]    RSP7_MASK_RX_PV               R/W  default = 1

   [   15]    RSP7_MASK_GROUP_ADDRESS       R/W  default = 0

   [   14]    RSP7_MASK_OPERATION           R/W  default = 1

   [   13]    RSP7_MASK_RX_INFO_AGG         R/W  default = 0

   [   12]    RSP7_RX_INFO_OK               R/W  default = 1

   [   11]    RSP7_RX_INFO_NDP              R/W  default = 0

   [   10]    RSP7_RX_NDP_PSPOLL            R/W  default = 0

   [ 9: 8]    RSP7_RX_PV0_TYPE              R/W  default = 1
                 0 : MANAGEMENT
                 1 : CONTROL
                 2 : DATA

   [ 7: 4]    RSP7_RX_PV0_SUBTYPE           R/W  default = 11

   [    3]    RSP7_RX_PV                    R/W  default = 0

   [    2]    RSP7_GROUP_ADDRESS            R/W  default = 0

   [    1]    RSP7_OPERATION                R/W  default = 1
                 0 : STA
                 1 : AP

   [    0]    RSP7_RX_INFO_AGG              R/W  default = 0


---------------------------------------------------------------------------------
    Address  : 0x400800e4
    Name     : RSP8
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   - This register describes which control frame to send as a response frame when frame is received
   - Received PS-POLL Frame : Send ACK
   [   31]    RSP8_VALID                    R/W  default = 1

   [30:26]    RSP8_CASE                     R/W  default = 5

   [   25]    RSP8_MASK_RX_INFO_OK          R/W  default = 1

   [   24]    RSP8_MASK_RX_INFO_NDP         R/W  default = 1

   [   23]    RSP8_MASK_RX_NDP_PSPOLL       R/W  default = 0

   [22:21]    RSP8_MASK_RX_PV0_TYPE         R/W  default = 3

   [20:17]    RSP8_MASK_RX_PV0_SUBTYPE      R/W  default = 15

   [   16]    RSP8_MASK_RX_PV               R/W  default = 1

   [   15]    RSP8_MASK_GROUP_ADDRESS       R/W  default = 0

   [   14]    RSP8_MASK_OPERATION           R/W  default = 0

   [   13]    RSP8_MASK_RX_INFO_AGG         R/W  default = 0

   [   12]    RSP8_RX_INFO_OK               R/W  default = 1

   [   11]    RSP8_RX_INFO_NDP              R/W  default = 0

   [   10]    RSP8_RX_NDP_PSPOLL            R/W  default = 0

   [ 9: 8]    RSP8_RX_PV0_TYPE              R/W  default = 1
                 0 : MANAGEMENT
                 1 : CONTROL
                 2 : DATA

   [ 7: 4]    RSP8_RX_PV0_SUBTYPE           R/W  default = 10

   [    3]    RSP8_RX_PV                    R/W  default = 0

   [    2]    RSP8_GROUP_ADDRESS            R/W  default = 0

   [    1]    RSP8_OPERATION                R/W  default = 0
                 0 : STA
                 1 : AP

   [    0]    RSP8_RX_INFO_AGG              R/W  default = 0


---------------------------------------------------------------------------------
    Address  : 0x400800e8
    Name     : RSP9
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   - This register describes which control frame to send as a response frame when frame is received
   - Received Single Data Frame : Send ACK
   [   31]    RSP9_VALID                    R/W  default = 1

   [30:26]    RSP9_CASE                     R/W  default = 1

   [   25]    RSP9_MASK_RX_INFO_OK          R/W  default = 1

   [   24]    RSP9_MASK_RX_INFO_NDP         R/W  default = 1

   [   23]    RSP9_MASK_RX_NDP_PSPOLL       R/W  default = 0

   [22:21]    RSP9_MASK_RX_PV0_TYPE         R/W  default = 3

   [20:17]    RSP9_MASK_RX_PV0_SUBTYPE      R/W  default = 15

   [   16]    RSP9_MASK_RX_PV               R/W  default = 1

   [   15]    RSP9_MASK_GROUP_ADDRESS       R/W  default = 0

   [   14]    RSP9_MASK_OPERATION           R/W  default = 0

   [   13]    RSP9_MASK_RX_INFO_AGG         R/W  default = 1

   [   12]    RSP9_RX_INFO_OK               R/W  default = 1

   [   11]    RSP9_RX_INFO_NDP              R/W  default = 0

   [   10]    RSP9_RX_NDP_PSPOLL            R/W  default = 0

   [ 9: 8]    RSP9_RX_PV0_TYPE              R/W  default = 2
                 0 : MANAGEMENT
                 1 : CONTROL
                 2 : DATA

   [ 7: 4]    RSP9_RX_PV0_SUBTYPE           R/W  default = 0

   [    3]    RSP9_RX_PV                    R/W  default = 0

   [    2]    RSP9_GROUP_ADDRESS            R/W  default = 0

   [    1]    RSP9_OPERATION                R/W  default = 0
                 0 : STA
                 1 : AP

   [    0]    RSP9_RX_INFO_AGG              R/W  default = 0


---------------------------------------------------------------------------------
    Address  : 0x400800ec
    Name     : RSP10
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   - This register describes which control frame to send as a response frame when frame is received
   - Received A-MPDU Frame : Send BA
   [   31]    RSP10_VALID                   R/W  default = 1

   [30:26]    RSP10_CASE                    R/W  default = 2

   [   25]    RSP10_MASK_RX_INFO_OK         R/W  default = 1

   [   24]    RSP10_MASK_RX_INFO_NDP        R/W  default = 1

   [   23]    RSP10_MASK_RX_NDP_PSPOLL      R/W  default = 0

   [22:21]    RSP10_MASK_RX_PV0_TYPE        R/W  default = 3

   [20:17]    RSP10_MASK_RX_PV0_SUBTYPE     R/W  default = 15

   [   16]    RSP10_MASK_RX_PV              R/W  default = 1

   [   15]    RSP10_MASK_GROUP_ADDRESS      R/W  default = 0

   [   14]    RSP10_MASK_OPERATION          R/W  default = 0

   [   13]    RSP10_MASK_RX_INFO_AGG        R/W  default = 1

   [   12]    RSP10_RX_INFO_OK              R/W  default = 1

   [   11]    RSP10_RX_INFO_NDP             R/W  default = 0

   [   10]    RSP10_RX_NDP_PSPOLL           R/W  default = 0

   [ 9: 8]    RSP10_RX_PV0_TYPE             R/W  default = 2
                 0 : MANAGEMENT
                 1 : CONTROL
                 2 : DATA

   [ 7: 4]    RSP10_RX_PV0_SUBTYPE          R/W  default = 0

   [    3]    RSP10_RX_PV                   R/W  default = 0

   [    2]    RSP10_GROUP_ADDRESS           R/W  default = 0

   [    1]    RSP10_OPERATION               R/W  default = 0
                 0 : STA
                 1 : AP

   [    0]    RSP10_RX_INFO_AGG             R/W  default = 1


---------------------------------------------------------------------------------
    Address  : 0x400800f0
    Name     : RSP11
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   - This register describes which control frame to send as a response frame when frame is received
   - Received NULL Data Frame : Send Ack
   [   31]    RSP11_VALID                   R/W  default = 1

   [30:26]    RSP11_CASE                    R/W  default = 1

   [   25]    RSP11_MASK_RX_INFO_OK         R/W  default = 1

   [   24]    RSP11_MASK_RX_INFO_NDP        R/W  default = 1

   [   23]    RSP11_MASK_RX_NDP_PSPOLL      R/W  default = 0

   [22:21]    RSP11_MASK_RX_PV0_TYPE        R/W  default = 3

   [20:17]    RSP11_MASK_RX_PV0_SUBTYPE     R/W  default = 15

   [   16]    RSP11_MASK_RX_PV              R/W  default = 1

   [   15]    RSP11_MASK_GROUP_ADDRESS      R/W  default = 0

   [   14]    RSP11_MASK_OPERATION          R/W  default = 0

   [   13]    RSP11_MASK_RX_INFO_AGG        R/W  default = 0

   [   12]    RSP11_RX_INFO_OK              R/W  default = 1

   [   11]    RSP11_RX_INFO_NDP             R/W  default = 0

   [   10]    RSP11_RX_NDP_PSPOLL           R/W  default = 0

   [ 9: 8]    RSP11_RX_PV0_TYPE             R/W  default = 2
                 0 : MANAGEMENT
                 1 : CONTROL
                 2 : DATA

   [ 7: 4]    RSP11_RX_PV0_SUBTYPE          R/W  default = 4

   [    3]    RSP11_RX_PV                   R/W  default = 0

   [    2]    RSP11_GROUP_ADDRESS           R/W  default = 0

   [    1]    RSP11_OPERATION               R/W  default = 0
                 0 : STA
                 1 : AP

   [    0]    RSP11_RX_INFO_AGG             R/W  default = 0


---------------------------------------------------------------------------------
    Address  : 0x400800f4
    Name     : RSP12
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   - This register describes which control frame to send as a response frame when frame is received
   - Received QoS Data : Send Ack
   [   31]    RSP12_VALID                   R/W  default = 1

   [30:26]    RSP12_CASE                    R/W  default = 1

   [   25]    RSP12_MASK_RX_INFO_OK         R/W  default = 1

   [   24]    RSP12_MASK_RX_INFO_NDP        R/W  default = 1

   [   23]    RSP12_MASK_RX_NDP_PSPOLL      R/W  default = 0

   [22:21]    RSP12_MASK_RX_PV0_TYPE        R/W  default = 3

   [20:17]    RSP12_MASK_RX_PV0_SUBTYPE     R/W  default = 15

   [   16]    RSP12_MASK_RX_PV              R/W  default = 1

   [   15]    RSP12_MASK_GROUP_ADDRESS      R/W  default = 0

   [   14]    RSP12_MASK_OPERATION          R/W  default = 0

   [   13]    RSP12_MASK_RX_INFO_AGG        R/W  default = 1

   [   12]    RSP12_RX_INFO_OK              R/W  default = 1

   [   11]    RSP12_RX_INFO_NDP             R/W  default = 0

   [   10]    RSP12_RX_NDP_PSPOLL           R/W  default = 0

   [ 9: 8]    RSP12_RX_PV0_TYPE             R/W  default = 2
                 0 : MANAGEMENT
                 1 : CONTROL
                 2 : DATA

   [ 7: 4]    RSP12_RX_PV0_SUBTYPE          R/W  default = 8

   [    3]    RSP12_RX_PV                   R/W  default = 0

   [    2]    RSP12_GROUP_ADDRESS           R/W  default = 0

   [    1]    RSP12_OPERATION               R/W  default = 0
                 0 : STA
                 1 : AP

   [    0]    RSP12_RX_INFO_AGG             R/W  default = 0


---------------------------------------------------------------------------------
    Address  : 0x400800f8
    Name     : RSP13
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   - This register describes which control frame to send as a response frame when frame is received
   - Received A-MPDU QoS Data : Send BA
   [   31]    RSP13_VALID                   R/W  default = 1

   [30:26]    RSP13_CASE                    R/W  default = 2

   [   25]    RSP13_MASK_RX_INFO_OK         R/W  default = 1

   [   24]    RSP13_MASK_RX_INFO_NDP        R/W  default = 1

   [   23]    RSP13_MASK_RX_NDP_PSPOLL      R/W  default = 0

   [22:21]    RSP13_MASK_RX_PV0_TYPE        R/W  default = 3

   [20:17]    RSP13_MASK_RX_PV0_SUBTYPE     R/W  default = 15

   [   16]    RSP13_MASK_RX_PV              R/W  default = 1

   [   15]    RSP13_MASK_GROUP_ADDRESS      R/W  default = 0

   [   14]    RSP13_MASK_OPERATION          R/W  default = 0

   [   13]    RSP13_MASK_RX_INFO_AGG        R/W  default = 1

   [   12]    RSP13_RX_INFO_OK              R/W  default = 1

   [   11]    RSP13_RX_INFO_NDP             R/W  default = 0

   [   10]    RSP13_RX_NDP_PSPOLL           R/W  default = 0

   [ 9: 8]    RSP13_RX_PV0_TYPE             R/W  default = 2
                 0 : MANAGEMENT
                 1 : CONTROL
                 2 : DATA

   [ 7: 4]    RSP13_RX_PV0_SUBTYPE          R/W  default = 8

   [    3]    RSP13_RX_PV                   R/W  default = 0

   [    2]    RSP13_GROUP_ADDRESS           R/W  default = 0

   [    1]    RSP13_OPERATION               R/W  default = 0
                 0 : STA
                 1 : AP

   [    0]    RSP13_RX_INFO_AGG             R/W  default = 1


---------------------------------------------------------------------------------
    Address  : 0x400800fc
    Name     : RSP14
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   - This register describes which control frame to send as a response frame when frame is received
   - Received QoS NULL Data : Send Ack
   [   31]    RSP14_VALID                   R/W  default = 1

   [30:26]    RSP14_CASE                    R/W  default = 1

   [   25]    RSP14_MASK_RX_INFO_OK         R/W  default = 1

   [   24]    RSP14_MASK_RX_INFO_NDP        R/W  default = 1

   [   23]    RSP14_MASK_RX_NDP_PSPOLL      R/W  default = 0

   [22:21]    RSP14_MASK_RX_PV0_TYPE        R/W  default = 3

   [20:17]    RSP14_MASK_RX_PV0_SUBTYPE     R/W  default = 15

   [   16]    RSP14_MASK_RX_PV              R/W  default = 1

   [   15]    RSP14_MASK_GROUP_ADDRESS      R/W  default = 0

   [   14]    RSP14_MASK_OPERATION          R/W  default = 0

   [   13]    RSP14_MASK_RX_INFO_AGG        R/W  default = 0

   [   12]    RSP14_RX_INFO_OK              R/W  default = 1

   [   11]    RSP14_RX_INFO_NDP             R/W  default = 0

   [   10]    RSP14_RX_NDP_PSPOLL           R/W  default = 0

   [ 9: 8]    RSP14_RX_PV0_TYPE             R/W  default = 2
                 0 : MANAGEMENT
                 1 : CONTROL
                 2 : DATA

   [ 7: 4]    RSP14_RX_PV0_SUBTYPE          R/W  default = 12

   [    3]    RSP14_RX_PV                   R/W  default = 0

   [    2]    RSP14_GROUP_ADDRESS           R/W  default = 0

   [    1]    RSP14_OPERATION               R/W  default = 0
                 0 : STA
                 1 : AP

   [    0]    RSP14_RX_INFO_AGG             R/W  default = 0


---------------------------------------------------------------------------------
    Address  : 0x40080100
    Name     : RSP15
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   - This register describes which control frame to send as a response frame when frame is received
   - Received PV1 QOS_DATA0 : Send Ack
   [   31]    RSP15_VALID                   R/W  default = 1

   [30:26]    RSP15_CASE                    R/W  default = 1

   [   25]    RSP15_MASK_RX_INFO_OK         R/W  default = 1

   [   24]    RSP15_MASK_RX_INFO_NDP        R/W  default = 1

   [   23]    RSP15_MASK_RX_NDP_PSPOLL      R/W  default = 0

   [22:21]    RSP15_MASK_RX_PV0_TYPE        R/W  default = 3

   [20:17]    RSP15_MASK_RX_PV0_SUBTYPE     R/W  default = 1

   [   16]    RSP15_MASK_RX_PV              R/W  default = 1

   [   15]    RSP15_MASK_GROUP_ADDRESS      R/W  default = 0

   [   14]    RSP15_MASK_OPERATION          R/W  default = 0

   [   13]    RSP15_MASK_RX_INFO_AGG        R/W  default = 1

   [   12]    RSP15_RX_INFO_OK              R/W  default = 1

   [   11]    RSP15_RX_INFO_NDP             R/W  default = 0

   [   10]    RSP15_RX_NDP_PSPOLL           R/W  default = 0

   [ 9: 8]    RSP15_RX_PV0_TYPE             R/W  default = 0
                 0 : MANAGEMENT
                 1 : CONTROL
                 2 : DATA

   [ 7: 4]    RSP15_RX_PV0_SUBTYPE          R/W  default = 0

   [    3]    RSP15_RX_PV                   R/W  default = 1

   [    2]    RSP15_GROUP_ADDRESS           R/W  default = 0

   [    1]    RSP15_OPERATION               R/W  default = 0
                 0 : STA
                 1 : AP

   [    0]    RSP15_RX_INFO_AGG             R/W  default = 0


---------------------------------------------------------------------------------
    Address  : 0x40080104
    Name     : RSP16
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   - This register describes which control frame to send as a response frame when frame is received
   - Received Aggregated PV1 QOS_DATA0 : Send BA
   [   31]    RSP16_VALID                   R/W  default = 1

   [30:26]    RSP16_CASE                    R/W  default = 2

   [   25]    RSP16_MASK_RX_INFO_OK         R/W  default = 1

   [   24]    RSP16_MASK_RX_INFO_NDP        R/W  default = 1

   [   23]    RSP16_MASK_RX_NDP_PSPOLL      R/W  default = 0

   [22:21]    RSP16_MASK_RX_PV0_TYPE        R/W  default = 3

   [20:17]    RSP16_MASK_RX_PV0_SUBTYPE     R/W  default = 1

   [   16]    RSP16_MASK_RX_PV              R/W  default = 1

   [   15]    RSP16_MASK_GROUP_ADDRESS      R/W  default = 0

   [   14]    RSP16_MASK_OPERATION          R/W  default = 0

   [   13]    RSP16_MASK_RX_INFO_AGG        R/W  default = 1

   [   12]    RSP16_RX_INFO_OK              R/W  default = 1

   [   11]    RSP16_RX_INFO_NDP             R/W  default = 0

   [   10]    RSP16_RX_NDP_PSPOLL           R/W  default = 0

   [ 9: 8]    RSP16_RX_PV0_TYPE             R/W  default = 0
                 0 : MANAGEMENT
                 1 : CONTROL
                 2 : DATA

   [ 7: 4]    RSP16_RX_PV0_SUBTYPE          R/W  default = 0

   [    3]    RSP16_RX_PV                   R/W  default = 1

   [    2]    RSP16_GROUP_ADDRESS           R/W  default = 0

   [    1]    RSP16_OPERATION               R/W  default = 0
                 0 : STA
                 1 : AP

   [    0]    RSP16_RX_INFO_AGG             R/W  default = 1


---------------------------------------------------------------------------------
    Address  : 0x40080108
    Name     : RSP17
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   - This register describes which control frame to send as a response frame when frame is received
   - Received PV1 Action : Send Ack
   [   31]    RSP17_VALID                   R/W  default = 1

   [30:26]    RSP17_CASE                    R/W  default = 1

   [   25]    RSP17_MASK_RX_INFO_OK         R/W  default = 1

   [   24]    RSP17_MASK_RX_INFO_NDP        R/W  default = 1

   [   23]    RSP17_MASK_RX_NDP_PSPOLL      R/W  default = 0

   [22:21]    RSP17_MASK_RX_PV0_TYPE        R/W  default = 3

   [20:17]    RSP17_MASK_RX_PV0_SUBTYPE     R/W  default = 15

   [   16]    RSP17_MASK_RX_PV              R/W  default = 1

   [   15]    RSP17_MASK_GROUP_ADDRESS      R/W  default = 0

   [   14]    RSP17_MASK_OPERATION          R/W  default = 0

   [   13]    RSP17_MASK_RX_INFO_AGG        R/W  default = 0

   [   12]    RSP17_RX_INFO_OK              R/W  default = 1

   [   11]    RSP17_RX_INFO_NDP             R/W  default = 0

   [   10]    RSP17_RX_NDP_PSPOLL           R/W  default = 0

   [ 9: 8]    RSP17_RX_PV0_TYPE             R/W  default = 1
                 0 : MANAGEMENT
                 1 : CONTROL
                 2 : DATA

   [ 7: 4]    RSP17_RX_PV0_SUBTYPE          R/W  default = 0

   [    3]    RSP17_RX_PV                   R/W  default = 1

   [    2]    RSP17_GROUP_ADDRESS           R/W  default = 0

   [    1]    RSP17_OPERATION               R/W  default = 0
                 0 : STA
                 1 : AP

   [    0]    RSP17_RX_INFO_AGG             R/W  default = 0


---------------------------------------------------------------------------------
    Address  : 0x4008010c
    Name     : RSP18
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   - This register describes which control frame to send as a response frame when frame is received
   - Received PV1 Probe Response : Send Ack
   [   31]    RSP18_VALID                   R/W  default = 1

   [30:26]    RSP18_CASE                    R/W  default = 1

   [   25]    RSP18_MASK_RX_INFO_OK         R/W  default = 1

   [   24]    RSP18_MASK_RX_INFO_NDP        R/W  default = 1

   [   23]    RSP18_MASK_RX_NDP_PSPOLL      R/W  default = 0

   [22:21]    RSP18_MASK_RX_PV0_TYPE        R/W  default = 3

   [20:17]    RSP18_MASK_RX_PV0_SUBTYPE     R/W  default = 15

   [   16]    RSP18_MASK_RX_PV              R/W  default = 1

   [   15]    RSP18_MASK_GROUP_ADDRESS      R/W  default = 0

   [   14]    RSP18_MASK_OPERATION          R/W  default = 0

   [   13]    RSP18_MASK_RX_INFO_AGG        R/W  default = 0

   [   12]    RSP18_RX_INFO_OK              R/W  default = 1

   [   11]    RSP18_RX_INFO_NDP             R/W  default = 0

   [   10]    RSP18_RX_NDP_PSPOLL           R/W  default = 0

   [ 9: 8]    RSP18_RX_PV0_TYPE             R/W  default = 1
                 0 : MANAGEMENT
                 1 : CONTROL
                 2 : DATA

   [ 7: 4]    RSP18_RX_PV0_SUBTYPE          R/W  default = 4

   [    3]    RSP18_RX_PV                   R/W  default = 1

   [    2]    RSP18_GROUP_ADDRESS           R/W  default = 0

   [    1]    RSP18_OPERATION               R/W  default = 0
                 0 : STA
                 1 : AP

   [    0]    RSP18_RX_INFO_AGG             R/W  default = 0


---------------------------------------------------------------------------------
    Address  : 0x40080110
    Name     : RSP19
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   - This register describes which control frame to send as a response frame when frame is received
   - Received PV1 QOS_DATA3 : Send Ack
   [   31]    RSP19_VALID                   R/W  default = 1

   [30:26]    RSP19_CASE                    R/W  default = 1

   [   25]    RSP19_MASK_RX_INFO_OK         R/W  default = 1

   [   24]    RSP19_MASK_RX_INFO_NDP        R/W  default = 1

   [   23]    RSP19_MASK_RX_NDP_PSPOLL      R/W  default = 0

   [22:21]    RSP19_MASK_RX_PV0_TYPE        R/W  default = 3

   [20:17]    RSP19_MASK_RX_PV0_SUBTYPE     R/W  default = 1

   [   16]    RSP19_MASK_RX_PV              R/W  default = 1

   [   15]    RSP19_MASK_GROUP_ADDRESS      R/W  default = 0

   [   14]    RSP19_MASK_OPERATION          R/W  default = 0

   [   13]    RSP19_MASK_RX_INFO_AGG        R/W  default = 1

   [   12]    RSP19_RX_INFO_OK              R/W  default = 1

   [   11]    RSP19_RX_INFO_NDP             R/W  default = 0

   [   10]    RSP19_RX_NDP_PSPOLL           R/W  default = 0

   [ 9: 8]    RSP19_RX_PV0_TYPE             R/W  default = 3
                 0 : MANAGEMENT
                 1 : CONTROL
                 2 : DATA

   [ 7: 4]    RSP19_RX_PV0_SUBTYPE          R/W  default = 0

   [    3]    RSP19_RX_PV                   R/W  default = 1

   [    2]    RSP19_GROUP_ADDRESS           R/W  default = 0

   [    1]    RSP19_OPERATION               R/W  default = 0
                 0 : STA
                 1 : AP

   [    0]    RSP19_RX_INFO_AGG             R/W  default = 0


---------------------------------------------------------------------------------
    Address  : 0x40080114
    Name     : RSP20
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   - This register describes which control frame to send as a response frame when frame is received
   - Received Aggregated PV1 QOS_DATA3 : Send BA
   [   31]    RSP20_VALID                   R/W  default = 1

   [30:26]    RSP20_CASE                    R/W  default = 2

   [   25]    RSP20_MASK_RX_INFO_OK         R/W  default = 1

   [   24]    RSP20_MASK_RX_INFO_NDP        R/W  default = 1

   [   23]    RSP20_MASK_RX_NDP_PSPOLL      R/W  default = 0

   [22:21]    RSP20_MASK_RX_PV0_TYPE        R/W  default = 3

   [20:17]    RSP20_MASK_RX_PV0_SUBTYPE     R/W  default = 1

   [   16]    RSP20_MASK_RX_PV              R/W  default = 1

   [   15]    RSP20_MASK_GROUP_ADDRESS      R/W  default = 0

   [   14]    RSP20_MASK_OPERATION          R/W  default = 0

   [   13]    RSP20_MASK_RX_INFO_AGG        R/W  default = 1

   [   12]    RSP20_RX_INFO_OK              R/W  default = 1

   [   11]    RSP20_RX_INFO_NDP             R/W  default = 0

   [   10]    RSP20_RX_NDP_PSPOLL           R/W  default = 0

   [ 9: 8]    RSP20_RX_PV0_TYPE             R/W  default = 3
                 0 : MANAGEMENT
                 1 : CONTROL
                 2 : DATA

   [ 7: 4]    RSP20_RX_PV0_SUBTYPE          R/W  default = 0

   [    3]    RSP20_RX_PV                   R/W  default = 1

   [    2]    RSP20_GROUP_ADDRESS           R/W  default = 0

   [    1]    RSP20_OPERATION               R/W  default = 0
                 0 : STA
                 1 : AP

   [    0]    RSP20_RX_INFO_AGG             R/W  default = 1


---------------------------------------------------------------------------------
    Address  : 0x40080118
    Name     : RSP21
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   - This register describes which control frame to send as a response frame when frame is received
   - Received Aggregated PV1 QOS_DATA3 : Send BA
   [   31]    RSP21_VALID                   R/W  default = 1

   [30:26]    RSP21_CASE                    R/W  default = 2

   [   25]    RSP21_MASK_RX_INFO_OK         R/W  default = 1

   [   24]    RSP21_MASK_RX_INFO_NDP        R/W  default = 1

   [   23]    RSP21_MASK_RX_NDP_PSPOLL      R/W  default = 0

   [22:21]    RSP21_MASK_RX_PV0_TYPE        R/W  default = 3

   [20:17]    RSP21_MASK_RX_PV0_SUBTYPE     R/W  default = 1

   [   16]    RSP21_MASK_RX_PV              R/W  default = 1

   [   15]    RSP21_MASK_GROUP_ADDRESS      R/W  default = 0

   [   14]    RSP21_MASK_OPERATION          R/W  default = 0

   [   13]    RSP21_MASK_RX_INFO_AGG        R/W  default = 1

   [   12]    RSP21_RX_INFO_OK              R/W  default = 1

   [   11]    RSP21_RX_INFO_NDP             R/W  default = 0

   [   10]    RSP21_RX_NDP_PSPOLL           R/W  default = 0

   [ 9: 8]    RSP21_RX_PV0_TYPE             R/W  default = 3
                 0 : MANAGEMENT
                 1 : CONTROL
                 2 : DATA

   [ 7: 4]    RSP21_RX_PV0_SUBTYPE          R/W  default = 0

   [    3]    RSP21_RX_PV                   R/W  default = 1

   [    2]    RSP21_GROUP_ADDRESS           R/W  default = 0

   [    1]    RSP21_OPERATION               R/W  default = 0
                 0 : STA
                 1 : AP

   [    0]    RSP21_RX_INFO_AGG             R/W  default = 1


---------------------------------------------------------------------------------
    Address  : 0x4008011c
    Name     : RSP22
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   - This register describes which control frame to send as a response frame when frame is received
   - Received Aggregated PV1 QOS_DATA3 : Send BA
   [   31]    RSP22_VALID                   R/W  default = 1

   [30:26]    RSP22_CASE                    R/W  default = 2

   [   25]    RSP22_MASK_RX_INFO_OK         R/W  default = 1

   [   24]    RSP22_MASK_RX_INFO_NDP        R/W  default = 1

   [   23]    RSP22_MASK_RX_NDP_PSPOLL      R/W  default = 0

   [22:21]    RSP22_MASK_RX_PV0_TYPE        R/W  default = 3

   [20:17]    RSP22_MASK_RX_PV0_SUBTYPE     R/W  default = 1

   [   16]    RSP22_MASK_RX_PV              R/W  default = 1

   [   15]    RSP22_MASK_GROUP_ADDRESS      R/W  default = 0

   [   14]    RSP22_MASK_OPERATION          R/W  default = 0

   [   13]    RSP22_MASK_RX_INFO_AGG        R/W  default = 1

   [   12]    RSP22_RX_INFO_OK              R/W  default = 1

   [   11]    RSP22_RX_INFO_NDP             R/W  default = 0

   [   10]    RSP22_RX_NDP_PSPOLL           R/W  default = 0

   [ 9: 8]    RSP22_RX_PV0_TYPE             R/W  default = 3
                 0 : MANAGEMENT
                 1 : CONTROL
                 2 : DATA

   [ 7: 4]    RSP22_RX_PV0_SUBTYPE          R/W  default = 0

   [    3]    RSP22_RX_PV                   R/W  default = 1

   [    2]    RSP22_GROUP_ADDRESS           R/W  default = 0

   [    1]    RSP22_OPERATION               R/W  default = 0
                 0 : STA
                 1 : AP

   [    0]    RSP22_RX_INFO_AGG             R/W  default = 1


---------------------------------------------------------------------------------
    Address  : 0x40080120
    Name     : RSP23
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   - This register describes which control frame to send as a response frame when frame is received
   - Received Aggregated PV1 QOS_DATA3 : Send BA
   [   31]    RSP23_VALID                   R/W  default = 1

   [30:26]    RSP23_CASE                    R/W  default = 2

   [   25]    RSP23_MASK_RX_INFO_OK         R/W  default = 1

   [   24]    RSP23_MASK_RX_INFO_NDP        R/W  default = 1

   [   23]    RSP23_MASK_RX_NDP_PSPOLL      R/W  default = 0

   [22:21]    RSP23_MASK_RX_PV0_TYPE        R/W  default = 3

   [20:17]    RSP23_MASK_RX_PV0_SUBTYPE     R/W  default = 1

   [   16]    RSP23_MASK_RX_PV              R/W  default = 1

   [   15]    RSP23_MASK_GROUP_ADDRESS      R/W  default = 0

   [   14]    RSP23_MASK_OPERATION          R/W  default = 0

   [   13]    RSP23_MASK_RX_INFO_AGG        R/W  default = 1

   [   12]    RSP23_RX_INFO_OK              R/W  default = 1

   [   11]    RSP23_RX_INFO_NDP             R/W  default = 0

   [   10]    RSP23_RX_NDP_PSPOLL           R/W  default = 0

   [ 9: 8]    RSP23_RX_PV0_TYPE             R/W  default = 3
                 0 : MANAGEMENT
                 1 : CONTROL
                 2 : DATA

   [ 7: 4]    RSP23_RX_PV0_SUBTYPE          R/W  default = 0

   [    3]    RSP23_RX_PV                   R/W  default = 1

   [    2]    RSP23_GROUP_ADDRESS           R/W  default = 0

   [    1]    RSP23_OPERATION               R/W  default = 0
                 0 : STA
                 1 : AP

   [    0]    RSP23_RX_INFO_AGG             R/W  default = 1


---------------------------------------------------------------------------------
    Address  : 0x40080124
    Name     : RSP24
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   - This register describes which control frame to send as a response frame when frame is received
   - Received Aggregated PV1 QOS_DATA3 : Send BA
   [   31]    RSP24_VALID                   R/W  default = 1

   [30:26]    RSP24_CASE                    R/W  default = 2

   [   25]    RSP24_MASK_RX_INFO_OK         R/W  default = 1

   [   24]    RSP24_MASK_RX_INFO_NDP        R/W  default = 1

   [   23]    RSP24_MASK_RX_NDP_PSPOLL      R/W  default = 0

   [22:21]    RSP24_MASK_RX_PV0_TYPE        R/W  default = 3

   [20:17]    RSP24_MASK_RX_PV0_SUBTYPE     R/W  default = 1

   [   16]    RSP24_MASK_RX_PV              R/W  default = 1

   [   15]    RSP24_MASK_GROUP_ADDRESS      R/W  default = 0

   [   14]    RSP24_MASK_OPERATION          R/W  default = 0

   [   13]    RSP24_MASK_RX_INFO_AGG        R/W  default = 1

   [   12]    RSP24_RX_INFO_OK              R/W  default = 1

   [   11]    RSP24_RX_INFO_NDP             R/W  default = 0

   [   10]    RSP24_RX_NDP_PSPOLL           R/W  default = 0

   [ 9: 8]    RSP24_RX_PV0_TYPE             R/W  default = 3
                 0 : MANAGEMENT
                 1 : CONTROL
                 2 : DATA

   [ 7: 4]    RSP24_RX_PV0_SUBTYPE          R/W  default = 0

   [    3]    RSP24_RX_PV                   R/W  default = 1

   [    2]    RSP24_GROUP_ADDRESS           R/W  default = 0

   [    1]    RSP24_OPERATION               R/W  default = 0
                 0 : STA
                 1 : AP

   [    0]    RSP24_RX_INFO_AGG             R/W  default = 1


---------------------------------------------------------------------------------
    Address  : 0x40080128
    Name     : RSP25
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   - This register describes which control frame to send as a response frame when frame is received
   - Received Aggregated PV1 QOS_DATA3 : Send BA
   [   31]    RSP25_VALID                   R/W  default = 1

   [30:26]    RSP25_CASE                    R/W  default = 2

   [   25]    RSP25_MASK_RX_INFO_OK         R/W  default = 1

   [   24]    RSP25_MASK_RX_INFO_NDP        R/W  default = 1

   [   23]    RSP25_MASK_RX_NDP_PSPOLL      R/W  default = 0

   [22:21]    RSP25_MASK_RX_PV0_TYPE        R/W  default = 3

   [20:17]    RSP25_MASK_RX_PV0_SUBTYPE     R/W  default = 1

   [   16]    RSP25_MASK_RX_PV              R/W  default = 1

   [   15]    RSP25_MASK_GROUP_ADDRESS      R/W  default = 0

   [   14]    RSP25_MASK_OPERATION          R/W  default = 0

   [   13]    RSP25_MASK_RX_INFO_AGG        R/W  default = 1

   [   12]    RSP25_RX_INFO_OK              R/W  default = 1

   [   11]    RSP25_RX_INFO_NDP             R/W  default = 0

   [   10]    RSP25_RX_NDP_PSPOLL           R/W  default = 0

   [ 9: 8]    RSP25_RX_PV0_TYPE             R/W  default = 3
                 0 : MANAGEMENT
                 1 : CONTROL
                 2 : DATA

   [ 7: 4]    RSP25_RX_PV0_SUBTYPE          R/W  default = 0

   [    3]    RSP25_RX_PV                   R/W  default = 1

   [    2]    RSP25_GROUP_ADDRESS           R/W  default = 0

   [    1]    RSP25_OPERATION               R/W  default = 0
                 0 : STA
                 1 : AP

   [    0]    RSP25_RX_INFO_AGG             R/W  default = 1


---------------------------------------------------------------------------------
    Address  : 0x4008012c
    Name     : RSP26
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   - This register describes which control frame to send as a response frame when frame is received
   - Received Aggregated PV1 QOS_DATA3 : Send BA
   [   31]    RSP26_VALID                   R/W  default = 1

   [30:26]    RSP26_CASE                    R/W  default = 2

   [   25]    RSP26_MASK_RX_INFO_OK         R/W  default = 1

   [   24]    RSP26_MASK_RX_INFO_NDP        R/W  default = 1

   [   23]    RSP26_MASK_RX_NDP_PSPOLL      R/W  default = 0

   [22:21]    RSP26_MASK_RX_PV0_TYPE        R/W  default = 3

   [20:17]    RSP26_MASK_RX_PV0_SUBTYPE     R/W  default = 1

   [   16]    RSP26_MASK_RX_PV              R/W  default = 1

   [   15]    RSP26_MASK_GROUP_ADDRESS      R/W  default = 0

   [   14]    RSP26_MASK_OPERATION          R/W  default = 0

   [   13]    RSP26_MASK_RX_INFO_AGG        R/W  default = 1

   [   12]    RSP26_RX_INFO_OK              R/W  default = 1

   [   11]    RSP26_RX_INFO_NDP             R/W  default = 0

   [   10]    RSP26_RX_NDP_PSPOLL           R/W  default = 0

   [ 9: 8]    RSP26_RX_PV0_TYPE             R/W  default = 3
                 0 : MANAGEMENT
                 1 : CONTROL
                 2 : DATA

   [ 7: 4]    RSP26_RX_PV0_SUBTYPE          R/W  default = 0

   [    3]    RSP26_RX_PV                   R/W  default = 1

   [    2]    RSP26_GROUP_ADDRESS           R/W  default = 0

   [    1]    RSP26_OPERATION               R/W  default = 0
                 0 : STA
                 1 : AP

   [    0]    RSP26_RX_INFO_AGG             R/W  default = 1


---------------------------------------------------------------------------------
    Address  : 0x40080130
    Name     : RSP27
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   - This register describes which control frame to send as a response frame when frame is received
   - Received Aggregated PV1 QOS_DATA3 : Send BA
   [   31]    RSP27_VALID                   R/W  default = 1

   [30:26]    RSP27_CASE                    R/W  default = 2

   [   25]    RSP27_MASK_RX_INFO_OK         R/W  default = 1

   [   24]    RSP27_MASK_RX_INFO_NDP        R/W  default = 1

   [   23]    RSP27_MASK_RX_NDP_PSPOLL      R/W  default = 0

   [22:21]    RSP27_MASK_RX_PV0_TYPE        R/W  default = 3

   [20:17]    RSP27_MASK_RX_PV0_SUBTYPE     R/W  default = 1

   [   16]    RSP27_MASK_RX_PV              R/W  default = 1

   [   15]    RSP27_MASK_GROUP_ADDRESS      R/W  default = 0

   [   14]    RSP27_MASK_OPERATION          R/W  default = 0

   [   13]    RSP27_MASK_RX_INFO_AGG        R/W  default = 1

   [   12]    RSP27_RX_INFO_OK              R/W  default = 1

   [   11]    RSP27_RX_INFO_NDP             R/W  default = 0

   [   10]    RSP27_RX_NDP_PSPOLL           R/W  default = 0

   [ 9: 8]    RSP27_RX_PV0_TYPE             R/W  default = 3
                 0 : MANAGEMENT
                 1 : CONTROL
                 2 : DATA

   [ 7: 4]    RSP27_RX_PV0_SUBTYPE          R/W  default = 0

   [    3]    RSP27_RX_PV                   R/W  default = 1

   [    2]    RSP27_GROUP_ADDRESS           R/W  default = 0

   [    1]    RSP27_OPERATION               R/W  default = 0
                 0 : STA
                 1 : AP

   [    0]    RSP27_RX_INFO_AGG             R/W  default = 1


---------------------------------------------------------------------------------
    Address  : 0x40080134
    Name     : RSP28
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   - This register describes which control frame to send as a response frame when frame is received
   - Received Aggregated PV1 QOS_DATA3 : Send BA
   [   31]    RSP28_VALID                   R/W  default = 1

   [30:26]    RSP28_CASE                    R/W  default = 2

   [   25]    RSP28_MASK_RX_INFO_OK         R/W  default = 1

   [   24]    RSP28_MASK_RX_INFO_NDP        R/W  default = 1

   [   23]    RSP28_MASK_RX_NDP_PSPOLL      R/W  default = 0

   [22:21]    RSP28_MASK_RX_PV0_TYPE        R/W  default = 3

   [20:17]    RSP28_MASK_RX_PV0_SUBTYPE     R/W  default = 1

   [   16]    RSP28_MASK_RX_PV              R/W  default = 1

   [   15]    RSP28_MASK_GROUP_ADDRESS      R/W  default = 0

   [   14]    RSP28_MASK_OPERATION          R/W  default = 0

   [   13]    RSP28_MASK_RX_INFO_AGG        R/W  default = 1

   [   12]    RSP28_RX_INFO_OK              R/W  default = 1

   [   11]    RSP28_RX_INFO_NDP             R/W  default = 0

   [   10]    RSP28_RX_NDP_PSPOLL           R/W  default = 0

   [ 9: 8]    RSP28_RX_PV0_TYPE             R/W  default = 3
                 0 : MANAGEMENT
                 1 : CONTROL
                 2 : DATA

   [ 7: 4]    RSP28_RX_PV0_SUBTYPE          R/W  default = 0

   [    3]    RSP28_RX_PV                   R/W  default = 1

   [    2]    RSP28_GROUP_ADDRESS           R/W  default = 0

   [    1]    RSP28_OPERATION               R/W  default = 0
                 0 : STA
                 1 : AP

   [    0]    RSP28_RX_INFO_AGG             R/W  default = 1


---------------------------------------------------------------------------------
    Address  : 0x40080138
    Name     : RSP29
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   - This register describes which control frame to send as a response frame when frame is received
   - Received Aggregated PV1 QOS_DATA3 : Send BA
   [   31]    RSP29_VALID                   R/W  default = 1

   [30:26]    RSP29_CASE                    R/W  default = 2

   [   25]    RSP29_MASK_RX_INFO_OK         R/W  default = 1

   [   24]    RSP29_MASK_RX_INFO_NDP        R/W  default = 1

   [   23]    RSP29_MASK_RX_NDP_PSPOLL      R/W  default = 0

   [22:21]    RSP29_MASK_RX_PV0_TYPE        R/W  default = 3

   [20:17]    RSP29_MASK_RX_PV0_SUBTYPE     R/W  default = 1

   [   16]    RSP29_MASK_RX_PV              R/W  default = 1

   [   15]    RSP29_MASK_GROUP_ADDRESS      R/W  default = 0

   [   14]    RSP29_MASK_OPERATION          R/W  default = 0

   [   13]    RSP29_MASK_RX_INFO_AGG        R/W  default = 1

   [   12]    RSP29_RX_INFO_OK              R/W  default = 1

   [   11]    RSP29_RX_INFO_NDP             R/W  default = 0

   [   10]    RSP29_RX_NDP_PSPOLL           R/W  default = 0

   [ 9: 8]    RSP29_RX_PV0_TYPE             R/W  default = 3
                 0 : MANAGEMENT
                 1 : CONTROL
                 2 : DATA

   [ 7: 4]    RSP29_RX_PV0_SUBTYPE          R/W  default = 0

   [    3]    RSP29_RX_PV                   R/W  default = 1

   [    2]    RSP29_GROUP_ADDRESS           R/W  default = 0

   [    1]    RSP29_OPERATION               R/W  default = 0
                 0 : STA
                 1 : AP

   [    0]    RSP29_RX_INFO_AGG             R/W  default = 1


---------------------------------------------------------------------------------
    Address  : 0x4008013c
    Name     : RSP30
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   - This register describes which control frame to send as a response frame when frame is received
   - Received Aggregated PV1 QOS_DATA3 : Send BA
   [   31]    RSP30_VALID                   R/W  default = 1

   [30:26]    RSP30_CASE                    R/W  default = 2

   [   25]    RSP30_MASK_RX_INFO_OK         R/W  default = 1

   [   24]    RSP30_MASK_RX_INFO_NDP        R/W  default = 1

   [   23]    RSP30_MASK_RX_NDP_PSPOLL      R/W  default = 0

   [22:21]    RSP30_MASK_RX_PV0_TYPE        R/W  default = 3

   [20:17]    RSP30_MASK_RX_PV0_SUBTYPE     R/W  default = 1

   [   16]    RSP30_MASK_RX_PV              R/W  default = 1

   [   15]    RSP30_MASK_GROUP_ADDRESS      R/W  default = 0

   [   14]    RSP30_MASK_OPERATION          R/W  default = 0

   [   13]    RSP30_MASK_RX_INFO_AGG        R/W  default = 1

   [   12]    RSP30_RX_INFO_OK              R/W  default = 1

   [   11]    RSP30_RX_INFO_NDP             R/W  default = 0

   [   10]    RSP30_RX_NDP_PSPOLL           R/W  default = 0

   [ 9: 8]    RSP30_RX_PV0_TYPE             R/W  default = 3
                 0 : MANAGEMENT
                 1 : CONTROL
                 2 : DATA

   [ 7: 4]    RSP30_RX_PV0_SUBTYPE          R/W  default = 0

   [    3]    RSP30_RX_PV                   R/W  default = 1

   [    2]    RSP30_GROUP_ADDRESS           R/W  default = 0

   [    1]    RSP30_OPERATION               R/W  default = 0
                 0 : STA
                 1 : AP

   [    0]    RSP30_RX_INFO_AGG             R/W  default = 1


---------------------------------------------------------------------------------
    Address  : 0x40080140
    Name     : RSP31
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   - This register describes which control frame to send as a response frame when frame is received
   - Received Aggregated PV1 QOS_DATA3 : Send BA
   [   31]    RSP31_VALID                   R/W  default = 1

   [30:26]    RSP31_CASE                    R/W  default = 2

   [   25]    RSP31_MASK_RX_INFO_OK         R/W  default = 1

   [   24]    RSP31_MASK_RX_INFO_NDP        R/W  default = 1

   [   23]    RSP31_MASK_RX_NDP_PSPOLL      R/W  default = 0

   [22:21]    RSP31_MASK_RX_PV0_TYPE        R/W  default = 3

   [20:17]    RSP31_MASK_RX_PV0_SUBTYPE     R/W  default = 1

   [   16]    RSP31_MASK_RX_PV              R/W  default = 1

   [   15]    RSP31_MASK_GROUP_ADDRESS      R/W  default = 0

   [   14]    RSP31_MASK_OPERATION          R/W  default = 0

   [   13]    RSP31_MASK_RX_INFO_AGG        R/W  default = 1

   [   12]    RSP31_RX_INFO_OK              R/W  default = 1

   [   11]    RSP31_RX_INFO_NDP             R/W  default = 0

   [   10]    RSP31_RX_NDP_PSPOLL           R/W  default = 0

   [ 9: 8]    RSP31_RX_PV0_TYPE             R/W  default = 3
                 0 : MANAGEMENT
                 1 : CONTROL
                 2 : DATA

   [ 7: 4]    RSP31_RX_PV0_SUBTYPE          R/W  default = 0

   [    3]    RSP31_RX_PV                   R/W  default = 1

   [    2]    RSP31_GROUP_ADDRESS           R/W  default = 0

   [    1]    RSP31_OPERATION               R/W  default = 0
                 0 : STA
                 1 : AP

   [    0]    RSP31_RX_INFO_AGG             R/W  default = 1


---------------------------------------------------------------------------------
    Address  : 0x40080144
    Name     : RSP_CASE0
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   - Response Case 0 : Send Nothing
   - CF_TYPE_NONE : 0
   - CF_TYPE_CTS  : 2
   - CF_TYPE_ACK  : 3
   - CF_TYPE_BA   : 4
   - CF_TYPE_NDPCTS               : 6
   - CF_TYPE_NDPACK               : 7
   - CF_TYPE_NDPACK_Default       : 8
   - CF_TYPE_NDPPSPOLLACK         : 9
   - CF_TYPE_NDPPSPOLLACK Default : 10
   - CF_TYPE_NDPBA                : 11
   [   31]    CASE0_IRQ_NO                  R/W  default = 0

   [28:24]    CASE0_CF_TYPE_NO              R/W  default = 0

   [   23]    CASE0_IRQ_NDP                 R/W  default = 0

   [20:16]    CASE0_CF_TYPE_NDP             R/W  default = 0

   [   15]    CASE0_IRQ_NORMAL              R/W  default = 0

   [12: 8]    CASE0_CF_TYPE_NORMAL          R/W  default = 0

   [    7]    CASE0_IRQ_LONG                R/W  default = 0

   [ 4: 0]    CASE0_CF_TYPE_LONG            R/W  default = 0


---------------------------------------------------------------------------------
    Address  : 0x40080148
    Name     : RSP_CASE1
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   - Response Case 1 : Send ACK
   - CF_TYPE_NONE : 0
   - CF_TYPE_CTS  : 2
   - CF_TYPE_ACK  : 3
   - CF_TYPE_BA   : 4
   - CF_TYPE_NDPCTS               : 6
   - CF_TYPE_NDPACK               : 7
   - CF_TYPE_NDPACK_Default       : 8
   - CF_TYPE_NDPPSPOLLACK         : 9
   - CF_TYPE_NDPPSPOLLACK Default : 10
   - CF_TYPE_NDPBA                : 11
   [   31]    CASE1_IRQ_NO                  R/W  default = 0

   [28:24]    CASE1_CF_TYPE_NO              R/W  default = 0

   [   23]    CASE1_IRQ_NDP                 R/W  default = 0

   [20:16]    CASE1_CF_TYPE_NDP             R/W  default = 8

   [   15]    CASE1_IRQ_NORMAL              R/W  default = 0

   [12: 8]    CASE1_CF_TYPE_NORMAL          R/W  default = 3

   [    7]    CASE1_IRQ_LONG                R/W  default = 0

   [ 4: 0]    CASE1_CF_TYPE_LONG            R/W  default = 0


---------------------------------------------------------------------------------
    Address  : 0x4008014c
    Name     : RSP_CASE2
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   - Response Case 2 : Send BA
   - CF_TYPE_NONE : 0
   - CF_TYPE_CTS  : 2
   - CF_TYPE_ACK  : 3
   - CF_TYPE_BA   : 4
   - CF_TYPE_NDPCTS               : 6
   - CF_TYPE_NDPACK               : 7
   - CF_TYPE_NDPACK_Default       : 8
   - CF_TYPE_NDPPSPOLLACK         : 9
   - CF_TYPE_NDPPSPOLLACK Default : 10
   - CF_TYPE_NDPBA                : 11
   [   31]    CASE2_IRQ_NO                  R/W  default = 0

   [28:24]    CASE2_CF_TYPE_NO              R/W  default = 0

   [   23]    CASE2_IRQ_NDP                 R/W  default = 0

   [20:16]    CASE2_CF_TYPE_NDP             R/W  default = 11

   [   15]    CASE2_IRQ_NORMAL              R/W  default = 0

   [12: 8]    CASE2_CF_TYPE_NORMAL          R/W  default = 4

   [    7]    CASE2_IRQ_LONG                R/W  default = 0

   [ 4: 0]    CASE2_CF_TYPE_LONG            R/W  default = 0


---------------------------------------------------------------------------------
    Address  : 0x40080150
    Name     : RSP_CASE3
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   - Response Case 3 : Send CTS_STA
   - CF_TYPE_NONE : 0
   - CF_TYPE_CTS  : 2
   - CF_TYPE_ACK  : 3
   - CF_TYPE_BA   : 4
   - CF_TYPE_NDPCTS               : 6
   - CF_TYPE_NDPACK               : 7
   - CF_TYPE_NDPACK_Default       : 8
   - CF_TYPE_NDPPSPOLLACK         : 9
   - CF_TYPE_NDPPSPOLLACK Default : 10
   - CF_TYPE_NDPBA                : 11
   [   31]    CASE3_IRQ_NO                  R/W  default = 0

   [28:24]    CASE3_CF_TYPE_NO              R/W  default = 0

   [   23]    CASE3_IRQ_NDP                 R/W  default = 0

   [20:16]    CASE3_CF_TYPE_NDP             R/W  default = 6

   [   15]    CASE3_IRQ_NORMAL              R/W  default = 0

   [12: 8]    CASE3_CF_TYPE_NORMAL          R/W  default = 2

   [    7]    CASE3_IRQ_LONG                R/W  default = 0

   [ 4: 0]    CASE3_CF_TYPE_LONG            R/W  default = 0


---------------------------------------------------------------------------------
    Address  : 0x40080154
    Name     : RSP_CASE4
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   - Response Case 4 : Send CTS_AP
   - CF_TYPE_NONE : 0
   - CF_TYPE_CTS  : 2
   - CF_TYPE_ACK  : 3
   - CF_TYPE_BA   : 4
   - CF_TYPE_NDPCTS               : 6
   - CF_TYPE_NDPACK               : 7
   - CF_TYPE_NDPACK_Default       : 8
   - CF_TYPE_NDPPSPOLLACK         : 9
   - CF_TYPE_NDPPSPOLLACK Default : 10
   - CF_TYPE_NDPBA                : 11
   [   31]    CASE4_IRQ_NO                  R/W  default = 0

   [28:24]    CASE4_CF_TYPE_NO              R/W  default = 0

   [   23]    CASE4_IRQ_NDP                 R/W  default = 0

   [20:16]    CASE4_CF_TYPE_NDP             R/W  default = 6

   [   15]    CASE4_IRQ_NORMAL              R/W  default = 0

   [12: 8]    CASE4_CF_TYPE_NORMAL          R/W  default = 2

   [    7]    CASE4_IRQ_LONG                R/W  default = 0

   [ 4: 0]    CASE4_CF_TYPE_LONG            R/W  default = 0


---------------------------------------------------------------------------------
    Address  : 0x40080158
    Name     : RSP_CASE5
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   - Response Case 5 : Send PSPOLL
   - CF_TYPE_NONE : 0
   - CF_TYPE_CTS  : 2
   - CF_TYPE_ACK  : 3
   - CF_TYPE_BA   : 4
   - CF_TYPE_NDPCTS               : 6
   - CF_TYPE_NDPACK               : 7
   - CF_TYPE_NDPACK_Default       : 8
   - CF_TYPE_NDPPSPOLLACK         : 9
   - CF_TYPE_NDPPSPOLLACK Default : 10
   - CF_TYPE_NDPBA                : 11
   [   31]    CASE5_IRQ_NO                  R/W  default = 0

   [28:24]    CASE5_CF_TYPE_NO              R/W  default = 0

   [   23]    CASE5_IRQ_NDP                 R/W  default = 1

   [20:16]    CASE5_CF_TYPE_NDP             R/W  default = 8

   [   15]    CASE5_IRQ_NORMAL              R/W  default = 1

   [12: 8]    CASE5_CF_TYPE_NORMAL          R/W  default = 3

   [    7]    CASE5_IRQ_LONG                R/W  default = 0

   [ 4: 0]    CASE5_CF_TYPE_LONG            R/W  default = 0


---------------------------------------------------------------------------------
    Address  : 0x4008015c
    Name     : RSP_CASE6
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   - Response Case 6 : Send NDP_PSPOLL
   - CF_TYPE_NONE : 0
   - CF_TYPE_CTS  : 2
   - CF_TYPE_ACK  : 3
   - CF_TYPE_BA   : 4
   - CF_TYPE_NDPCTS               : 6
   - CF_TYPE_NDPACK               : 7
   - CF_TYPE_NDPACK_Default       : 8
   - CF_TYPE_NDPPSPOLLACK         : 9
   - CF_TYPE_NDPPSPOLLACK Default : 10
   - CF_TYPE_NDPBA                : 11
   [   31]    CASE6_IRQ_NO                  R/W  default = 0

   [28:24]    CASE6_CF_TYPE_NO              R/W  default = 0

   [   23]    CASE6_IRQ_NDP                 R/W  default = 1

   [20:16]    CASE6_CF_TYPE_NDP             R/W  default = 10

   [   15]    CASE6_IRQ_NORMAL              R/W  default = 1

   [12: 8]    CASE6_CF_TYPE_NORMAL          R/W  default = 10

   [    7]    CASE6_IRQ_LONG                R/W  default = 0

   [ 4: 0]    CASE6_CF_TYPE_LONG            R/W  default = 0


---------------------------------------------------------------------------------
    Address  : 0x40080160
    Name     : RSP_CASE7
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    RSP_CASE7                     R/W  default = 0
               -Response Frame Type


---------------------------------------------------------------------------------
    Address  : 0x40080164
    Name     : RSP_CASE8
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    RSP_CASE8                     R/W  default = 0
               -Response Frame Type


---------------------------------------------------------------------------------
    Address  : 0x40080168
    Name     : RSP_CASE9
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    RSP_CASE9                     R/W  default = 0
               -Response Frame Type


---------------------------------------------------------------------------------
    Address  : 0x4008016c
    Name     : RSP_CASE10
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    RSP_CASE10                    R/W  default = 0
               -Response Frame Type


---------------------------------------------------------------------------------
    Address  : 0x40080170
    Name     : RSP_CASE11
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    RSP_CASE11                    R/W  default = 0
               -Response Frame Type


---------------------------------------------------------------------------------
    Address  : 0x40080174
    Name     : WAIT_MODE_WR
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [   28]    RXINFO_READ_SKIP              R/W  default = 0

   [   27]    RXINFO_WRITE_SKIP             R/W  default = 0

   [   26]    RXINFO_4SET_ENABLE            R/W  default = 0
                 0 : 2 sets (Default)
                 1 : 4 sets (Extension)

   [   24]    AHB_WAIT_MODE_WR_ON           R/W  default = 0
               -Waiting mode for AHB writing. This mode will be used for debugging of AHB bus writing
                 0 : OFF
                 1 : ON

   [23: 8]    AHB_WR_WAIT_CLOCK             R/W  default = 10000
               -The number of waiting clock(MAC clock) in one waiting operation

   [ 7: 0]    AHB_WR_WAIT_INTERVAL          R/W  default = 200
               -How often will AHB bus transactions be waited


---------------------------------------------------------------------------------
    Address  : 0x40080178
    Name     : WAIT_MODE_RD
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [   24]    AHB_WAIT_MODE_RD_ON           R/W  default = 0
               -Waiting mode for AHB reading. This mode will be used for debugging of AHB bus reading
                 0 : OFF
                 1 : ON

   [23: 8]    AHB_RD_WAIT_CLOCK             R/W  default = 100
               -The number of waiting clock(MAC clock) in one waiting operation

   [ 7: 0]    AHB_RD_WAIT_INTERVAL          R/W  default = 20
               -How often will AHB bus transactions be waited


---------------------------------------------------------------------------------
    Address  : 0x4008017c
    Name     : TX_COMMAND_0
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   + write_enable
---------------------------------------------------------------------------------
   [31:16]    BUFFER_WORD_OFFSET            R/W  default = 0
               -Word offset from TX_BASE_ADDRESS
               -BUFFER_WORD_OFFSET = (BUFFER Address - TX_BASE_ADDRESS) >> 2
               -For example, when TX_BASE_ADDRESS == 0x12340000,
               -BUFFER_WORD_OFFSET of BUFFERADDRESS 0x12340008 is 2

   [15:14]    BANDWIDTH                     R/W  default = 0
               -Bandwidth of the frame

   [13:10]    AIFSN                         R/W  default = 0
               -AIFSN value used at Random Backoff

   [ 9: 0]    CW_COUNT                      R/W  default = 0
               -RANDOM CW Number (0 ~ Current CW)


---------------------------------------------------------------------------------
    Address  : 0x40080180
    Name     : TX_COMMAND_1
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   + write_enable
---------------------------------------------------------------------------------
   [31: 0]    TX_COMMAND_1                  R/W  default = 0
               -Same as TX_COMMAND_0


---------------------------------------------------------------------------------
    Address  : 0x40080184
    Name     : TX_COMMAND_2
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   + write_enable
---------------------------------------------------------------------------------
   [31: 0]    TX_COMMAND_2                  R/W  default = 0
               -Same as TX_COMMAND_0


---------------------------------------------------------------------------------
    Address  : 0x40080188
    Name     : TX_COMMAND_3
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   + write_enable
---------------------------------------------------------------------------------
   [31: 0]    TX_COMMAND_3                  R/W  default = 0
               -Same as TX_COMMAND_0


---------------------------------------------------------------------------------
    Address  : 0x4008018c
    Name     : TX_COMMAND_4
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   + write_enable
---------------------------------------------------------------------------------
   [31: 0]    TX_COMMAND_4                  R/W  default = 0
               -Same as TX_COMMAND_0


---------------------------------------------------------------------------------
    Address  : 0x40080190
    Name     : TX_COMMAND_5
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   + write_enable
---------------------------------------------------------------------------------
   [31: 0]    TX_COMMAND_5                  R/W  default = 0
               -Same as TX_COMMAND_0


---------------------------------------------------------------------------------
    Address  : 0x40080194
    Name     : TX_COMMAND_6
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   + write_enable
---------------------------------------------------------------------------------
   [31: 0]    TX_COMMAND_6                  R/W  default = 0
               -Same as TX_COMMAND_0


---------------------------------------------------------------------------------
    Address  : 0x40080198
    Name     : TX_COMMAND_7
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   + write_enable
---------------------------------------------------------------------------------
   [31: 0]    TX_COMMAND_7                  R/W  default = 0
               -Same as TX_COMMAND_0


---------------------------------------------------------------------------------
    Address  : 0x4008019c
    Name     : TX_COMMAND_8
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   + write_enable
---------------------------------------------------------------------------------
   [31: 0]    TX_COMMAND_8                  R/W  default = 0
               -Same as TX_COMMAND_0


---------------------------------------------------------------------------------
    Address  : 0x400801a0
    Name     : TX_COMMAND_9
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   + write_enable
---------------------------------------------------------------------------------
   [31: 0]    TX_COMMAND_9                  R/W  default = 0
               -Same as TX_COMMAND_0


---------------------------------------------------------------------------------
    Address  : 0x400801a4
    Name     : TX_COMMAND_10
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   + write_enable
---------------------------------------------------------------------------------
   [31: 0]    TX_COMMAND_10                 R/W  default = 0
               -Same as TX_COMMAND_0


---------------------------------------------------------------------------------
    Address  : 0x400801a8
    Name     : TXOP_COMMAND_0
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   + write_enable
---------------------------------------------------------------------------------
   [31:16]    BUFFER_WORD_OFFSET            R/W  default = 0
               -Word offset from TX_BASE_ADDRESS
               -BUFFER_WORD_OFFSET = (BUFFER Address - TX_BASE_ADDRESS) >> 2
               -For example, when TX_BASE_ADDRESS == 0x12340000,
               -BUFFER_WORD_OFFSET of BUFFERADDRESS 0x12340008 is 2

   [15: 0]    TX_TIME                       R/W  default = 0
               -TX TIME(+Response time) : unit us


---------------------------------------------------------------------------------
    Address  : 0x400801ac
    Name     : TXOP_COMMAND_1
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   + write_enable
---------------------------------------------------------------------------------
   [31: 0]    TXOP_COMMAND_1                R/W  default = 0
               -Same as TXOP_COMMAND_0


---------------------------------------------------------------------------------
    Address  : 0x400801b0
    Name     : TXOP_COMMAND_2
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   + write_enable
---------------------------------------------------------------------------------
   [31: 0]    TXOP_COMMAND_2                R/W  default = 0
               -Same as TXOP_COMMAND_0


---------------------------------------------------------------------------------
    Address  : 0x400801b4
    Name     : TXOP_COMMAND_3
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   + write_enable
---------------------------------------------------------------------------------
   [31: 0]    TXOP_COMMAND_3                R/W  default = 0
               -Same as TXOP_COMMAND_0


---------------------------------------------------------------------------------
    Address  : 0x400801b8
    Name     : TXOP_COMMAND_4
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   + write_enable
---------------------------------------------------------------------------------
   [31: 0]    TXOP_COMMAND_4                R/W  default = 0
               -Same as TXOP_COMMAND_0


---------------------------------------------------------------------------------
    Address  : 0x400801bc
    Name     : TXOP_COMMAND_5
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   + write_enable
---------------------------------------------------------------------------------
   [31: 0]    TXOP_COMMAND_5                R/W  default = 0
               -Same as TXOP_COMMAND_0


---------------------------------------------------------------------------------
    Address  : 0x400801c0
    Name     : TXOP_COMMAND_6
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   + write_enable
---------------------------------------------------------------------------------
   [31: 0]    TXOP_COMMAND_6                R/W  default = 0
               -Same as TXOP_COMMAND_0


---------------------------------------------------------------------------------
    Address  : 0x400801c4
    Name     : TXOP_COMMAND_7
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   + write_enable
---------------------------------------------------------------------------------
   [31: 0]    TXOP_COMMAND_7                R/W  default = 0
               -Same as TXOP_COMMAND_0


---------------------------------------------------------------------------------
    Address  : 0x400801c8
    Name     : TXOP_COMMAND_8
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   + write_enable
---------------------------------------------------------------------------------
   [31: 0]    TXOP_COMMAND_8                R/W  default = 0
               -Same as TXOP_COMMAND_0


---------------------------------------------------------------------------------
    Address  : 0x400801cc
    Name     : TXOP_COMMAND_9
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   + write_enable
---------------------------------------------------------------------------------
   [31: 0]    TXOP_COMMAND_9                R/W  default = 0
               -Same as TXOP_COMMAND_0


---------------------------------------------------------------------------------
    Address  : 0x400801d0
    Name     : TXOP_COMMAND_10
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   + write_enable
---------------------------------------------------------------------------------
   [31: 0]    TXOP_COMMAND_10               R/W  default = 0
               -Same as TXOP_COMMAND_0


---------------------------------------------------------------------------------
    Address  : 0x400801d4
    Name     : TX_GAIN_LOWER_0
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    TX_GAIN_LOWER_0               R/W  default = 0
               -TX GAIN lower 32bit for TX_COMMAND_0
               -   : BIT[ 9: 0] - TXLO_PARA_Q
               -   : BIT[19:10] - TXLO_PARA_I
               -   : BIT[30:20] - TXIQ_PARA_1
               -   : BIT[31]    - TXIQ_PARA_0[0]


---------------------------------------------------------------------------------
    Address  : 0x400801d8
    Name     : TX_GAIN_UPPER_0
    Bit      : 26
    R/W      : R/W
---------------------------------------------------------------------------------
   [25: 0]    TX_GAIN_UPPER_0               R/W  default = 0
               -TX GAIN upper 26bit for TX_COMMAND_0
               -   : BIT[ 9: 0] - TXIQ_PARA_0[10:1]
               -   : BIT[25:10] - TX_DIGITAL_GAIN


---------------------------------------------------------------------------------
    Address  : 0x400801dc
    Name     : TX_GAIN_LOWER_1
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    TX_GAIN_LOWER_1               R/W  default = 0
               -TX GAIN lower 32bit for TX_COMMAND_1


---------------------------------------------------------------------------------
    Address  : 0x400801e0
    Name     : TX_GAIN_UPPER_1
    Bit      : 26
    R/W      : R/W
---------------------------------------------------------------------------------
   [25: 0]    TX_GAIN_UPPER_1               R/W  default = 0
               -TX GAIN upper 26bit for TX_COMMAND_1


---------------------------------------------------------------------------------
    Address  : 0x400801e4
    Name     : TX_GAIN_LOWER_2
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    TX_GAIN_LOWER_2               R/W  default = 0
               -TX GAIN lower 32bit for TX_COMMAND_2


---------------------------------------------------------------------------------
    Address  : 0x400801e8
    Name     : TX_GAIN_UPPER_2
    Bit      : 26
    R/W      : R/W
---------------------------------------------------------------------------------
   [25: 0]    TX_GAIN_UPPER_2               R/W  default = 0
               -TX GAIN upper 26bit for TX_COMMAND_2


---------------------------------------------------------------------------------
    Address  : 0x400801ec
    Name     : TX_GAIN_LOWER_3
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    TX_GAIN_LOWER_3               R/W  default = 0
               -TX GAIN lower 32bit for TX_COMMAND_3


---------------------------------------------------------------------------------
    Address  : 0x400801f0
    Name     : TX_GAIN_UPPER_3
    Bit      : 26
    R/W      : R/W
---------------------------------------------------------------------------------
   [25: 0]    TX_GAIN_UPPER_3               R/W  default = 0
               -TX GAIN upper 26bit for TX_COMMAND_3


---------------------------------------------------------------------------------
    Address  : 0x400801f4
    Name     : TX_GAIN_LOWER_4
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    TX_GAIN_LOWER_4               R/W  default = 0
               -TX GAIN lower 32bit for TX_COMMAND_4


---------------------------------------------------------------------------------
    Address  : 0x400801f8
    Name     : TX_GAIN_UPPER_4
    Bit      : 26
    R/W      : R/W
---------------------------------------------------------------------------------
   [25: 0]    TX_GAIN_UPPER_4               R/W  default = 0
               -TX GAIN upper 26bit for TX_COMMAND_4


---------------------------------------------------------------------------------
    Address  : 0x400801fc
    Name     : TX_GAIN_LOWER_5
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    TX_GAIN_LOWER_5               R/W  default = 0
               -TX GAIN lower 32bit for TX_COMMAND_5


---------------------------------------------------------------------------------
    Address  : 0x40080200
    Name     : TX_GAIN_UPPER_5
    Bit      : 26
    R/W      : R/W
---------------------------------------------------------------------------------
   [25: 0]    TX_GAIN_UPPER_5               R/W  default = 0
               -TX GAIN upper 26bit for TX_COMMAND_5


---------------------------------------------------------------------------------
    Address  : 0x40080204
    Name     : TX_GAIN_LOWER_6
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    TX_GAIN_LOWER_6               R/W  default = 0
               -TX GAIN lower 32bit for TX_COMMAND_6


---------------------------------------------------------------------------------
    Address  : 0x40080208
    Name     : TX_GAIN_UPPER_6
    Bit      : 26
    R/W      : R/W
---------------------------------------------------------------------------------
   [25: 0]    TX_GAIN_UPPER_6               R/W  default = 0
               -TX GAIN upper 26bit for TX_COMMAND_6


---------------------------------------------------------------------------------
    Address  : 0x4008020c
    Name     : TX_GAIN_LOWER_7
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    TX_GAIN_LOWER_7               R/W  default = 0
               -TX GAIN lower 32bit for TX_COMMAND_7


---------------------------------------------------------------------------------
    Address  : 0x40080210
    Name     : TX_GAIN_UPPER_7
    Bit      : 26
    R/W      : R/W
---------------------------------------------------------------------------------
   [25: 0]    TX_GAIN_UPPER_7               R/W  default = 0
               -TX GAIN upper 26bit for TX_COMMAND_7


---------------------------------------------------------------------------------
    Address  : 0x40080214
    Name     : TX_GAIN_LOWER_8
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    TX_GAIN_LOWER_8               R/W  default = 0
               -TX GAIN lower 32bit for TX_COMMAND_8


---------------------------------------------------------------------------------
    Address  : 0x40080218
    Name     : TX_GAIN_UPPER_8
    Bit      : 26
    R/W      : R/W
---------------------------------------------------------------------------------
   [25: 0]    TX_GAIN_UPPER_8               R/W  default = 0
               -TX GAIN upper 26bit for TX_COMMAND_8


---------------------------------------------------------------------------------
    Address  : 0x4008021c
    Name     : TX_GAIN_LOWER_9
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    TX_GAIN_LOWER_9               R/W  default = 0
               -TX GAIN lower 32bit for TX_COMMAND_9


---------------------------------------------------------------------------------
    Address  : 0x40080220
    Name     : TX_GAIN_UPPER_9
    Bit      : 26
    R/W      : R/W
---------------------------------------------------------------------------------
   [25: 0]    TX_GAIN_UPPER_9               R/W  default = 0
               -TX GAIN upper 26bit for TX_COMMAND_9


---------------------------------------------------------------------------------
    Address  : 0x40080224
    Name     : TX_GAIN_LOWER_10
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    TX_GAIN_LOWER_10              R/W  default = 0
               -TX GAIN lower 32bit for TX_COMMAND_10


---------------------------------------------------------------------------------
    Address  : 0x40080228
    Name     : TX_GAIN_UPPER_10
    Bit      : 26
    R/W      : R/W
---------------------------------------------------------------------------------
   [25: 0]    TX_GAIN_UPPER_10              R/W  default = 0
               -TX GAIN upper 26bit for TX_COMMAND_10


---------------------------------------------------------------------------------
    Address  : 0x4008022c
    Name     : TX_GAIN_LOWER_CF
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    TX_GAIN_LOWER_CF              R/W  default = 0
               -TX GAIN lower 32bit for Control Frame


---------------------------------------------------------------------------------
    Address  : 0x40080230
    Name     : TX_GAIN_UPPER_CF
    Bit      : 26
    R/W      : R/W
---------------------------------------------------------------------------------
   [25: 0]    TX_GAIN_UPPER_CF              R/W  default = 0
               -TX GAIN upper 26bit for Control Frame


---------------------------------------------------------------------------------
    Address  : 0x40080234
    Name     : TX_RAW_EDCA_0
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31:16]    TX_TIME                       R/W  default = 0
               -TX TIME(+Response time) : unit us

   [13:10]    AIFSN_RAW                     R/W  default = 0
               -AIFSN value used at Random Backoff in RAW

   [ 9: 0]    CW_COUNT_RAW                  R/W  default = 0
               -RANDOM CW Number (0 ~ Current CW) in RAW


---------------------------------------------------------------------------------
    Address  : 0x40080238
    Name     : TX_RAW_EDCA_1
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    TX_RAW_EDCA_1                 R/W  default = 0
               -Same as TX_RAW_EDCA_0


---------------------------------------------------------------------------------
    Address  : 0x4008023c
    Name     : TX_RAW_EDCA_2
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    TX_RAW_EDCA_2                 R/W  default = 0
               -Same as TX_RAW_EDCA_0


---------------------------------------------------------------------------------
    Address  : 0x40080240
    Name     : TX_RAW_EDCA_3
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    TX_RAW_EDCA_3                 R/W  default = 0
               -Same as TX_RAW_EDCA_0


---------------------------------------------------------------------------------
    Address  : 0x40080244
    Name     : TX_RAW_EDCA_4
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    TX_RAW_EDCA_4                 R/W  default = 0
               -Same as TX_RAW_EDCA_0


---------------------------------------------------------------------------------
    Address  : 0x40080248
    Name     : TX_RAW_EDCA_5
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    TX_RAW_EDCA_5                 R/W  default = 0
               -Same as TX_RAW_EDCA_0


---------------------------------------------------------------------------------
    Address  : 0x4008024c
    Name     : TX_BASE_ADDRESS
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    TX_BASE_ADDRESS               R/W  default = 0
               -Base Address of TX Buffer


---------------------------------------------------------------------------------
    Address  : 0x40080250
    Name     : TSW_DATA_IN_WAIT
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    TSW_DATA_IN_WAIT              R/W  default = 0


---------------------------------------------------------------------------------
    Address  : 0x40080254
    Name     : TX_SUPPRESS_COMMAND
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   + write_enable
---------------------------------------------------------------------------------
   [   31]    REFERENC_TSF                  R/W  default = 0
               -Select TSF for referring the configuration

   [   30]    XROSS_BOUNDARY                R/W  default = 0
               -Cross Slot Boundary Enable in the assigned RAW

   [   29]    HOLD_AFTER_SUPPRESS           R/W  default = 0
               -Hold transmit after Tx suppress

   [   15]    MYRAW_CMD_VALID               R/W  default = 0
               -Valid for MYRAW Command : '0' means that it doesn't care the command

   [11: 8]    MYRAW_COMMAND                 R/W  default = 0
               -Command for the assigne RAW period. Same as Suppression command

   [    7]    SUPPRESS_CMD_VALID            R/W  default = 0
               -Valid for Suppression Command : '0' means that it doesn't care the command

   [ 3: 0]    SUPPRESS_COMMAND              R/W  default = 0
               -Command is as below
                 7 : Force to exit a suppression mode immediately
                 6 : Start suppression immediately and it is ended when specified duration (refer TX_SUPPRESS_DURATION register) is expired
                 5 : Start suppression immediately and it is ended when lower 32 bit TSF timer reaches specified value (refer to TX_SUPPRESS_END_TSF register)
                 4 : Start suppression when TSF reaches specified value (refer to TX_SUPPRESS_START_TSF register) and it is ended when specified duration (refer TX_SUPPRESS_DURATION) is expired since it begins suppression
                 3 : Start suppression when TSF timer reaches specified value (STAR_TSF register) and then it is scheduled to be ended when TSF timer reaches specified value (END_TSF register)
                 2 : Start suppression immediately
                 1 : Start suppression when TSF timer reaches specified value resides in 'TX_SUPPRESS_START_TSF' register. Suppression continues permanently until any external command enters
                 0 : Make an internal FSM return to idle state


---------------------------------------------------------------------------------
    Address  : 0x40080258
    Name     : TX_SUPPRESS_START_TSF
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    TX_SUPPRESS_START_TSF         R/W  default = 0
               -Start time of Tx suppression rely on TSF


---------------------------------------------------------------------------------
    Address  : 0x4008025c
    Name     : TX_SUPPRESS_END_TSF
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    TX_SUPPRESS_END_TSF           R/W  default = 0
               -End time of Tx suppression. It relies on TSF


---------------------------------------------------------------------------------
    Address  : 0x40080260
    Name     : TX_SUPPRESS_DURATION
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    TX_SUPPRESS_DURATION          R/W  default = 1024
               -Duration of Tx suppression


---------------------------------------------------------------------------------
    Address  : 0x40080264
    Name     : TX_MYRAW_START_TSF
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    TX_MYRAW_START_TSF            R/W  default = 0
               -Start time of the assigned RAW. It relies on TSF


---------------------------------------------------------------------------------
    Address  : 0x40080268
    Name     : TX_MYRAW_END_TSF
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    TX_MYRAW_END_TSF              R/W  default = 0
               -End time of the assigned RAW. It relies on TSF


---------------------------------------------------------------------------------
    Address  : 0x4008026c
    Name     : TX_MYRAW_DURATION
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    TX_MYRAW_DURATION             R/W  default = 1024
               -Duration of the assigned RAW


---------------------------------------------------------------------------------
    Address  : 0x40080270
    Name     : TX_SUPPRESS_SETTING
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    TX_SUPPRESS_SETTING           R/W  default = 0
               -Specify the queue not to transmit when the suppression command is active state
               -[31:12] : Reserved
               -[11] : SIFS Queue
               -[10] : Queue10
               -[9] : Queue9
               -[8] : Queue8
               -[7] : Queue7
               -[6] : Queue6
               -[5] : Queue5
               -[4] : Queue4
               -[3] : Queue3
               -[2] : Queue2
               -[1] : Queue1
               -[0] : Queue0


---------------------------------------------------------------------------------
    Address  : 0x40080274
    Name     : TX_SUPPRESS_STATUS
    Bit      : 32
    R/W      : R
---------------------------------------------------------------------------------
   [15:12]    MYRAW_CMD                     R    default = 0
               -Show the latest MYRAW_CMD

   [11: 8]    SUPPRESS_CMD                  R    default = 0
               -Show the latest SUPPRESS_CMD

   [    3]    REFERENCE_TSF                 R    default = 0
               -0: TSF 0 is the command referece
               -1: TSF 1 is the command referece

   [    2]    XROSS_BOUNDARY                R    default = 0
               -0: Cross Slot Boundary is disabled
               -1: Cross Slot Boundary is enabled

   [    1]    TX_MYRAW_PERIOD               R    default = 0
               -0: the current status is not the assigned period
               -1: the current status is assigned period

   [    0]    TX_SUPPRESS_PERIOD            R    default = 0
               -0: the current status is not the TX suppression period
               -1: the current status is TX suppression period


---------------------------------------------------------------------------------
    Address  : 0x40080278
    Name     : TX_DATA_IN_WAIT
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [   31]    SECURITY_OFFLINE              R/W  default = 0
               -Disable inline security mode in TX Side

   [15: 8]    TIKIP_DATA_IN_WAIT            R/W  default = 38
               -WAIT Counter for TKIP/WEP block input in Tx SEC interface module

   [ 7: 0]    CCMP_DATA_IN_WAIT             R/W  default = 11
               -WAIT Counter for CCMP block input in Tx SEC interface module


---------------------------------------------------------------------------------
    Address  : 0x4008027c
    Name     : PHY_TXFIFO_MAX_DEPTH
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    PHY_TXFIFO_MAX_DEPTH          R/W  default = 24
               -This value is used at flow control of tx data not to exceed PHY TX FIFO limit


---------------------------------------------------------------------------------
    Address  : 0x40080280
    Name     : TXNAV_VALUE
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   + write_enable
---------------------------------------------------------------------------------
   [31: 0]    TXNAV_VALUE                   R/W  default = 0
               -SW can configures TXNAV by writing this register


---------------------------------------------------------------------------------
    Address  : 0x40080284
    Name     : RXNAV_VALUE
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   + write_enable
---------------------------------------------------------------------------------
   [31: 0]    RXNAV_VALUE                   R/W  default = 0
               -SW can configures RXNAV by writing this register


---------------------------------------------------------------------------------
    Address  : 0x40080288
    Name     : RID_VALUE
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   + write_enable
---------------------------------------------------------------------------------
   [31: 0]    RID_VALUE                     R/W  default = 0
               -SW can configures RID by writing this register


---------------------------------------------------------------------------------
    Address  : 0x4008028c
    Name     : NAV_RESET
    Bit      : 1
    R/W      : R/W
---------------------------------------------------------------------------------
   + write_enable
---------------------------------------------------------------------------------
   [    0]    NAV_RESET                     R/W  default = 0
               -SW can reset RXNAV to zero


---------------------------------------------------------------------------------
    Address  : 0x40080290
    Name     : RID_RESET
    Bit      : 1
    R/W      : R/W
---------------------------------------------------------------------------------
   + write_enable
---------------------------------------------------------------------------------
   [    0]    RID_RESET                     R/W  default = 0
               -SW can reset RID to zero


---------------------------------------------------------------------------------
    Address  : 0x40080294
    Name     : NAV_RID_CONTROL_MODE
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    NAV_RID_CONTROL_MODE          R/W  default = 0
                 1 : HW module configures RXNAV and RID automatically
                 0 : SW manually configures RXNAV and RID


---------------------------------------------------------------------------------
    Address  : 0x40080298
    Name     : TXNAV_HW_SETTING_VALUE
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    TXNAV_HW_SETTING_VALUE        R/W  default = 0
               -[16]  : Setting mode
               -[15:0]: TXNAV value used by HW
                 1 : Disable
                 0 : HW overwrites with configured value


---------------------------------------------------------------------------------
    Address  : 0x4008029c
    Name     : PREAMBLE_TYPE
    Bit      : 1
    R/W      : R/W
---------------------------------------------------------------------------------
   [    0]    PREAMBLE_TYPE                 R/W  default = 0
               -The preamble type field in response control frames


---------------------------------------------------------------------------------
    Address  : 0x400802a0
    Name     : CF_FIX_MOREDATA
    Bit      : 1
    R/W      : R/W
---------------------------------------------------------------------------------
   [    0]    CF_FIX_MOREDATA               R/W  default = 0
               -If the value is 1, More Data field is set to 1. Otherwise, More Data field is decided as normally.


---------------------------------------------------------------------------------
    Address  : 0x400802a4
    Name     : SET_PS_POLL_ACK_SW
    Bit      : 30
    R/W      : R/W
---------------------------------------------------------------------------------
   + separate
---------------------------------------------------------------------------------
   [29:16]    REG_SW_DURATION               R/W  default = 0
               -The duration field in ndp ps-poll ack(sw)

   [    4]    REG_SW_MOREDATA               R/W  default = 0
               -The moredata field in ndp ps-poll ack(sw)

   [    0]    REG_SW_IDLE_INDICATION        R/W  default = 0
               -The idle indication field in ndp ps-poll ack(sw)


---------------------------------------------------------------------------------
    Address  : 0x400802a8
    Name     : SET_PS_POLL_ACK_DEFAULT
    Bit      : 30
    R/W      : R/W
---------------------------------------------------------------------------------
   + separate
---------------------------------------------------------------------------------
   [29:16]    REG_DEFAULT_DURATION          R/W  default = 0
               -The duration field in ps-poll ack(default)

   [    4]    REG_DEFAULT_MOREDATA          R/W  default = 0
               -The moredata field in ndp ps-poll ack(default)

   [    0]    REG_DEFAULT_IDLE_INDICATION   R/W  default = 0
               -The idle indication field in ndp ps-poll ack(default)


---------------------------------------------------------------------------------
    Address  : 0x400802ac
    Name     : SET_RTSRID
    Bit      : 2
    R/W      : R/W
---------------------------------------------------------------------------------
   [ 1: 0]    SET_RTSRID                    R/W  default = 1
               -The response indication field in RTS frame


---------------------------------------------------------------------------------
    Address  : 0x400802b0
    Name     : CF_CHANNEL_WIDTH_SELECTION
    Bit      : 5
    R/W      : R/W
---------------------------------------------------------------------------------
   + separate
---------------------------------------------------------------------------------
   [    4]    REG_1M_RES_PREAMBLE_SUPPORT   R/W  default = 1
               -It indicates the 1mhz response preabmels support

   [    0]    REG_DUP_1M_SUPPORT            R/W  default = 1
               -It indicates the duplicate 1mhz support


---------------------------------------------------------------------------------
    Address  : 0x400802b4
    Name     : SET_FLOW_CONTROL_INFO_0
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   + separate
---------------------------------------------------------------------------------
   [31:16]    SET_TSF_INFO_0                R/W  default = 0
               -Next TWT Suspsend Duration TSF lower bits

   [   10]    REG_PSPOLL_RES_MOREDATA       R/W  default = 0
               -The more data field in tack, bat, and stack

   [    9]    REG_FLOW_CONTROL              R/W  default = 0
               -The flow control field in BAT, TACK, and STACK

   [    8]    REG_NEXT_TWT_INFO_PRESENT     R/W  default = 0
               -The next twt info present field in BAT, TACK, and STACK

   [ 7: 0]    REG_BEACON_SEQUENCE           R/W  default = 0
               -The beacon sequence field in BAT and TACK


---------------------------------------------------------------------------------
    Address  : 0x400802b8
    Name     : SET_FLOW_CONTROL_INFO_1
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    SET_FLOW_CONTROL_INFO_1       R/W  default = 0
               -Next TWT Suspsend Duration TSF Upper bits


---------------------------------------------------------------------------------
    Address  : 0x400802bc
    Name     : SET_ACK_SW
    Bit      : 30
    R/W      : R/W
---------------------------------------------------------------------------------
   + separate
---------------------------------------------------------------------------------
   [29:16]    REG_SW_ACK_DURATION           R/W  default = 0
               -The duration field in ndp ack(sw)

   [    8]    REG_SW_ACK_RELAYED_FRAME      R/W  default = 0
               -The relayed frame field in ndp ack(sw)

   [    4]    REG_SW_ACK_MOREDATA           R/W  default = 0
               -The moredata field in ndp ack(sw)

   [    0]    REG_SW_ACK_IDLE_INDICATION    R/W  default = 0
               -The idle indication field in ndp ack(sw)


---------------------------------------------------------------------------------
    Address  : 0x400802c0
    Name     : SET_ACK_DEFAULT
    Bit      : 30
    R/W      : R/W
---------------------------------------------------------------------------------
   + separate
---------------------------------------------------------------------------------
   [29:16]    REG_DEFAULT_ACK_DURATION      R/W  default = 0
               -The duration field in ndp ack(default)

   [    8]    REG_DEFAULT_ACK_RELAYED_FRAME R/W  default = 0
               -The relayed frame field in ndp ack(default)

   [    4]    REG_DEFAULT_ACK_MOREDATA      R/W  default = 0
               -The moredata field in ndp ack(default)

   [    0]    REG_DEFAULT_ACK_IDLE_INDICATIONR/W  default = 0
               -The idle indication field in ndp ack(default)


---------------------------------------------------------------------------------
    Address  : 0x400802c4
    Name     : BASIC_RATE_BITMAP
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    BASIC_RATE_BITMAP             R/W  default = 523519
               -Basic rate bitmap


---------------------------------------------------------------------------------
    Address  : 0x400802c8
    Name     : BASIC_RATE_BITMAP_2ND
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    BASIC_RATE_BITMAP_2ND         R/W  default = 523519
               -2nd Basic rate bitmap


---------------------------------------------------------------------------------
    Address  : 0x400802cc
    Name     : MCS_DIFFERENCE
    Bit      : 16
    R/W      : R/W
---------------------------------------------------------------------------------
   + separate
---------------------------------------------------------------------------------
   [15:12]    BA_MCS_DIFFERENCE             R/W  default = 0
               -It reduces the mcs value of block ack only

   [11: 4]    MCS_DIFFERENCE_SWITCH         R/W  default = 63
               -A bitmap indicates which response control frame use this feature

   [ 3: 0]    MCS_DIFFERENCE                R/W  default = 0
               -It reduces the mcs value of the response control frames


---------------------------------------------------------------------------------
    Address  : 0x400802d0
    Name     : RESPONSE_TX_COMMAND
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   + write_enable
---------------------------------------------------------------------------------
   [    5]    RESPONSE_TYPE                 R/W  default = 0
                 0 : Use H/W Control Frame Template
                 1 : User defined response control frame

   [ 4: 0]    COMMAND                       R/W  default = 0
               -If RESPONSE_TYPE == 1 , Word Length of Data(MAC Header + Payload)
               -If RESPONSE_TYPE == 0 ,
                 0 : NONE
                 1 : RTS
                 2 : CTS
                 3 : ACK
                 4 : BA
                 5 : CF END
                 6 : CTS TO Self


---------------------------------------------------------------------------------
    Address  : 0x400802d4
    Name     : RSP_TX_VECTOR
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    RSP_TX_VECTOR                 R/W  default = 0
               -First TX_VECTOR of reponse frame


---------------------------------------------------------------------------------
    Address  : 0x400802d8
    Name     : RSP_TX_SIG0
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    RSP_TX_SIG0                   R/W  default = 0
               -Second TX_VECTOR of reponse frame


---------------------------------------------------------------------------------
    Address  : 0x400802dc
    Name     : RSP_TX_SIG1
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    RSP_TX_SIG1                   R/W  default = 0
               -Third TX_VECTOR of reponse frame


---------------------------------------------------------------------------------
    Address  : 0x400802e0
    Name     : RSP_TX_INFO0
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   - First TX_INFO of reponse frame
   [28:23]    RSP_TXINFO_TIMESTAMP_POSITION R/W  default = 0

   [   22]    RSP_TXINFO_TIMESTAMP_UPDATE   R/W  default = 0

   [17:15]    RSP_TXINFO_CIPHER_TYPE        R/W  default = 0

   [   14]    RSP_TXINFO_SINGLE_AMPDU       R/W  default = 0

   [13: 0]    RSP_TXINFO_MPDU_LENGTH        R/W  default = 0


---------------------------------------------------------------------------------
    Address  : 0x400802e4
    Name     : RSP_TX_INFO1
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   - Second TX_INFO of reponse frame
   [23:21]    RSP_TXINFO_FORMAT             R/W  default = 0

   [   20]    RSP_TXINFO_AGGREGATION        R/W  default = 0

   [19: 0]    RSP_TXINFO_PSDU_LENGTH        R/W  default = 0


---------------------------------------------------------------------------------
    Address  : 0x400802e8
    Name     : RSP_TX_DATA0
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    RSP_TX_DATA0                  R/W  default = 0
               -TX_DATA0 of response frame


---------------------------------------------------------------------------------
    Address  : 0x400802ec
    Name     : RSP_TX_DATA1
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    RSP_TX_DATA1                  R/W  default = 0
               -TX_DATA1 of response frame


---------------------------------------------------------------------------------
    Address  : 0x400802f0
    Name     : RSP_TX_DATA2
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    RSP_TX_DATA2                  R/W  default = 0
               -TX_DATA2 of response frame


---------------------------------------------------------------------------------
    Address  : 0x400802f4
    Name     : RSP_TX_DATA3
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    RSP_TX_DATA3                  R/W  default = 0
               -TX_DATA3 of response frame


---------------------------------------------------------------------------------
    Address  : 0x400802f8
    Name     : RSP_TX_DATA4
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    RSP_TX_DATA4                  R/W  default = 0
               -TX_DATA4 of response frame


---------------------------------------------------------------------------------
    Address  : 0x400802fc
    Name     : RSP_TX_DATA5
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    RSP_TX_DATA5                  R/W  default = 0
               -TX_DATA5 of response frame


---------------------------------------------------------------------------------
    Address  : 0x40080300
    Name     : RSP_TX_DATA6
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    RSP_TX_DATA6                  R/W  default = 0
               -TX_DATA6 of response frame


---------------------------------------------------------------------------------
    Address  : 0x40080304
    Name     : RSP_TX_DATA7
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    RSP_TX_DATA7                  R/W  default = 0
               -TX_DATA7 of response frame


---------------------------------------------------------------------------------
    Address  : 0x40080308
    Name     : RSP_TX_DATA8
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    RSP_TX_DATA8                  R/W  default = 0
               -TX_DATA8 of response frame


---------------------------------------------------------------------------------
    Address  : 0x4008030c
    Name     : RSP_TX_DATA9
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    RSP_TX_DATA9                  R/W  default = 0
               -TX_DATA9 of response frame


---------------------------------------------------------------------------------
    Address  : 0x40080310
    Name     : RSP_TX_DATA10
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    RSP_TX_DATA10                 R/W  default = 0
               -TX_DATA10 of response frame


---------------------------------------------------------------------------------
    Address  : 0x40080314
    Name     : SET_CF_TXVECTOR_SIG
    Bit      : 18
    R/W      : R/W
---------------------------------------------------------------------------------
   + separate
---------------------------------------------------------------------------------
   - Default value of txvector and sig for response control frame
   [   17]    REG_SIG_UPLINK_IND            R/W  default = 0

   [   16]    REG_SIG_DOPPLER               R/W  default = 0

   [15: 8]    REG_TXPWR_LEVEL               R/W  default = 0

   [    7]    REG_SCRAMBLER_EXIST           R/W  default = 1

   [ 6: 0]    REG_SCRAMBLER_OR_CRC          R/W  default = 1


---------------------------------------------------------------------------------
    Address  : 0x40080318
    Name     : MONITOR_INTERVAL
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    MONITOR_INTERVAL              R/W  default = 0


---------------------------------------------------------------------------------
    Address  : 0x4008031c
    Name     : CCA_RANGE_VAR_SET0
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   - Diagnose current channel status
   - Grouping CCA occurrence based on time range
   [31:16]    RANGE_VAR_1                   R/W  default = 1000

   [15: 0]    RANGE_VAR_0                   R/W  default = 10


---------------------------------------------------------------------------------
    Address  : 0x40080320
    Name     : CCA_RANGE_VAR_SET1
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    CCA_RANGE_VAR_SET1            R/W  default = 10000
               -Last grouping variable


---------------------------------------------------------------------------------
    Address  : 0x40080324
    Name     : RX_BASE_ADDRESS
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    RX_BASE_ADDRESS               R/W  default = 0
               -Base Address of RX Buffer


---------------------------------------------------------------------------------
    Address  : 0x40080328
    Name     : RX_DSC_NUM
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    RX_DSC_NUM                    R/W  default = 0
               -Number of RX Descriptor
                 0 : Maximum number of Rx buffer 32


---------------------------------------------------------------------------------
    Address  : 0x4008032c
    Name     : RX_REG_DL_DESC0
    Bit      : 26
    R/W      : R/W
---------------------------------------------------------------------------------
   [25:15]    BUFFER_LENGTH                 R/W  default = 1024
               -11bit Byte Length of RX BUFFER

   [14: 0]    DATA_ADDRESS_OFFSET           R/W  default = 0
               -Address of buffer in 4Byte Unit, based on RX_BASE_ADDR


---------------------------------------------------------------------------------
    Address  : 0x40080330
    Name     : RX_REG_DL_DESC1
    Bit      : 26
    R/W      : R/W
---------------------------------------------------------------------------------
   [25: 0]    RX_REG_DL_DESC1               R/W  default = 33554432
               -Same as RX_REG_DL_DESC0


---------------------------------------------------------------------------------
    Address  : 0x40080334
    Name     : RX_REG_DL_DESC2
    Bit      : 26
    R/W      : R/W
---------------------------------------------------------------------------------
   [25: 0]    RX_REG_DL_DESC2               R/W  default = 33554432
               -Same as RX_REG_DL_DESC0


---------------------------------------------------------------------------------
    Address  : 0x40080338
    Name     : RX_REG_DL_DESC3
    Bit      : 26
    R/W      : R/W
---------------------------------------------------------------------------------
   [25: 0]    RX_REG_DL_DESC3               R/W  default = 33554432
               -Same as RX_REG_DL_DESC0


---------------------------------------------------------------------------------
    Address  : 0x4008033c
    Name     : RX_REG_DL_DESC4
    Bit      : 26
    R/W      : R/W
---------------------------------------------------------------------------------
   [25: 0]    RX_REG_DL_DESC4               R/W  default = 33554432
               -Same as RX_REG_DL_DESC0


---------------------------------------------------------------------------------
    Address  : 0x40080340
    Name     : RX_REG_DL_DESC5
    Bit      : 26
    R/W      : R/W
---------------------------------------------------------------------------------
   [25: 0]    RX_REG_DL_DESC5               R/W  default = 33554432
               -Same as RX_REG_DL_DESC0


---------------------------------------------------------------------------------
    Address  : 0x40080344
    Name     : RX_REG_DL_DESC6
    Bit      : 26
    R/W      : R/W
---------------------------------------------------------------------------------
   [25: 0]    RX_REG_DL_DESC6               R/W  default = 33554432
               -Same as RX_REG_DL_DESC0


---------------------------------------------------------------------------------
    Address  : 0x40080348
    Name     : RX_REG_DL_DESC7
    Bit      : 26
    R/W      : R/W
---------------------------------------------------------------------------------
   [25: 0]    RX_REG_DL_DESC7               R/W  default = 33554432
               -Same as RX_REG_DL_DESC0


---------------------------------------------------------------------------------
    Address  : 0x4008034c
    Name     : RX_REG_DL_DESC8
    Bit      : 26
    R/W      : R/W
---------------------------------------------------------------------------------
   [25: 0]    RX_REG_DL_DESC8               R/W  default = 33554432
               -Same as RX_REG_DL_DESC0


---------------------------------------------------------------------------------
    Address  : 0x40080350
    Name     : RX_REG_DL_DESC9
    Bit      : 26
    R/W      : R/W
---------------------------------------------------------------------------------
   [25: 0]    RX_REG_DL_DESC9               R/W  default = 33554432
               -Same as RX_REG_DL_DESC0


---------------------------------------------------------------------------------
    Address  : 0x40080354
    Name     : RX_REG_DL_DESC10
    Bit      : 26
    R/W      : R/W
---------------------------------------------------------------------------------
   [25: 0]    RX_REG_DL_DESC10              R/W  default = 33554432
               -Same as RX_REG_DL_DESC0


---------------------------------------------------------------------------------
    Address  : 0x40080358
    Name     : RX_REG_DL_DESC11
    Bit      : 26
    R/W      : R/W
---------------------------------------------------------------------------------
   [25: 0]    RX_REG_DL_DESC11              R/W  default = 33554432
               -Same as RX_REG_DL_DESC0


---------------------------------------------------------------------------------
    Address  : 0x4008035c
    Name     : RX_REG_DL_DESC12
    Bit      : 26
    R/W      : R/W
---------------------------------------------------------------------------------
   [25: 0]    RX_REG_DL_DESC12              R/W  default = 33554432
               -Same as RX_REG_DL_DESC0


---------------------------------------------------------------------------------
    Address  : 0x40080360
    Name     : RX_REG_DL_DESC13
    Bit      : 26
    R/W      : R/W
---------------------------------------------------------------------------------
   [25: 0]    RX_REG_DL_DESC13              R/W  default = 33554432
               -Same as RX_REG_DL_DESC0


---------------------------------------------------------------------------------
    Address  : 0x40080364
    Name     : RX_REG_DL_DESC14
    Bit      : 26
    R/W      : R/W
---------------------------------------------------------------------------------
   [25: 0]    RX_REG_DL_DESC14              R/W  default = 33554432
               -Same as RX_REG_DL_DESC0


---------------------------------------------------------------------------------
    Address  : 0x40080368
    Name     : RX_REG_DL_DESC15
    Bit      : 26
    R/W      : R/W
---------------------------------------------------------------------------------
   [25: 0]    RX_REG_DL_DESC15              R/W  default = 33554432
               -Same as RX_REG_DL_DESC0


---------------------------------------------------------------------------------
    Address  : 0x4008036c
    Name     : RX_REG_DL_DESC16
    Bit      : 26
    R/W      : R/W
---------------------------------------------------------------------------------
   [25: 0]    RX_REG_DL_DESC16              R/W  default = 33554432
               -Same as RX_REG_DL_DESC0


---------------------------------------------------------------------------------
    Address  : 0x40080370
    Name     : RX_REG_DL_DESC17
    Bit      : 26
    R/W      : R/W
---------------------------------------------------------------------------------
   [25: 0]    RX_REG_DL_DESC17              R/W  default = 33554432
               -Same as RX_REG_DL_DESC0


---------------------------------------------------------------------------------
    Address  : 0x40080374
    Name     : RX_REG_DL_DESC18
    Bit      : 26
    R/W      : R/W
---------------------------------------------------------------------------------
   [25: 0]    RX_REG_DL_DESC18              R/W  default = 33554432
               -Same as RX_REG_DL_DESC0


---------------------------------------------------------------------------------
    Address  : 0x40080378
    Name     : RX_REG_DL_DESC19
    Bit      : 26
    R/W      : R/W
---------------------------------------------------------------------------------
   [25: 0]    RX_REG_DL_DESC19              R/W  default = 33554432
               -Same as RX_REG_DL_DESC0


---------------------------------------------------------------------------------
    Address  : 0x4008037c
    Name     : RX_REG_DL_DESC20
    Bit      : 26
    R/W      : R/W
---------------------------------------------------------------------------------
   [25: 0]    RX_REG_DL_DESC20              R/W  default = 33554432
               -Same as RX_REG_DL_DESC0


---------------------------------------------------------------------------------
    Address  : 0x40080380
    Name     : RX_REG_DL_DESC21
    Bit      : 26
    R/W      : R/W
---------------------------------------------------------------------------------
   [25: 0]    RX_REG_DL_DESC21              R/W  default = 33554432
               -Same as RX_REG_DL_DESC0


---------------------------------------------------------------------------------
    Address  : 0x40080384
    Name     : RX_REG_DL_DESC22
    Bit      : 26
    R/W      : R/W
---------------------------------------------------------------------------------
   [25: 0]    RX_REG_DL_DESC22              R/W  default = 33554432
               -Same as RX_REG_DL_DESC0


---------------------------------------------------------------------------------
    Address  : 0x40080388
    Name     : RX_REG_DL_DESC23
    Bit      : 26
    R/W      : R/W
---------------------------------------------------------------------------------
   [25: 0]    RX_REG_DL_DESC23              R/W  default = 33554432
               -Same as RX_REG_DL_DESC0


---------------------------------------------------------------------------------
    Address  : 0x4008038c
    Name     : RX_REG_DL_DESC24
    Bit      : 26
    R/W      : R/W
---------------------------------------------------------------------------------
   [25: 0]    RX_REG_DL_DESC24              R/W  default = 33554432
               -Same as RX_REG_DL_DESC0


---------------------------------------------------------------------------------
    Address  : 0x40080390
    Name     : RX_REG_DL_DESC25
    Bit      : 26
    R/W      : R/W
---------------------------------------------------------------------------------
   [25: 0]    RX_REG_DL_DESC25              R/W  default = 33554432
               -Same as RX_REG_DL_DESC0


---------------------------------------------------------------------------------
    Address  : 0x40080394
    Name     : RX_REG_DL_DESC26
    Bit      : 26
    R/W      : R/W
---------------------------------------------------------------------------------
   [25: 0]    RX_REG_DL_DESC26              R/W  default = 33554432
               -Same as RX_REG_DL_DESC0


---------------------------------------------------------------------------------
    Address  : 0x40080398
    Name     : RX_REG_DL_DESC27
    Bit      : 26
    R/W      : R/W
---------------------------------------------------------------------------------
   [25: 0]    RX_REG_DL_DESC27              R/W  default = 33554432
               -Same as RX_REG_DL_DESC0


---------------------------------------------------------------------------------
    Address  : 0x4008039c
    Name     : RX_REG_DL_DESC28
    Bit      : 26
    R/W      : R/W
---------------------------------------------------------------------------------
   [25: 0]    RX_REG_DL_DESC28              R/W  default = 33554432
               -Same as RX_REG_DL_DESC0


---------------------------------------------------------------------------------
    Address  : 0x400803a0
    Name     : RX_REG_DL_DESC29
    Bit      : 26
    R/W      : R/W
---------------------------------------------------------------------------------
   [25: 0]    RX_REG_DL_DESC29              R/W  default = 33554432
               -Same as RX_REG_DL_DESC0


---------------------------------------------------------------------------------
    Address  : 0x400803a4
    Name     : RX_REG_DL_DESC30
    Bit      : 26
    R/W      : R/W
---------------------------------------------------------------------------------
   [25: 0]    RX_REG_DL_DESC30              R/W  default = 33554432
               -Same as RX_REG_DL_DESC0


---------------------------------------------------------------------------------
    Address  : 0x400803a8
    Name     : RX_REG_DL_DESC31
    Bit      : 26
    R/W      : R/W
---------------------------------------------------------------------------------
   [25: 0]    RX_REG_DL_DESC31              R/W  default = 33554432
               -Same as RX_REG_DL_DESC0


---------------------------------------------------------------------------------
    Address  : 0x400803ac
    Name     : SET_OWNER_ADDR
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   + write_enable
---------------------------------------------------------------------------------
   [31: 0]    SET_OWNER_ADDR                R/W  default = 0
               -Address of ownership bit set to be 1
               -For example, when SW write 5 on this register, owner bit of 6th(5+1) Rx buffer is reset to 0


---------------------------------------------------------------------------------
    Address  : 0x400803b0
    Name     : RX_DATA_IN_WAIT
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [   31]    SECURITY_OFFLINE              R/W  default = 0
               -Disable inline security mode in RX Side

   [   23]    RX_WAIT_MODE                  R/W  default = 0
               -Tx/Rx arbitration for security mode
               -Rx block waits encryption of Tx block when this mode is on
                 0 : Mode ON
                 1 : Mode OFF

   [ 7: 0]    CCMP_DATA_IN_WAIT             R/W  default = 6
               -WAIT Counter for CCMP block input in Rx SEC interface module


---------------------------------------------------------------------------------
    Address  : 0x400803b4
    Name     : DMA_SEG_THRESHOLD
    Bit      : 15
    R/W      : R/W
---------------------------------------------------------------------------------
   + separate
---------------------------------------------------------------------------------
   [14:12]    DMA_CMD_QUEUE_THRESHOLD       R/W  default = 3

   [10: 8]    ABORT_STOP_MODE               R/W  default = 0
               -CRC ERROR // Length ERROR // Sequence ERROR

   [ 7: 0]    DMA_SEG_THRESHOLD             R/W  default = 8
               -Threshold for Rx DMA Command. Rx DMA command is generated when number of input rx data is bigger than this threshold.


---------------------------------------------------------------------------------
    Address  : 0x400803b8
    Name     : SEC_KEY_CMD
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31:28]    TYPE                          R/W  default = 0
               -Command type
                 0 : ADD KEY
                 1 : DELETE KEY
                 2 : DELETE ALL KEY

   [25:24]    KEY_ID                        R/W  default = 0

   [   20]    KEY_TYPE                      R/W  default = 0
               -key type
                 0 : PTK
                 1 : GTK


---------------------------------------------------------------------------------
    Address  : 0x400803bc
    Name     : SEC_KEY_CMD_EN
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    SEC_KEY_CMD_EN                R/W  default = 0
               -When SW writes key command, this value should be set to '1'
               -And, after operation of key command is done by HW, this value is chaged to '0'


---------------------------------------------------------------------------------
    Address  : 0x400803c0
    Name     : SEC_KEY_VALUE0
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    SEC_KEY_VALUE0                R/W  default = 0
               -LSB 32bit of 128bit KEY


---------------------------------------------------------------------------------
    Address  : 0x400803c4
    Name     : SEC_KEY_VALUE1
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    SEC_KEY_VALUE1                R/W  default = 0
               -Next LSB 32bit of 128bit KEY


---------------------------------------------------------------------------------
    Address  : 0x400803c8
    Name     : SEC_KEY_VALUE2
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    SEC_KEY_VALUE2                R/W  default = 0
               -Next MSB 32bit of 128bit KEY


---------------------------------------------------------------------------------
    Address  : 0x400803cc
    Name     : SEC_KEY_VALUE3
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    SEC_KEY_VALUE3                R/W  default = 0
               -MSB 32bit of 128bit KEY


---------------------------------------------------------------------------------
    Address  : 0x400803d0
    Name     : SEC_STA_ADDRESS0
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    SEC_STA_ADDRESS0              R/W  default = 0
               -LSB 32bit of peer STA's MAC address


---------------------------------------------------------------------------------
    Address  : 0x400803d4
    Name     : SEC_STA_ADDRESS1
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   - MSB 16bit of peer STA's MAC address and AID
   [28:16]    AID                           R/W  default = 0

   [15: 0]    MAC_ADDRESS                   R/W  default = 0


---------------------------------------------------------------------------------
    Address  : 0x400803d8
    Name     : SEC_CCMP_UPDATE_INFO
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [   31]    MOREDATA                      R/W  default = 0

   [   30]    TWT                           R/W  default = 0

   [ 5: 4]    KEY_ID                        R/W  default = 0

   [ 3: 0]    TID                           R/W  default = 0


---------------------------------------------------------------------------------
    Address  : 0x400803dc
    Name     : SEC_CONFIG
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   + separate
---------------------------------------------------------------------------------
   [   31]    SEC_PV0_MANAGEMENT_DEC_BYPASS R/W  default = 0

   [   30]    SEC_PV0_MANAGEMENT_ENC_BYPASS R/W  default = 0

   [   29]    SEC_SPP_ENABLE                R/W  default = 0
               -SPP A-MSDU enable
               -This value is used when making AAD of CCMP

   [   28]    SEC_KEY_LOC_ENABLE            R/W  default = 0


---------------------------------------------------------------------------------
    Address  : 0x400803e0
    Name     : SEC_READ_BASE_ADDR
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   + write_enable
---------------------------------------------------------------------------------
   [31: 0]    SEC_READ_BASE_ADDR            R/W  default = 0
               -Base address of read operation in offline mode


---------------------------------------------------------------------------------
    Address  : 0x400803e4
    Name     : SEC_WRITE_BASE_ADDR
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    SEC_WRITE_BASE_ADDR           R/W  default = 0
               -Base address of write operation in offline mode


---------------------------------------------------------------------------------
    Address  : 0x400803e8
    Name     : SEC_INFO_0
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [   31]    HEADER_EXTENSION_ENABLE       R/W  default = 0

   [30:20]    MAC_HEADER_LENGTH             R/W  default = 0

   [17: 4]    MPDU_LENGTH                   R/W  default = 0
               -MPDU length for offline mode

   [ 3: 1]    CIPHER_TYPE                   R/W  default = 0
               -Cipher type for offline mode
                 0 : WEP-40
                 1 : WEP-128
                 2 : TKIP
                 3 : CCMP

   [    0]    ENCRYPTION                    R/W  default = 0
               -Encryption or Decryption for offline mode


---------------------------------------------------------------------------------
    Address  : 0x400803ec
    Name     : SEC_INFO_1
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    SEC_INFO_1                    R/W  default = 0
               -Key value 0 - LSB 32bit of 128bit KEY for offline mode


---------------------------------------------------------------------------------
    Address  : 0x400803f0
    Name     : SEC_INFO_2
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    SEC_INFO_2                    R/W  default = 0
               -Key value 1 - Next LSB 32bit of 128bit KEY for offline mode


---------------------------------------------------------------------------------
    Address  : 0x400803f4
    Name     : SEC_INFO_3
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    SEC_INFO_3                    R/W  default = 0
               -Key value 2 - Next MSB 32bit of 128bit KEY for offline mode


---------------------------------------------------------------------------------
    Address  : 0x400803f8
    Name     : SEC_INFO_4
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    SEC_INFO_4                    R/W  default = 0
               -Key value 3 - MSB 32bit of 128bit KEY for offline mode


---------------------------------------------------------------------------------
    Address  : 0x400803fc
    Name     : SEC_OFFSET
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [30:26]    READ_OFFSET_ENCRYPT_3         R/W  default = 0

   [25:21]    READ_OFFSET_ENCRYPT_2         R/W  default = 0

   [20:16]    READ_OFFSET_DECRYPT           R/W  default = 0
               -Offset of read word in decryption

   [12: 8]    READ_OFFSET_ENCRYPT_1         R/W  default = 0
               -Offset of read word in encryption 1

   [ 4: 0]    READ_OFFSET_ENCRYPT_0         R/W  default = 0
               -Offset of read word in encryption 0


---------------------------------------------------------------------------------
    Address  : 0x40080400
    Name     : SEC_DATA_IN_WAIT_CNT
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    SEC_DATA_IN_WAIT_CNT          R/W  default = 0


---------------------------------------------------------------------------------
    Address  : 0x40080404
    Name     : SEC_KEY_FLAG_IDX
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    SEC_KEY_FLAG_IDX              R/W  default = 0


---------------------------------------------------------------------------------
    Address  : 0x40080408
    Name     : TX_INDIR_REG_ADDR
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    TX_INDIR_REG_ADDR             R/W  default = 0
               -Tx indirect address - Index of Tx indirect registers for debugging


---------------------------------------------------------------------------------
    Address  : 0x4008040c
    Name     : RX_INDIR_REG_ADDR
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    RX_INDIR_REG_ADDR             R/W  default = 0
               -Rx indirect address - Index of Rx indirect registers for debugging


---------------------------------------------------------------------------------
    Address  : 0x40080410
    Name     : SEC_INDIR_REG_ADDR
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    SEC_INDIR_REG_ADDR            R/W  default = 0
               -SEC indirect address - Index of security indirect registers for debugging


---------------------------------------------------------------------------------
    Address  : 0x40080414
    Name     : DMA_INDIR_REG_ADDR
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    DMA_INDIR_REG_ADDR            R/W  default = 0
               -DMA indirect address - Index of DMA indirect registers for debugging


---------------------------------------------------------------------------------
    Address  : 0x40080418
    Name     : IRQ_INDIR_REG_ADDR
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    IRQ_INDIR_REG_ADDR            R/W  default = 0
               -IRQ indirect address - Index of IRQ indirect registers for debugging


---------------------------------------------------------------------------------
    Address  : 0x4008041c
    Name     : MEM_INDIR_REG_ADDR
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    MEM_INDIR_REG_ADDR            R/W  default = 0


---------------------------------------------------------------------------------
    Address  : 0x40080420
    Name     : TSF_0_LOWER
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   + write_enable
---------------------------------------------------------------------------------
   [31: 0]    TSF_0_LOWER                   R/W  default = 0
               -Setting lower 32bit of TSF 0
               -Internal TSF0 which has 64bit width will only update it value if TSF_UPPER and TSF_LOWER are sequentially written both


---------------------------------------------------------------------------------
    Address  : 0x40080424
    Name     : TSF_0_UPPER
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   + write_enable
---------------------------------------------------------------------------------
   [31: 0]    TSF_0_UPPER                   R/W  default = 0
               -Setting upper 32bit of TSF 0
               -Internal TSF0 which has 64bit width will only update it value if TSF_UPPER and TSF_LOWER are sequentially written both


---------------------------------------------------------------------------------
    Address  : 0x40080428
    Name     : TSF_0_ALARM_LOWER
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   + write_enable
---------------------------------------------------------------------------------
   [31: 0]    TSF_0_ALARM_LOWER             R/W  default = 0
               -When value of TSF0 reaches the value designated in TSF_0_ALARM_LOWER register, the system will raise TSF Alarm interrupt


---------------------------------------------------------------------------------
    Address  : 0x4008042c
    Name     : BCN_INTERVAL_0
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   + write_enable
---------------------------------------------------------------------------------
   [31: 0]    BCN_INTERVAL_0                R/W  default = 0
               -Time interval between consecutive target beacon transmission times (TBTTs) of TSF0. The unit is TU equal to 1024 microseconds


---------------------------------------------------------------------------------
    Address  : 0x40080430
    Name     : TBTT_INTERRUPT_MARGIN_0
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   + write_enable
---------------------------------------------------------------------------------
   [31: 0]    TBTT_INTERRUPT_MARGIN_0       R/W  default = 0
               -Time margin between TBTT interrupt and actual TBTT of TSF0
               -TBTT interrupt occurs in advance before the actual TBTT timing
               -The value is represented in the unit of microsecond


---------------------------------------------------------------------------------
    Address  : 0x40080434
    Name     : TBTT_RESTART_RANGE_0
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   + write_enable
---------------------------------------------------------------------------------
   [31: 0]    TBTT_RESTART_RANGE_0          R/W  default = 0
               -Time threshold to recalculate next TBTT of TSF0
               -When MAC timer is updated to new value with larger difference than the threshold, next TBTT may be recalculated


---------------------------------------------------------------------------------
    Address  : 0x40080438
    Name     : TSF_1_LOWER
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   + write_enable
---------------------------------------------------------------------------------
   [31: 0]    TSF_1_LOWER                   R/W  default = 0
               -Setting lower 32bit of TSF 1
               -Internal TSF0 which has 64bit width will only update it value if TSF_UPPER and TSF_LOWER are sequentially written both


---------------------------------------------------------------------------------
    Address  : 0x4008043c
    Name     : TSF_1_UPPER
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   + write_enable
---------------------------------------------------------------------------------
   [31: 0]    TSF_1_UPPER                   R/W  default = 0
               -Setting upper 32bit of TSF 1
               -Internal TSF1 which has 64bit width will only update it value if TSF_UPPER and TSF_LOWER are sequentially written both


---------------------------------------------------------------------------------
    Address  : 0x40080440
    Name     : TSF_1_ALARM_LOWER
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   + write_enable
---------------------------------------------------------------------------------
   [31: 0]    TSF_1_ALARM_LOWER             R/W  default = 0
               -When value of TSF0 reaches the value designated in TSF_1_ALARM_LOWER register, the system will raise TSF Alarm interrupt


---------------------------------------------------------------------------------
    Address  : 0x40080444
    Name     : BCN_INTERVAL_1
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   + write_enable
---------------------------------------------------------------------------------
   [31: 0]    BCN_INTERVAL_1                R/W  default = 0
               -Time interval between consecutive target beacon transmission times (TBTTs) of TSF1. The unit is TU equal to 1024 microseconds


---------------------------------------------------------------------------------
    Address  : 0x40080448
    Name     : TBTT_INTERRUPT_MARGIN_1
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   + write_enable
---------------------------------------------------------------------------------
   [31: 0]    TBTT_INTERRUPT_MARGIN_1       R/W  default = 0
               -Time margin between TBTT interrupt and actual TBTT of TSF1
               -TBTT interrupt occurs in advance before the actual TBTT timing
               -The value is represented in the unit of microsecond


---------------------------------------------------------------------------------
    Address  : 0x4008044c
    Name     : TBTT_RESTART_RANGE_1
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   + write_enable
---------------------------------------------------------------------------------
   [31: 0]    TBTT_RESTART_RANGE_1          R/W  default = 0
               -Time threshold to recalculate next TBTT of TSF1
               -When MAC timer is updated to new value with larger difference than the threshold, next TBTT may be recalculated


---------------------------------------------------------------------------------
    Address  : 0x40080450
    Name     : IRQ_MASK0
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    IRQ_MASK0                     R/W  default = 4294967295
               -Bit value 0 of IRQ0_MASK will disable interrupt for corresponding IRQ source


---------------------------------------------------------------------------------
    Address  : 0x40080454
    Name     : IRQ_MASK1
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [31: 0]    IRQ_MASK1                     R/W  default = 4294967295
               -Bit value 0 of IRQ1_MASK will disable interrupt for corresponding IRQ source


---------------------------------------------------------------------------------
    Address  : 0x40080458
    Name     : IRQ_SET_CLEAR0
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   + write_enable
---------------------------------------------------------------------------------
   [31: 0]    IRQ_SET_CLEAR0                R/W  default = 0
               -Clear lower Interrupt Source


---------------------------------------------------------------------------------
    Address  : 0x4008045c
    Name     : IRQ_SET_CLEAR1
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   + write_enable
---------------------------------------------------------------------------------
   [31: 0]    IRQ_SET_CLEAR1                R/W  default = 0
               -Clear upper Interrupt Source


---------------------------------------------------------------------------------
    Address  : 0x40080460
    Name     : CLOCK_GATING_CONFIG
    Bit      : 32
    R/W      : R/W
---------------------------------------------------------------------------------
   [   31]    GLOBAL_CG_EN                  R/W  default = 0
                 0 : Each clock configuration
                 1 : All clock ON

   [ 7: 6]    LUT_CG_MODE                   R/W  default = 2
                 0 : Always OFF
                 1 : Always ON
                 2 : Auto

   [ 5: 4]    CCMP_CG_MODE                  R/W  default = 2
                 0 : Always OFF
                 1 : Always ON
                 2 : Auto

   [ 3: 2]    BUS_CG_MODE                   R/W  default = 2
                 0 : Always OFF
                 1 : Always ON
                 2 : Auto

   [ 1: 0]    MAC_CG_MODE                   R/W  default = 2
                 0 : Always OFF
                 1 : Always ON
                 2 : Auto


---------------------------------------------------------------------------------
    Address  : 0x40080464
    Name     : TX_RESULT_0
    Bit      : 32
    R/W      : R
---------------------------------------------------------------------------------
   [   31]    FEEDBACK_VALID                R    default = 0
               -Feedback SNR of transmitted frame

   [30:24]    FEEDBACK_SNR                  R    default = 0
               -Feedback SNR of transmitted frame

   [23:16]    RECEIVED_SNR                  R    default = 0
               -SNR of received response

   [   15]    VALID_RESULT                  R    default = 0
               -0: Not valid
               -1: Valid

   [14:12]    SEQUENCE                      R    default = 0
               -Sequence of result under TXOP

   [   11]    MORE_DATA                     R    default = 0
               -Peer STA has data to send

   [   10]    LACK_TXTIME                   R    default = 0
               -Lack of Tx time in TXOP

   [    9]    INSIDE_RAW                    R    default = 0
               -Tx is done inside RAW

   [    8]    SIFS_TIMEOUT                  R    default = 0
               -Time out when waiting SIFS invoking

   [    7]    BW_MATCH_FAIL                 R    default = 0
               -Bandwidth Match fail

   [    6]    ACK_POLICY                    R    default = 0
               -0: Normal ACK Transmit
               -1: NoACK Transmit

   [ 5: 3]    FAIL_REASON                   R    default = 0
               -Value of FAIL_REASON is only valid when ACK_SUCCESS was 0
                 0 : ACK Timeout(Doesn't receive ACK)
                 1 : CTS Timeout(Doesn't receive CTS)
                 2 : Received ACK but CRC fail or Address Match Fail
                 3 : Received CTS but CRC fail or Address Match Fail
                 4 : Received ACK after sending A-MPDU
                 5 : Received Block ACK after sending non A-MPDU
                 6 : Received non ACK while waiting for ACK
                 7 : Received non CTS while waiting for CTS

   [    2]    TXOP_END                      R    default = 0
                 0 : Next MPDU is scheduled to send within TXOP
                 1 : Current TX was the end of TXOP

   [    1]    FAILED_BITMAP_VALID           R    default = 0
                 0 : All transmitted A-MPDU has been acknowledged
                 1 : One or more MPDU in A-MPDU has been failed. Should see corresponding TX_FAILED_BITMAP register

   [    0]    ACK_SUCCESS                   R    default = 0
                 0 : Transmission sequence has been failed. Reason for fail can be seen in bit [5:3]
                 1 : Transmission sequence success. No-ACK and No-RTS transmit will always set to 1. In A-MPDU transmit, it will set to 1 if BA has been received regardless of contents of BA


---------------------------------------------------------------------------------
    Address  : 0x40080468
    Name     : TX_RESULT_1
    Bit      : 32
    R/W      : R
---------------------------------------------------------------------------------
   [31: 0]    TX_RESULT_1                   R    default = 0
               -Same as TX_RESULT_0


---------------------------------------------------------------------------------
    Address  : 0x4008046c
    Name     : TX_RESULT_2
    Bit      : 32
    R/W      : R
---------------------------------------------------------------------------------
   [31: 0]    TX_RESULT_2                   R    default = 0
               -Same as TX_RESULT_0


---------------------------------------------------------------------------------
    Address  : 0x40080470
    Name     : TX_RESULT_3
    Bit      : 32
    R/W      : R
---------------------------------------------------------------------------------
   [31: 0]    TX_RESULT_3                   R    default = 0
               -Same as TX_RESULT_0


---------------------------------------------------------------------------------
    Address  : 0x40080474
    Name     : TX_RESULT_4
    Bit      : 32
    R/W      : R
---------------------------------------------------------------------------------
   [31: 0]    TX_RESULT_4                   R    default = 0
               -Same as TX_RESULT_0


---------------------------------------------------------------------------------
    Address  : 0x40080478
    Name     : TX_RESULT_5
    Bit      : 32
    R/W      : R
---------------------------------------------------------------------------------
   [31: 0]    TX_RESULT_5                   R    default = 0
               -Same as TX_RESULT_0


---------------------------------------------------------------------------------
    Address  : 0x4008047c
    Name     : TX_RESULT_6
    Bit      : 32
    R/W      : R
---------------------------------------------------------------------------------
   [31: 0]    TX_RESULT_6                   R    default = 0
               -Same as TX_RESULT_0


---------------------------------------------------------------------------------
    Address  : 0x40080480
    Name     : TX_RESULT_7
    Bit      : 32
    R/W      : R
---------------------------------------------------------------------------------
   [31: 0]    TX_RESULT_7                   R    default = 0
               -Same as TX_RESULT_0


---------------------------------------------------------------------------------
    Address  : 0x40080484
    Name     : TX_RESULT_8
    Bit      : 32
    R/W      : R
---------------------------------------------------------------------------------
   [31: 0]    TX_RESULT_8                   R    default = 0
               -Same as TX_RESULT_0


---------------------------------------------------------------------------------
    Address  : 0x40080488
    Name     : TX_RESULT_9
    Bit      : 32
    R/W      : R
---------------------------------------------------------------------------------
   [31: 0]    TX_RESULT_9                   R    default = 0
               -Same as TX_RESULT_0


---------------------------------------------------------------------------------
    Address  : 0x4008048c
    Name     : TX_RESULT_10
    Bit      : 32
    R/W      : R
---------------------------------------------------------------------------------
   [31: 0]    TX_RESULT_10                  R    default = 0
               -Same as TX_RESULT_0


---------------------------------------------------------------------------------
    Address  : 0x40080490
    Name     : TX_RESULT_11
    Bit      : 32
    R/W      : R
---------------------------------------------------------------------------------
   [31: 0]    TX_RESULT_11                  R    default = 0
               -Same as TX_RESULT_0


---------------------------------------------------------------------------------
    Address  : 0x40080494
    Name     : TX_RESULT_12
    Bit      : 32
    R/W      : R
---------------------------------------------------------------------------------
   [31: 0]    TX_RESULT_12                  R    default = 0
               -Same as TX_RESULT_0


---------------------------------------------------------------------------------
    Address  : 0x40080498
    Name     : TX_RESULT_13
    Bit      : 32
    R/W      : R
---------------------------------------------------------------------------------
   [31: 0]    TX_RESULT_13                  R    default = 0
               -Same as TX_RESULT_0


---------------------------------------------------------------------------------
    Address  : 0x4008049c
    Name     : TX_RESULT_14
    Bit      : 32
    R/W      : R
---------------------------------------------------------------------------------
   [31: 0]    TX_RESULT_14                  R    default = 0
               -Same as TX_RESULT_0


---------------------------------------------------------------------------------
    Address  : 0x400804a0
    Name     : TX_RESULT_15
    Bit      : 32
    R/W      : R
---------------------------------------------------------------------------------
   [31: 0]    TX_RESULT_15                  R    default = 0
               -Same as TX_RESULT_0


---------------------------------------------------------------------------------
    Address  : 0x400804a4
    Name     : TX_RESULT_16
    Bit      : 32
    R/W      : R
---------------------------------------------------------------------------------
   [31: 0]    TX_RESULT_16                  R    default = 0
               -Same as TX_RESULT_0


---------------------------------------------------------------------------------
    Address  : 0x400804a8
    Name     : TX_RESULT_17
    Bit      : 32
    R/W      : R
---------------------------------------------------------------------------------
   [31: 0]    TX_RESULT_17                  R    default = 0
               -Same as TX_RESULT_0


---------------------------------------------------------------------------------
    Address  : 0x400804ac
    Name     : TX_RESULT_18
    Bit      : 32
    R/W      : R
---------------------------------------------------------------------------------
   [31: 0]    TX_RESULT_18                  R    default = 0
               -Same as TX_RESULT_0


---------------------------------------------------------------------------------
    Address  : 0x400804b0
    Name     : TX_RESULT_19
    Bit      : 32
    R/W      : R
---------------------------------------------------------------------------------
   [31: 0]    TX_RESULT_19                  R    default = 0
               -Same as TX_RESULT_0


---------------------------------------------------------------------------------
    Address  : 0x400804b4
    Name     : TX_RESULT_20
    Bit      : 32
    R/W      : R
---------------------------------------------------------------------------------
   [31: 0]    TX_RESULT_20                  R    default = 0
               -Same as TX_RESULT_0


---------------------------------------------------------------------------------
    Address  : 0x400804b8
    Name     : TX_RESULT_21
    Bit      : 32
    R/W      : R
---------------------------------------------------------------------------------
   [31: 0]    TX_RESULT_21                  R    default = 0
               -Same as TX_RESULT_0


---------------------------------------------------------------------------------
    Address  : 0x400804bc
    Name     : TX_FAILED_BITMAP_LOWER_0
    Bit      : 32
    R/W      : R
---------------------------------------------------------------------------------
   [31: 0]    TX_FAILED_BITMAP_LOWER_0      R    default = 0
               -Lower 32 bit of 64 bit failed bitmap. Bit 0 correspond to TX SSN


---------------------------------------------------------------------------------
    Address  : 0x400804c0
    Name     : TX_FAILED_BITMAP_UPPER_0
    Bit      : 32
    R/W      : R
---------------------------------------------------------------------------------
   [31: 0]    TX_FAILED_BITMAP_UPPER_0      R    default = 0
               -Upper 32 bit of 64 bit failed bitmap


---------------------------------------------------------------------------------
    Address  : 0x400804c4
    Name     : TX_FAILED_BITMAP_LOWER_1
    Bit      : 32
    R/W      : R
---------------------------------------------------------------------------------
   [31: 0]    TX_FAILED_BITMAP_LOWER_1      R    default = 0
               -Lower 32 bit of 64 bit failed bitmap. Bit 0 correspond to TX SSN


---------------------------------------------------------------------------------
    Address  : 0x400804c8
    Name     : TX_FAILED_BITMAP_UPPER_1
    Bit      : 32
    R/W      : R
---------------------------------------------------------------------------------
   [31: 0]    TX_FAILED_BITMAP_UPPER_1      R    default = 0
               -Upper 32 bit of 64 bit failed bitmap


---------------------------------------------------------------------------------
    Address  : 0x400804cc
    Name     : TX_FAILED_BITMAP_LOWER_2
    Bit      : 32
    R/W      : R
---------------------------------------------------------------------------------
   [31: 0]    TX_FAILED_BITMAP_LOWER_2      R    default = 0
               -Lower 32 bit of 64 bit failed bitmap. Bit 0 correspond to TX SSN


---------------------------------------------------------------------------------
    Address  : 0x400804d0
    Name     : TX_FAILED_BITMAP_UPPER_2
    Bit      : 32
    R/W      : R
---------------------------------------------------------------------------------
   [31: 0]    TX_FAILED_BITMAP_UPPER_2      R    default = 0
               -Upper 32 bit of 64 bit failed bitmap


---------------------------------------------------------------------------------
    Address  : 0x400804d4
    Name     : TX_FAILED_BITMAP_LOWER_3
    Bit      : 32
    R/W      : R
---------------------------------------------------------------------------------
   [31: 0]    TX_FAILED_BITMAP_LOWER_3      R    default = 0
               -Lower 32 bit of 64 bit failed bitmap. Bit 0 correspond to TX SSN


---------------------------------------------------------------------------------
    Address  : 0x400804d8
    Name     : TX_FAILED_BITMAP_UPPER_3
    Bit      : 32
    R/W      : R
---------------------------------------------------------------------------------
   [31: 0]    TX_FAILED_BITMAP_UPPER_3      R    default = 0
               -Upper 32 bit of 64 bit failed bitmap


---------------------------------------------------------------------------------
    Address  : 0x400804dc
    Name     : TX_FAILED_BITMAP_LOWER_4
    Bit      : 32
    R/W      : R
---------------------------------------------------------------------------------
   [31: 0]    TX_FAILED_BITMAP_LOWER_4      R    default = 0
               -Lower 32 bit of 64 bit failed bitmap. Bit 0 correspond to TX SSN


---------------------------------------------------------------------------------
    Address  : 0x400804e0
    Name     : TX_FAILED_BITMAP_UPPER_4
    Bit      : 32
    R/W      : R
---------------------------------------------------------------------------------
   [31: 0]    TX_FAILED_BITMAP_UPPER_4      R    default = 0
               -Upper 32 bit of 64 bit failed bitmap


---------------------------------------------------------------------------------
    Address  : 0x400804e4
    Name     : TX_FAILED_BITMAP_LOWER_5
    Bit      : 32
    R/W      : R
---------------------------------------------------------------------------------
   [31: 0]    TX_FAILED_BITMAP_LOWER_5      R    default = 0
               -Lower 32 bit of 64 bit failed bitmap. Bit 0 correspond to TX SSN


---------------------------------------------------------------------------------
    Address  : 0x400804e8
    Name     : TX_FAILED_BITMAP_UPPER_5
    Bit      : 32
    R/W      : R
---------------------------------------------------------------------------------
   [31: 0]    TX_FAILED_BITMAP_UPPER_5      R    default = 0
               -Upper 32 bit of 64 bit failed bitmap


---------------------------------------------------------------------------------
    Address  : 0x400804ec
    Name     : TX_FAILED_BITMAP_LOWER_6
    Bit      : 32
    R/W      : R
---------------------------------------------------------------------------------
   [31: 0]    TX_FAILED_BITMAP_LOWER_6      R    default = 0
               -Lower 32 bit of 64 bit failed bitmap. Bit 0 correspond to TX SSN


---------------------------------------------------------------------------------
    Address  : 0x400804f0
    Name     : TX_FAILED_BITMAP_UPPER_6
    Bit      : 32
    R/W      : R
---------------------------------------------------------------------------------
   [31: 0]    TX_FAILED_BITMAP_UPPER_6      R    default = 0
               -Upper 32 bit of 64 bit failed bitmap


---------------------------------------------------------------------------------
    Address  : 0x400804f4
    Name     : TX_FAILED_BITMAP_LOWER_7
    Bit      : 32
    R/W      : R
---------------------------------------------------------------------------------
   [31: 0]    TX_FAILED_BITMAP_LOWER_7      R    default = 0
               -Lower 32 bit of 64 bit failed bitmap. Bit 0 correspond to TX SSN


---------------------------------------------------------------------------------
    Address  : 0x400804f8
    Name     : TX_FAILED_BITMAP_UPPER_7
    Bit      : 32
    R/W      : R
---------------------------------------------------------------------------------
   [31: 0]    TX_FAILED_BITMAP_UPPER_7      R    default = 0
               -Upper 32 bit of 64 bit failed bitmap


---------------------------------------------------------------------------------
    Address  : 0x400804fc
    Name     : TX_FAILED_BITMAP_LOWER_8
    Bit      : 32
    R/W      : R
---------------------------------------------------------------------------------
   [31: 0]    TX_FAILED_BITMAP_LOWER_8      R    default = 0
               -Lower 32 bit of 64 bit failed bitmap. Bit 0 correspond to TX SSN


---------------------------------------------------------------------------------
    Address  : 0x40080500
    Name     : TX_FAILED_BITMAP_UPPER_8
    Bit      : 32
    R/W      : R
---------------------------------------------------------------------------------
   [31: 0]    TX_FAILED_BITMAP_UPPER_8      R    default = 0
               -Upper 32 bit of 64 bit failed bitmap


---------------------------------------------------------------------------------
    Address  : 0x40080504
    Name     : TX_FAILED_BITMAP_LOWER_9
    Bit      : 32
    R/W      : R
---------------------------------------------------------------------------------
   [31: 0]    TX_FAILED_BITMAP_LOWER_9      R    default = 0
               -Lower 32 bit of 64 bit failed bitmap. Bit 0 correspond to TX SSN


---------------------------------------------------------------------------------
    Address  : 0x40080508
    Name     : TX_FAILED_BITMAP_UPPER_9
    Bit      : 32
    R/W      : R
---------------------------------------------------------------------------------
   [31: 0]    TX_FAILED_BITMAP_UPPER_9      R    default = 0
               -Upper 32 bit of 64 bit failed bitmap


---------------------------------------------------------------------------------
    Address  : 0x4008050c
    Name     : TX_FAILED_BITMAP_LOWER_10
    Bit      : 32
    R/W      : R
---------------------------------------------------------------------------------
   [31: 0]    TX_FAILED_BITMAP_LOWER_10     R    default = 0
               -Lower 32 bit of 64 bit failed bitmap. Bit 0 correspond to TX SSN


---------------------------------------------------------------------------------
    Address  : 0x40080510
    Name     : TX_FAILED_BITMAP_UPPER_10
    Bit      : 32
    R/W      : R
---------------------------------------------------------------------------------
   [31: 0]    TX_FAILED_BITMAP_UPPER_10     R    default = 0
               -Upper 32 bit of 64 bit failed bitmap


---------------------------------------------------------------------------------
    Address  : 0x40080514
    Name     : RESPONSE_TX_RESULT
    Bit      : 16
    R/W      : R
---------------------------------------------------------------------------------
   [15: 0]    RESPONSE_TX_RESULT            R    default = 0


---------------------------------------------------------------------------------
    Address  : 0x40080518
    Name     : RX_WRITE_EN_DL_DESC0
    Bit      : 3
    R/W      : R
---------------------------------------------------------------------------------
   [    2]    OWNERSHIP                     R    default = 0
               -Indicate that this register is valid. S/W should write this field to 1 after reading valid Data Address Offset, and H/W write this field to 0 after DMA write to the address indicated in Data Address Offset field has been done

   [ 1: 0]    FRAGMENT                      R    default = 0
               -Fragment Position of MPDU
                 0 : Single MPDU
                 1 : Last Fragment
                 2 : First Fragment
                 3 : Middle Fragment


---------------------------------------------------------------------------------
    Address  : 0x4008051c
    Name     : RX_WRITE_EN_DL_DESC1
    Bit      : 3
    R/W      : R
---------------------------------------------------------------------------------
   [ 2: 0]    RX_WRITE_EN_DL_DESC1          R    default = 0
               -Same as RX_WRITE_EN_DL_DESC0


---------------------------------------------------------------------------------
    Address  : 0x40080520
    Name     : RX_WRITE_EN_DL_DESC2
    Bit      : 3
    R/W      : R
---------------------------------------------------------------------------------
   [ 2: 0]    RX_WRITE_EN_DL_DESC2          R    default = 0
               -Same as RX_WRITE_EN_DL_DESC0


---------------------------------------------------------------------------------
    Address  : 0x40080524
    Name     : RX_WRITE_EN_DL_DESC3
    Bit      : 3
    R/W      : R
---------------------------------------------------------------------------------
   [ 2: 0]    RX_WRITE_EN_DL_DESC3          R    default = 0
               -Same as RX_WRITE_EN_DL_DESC0


---------------------------------------------------------------------------------
    Address  : 0x40080528
    Name     : RX_WRITE_EN_DL_DESC4
    Bit      : 3
    R/W      : R
---------------------------------------------------------------------------------
   [ 2: 0]    RX_WRITE_EN_DL_DESC4          R    default = 0
               -Same as RX_WRITE_EN_DL_DESC0


---------------------------------------------------------------------------------
    Address  : 0x4008052c
    Name     : RX_WRITE_EN_DL_DESC5
    Bit      : 3
    R/W      : R
---------------------------------------------------------------------------------
   [ 2: 0]    RX_WRITE_EN_DL_DESC5          R    default = 0
               -Same as RX_WRITE_EN_DL_DESC0


---------------------------------------------------------------------------------
    Address  : 0x40080530
    Name     : RX_WRITE_EN_DL_DESC6
    Bit      : 3
    R/W      : R
---------------------------------------------------------------------------------
   [ 2: 0]    RX_WRITE_EN_DL_DESC6          R    default = 0
               -Same as RX_WRITE_EN_DL_DESC0


---------------------------------------------------------------------------------
    Address  : 0x40080534
    Name     : RX_WRITE_EN_DL_DESC7
    Bit      : 3
    R/W      : R
---------------------------------------------------------------------------------
   [ 2: 0]    RX_WRITE_EN_DL_DESC7          R    default = 0
               -Same as RX_WRITE_EN_DL_DESC0


---------------------------------------------------------------------------------
    Address  : 0x40080538
    Name     : RX_WRITE_EN_DL_DESC8
    Bit      : 3
    R/W      : R
---------------------------------------------------------------------------------
   [ 2: 0]    RX_WRITE_EN_DL_DESC8          R    default = 0
               -Same as RX_WRITE_EN_DL_DESC0


---------------------------------------------------------------------------------
    Address  : 0x4008053c
    Name     : RX_WRITE_EN_DL_DESC9
    Bit      : 3
    R/W      : R
---------------------------------------------------------------------------------
   [ 2: 0]    RX_WRITE_EN_DL_DESC9          R    default = 0
               -Same as RX_WRITE_EN_DL_DESC0


---------------------------------------------------------------------------------
    Address  : 0x40080540
    Name     : RX_WRITE_EN_DL_DESC10
    Bit      : 3
    R/W      : R
---------------------------------------------------------------------------------
   [ 2: 0]    RX_WRITE_EN_DL_DESC10         R    default = 0
               -Same as RX_WRITE_EN_DL_DESC0


---------------------------------------------------------------------------------
    Address  : 0x40080544
    Name     : RX_WRITE_EN_DL_DESC11
    Bit      : 3
    R/W      : R
---------------------------------------------------------------------------------
   [ 2: 0]    RX_WRITE_EN_DL_DESC11         R    default = 0
               -Same as RX_WRITE_EN_DL_DESC0


---------------------------------------------------------------------------------
    Address  : 0x40080548
    Name     : RX_WRITE_EN_DL_DESC12
    Bit      : 3
    R/W      : R
---------------------------------------------------------------------------------
   [ 2: 0]    RX_WRITE_EN_DL_DESC12         R    default = 0
               -Same as RX_WRITE_EN_DL_DESC0


---------------------------------------------------------------------------------
    Address  : 0x4008054c
    Name     : RX_WRITE_EN_DL_DESC13
    Bit      : 3
    R/W      : R
---------------------------------------------------------------------------------
   [ 2: 0]    RX_WRITE_EN_DL_DESC13         R    default = 0
               -Same as RX_WRITE_EN_DL_DESC0


---------------------------------------------------------------------------------
    Address  : 0x40080550
    Name     : RX_WRITE_EN_DL_DESC14
    Bit      : 3
    R/W      : R
---------------------------------------------------------------------------------
   [ 2: 0]    RX_WRITE_EN_DL_DESC14         R    default = 0
               -Same as RX_WRITE_EN_DL_DESC0


---------------------------------------------------------------------------------
    Address  : 0x40080554
    Name     : RX_WRITE_EN_DL_DESC15
    Bit      : 3
    R/W      : R
---------------------------------------------------------------------------------
   [ 2: 0]    RX_WRITE_EN_DL_DESC15         R    default = 0
               -Same as RX_WRITE_EN_DL_DESC0


---------------------------------------------------------------------------------
    Address  : 0x40080558
    Name     : RX_WRITE_EN_DL_DESC16
    Bit      : 3
    R/W      : R
---------------------------------------------------------------------------------
   [ 2: 0]    RX_WRITE_EN_DL_DESC16         R    default = 0
               -Same as RX_WRITE_EN_DL_DESC0


---------------------------------------------------------------------------------
    Address  : 0x4008055c
    Name     : RX_WRITE_EN_DL_DESC17
    Bit      : 3
    R/W      : R
---------------------------------------------------------------------------------
   [ 2: 0]    RX_WRITE_EN_DL_DESC17         R    default = 0
               -Same as RX_WRITE_EN_DL_DESC0


---------------------------------------------------------------------------------
    Address  : 0x40080560
    Name     : RX_WRITE_EN_DL_DESC18
    Bit      : 3
    R/W      : R
---------------------------------------------------------------------------------
   [ 2: 0]    RX_WRITE_EN_DL_DESC18         R    default = 0
               -Same as RX_WRITE_EN_DL_DESC0


---------------------------------------------------------------------------------
    Address  : 0x40080564
    Name     : RX_WRITE_EN_DL_DESC19
    Bit      : 3
    R/W      : R
---------------------------------------------------------------------------------
   [ 2: 0]    RX_WRITE_EN_DL_DESC19         R    default = 0
               -Same as RX_WRITE_EN_DL_DESC0


---------------------------------------------------------------------------------
    Address  : 0x40080568
    Name     : RX_WRITE_EN_DL_DESC20
    Bit      : 3
    R/W      : R
---------------------------------------------------------------------------------
   [ 2: 0]    RX_WRITE_EN_DL_DESC20         R    default = 0
               -Same as RX_WRITE_EN_DL_DESC0


---------------------------------------------------------------------------------
    Address  : 0x4008056c
    Name     : RX_WRITE_EN_DL_DESC21
    Bit      : 3
    R/W      : R
---------------------------------------------------------------------------------
   [ 2: 0]    RX_WRITE_EN_DL_DESC21         R    default = 0
               -Same as RX_WRITE_EN_DL_DESC0


---------------------------------------------------------------------------------
    Address  : 0x40080570
    Name     : RX_WRITE_EN_DL_DESC22
    Bit      : 3
    R/W      : R
---------------------------------------------------------------------------------
   [ 2: 0]    RX_WRITE_EN_DL_DESC22         R    default = 0
               -Same as RX_WRITE_EN_DL_DESC0


---------------------------------------------------------------------------------
    Address  : 0x40080574
    Name     : RX_WRITE_EN_DL_DESC23
    Bit      : 3
    R/W      : R
---------------------------------------------------------------------------------
   [ 2: 0]    RX_WRITE_EN_DL_DESC23         R    default = 0
               -Same as RX_WRITE_EN_DL_DESC0


---------------------------------------------------------------------------------
    Address  : 0x40080578
    Name     : RX_WRITE_EN_DL_DESC24
    Bit      : 3
    R/W      : R
---------------------------------------------------------------------------------
   [ 2: 0]    RX_WRITE_EN_DL_DESC24         R    default = 0
               -Same as RX_WRITE_EN_DL_DESC0


---------------------------------------------------------------------------------
    Address  : 0x4008057c
    Name     : RX_WRITE_EN_DL_DESC25
    Bit      : 3
    R/W      : R
---------------------------------------------------------------------------------
   [ 2: 0]    RX_WRITE_EN_DL_DESC25         R    default = 0
               -Same as RX_WRITE_EN_DL_DESC0


---------------------------------------------------------------------------------
    Address  : 0x40080580
    Name     : RX_WRITE_EN_DL_DESC26
    Bit      : 3
    R/W      : R
---------------------------------------------------------------------------------
   [ 2: 0]    RX_WRITE_EN_DL_DESC26         R    default = 0
               -Same as RX_WRITE_EN_DL_DESC0


---------------------------------------------------------------------------------
    Address  : 0x40080584
    Name     : RX_WRITE_EN_DL_DESC27
    Bit      : 3
    R/W      : R
---------------------------------------------------------------------------------
   [ 2: 0]    RX_WRITE_EN_DL_DESC27         R    default = 0
               -Same as RX_WRITE_EN_DL_DESC0


---------------------------------------------------------------------------------
    Address  : 0x40080588
    Name     : RX_WRITE_EN_DL_DESC28
    Bit      : 3
    R/W      : R
---------------------------------------------------------------------------------
   [ 2: 0]    RX_WRITE_EN_DL_DESC28         R    default = 0
               -Same as RX_WRITE_EN_DL_DESC0


---------------------------------------------------------------------------------
    Address  : 0x4008058c
    Name     : RX_WRITE_EN_DL_DESC29
    Bit      : 3
    R/W      : R
---------------------------------------------------------------------------------
   [ 2: 0]    RX_WRITE_EN_DL_DESC29         R    default = 0
               -Same as RX_WRITE_EN_DL_DESC0


---------------------------------------------------------------------------------
    Address  : 0x40080590
    Name     : RX_WRITE_EN_DL_DESC30
    Bit      : 3
    R/W      : R
---------------------------------------------------------------------------------
   [ 2: 0]    RX_WRITE_EN_DL_DESC30         R    default = 0
               -Same as RX_WRITE_EN_DL_DESC0


---------------------------------------------------------------------------------
    Address  : 0x40080594
    Name     : RX_WRITE_EN_DL_DESC31
    Bit      : 3
    R/W      : R
---------------------------------------------------------------------------------
   [ 2: 0]    RX_WRITE_EN_DL_DESC31         R    default = 0
               -Same as RX_WRITE_EN_DL_DESC0


---------------------------------------------------------------------------------
    Address  : 0x40080598
    Name     : RXSIG0
    Bit      : 32
    R/W      : R
---------------------------------------------------------------------------------
   [31: 0]    RXSIG0                        R    default = 0


---------------------------------------------------------------------------------
    Address  : 0x4008059c
    Name     : RXSIG1
    Bit      : 32
    R/W      : R
---------------------------------------------------------------------------------
   [31: 0]    RXSIG1                        R    default = 0


---------------------------------------------------------------------------------
    Address  : 0x400805a0
    Name     : RXVECTOR0
    Bit      : 32
    R/W      : R
---------------------------------------------------------------------------------
   [31: 0]    RXVECTOR0                     R    default = 0


---------------------------------------------------------------------------------
    Address  : 0x400805a4
    Name     : RXVECTOR1
    Bit      : 32
    R/W      : R
---------------------------------------------------------------------------------
   [31: 0]    RXVECTOR1                     R    default = 0


---------------------------------------------------------------------------------
    Address  : 0x400805a8
    Name     : RXVECTOR2
    Bit      : 32
    R/W      : R
---------------------------------------------------------------------------------
   [31: 0]    RXVECTOR2                     R    default = 0


---------------------------------------------------------------------------------
    Address  : 0x400805ac
    Name     : RXINFO0
    Bit      : 32
    R/W      : R
---------------------------------------------------------------------------------
   [31: 0]    RXINFO0                       R    default = 0


---------------------------------------------------------------------------------
    Address  : 0x400805b0
    Name     : RXINFO1
    Bit      : 32
    R/W      : R
---------------------------------------------------------------------------------
   [31: 0]    RXINFO1                       R    default = 0


---------------------------------------------------------------------------------
    Address  : 0x400805b4
    Name     : RXINFO2
    Bit      : 32
    R/W      : R
---------------------------------------------------------------------------------
   [31: 0]    RXINFO2                       R    default = 0


---------------------------------------------------------------------------------
    Address  : 0x400805b8
    Name     : RXINFO3
    Bit      : 32
    R/W      : R
---------------------------------------------------------------------------------
   [31: 0]    RXINFO3                       R    default = 0


---------------------------------------------------------------------------------
    Address  : 0x400805bc
    Name     : RXHEADER0
    Bit      : 32
    R/W      : R
---------------------------------------------------------------------------------
   [31: 0]    RXHEADER0                     R    default = 0


---------------------------------------------------------------------------------
    Address  : 0x400805c0
    Name     : RXHEADER1
    Bit      : 32
    R/W      : R
---------------------------------------------------------------------------------
   [31: 0]    RXHEADER1                     R    default = 0


---------------------------------------------------------------------------------
    Address  : 0x400805c4
    Name     : RXHEADER2
    Bit      : 32
    R/W      : R
---------------------------------------------------------------------------------
   [31: 0]    RXHEADER2                     R    default = 0


---------------------------------------------------------------------------------
    Address  : 0x400805c8
    Name     : RXHEADER3
    Bit      : 32
    R/W      : R
---------------------------------------------------------------------------------
   [31: 0]    RXHEADER3                     R    default = 0


---------------------------------------------------------------------------------
    Address  : 0x400805cc
    Name     : RXHEADER4
    Bit      : 32
    R/W      : R
---------------------------------------------------------------------------------
   [31: 0]    RXHEADER4                     R    default = 0


---------------------------------------------------------------------------------
    Address  : 0x400805d0
    Name     : RXHEADER5
    Bit      : 32
    R/W      : R
---------------------------------------------------------------------------------
   [31: 0]    RXHEADER5                     R    default = 0


---------------------------------------------------------------------------------
    Address  : 0x400805d4
    Name     : RXHEADER6
    Bit      : 32
    R/W      : R
---------------------------------------------------------------------------------
   [31: 0]    RXHEADER6                     R    default = 0


---------------------------------------------------------------------------------
    Address  : 0x400805d8
    Name     : RXHEADER7
    Bit      : 32
    R/W      : R
---------------------------------------------------------------------------------
   [31: 0]    RXHEADER7                     R    default = 0


---------------------------------------------------------------------------------
    Address  : 0x400805dc
    Name     : RXHEADER8
    Bit      : 32
    R/W      : R
---------------------------------------------------------------------------------
   [31: 0]    RXHEADER8                     R    default = 0


---------------------------------------------------------------------------------
    Address  : 0x400805e0
    Name     : AMPDU_BITMAP
    Bit      : 32
    R/W      : R
---------------------------------------------------------------------------------
   [31: 0]    AMPDU_BITMAP                  R    default = 0


---------------------------------------------------------------------------------
    Address  : 0x400805e4
    Name     : KEY_CMD_RESULT_EN
    Bit      : 1
    R/W      : R
---------------------------------------------------------------------------------
   [    0]    KEY_CMD_RESULT_EN             R    default = 0
               -Command result enable


---------------------------------------------------------------------------------
    Address  : 0x400805e8
    Name     : KEY_CMD_RESULT
    Bit      : 32
    R/W      : R
---------------------------------------------------------------------------------
   [31:28]    COMMAND                       R    default = 0
               -Command of operation
                 0 : Add key
                 1 : Delete key
                 2 : Delete all key

   [27:20]    RESULT                        R    default = 0
               -Result of operation
                 1 : Unsupported command type
                 2 : Add KEY fail because entries are full
                 3 : Add KEY success
                 4 : Delete KEY success
                 5 : Delete KEY fail because address matching is fail

   [ 2: 0]    ADDRESS                       R    default = 0
               -Address of memory


---------------------------------------------------------------------------------
    Address  : 0x400805ec
    Name     : SEC_REG_MIC_CHECK_FAIL
    Bit      : 1
    R/W      : R
---------------------------------------------------------------------------------
   [    0]    MIC_FAIL                      R    default = 0
               -Result of MIC check


---------------------------------------------------------------------------------
    Address  : 0x400805f0
    Name     : SEC_KEY_FLAG
    Bit      : 32
    R/W      : R
---------------------------------------------------------------------------------
   [31: 0]    SEC_KEY_FLAG                  R    default = 0


---------------------------------------------------------------------------------
    Address  : 0x400805f4
    Name     : SEC_MIC_VALUE_RX_FAILED_0
    Bit      : 32
    R/W      : R
---------------------------------------------------------------------------------
   [31: 0]    SEC_MIC_VALUE_RX_FAILED_0     R    default = 0


---------------------------------------------------------------------------------
    Address  : 0x400805f8
    Name     : SEC_MIC_VALUE_RX_FAILED_1
    Bit      : 32
    R/W      : R
---------------------------------------------------------------------------------
   [31: 0]    SEC_MIC_VALUE_RX_FAILED_1     R    default = 0


---------------------------------------------------------------------------------
    Address  : 0x400805fc
    Name     : TX_INDIR_REG_DATA
    Bit      : 32
    R/W      : R
---------------------------------------------------------------------------------
   [31: 0]    TX_INDIR_REG_DATA             R    default = 0
               -Indirect register data in TX Category


---------------------------------------------------------------------------------
    Address  : 0x40080600
    Name     : RX_INDIR_REG_DATA
    Bit      : 32
    R/W      : R
---------------------------------------------------------------------------------
   [31: 0]    RX_INDIR_REG_DATA             R    default = 0
               -Indirect register data in RX Category


---------------------------------------------------------------------------------
    Address  : 0x40080604
    Name     : SEC_INDIR_REG_DATA
    Bit      : 32
    R/W      : R
---------------------------------------------------------------------------------
   [31: 0]    SEC_INDIR_REG_DATA            R    default = 0
               -Indirect register data in Security Category


---------------------------------------------------------------------------------
    Address  : 0x40080608
    Name     : DMA_INDIR_REG_DATA
    Bit      : 32
    R/W      : R
---------------------------------------------------------------------------------
   [31: 0]    DMA_INDIR_REG_DATA            R    default = 0
               -Indirect register data in DMA Category


---------------------------------------------------------------------------------
    Address  : 0x4008060c
    Name     : IRQ_INDIR_REG_DATA
    Bit      : 32
    R/W      : R
---------------------------------------------------------------------------------
   [31: 0]    IRQ_INDIR_REG_DATA            R    default = 0
               -Indirect register data in Interrupt Category


---------------------------------------------------------------------------------
    Address  : 0x40080610
    Name     : TSF_0_LOWER_READONLY
    Bit      : 32
    R/W      : R
---------------------------------------------------------------------------------
   [31: 0]    TSF_0_LOWER_READONLY          R    default = 0
               -Lower 32bit of 64bit TSF0


---------------------------------------------------------------------------------
    Address  : 0x40080614
    Name     : TSF_0_UPPER_READONLY
    Bit      : 32
    R/W      : R
---------------------------------------------------------------------------------
   [31: 0]    TSF_0_UPPER_READONLY          R    default = 0
               -Upper 32bit of 64bit TSF0


---------------------------------------------------------------------------------
    Address  : 0x40080618
    Name     : TSF_1_LOWER_READONLY
    Bit      : 32
    R/W      : R
---------------------------------------------------------------------------------
   [31: 0]    TSF_1_LOWER_READONLY          R    default = 0
               -Lower 32bit of 64bit TSF1


---------------------------------------------------------------------------------
    Address  : 0x4008061c
    Name     : TSF_1_UPPER_READONLY
    Bit      : 32
    R/W      : R
---------------------------------------------------------------------------------
   [31: 0]    TSF_1_UPPER_READONLY          R    default = 0
               -Upper 32bit of 64bit TSF1


---------------------------------------------------------------------------------
    Address  : 0x40080620
    Name     : IRQ_SRC_NOCLEAR0
    Bit      : 32
    R/W      : R
---------------------------------------------------------------------------------
   [31: 0]    IRQ_SRC_NOCLEAR0              R    default = 0


---------------------------------------------------------------------------------
    Address  : 0x40080624
    Name     : IRQ_SRC_NOCLEAR1
    Bit      : 32
    R/W      : R
---------------------------------------------------------------------------------
   [31: 0]    IRQ_SRC_NOCLEAR1              R    default = 0


---------------------------------------------------------------------------------
    Address  : 0x40080628
    Name     : IRQ_SRC0
    Bit      : 32
    R/W      : R
---------------------------------------------------------------------------------
   + read_enable
---------------------------------------------------------------------------------
   [   31]    TSF1_ALARM                    R    default = 0

   [   30]    TBTT_IRQ_TSF1                 R    default = 0

   [   29]    RX_BUFFER_LOOKUP              R    default = 0

   [   28]    TSF0_ALARM                    R    default = 0

   [   27]    TBTT_IRQ_TSF0                 R    default = 0

   [   26]    AHB_SEC_IRQ                   R    default = 0

   [   25]    DMA_ERROR                     R    default = 0

   [   24]    TX_RESPONSE_TIMEOUT           R    default = 0

   [   23]    RX_DMA_DONE                   R    default = 0

   [   22]    RX_DONE                       R    default = 0

   [21:11]    TX_DONE_BITMAP                R    default = 0

   [10: 0]    WIN_AC_BITMAP                 R    default = 0


---------------------------------------------------------------------------------
    Address  : 0x4008062c
    Name     : IRQ_SRC1
    Bit      : 32
    R/W      : R
---------------------------------------------------------------------------------
   + read_enable
---------------------------------------------------------------------------------
   [    2]    RX_PAGING                     R    default = 0

   [    1]    MYRAW_END                     R    default = 0

   [    0]    SUPPRESS_END                  R    default = 0


---------------------------------------------------------------------------------
    Address  : 0x40080630
    Name     : RX_NDP_PAGING
    Bit      : 32
    R/W      : R
---------------------------------------------------------------------------------
   [31: 0]    RX_NDP_PAGING                 R    default = 0
               -Save received NDP Paging frame addressed to me


---------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------*/
enum {
    MAC_REG_BASE_START                                                          = 0x40080000,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RST_SW                                                              = 0x40080000,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_CONFIG                                                              = 0x40080004,
//-------------------------------------------------------------------------------------------------------------------------------,
          MAC_REG_CONFIG_IRQ_CLEAR_MODE                                         = MAC_REG_CONFIG,
          MAC_REG_CONFIG_IRQ_CLEAR_MODE_SHIFT                                   = 31,
          MAC_REG_CONFIG_IRQ_CLEAR_MODE_MASK                                    = 0x80000000,
          MAC_REG_CONFIG_PV1_PAYLOAD_SHIFT_RX                                   = MAC_REG_CONFIG,
          MAC_REG_CONFIG_PV1_PAYLOAD_SHIFT_RX_SHIFT                             = 30,
          MAC_REG_CONFIG_PV1_PAYLOAD_SHIFT_RX_MASK                              = 0x40000000,
          MAC_REG_CONFIG_BITMAP_PROTECT_EN                                      = MAC_REG_CONFIG,
          MAC_REG_CONFIG_BITMAP_PROTECT_EN_SHIFT                                = 29,
          MAC_REG_CONFIG_BITMAP_PROTECT_EN_MASK                                 = 0x20000000,
          MAC_REG_CONFIG_RX_BUFFER_LOOKUP_IRQ_EN                                = MAC_REG_CONFIG,
          MAC_REG_CONFIG_RX_BUFFER_LOOKUP_IRQ_EN_SHIFT                          = 26,
          MAC_REG_CONFIG_RX_BUFFER_LOOKUP_IRQ_EN_MASK                           = 0x04000000,
          MAC_REG_CONFIG_RX_BUFFER_LOOKUP_MODE_TYPE                             = MAC_REG_CONFIG,
          MAC_REG_CONFIG_RX_BUFFER_LOOKUP_MODE_TYPE_SHIFT                       = 25,
          MAC_REG_CONFIG_RX_BUFFER_LOOKUP_MODE_TYPE_MASK                        = 0x02000000,
          MAC_REG_CONFIG_RX_BUFFER_LOOKUP_EN                                    = MAC_REG_CONFIG,
          MAC_REG_CONFIG_RX_BUFFER_LOOKUP_EN_SHIFT                              = 24,
          MAC_REG_CONFIG_RX_BUFFER_LOOKUP_EN_MASK                               = 0x01000000,
          MAC_REG_CONFIG_US_CLOCK                                               = MAC_REG_CONFIG,
          MAC_REG_CONFIG_US_CLOCK_SHIFT                                         = 16,
          MAC_REG_CONFIG_US_CLOCK_MASK                                          = 0x00ff0000,
          MAC_REG_CONFIG_ENCR_MIC_SELECTED                                      = MAC_REG_CONFIG,
          MAC_REG_CONFIG_ENCR_MIC_SELECTED_SHIFT                                = 13,
          MAC_REG_CONFIG_ENCR_MIC_SELECTED_MASK                                 = 0x00002000,
          MAC_REG_CONFIG_RECV_MIC_REMAIN                                        = MAC_REG_CONFIG,
          MAC_REG_CONFIG_RECV_MIC_REMAIN_SHIFT                                  = 12,
          MAC_REG_CONFIG_RECV_MIC_REMAIN_MASK                                   = 0x00001000,
          MAC_REG_CONFIG_AIFSN_UPPER                                            = MAC_REG_CONFIG,
          MAC_REG_CONFIG_AIFSN_UPPER_SHIFT                                      = 8,
          MAC_REG_CONFIG_AIFSN_UPPER_MASK                                       = 0x00000f00,
          MAC_REG_CONFIG_TX_PD_CONFIG                                           = MAC_REG_CONFIG,
          MAC_REG_CONFIG_TX_PD_CONFIG_SHIFT                                     = 6,
          MAC_REG_CONFIG_TX_PD_CONFIG_MASK                                      = 0x000000c0,
          MAC_REG_CONFIG_PD_MAC_RX_TOP                                          = MAC_REG_CONFIG,
          MAC_REG_CONFIG_PD_MAC_RX_TOP_SHIFT                                    = 5,
          MAC_REG_CONFIG_PD_MAC_RX_TOP_MASK                                     = 0x00000020,
          MAC_REG_CONFIG_PD_MAC_LOOPBACK                                        = MAC_REG_CONFIG,
          MAC_REG_CONFIG_PD_MAC_LOOPBACK_SHIFT                                  = 4,
          MAC_REG_CONFIG_PD_MAC_LOOPBACK_MASK                                   = 0x00000010,
          MAC_REG_CONFIG_RX_DMA_PROMISCUOUS_MODE                                = MAC_REG_CONFIG,
          MAC_REG_CONFIG_RX_DMA_PROMISCUOUS_MODE_SHIFT                          = 2,
          MAC_REG_CONFIG_RX_DMA_PROMISCUOUS_MODE_MASK                           = 0x00000004,
          MAC_REG_CONFIG_CCA_IGNORE                                             = MAC_REG_CONFIG,
          MAC_REG_CONFIG_CCA_IGNORE_SHIFT                                       = 1,
          MAC_REG_CONFIG_CCA_IGNORE_MASK                                        = 0x00000002,
          MAC_REG_CONFIG_MAC_LOOPBACK                                           = MAC_REG_CONFIG,
          MAC_REG_CONFIG_MAC_LOOPBACK_SHIFT                                     = 0,
          MAC_REG_CONFIG_MAC_LOOPBACK_MASK                                      = 0x00000001,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_SIFS_DURATION                                                       = 0x40080008,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_SLOT_DURATION                                                       = 0x4008000c,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TXPWR_POST_DELAY_CLOCK                                              = 0x40080010,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_CRASH                                                               = 0x40080014,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_RESPONSE_CONTROL                                                 = 0x40080018,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_OPERATION_BAND                                                      = 0x4008001c,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TXPPDU_DELAY_CLOCK                                                  = 0x40080020,
//-------------------------------------------------------------------------------------------------------------------------------,
          MAC_REG_TXPPDU_DELAY_CLOCK_FILTER_DELAY2                              = MAC_REG_TXPPDU_DELAY_CLOCK,
          MAC_REG_TXPPDU_DELAY_CLOCK_FILTER_DELAY2_SHIFT                        = 20,
          MAC_REG_TXPPDU_DELAY_CLOCK_FILTER_DELAY2_MASK                         = 0x3ff00000,
          MAC_REG_TXPPDU_DELAY_CLOCK_FILTER_DELAY1                              = MAC_REG_TXPPDU_DELAY_CLOCK,
          MAC_REG_TXPPDU_DELAY_CLOCK_FILTER_DELAY1_SHIFT                        = 10,
          MAC_REG_TXPPDU_DELAY_CLOCK_FILTER_DELAY1_MASK                         = 0x000ffc00,
          MAC_REG_TXPPDU_DELAY_CLOCK_FILTER_DELAY0                              = MAC_REG_TXPPDU_DELAY_CLOCK,
          MAC_REG_TXPPDU_DELAY_CLOCK_FILTER_DELAY0_SHIFT                        = 0,
          MAC_REG_TXPPDU_DELAY_CLOCK_FILTER_DELAY0_MASK                         = 0x000003ff,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_READY_BEFORE_TXPPDU_CLOCK                                           = 0x40080024,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_READY_TO_TXPOWER_CLOCK                                              = 0x40080028,
//-------------------------------------------------------------------------------------------------------------------------------,
          MAC_REG_READY_TO_TXPOWER_CLOCK_READY_TO_TXPOWER_CLOCK_1M              = MAC_REG_READY_TO_TXPOWER_CLOCK,
          MAC_REG_READY_TO_TXPOWER_CLOCK_READY_TO_TXPOWER_CLOCK_1M_SHIFT        = 20,
          MAC_REG_READY_TO_TXPOWER_CLOCK_READY_TO_TXPOWER_CLOCK_1M_MASK         = 0x3ff00000,
          MAC_REG_READY_TO_TXPOWER_CLOCK_READY_TO_TXPOWER_CLOCK_2M              = MAC_REG_READY_TO_TXPOWER_CLOCK,
          MAC_REG_READY_TO_TXPOWER_CLOCK_READY_TO_TXPOWER_CLOCK_2M_SHIFT        = 10,
          MAC_REG_READY_TO_TXPOWER_CLOCK_READY_TO_TXPOWER_CLOCK_2M_MASK         = 0x000ffc00,
          MAC_REG_READY_TO_TXPOWER_CLOCK_READY_TO_TXPOWER_CLOCK_4M              = MAC_REG_READY_TO_TXPOWER_CLOCK,
          MAC_REG_READY_TO_TXPOWER_CLOCK_READY_TO_TXPOWER_CLOCK_4M_SHIFT        = 0,
          MAC_REG_READY_TO_TXPOWER_CLOCK_READY_TO_TXPOWER_CLOCK_4M_MASK         = 0x000003ff,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TXPOWER_TO_TXREQUEST_CLOCK                                          = 0x4008002c,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RESPONSE_TIMEOUT_US                                                 = 0x40080030,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_CONFIG_EXT                                                          = 0x40080034,
//-------------------------------------------------------------------------------------------------------------------------------,
          MAC_REG_CONFIG_EXT_SEARCH_FIELD_TIMEOUT                               = MAC_REG_CONFIG_EXT,
          MAC_REG_CONFIG_EXT_SEARCH_FIELD_TIMEOUT_SHIFT                         = 16,
          MAC_REG_CONFIG_EXT_SEARCH_FIELD_TIMEOUT_MASK                          = 0x003f0000,
          MAC_REG_CONFIG_EXT_BACKOFF_FINE_TUNE                                  = MAC_REG_CONFIG_EXT,
          MAC_REG_CONFIG_EXT_BACKOFF_FINE_TUNE_SHIFT                            = 14,
          MAC_REG_CONFIG_EXT_BACKOFF_FINE_TUNE_MASK                             = 0x00004000,
          MAC_REG_CONFIG_EXT_MPDU_FCS                                           = MAC_REG_CONFIG_EXT,
          MAC_REG_CONFIG_EXT_MPDU_FCS_SHIFT                                     = 13,
          MAC_REG_CONFIG_EXT_MPDU_FCS_MASK                                      = 0x00002000,
          MAC_REG_CONFIG_EXT_SIFS_TIMEOUT_EN                                    = MAC_REG_CONFIG_EXT,
          MAC_REG_CONFIG_EXT_SIFS_TIMEOUT_EN_SHIFT                              = 12,
          MAC_REG_CONFIG_EXT_SIFS_TIMEOUT_EN_MASK                               = 0x00001000,
          MAC_REG_CONFIG_EXT_RESP_MOREDATA_MODE                                 = MAC_REG_CONFIG_EXT,
          MAC_REG_CONFIG_EXT_RESP_MOREDATA_MODE_SHIFT                           = 8,
          MAC_REG_CONFIG_EXT_RESP_MOREDATA_MODE_MASK                            = 0x00000f00,
          MAC_REG_CONFIG_EXT_SNR_FEEDBACK_EN                                    = MAC_REG_CONFIG_EXT,
          MAC_REG_CONFIG_EXT_SNR_FEEDBACK_EN_SHIFT                              = 6,
          MAC_REG_CONFIG_EXT_SNR_FEEDBACK_EN_MASK                               = 0x000000c0,
          MAC_REG_CONFIG_EXT_NDP_PAGING_WAKEUP                                  = MAC_REG_CONFIG_EXT,
          MAC_REG_CONFIG_EXT_NDP_PAGING_WAKEUP_SHIFT                            = 5,
          MAC_REG_CONFIG_EXT_NDP_PAGING_WAKEUP_MASK                             = 0x00000020,
          MAC_REG_CONFIG_EXT_TWT_RESPONDER_EN                                   = MAC_REG_CONFIG_EXT,
          MAC_REG_CONFIG_EXT_TWT_RESPONDER_EN_SHIFT                             = 4,
          MAC_REG_CONFIG_EXT_TWT_RESPONDER_EN_MASK                              = 0x00000010,
          MAC_REG_CONFIG_EXT_RX_REG_INTF_CTRL                                   = MAC_REG_CONFIG_EXT,
          MAC_REG_CONFIG_EXT_RX_REG_INTF_CTRL_SHIFT                             = 0,
          MAC_REG_CONFIG_EXT_RX_REG_INTF_CTRL_MASK                              = 0x0000000f,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_STA_FILTER_MODE                                                     = 0x40080038,
//-------------------------------------------------------------------------------------------------------------------------------,
          MAC_REG_STA_FILTER_MODE_RX_MY_NDP_PAGING                              = MAC_REG_STA_FILTER_MODE,
          MAC_REG_STA_FILTER_MODE_RX_MY_NDP_PAGING_SHIFT                        = 12,
          MAC_REG_STA_FILTER_MODE_RX_MY_NDP_PAGING_MASK                         = 0x00001000,
          MAC_REG_STA_FILTER_MODE_RX_NDP_PROBE_REQ                              = MAC_REG_STA_FILTER_MODE,
          MAC_REG_STA_FILTER_MODE_RX_NDP_PROBE_REQ_SHIFT                        = 11,
          MAC_REG_STA_FILTER_MODE_RX_NDP_PROBE_REQ_MASK                         = 0x00000800,
          MAC_REG_STA_FILTER_MODE_RX_ALL                                        = MAC_REG_STA_FILTER_MODE,
          MAC_REG_STA_FILTER_MODE_RX_ALL_SHIFT                                  = 10,
          MAC_REG_STA_FILTER_MODE_RX_ALL_MASK                                   = 0x00000400,
          MAC_REG_STA_FILTER_MODE_RX_PV1_FRAME                                  = MAC_REG_STA_FILTER_MODE,
          MAC_REG_STA_FILTER_MODE_RX_PV1_FRAME_SHIFT                            = 9,
          MAC_REG_STA_FILTER_MODE_RX_PV1_FRAME_MASK                             = 0x00000200,
          MAC_REG_STA_FILTER_MODE_RX_CONTROL_FRAME                              = MAC_REG_STA_FILTER_MODE,
          MAC_REG_STA_FILTER_MODE_RX_CONTROL_FRAME_SHIFT                        = 8,
          MAC_REG_STA_FILTER_MODE_RX_CONTROL_FRAME_MASK                         = 0x00000100,
          MAC_REG_STA_FILTER_MODE_RX_MANAGEMENT_FRAME                           = MAC_REG_STA_FILTER_MODE,
          MAC_REG_STA_FILTER_MODE_RX_MANAGEMENT_FRAME_SHIFT                     = 7,
          MAC_REG_STA_FILTER_MODE_RX_MANAGEMENT_FRAME_MASK                      = 0x00000080,
          MAC_REG_STA_FILTER_MODE_RX_GROUP_ADDRESSED                            = MAC_REG_STA_FILTER_MODE,
          MAC_REG_STA_FILTER_MODE_RX_GROUP_ADDRESSED_SHIFT                      = 6,
          MAC_REG_STA_FILTER_MODE_RX_GROUP_ADDRESSED_MASK                       = 0x00000040,
          MAC_REG_STA_FILTER_MODE_RX_ALL_NDP_FRAME                              = MAC_REG_STA_FILTER_MODE,
          MAC_REG_STA_FILTER_MODE_RX_ALL_NDP_FRAME_SHIFT                        = 5,
          MAC_REG_STA_FILTER_MODE_RX_ALL_NDP_FRAME_MASK                         = 0x00000020,
          MAC_REG_STA_FILTER_MODE_RX_MY_CONTROL_FRAME                           = MAC_REG_STA_FILTER_MODE,
          MAC_REG_STA_FILTER_MODE_RX_MY_CONTROL_FRAME_SHIFT                     = 4,
          MAC_REG_STA_FILTER_MODE_RX_MY_CONTROL_FRAME_MASK                      = 0x00000010,
          MAC_REG_STA_FILTER_MODE_RX_MY_NDP_FRAME                               = MAC_REG_STA_FILTER_MODE,
          MAC_REG_STA_FILTER_MODE_RX_MY_NDP_FRAME_SHIFT                         = 3,
          MAC_REG_STA_FILTER_MODE_RX_MY_NDP_FRAME_MASK                          = 0x00000008,
          MAC_REG_STA_FILTER_MODE_RX_MY_ACK_FRAME                               = MAC_REG_STA_FILTER_MODE,
          MAC_REG_STA_FILTER_MODE_RX_MY_ACK_FRAME_SHIFT                         = 2,
          MAC_REG_STA_FILTER_MODE_RX_MY_ACK_FRAME_MASK                          = 0x00000004,
          MAC_REG_STA_FILTER_MODE_RX_MY_IDLE_INDICATION                         = MAC_REG_STA_FILTER_MODE,
          MAC_REG_STA_FILTER_MODE_RX_MY_IDLE_INDICATION_SHIFT                   = 1,
          MAC_REG_STA_FILTER_MODE_RX_MY_IDLE_INDICATION_MASK                    = 0x00000002,
          MAC_REG_STA_FILTER_MODE_RX_MY_PM_BIT_FRAME                            = MAC_REG_STA_FILTER_MODE,
          MAC_REG_STA_FILTER_MODE_RX_MY_PM_BIT_FRAME_SHIFT                      = 0,
          MAC_REG_STA_FILTER_MODE_RX_MY_PM_BIT_FRAME_MASK                       = 0x00000001,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_INTF_CFG_ACTIVE_BITMAP                                              = 0x4008003c,
//-------------------------------------------------------------------------------------------------------------------------------,
          MAC_REG_INTF_CFG_ACTIVE_BITMAP_AID_INTF_CFG                           = MAC_REG_INTF_CFG_ACTIVE_BITMAP,
          MAC_REG_INTF_CFG_ACTIVE_BITMAP_AID_INTF_CFG_SHIFT                     = 24,
          MAC_REG_INTF_CFG_ACTIVE_BITMAP_AID_INTF_CFG_MASK                      = 0x0f000000,
          MAC_REG_INTF_CFG_ACTIVE_BITMAP_MACADDR_INTF_CFG                       = MAC_REG_INTF_CFG_ACTIVE_BITMAP,
          MAC_REG_INTF_CFG_ACTIVE_BITMAP_MACADDR_INTF_CFG_SHIFT                 = 20,
          MAC_REG_INTF_CFG_ACTIVE_BITMAP_MACADDR_INTF_CFG_MASK                  = 0x00f00000,
          MAC_REG_INTF_CFG_ACTIVE_BITMAP_BSS_INTF_CFG                           = MAC_REG_INTF_CFG_ACTIVE_BITMAP,
          MAC_REG_INTF_CFG_ACTIVE_BITMAP_BSS_INTF_CFG_SHIFT                     = 16,
          MAC_REG_INTF_CFG_ACTIVE_BITMAP_BSS_INTF_CFG_MASK                      = 0x000f0000,
          MAC_REG_INTF_CFG_ACTIVE_BITMAP_BSSID_MODE                             = MAC_REG_INTF_CFG_ACTIVE_BITMAP,
          MAC_REG_INTF_CFG_ACTIVE_BITMAP_BSSID_MODE_SHIFT                       = 8,
          MAC_REG_INTF_CFG_ACTIVE_BITMAP_BSSID_MODE_MASK                        = 0x00000f00,
          MAC_REG_INTF_CFG_ACTIVE_BITMAP_MACADDR_ENABLE                         = MAC_REG_INTF_CFG_ACTIVE_BITMAP,
          MAC_REG_INTF_CFG_ACTIVE_BITMAP_MACADDR_ENABLE_SHIFT                   = 4,
          MAC_REG_INTF_CFG_ACTIVE_BITMAP_MACADDR_ENABLE_MASK                    = 0x000000f0,
          MAC_REG_INTF_CFG_ACTIVE_BITMAP_BSS_ENABLE                             = MAC_REG_INTF_CFG_ACTIVE_BITMAP,
          MAC_REG_INTF_CFG_ACTIVE_BITMAP_BSS_ENABLE_SHIFT                       = 0,
          MAC_REG_INTF_CFG_ACTIVE_BITMAP_BSS_ENABLE_MASK                        = 0x0000000f,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_SIFS_TIMEOUT                                                        = 0x40080040,
//-------------------------------------------------------------------------------------------------------------------------------,
          MAC_REG_SIFS_TIMEOUT_SIFS_TIMEOUT_US                                  = MAC_REG_SIFS_TIMEOUT,
          MAC_REG_SIFS_TIMEOUT_SIFS_TIMEOUT_US_SHIFT                            = 0,
          MAC_REG_SIFS_TIMEOUT_SIFS_TIMEOUT_US_MASK                             = 0x0000ffff,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_STA_BSSID0_LOWER                                                    = 0x40080044,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_STA_BSSID0_UPPER                                                    = 0x40080048,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_STA_BSSID1_LOWER                                                    = 0x4008004c,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_STA_BSSID1_UPPER                                                    = 0x40080050,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_STA_BSSID2_LOWER                                                    = 0x40080054,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_STA_BSSID2_UPPER                                                    = 0x40080058,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_STA_BSSID3_LOWER                                                    = 0x4008005c,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_STA_BSSID3_UPPER                                                    = 0x40080060,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_STA_MAC_ADDRESS0_LOWER                                                  = 0x40080064,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_STA_MAC_ADDRESS0_UPPER                                                  = 0x40080068,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_STA_MAC_ADDRESS1_LOWER                                                  = 0x4008006c,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_STA_MAC_ADDRESS1_UPPER                                                  = 0x40080070,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_STA_MAC_ADDRESS2_LOWER                                                  = 0x40080074,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_STA_MAC_ADDRESS2_UPPER                                                  = 0x40080078,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_STA_MAC_ADDRESS3_LOWER                                                  = 0x4008007c,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_STA_MAC_ADDRESS3_UPPER                                                  = 0x40080080,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_STA_AID0_0                                                          = 0x40080084,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_STA_AID0_1                                                          = 0x40080088,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_STA_AID0_2                                                          = 0x4008008c,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_STA_AID1_0                                                          = 0x40080090,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_STA_AID1_1                                                          = 0x40080094,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_STA_AID1_2                                                          = 0x40080098,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_STA_AID2_0                                                          = 0x4008009c,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_STA_AID2_1                                                          = 0x400800a0,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_STA_AID2_2                                                          = 0x400800a4,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_STA_AID3_0                                                          = 0x400800a8,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_STA_AID3_1                                                          = 0x400800ac,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_STA_AID3_2                                                          = 0x400800b0,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_DMA_BURST                                                           = 0x400800b4,
//-------------------------------------------------------------------------------------------------------------------------------,
          MAC_REG_DMA_BURST_DMA_BURST_MAX                                       = MAC_REG_DMA_BURST,
          MAC_REG_DMA_BURST_DMA_BURST_MAX_SHIFT                                 = 6,
          MAC_REG_DMA_BURST_DMA_BURST_MAX_MASK                                  = 0x00000fc0,
          MAC_REG_DMA_BURST_DMA_BURST_MIN                                       = MAC_REG_DMA_BURST,
          MAC_REG_DMA_BURST_DMA_BURST_MIN_SHIFT                                 = 0,
          MAC_REG_DMA_BURST_DMA_BURST_MIN_MASK                                  = 0x0000003f,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_DMA_READ_FIFO_ADJUST                                                = 0x400800b8,
//-------------------------------------------------------------------------------------------------------------------------------,
          MAC_REG_DMA_READ_FIFO_ADJUST_DMA_READ_FIFO_REFRESH_SWITCH             = MAC_REG_DMA_READ_FIFO_ADJUST,
          MAC_REG_DMA_READ_FIFO_ADJUST_DMA_READ_FIFO_REFRESH_SWITCH_SHIFT       = 31,
          MAC_REG_DMA_READ_FIFO_ADJUST_DMA_READ_FIFO_REFRESH_SWITCH_MASK        = 0x80000000,
          MAC_REG_DMA_READ_FIFO_ADJUST_DMA_READ_FIFO_REFRESH_SIZE               = MAC_REG_DMA_READ_FIFO_ADJUST,
          MAC_REG_DMA_READ_FIFO_ADJUST_DMA_READ_FIFO_REFRESH_SIZE_SHIFT         = 20,
          MAC_REG_DMA_READ_FIFO_ADJUST_DMA_READ_FIFO_REFRESH_SIZE_MASK          = 0x0ff00000,
          MAC_REG_DMA_READ_FIFO_ADJUST_DMA_READ_FIFO_FULL_ADJUST                = MAC_REG_DMA_READ_FIFO_ADJUST,
          MAC_REG_DMA_READ_FIFO_ADJUST_DMA_READ_FIFO_FULL_ADJUST_SHIFT          = 0,
          MAC_REG_DMA_READ_FIFO_ADJUST_DMA_READ_FIFO_FULL_ADJUST_MASK           = 0x000000ff,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_CONCURRENT_CONFIG_BITMAP                                            = 0x400800bc,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_CONTROL_PARAMETER                                                = 0x400800c0,
//-------------------------------------------------------------------------------------------------------------------------------,
          MAC_REG_TX_CONTROL_PARAMETER_RX_RESPONSE_CONTROL                      = MAC_REG_TX_CONTROL_PARAMETER,
          MAC_REG_TX_CONTROL_PARAMETER_RX_RESPONSE_CONTROL_SHIFT                = 30,
          MAC_REG_TX_CONTROL_PARAMETER_RX_RESPONSE_CONTROL_MASK                 = 0xc0000000,
          MAC_REG_TX_CONTROL_PARAMETER_TX_ERROR_RECOVERY                        = MAC_REG_TX_CONTROL_PARAMETER,
          MAC_REG_TX_CONTROL_PARAMETER_TX_ERROR_RECOVERY_SHIFT                  = 29,
          MAC_REG_TX_CONTROL_PARAMETER_TX_ERROR_RECOVERY_MASK                   = 0x20000000,
          MAC_REG_TX_CONTROL_PARAMETER_CCA_LATE_DETECTION                       = MAC_REG_TX_CONTROL_PARAMETER,
          MAC_REG_TX_CONTROL_PARAMETER_CCA_LATE_DETECTION_SHIFT                 = 28,
          MAC_REG_TX_CONTROL_PARAMETER_CCA_LATE_DETECTION_MASK                  = 0x10000000,
          MAC_REG_TX_CONTROL_PARAMETER_VECTOR_TIMEOUT                           = MAC_REG_TX_CONTROL_PARAMETER,
          MAC_REG_TX_CONTROL_PARAMETER_VECTOR_TIMEOUT_SHIFT                     = 20,
          MAC_REG_TX_CONTROL_PARAMETER_VECTOR_TIMEOUT_MASK                      = 0x0ff00000,
          MAC_REG_TX_CONTROL_PARAMETER_VECTOR_WAIT_TIME                         = MAC_REG_TX_CONTROL_PARAMETER,
          MAC_REG_TX_CONTROL_PARAMETER_VECTOR_WAIT_TIME_SHIFT                   = 16,
          MAC_REG_TX_CONTROL_PARAMETER_VECTOR_WAIT_TIME_MASK                    = 0x000f0000,
          MAC_REG_TX_CONTROL_PARAMETER_OTHER_FRAG_DATA_WORD_OFFSET              = MAC_REG_TX_CONTROL_PARAMETER,
          MAC_REG_TX_CONTROL_PARAMETER_OTHER_FRAG_DATA_WORD_OFFSET_SHIFT        = 12,
          MAC_REG_TX_CONTROL_PARAMETER_OTHER_FRAG_DATA_WORD_OFFSET_MASK         = 0x0000f000,
          MAC_REG_TX_CONTROL_PARAMETER_FIRST_FRAG_DATA_WORD_OFFSET              = MAC_REG_TX_CONTROL_PARAMETER,
          MAC_REG_TX_CONTROL_PARAMETER_FIRST_FRAG_DATA_WORD_OFFSET_SHIFT        = 8,
          MAC_REG_TX_CONTROL_PARAMETER_FIRST_FRAG_DATA_WORD_OFFSET_MASK         = 0x00000f00,
          MAC_REG_TX_CONTROL_PARAMETER_RESPONSE_WAIT_TIME_US                    = MAC_REG_TX_CONTROL_PARAMETER,
          MAC_REG_TX_CONTROL_PARAMETER_RESPONSE_WAIT_TIME_US_SHIFT              = 0,
          MAC_REG_TX_CONTROL_PARAMETER_RESPONSE_WAIT_TIME_US_MASK               = 0x000000ff,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RSP0                                                                = 0x400800c4,
//-------------------------------------------------------------------------------------------------------------------------------,
          MAC_REG_RSP0_RSP0_VALID                                               = MAC_REG_RSP0,
          MAC_REG_RSP0_RSP0_VALID_SHIFT                                         = 31,
          MAC_REG_RSP0_RSP0_VALID_MASK                                          = 0x80000000,
          MAC_REG_RSP0_RSP0_CASE                                                = MAC_REG_RSP0,
          MAC_REG_RSP0_RSP0_CASE_SHIFT                                          = 26,
          MAC_REG_RSP0_RSP0_CASE_MASK                                           = 0x7c000000,
          MAC_REG_RSP0_RSP0_MASK_RX_INFO_OK                                     = MAC_REG_RSP0,
          MAC_REG_RSP0_RSP0_MASK_RX_INFO_OK_SHIFT                               = 25,
          MAC_REG_RSP0_RSP0_MASK_RX_INFO_OK_MASK                                = 0x02000000,
          MAC_REG_RSP0_RSP0_MASK_RX_INFO_NDP                                    = MAC_REG_RSP0,
          MAC_REG_RSP0_RSP0_MASK_RX_INFO_NDP_SHIFT                              = 24,
          MAC_REG_RSP0_RSP0_MASK_RX_INFO_NDP_MASK                               = 0x01000000,
          MAC_REG_RSP0_RSP0_MASK_RX_NDP_PSPOLL                                  = MAC_REG_RSP0,
          MAC_REG_RSP0_RSP0_MASK_RX_NDP_PSPOLL_SHIFT                            = 23,
          MAC_REG_RSP0_RSP0_MASK_RX_NDP_PSPOLL_MASK                             = 0x00800000,
          MAC_REG_RSP0_RSP0_MASK_RX_PV0_TYPE                                    = MAC_REG_RSP0,
          MAC_REG_RSP0_RSP0_MASK_RX_PV0_TYPE_SHIFT                              = 21,
          MAC_REG_RSP0_RSP0_MASK_RX_PV0_TYPE_MASK                               = 0x00600000,
          MAC_REG_RSP0_RSP0_MASK_RX_PV0_SUBTYPE                                 = MAC_REG_RSP0,
          MAC_REG_RSP0_RSP0_MASK_RX_PV0_SUBTYPE_SHIFT                           = 17,
          MAC_REG_RSP0_RSP0_MASK_RX_PV0_SUBTYPE_MASK                            = 0x001e0000,
          MAC_REG_RSP0_RSP0_MASK_RX_PV                                          = MAC_REG_RSP0,
          MAC_REG_RSP0_RSP0_MASK_RX_PV_SHIFT                                    = 16,
          MAC_REG_RSP0_RSP0_MASK_RX_PV_MASK                                     = 0x00010000,
          MAC_REG_RSP0_RSP0_MASK_GROUP_ADDRESS                                  = MAC_REG_RSP0,
          MAC_REG_RSP0_RSP0_MASK_GROUP_ADDRESS_SHIFT                            = 15,
          MAC_REG_RSP0_RSP0_MASK_GROUP_ADDRESS_MASK                             = 0x00008000,
          MAC_REG_RSP0_RSP0_MASK_OPERATION                                      = MAC_REG_RSP0,
          MAC_REG_RSP0_RSP0_MASK_OPERATION_SHIFT                                = 14,
          MAC_REG_RSP0_RSP0_MASK_OPERATION_MASK                                 = 0x00004000,
          MAC_REG_RSP0_RSP0_MASK_RX_INFO_AGG                                    = MAC_REG_RSP0,
          MAC_REG_RSP0_RSP0_MASK_RX_INFO_AGG_SHIFT                              = 13,
          MAC_REG_RSP0_RSP0_MASK_RX_INFO_AGG_MASK                               = 0x00002000,
          MAC_REG_RSP0_RSP0_RX_INFO_OK                                          = MAC_REG_RSP0,
          MAC_REG_RSP0_RSP0_RX_INFO_OK_SHIFT                                    = 12,
          MAC_REG_RSP0_RSP0_RX_INFO_OK_MASK                                     = 0x00001000,
          MAC_REG_RSP0_RSP0_RX_INFO_NDP                                         = MAC_REG_RSP0,
          MAC_REG_RSP0_RSP0_RX_INFO_NDP_SHIFT                                   = 11,
          MAC_REG_RSP0_RSP0_RX_INFO_NDP_MASK                                    = 0x00000800,
          MAC_REG_RSP0_RSP0_RX_NDP_PSPOLL                                       = MAC_REG_RSP0,
          MAC_REG_RSP0_RSP0_RX_NDP_PSPOLL_SHIFT                                 = 10,
          MAC_REG_RSP0_RSP0_RX_NDP_PSPOLL_MASK                                  = 0x00000400,
          MAC_REG_RSP0_RSP0_RX_PV0_TYPE                                         = MAC_REG_RSP0,
          MAC_REG_RSP0_RSP0_RX_PV0_TYPE_SHIFT                                   = 8,
          MAC_REG_RSP0_RSP0_RX_PV0_TYPE_MASK                                    = 0x00000300,
          MAC_REG_RSP0_RSP0_RX_PV0_SUBTYPE                                      = MAC_REG_RSP0,
          MAC_REG_RSP0_RSP0_RX_PV0_SUBTYPE_SHIFT                                = 4,
          MAC_REG_RSP0_RSP0_RX_PV0_SUBTYPE_MASK                                 = 0x000000f0,
          MAC_REG_RSP0_RSP0_RX_PV                                               = MAC_REG_RSP0,
          MAC_REG_RSP0_RSP0_RX_PV_SHIFT                                         = 3,
          MAC_REG_RSP0_RSP0_RX_PV_MASK                                          = 0x00000008,
          MAC_REG_RSP0_RSP0_GROUP_ADDRESS                                       = MAC_REG_RSP0,
          MAC_REG_RSP0_RSP0_GROUP_ADDRESS_SHIFT                                 = 2,
          MAC_REG_RSP0_RSP0_GROUP_ADDRESS_MASK                                  = 0x00000004,
          MAC_REG_RSP0_RSP0_OPERATION                                           = MAC_REG_RSP0,
          MAC_REG_RSP0_RSP0_OPERATION_SHIFT                                     = 1,
          MAC_REG_RSP0_RSP0_OPERATION_MASK                                      = 0x00000002,
          MAC_REG_RSP0_RSP0_RX_INFO_AGG                                         = MAC_REG_RSP0,
          MAC_REG_RSP0_RSP0_RX_INFO_AGG_SHIFT                                   = 0,
          MAC_REG_RSP0_RSP0_RX_INFO_AGG_MASK                                    = 0x00000001,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RSP1                                                                = 0x400800c8,
//-------------------------------------------------------------------------------------------------------------------------------,
          MAC_REG_RSP1_RSP1_VALID                                               = MAC_REG_RSP1,
          MAC_REG_RSP1_RSP1_VALID_SHIFT                                         = 31,
          MAC_REG_RSP1_RSP1_VALID_MASK                                          = 0x80000000,
          MAC_REG_RSP1_RSP1_CASE                                                = MAC_REG_RSP1,
          MAC_REG_RSP1_RSP1_CASE_SHIFT                                          = 26,
          MAC_REG_RSP1_RSP1_CASE_MASK                                           = 0x7c000000,
          MAC_REG_RSP1_RSP1_MASK_RX_INFO_OK                                     = MAC_REG_RSP1,
          MAC_REG_RSP1_RSP1_MASK_RX_INFO_OK_SHIFT                               = 25,
          MAC_REG_RSP1_RSP1_MASK_RX_INFO_OK_MASK                                = 0x02000000,
          MAC_REG_RSP1_RSP1_MASK_RX_INFO_NDP                                    = MAC_REG_RSP1,
          MAC_REG_RSP1_RSP1_MASK_RX_INFO_NDP_SHIFT                              = 24,
          MAC_REG_RSP1_RSP1_MASK_RX_INFO_NDP_MASK                               = 0x01000000,
          MAC_REG_RSP1_RSP1_MASK_RX_NDP_PSPOLL                                  = MAC_REG_RSP1,
          MAC_REG_RSP1_RSP1_MASK_RX_NDP_PSPOLL_SHIFT                            = 23,
          MAC_REG_RSP1_RSP1_MASK_RX_NDP_PSPOLL_MASK                             = 0x00800000,
          MAC_REG_RSP1_RSP1_MASK_RX_PV0_TYPE                                    = MAC_REG_RSP1,
          MAC_REG_RSP1_RSP1_MASK_RX_PV0_TYPE_SHIFT                              = 21,
          MAC_REG_RSP1_RSP1_MASK_RX_PV0_TYPE_MASK                               = 0x00600000,
          MAC_REG_RSP1_RSP1_MASK_RX_PV0_SUBTYPE                                 = MAC_REG_RSP1,
          MAC_REG_RSP1_RSP1_MASK_RX_PV0_SUBTYPE_SHIFT                           = 17,
          MAC_REG_RSP1_RSP1_MASK_RX_PV0_SUBTYPE_MASK                            = 0x001e0000,
          MAC_REG_RSP1_RSP1_MASK_RX_PV                                          = MAC_REG_RSP1,
          MAC_REG_RSP1_RSP1_MASK_RX_PV_SHIFT                                    = 16,
          MAC_REG_RSP1_RSP1_MASK_RX_PV_MASK                                     = 0x00010000,
          MAC_REG_RSP1_RSP1_MASK_GROUP_ADDRESS                                  = MAC_REG_RSP1,
          MAC_REG_RSP1_RSP1_MASK_GROUP_ADDRESS_SHIFT                            = 15,
          MAC_REG_RSP1_RSP1_MASK_GROUP_ADDRESS_MASK                             = 0x00008000,
          MAC_REG_RSP1_RSP1_MASK_OPERATION                                      = MAC_REG_RSP1,
          MAC_REG_RSP1_RSP1_MASK_OPERATION_SHIFT                                = 14,
          MAC_REG_RSP1_RSP1_MASK_OPERATION_MASK                                 = 0x00004000,
          MAC_REG_RSP1_RSP1_MASK_RX_INFO_AGG                                    = MAC_REG_RSP1,
          MAC_REG_RSP1_RSP1_MASK_RX_INFO_AGG_SHIFT                              = 13,
          MAC_REG_RSP1_RSP1_MASK_RX_INFO_AGG_MASK                               = 0x00002000,
          MAC_REG_RSP1_RSP1_RX_INFO_OK                                          = MAC_REG_RSP1,
          MAC_REG_RSP1_RSP1_RX_INFO_OK_SHIFT                                    = 12,
          MAC_REG_RSP1_RSP1_RX_INFO_OK_MASK                                     = 0x00001000,
          MAC_REG_RSP1_RSP1_RX_INFO_NDP                                         = MAC_REG_RSP1,
          MAC_REG_RSP1_RSP1_RX_INFO_NDP_SHIFT                                   = 11,
          MAC_REG_RSP1_RSP1_RX_INFO_NDP_MASK                                    = 0x00000800,
          MAC_REG_RSP1_RSP1_RX_NDP_PSPOLL                                       = MAC_REG_RSP1,
          MAC_REG_RSP1_RSP1_RX_NDP_PSPOLL_SHIFT                                 = 10,
          MAC_REG_RSP1_RSP1_RX_NDP_PSPOLL_MASK                                  = 0x00000400,
          MAC_REG_RSP1_RSP1_RX_PV0_TYPE                                         = MAC_REG_RSP1,
          MAC_REG_RSP1_RSP1_RX_PV0_TYPE_SHIFT                                   = 8,
          MAC_REG_RSP1_RSP1_RX_PV0_TYPE_MASK                                    = 0x00000300,
          MAC_REG_RSP1_RSP1_RX_PV0_SUBTYPE                                      = MAC_REG_RSP1,
          MAC_REG_RSP1_RSP1_RX_PV0_SUBTYPE_SHIFT                                = 4,
          MAC_REG_RSP1_RSP1_RX_PV0_SUBTYPE_MASK                                 = 0x000000f0,
          MAC_REG_RSP1_RSP1_RX_PV                                               = MAC_REG_RSP1,
          MAC_REG_RSP1_RSP1_RX_PV_SHIFT                                         = 3,
          MAC_REG_RSP1_RSP1_RX_PV_MASK                                          = 0x00000008,
          MAC_REG_RSP1_RSP1_GROUP_ADDRESS                                       = MAC_REG_RSP1,
          MAC_REG_RSP1_RSP1_GROUP_ADDRESS_SHIFT                                 = 2,
          MAC_REG_RSP1_RSP1_GROUP_ADDRESS_MASK                                  = 0x00000004,
          MAC_REG_RSP1_RSP1_OPERATION                                           = MAC_REG_RSP1,
          MAC_REG_RSP1_RSP1_OPERATION_SHIFT                                     = 1,
          MAC_REG_RSP1_RSP1_OPERATION_MASK                                      = 0x00000002,
          MAC_REG_RSP1_RSP1_RX_INFO_AGG                                         = MAC_REG_RSP1,
          MAC_REG_RSP1_RSP1_RX_INFO_AGG_SHIFT                                   = 0,
          MAC_REG_RSP1_RSP1_RX_INFO_AGG_MASK                                    = 0x00000001,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RSP2                                                                = 0x400800cc,
//-------------------------------------------------------------------------------------------------------------------------------,
          MAC_REG_RSP2_RSP2_VALID                                               = MAC_REG_RSP2,
          MAC_REG_RSP2_RSP2_VALID_SHIFT                                         = 31,
          MAC_REG_RSP2_RSP2_VALID_MASK                                          = 0x80000000,
          MAC_REG_RSP2_RSP2_CASE                                                = MAC_REG_RSP2,
          MAC_REG_RSP2_RSP2_CASE_SHIFT                                          = 26,
          MAC_REG_RSP2_RSP2_CASE_MASK                                           = 0x7c000000,
          MAC_REG_RSP2_RSP2_MASK_RX_INFO_OK                                     = MAC_REG_RSP2,
          MAC_REG_RSP2_RSP2_MASK_RX_INFO_OK_SHIFT                               = 25,
          MAC_REG_RSP2_RSP2_MASK_RX_INFO_OK_MASK                                = 0x02000000,
          MAC_REG_RSP2_RSP2_MASK_RX_INFO_NDP                                    = MAC_REG_RSP2,
          MAC_REG_RSP2_RSP2_MASK_RX_INFO_NDP_SHIFT                              = 24,
          MAC_REG_RSP2_RSP2_MASK_RX_INFO_NDP_MASK                               = 0x01000000,
          MAC_REG_RSP2_RSP2_MASK_RX_NDP_PSPOLL                                  = MAC_REG_RSP2,
          MAC_REG_RSP2_RSP2_MASK_RX_NDP_PSPOLL_SHIFT                            = 23,
          MAC_REG_RSP2_RSP2_MASK_RX_NDP_PSPOLL_MASK                             = 0x00800000,
          MAC_REG_RSP2_RSP2_MASK_RX_PV0_TYPE                                    = MAC_REG_RSP2,
          MAC_REG_RSP2_RSP2_MASK_RX_PV0_TYPE_SHIFT                              = 21,
          MAC_REG_RSP2_RSP2_MASK_RX_PV0_TYPE_MASK                               = 0x00600000,
          MAC_REG_RSP2_RSP2_MASK_RX_PV0_SUBTYPE                                 = MAC_REG_RSP2,
          MAC_REG_RSP2_RSP2_MASK_RX_PV0_SUBTYPE_SHIFT                           = 17,
          MAC_REG_RSP2_RSP2_MASK_RX_PV0_SUBTYPE_MASK                            = 0x001e0000,
          MAC_REG_RSP2_RSP2_MASK_RX_PV                                          = MAC_REG_RSP2,
          MAC_REG_RSP2_RSP2_MASK_RX_PV_SHIFT                                    = 16,
          MAC_REG_RSP2_RSP2_MASK_RX_PV_MASK                                     = 0x00010000,
          MAC_REG_RSP2_RSP2_MASK_GROUP_ADDRESS                                  = MAC_REG_RSP2,
          MAC_REG_RSP2_RSP2_MASK_GROUP_ADDRESS_SHIFT                            = 15,
          MAC_REG_RSP2_RSP2_MASK_GROUP_ADDRESS_MASK                             = 0x00008000,
          MAC_REG_RSP2_RSP2_MASK_OPERATION                                      = MAC_REG_RSP2,
          MAC_REG_RSP2_RSP2_MASK_OPERATION_SHIFT                                = 14,
          MAC_REG_RSP2_RSP2_MASK_OPERATION_MASK                                 = 0x00004000,
          MAC_REG_RSP2_RSP2_MASK_RX_INFO_AGG                                    = MAC_REG_RSP2,
          MAC_REG_RSP2_RSP2_MASK_RX_INFO_AGG_SHIFT                              = 13,
          MAC_REG_RSP2_RSP2_MASK_RX_INFO_AGG_MASK                               = 0x00002000,
          MAC_REG_RSP2_RSP2_RX_INFO_OK                                          = MAC_REG_RSP2,
          MAC_REG_RSP2_RSP2_RX_INFO_OK_SHIFT                                    = 12,
          MAC_REG_RSP2_RSP2_RX_INFO_OK_MASK                                     = 0x00001000,
          MAC_REG_RSP2_RSP2_RX_INFO_NDP                                         = MAC_REG_RSP2,
          MAC_REG_RSP2_RSP2_RX_INFO_NDP_SHIFT                                   = 11,
          MAC_REG_RSP2_RSP2_RX_INFO_NDP_MASK                                    = 0x00000800,
          MAC_REG_RSP2_RSP2_RX_NDP_PSPOLL                                       = MAC_REG_RSP2,
          MAC_REG_RSP2_RSP2_RX_NDP_PSPOLL_SHIFT                                 = 10,
          MAC_REG_RSP2_RSP2_RX_NDP_PSPOLL_MASK                                  = 0x00000400,
          MAC_REG_RSP2_RSP2_RX_PV0_TYPE                                         = MAC_REG_RSP2,
          MAC_REG_RSP2_RSP2_RX_PV0_TYPE_SHIFT                                   = 8,
          MAC_REG_RSP2_RSP2_RX_PV0_TYPE_MASK                                    = 0x00000300,
          MAC_REG_RSP2_RSP2_RX_PV0_SUBTYPE                                      = MAC_REG_RSP2,
          MAC_REG_RSP2_RSP2_RX_PV0_SUBTYPE_SHIFT                                = 4,
          MAC_REG_RSP2_RSP2_RX_PV0_SUBTYPE_MASK                                 = 0x000000f0,
          MAC_REG_RSP2_RSP2_RX_PV                                               = MAC_REG_RSP2,
          MAC_REG_RSP2_RSP2_RX_PV_SHIFT                                         = 3,
          MAC_REG_RSP2_RSP2_RX_PV_MASK                                          = 0x00000008,
          MAC_REG_RSP2_RSP2_GROUP_ADDRESS                                       = MAC_REG_RSP2,
          MAC_REG_RSP2_RSP2_GROUP_ADDRESS_SHIFT                                 = 2,
          MAC_REG_RSP2_RSP2_GROUP_ADDRESS_MASK                                  = 0x00000004,
          MAC_REG_RSP2_RSP2_OPERATION                                           = MAC_REG_RSP2,
          MAC_REG_RSP2_RSP2_OPERATION_SHIFT                                     = 1,
          MAC_REG_RSP2_RSP2_OPERATION_MASK                                      = 0x00000002,
          MAC_REG_RSP2_RSP2_RX_INFO_AGG                                         = MAC_REG_RSP2,
          MAC_REG_RSP2_RSP2_RX_INFO_AGG_SHIFT                                   = 0,
          MAC_REG_RSP2_RSP2_RX_INFO_AGG_MASK                                    = 0x00000001,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RSP3                                                                = 0x400800d0,
//-------------------------------------------------------------------------------------------------------------------------------,
          MAC_REG_RSP3_RSP3_VALID                                               = MAC_REG_RSP3,
          MAC_REG_RSP3_RSP3_VALID_SHIFT                                         = 31,
          MAC_REG_RSP3_RSP3_VALID_MASK                                          = 0x80000000,
          MAC_REG_RSP3_RSP3_CASE                                                = MAC_REG_RSP3,
          MAC_REG_RSP3_RSP3_CASE_SHIFT                                          = 26,
          MAC_REG_RSP3_RSP3_CASE_MASK                                           = 0x7c000000,
          MAC_REG_RSP3_RSP3_MASK_RX_INFO_OK                                     = MAC_REG_RSP3,
          MAC_REG_RSP3_RSP3_MASK_RX_INFO_OK_SHIFT                               = 25,
          MAC_REG_RSP3_RSP3_MASK_RX_INFO_OK_MASK                                = 0x02000000,
          MAC_REG_RSP3_RSP3_MASK_RX_INFO_NDP                                    = MAC_REG_RSP3,
          MAC_REG_RSP3_RSP3_MASK_RX_INFO_NDP_SHIFT                              = 24,
          MAC_REG_RSP3_RSP3_MASK_RX_INFO_NDP_MASK                               = 0x01000000,
          MAC_REG_RSP3_RSP3_MASK_RX_NDP_PSPOLL                                  = MAC_REG_RSP3,
          MAC_REG_RSP3_RSP3_MASK_RX_NDP_PSPOLL_SHIFT                            = 23,
          MAC_REG_RSP3_RSP3_MASK_RX_NDP_PSPOLL_MASK                             = 0x00800000,
          MAC_REG_RSP3_RSP3_MASK_RX_PV0_TYPE                                    = MAC_REG_RSP3,
          MAC_REG_RSP3_RSP3_MASK_RX_PV0_TYPE_SHIFT                              = 21,
          MAC_REG_RSP3_RSP3_MASK_RX_PV0_TYPE_MASK                               = 0x00600000,
          MAC_REG_RSP3_RSP3_MASK_RX_PV0_SUBTYPE                                 = MAC_REG_RSP3,
          MAC_REG_RSP3_RSP3_MASK_RX_PV0_SUBTYPE_SHIFT                           = 17,
          MAC_REG_RSP3_RSP3_MASK_RX_PV0_SUBTYPE_MASK                            = 0x001e0000,
          MAC_REG_RSP3_RSP3_MASK_RX_PV                                          = MAC_REG_RSP3,
          MAC_REG_RSP3_RSP3_MASK_RX_PV_SHIFT                                    = 16,
          MAC_REG_RSP3_RSP3_MASK_RX_PV_MASK                                     = 0x00010000,
          MAC_REG_RSP3_RSP3_MASK_GROUP_ADDRESS                                  = MAC_REG_RSP3,
          MAC_REG_RSP3_RSP3_MASK_GROUP_ADDRESS_SHIFT                            = 15,
          MAC_REG_RSP3_RSP3_MASK_GROUP_ADDRESS_MASK                             = 0x00008000,
          MAC_REG_RSP3_RSP3_MASK_OPERATION                                      = MAC_REG_RSP3,
          MAC_REG_RSP3_RSP3_MASK_OPERATION_SHIFT                                = 14,
          MAC_REG_RSP3_RSP3_MASK_OPERATION_MASK                                 = 0x00004000,
          MAC_REG_RSP3_RSP3_MASK_RX_INFO_AGG                                    = MAC_REG_RSP3,
          MAC_REG_RSP3_RSP3_MASK_RX_INFO_AGG_SHIFT                              = 13,
          MAC_REG_RSP3_RSP3_MASK_RX_INFO_AGG_MASK                               = 0x00002000,
          MAC_REG_RSP3_RSP3_RX_INFO_OK                                          = MAC_REG_RSP3,
          MAC_REG_RSP3_RSP3_RX_INFO_OK_SHIFT                                    = 12,
          MAC_REG_RSP3_RSP3_RX_INFO_OK_MASK                                     = 0x00001000,
          MAC_REG_RSP3_RSP3_RX_INFO_NDP                                         = MAC_REG_RSP3,
          MAC_REG_RSP3_RSP3_RX_INFO_NDP_SHIFT                                   = 11,
          MAC_REG_RSP3_RSP3_RX_INFO_NDP_MASK                                    = 0x00000800,
          MAC_REG_RSP3_RSP3_RX_NDP_PSPOLL                                       = MAC_REG_RSP3,
          MAC_REG_RSP3_RSP3_RX_NDP_PSPOLL_SHIFT                                 = 10,
          MAC_REG_RSP3_RSP3_RX_NDP_PSPOLL_MASK                                  = 0x00000400,
          MAC_REG_RSP3_RSP3_RX_PV0_TYPE                                         = MAC_REG_RSP3,
          MAC_REG_RSP3_RSP3_RX_PV0_TYPE_SHIFT                                   = 8,
          MAC_REG_RSP3_RSP3_RX_PV0_TYPE_MASK                                    = 0x00000300,
          MAC_REG_RSP3_RSP3_RX_PV0_SUBTYPE                                      = MAC_REG_RSP3,
          MAC_REG_RSP3_RSP3_RX_PV0_SUBTYPE_SHIFT                                = 4,
          MAC_REG_RSP3_RSP3_RX_PV0_SUBTYPE_MASK                                 = 0x000000f0,
          MAC_REG_RSP3_RSP3_RX_PV                                               = MAC_REG_RSP3,
          MAC_REG_RSP3_RSP3_RX_PV_SHIFT                                         = 3,
          MAC_REG_RSP3_RSP3_RX_PV_MASK                                          = 0x00000008,
          MAC_REG_RSP3_RSP3_GROUP_ADDRESS                                       = MAC_REG_RSP3,
          MAC_REG_RSP3_RSP3_GROUP_ADDRESS_SHIFT                                 = 2,
          MAC_REG_RSP3_RSP3_GROUP_ADDRESS_MASK                                  = 0x00000004,
          MAC_REG_RSP3_RSP3_OPERATION                                           = MAC_REG_RSP3,
          MAC_REG_RSP3_RSP3_OPERATION_SHIFT                                     = 1,
          MAC_REG_RSP3_RSP3_OPERATION_MASK                                      = 0x00000002,
          MAC_REG_RSP3_RSP3_RX_INFO_AGG                                         = MAC_REG_RSP3,
          MAC_REG_RSP3_RSP3_RX_INFO_AGG_SHIFT                                   = 0,
          MAC_REG_RSP3_RSP3_RX_INFO_AGG_MASK                                    = 0x00000001,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RSP4                                                                = 0x400800d4,
//-------------------------------------------------------------------------------------------------------------------------------,
          MAC_REG_RSP4_RSP4_VALID                                               = MAC_REG_RSP4,
          MAC_REG_RSP4_RSP4_VALID_SHIFT                                         = 31,
          MAC_REG_RSP4_RSP4_VALID_MASK                                          = 0x80000000,
          MAC_REG_RSP4_RSP4_CASE                                                = MAC_REG_RSP4,
          MAC_REG_RSP4_RSP4_CASE_SHIFT                                          = 26,
          MAC_REG_RSP4_RSP4_CASE_MASK                                           = 0x7c000000,
          MAC_REG_RSP4_RSP4_MASK_RX_INFO_OK                                     = MAC_REG_RSP4,
          MAC_REG_RSP4_RSP4_MASK_RX_INFO_OK_SHIFT                               = 25,
          MAC_REG_RSP4_RSP4_MASK_RX_INFO_OK_MASK                                = 0x02000000,
          MAC_REG_RSP4_RSP4_MASK_RX_INFO_NDP                                    = MAC_REG_RSP4,
          MAC_REG_RSP4_RSP4_MASK_RX_INFO_NDP_SHIFT                              = 24,
          MAC_REG_RSP4_RSP4_MASK_RX_INFO_NDP_MASK                               = 0x01000000,
          MAC_REG_RSP4_RSP4_MASK_RX_NDP_PSPOLL                                  = MAC_REG_RSP4,
          MAC_REG_RSP4_RSP4_MASK_RX_NDP_PSPOLL_SHIFT                            = 23,
          MAC_REG_RSP4_RSP4_MASK_RX_NDP_PSPOLL_MASK                             = 0x00800000,
          MAC_REG_RSP4_RSP4_MASK_RX_PV0_TYPE                                    = MAC_REG_RSP4,
          MAC_REG_RSP4_RSP4_MASK_RX_PV0_TYPE_SHIFT                              = 21,
          MAC_REG_RSP4_RSP4_MASK_RX_PV0_TYPE_MASK                               = 0x00600000,
          MAC_REG_RSP4_RSP4_MASK_RX_PV0_SUBTYPE                                 = MAC_REG_RSP4,
          MAC_REG_RSP4_RSP4_MASK_RX_PV0_SUBTYPE_SHIFT                           = 17,
          MAC_REG_RSP4_RSP4_MASK_RX_PV0_SUBTYPE_MASK                            = 0x001e0000,
          MAC_REG_RSP4_RSP4_MASK_RX_PV                                          = MAC_REG_RSP4,
          MAC_REG_RSP4_RSP4_MASK_RX_PV_SHIFT                                    = 16,
          MAC_REG_RSP4_RSP4_MASK_RX_PV_MASK                                     = 0x00010000,
          MAC_REG_RSP4_RSP4_MASK_GROUP_ADDRESS                                  = MAC_REG_RSP4,
          MAC_REG_RSP4_RSP4_MASK_GROUP_ADDRESS_SHIFT                            = 15,
          MAC_REG_RSP4_RSP4_MASK_GROUP_ADDRESS_MASK                             = 0x00008000,
          MAC_REG_RSP4_RSP4_MASK_OPERATION                                      = MAC_REG_RSP4,
          MAC_REG_RSP4_RSP4_MASK_OPERATION_SHIFT                                = 14,
          MAC_REG_RSP4_RSP4_MASK_OPERATION_MASK                                 = 0x00004000,
          MAC_REG_RSP4_RSP4_MASK_RX_INFO_AGG                                    = MAC_REG_RSP4,
          MAC_REG_RSP4_RSP4_MASK_RX_INFO_AGG_SHIFT                              = 13,
          MAC_REG_RSP4_RSP4_MASK_RX_INFO_AGG_MASK                               = 0x00002000,
          MAC_REG_RSP4_RSP4_RX_INFO_OK                                          = MAC_REG_RSP4,
          MAC_REG_RSP4_RSP4_RX_INFO_OK_SHIFT                                    = 12,
          MAC_REG_RSP4_RSP4_RX_INFO_OK_MASK                                     = 0x00001000,
          MAC_REG_RSP4_RSP4_RX_INFO_NDP                                         = MAC_REG_RSP4,
          MAC_REG_RSP4_RSP4_RX_INFO_NDP_SHIFT                                   = 11,
          MAC_REG_RSP4_RSP4_RX_INFO_NDP_MASK                                    = 0x00000800,
          MAC_REG_RSP4_RSP4_RX_NDP_PSPOLL                                       = MAC_REG_RSP4,
          MAC_REG_RSP4_RSP4_RX_NDP_PSPOLL_SHIFT                                 = 10,
          MAC_REG_RSP4_RSP4_RX_NDP_PSPOLL_MASK                                  = 0x00000400,
          MAC_REG_RSP4_RSP4_RX_PV0_TYPE                                         = MAC_REG_RSP4,
          MAC_REG_RSP4_RSP4_RX_PV0_TYPE_SHIFT                                   = 8,
          MAC_REG_RSP4_RSP4_RX_PV0_TYPE_MASK                                    = 0x00000300,
          MAC_REG_RSP4_RSP4_RX_PV0_SUBTYPE                                      = MAC_REG_RSP4,
          MAC_REG_RSP4_RSP4_RX_PV0_SUBTYPE_SHIFT                                = 4,
          MAC_REG_RSP4_RSP4_RX_PV0_SUBTYPE_MASK                                 = 0x000000f0,
          MAC_REG_RSP4_RSP4_RX_PV                                               = MAC_REG_RSP4,
          MAC_REG_RSP4_RSP4_RX_PV_SHIFT                                         = 3,
          MAC_REG_RSP4_RSP4_RX_PV_MASK                                          = 0x00000008,
          MAC_REG_RSP4_RSP4_GROUP_ADDRESS                                       = MAC_REG_RSP4,
          MAC_REG_RSP4_RSP4_GROUP_ADDRESS_SHIFT                                 = 2,
          MAC_REG_RSP4_RSP4_GROUP_ADDRESS_MASK                                  = 0x00000004,
          MAC_REG_RSP4_RSP4_OPERATION                                           = MAC_REG_RSP4,
          MAC_REG_RSP4_RSP4_OPERATION_SHIFT                                     = 1,
          MAC_REG_RSP4_RSP4_OPERATION_MASK                                      = 0x00000002,
          MAC_REG_RSP4_RSP4_RX_INFO_AGG                                         = MAC_REG_RSP4,
          MAC_REG_RSP4_RSP4_RX_INFO_AGG_SHIFT                                   = 0,
          MAC_REG_RSP4_RSP4_RX_INFO_AGG_MASK                                    = 0x00000001,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RSP5                                                                = 0x400800d8,
//-------------------------------------------------------------------------------------------------------------------------------,
          MAC_REG_RSP5_RSP5_VALID                                               = MAC_REG_RSP5,
          MAC_REG_RSP5_RSP5_VALID_SHIFT                                         = 31,
          MAC_REG_RSP5_RSP5_VALID_MASK                                          = 0x80000000,
          MAC_REG_RSP5_RSP5_CASE                                                = MAC_REG_RSP5,
          MAC_REG_RSP5_RSP5_CASE_SHIFT                                          = 26,
          MAC_REG_RSP5_RSP5_CASE_MASK                                           = 0x7c000000,
          MAC_REG_RSP5_RSP5_MASK_RX_INFO_OK                                     = MAC_REG_RSP5,
          MAC_REG_RSP5_RSP5_MASK_RX_INFO_OK_SHIFT                               = 25,
          MAC_REG_RSP5_RSP5_MASK_RX_INFO_OK_MASK                                = 0x02000000,
          MAC_REG_RSP5_RSP5_MASK_RX_INFO_NDP                                    = MAC_REG_RSP5,
          MAC_REG_RSP5_RSP5_MASK_RX_INFO_NDP_SHIFT                              = 24,
          MAC_REG_RSP5_RSP5_MASK_RX_INFO_NDP_MASK                               = 0x01000000,
          MAC_REG_RSP5_RSP5_MASK_RX_NDP_PSPOLL                                  = MAC_REG_RSP5,
          MAC_REG_RSP5_RSP5_MASK_RX_NDP_PSPOLL_SHIFT                            = 23,
          MAC_REG_RSP5_RSP5_MASK_RX_NDP_PSPOLL_MASK                             = 0x00800000,
          MAC_REG_RSP5_RSP5_MASK_RX_PV0_TYPE                                    = MAC_REG_RSP5,
          MAC_REG_RSP5_RSP5_MASK_RX_PV0_TYPE_SHIFT                              = 21,
          MAC_REG_RSP5_RSP5_MASK_RX_PV0_TYPE_MASK                               = 0x00600000,
          MAC_REG_RSP5_RSP5_MASK_RX_PV0_SUBTYPE                                 = MAC_REG_RSP5,
          MAC_REG_RSP5_RSP5_MASK_RX_PV0_SUBTYPE_SHIFT                           = 17,
          MAC_REG_RSP5_RSP5_MASK_RX_PV0_SUBTYPE_MASK                            = 0x001e0000,
          MAC_REG_RSP5_RSP5_MASK_RX_PV                                          = MAC_REG_RSP5,
          MAC_REG_RSP5_RSP5_MASK_RX_PV_SHIFT                                    = 16,
          MAC_REG_RSP5_RSP5_MASK_RX_PV_MASK                                     = 0x00010000,
          MAC_REG_RSP5_RSP5_MASK_GROUP_ADDRESS                                  = MAC_REG_RSP5,
          MAC_REG_RSP5_RSP5_MASK_GROUP_ADDRESS_SHIFT                            = 15,
          MAC_REG_RSP5_RSP5_MASK_GROUP_ADDRESS_MASK                             = 0x00008000,
          MAC_REG_RSP5_RSP5_MASK_OPERATION                                      = MAC_REG_RSP5,
          MAC_REG_RSP5_RSP5_MASK_OPERATION_SHIFT                                = 14,
          MAC_REG_RSP5_RSP5_MASK_OPERATION_MASK                                 = 0x00004000,
          MAC_REG_RSP5_RSP5_MASK_RX_INFO_AGG                                    = MAC_REG_RSP5,
          MAC_REG_RSP5_RSP5_MASK_RX_INFO_AGG_SHIFT                              = 13,
          MAC_REG_RSP5_RSP5_MASK_RX_INFO_AGG_MASK                               = 0x00002000,
          MAC_REG_RSP5_RSP5_RX_INFO_OK                                          = MAC_REG_RSP5,
          MAC_REG_RSP5_RSP5_RX_INFO_OK_SHIFT                                    = 12,
          MAC_REG_RSP5_RSP5_RX_INFO_OK_MASK                                     = 0x00001000,
          MAC_REG_RSP5_RSP5_RX_INFO_NDP                                         = MAC_REG_RSP5,
          MAC_REG_RSP5_RSP5_RX_INFO_NDP_SHIFT                                   = 11,
          MAC_REG_RSP5_RSP5_RX_INFO_NDP_MASK                                    = 0x00000800,
          MAC_REG_RSP5_RSP5_RX_NDP_PSPOLL                                       = MAC_REG_RSP5,
          MAC_REG_RSP5_RSP5_RX_NDP_PSPOLL_SHIFT                                 = 10,
          MAC_REG_RSP5_RSP5_RX_NDP_PSPOLL_MASK                                  = 0x00000400,
          MAC_REG_RSP5_RSP5_RX_PV0_TYPE                                         = MAC_REG_RSP5,
          MAC_REG_RSP5_RSP5_RX_PV0_TYPE_SHIFT                                   = 8,
          MAC_REG_RSP5_RSP5_RX_PV0_TYPE_MASK                                    = 0x00000300,
          MAC_REG_RSP5_RSP5_RX_PV0_SUBTYPE                                      = MAC_REG_RSP5,
          MAC_REG_RSP5_RSP5_RX_PV0_SUBTYPE_SHIFT                                = 4,
          MAC_REG_RSP5_RSP5_RX_PV0_SUBTYPE_MASK                                 = 0x000000f0,
          MAC_REG_RSP5_RSP5_RX_PV                                               = MAC_REG_RSP5,
          MAC_REG_RSP5_RSP5_RX_PV_SHIFT                                         = 3,
          MAC_REG_RSP5_RSP5_RX_PV_MASK                                          = 0x00000008,
          MAC_REG_RSP5_RSP5_GROUP_ADDRESS                                       = MAC_REG_RSP5,
          MAC_REG_RSP5_RSP5_GROUP_ADDRESS_SHIFT                                 = 2,
          MAC_REG_RSP5_RSP5_GROUP_ADDRESS_MASK                                  = 0x00000004,
          MAC_REG_RSP5_RSP5_OPERATION                                           = MAC_REG_RSP5,
          MAC_REG_RSP5_RSP5_OPERATION_SHIFT                                     = 1,
          MAC_REG_RSP5_RSP5_OPERATION_MASK                                      = 0x00000002,
          MAC_REG_RSP5_RSP5_RX_INFO_AGG                                         = MAC_REG_RSP5,
          MAC_REG_RSP5_RSP5_RX_INFO_AGG_SHIFT                                   = 0,
          MAC_REG_RSP5_RSP5_RX_INFO_AGG_MASK                                    = 0x00000001,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RSP6                                                                = 0x400800dc,
//-------------------------------------------------------------------------------------------------------------------------------,
          MAC_REG_RSP6_RSP6_VALID                                               = MAC_REG_RSP6,
          MAC_REG_RSP6_RSP6_VALID_SHIFT                                         = 31,
          MAC_REG_RSP6_RSP6_VALID_MASK                                          = 0x80000000,
          MAC_REG_RSP6_RSP6_CASE                                                = MAC_REG_RSP6,
          MAC_REG_RSP6_RSP6_CASE_SHIFT                                          = 26,
          MAC_REG_RSP6_RSP6_CASE_MASK                                           = 0x7c000000,
          MAC_REG_RSP6_RSP6_MASK_RX_INFO_OK                                     = MAC_REG_RSP6,
          MAC_REG_RSP6_RSP6_MASK_RX_INFO_OK_SHIFT                               = 25,
          MAC_REG_RSP6_RSP6_MASK_RX_INFO_OK_MASK                                = 0x02000000,
          MAC_REG_RSP6_RSP6_MASK_RX_INFO_NDP                                    = MAC_REG_RSP6,
          MAC_REG_RSP6_RSP6_MASK_RX_INFO_NDP_SHIFT                              = 24,
          MAC_REG_RSP6_RSP6_MASK_RX_INFO_NDP_MASK                               = 0x01000000,
          MAC_REG_RSP6_RSP6_MASK_RX_NDP_PSPOLL                                  = MAC_REG_RSP6,
          MAC_REG_RSP6_RSP6_MASK_RX_NDP_PSPOLL_SHIFT                            = 23,
          MAC_REG_RSP6_RSP6_MASK_RX_NDP_PSPOLL_MASK                             = 0x00800000,
          MAC_REG_RSP6_RSP6_MASK_RX_PV0_TYPE                                    = MAC_REG_RSP6,
          MAC_REG_RSP6_RSP6_MASK_RX_PV0_TYPE_SHIFT                              = 21,
          MAC_REG_RSP6_RSP6_MASK_RX_PV0_TYPE_MASK                               = 0x00600000,
          MAC_REG_RSP6_RSP6_MASK_RX_PV0_SUBTYPE                                 = MAC_REG_RSP6,
          MAC_REG_RSP6_RSP6_MASK_RX_PV0_SUBTYPE_SHIFT                           = 17,
          MAC_REG_RSP6_RSP6_MASK_RX_PV0_SUBTYPE_MASK                            = 0x001e0000,
          MAC_REG_RSP6_RSP6_MASK_RX_PV                                          = MAC_REG_RSP6,
          MAC_REG_RSP6_RSP6_MASK_RX_PV_SHIFT                                    = 16,
          MAC_REG_RSP6_RSP6_MASK_RX_PV_MASK                                     = 0x00010000,
          MAC_REG_RSP6_RSP6_MASK_GROUP_ADDRESS                                  = MAC_REG_RSP6,
          MAC_REG_RSP6_RSP6_MASK_GROUP_ADDRESS_SHIFT                            = 15,
          MAC_REG_RSP6_RSP6_MASK_GROUP_ADDRESS_MASK                             = 0x00008000,
          MAC_REG_RSP6_RSP6_MASK_OPERATION                                      = MAC_REG_RSP6,
          MAC_REG_RSP6_RSP6_MASK_OPERATION_SHIFT                                = 14,
          MAC_REG_RSP6_RSP6_MASK_OPERATION_MASK                                 = 0x00004000,
          MAC_REG_RSP6_RSP6_MASK_RX_INFO_AGG                                    = MAC_REG_RSP6,
          MAC_REG_RSP6_RSP6_MASK_RX_INFO_AGG_SHIFT                              = 13,
          MAC_REG_RSP6_RSP6_MASK_RX_INFO_AGG_MASK                               = 0x00002000,
          MAC_REG_RSP6_RSP6_RX_INFO_OK                                          = MAC_REG_RSP6,
          MAC_REG_RSP6_RSP6_RX_INFO_OK_SHIFT                                    = 12,
          MAC_REG_RSP6_RSP6_RX_INFO_OK_MASK                                     = 0x00001000,
          MAC_REG_RSP6_RSP6_RX_INFO_NDP                                         = MAC_REG_RSP6,
          MAC_REG_RSP6_RSP6_RX_INFO_NDP_SHIFT                                   = 11,
          MAC_REG_RSP6_RSP6_RX_INFO_NDP_MASK                                    = 0x00000800,
          MAC_REG_RSP6_RSP6_RX_NDP_PSPOLL                                       = MAC_REG_RSP6,
          MAC_REG_RSP6_RSP6_RX_NDP_PSPOLL_SHIFT                                 = 10,
          MAC_REG_RSP6_RSP6_RX_NDP_PSPOLL_MASK                                  = 0x00000400,
          MAC_REG_RSP6_RSP6_RX_PV0_TYPE                                         = MAC_REG_RSP6,
          MAC_REG_RSP6_RSP6_RX_PV0_TYPE_SHIFT                                   = 8,
          MAC_REG_RSP6_RSP6_RX_PV0_TYPE_MASK                                    = 0x00000300,
          MAC_REG_RSP6_RSP6_RX_PV0_SUBTYPE                                      = MAC_REG_RSP6,
          MAC_REG_RSP6_RSP6_RX_PV0_SUBTYPE_SHIFT                                = 4,
          MAC_REG_RSP6_RSP6_RX_PV0_SUBTYPE_MASK                                 = 0x000000f0,
          MAC_REG_RSP6_RSP6_RX_PV                                               = MAC_REG_RSP6,
          MAC_REG_RSP6_RSP6_RX_PV_SHIFT                                         = 3,
          MAC_REG_RSP6_RSP6_RX_PV_MASK                                          = 0x00000008,
          MAC_REG_RSP6_RSP6_GROUP_ADDRESS                                       = MAC_REG_RSP6,
          MAC_REG_RSP6_RSP6_GROUP_ADDRESS_SHIFT                                 = 2,
          MAC_REG_RSP6_RSP6_GROUP_ADDRESS_MASK                                  = 0x00000004,
          MAC_REG_RSP6_RSP6_OPERATION                                           = MAC_REG_RSP6,
          MAC_REG_RSP6_RSP6_OPERATION_SHIFT                                     = 1,
          MAC_REG_RSP6_RSP6_OPERATION_MASK                                      = 0x00000002,
          MAC_REG_RSP6_RSP6_RX_INFO_AGG                                         = MAC_REG_RSP6,
          MAC_REG_RSP6_RSP6_RX_INFO_AGG_SHIFT                                   = 0,
          MAC_REG_RSP6_RSP6_RX_INFO_AGG_MASK                                    = 0x00000001,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RSP7                                                                = 0x400800e0,
//-------------------------------------------------------------------------------------------------------------------------------,
          MAC_REG_RSP7_RSP7_VALID                                               = MAC_REG_RSP7,
          MAC_REG_RSP7_RSP7_VALID_SHIFT                                         = 31,
          MAC_REG_RSP7_RSP7_VALID_MASK                                          = 0x80000000,
          MAC_REG_RSP7_RSP7_CASE                                                = MAC_REG_RSP7,
          MAC_REG_RSP7_RSP7_CASE_SHIFT                                          = 26,
          MAC_REG_RSP7_RSP7_CASE_MASK                                           = 0x7c000000,
          MAC_REG_RSP7_RSP7_MASK_RX_INFO_OK                                     = MAC_REG_RSP7,
          MAC_REG_RSP7_RSP7_MASK_RX_INFO_OK_SHIFT                               = 25,
          MAC_REG_RSP7_RSP7_MASK_RX_INFO_OK_MASK                                = 0x02000000,
          MAC_REG_RSP7_RSP7_MASK_RX_INFO_NDP                                    = MAC_REG_RSP7,
          MAC_REG_RSP7_RSP7_MASK_RX_INFO_NDP_SHIFT                              = 24,
          MAC_REG_RSP7_RSP7_MASK_RX_INFO_NDP_MASK                               = 0x01000000,
          MAC_REG_RSP7_RSP7_MASK_RX_NDP_PSPOLL                                  = MAC_REG_RSP7,
          MAC_REG_RSP7_RSP7_MASK_RX_NDP_PSPOLL_SHIFT                            = 23,
          MAC_REG_RSP7_RSP7_MASK_RX_NDP_PSPOLL_MASK                             = 0x00800000,
          MAC_REG_RSP7_RSP7_MASK_RX_PV0_TYPE                                    = MAC_REG_RSP7,
          MAC_REG_RSP7_RSP7_MASK_RX_PV0_TYPE_SHIFT                              = 21,
          MAC_REG_RSP7_RSP7_MASK_RX_PV0_TYPE_MASK                               = 0x00600000,
          MAC_REG_RSP7_RSP7_MASK_RX_PV0_SUBTYPE                                 = MAC_REG_RSP7,
          MAC_REG_RSP7_RSP7_MASK_RX_PV0_SUBTYPE_SHIFT                           = 17,
          MAC_REG_RSP7_RSP7_MASK_RX_PV0_SUBTYPE_MASK                            = 0x001e0000,
          MAC_REG_RSP7_RSP7_MASK_RX_PV                                          = MAC_REG_RSP7,
          MAC_REG_RSP7_RSP7_MASK_RX_PV_SHIFT                                    = 16,
          MAC_REG_RSP7_RSP7_MASK_RX_PV_MASK                                     = 0x00010000,
          MAC_REG_RSP7_RSP7_MASK_GROUP_ADDRESS                                  = MAC_REG_RSP7,
          MAC_REG_RSP7_RSP7_MASK_GROUP_ADDRESS_SHIFT                            = 15,
          MAC_REG_RSP7_RSP7_MASK_GROUP_ADDRESS_MASK                             = 0x00008000,
          MAC_REG_RSP7_RSP7_MASK_OPERATION                                      = MAC_REG_RSP7,
          MAC_REG_RSP7_RSP7_MASK_OPERATION_SHIFT                                = 14,
          MAC_REG_RSP7_RSP7_MASK_OPERATION_MASK                                 = 0x00004000,
          MAC_REG_RSP7_RSP7_MASK_RX_INFO_AGG                                    = MAC_REG_RSP7,
          MAC_REG_RSP7_RSP7_MASK_RX_INFO_AGG_SHIFT                              = 13,
          MAC_REG_RSP7_RSP7_MASK_RX_INFO_AGG_MASK                               = 0x00002000,
          MAC_REG_RSP7_RSP7_RX_INFO_OK                                          = MAC_REG_RSP7,
          MAC_REG_RSP7_RSP7_RX_INFO_OK_SHIFT                                    = 12,
          MAC_REG_RSP7_RSP7_RX_INFO_OK_MASK                                     = 0x00001000,
          MAC_REG_RSP7_RSP7_RX_INFO_NDP                                         = MAC_REG_RSP7,
          MAC_REG_RSP7_RSP7_RX_INFO_NDP_SHIFT                                   = 11,
          MAC_REG_RSP7_RSP7_RX_INFO_NDP_MASK                                    = 0x00000800,
          MAC_REG_RSP7_RSP7_RX_NDP_PSPOLL                                       = MAC_REG_RSP7,
          MAC_REG_RSP7_RSP7_RX_NDP_PSPOLL_SHIFT                                 = 10,
          MAC_REG_RSP7_RSP7_RX_NDP_PSPOLL_MASK                                  = 0x00000400,
          MAC_REG_RSP7_RSP7_RX_PV0_TYPE                                         = MAC_REG_RSP7,
          MAC_REG_RSP7_RSP7_RX_PV0_TYPE_SHIFT                                   = 8,
          MAC_REG_RSP7_RSP7_RX_PV0_TYPE_MASK                                    = 0x00000300,
          MAC_REG_RSP7_RSP7_RX_PV0_SUBTYPE                                      = MAC_REG_RSP7,
          MAC_REG_RSP7_RSP7_RX_PV0_SUBTYPE_SHIFT                                = 4,
          MAC_REG_RSP7_RSP7_RX_PV0_SUBTYPE_MASK                                 = 0x000000f0,
          MAC_REG_RSP7_RSP7_RX_PV                                               = MAC_REG_RSP7,
          MAC_REG_RSP7_RSP7_RX_PV_SHIFT                                         = 3,
          MAC_REG_RSP7_RSP7_RX_PV_MASK                                          = 0x00000008,
          MAC_REG_RSP7_RSP7_GROUP_ADDRESS                                       = MAC_REG_RSP7,
          MAC_REG_RSP7_RSP7_GROUP_ADDRESS_SHIFT                                 = 2,
          MAC_REG_RSP7_RSP7_GROUP_ADDRESS_MASK                                  = 0x00000004,
          MAC_REG_RSP7_RSP7_OPERATION                                           = MAC_REG_RSP7,
          MAC_REG_RSP7_RSP7_OPERATION_SHIFT                                     = 1,
          MAC_REG_RSP7_RSP7_OPERATION_MASK                                      = 0x00000002,
          MAC_REG_RSP7_RSP7_RX_INFO_AGG                                         = MAC_REG_RSP7,
          MAC_REG_RSP7_RSP7_RX_INFO_AGG_SHIFT                                   = 0,
          MAC_REG_RSP7_RSP7_RX_INFO_AGG_MASK                                    = 0x00000001,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RSP8                                                                = 0x400800e4,
//-------------------------------------------------------------------------------------------------------------------------------,
          MAC_REG_RSP8_RSP8_VALID                                               = MAC_REG_RSP8,
          MAC_REG_RSP8_RSP8_VALID_SHIFT                                         = 31,
          MAC_REG_RSP8_RSP8_VALID_MASK                                          = 0x80000000,
          MAC_REG_RSP8_RSP8_CASE                                                = MAC_REG_RSP8,
          MAC_REG_RSP8_RSP8_CASE_SHIFT                                          = 26,
          MAC_REG_RSP8_RSP8_CASE_MASK                                           = 0x7c000000,
          MAC_REG_RSP8_RSP8_MASK_RX_INFO_OK                                     = MAC_REG_RSP8,
          MAC_REG_RSP8_RSP8_MASK_RX_INFO_OK_SHIFT                               = 25,
          MAC_REG_RSP8_RSP8_MASK_RX_INFO_OK_MASK                                = 0x02000000,
          MAC_REG_RSP8_RSP8_MASK_RX_INFO_NDP                                    = MAC_REG_RSP8,
          MAC_REG_RSP8_RSP8_MASK_RX_INFO_NDP_SHIFT                              = 24,
          MAC_REG_RSP8_RSP8_MASK_RX_INFO_NDP_MASK                               = 0x01000000,
          MAC_REG_RSP8_RSP8_MASK_RX_NDP_PSPOLL                                  = MAC_REG_RSP8,
          MAC_REG_RSP8_RSP8_MASK_RX_NDP_PSPOLL_SHIFT                            = 23,
          MAC_REG_RSP8_RSP8_MASK_RX_NDP_PSPOLL_MASK                             = 0x00800000,
          MAC_REG_RSP8_RSP8_MASK_RX_PV0_TYPE                                    = MAC_REG_RSP8,
          MAC_REG_RSP8_RSP8_MASK_RX_PV0_TYPE_SHIFT                              = 21,
          MAC_REG_RSP8_RSP8_MASK_RX_PV0_TYPE_MASK                               = 0x00600000,
          MAC_REG_RSP8_RSP8_MASK_RX_PV0_SUBTYPE                                 = MAC_REG_RSP8,
          MAC_REG_RSP8_RSP8_MASK_RX_PV0_SUBTYPE_SHIFT                           = 17,
          MAC_REG_RSP8_RSP8_MASK_RX_PV0_SUBTYPE_MASK                            = 0x001e0000,
          MAC_REG_RSP8_RSP8_MASK_RX_PV                                          = MAC_REG_RSP8,
          MAC_REG_RSP8_RSP8_MASK_RX_PV_SHIFT                                    = 16,
          MAC_REG_RSP8_RSP8_MASK_RX_PV_MASK                                     = 0x00010000,
          MAC_REG_RSP8_RSP8_MASK_GROUP_ADDRESS                                  = MAC_REG_RSP8,
          MAC_REG_RSP8_RSP8_MASK_GROUP_ADDRESS_SHIFT                            = 15,
          MAC_REG_RSP8_RSP8_MASK_GROUP_ADDRESS_MASK                             = 0x00008000,
          MAC_REG_RSP8_RSP8_MASK_OPERATION                                      = MAC_REG_RSP8,
          MAC_REG_RSP8_RSP8_MASK_OPERATION_SHIFT                                = 14,
          MAC_REG_RSP8_RSP8_MASK_OPERATION_MASK                                 = 0x00004000,
          MAC_REG_RSP8_RSP8_MASK_RX_INFO_AGG                                    = MAC_REG_RSP8,
          MAC_REG_RSP8_RSP8_MASK_RX_INFO_AGG_SHIFT                              = 13,
          MAC_REG_RSP8_RSP8_MASK_RX_INFO_AGG_MASK                               = 0x00002000,
          MAC_REG_RSP8_RSP8_RX_INFO_OK                                          = MAC_REG_RSP8,
          MAC_REG_RSP8_RSP8_RX_INFO_OK_SHIFT                                    = 12,
          MAC_REG_RSP8_RSP8_RX_INFO_OK_MASK                                     = 0x00001000,
          MAC_REG_RSP8_RSP8_RX_INFO_NDP                                         = MAC_REG_RSP8,
          MAC_REG_RSP8_RSP8_RX_INFO_NDP_SHIFT                                   = 11,
          MAC_REG_RSP8_RSP8_RX_INFO_NDP_MASK                                    = 0x00000800,
          MAC_REG_RSP8_RSP8_RX_NDP_PSPOLL                                       = MAC_REG_RSP8,
          MAC_REG_RSP8_RSP8_RX_NDP_PSPOLL_SHIFT                                 = 10,
          MAC_REG_RSP8_RSP8_RX_NDP_PSPOLL_MASK                                  = 0x00000400,
          MAC_REG_RSP8_RSP8_RX_PV0_TYPE                                         = MAC_REG_RSP8,
          MAC_REG_RSP8_RSP8_RX_PV0_TYPE_SHIFT                                   = 8,
          MAC_REG_RSP8_RSP8_RX_PV0_TYPE_MASK                                    = 0x00000300,
          MAC_REG_RSP8_RSP8_RX_PV0_SUBTYPE                                      = MAC_REG_RSP8,
          MAC_REG_RSP8_RSP8_RX_PV0_SUBTYPE_SHIFT                                = 4,
          MAC_REG_RSP8_RSP8_RX_PV0_SUBTYPE_MASK                                 = 0x000000f0,
          MAC_REG_RSP8_RSP8_RX_PV                                               = MAC_REG_RSP8,
          MAC_REG_RSP8_RSP8_RX_PV_SHIFT                                         = 3,
          MAC_REG_RSP8_RSP8_RX_PV_MASK                                          = 0x00000008,
          MAC_REG_RSP8_RSP8_GROUP_ADDRESS                                       = MAC_REG_RSP8,
          MAC_REG_RSP8_RSP8_GROUP_ADDRESS_SHIFT                                 = 2,
          MAC_REG_RSP8_RSP8_GROUP_ADDRESS_MASK                                  = 0x00000004,
          MAC_REG_RSP8_RSP8_OPERATION                                           = MAC_REG_RSP8,
          MAC_REG_RSP8_RSP8_OPERATION_SHIFT                                     = 1,
          MAC_REG_RSP8_RSP8_OPERATION_MASK                                      = 0x00000002,
          MAC_REG_RSP8_RSP8_RX_INFO_AGG                                         = MAC_REG_RSP8,
          MAC_REG_RSP8_RSP8_RX_INFO_AGG_SHIFT                                   = 0,
          MAC_REG_RSP8_RSP8_RX_INFO_AGG_MASK                                    = 0x00000001,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RSP9                                                                = 0x400800e8,
//-------------------------------------------------------------------------------------------------------------------------------,
          MAC_REG_RSP9_RSP9_VALID                                               = MAC_REG_RSP9,
          MAC_REG_RSP9_RSP9_VALID_SHIFT                                         = 31,
          MAC_REG_RSP9_RSP9_VALID_MASK                                          = 0x80000000,
          MAC_REG_RSP9_RSP9_CASE                                                = MAC_REG_RSP9,
          MAC_REG_RSP9_RSP9_CASE_SHIFT                                          = 26,
          MAC_REG_RSP9_RSP9_CASE_MASK                                           = 0x7c000000,
          MAC_REG_RSP9_RSP9_MASK_RX_INFO_OK                                     = MAC_REG_RSP9,
          MAC_REG_RSP9_RSP9_MASK_RX_INFO_OK_SHIFT                               = 25,
          MAC_REG_RSP9_RSP9_MASK_RX_INFO_OK_MASK                                = 0x02000000,
          MAC_REG_RSP9_RSP9_MASK_RX_INFO_NDP                                    = MAC_REG_RSP9,
          MAC_REG_RSP9_RSP9_MASK_RX_INFO_NDP_SHIFT                              = 24,
          MAC_REG_RSP9_RSP9_MASK_RX_INFO_NDP_MASK                               = 0x01000000,
          MAC_REG_RSP9_RSP9_MASK_RX_NDP_PSPOLL                                  = MAC_REG_RSP9,
          MAC_REG_RSP9_RSP9_MASK_RX_NDP_PSPOLL_SHIFT                            = 23,
          MAC_REG_RSP9_RSP9_MASK_RX_NDP_PSPOLL_MASK                             = 0x00800000,
          MAC_REG_RSP9_RSP9_MASK_RX_PV0_TYPE                                    = MAC_REG_RSP9,
          MAC_REG_RSP9_RSP9_MASK_RX_PV0_TYPE_SHIFT                              = 21,
          MAC_REG_RSP9_RSP9_MASK_RX_PV0_TYPE_MASK                               = 0x00600000,
          MAC_REG_RSP9_RSP9_MASK_RX_PV0_SUBTYPE                                 = MAC_REG_RSP9,
          MAC_REG_RSP9_RSP9_MASK_RX_PV0_SUBTYPE_SHIFT                           = 17,
          MAC_REG_RSP9_RSP9_MASK_RX_PV0_SUBTYPE_MASK                            = 0x001e0000,
          MAC_REG_RSP9_RSP9_MASK_RX_PV                                          = MAC_REG_RSP9,
          MAC_REG_RSP9_RSP9_MASK_RX_PV_SHIFT                                    = 16,
          MAC_REG_RSP9_RSP9_MASK_RX_PV_MASK                                     = 0x00010000,
          MAC_REG_RSP9_RSP9_MASK_GROUP_ADDRESS                                  = MAC_REG_RSP9,
          MAC_REG_RSP9_RSP9_MASK_GROUP_ADDRESS_SHIFT                            = 15,
          MAC_REG_RSP9_RSP9_MASK_GROUP_ADDRESS_MASK                             = 0x00008000,
          MAC_REG_RSP9_RSP9_MASK_OPERATION                                      = MAC_REG_RSP9,
          MAC_REG_RSP9_RSP9_MASK_OPERATION_SHIFT                                = 14,
          MAC_REG_RSP9_RSP9_MASK_OPERATION_MASK                                 = 0x00004000,
          MAC_REG_RSP9_RSP9_MASK_RX_INFO_AGG                                    = MAC_REG_RSP9,
          MAC_REG_RSP9_RSP9_MASK_RX_INFO_AGG_SHIFT                              = 13,
          MAC_REG_RSP9_RSP9_MASK_RX_INFO_AGG_MASK                               = 0x00002000,
          MAC_REG_RSP9_RSP9_RX_INFO_OK                                          = MAC_REG_RSP9,
          MAC_REG_RSP9_RSP9_RX_INFO_OK_SHIFT                                    = 12,
          MAC_REG_RSP9_RSP9_RX_INFO_OK_MASK                                     = 0x00001000,
          MAC_REG_RSP9_RSP9_RX_INFO_NDP                                         = MAC_REG_RSP9,
          MAC_REG_RSP9_RSP9_RX_INFO_NDP_SHIFT                                   = 11,
          MAC_REG_RSP9_RSP9_RX_INFO_NDP_MASK                                    = 0x00000800,
          MAC_REG_RSP9_RSP9_RX_NDP_PSPOLL                                       = MAC_REG_RSP9,
          MAC_REG_RSP9_RSP9_RX_NDP_PSPOLL_SHIFT                                 = 10,
          MAC_REG_RSP9_RSP9_RX_NDP_PSPOLL_MASK                                  = 0x00000400,
          MAC_REG_RSP9_RSP9_RX_PV0_TYPE                                         = MAC_REG_RSP9,
          MAC_REG_RSP9_RSP9_RX_PV0_TYPE_SHIFT                                   = 8,
          MAC_REG_RSP9_RSP9_RX_PV0_TYPE_MASK                                    = 0x00000300,
          MAC_REG_RSP9_RSP9_RX_PV0_SUBTYPE                                      = MAC_REG_RSP9,
          MAC_REG_RSP9_RSP9_RX_PV0_SUBTYPE_SHIFT                                = 4,
          MAC_REG_RSP9_RSP9_RX_PV0_SUBTYPE_MASK                                 = 0x000000f0,
          MAC_REG_RSP9_RSP9_RX_PV                                               = MAC_REG_RSP9,
          MAC_REG_RSP9_RSP9_RX_PV_SHIFT                                         = 3,
          MAC_REG_RSP9_RSP9_RX_PV_MASK                                          = 0x00000008,
          MAC_REG_RSP9_RSP9_GROUP_ADDRESS                                       = MAC_REG_RSP9,
          MAC_REG_RSP9_RSP9_GROUP_ADDRESS_SHIFT                                 = 2,
          MAC_REG_RSP9_RSP9_GROUP_ADDRESS_MASK                                  = 0x00000004,
          MAC_REG_RSP9_RSP9_OPERATION                                           = MAC_REG_RSP9,
          MAC_REG_RSP9_RSP9_OPERATION_SHIFT                                     = 1,
          MAC_REG_RSP9_RSP9_OPERATION_MASK                                      = 0x00000002,
          MAC_REG_RSP9_RSP9_RX_INFO_AGG                                         = MAC_REG_RSP9,
          MAC_REG_RSP9_RSP9_RX_INFO_AGG_SHIFT                                   = 0,
          MAC_REG_RSP9_RSP9_RX_INFO_AGG_MASK                                    = 0x00000001,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RSP10                                                               = 0x400800ec,
//-------------------------------------------------------------------------------------------------------------------------------,
          MAC_REG_RSP10_RSP10_VALID                                             = MAC_REG_RSP10,
          MAC_REG_RSP10_RSP10_VALID_SHIFT                                       = 31,
          MAC_REG_RSP10_RSP10_VALID_MASK                                        = 0x80000000,
          MAC_REG_RSP10_RSP10_CASE                                              = MAC_REG_RSP10,
          MAC_REG_RSP10_RSP10_CASE_SHIFT                                        = 26,
          MAC_REG_RSP10_RSP10_CASE_MASK                                         = 0x7c000000,
          MAC_REG_RSP10_RSP10_MASK_RX_INFO_OK                                   = MAC_REG_RSP10,
          MAC_REG_RSP10_RSP10_MASK_RX_INFO_OK_SHIFT                             = 25,
          MAC_REG_RSP10_RSP10_MASK_RX_INFO_OK_MASK                              = 0x02000000,
          MAC_REG_RSP10_RSP10_MASK_RX_INFO_NDP                                  = MAC_REG_RSP10,
          MAC_REG_RSP10_RSP10_MASK_RX_INFO_NDP_SHIFT                            = 24,
          MAC_REG_RSP10_RSP10_MASK_RX_INFO_NDP_MASK                             = 0x01000000,
          MAC_REG_RSP10_RSP10_MASK_RX_NDP_PSPOLL                                = MAC_REG_RSP10,
          MAC_REG_RSP10_RSP10_MASK_RX_NDP_PSPOLL_SHIFT                          = 23,
          MAC_REG_RSP10_RSP10_MASK_RX_NDP_PSPOLL_MASK                           = 0x00800000,
          MAC_REG_RSP10_RSP10_MASK_RX_PV0_TYPE                                  = MAC_REG_RSP10,
          MAC_REG_RSP10_RSP10_MASK_RX_PV0_TYPE_SHIFT                            = 21,
          MAC_REG_RSP10_RSP10_MASK_RX_PV0_TYPE_MASK                             = 0x00600000,
          MAC_REG_RSP10_RSP10_MASK_RX_PV0_SUBTYPE                               = MAC_REG_RSP10,
          MAC_REG_RSP10_RSP10_MASK_RX_PV0_SUBTYPE_SHIFT                         = 17,
          MAC_REG_RSP10_RSP10_MASK_RX_PV0_SUBTYPE_MASK                          = 0x001e0000,
          MAC_REG_RSP10_RSP10_MASK_RX_PV                                        = MAC_REG_RSP10,
          MAC_REG_RSP10_RSP10_MASK_RX_PV_SHIFT                                  = 16,
          MAC_REG_RSP10_RSP10_MASK_RX_PV_MASK                                   = 0x00010000,
          MAC_REG_RSP10_RSP10_MASK_GROUP_ADDRESS                                = MAC_REG_RSP10,
          MAC_REG_RSP10_RSP10_MASK_GROUP_ADDRESS_SHIFT                          = 15,
          MAC_REG_RSP10_RSP10_MASK_GROUP_ADDRESS_MASK                           = 0x00008000,
          MAC_REG_RSP10_RSP10_MASK_OPERATION                                    = MAC_REG_RSP10,
          MAC_REG_RSP10_RSP10_MASK_OPERATION_SHIFT                              = 14,
          MAC_REG_RSP10_RSP10_MASK_OPERATION_MASK                               = 0x00004000,
          MAC_REG_RSP10_RSP10_MASK_RX_INFO_AGG                                  = MAC_REG_RSP10,
          MAC_REG_RSP10_RSP10_MASK_RX_INFO_AGG_SHIFT                            = 13,
          MAC_REG_RSP10_RSP10_MASK_RX_INFO_AGG_MASK                             = 0x00002000,
          MAC_REG_RSP10_RSP10_RX_INFO_OK                                        = MAC_REG_RSP10,
          MAC_REG_RSP10_RSP10_RX_INFO_OK_SHIFT                                  = 12,
          MAC_REG_RSP10_RSP10_RX_INFO_OK_MASK                                   = 0x00001000,
          MAC_REG_RSP10_RSP10_RX_INFO_NDP                                       = MAC_REG_RSP10,
          MAC_REG_RSP10_RSP10_RX_INFO_NDP_SHIFT                                 = 11,
          MAC_REG_RSP10_RSP10_RX_INFO_NDP_MASK                                  = 0x00000800,
          MAC_REG_RSP10_RSP10_RX_NDP_PSPOLL                                     = MAC_REG_RSP10,
          MAC_REG_RSP10_RSP10_RX_NDP_PSPOLL_SHIFT                               = 10,
          MAC_REG_RSP10_RSP10_RX_NDP_PSPOLL_MASK                                = 0x00000400,
          MAC_REG_RSP10_RSP10_RX_PV0_TYPE                                       = MAC_REG_RSP10,
          MAC_REG_RSP10_RSP10_RX_PV0_TYPE_SHIFT                                 = 8,
          MAC_REG_RSP10_RSP10_RX_PV0_TYPE_MASK                                  = 0x00000300,
          MAC_REG_RSP10_RSP10_RX_PV0_SUBTYPE                                    = MAC_REG_RSP10,
          MAC_REG_RSP10_RSP10_RX_PV0_SUBTYPE_SHIFT                              = 4,
          MAC_REG_RSP10_RSP10_RX_PV0_SUBTYPE_MASK                               = 0x000000f0,
          MAC_REG_RSP10_RSP10_RX_PV                                             = MAC_REG_RSP10,
          MAC_REG_RSP10_RSP10_RX_PV_SHIFT                                       = 3,
          MAC_REG_RSP10_RSP10_RX_PV_MASK                                        = 0x00000008,
          MAC_REG_RSP10_RSP10_GROUP_ADDRESS                                     = MAC_REG_RSP10,
          MAC_REG_RSP10_RSP10_GROUP_ADDRESS_SHIFT                               = 2,
          MAC_REG_RSP10_RSP10_GROUP_ADDRESS_MASK                                = 0x00000004,
          MAC_REG_RSP10_RSP10_OPERATION                                         = MAC_REG_RSP10,
          MAC_REG_RSP10_RSP10_OPERATION_SHIFT                                   = 1,
          MAC_REG_RSP10_RSP10_OPERATION_MASK                                    = 0x00000002,
          MAC_REG_RSP10_RSP10_RX_INFO_AGG                                       = MAC_REG_RSP10,
          MAC_REG_RSP10_RSP10_RX_INFO_AGG_SHIFT                                 = 0,
          MAC_REG_RSP10_RSP10_RX_INFO_AGG_MASK                                  = 0x00000001,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RSP11                                                               = 0x400800f0,
//-------------------------------------------------------------------------------------------------------------------------------,
          MAC_REG_RSP11_RSP11_VALID                                             = MAC_REG_RSP11,
          MAC_REG_RSP11_RSP11_VALID_SHIFT                                       = 31,
          MAC_REG_RSP11_RSP11_VALID_MASK                                        = 0x80000000,
          MAC_REG_RSP11_RSP11_CASE                                              = MAC_REG_RSP11,
          MAC_REG_RSP11_RSP11_CASE_SHIFT                                        = 26,
          MAC_REG_RSP11_RSP11_CASE_MASK                                         = 0x7c000000,
          MAC_REG_RSP11_RSP11_MASK_RX_INFO_OK                                   = MAC_REG_RSP11,
          MAC_REG_RSP11_RSP11_MASK_RX_INFO_OK_SHIFT                             = 25,
          MAC_REG_RSP11_RSP11_MASK_RX_INFO_OK_MASK                              = 0x02000000,
          MAC_REG_RSP11_RSP11_MASK_RX_INFO_NDP                                  = MAC_REG_RSP11,
          MAC_REG_RSP11_RSP11_MASK_RX_INFO_NDP_SHIFT                            = 24,
          MAC_REG_RSP11_RSP11_MASK_RX_INFO_NDP_MASK                             = 0x01000000,
          MAC_REG_RSP11_RSP11_MASK_RX_NDP_PSPOLL                                = MAC_REG_RSP11,
          MAC_REG_RSP11_RSP11_MASK_RX_NDP_PSPOLL_SHIFT                          = 23,
          MAC_REG_RSP11_RSP11_MASK_RX_NDP_PSPOLL_MASK                           = 0x00800000,
          MAC_REG_RSP11_RSP11_MASK_RX_PV0_TYPE                                  = MAC_REG_RSP11,
          MAC_REG_RSP11_RSP11_MASK_RX_PV0_TYPE_SHIFT                            = 21,
          MAC_REG_RSP11_RSP11_MASK_RX_PV0_TYPE_MASK                             = 0x00600000,
          MAC_REG_RSP11_RSP11_MASK_RX_PV0_SUBTYPE                               = MAC_REG_RSP11,
          MAC_REG_RSP11_RSP11_MASK_RX_PV0_SUBTYPE_SHIFT                         = 17,
          MAC_REG_RSP11_RSP11_MASK_RX_PV0_SUBTYPE_MASK                          = 0x001e0000,
          MAC_REG_RSP11_RSP11_MASK_RX_PV                                        = MAC_REG_RSP11,
          MAC_REG_RSP11_RSP11_MASK_RX_PV_SHIFT                                  = 16,
          MAC_REG_RSP11_RSP11_MASK_RX_PV_MASK                                   = 0x00010000,
          MAC_REG_RSP11_RSP11_MASK_GROUP_ADDRESS                                = MAC_REG_RSP11,
          MAC_REG_RSP11_RSP11_MASK_GROUP_ADDRESS_SHIFT                          = 15,
          MAC_REG_RSP11_RSP11_MASK_GROUP_ADDRESS_MASK                           = 0x00008000,
          MAC_REG_RSP11_RSP11_MASK_OPERATION                                    = MAC_REG_RSP11,
          MAC_REG_RSP11_RSP11_MASK_OPERATION_SHIFT                              = 14,
          MAC_REG_RSP11_RSP11_MASK_OPERATION_MASK                               = 0x00004000,
          MAC_REG_RSP11_RSP11_MASK_RX_INFO_AGG                                  = MAC_REG_RSP11,
          MAC_REG_RSP11_RSP11_MASK_RX_INFO_AGG_SHIFT                            = 13,
          MAC_REG_RSP11_RSP11_MASK_RX_INFO_AGG_MASK                             = 0x00002000,
          MAC_REG_RSP11_RSP11_RX_INFO_OK                                        = MAC_REG_RSP11,
          MAC_REG_RSP11_RSP11_RX_INFO_OK_SHIFT                                  = 12,
          MAC_REG_RSP11_RSP11_RX_INFO_OK_MASK                                   = 0x00001000,
          MAC_REG_RSP11_RSP11_RX_INFO_NDP                                       = MAC_REG_RSP11,
          MAC_REG_RSP11_RSP11_RX_INFO_NDP_SHIFT                                 = 11,
          MAC_REG_RSP11_RSP11_RX_INFO_NDP_MASK                                  = 0x00000800,
          MAC_REG_RSP11_RSP11_RX_NDP_PSPOLL                                     = MAC_REG_RSP11,
          MAC_REG_RSP11_RSP11_RX_NDP_PSPOLL_SHIFT                               = 10,
          MAC_REG_RSP11_RSP11_RX_NDP_PSPOLL_MASK                                = 0x00000400,
          MAC_REG_RSP11_RSP11_RX_PV0_TYPE                                       = MAC_REG_RSP11,
          MAC_REG_RSP11_RSP11_RX_PV0_TYPE_SHIFT                                 = 8,
          MAC_REG_RSP11_RSP11_RX_PV0_TYPE_MASK                                  = 0x00000300,
          MAC_REG_RSP11_RSP11_RX_PV0_SUBTYPE                                    = MAC_REG_RSP11,
          MAC_REG_RSP11_RSP11_RX_PV0_SUBTYPE_SHIFT                              = 4,
          MAC_REG_RSP11_RSP11_RX_PV0_SUBTYPE_MASK                               = 0x000000f0,
          MAC_REG_RSP11_RSP11_RX_PV                                             = MAC_REG_RSP11,
          MAC_REG_RSP11_RSP11_RX_PV_SHIFT                                       = 3,
          MAC_REG_RSP11_RSP11_RX_PV_MASK                                        = 0x00000008,
          MAC_REG_RSP11_RSP11_GROUP_ADDRESS                                     = MAC_REG_RSP11,
          MAC_REG_RSP11_RSP11_GROUP_ADDRESS_SHIFT                               = 2,
          MAC_REG_RSP11_RSP11_GROUP_ADDRESS_MASK                                = 0x00000004,
          MAC_REG_RSP11_RSP11_OPERATION                                         = MAC_REG_RSP11,
          MAC_REG_RSP11_RSP11_OPERATION_SHIFT                                   = 1,
          MAC_REG_RSP11_RSP11_OPERATION_MASK                                    = 0x00000002,
          MAC_REG_RSP11_RSP11_RX_INFO_AGG                                       = MAC_REG_RSP11,
          MAC_REG_RSP11_RSP11_RX_INFO_AGG_SHIFT                                 = 0,
          MAC_REG_RSP11_RSP11_RX_INFO_AGG_MASK                                  = 0x00000001,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RSP12                                                               = 0x400800f4,
//-------------------------------------------------------------------------------------------------------------------------------,
          MAC_REG_RSP12_RSP12_VALID                                             = MAC_REG_RSP12,
          MAC_REG_RSP12_RSP12_VALID_SHIFT                                       = 31,
          MAC_REG_RSP12_RSP12_VALID_MASK                                        = 0x80000000,
          MAC_REG_RSP12_RSP12_CASE                                              = MAC_REG_RSP12,
          MAC_REG_RSP12_RSP12_CASE_SHIFT                                        = 26,
          MAC_REG_RSP12_RSP12_CASE_MASK                                         = 0x7c000000,
          MAC_REG_RSP12_RSP12_MASK_RX_INFO_OK                                   = MAC_REG_RSP12,
          MAC_REG_RSP12_RSP12_MASK_RX_INFO_OK_SHIFT                             = 25,
          MAC_REG_RSP12_RSP12_MASK_RX_INFO_OK_MASK                              = 0x02000000,
          MAC_REG_RSP12_RSP12_MASK_RX_INFO_NDP                                  = MAC_REG_RSP12,
          MAC_REG_RSP12_RSP12_MASK_RX_INFO_NDP_SHIFT                            = 24,
          MAC_REG_RSP12_RSP12_MASK_RX_INFO_NDP_MASK                             = 0x01000000,
          MAC_REG_RSP12_RSP12_MASK_RX_NDP_PSPOLL                                = MAC_REG_RSP12,
          MAC_REG_RSP12_RSP12_MASK_RX_NDP_PSPOLL_SHIFT                          = 23,
          MAC_REG_RSP12_RSP12_MASK_RX_NDP_PSPOLL_MASK                           = 0x00800000,
          MAC_REG_RSP12_RSP12_MASK_RX_PV0_TYPE                                  = MAC_REG_RSP12,
          MAC_REG_RSP12_RSP12_MASK_RX_PV0_TYPE_SHIFT                            = 21,
          MAC_REG_RSP12_RSP12_MASK_RX_PV0_TYPE_MASK                             = 0x00600000,
          MAC_REG_RSP12_RSP12_MASK_RX_PV0_SUBTYPE                               = MAC_REG_RSP12,
          MAC_REG_RSP12_RSP12_MASK_RX_PV0_SUBTYPE_SHIFT                         = 17,
          MAC_REG_RSP12_RSP12_MASK_RX_PV0_SUBTYPE_MASK                          = 0x001e0000,
          MAC_REG_RSP12_RSP12_MASK_RX_PV                                        = MAC_REG_RSP12,
          MAC_REG_RSP12_RSP12_MASK_RX_PV_SHIFT                                  = 16,
          MAC_REG_RSP12_RSP12_MASK_RX_PV_MASK                                   = 0x00010000,
          MAC_REG_RSP12_RSP12_MASK_GROUP_ADDRESS                                = MAC_REG_RSP12,
          MAC_REG_RSP12_RSP12_MASK_GROUP_ADDRESS_SHIFT                          = 15,
          MAC_REG_RSP12_RSP12_MASK_GROUP_ADDRESS_MASK                           = 0x00008000,
          MAC_REG_RSP12_RSP12_MASK_OPERATION                                    = MAC_REG_RSP12,
          MAC_REG_RSP12_RSP12_MASK_OPERATION_SHIFT                              = 14,
          MAC_REG_RSP12_RSP12_MASK_OPERATION_MASK                               = 0x00004000,
          MAC_REG_RSP12_RSP12_MASK_RX_INFO_AGG                                  = MAC_REG_RSP12,
          MAC_REG_RSP12_RSP12_MASK_RX_INFO_AGG_SHIFT                            = 13,
          MAC_REG_RSP12_RSP12_MASK_RX_INFO_AGG_MASK                             = 0x00002000,
          MAC_REG_RSP12_RSP12_RX_INFO_OK                                        = MAC_REG_RSP12,
          MAC_REG_RSP12_RSP12_RX_INFO_OK_SHIFT                                  = 12,
          MAC_REG_RSP12_RSP12_RX_INFO_OK_MASK                                   = 0x00001000,
          MAC_REG_RSP12_RSP12_RX_INFO_NDP                                       = MAC_REG_RSP12,
          MAC_REG_RSP12_RSP12_RX_INFO_NDP_SHIFT                                 = 11,
          MAC_REG_RSP12_RSP12_RX_INFO_NDP_MASK                                  = 0x00000800,
          MAC_REG_RSP12_RSP12_RX_NDP_PSPOLL                                     = MAC_REG_RSP12,
          MAC_REG_RSP12_RSP12_RX_NDP_PSPOLL_SHIFT                               = 10,
          MAC_REG_RSP12_RSP12_RX_NDP_PSPOLL_MASK                                = 0x00000400,
          MAC_REG_RSP12_RSP12_RX_PV0_TYPE                                       = MAC_REG_RSP12,
          MAC_REG_RSP12_RSP12_RX_PV0_TYPE_SHIFT                                 = 8,
          MAC_REG_RSP12_RSP12_RX_PV0_TYPE_MASK                                  = 0x00000300,
          MAC_REG_RSP12_RSP12_RX_PV0_SUBTYPE                                    = MAC_REG_RSP12,
          MAC_REG_RSP12_RSP12_RX_PV0_SUBTYPE_SHIFT                              = 4,
          MAC_REG_RSP12_RSP12_RX_PV0_SUBTYPE_MASK                               = 0x000000f0,
          MAC_REG_RSP12_RSP12_RX_PV                                             = MAC_REG_RSP12,
          MAC_REG_RSP12_RSP12_RX_PV_SHIFT                                       = 3,
          MAC_REG_RSP12_RSP12_RX_PV_MASK                                        = 0x00000008,
          MAC_REG_RSP12_RSP12_GROUP_ADDRESS                                     = MAC_REG_RSP12,
          MAC_REG_RSP12_RSP12_GROUP_ADDRESS_SHIFT                               = 2,
          MAC_REG_RSP12_RSP12_GROUP_ADDRESS_MASK                                = 0x00000004,
          MAC_REG_RSP12_RSP12_OPERATION                                         = MAC_REG_RSP12,
          MAC_REG_RSP12_RSP12_OPERATION_SHIFT                                   = 1,
          MAC_REG_RSP12_RSP12_OPERATION_MASK                                    = 0x00000002,
          MAC_REG_RSP12_RSP12_RX_INFO_AGG                                       = MAC_REG_RSP12,
          MAC_REG_RSP12_RSP12_RX_INFO_AGG_SHIFT                                 = 0,
          MAC_REG_RSP12_RSP12_RX_INFO_AGG_MASK                                  = 0x00000001,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RSP13                                                               = 0x400800f8,
//-------------------------------------------------------------------------------------------------------------------------------,
          MAC_REG_RSP13_RSP13_VALID                                             = MAC_REG_RSP13,
          MAC_REG_RSP13_RSP13_VALID_SHIFT                                       = 31,
          MAC_REG_RSP13_RSP13_VALID_MASK                                        = 0x80000000,
          MAC_REG_RSP13_RSP13_CASE                                              = MAC_REG_RSP13,
          MAC_REG_RSP13_RSP13_CASE_SHIFT                                        = 26,
          MAC_REG_RSP13_RSP13_CASE_MASK                                         = 0x7c000000,
          MAC_REG_RSP13_RSP13_MASK_RX_INFO_OK                                   = MAC_REG_RSP13,
          MAC_REG_RSP13_RSP13_MASK_RX_INFO_OK_SHIFT                             = 25,
          MAC_REG_RSP13_RSP13_MASK_RX_INFO_OK_MASK                              = 0x02000000,
          MAC_REG_RSP13_RSP13_MASK_RX_INFO_NDP                                  = MAC_REG_RSP13,
          MAC_REG_RSP13_RSP13_MASK_RX_INFO_NDP_SHIFT                            = 24,
          MAC_REG_RSP13_RSP13_MASK_RX_INFO_NDP_MASK                             = 0x01000000,
          MAC_REG_RSP13_RSP13_MASK_RX_NDP_PSPOLL                                = MAC_REG_RSP13,
          MAC_REG_RSP13_RSP13_MASK_RX_NDP_PSPOLL_SHIFT                          = 23,
          MAC_REG_RSP13_RSP13_MASK_RX_NDP_PSPOLL_MASK                           = 0x00800000,
          MAC_REG_RSP13_RSP13_MASK_RX_PV0_TYPE                                  = MAC_REG_RSP13,
          MAC_REG_RSP13_RSP13_MASK_RX_PV0_TYPE_SHIFT                            = 21,
          MAC_REG_RSP13_RSP13_MASK_RX_PV0_TYPE_MASK                             = 0x00600000,
          MAC_REG_RSP13_RSP13_MASK_RX_PV0_SUBTYPE                               = MAC_REG_RSP13,
          MAC_REG_RSP13_RSP13_MASK_RX_PV0_SUBTYPE_SHIFT                         = 17,
          MAC_REG_RSP13_RSP13_MASK_RX_PV0_SUBTYPE_MASK                          = 0x001e0000,
          MAC_REG_RSP13_RSP13_MASK_RX_PV                                        = MAC_REG_RSP13,
          MAC_REG_RSP13_RSP13_MASK_RX_PV_SHIFT                                  = 16,
          MAC_REG_RSP13_RSP13_MASK_RX_PV_MASK                                   = 0x00010000,
          MAC_REG_RSP13_RSP13_MASK_GROUP_ADDRESS                                = MAC_REG_RSP13,
          MAC_REG_RSP13_RSP13_MASK_GROUP_ADDRESS_SHIFT                          = 15,
          MAC_REG_RSP13_RSP13_MASK_GROUP_ADDRESS_MASK                           = 0x00008000,
          MAC_REG_RSP13_RSP13_MASK_OPERATION                                    = MAC_REG_RSP13,
          MAC_REG_RSP13_RSP13_MASK_OPERATION_SHIFT                              = 14,
          MAC_REG_RSP13_RSP13_MASK_OPERATION_MASK                               = 0x00004000,
          MAC_REG_RSP13_RSP13_MASK_RX_INFO_AGG                                  = MAC_REG_RSP13,
          MAC_REG_RSP13_RSP13_MASK_RX_INFO_AGG_SHIFT                            = 13,
          MAC_REG_RSP13_RSP13_MASK_RX_INFO_AGG_MASK                             = 0x00002000,
          MAC_REG_RSP13_RSP13_RX_INFO_OK                                        = MAC_REG_RSP13,
          MAC_REG_RSP13_RSP13_RX_INFO_OK_SHIFT                                  = 12,
          MAC_REG_RSP13_RSP13_RX_INFO_OK_MASK                                   = 0x00001000,
          MAC_REG_RSP13_RSP13_RX_INFO_NDP                                       = MAC_REG_RSP13,
          MAC_REG_RSP13_RSP13_RX_INFO_NDP_SHIFT                                 = 11,
          MAC_REG_RSP13_RSP13_RX_INFO_NDP_MASK                                  = 0x00000800,
          MAC_REG_RSP13_RSP13_RX_NDP_PSPOLL                                     = MAC_REG_RSP13,
          MAC_REG_RSP13_RSP13_RX_NDP_PSPOLL_SHIFT                               = 10,
          MAC_REG_RSP13_RSP13_RX_NDP_PSPOLL_MASK                                = 0x00000400,
          MAC_REG_RSP13_RSP13_RX_PV0_TYPE                                       = MAC_REG_RSP13,
          MAC_REG_RSP13_RSP13_RX_PV0_TYPE_SHIFT                                 = 8,
          MAC_REG_RSP13_RSP13_RX_PV0_TYPE_MASK                                  = 0x00000300,
          MAC_REG_RSP13_RSP13_RX_PV0_SUBTYPE                                    = MAC_REG_RSP13,
          MAC_REG_RSP13_RSP13_RX_PV0_SUBTYPE_SHIFT                              = 4,
          MAC_REG_RSP13_RSP13_RX_PV0_SUBTYPE_MASK                               = 0x000000f0,
          MAC_REG_RSP13_RSP13_RX_PV                                             = MAC_REG_RSP13,
          MAC_REG_RSP13_RSP13_RX_PV_SHIFT                                       = 3,
          MAC_REG_RSP13_RSP13_RX_PV_MASK                                        = 0x00000008,
          MAC_REG_RSP13_RSP13_GROUP_ADDRESS                                     = MAC_REG_RSP13,
          MAC_REG_RSP13_RSP13_GROUP_ADDRESS_SHIFT                               = 2,
          MAC_REG_RSP13_RSP13_GROUP_ADDRESS_MASK                                = 0x00000004,
          MAC_REG_RSP13_RSP13_OPERATION                                         = MAC_REG_RSP13,
          MAC_REG_RSP13_RSP13_OPERATION_SHIFT                                   = 1,
          MAC_REG_RSP13_RSP13_OPERATION_MASK                                    = 0x00000002,
          MAC_REG_RSP13_RSP13_RX_INFO_AGG                                       = MAC_REG_RSP13,
          MAC_REG_RSP13_RSP13_RX_INFO_AGG_SHIFT                                 = 0,
          MAC_REG_RSP13_RSP13_RX_INFO_AGG_MASK                                  = 0x00000001,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RSP14                                                               = 0x400800fc,
//-------------------------------------------------------------------------------------------------------------------------------,
          MAC_REG_RSP14_RSP14_VALID                                             = MAC_REG_RSP14,
          MAC_REG_RSP14_RSP14_VALID_SHIFT                                       = 31,
          MAC_REG_RSP14_RSP14_VALID_MASK                                        = 0x80000000,
          MAC_REG_RSP14_RSP14_CASE                                              = MAC_REG_RSP14,
          MAC_REG_RSP14_RSP14_CASE_SHIFT                                        = 26,
          MAC_REG_RSP14_RSP14_CASE_MASK                                         = 0x7c000000,
          MAC_REG_RSP14_RSP14_MASK_RX_INFO_OK                                   = MAC_REG_RSP14,
          MAC_REG_RSP14_RSP14_MASK_RX_INFO_OK_SHIFT                             = 25,
          MAC_REG_RSP14_RSP14_MASK_RX_INFO_OK_MASK                              = 0x02000000,
          MAC_REG_RSP14_RSP14_MASK_RX_INFO_NDP                                  = MAC_REG_RSP14,
          MAC_REG_RSP14_RSP14_MASK_RX_INFO_NDP_SHIFT                            = 24,
          MAC_REG_RSP14_RSP14_MASK_RX_INFO_NDP_MASK                             = 0x01000000,
          MAC_REG_RSP14_RSP14_MASK_RX_NDP_PSPOLL                                = MAC_REG_RSP14,
          MAC_REG_RSP14_RSP14_MASK_RX_NDP_PSPOLL_SHIFT                          = 23,
          MAC_REG_RSP14_RSP14_MASK_RX_NDP_PSPOLL_MASK                           = 0x00800000,
          MAC_REG_RSP14_RSP14_MASK_RX_PV0_TYPE                                  = MAC_REG_RSP14,
          MAC_REG_RSP14_RSP14_MASK_RX_PV0_TYPE_SHIFT                            = 21,
          MAC_REG_RSP14_RSP14_MASK_RX_PV0_TYPE_MASK                             = 0x00600000,
          MAC_REG_RSP14_RSP14_MASK_RX_PV0_SUBTYPE                               = MAC_REG_RSP14,
          MAC_REG_RSP14_RSP14_MASK_RX_PV0_SUBTYPE_SHIFT                         = 17,
          MAC_REG_RSP14_RSP14_MASK_RX_PV0_SUBTYPE_MASK                          = 0x001e0000,
          MAC_REG_RSP14_RSP14_MASK_RX_PV                                        = MAC_REG_RSP14,
          MAC_REG_RSP14_RSP14_MASK_RX_PV_SHIFT                                  = 16,
          MAC_REG_RSP14_RSP14_MASK_RX_PV_MASK                                   = 0x00010000,
          MAC_REG_RSP14_RSP14_MASK_GROUP_ADDRESS                                = MAC_REG_RSP14,
          MAC_REG_RSP14_RSP14_MASK_GROUP_ADDRESS_SHIFT                          = 15,
          MAC_REG_RSP14_RSP14_MASK_GROUP_ADDRESS_MASK                           = 0x00008000,
          MAC_REG_RSP14_RSP14_MASK_OPERATION                                    = MAC_REG_RSP14,
          MAC_REG_RSP14_RSP14_MASK_OPERATION_SHIFT                              = 14,
          MAC_REG_RSP14_RSP14_MASK_OPERATION_MASK                               = 0x00004000,
          MAC_REG_RSP14_RSP14_MASK_RX_INFO_AGG                                  = MAC_REG_RSP14,
          MAC_REG_RSP14_RSP14_MASK_RX_INFO_AGG_SHIFT                            = 13,
          MAC_REG_RSP14_RSP14_MASK_RX_INFO_AGG_MASK                             = 0x00002000,
          MAC_REG_RSP14_RSP14_RX_INFO_OK                                        = MAC_REG_RSP14,
          MAC_REG_RSP14_RSP14_RX_INFO_OK_SHIFT                                  = 12,
          MAC_REG_RSP14_RSP14_RX_INFO_OK_MASK                                   = 0x00001000,
          MAC_REG_RSP14_RSP14_RX_INFO_NDP                                       = MAC_REG_RSP14,
          MAC_REG_RSP14_RSP14_RX_INFO_NDP_SHIFT                                 = 11,
          MAC_REG_RSP14_RSP14_RX_INFO_NDP_MASK                                  = 0x00000800,
          MAC_REG_RSP14_RSP14_RX_NDP_PSPOLL                                     = MAC_REG_RSP14,
          MAC_REG_RSP14_RSP14_RX_NDP_PSPOLL_SHIFT                               = 10,
          MAC_REG_RSP14_RSP14_RX_NDP_PSPOLL_MASK                                = 0x00000400,
          MAC_REG_RSP14_RSP14_RX_PV0_TYPE                                       = MAC_REG_RSP14,
          MAC_REG_RSP14_RSP14_RX_PV0_TYPE_SHIFT                                 = 8,
          MAC_REG_RSP14_RSP14_RX_PV0_TYPE_MASK                                  = 0x00000300,
          MAC_REG_RSP14_RSP14_RX_PV0_SUBTYPE                                    = MAC_REG_RSP14,
          MAC_REG_RSP14_RSP14_RX_PV0_SUBTYPE_SHIFT                              = 4,
          MAC_REG_RSP14_RSP14_RX_PV0_SUBTYPE_MASK                               = 0x000000f0,
          MAC_REG_RSP14_RSP14_RX_PV                                             = MAC_REG_RSP14,
          MAC_REG_RSP14_RSP14_RX_PV_SHIFT                                       = 3,
          MAC_REG_RSP14_RSP14_RX_PV_MASK                                        = 0x00000008,
          MAC_REG_RSP14_RSP14_GROUP_ADDRESS                                     = MAC_REG_RSP14,
          MAC_REG_RSP14_RSP14_GROUP_ADDRESS_SHIFT                               = 2,
          MAC_REG_RSP14_RSP14_GROUP_ADDRESS_MASK                                = 0x00000004,
          MAC_REG_RSP14_RSP14_OPERATION                                         = MAC_REG_RSP14,
          MAC_REG_RSP14_RSP14_OPERATION_SHIFT                                   = 1,
          MAC_REG_RSP14_RSP14_OPERATION_MASK                                    = 0x00000002,
          MAC_REG_RSP14_RSP14_RX_INFO_AGG                                       = MAC_REG_RSP14,
          MAC_REG_RSP14_RSP14_RX_INFO_AGG_SHIFT                                 = 0,
          MAC_REG_RSP14_RSP14_RX_INFO_AGG_MASK                                  = 0x00000001,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RSP15                                                               = 0x40080100,
//-------------------------------------------------------------------------------------------------------------------------------,
          MAC_REG_RSP15_RSP15_VALID                                             = MAC_REG_RSP15,
          MAC_REG_RSP15_RSP15_VALID_SHIFT                                       = 31,
          MAC_REG_RSP15_RSP15_VALID_MASK                                        = 0x80000000,
          MAC_REG_RSP15_RSP15_CASE                                              = MAC_REG_RSP15,
          MAC_REG_RSP15_RSP15_CASE_SHIFT                                        = 26,
          MAC_REG_RSP15_RSP15_CASE_MASK                                         = 0x7c000000,
          MAC_REG_RSP15_RSP15_MASK_RX_INFO_OK                                   = MAC_REG_RSP15,
          MAC_REG_RSP15_RSP15_MASK_RX_INFO_OK_SHIFT                             = 25,
          MAC_REG_RSP15_RSP15_MASK_RX_INFO_OK_MASK                              = 0x02000000,
          MAC_REG_RSP15_RSP15_MASK_RX_INFO_NDP                                  = MAC_REG_RSP15,
          MAC_REG_RSP15_RSP15_MASK_RX_INFO_NDP_SHIFT                            = 24,
          MAC_REG_RSP15_RSP15_MASK_RX_INFO_NDP_MASK                             = 0x01000000,
          MAC_REG_RSP15_RSP15_MASK_RX_NDP_PSPOLL                                = MAC_REG_RSP15,
          MAC_REG_RSP15_RSP15_MASK_RX_NDP_PSPOLL_SHIFT                          = 23,
          MAC_REG_RSP15_RSP15_MASK_RX_NDP_PSPOLL_MASK                           = 0x00800000,
          MAC_REG_RSP15_RSP15_MASK_RX_PV0_TYPE                                  = MAC_REG_RSP15,
          MAC_REG_RSP15_RSP15_MASK_RX_PV0_TYPE_SHIFT                            = 21,
          MAC_REG_RSP15_RSP15_MASK_RX_PV0_TYPE_MASK                             = 0x00600000,
          MAC_REG_RSP15_RSP15_MASK_RX_PV0_SUBTYPE                               = MAC_REG_RSP15,
          MAC_REG_RSP15_RSP15_MASK_RX_PV0_SUBTYPE_SHIFT                         = 17,
          MAC_REG_RSP15_RSP15_MASK_RX_PV0_SUBTYPE_MASK                          = 0x001e0000,
          MAC_REG_RSP15_RSP15_MASK_RX_PV                                        = MAC_REG_RSP15,
          MAC_REG_RSP15_RSP15_MASK_RX_PV_SHIFT                                  = 16,
          MAC_REG_RSP15_RSP15_MASK_RX_PV_MASK                                   = 0x00010000,
          MAC_REG_RSP15_RSP15_MASK_GROUP_ADDRESS                                = MAC_REG_RSP15,
          MAC_REG_RSP15_RSP15_MASK_GROUP_ADDRESS_SHIFT                          = 15,
          MAC_REG_RSP15_RSP15_MASK_GROUP_ADDRESS_MASK                           = 0x00008000,
          MAC_REG_RSP15_RSP15_MASK_OPERATION                                    = MAC_REG_RSP15,
          MAC_REG_RSP15_RSP15_MASK_OPERATION_SHIFT                              = 14,
          MAC_REG_RSP15_RSP15_MASK_OPERATION_MASK                               = 0x00004000,
          MAC_REG_RSP15_RSP15_MASK_RX_INFO_AGG                                  = MAC_REG_RSP15,
          MAC_REG_RSP15_RSP15_MASK_RX_INFO_AGG_SHIFT                            = 13,
          MAC_REG_RSP15_RSP15_MASK_RX_INFO_AGG_MASK                             = 0x00002000,
          MAC_REG_RSP15_RSP15_RX_INFO_OK                                        = MAC_REG_RSP15,
          MAC_REG_RSP15_RSP15_RX_INFO_OK_SHIFT                                  = 12,
          MAC_REG_RSP15_RSP15_RX_INFO_OK_MASK                                   = 0x00001000,
          MAC_REG_RSP15_RSP15_RX_INFO_NDP                                       = MAC_REG_RSP15,
          MAC_REG_RSP15_RSP15_RX_INFO_NDP_SHIFT                                 = 11,
          MAC_REG_RSP15_RSP15_RX_INFO_NDP_MASK                                  = 0x00000800,
          MAC_REG_RSP15_RSP15_RX_NDP_PSPOLL                                     = MAC_REG_RSP15,
          MAC_REG_RSP15_RSP15_RX_NDP_PSPOLL_SHIFT                               = 10,
          MAC_REG_RSP15_RSP15_RX_NDP_PSPOLL_MASK                                = 0x00000400,
          MAC_REG_RSP15_RSP15_RX_PV0_TYPE                                       = MAC_REG_RSP15,
          MAC_REG_RSP15_RSP15_RX_PV0_TYPE_SHIFT                                 = 8,
          MAC_REG_RSP15_RSP15_RX_PV0_TYPE_MASK                                  = 0x00000300,
          MAC_REG_RSP15_RSP15_RX_PV0_SUBTYPE                                    = MAC_REG_RSP15,
          MAC_REG_RSP15_RSP15_RX_PV0_SUBTYPE_SHIFT                              = 4,
          MAC_REG_RSP15_RSP15_RX_PV0_SUBTYPE_MASK                               = 0x000000f0,
          MAC_REG_RSP15_RSP15_RX_PV                                             = MAC_REG_RSP15,
          MAC_REG_RSP15_RSP15_RX_PV_SHIFT                                       = 3,
          MAC_REG_RSP15_RSP15_RX_PV_MASK                                        = 0x00000008,
          MAC_REG_RSP15_RSP15_GROUP_ADDRESS                                     = MAC_REG_RSP15,
          MAC_REG_RSP15_RSP15_GROUP_ADDRESS_SHIFT                               = 2,
          MAC_REG_RSP15_RSP15_GROUP_ADDRESS_MASK                                = 0x00000004,
          MAC_REG_RSP15_RSP15_OPERATION                                         = MAC_REG_RSP15,
          MAC_REG_RSP15_RSP15_OPERATION_SHIFT                                   = 1,
          MAC_REG_RSP15_RSP15_OPERATION_MASK                                    = 0x00000002,
          MAC_REG_RSP15_RSP15_RX_INFO_AGG                                       = MAC_REG_RSP15,
          MAC_REG_RSP15_RSP15_RX_INFO_AGG_SHIFT                                 = 0,
          MAC_REG_RSP15_RSP15_RX_INFO_AGG_MASK                                  = 0x00000001,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RSP16                                                               = 0x40080104,
//-------------------------------------------------------------------------------------------------------------------------------,
          MAC_REG_RSP16_RSP16_VALID                                             = MAC_REG_RSP16,
          MAC_REG_RSP16_RSP16_VALID_SHIFT                                       = 31,
          MAC_REG_RSP16_RSP16_VALID_MASK                                        = 0x80000000,
          MAC_REG_RSP16_RSP16_CASE                                              = MAC_REG_RSP16,
          MAC_REG_RSP16_RSP16_CASE_SHIFT                                        = 26,
          MAC_REG_RSP16_RSP16_CASE_MASK                                         = 0x7c000000,
          MAC_REG_RSP16_RSP16_MASK_RX_INFO_OK                                   = MAC_REG_RSP16,
          MAC_REG_RSP16_RSP16_MASK_RX_INFO_OK_SHIFT                             = 25,
          MAC_REG_RSP16_RSP16_MASK_RX_INFO_OK_MASK                              = 0x02000000,
          MAC_REG_RSP16_RSP16_MASK_RX_INFO_NDP                                  = MAC_REG_RSP16,
          MAC_REG_RSP16_RSP16_MASK_RX_INFO_NDP_SHIFT                            = 24,
          MAC_REG_RSP16_RSP16_MASK_RX_INFO_NDP_MASK                             = 0x01000000,
          MAC_REG_RSP16_RSP16_MASK_RX_NDP_PSPOLL                                = MAC_REG_RSP16,
          MAC_REG_RSP16_RSP16_MASK_RX_NDP_PSPOLL_SHIFT                          = 23,
          MAC_REG_RSP16_RSP16_MASK_RX_NDP_PSPOLL_MASK                           = 0x00800000,
          MAC_REG_RSP16_RSP16_MASK_RX_PV0_TYPE                                  = MAC_REG_RSP16,
          MAC_REG_RSP16_RSP16_MASK_RX_PV0_TYPE_SHIFT                            = 21,
          MAC_REG_RSP16_RSP16_MASK_RX_PV0_TYPE_MASK                             = 0x00600000,
          MAC_REG_RSP16_RSP16_MASK_RX_PV0_SUBTYPE                               = MAC_REG_RSP16,
          MAC_REG_RSP16_RSP16_MASK_RX_PV0_SUBTYPE_SHIFT                         = 17,
          MAC_REG_RSP16_RSP16_MASK_RX_PV0_SUBTYPE_MASK                          = 0x001e0000,
          MAC_REG_RSP16_RSP16_MASK_RX_PV                                        = MAC_REG_RSP16,
          MAC_REG_RSP16_RSP16_MASK_RX_PV_SHIFT                                  = 16,
          MAC_REG_RSP16_RSP16_MASK_RX_PV_MASK                                   = 0x00010000,
          MAC_REG_RSP16_RSP16_MASK_GROUP_ADDRESS                                = MAC_REG_RSP16,
          MAC_REG_RSP16_RSP16_MASK_GROUP_ADDRESS_SHIFT                          = 15,
          MAC_REG_RSP16_RSP16_MASK_GROUP_ADDRESS_MASK                           = 0x00008000,
          MAC_REG_RSP16_RSP16_MASK_OPERATION                                    = MAC_REG_RSP16,
          MAC_REG_RSP16_RSP16_MASK_OPERATION_SHIFT                              = 14,
          MAC_REG_RSP16_RSP16_MASK_OPERATION_MASK                               = 0x00004000,
          MAC_REG_RSP16_RSP16_MASK_RX_INFO_AGG                                  = MAC_REG_RSP16,
          MAC_REG_RSP16_RSP16_MASK_RX_INFO_AGG_SHIFT                            = 13,
          MAC_REG_RSP16_RSP16_MASK_RX_INFO_AGG_MASK                             = 0x00002000,
          MAC_REG_RSP16_RSP16_RX_INFO_OK                                        = MAC_REG_RSP16,
          MAC_REG_RSP16_RSP16_RX_INFO_OK_SHIFT                                  = 12,
          MAC_REG_RSP16_RSP16_RX_INFO_OK_MASK                                   = 0x00001000,
          MAC_REG_RSP16_RSP16_RX_INFO_NDP                                       = MAC_REG_RSP16,
          MAC_REG_RSP16_RSP16_RX_INFO_NDP_SHIFT                                 = 11,
          MAC_REG_RSP16_RSP16_RX_INFO_NDP_MASK                                  = 0x00000800,
          MAC_REG_RSP16_RSP16_RX_NDP_PSPOLL                                     = MAC_REG_RSP16,
          MAC_REG_RSP16_RSP16_RX_NDP_PSPOLL_SHIFT                               = 10,
          MAC_REG_RSP16_RSP16_RX_NDP_PSPOLL_MASK                                = 0x00000400,
          MAC_REG_RSP16_RSP16_RX_PV0_TYPE                                       = MAC_REG_RSP16,
          MAC_REG_RSP16_RSP16_RX_PV0_TYPE_SHIFT                                 = 8,
          MAC_REG_RSP16_RSP16_RX_PV0_TYPE_MASK                                  = 0x00000300,
          MAC_REG_RSP16_RSP16_RX_PV0_SUBTYPE                                    = MAC_REG_RSP16,
          MAC_REG_RSP16_RSP16_RX_PV0_SUBTYPE_SHIFT                              = 4,
          MAC_REG_RSP16_RSP16_RX_PV0_SUBTYPE_MASK                               = 0x000000f0,
          MAC_REG_RSP16_RSP16_RX_PV                                             = MAC_REG_RSP16,
          MAC_REG_RSP16_RSP16_RX_PV_SHIFT                                       = 3,
          MAC_REG_RSP16_RSP16_RX_PV_MASK                                        = 0x00000008,
          MAC_REG_RSP16_RSP16_GROUP_ADDRESS                                     = MAC_REG_RSP16,
          MAC_REG_RSP16_RSP16_GROUP_ADDRESS_SHIFT                               = 2,
          MAC_REG_RSP16_RSP16_GROUP_ADDRESS_MASK                                = 0x00000004,
          MAC_REG_RSP16_RSP16_OPERATION                                         = MAC_REG_RSP16,
          MAC_REG_RSP16_RSP16_OPERATION_SHIFT                                   = 1,
          MAC_REG_RSP16_RSP16_OPERATION_MASK                                    = 0x00000002,
          MAC_REG_RSP16_RSP16_RX_INFO_AGG                                       = MAC_REG_RSP16,
          MAC_REG_RSP16_RSP16_RX_INFO_AGG_SHIFT                                 = 0,
          MAC_REG_RSP16_RSP16_RX_INFO_AGG_MASK                                  = 0x00000001,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RSP17                                                               = 0x40080108,
//-------------------------------------------------------------------------------------------------------------------------------,
          MAC_REG_RSP17_RSP17_VALID                                             = MAC_REG_RSP17,
          MAC_REG_RSP17_RSP17_VALID_SHIFT                                       = 31,
          MAC_REG_RSP17_RSP17_VALID_MASK                                        = 0x80000000,
          MAC_REG_RSP17_RSP17_CASE                                              = MAC_REG_RSP17,
          MAC_REG_RSP17_RSP17_CASE_SHIFT                                        = 26,
          MAC_REG_RSP17_RSP17_CASE_MASK                                         = 0x7c000000,
          MAC_REG_RSP17_RSP17_MASK_RX_INFO_OK                                   = MAC_REG_RSP17,
          MAC_REG_RSP17_RSP17_MASK_RX_INFO_OK_SHIFT                             = 25,
          MAC_REG_RSP17_RSP17_MASK_RX_INFO_OK_MASK                              = 0x02000000,
          MAC_REG_RSP17_RSP17_MASK_RX_INFO_NDP                                  = MAC_REG_RSP17,
          MAC_REG_RSP17_RSP17_MASK_RX_INFO_NDP_SHIFT                            = 24,
          MAC_REG_RSP17_RSP17_MASK_RX_INFO_NDP_MASK                             = 0x01000000,
          MAC_REG_RSP17_RSP17_MASK_RX_NDP_PSPOLL                                = MAC_REG_RSP17,
          MAC_REG_RSP17_RSP17_MASK_RX_NDP_PSPOLL_SHIFT                          = 23,
          MAC_REG_RSP17_RSP17_MASK_RX_NDP_PSPOLL_MASK                           = 0x00800000,
          MAC_REG_RSP17_RSP17_MASK_RX_PV0_TYPE                                  = MAC_REG_RSP17,
          MAC_REG_RSP17_RSP17_MASK_RX_PV0_TYPE_SHIFT                            = 21,
          MAC_REG_RSP17_RSP17_MASK_RX_PV0_TYPE_MASK                             = 0x00600000,
          MAC_REG_RSP17_RSP17_MASK_RX_PV0_SUBTYPE                               = MAC_REG_RSP17,
          MAC_REG_RSP17_RSP17_MASK_RX_PV0_SUBTYPE_SHIFT                         = 17,
          MAC_REG_RSP17_RSP17_MASK_RX_PV0_SUBTYPE_MASK                          = 0x001e0000,
          MAC_REG_RSP17_RSP17_MASK_RX_PV                                        = MAC_REG_RSP17,
          MAC_REG_RSP17_RSP17_MASK_RX_PV_SHIFT                                  = 16,
          MAC_REG_RSP17_RSP17_MASK_RX_PV_MASK                                   = 0x00010000,
          MAC_REG_RSP17_RSP17_MASK_GROUP_ADDRESS                                = MAC_REG_RSP17,
          MAC_REG_RSP17_RSP17_MASK_GROUP_ADDRESS_SHIFT                          = 15,
          MAC_REG_RSP17_RSP17_MASK_GROUP_ADDRESS_MASK                           = 0x00008000,
          MAC_REG_RSP17_RSP17_MASK_OPERATION                                    = MAC_REG_RSP17,
          MAC_REG_RSP17_RSP17_MASK_OPERATION_SHIFT                              = 14,
          MAC_REG_RSP17_RSP17_MASK_OPERATION_MASK                               = 0x00004000,
          MAC_REG_RSP17_RSP17_MASK_RX_INFO_AGG                                  = MAC_REG_RSP17,
          MAC_REG_RSP17_RSP17_MASK_RX_INFO_AGG_SHIFT                            = 13,
          MAC_REG_RSP17_RSP17_MASK_RX_INFO_AGG_MASK                             = 0x00002000,
          MAC_REG_RSP17_RSP17_RX_INFO_OK                                        = MAC_REG_RSP17,
          MAC_REG_RSP17_RSP17_RX_INFO_OK_SHIFT                                  = 12,
          MAC_REG_RSP17_RSP17_RX_INFO_OK_MASK                                   = 0x00001000,
          MAC_REG_RSP17_RSP17_RX_INFO_NDP                                       = MAC_REG_RSP17,
          MAC_REG_RSP17_RSP17_RX_INFO_NDP_SHIFT                                 = 11,
          MAC_REG_RSP17_RSP17_RX_INFO_NDP_MASK                                  = 0x00000800,
          MAC_REG_RSP17_RSP17_RX_NDP_PSPOLL                                     = MAC_REG_RSP17,
          MAC_REG_RSP17_RSP17_RX_NDP_PSPOLL_SHIFT                               = 10,
          MAC_REG_RSP17_RSP17_RX_NDP_PSPOLL_MASK                                = 0x00000400,
          MAC_REG_RSP17_RSP17_RX_PV0_TYPE                                       = MAC_REG_RSP17,
          MAC_REG_RSP17_RSP17_RX_PV0_TYPE_SHIFT                                 = 8,
          MAC_REG_RSP17_RSP17_RX_PV0_TYPE_MASK                                  = 0x00000300,
          MAC_REG_RSP17_RSP17_RX_PV0_SUBTYPE                                    = MAC_REG_RSP17,
          MAC_REG_RSP17_RSP17_RX_PV0_SUBTYPE_SHIFT                              = 4,
          MAC_REG_RSP17_RSP17_RX_PV0_SUBTYPE_MASK                               = 0x000000f0,
          MAC_REG_RSP17_RSP17_RX_PV                                             = MAC_REG_RSP17,
          MAC_REG_RSP17_RSP17_RX_PV_SHIFT                                       = 3,
          MAC_REG_RSP17_RSP17_RX_PV_MASK                                        = 0x00000008,
          MAC_REG_RSP17_RSP17_GROUP_ADDRESS                                     = MAC_REG_RSP17,
          MAC_REG_RSP17_RSP17_GROUP_ADDRESS_SHIFT                               = 2,
          MAC_REG_RSP17_RSP17_GROUP_ADDRESS_MASK                                = 0x00000004,
          MAC_REG_RSP17_RSP17_OPERATION                                         = MAC_REG_RSP17,
          MAC_REG_RSP17_RSP17_OPERATION_SHIFT                                   = 1,
          MAC_REG_RSP17_RSP17_OPERATION_MASK                                    = 0x00000002,
          MAC_REG_RSP17_RSP17_RX_INFO_AGG                                       = MAC_REG_RSP17,
          MAC_REG_RSP17_RSP17_RX_INFO_AGG_SHIFT                                 = 0,
          MAC_REG_RSP17_RSP17_RX_INFO_AGG_MASK                                  = 0x00000001,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RSP18                                                               = 0x4008010c,
//-------------------------------------------------------------------------------------------------------------------------------,
          MAC_REG_RSP18_RSP18_VALID                                             = MAC_REG_RSP18,
          MAC_REG_RSP18_RSP18_VALID_SHIFT                                       = 31,
          MAC_REG_RSP18_RSP18_VALID_MASK                                        = 0x80000000,
          MAC_REG_RSP18_RSP18_CASE                                              = MAC_REG_RSP18,
          MAC_REG_RSP18_RSP18_CASE_SHIFT                                        = 26,
          MAC_REG_RSP18_RSP18_CASE_MASK                                         = 0x7c000000,
          MAC_REG_RSP18_RSP18_MASK_RX_INFO_OK                                   = MAC_REG_RSP18,
          MAC_REG_RSP18_RSP18_MASK_RX_INFO_OK_SHIFT                             = 25,
          MAC_REG_RSP18_RSP18_MASK_RX_INFO_OK_MASK                              = 0x02000000,
          MAC_REG_RSP18_RSP18_MASK_RX_INFO_NDP                                  = MAC_REG_RSP18,
          MAC_REG_RSP18_RSP18_MASK_RX_INFO_NDP_SHIFT                            = 24,
          MAC_REG_RSP18_RSP18_MASK_RX_INFO_NDP_MASK                             = 0x01000000,
          MAC_REG_RSP18_RSP18_MASK_RX_NDP_PSPOLL                                = MAC_REG_RSP18,
          MAC_REG_RSP18_RSP18_MASK_RX_NDP_PSPOLL_SHIFT                          = 23,
          MAC_REG_RSP18_RSP18_MASK_RX_NDP_PSPOLL_MASK                           = 0x00800000,
          MAC_REG_RSP18_RSP18_MASK_RX_PV0_TYPE                                  = MAC_REG_RSP18,
          MAC_REG_RSP18_RSP18_MASK_RX_PV0_TYPE_SHIFT                            = 21,
          MAC_REG_RSP18_RSP18_MASK_RX_PV0_TYPE_MASK                             = 0x00600000,
          MAC_REG_RSP18_RSP18_MASK_RX_PV0_SUBTYPE                               = MAC_REG_RSP18,
          MAC_REG_RSP18_RSP18_MASK_RX_PV0_SUBTYPE_SHIFT                         = 17,
          MAC_REG_RSP18_RSP18_MASK_RX_PV0_SUBTYPE_MASK                          = 0x001e0000,
          MAC_REG_RSP18_RSP18_MASK_RX_PV                                        = MAC_REG_RSP18,
          MAC_REG_RSP18_RSP18_MASK_RX_PV_SHIFT                                  = 16,
          MAC_REG_RSP18_RSP18_MASK_RX_PV_MASK                                   = 0x00010000,
          MAC_REG_RSP18_RSP18_MASK_GROUP_ADDRESS                                = MAC_REG_RSP18,
          MAC_REG_RSP18_RSP18_MASK_GROUP_ADDRESS_SHIFT                          = 15,
          MAC_REG_RSP18_RSP18_MASK_GROUP_ADDRESS_MASK                           = 0x00008000,
          MAC_REG_RSP18_RSP18_MASK_OPERATION                                    = MAC_REG_RSP18,
          MAC_REG_RSP18_RSP18_MASK_OPERATION_SHIFT                              = 14,
          MAC_REG_RSP18_RSP18_MASK_OPERATION_MASK                               = 0x00004000,
          MAC_REG_RSP18_RSP18_MASK_RX_INFO_AGG                                  = MAC_REG_RSP18,
          MAC_REG_RSP18_RSP18_MASK_RX_INFO_AGG_SHIFT                            = 13,
          MAC_REG_RSP18_RSP18_MASK_RX_INFO_AGG_MASK                             = 0x00002000,
          MAC_REG_RSP18_RSP18_RX_INFO_OK                                        = MAC_REG_RSP18,
          MAC_REG_RSP18_RSP18_RX_INFO_OK_SHIFT                                  = 12,
          MAC_REG_RSP18_RSP18_RX_INFO_OK_MASK                                   = 0x00001000,
          MAC_REG_RSP18_RSP18_RX_INFO_NDP                                       = MAC_REG_RSP18,
          MAC_REG_RSP18_RSP18_RX_INFO_NDP_SHIFT                                 = 11,
          MAC_REG_RSP18_RSP18_RX_INFO_NDP_MASK                                  = 0x00000800,
          MAC_REG_RSP18_RSP18_RX_NDP_PSPOLL                                     = MAC_REG_RSP18,
          MAC_REG_RSP18_RSP18_RX_NDP_PSPOLL_SHIFT                               = 10,
          MAC_REG_RSP18_RSP18_RX_NDP_PSPOLL_MASK                                = 0x00000400,
          MAC_REG_RSP18_RSP18_RX_PV0_TYPE                                       = MAC_REG_RSP18,
          MAC_REG_RSP18_RSP18_RX_PV0_TYPE_SHIFT                                 = 8,
          MAC_REG_RSP18_RSP18_RX_PV0_TYPE_MASK                                  = 0x00000300,
          MAC_REG_RSP18_RSP18_RX_PV0_SUBTYPE                                    = MAC_REG_RSP18,
          MAC_REG_RSP18_RSP18_RX_PV0_SUBTYPE_SHIFT                              = 4,
          MAC_REG_RSP18_RSP18_RX_PV0_SUBTYPE_MASK                               = 0x000000f0,
          MAC_REG_RSP18_RSP18_RX_PV                                             = MAC_REG_RSP18,
          MAC_REG_RSP18_RSP18_RX_PV_SHIFT                                       = 3,
          MAC_REG_RSP18_RSP18_RX_PV_MASK                                        = 0x00000008,
          MAC_REG_RSP18_RSP18_GROUP_ADDRESS                                     = MAC_REG_RSP18,
          MAC_REG_RSP18_RSP18_GROUP_ADDRESS_SHIFT                               = 2,
          MAC_REG_RSP18_RSP18_GROUP_ADDRESS_MASK                                = 0x00000004,
          MAC_REG_RSP18_RSP18_OPERATION                                         = MAC_REG_RSP18,
          MAC_REG_RSP18_RSP18_OPERATION_SHIFT                                   = 1,
          MAC_REG_RSP18_RSP18_OPERATION_MASK                                    = 0x00000002,
          MAC_REG_RSP18_RSP18_RX_INFO_AGG                                       = MAC_REG_RSP18,
          MAC_REG_RSP18_RSP18_RX_INFO_AGG_SHIFT                                 = 0,
          MAC_REG_RSP18_RSP18_RX_INFO_AGG_MASK                                  = 0x00000001,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RSP19                                                               = 0x40080110,
//-------------------------------------------------------------------------------------------------------------------------------,
          MAC_REG_RSP19_RSP19_VALID                                             = MAC_REG_RSP19,
          MAC_REG_RSP19_RSP19_VALID_SHIFT                                       = 31,
          MAC_REG_RSP19_RSP19_VALID_MASK                                        = 0x80000000,
          MAC_REG_RSP19_RSP19_CASE                                              = MAC_REG_RSP19,
          MAC_REG_RSP19_RSP19_CASE_SHIFT                                        = 26,
          MAC_REG_RSP19_RSP19_CASE_MASK                                         = 0x7c000000,
          MAC_REG_RSP19_RSP19_MASK_RX_INFO_OK                                   = MAC_REG_RSP19,
          MAC_REG_RSP19_RSP19_MASK_RX_INFO_OK_SHIFT                             = 25,
          MAC_REG_RSP19_RSP19_MASK_RX_INFO_OK_MASK                              = 0x02000000,
          MAC_REG_RSP19_RSP19_MASK_RX_INFO_NDP                                  = MAC_REG_RSP19,
          MAC_REG_RSP19_RSP19_MASK_RX_INFO_NDP_SHIFT                            = 24,
          MAC_REG_RSP19_RSP19_MASK_RX_INFO_NDP_MASK                             = 0x01000000,
          MAC_REG_RSP19_RSP19_MASK_RX_NDP_PSPOLL                                = MAC_REG_RSP19,
          MAC_REG_RSP19_RSP19_MASK_RX_NDP_PSPOLL_SHIFT                          = 23,
          MAC_REG_RSP19_RSP19_MASK_RX_NDP_PSPOLL_MASK                           = 0x00800000,
          MAC_REG_RSP19_RSP19_MASK_RX_PV0_TYPE                                  = MAC_REG_RSP19,
          MAC_REG_RSP19_RSP19_MASK_RX_PV0_TYPE_SHIFT                            = 21,
          MAC_REG_RSP19_RSP19_MASK_RX_PV0_TYPE_MASK                             = 0x00600000,
          MAC_REG_RSP19_RSP19_MASK_RX_PV0_SUBTYPE                               = MAC_REG_RSP19,
          MAC_REG_RSP19_RSP19_MASK_RX_PV0_SUBTYPE_SHIFT                         = 17,
          MAC_REG_RSP19_RSP19_MASK_RX_PV0_SUBTYPE_MASK                          = 0x001e0000,
          MAC_REG_RSP19_RSP19_MASK_RX_PV                                        = MAC_REG_RSP19,
          MAC_REG_RSP19_RSP19_MASK_RX_PV_SHIFT                                  = 16,
          MAC_REG_RSP19_RSP19_MASK_RX_PV_MASK                                   = 0x00010000,
          MAC_REG_RSP19_RSP19_MASK_GROUP_ADDRESS                                = MAC_REG_RSP19,
          MAC_REG_RSP19_RSP19_MASK_GROUP_ADDRESS_SHIFT                          = 15,
          MAC_REG_RSP19_RSP19_MASK_GROUP_ADDRESS_MASK                           = 0x00008000,
          MAC_REG_RSP19_RSP19_MASK_OPERATION                                    = MAC_REG_RSP19,
          MAC_REG_RSP19_RSP19_MASK_OPERATION_SHIFT                              = 14,
          MAC_REG_RSP19_RSP19_MASK_OPERATION_MASK                               = 0x00004000,
          MAC_REG_RSP19_RSP19_MASK_RX_INFO_AGG                                  = MAC_REG_RSP19,
          MAC_REG_RSP19_RSP19_MASK_RX_INFO_AGG_SHIFT                            = 13,
          MAC_REG_RSP19_RSP19_MASK_RX_INFO_AGG_MASK                             = 0x00002000,
          MAC_REG_RSP19_RSP19_RX_INFO_OK                                        = MAC_REG_RSP19,
          MAC_REG_RSP19_RSP19_RX_INFO_OK_SHIFT                                  = 12,
          MAC_REG_RSP19_RSP19_RX_INFO_OK_MASK                                   = 0x00001000,
          MAC_REG_RSP19_RSP19_RX_INFO_NDP                                       = MAC_REG_RSP19,
          MAC_REG_RSP19_RSP19_RX_INFO_NDP_SHIFT                                 = 11,
          MAC_REG_RSP19_RSP19_RX_INFO_NDP_MASK                                  = 0x00000800,
          MAC_REG_RSP19_RSP19_RX_NDP_PSPOLL                                     = MAC_REG_RSP19,
          MAC_REG_RSP19_RSP19_RX_NDP_PSPOLL_SHIFT                               = 10,
          MAC_REG_RSP19_RSP19_RX_NDP_PSPOLL_MASK                                = 0x00000400,
          MAC_REG_RSP19_RSP19_RX_PV0_TYPE                                       = MAC_REG_RSP19,
          MAC_REG_RSP19_RSP19_RX_PV0_TYPE_SHIFT                                 = 8,
          MAC_REG_RSP19_RSP19_RX_PV0_TYPE_MASK                                  = 0x00000300,
          MAC_REG_RSP19_RSP19_RX_PV0_SUBTYPE                                    = MAC_REG_RSP19,
          MAC_REG_RSP19_RSP19_RX_PV0_SUBTYPE_SHIFT                              = 4,
          MAC_REG_RSP19_RSP19_RX_PV0_SUBTYPE_MASK                               = 0x000000f0,
          MAC_REG_RSP19_RSP19_RX_PV                                             = MAC_REG_RSP19,
          MAC_REG_RSP19_RSP19_RX_PV_SHIFT                                       = 3,
          MAC_REG_RSP19_RSP19_RX_PV_MASK                                        = 0x00000008,
          MAC_REG_RSP19_RSP19_GROUP_ADDRESS                                     = MAC_REG_RSP19,
          MAC_REG_RSP19_RSP19_GROUP_ADDRESS_SHIFT                               = 2,
          MAC_REG_RSP19_RSP19_GROUP_ADDRESS_MASK                                = 0x00000004,
          MAC_REG_RSP19_RSP19_OPERATION                                         = MAC_REG_RSP19,
          MAC_REG_RSP19_RSP19_OPERATION_SHIFT                                   = 1,
          MAC_REG_RSP19_RSP19_OPERATION_MASK                                    = 0x00000002,
          MAC_REG_RSP19_RSP19_RX_INFO_AGG                                       = MAC_REG_RSP19,
          MAC_REG_RSP19_RSP19_RX_INFO_AGG_SHIFT                                 = 0,
          MAC_REG_RSP19_RSP19_RX_INFO_AGG_MASK                                  = 0x00000001,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RSP20                                                               = 0x40080114,
//-------------------------------------------------------------------------------------------------------------------------------,
          MAC_REG_RSP20_RSP20_VALID                                             = MAC_REG_RSP20,
          MAC_REG_RSP20_RSP20_VALID_SHIFT                                       = 31,
          MAC_REG_RSP20_RSP20_VALID_MASK                                        = 0x80000000,
          MAC_REG_RSP20_RSP20_CASE                                              = MAC_REG_RSP20,
          MAC_REG_RSP20_RSP20_CASE_SHIFT                                        = 26,
          MAC_REG_RSP20_RSP20_CASE_MASK                                         = 0x7c000000,
          MAC_REG_RSP20_RSP20_MASK_RX_INFO_OK                                   = MAC_REG_RSP20,
          MAC_REG_RSP20_RSP20_MASK_RX_INFO_OK_SHIFT                             = 25,
          MAC_REG_RSP20_RSP20_MASK_RX_INFO_OK_MASK                              = 0x02000000,
          MAC_REG_RSP20_RSP20_MASK_RX_INFO_NDP                                  = MAC_REG_RSP20,
          MAC_REG_RSP20_RSP20_MASK_RX_INFO_NDP_SHIFT                            = 24,
          MAC_REG_RSP20_RSP20_MASK_RX_INFO_NDP_MASK                             = 0x01000000,
          MAC_REG_RSP20_RSP20_MASK_RX_NDP_PSPOLL                                = MAC_REG_RSP20,
          MAC_REG_RSP20_RSP20_MASK_RX_NDP_PSPOLL_SHIFT                          = 23,
          MAC_REG_RSP20_RSP20_MASK_RX_NDP_PSPOLL_MASK                           = 0x00800000,
          MAC_REG_RSP20_RSP20_MASK_RX_PV0_TYPE                                  = MAC_REG_RSP20,
          MAC_REG_RSP20_RSP20_MASK_RX_PV0_TYPE_SHIFT                            = 21,
          MAC_REG_RSP20_RSP20_MASK_RX_PV0_TYPE_MASK                             = 0x00600000,
          MAC_REG_RSP20_RSP20_MASK_RX_PV0_SUBTYPE                               = MAC_REG_RSP20,
          MAC_REG_RSP20_RSP20_MASK_RX_PV0_SUBTYPE_SHIFT                         = 17,
          MAC_REG_RSP20_RSP20_MASK_RX_PV0_SUBTYPE_MASK                          = 0x001e0000,
          MAC_REG_RSP20_RSP20_MASK_RX_PV                                        = MAC_REG_RSP20,
          MAC_REG_RSP20_RSP20_MASK_RX_PV_SHIFT                                  = 16,
          MAC_REG_RSP20_RSP20_MASK_RX_PV_MASK                                   = 0x00010000,
          MAC_REG_RSP20_RSP20_MASK_GROUP_ADDRESS                                = MAC_REG_RSP20,
          MAC_REG_RSP20_RSP20_MASK_GROUP_ADDRESS_SHIFT                          = 15,
          MAC_REG_RSP20_RSP20_MASK_GROUP_ADDRESS_MASK                           = 0x00008000,
          MAC_REG_RSP20_RSP20_MASK_OPERATION                                    = MAC_REG_RSP20,
          MAC_REG_RSP20_RSP20_MASK_OPERATION_SHIFT                              = 14,
          MAC_REG_RSP20_RSP20_MASK_OPERATION_MASK                               = 0x00004000,
          MAC_REG_RSP20_RSP20_MASK_RX_INFO_AGG                                  = MAC_REG_RSP20,
          MAC_REG_RSP20_RSP20_MASK_RX_INFO_AGG_SHIFT                            = 13,
          MAC_REG_RSP20_RSP20_MASK_RX_INFO_AGG_MASK                             = 0x00002000,
          MAC_REG_RSP20_RSP20_RX_INFO_OK                                        = MAC_REG_RSP20,
          MAC_REG_RSP20_RSP20_RX_INFO_OK_SHIFT                                  = 12,
          MAC_REG_RSP20_RSP20_RX_INFO_OK_MASK                                   = 0x00001000,
          MAC_REG_RSP20_RSP20_RX_INFO_NDP                                       = MAC_REG_RSP20,
          MAC_REG_RSP20_RSP20_RX_INFO_NDP_SHIFT                                 = 11,
          MAC_REG_RSP20_RSP20_RX_INFO_NDP_MASK                                  = 0x00000800,
          MAC_REG_RSP20_RSP20_RX_NDP_PSPOLL                                     = MAC_REG_RSP20,
          MAC_REG_RSP20_RSP20_RX_NDP_PSPOLL_SHIFT                               = 10,
          MAC_REG_RSP20_RSP20_RX_NDP_PSPOLL_MASK                                = 0x00000400,
          MAC_REG_RSP20_RSP20_RX_PV0_TYPE                                       = MAC_REG_RSP20,
          MAC_REG_RSP20_RSP20_RX_PV0_TYPE_SHIFT                                 = 8,
          MAC_REG_RSP20_RSP20_RX_PV0_TYPE_MASK                                  = 0x00000300,
          MAC_REG_RSP20_RSP20_RX_PV0_SUBTYPE                                    = MAC_REG_RSP20,
          MAC_REG_RSP20_RSP20_RX_PV0_SUBTYPE_SHIFT                              = 4,
          MAC_REG_RSP20_RSP20_RX_PV0_SUBTYPE_MASK                               = 0x000000f0,
          MAC_REG_RSP20_RSP20_RX_PV                                             = MAC_REG_RSP20,
          MAC_REG_RSP20_RSP20_RX_PV_SHIFT                                       = 3,
          MAC_REG_RSP20_RSP20_RX_PV_MASK                                        = 0x00000008,
          MAC_REG_RSP20_RSP20_GROUP_ADDRESS                                     = MAC_REG_RSP20,
          MAC_REG_RSP20_RSP20_GROUP_ADDRESS_SHIFT                               = 2,
          MAC_REG_RSP20_RSP20_GROUP_ADDRESS_MASK                                = 0x00000004,
          MAC_REG_RSP20_RSP20_OPERATION                                         = MAC_REG_RSP20,
          MAC_REG_RSP20_RSP20_OPERATION_SHIFT                                   = 1,
          MAC_REG_RSP20_RSP20_OPERATION_MASK                                    = 0x00000002,
          MAC_REG_RSP20_RSP20_RX_INFO_AGG                                       = MAC_REG_RSP20,
          MAC_REG_RSP20_RSP20_RX_INFO_AGG_SHIFT                                 = 0,
          MAC_REG_RSP20_RSP20_RX_INFO_AGG_MASK                                  = 0x00000001,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RSP21                                                               = 0x40080118,
//-------------------------------------------------------------------------------------------------------------------------------,
          MAC_REG_RSP21_RSP21_VALID                                             = MAC_REG_RSP21,
          MAC_REG_RSP21_RSP21_VALID_SHIFT                                       = 31,
          MAC_REG_RSP21_RSP21_VALID_MASK                                        = 0x80000000,
          MAC_REG_RSP21_RSP21_CASE                                              = MAC_REG_RSP21,
          MAC_REG_RSP21_RSP21_CASE_SHIFT                                        = 26,
          MAC_REG_RSP21_RSP21_CASE_MASK                                         = 0x7c000000,
          MAC_REG_RSP21_RSP21_MASK_RX_INFO_OK                                   = MAC_REG_RSP21,
          MAC_REG_RSP21_RSP21_MASK_RX_INFO_OK_SHIFT                             = 25,
          MAC_REG_RSP21_RSP21_MASK_RX_INFO_OK_MASK                              = 0x02000000,
          MAC_REG_RSP21_RSP21_MASK_RX_INFO_NDP                                  = MAC_REG_RSP21,
          MAC_REG_RSP21_RSP21_MASK_RX_INFO_NDP_SHIFT                            = 24,
          MAC_REG_RSP21_RSP21_MASK_RX_INFO_NDP_MASK                             = 0x01000000,
          MAC_REG_RSP21_RSP21_MASK_RX_NDP_PSPOLL                                = MAC_REG_RSP21,
          MAC_REG_RSP21_RSP21_MASK_RX_NDP_PSPOLL_SHIFT                          = 23,
          MAC_REG_RSP21_RSP21_MASK_RX_NDP_PSPOLL_MASK                           = 0x00800000,
          MAC_REG_RSP21_RSP21_MASK_RX_PV0_TYPE                                  = MAC_REG_RSP21,
          MAC_REG_RSP21_RSP21_MASK_RX_PV0_TYPE_SHIFT                            = 21,
          MAC_REG_RSP21_RSP21_MASK_RX_PV0_TYPE_MASK                             = 0x00600000,
          MAC_REG_RSP21_RSP21_MASK_RX_PV0_SUBTYPE                               = MAC_REG_RSP21,
          MAC_REG_RSP21_RSP21_MASK_RX_PV0_SUBTYPE_SHIFT                         = 17,
          MAC_REG_RSP21_RSP21_MASK_RX_PV0_SUBTYPE_MASK                          = 0x001e0000,
          MAC_REG_RSP21_RSP21_MASK_RX_PV                                        = MAC_REG_RSP21,
          MAC_REG_RSP21_RSP21_MASK_RX_PV_SHIFT                                  = 16,
          MAC_REG_RSP21_RSP21_MASK_RX_PV_MASK                                   = 0x00010000,
          MAC_REG_RSP21_RSP21_MASK_GROUP_ADDRESS                                = MAC_REG_RSP21,
          MAC_REG_RSP21_RSP21_MASK_GROUP_ADDRESS_SHIFT                          = 15,
          MAC_REG_RSP21_RSP21_MASK_GROUP_ADDRESS_MASK                           = 0x00008000,
          MAC_REG_RSP21_RSP21_MASK_OPERATION                                    = MAC_REG_RSP21,
          MAC_REG_RSP21_RSP21_MASK_OPERATION_SHIFT                              = 14,
          MAC_REG_RSP21_RSP21_MASK_OPERATION_MASK                               = 0x00004000,
          MAC_REG_RSP21_RSP21_MASK_RX_INFO_AGG                                  = MAC_REG_RSP21,
          MAC_REG_RSP21_RSP21_MASK_RX_INFO_AGG_SHIFT                            = 13,
          MAC_REG_RSP21_RSP21_MASK_RX_INFO_AGG_MASK                             = 0x00002000,
          MAC_REG_RSP21_RSP21_RX_INFO_OK                                        = MAC_REG_RSP21,
          MAC_REG_RSP21_RSP21_RX_INFO_OK_SHIFT                                  = 12,
          MAC_REG_RSP21_RSP21_RX_INFO_OK_MASK                                   = 0x00001000,
          MAC_REG_RSP21_RSP21_RX_INFO_NDP                                       = MAC_REG_RSP21,
          MAC_REG_RSP21_RSP21_RX_INFO_NDP_SHIFT                                 = 11,
          MAC_REG_RSP21_RSP21_RX_INFO_NDP_MASK                                  = 0x00000800,
          MAC_REG_RSP21_RSP21_RX_NDP_PSPOLL                                     = MAC_REG_RSP21,
          MAC_REG_RSP21_RSP21_RX_NDP_PSPOLL_SHIFT                               = 10,
          MAC_REG_RSP21_RSP21_RX_NDP_PSPOLL_MASK                                = 0x00000400,
          MAC_REG_RSP21_RSP21_RX_PV0_TYPE                                       = MAC_REG_RSP21,
          MAC_REG_RSP21_RSP21_RX_PV0_TYPE_SHIFT                                 = 8,
          MAC_REG_RSP21_RSP21_RX_PV0_TYPE_MASK                                  = 0x00000300,
          MAC_REG_RSP21_RSP21_RX_PV0_SUBTYPE                                    = MAC_REG_RSP21,
          MAC_REG_RSP21_RSP21_RX_PV0_SUBTYPE_SHIFT                              = 4,
          MAC_REG_RSP21_RSP21_RX_PV0_SUBTYPE_MASK                               = 0x000000f0,
          MAC_REG_RSP21_RSP21_RX_PV                                             = MAC_REG_RSP21,
          MAC_REG_RSP21_RSP21_RX_PV_SHIFT                                       = 3,
          MAC_REG_RSP21_RSP21_RX_PV_MASK                                        = 0x00000008,
          MAC_REG_RSP21_RSP21_GROUP_ADDRESS                                     = MAC_REG_RSP21,
          MAC_REG_RSP21_RSP21_GROUP_ADDRESS_SHIFT                               = 2,
          MAC_REG_RSP21_RSP21_GROUP_ADDRESS_MASK                                = 0x00000004,
          MAC_REG_RSP21_RSP21_OPERATION                                         = MAC_REG_RSP21,
          MAC_REG_RSP21_RSP21_OPERATION_SHIFT                                   = 1,
          MAC_REG_RSP21_RSP21_OPERATION_MASK                                    = 0x00000002,
          MAC_REG_RSP21_RSP21_RX_INFO_AGG                                       = MAC_REG_RSP21,
          MAC_REG_RSP21_RSP21_RX_INFO_AGG_SHIFT                                 = 0,
          MAC_REG_RSP21_RSP21_RX_INFO_AGG_MASK                                  = 0x00000001,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RSP22                                                               = 0x4008011c,
//-------------------------------------------------------------------------------------------------------------------------------,
          MAC_REG_RSP22_RSP22_VALID                                             = MAC_REG_RSP22,
          MAC_REG_RSP22_RSP22_VALID_SHIFT                                       = 31,
          MAC_REG_RSP22_RSP22_VALID_MASK                                        = 0x80000000,
          MAC_REG_RSP22_RSP22_CASE                                              = MAC_REG_RSP22,
          MAC_REG_RSP22_RSP22_CASE_SHIFT                                        = 26,
          MAC_REG_RSP22_RSP22_CASE_MASK                                         = 0x7c000000,
          MAC_REG_RSP22_RSP22_MASK_RX_INFO_OK                                   = MAC_REG_RSP22,
          MAC_REG_RSP22_RSP22_MASK_RX_INFO_OK_SHIFT                             = 25,
          MAC_REG_RSP22_RSP22_MASK_RX_INFO_OK_MASK                              = 0x02000000,
          MAC_REG_RSP22_RSP22_MASK_RX_INFO_NDP                                  = MAC_REG_RSP22,
          MAC_REG_RSP22_RSP22_MASK_RX_INFO_NDP_SHIFT                            = 24,
          MAC_REG_RSP22_RSP22_MASK_RX_INFO_NDP_MASK                             = 0x01000000,
          MAC_REG_RSP22_RSP22_MASK_RX_NDP_PSPOLL                                = MAC_REG_RSP22,
          MAC_REG_RSP22_RSP22_MASK_RX_NDP_PSPOLL_SHIFT                          = 23,
          MAC_REG_RSP22_RSP22_MASK_RX_NDP_PSPOLL_MASK                           = 0x00800000,
          MAC_REG_RSP22_RSP22_MASK_RX_PV0_TYPE                                  = MAC_REG_RSP22,
          MAC_REG_RSP22_RSP22_MASK_RX_PV0_TYPE_SHIFT                            = 21,
          MAC_REG_RSP22_RSP22_MASK_RX_PV0_TYPE_MASK                             = 0x00600000,
          MAC_REG_RSP22_RSP22_MASK_RX_PV0_SUBTYPE                               = MAC_REG_RSP22,
          MAC_REG_RSP22_RSP22_MASK_RX_PV0_SUBTYPE_SHIFT                         = 17,
          MAC_REG_RSP22_RSP22_MASK_RX_PV0_SUBTYPE_MASK                          = 0x001e0000,
          MAC_REG_RSP22_RSP22_MASK_RX_PV                                        = MAC_REG_RSP22,
          MAC_REG_RSP22_RSP22_MASK_RX_PV_SHIFT                                  = 16,
          MAC_REG_RSP22_RSP22_MASK_RX_PV_MASK                                   = 0x00010000,
          MAC_REG_RSP22_RSP22_MASK_GROUP_ADDRESS                                = MAC_REG_RSP22,
          MAC_REG_RSP22_RSP22_MASK_GROUP_ADDRESS_SHIFT                          = 15,
          MAC_REG_RSP22_RSP22_MASK_GROUP_ADDRESS_MASK                           = 0x00008000,
          MAC_REG_RSP22_RSP22_MASK_OPERATION                                    = MAC_REG_RSP22,
          MAC_REG_RSP22_RSP22_MASK_OPERATION_SHIFT                              = 14,
          MAC_REG_RSP22_RSP22_MASK_OPERATION_MASK                               = 0x00004000,
          MAC_REG_RSP22_RSP22_MASK_RX_INFO_AGG                                  = MAC_REG_RSP22,
          MAC_REG_RSP22_RSP22_MASK_RX_INFO_AGG_SHIFT                            = 13,
          MAC_REG_RSP22_RSP22_MASK_RX_INFO_AGG_MASK                             = 0x00002000,
          MAC_REG_RSP22_RSP22_RX_INFO_OK                                        = MAC_REG_RSP22,
          MAC_REG_RSP22_RSP22_RX_INFO_OK_SHIFT                                  = 12,
          MAC_REG_RSP22_RSP22_RX_INFO_OK_MASK                                   = 0x00001000,
          MAC_REG_RSP22_RSP22_RX_INFO_NDP                                       = MAC_REG_RSP22,
          MAC_REG_RSP22_RSP22_RX_INFO_NDP_SHIFT                                 = 11,
          MAC_REG_RSP22_RSP22_RX_INFO_NDP_MASK                                  = 0x00000800,
          MAC_REG_RSP22_RSP22_RX_NDP_PSPOLL                                     = MAC_REG_RSP22,
          MAC_REG_RSP22_RSP22_RX_NDP_PSPOLL_SHIFT                               = 10,
          MAC_REG_RSP22_RSP22_RX_NDP_PSPOLL_MASK                                = 0x00000400,
          MAC_REG_RSP22_RSP22_RX_PV0_TYPE                                       = MAC_REG_RSP22,
          MAC_REG_RSP22_RSP22_RX_PV0_TYPE_SHIFT                                 = 8,
          MAC_REG_RSP22_RSP22_RX_PV0_TYPE_MASK                                  = 0x00000300,
          MAC_REG_RSP22_RSP22_RX_PV0_SUBTYPE                                    = MAC_REG_RSP22,
          MAC_REG_RSP22_RSP22_RX_PV0_SUBTYPE_SHIFT                              = 4,
          MAC_REG_RSP22_RSP22_RX_PV0_SUBTYPE_MASK                               = 0x000000f0,
          MAC_REG_RSP22_RSP22_RX_PV                                             = MAC_REG_RSP22,
          MAC_REG_RSP22_RSP22_RX_PV_SHIFT                                       = 3,
          MAC_REG_RSP22_RSP22_RX_PV_MASK                                        = 0x00000008,
          MAC_REG_RSP22_RSP22_GROUP_ADDRESS                                     = MAC_REG_RSP22,
          MAC_REG_RSP22_RSP22_GROUP_ADDRESS_SHIFT                               = 2,
          MAC_REG_RSP22_RSP22_GROUP_ADDRESS_MASK                                = 0x00000004,
          MAC_REG_RSP22_RSP22_OPERATION                                         = MAC_REG_RSP22,
          MAC_REG_RSP22_RSP22_OPERATION_SHIFT                                   = 1,
          MAC_REG_RSP22_RSP22_OPERATION_MASK                                    = 0x00000002,
          MAC_REG_RSP22_RSP22_RX_INFO_AGG                                       = MAC_REG_RSP22,
          MAC_REG_RSP22_RSP22_RX_INFO_AGG_SHIFT                                 = 0,
          MAC_REG_RSP22_RSP22_RX_INFO_AGG_MASK                                  = 0x00000001,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RSP23                                                               = 0x40080120,
//-------------------------------------------------------------------------------------------------------------------------------,
          MAC_REG_RSP23_RSP23_VALID                                             = MAC_REG_RSP23,
          MAC_REG_RSP23_RSP23_VALID_SHIFT                                       = 31,
          MAC_REG_RSP23_RSP23_VALID_MASK                                        = 0x80000000,
          MAC_REG_RSP23_RSP23_CASE                                              = MAC_REG_RSP23,
          MAC_REG_RSP23_RSP23_CASE_SHIFT                                        = 26,
          MAC_REG_RSP23_RSP23_CASE_MASK                                         = 0x7c000000,
          MAC_REG_RSP23_RSP23_MASK_RX_INFO_OK                                   = MAC_REG_RSP23,
          MAC_REG_RSP23_RSP23_MASK_RX_INFO_OK_SHIFT                             = 25,
          MAC_REG_RSP23_RSP23_MASK_RX_INFO_OK_MASK                              = 0x02000000,
          MAC_REG_RSP23_RSP23_MASK_RX_INFO_NDP                                  = MAC_REG_RSP23,
          MAC_REG_RSP23_RSP23_MASK_RX_INFO_NDP_SHIFT                            = 24,
          MAC_REG_RSP23_RSP23_MASK_RX_INFO_NDP_MASK                             = 0x01000000,
          MAC_REG_RSP23_RSP23_MASK_RX_NDP_PSPOLL                                = MAC_REG_RSP23,
          MAC_REG_RSP23_RSP23_MASK_RX_NDP_PSPOLL_SHIFT                          = 23,
          MAC_REG_RSP23_RSP23_MASK_RX_NDP_PSPOLL_MASK                           = 0x00800000,
          MAC_REG_RSP23_RSP23_MASK_RX_PV0_TYPE                                  = MAC_REG_RSP23,
          MAC_REG_RSP23_RSP23_MASK_RX_PV0_TYPE_SHIFT                            = 21,
          MAC_REG_RSP23_RSP23_MASK_RX_PV0_TYPE_MASK                             = 0x00600000,
          MAC_REG_RSP23_RSP23_MASK_RX_PV0_SUBTYPE                               = MAC_REG_RSP23,
          MAC_REG_RSP23_RSP23_MASK_RX_PV0_SUBTYPE_SHIFT                         = 17,
          MAC_REG_RSP23_RSP23_MASK_RX_PV0_SUBTYPE_MASK                          = 0x001e0000,
          MAC_REG_RSP23_RSP23_MASK_RX_PV                                        = MAC_REG_RSP23,
          MAC_REG_RSP23_RSP23_MASK_RX_PV_SHIFT                                  = 16,
          MAC_REG_RSP23_RSP23_MASK_RX_PV_MASK                                   = 0x00010000,
          MAC_REG_RSP23_RSP23_MASK_GROUP_ADDRESS                                = MAC_REG_RSP23,
          MAC_REG_RSP23_RSP23_MASK_GROUP_ADDRESS_SHIFT                          = 15,
          MAC_REG_RSP23_RSP23_MASK_GROUP_ADDRESS_MASK                           = 0x00008000,
          MAC_REG_RSP23_RSP23_MASK_OPERATION                                    = MAC_REG_RSP23,
          MAC_REG_RSP23_RSP23_MASK_OPERATION_SHIFT                              = 14,
          MAC_REG_RSP23_RSP23_MASK_OPERATION_MASK                               = 0x00004000,
          MAC_REG_RSP23_RSP23_MASK_RX_INFO_AGG                                  = MAC_REG_RSP23,
          MAC_REG_RSP23_RSP23_MASK_RX_INFO_AGG_SHIFT                            = 13,
          MAC_REG_RSP23_RSP23_MASK_RX_INFO_AGG_MASK                             = 0x00002000,
          MAC_REG_RSP23_RSP23_RX_INFO_OK                                        = MAC_REG_RSP23,
          MAC_REG_RSP23_RSP23_RX_INFO_OK_SHIFT                                  = 12,
          MAC_REG_RSP23_RSP23_RX_INFO_OK_MASK                                   = 0x00001000,
          MAC_REG_RSP23_RSP23_RX_INFO_NDP                                       = MAC_REG_RSP23,
          MAC_REG_RSP23_RSP23_RX_INFO_NDP_SHIFT                                 = 11,
          MAC_REG_RSP23_RSP23_RX_INFO_NDP_MASK                                  = 0x00000800,
          MAC_REG_RSP23_RSP23_RX_NDP_PSPOLL                                     = MAC_REG_RSP23,
          MAC_REG_RSP23_RSP23_RX_NDP_PSPOLL_SHIFT                               = 10,
          MAC_REG_RSP23_RSP23_RX_NDP_PSPOLL_MASK                                = 0x00000400,
          MAC_REG_RSP23_RSP23_RX_PV0_TYPE                                       = MAC_REG_RSP23,
          MAC_REG_RSP23_RSP23_RX_PV0_TYPE_SHIFT                                 = 8,
          MAC_REG_RSP23_RSP23_RX_PV0_TYPE_MASK                                  = 0x00000300,
          MAC_REG_RSP23_RSP23_RX_PV0_SUBTYPE                                    = MAC_REG_RSP23,
          MAC_REG_RSP23_RSP23_RX_PV0_SUBTYPE_SHIFT                              = 4,
          MAC_REG_RSP23_RSP23_RX_PV0_SUBTYPE_MASK                               = 0x000000f0,
          MAC_REG_RSP23_RSP23_RX_PV                                             = MAC_REG_RSP23,
          MAC_REG_RSP23_RSP23_RX_PV_SHIFT                                       = 3,
          MAC_REG_RSP23_RSP23_RX_PV_MASK                                        = 0x00000008,
          MAC_REG_RSP23_RSP23_GROUP_ADDRESS                                     = MAC_REG_RSP23,
          MAC_REG_RSP23_RSP23_GROUP_ADDRESS_SHIFT                               = 2,
          MAC_REG_RSP23_RSP23_GROUP_ADDRESS_MASK                                = 0x00000004,
          MAC_REG_RSP23_RSP23_OPERATION                                         = MAC_REG_RSP23,
          MAC_REG_RSP23_RSP23_OPERATION_SHIFT                                   = 1,
          MAC_REG_RSP23_RSP23_OPERATION_MASK                                    = 0x00000002,
          MAC_REG_RSP23_RSP23_RX_INFO_AGG                                       = MAC_REG_RSP23,
          MAC_REG_RSP23_RSP23_RX_INFO_AGG_SHIFT                                 = 0,
          MAC_REG_RSP23_RSP23_RX_INFO_AGG_MASK                                  = 0x00000001,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RSP24                                                               = 0x40080124,
//-------------------------------------------------------------------------------------------------------------------------------,
          MAC_REG_RSP24_RSP24_VALID                                             = MAC_REG_RSP24,
          MAC_REG_RSP24_RSP24_VALID_SHIFT                                       = 31,
          MAC_REG_RSP24_RSP24_VALID_MASK                                        = 0x80000000,
          MAC_REG_RSP24_RSP24_CASE                                              = MAC_REG_RSP24,
          MAC_REG_RSP24_RSP24_CASE_SHIFT                                        = 26,
          MAC_REG_RSP24_RSP24_CASE_MASK                                         = 0x7c000000,
          MAC_REG_RSP24_RSP24_MASK_RX_INFO_OK                                   = MAC_REG_RSP24,
          MAC_REG_RSP24_RSP24_MASK_RX_INFO_OK_SHIFT                             = 25,
          MAC_REG_RSP24_RSP24_MASK_RX_INFO_OK_MASK                              = 0x02000000,
          MAC_REG_RSP24_RSP24_MASK_RX_INFO_NDP                                  = MAC_REG_RSP24,
          MAC_REG_RSP24_RSP24_MASK_RX_INFO_NDP_SHIFT                            = 24,
          MAC_REG_RSP24_RSP24_MASK_RX_INFO_NDP_MASK                             = 0x01000000,
          MAC_REG_RSP24_RSP24_MASK_RX_NDP_PSPOLL                                = MAC_REG_RSP24,
          MAC_REG_RSP24_RSP24_MASK_RX_NDP_PSPOLL_SHIFT                          = 23,
          MAC_REG_RSP24_RSP24_MASK_RX_NDP_PSPOLL_MASK                           = 0x00800000,
          MAC_REG_RSP24_RSP24_MASK_RX_PV0_TYPE                                  = MAC_REG_RSP24,
          MAC_REG_RSP24_RSP24_MASK_RX_PV0_TYPE_SHIFT                            = 21,
          MAC_REG_RSP24_RSP24_MASK_RX_PV0_TYPE_MASK                             = 0x00600000,
          MAC_REG_RSP24_RSP24_MASK_RX_PV0_SUBTYPE                               = MAC_REG_RSP24,
          MAC_REG_RSP24_RSP24_MASK_RX_PV0_SUBTYPE_SHIFT                         = 17,
          MAC_REG_RSP24_RSP24_MASK_RX_PV0_SUBTYPE_MASK                          = 0x001e0000,
          MAC_REG_RSP24_RSP24_MASK_RX_PV                                        = MAC_REG_RSP24,
          MAC_REG_RSP24_RSP24_MASK_RX_PV_SHIFT                                  = 16,
          MAC_REG_RSP24_RSP24_MASK_RX_PV_MASK                                   = 0x00010000,
          MAC_REG_RSP24_RSP24_MASK_GROUP_ADDRESS                                = MAC_REG_RSP24,
          MAC_REG_RSP24_RSP24_MASK_GROUP_ADDRESS_SHIFT                          = 15,
          MAC_REG_RSP24_RSP24_MASK_GROUP_ADDRESS_MASK                           = 0x00008000,
          MAC_REG_RSP24_RSP24_MASK_OPERATION                                    = MAC_REG_RSP24,
          MAC_REG_RSP24_RSP24_MASK_OPERATION_SHIFT                              = 14,
          MAC_REG_RSP24_RSP24_MASK_OPERATION_MASK                               = 0x00004000,
          MAC_REG_RSP24_RSP24_MASK_RX_INFO_AGG                                  = MAC_REG_RSP24,
          MAC_REG_RSP24_RSP24_MASK_RX_INFO_AGG_SHIFT                            = 13,
          MAC_REG_RSP24_RSP24_MASK_RX_INFO_AGG_MASK                             = 0x00002000,
          MAC_REG_RSP24_RSP24_RX_INFO_OK                                        = MAC_REG_RSP24,
          MAC_REG_RSP24_RSP24_RX_INFO_OK_SHIFT                                  = 12,
          MAC_REG_RSP24_RSP24_RX_INFO_OK_MASK                                   = 0x00001000,
          MAC_REG_RSP24_RSP24_RX_INFO_NDP                                       = MAC_REG_RSP24,
          MAC_REG_RSP24_RSP24_RX_INFO_NDP_SHIFT                                 = 11,
          MAC_REG_RSP24_RSP24_RX_INFO_NDP_MASK                                  = 0x00000800,
          MAC_REG_RSP24_RSP24_RX_NDP_PSPOLL                                     = MAC_REG_RSP24,
          MAC_REG_RSP24_RSP24_RX_NDP_PSPOLL_SHIFT                               = 10,
          MAC_REG_RSP24_RSP24_RX_NDP_PSPOLL_MASK                                = 0x00000400,
          MAC_REG_RSP24_RSP24_RX_PV0_TYPE                                       = MAC_REG_RSP24,
          MAC_REG_RSP24_RSP24_RX_PV0_TYPE_SHIFT                                 = 8,
          MAC_REG_RSP24_RSP24_RX_PV0_TYPE_MASK                                  = 0x00000300,
          MAC_REG_RSP24_RSP24_RX_PV0_SUBTYPE                                    = MAC_REG_RSP24,
          MAC_REG_RSP24_RSP24_RX_PV0_SUBTYPE_SHIFT                              = 4,
          MAC_REG_RSP24_RSP24_RX_PV0_SUBTYPE_MASK                               = 0x000000f0,
          MAC_REG_RSP24_RSP24_RX_PV                                             = MAC_REG_RSP24,
          MAC_REG_RSP24_RSP24_RX_PV_SHIFT                                       = 3,
          MAC_REG_RSP24_RSP24_RX_PV_MASK                                        = 0x00000008,
          MAC_REG_RSP24_RSP24_GROUP_ADDRESS                                     = MAC_REG_RSP24,
          MAC_REG_RSP24_RSP24_GROUP_ADDRESS_SHIFT                               = 2,
          MAC_REG_RSP24_RSP24_GROUP_ADDRESS_MASK                                = 0x00000004,
          MAC_REG_RSP24_RSP24_OPERATION                                         = MAC_REG_RSP24,
          MAC_REG_RSP24_RSP24_OPERATION_SHIFT                                   = 1,
          MAC_REG_RSP24_RSP24_OPERATION_MASK                                    = 0x00000002,
          MAC_REG_RSP24_RSP24_RX_INFO_AGG                                       = MAC_REG_RSP24,
          MAC_REG_RSP24_RSP24_RX_INFO_AGG_SHIFT                                 = 0,
          MAC_REG_RSP24_RSP24_RX_INFO_AGG_MASK                                  = 0x00000001,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RSP25                                                               = 0x40080128,
//-------------------------------------------------------------------------------------------------------------------------------,
          MAC_REG_RSP25_RSP25_VALID                                             = MAC_REG_RSP25,
          MAC_REG_RSP25_RSP25_VALID_SHIFT                                       = 31,
          MAC_REG_RSP25_RSP25_VALID_MASK                                        = 0x80000000,
          MAC_REG_RSP25_RSP25_CASE                                              = MAC_REG_RSP25,
          MAC_REG_RSP25_RSP25_CASE_SHIFT                                        = 26,
          MAC_REG_RSP25_RSP25_CASE_MASK                                         = 0x7c000000,
          MAC_REG_RSP25_RSP25_MASK_RX_INFO_OK                                   = MAC_REG_RSP25,
          MAC_REG_RSP25_RSP25_MASK_RX_INFO_OK_SHIFT                             = 25,
          MAC_REG_RSP25_RSP25_MASK_RX_INFO_OK_MASK                              = 0x02000000,
          MAC_REG_RSP25_RSP25_MASK_RX_INFO_NDP                                  = MAC_REG_RSP25,
          MAC_REG_RSP25_RSP25_MASK_RX_INFO_NDP_SHIFT                            = 24,
          MAC_REG_RSP25_RSP25_MASK_RX_INFO_NDP_MASK                             = 0x01000000,
          MAC_REG_RSP25_RSP25_MASK_RX_NDP_PSPOLL                                = MAC_REG_RSP25,
          MAC_REG_RSP25_RSP25_MASK_RX_NDP_PSPOLL_SHIFT                          = 23,
          MAC_REG_RSP25_RSP25_MASK_RX_NDP_PSPOLL_MASK                           = 0x00800000,
          MAC_REG_RSP25_RSP25_MASK_RX_PV0_TYPE                                  = MAC_REG_RSP25,
          MAC_REG_RSP25_RSP25_MASK_RX_PV0_TYPE_SHIFT                            = 21,
          MAC_REG_RSP25_RSP25_MASK_RX_PV0_TYPE_MASK                             = 0x00600000,
          MAC_REG_RSP25_RSP25_MASK_RX_PV0_SUBTYPE                               = MAC_REG_RSP25,
          MAC_REG_RSP25_RSP25_MASK_RX_PV0_SUBTYPE_SHIFT                         = 17,
          MAC_REG_RSP25_RSP25_MASK_RX_PV0_SUBTYPE_MASK                          = 0x001e0000,
          MAC_REG_RSP25_RSP25_MASK_RX_PV                                        = MAC_REG_RSP25,
          MAC_REG_RSP25_RSP25_MASK_RX_PV_SHIFT                                  = 16,
          MAC_REG_RSP25_RSP25_MASK_RX_PV_MASK                                   = 0x00010000,
          MAC_REG_RSP25_RSP25_MASK_GROUP_ADDRESS                                = MAC_REG_RSP25,
          MAC_REG_RSP25_RSP25_MASK_GROUP_ADDRESS_SHIFT                          = 15,
          MAC_REG_RSP25_RSP25_MASK_GROUP_ADDRESS_MASK                           = 0x00008000,
          MAC_REG_RSP25_RSP25_MASK_OPERATION                                    = MAC_REG_RSP25,
          MAC_REG_RSP25_RSP25_MASK_OPERATION_SHIFT                              = 14,
          MAC_REG_RSP25_RSP25_MASK_OPERATION_MASK                               = 0x00004000,
          MAC_REG_RSP25_RSP25_MASK_RX_INFO_AGG                                  = MAC_REG_RSP25,
          MAC_REG_RSP25_RSP25_MASK_RX_INFO_AGG_SHIFT                            = 13,
          MAC_REG_RSP25_RSP25_MASK_RX_INFO_AGG_MASK                             = 0x00002000,
          MAC_REG_RSP25_RSP25_RX_INFO_OK                                        = MAC_REG_RSP25,
          MAC_REG_RSP25_RSP25_RX_INFO_OK_SHIFT                                  = 12,
          MAC_REG_RSP25_RSP25_RX_INFO_OK_MASK                                   = 0x00001000,
          MAC_REG_RSP25_RSP25_RX_INFO_NDP                                       = MAC_REG_RSP25,
          MAC_REG_RSP25_RSP25_RX_INFO_NDP_SHIFT                                 = 11,
          MAC_REG_RSP25_RSP25_RX_INFO_NDP_MASK                                  = 0x00000800,
          MAC_REG_RSP25_RSP25_RX_NDP_PSPOLL                                     = MAC_REG_RSP25,
          MAC_REG_RSP25_RSP25_RX_NDP_PSPOLL_SHIFT                               = 10,
          MAC_REG_RSP25_RSP25_RX_NDP_PSPOLL_MASK                                = 0x00000400,
          MAC_REG_RSP25_RSP25_RX_PV0_TYPE                                       = MAC_REG_RSP25,
          MAC_REG_RSP25_RSP25_RX_PV0_TYPE_SHIFT                                 = 8,
          MAC_REG_RSP25_RSP25_RX_PV0_TYPE_MASK                                  = 0x00000300,
          MAC_REG_RSP25_RSP25_RX_PV0_SUBTYPE                                    = MAC_REG_RSP25,
          MAC_REG_RSP25_RSP25_RX_PV0_SUBTYPE_SHIFT                              = 4,
          MAC_REG_RSP25_RSP25_RX_PV0_SUBTYPE_MASK                               = 0x000000f0,
          MAC_REG_RSP25_RSP25_RX_PV                                             = MAC_REG_RSP25,
          MAC_REG_RSP25_RSP25_RX_PV_SHIFT                                       = 3,
          MAC_REG_RSP25_RSP25_RX_PV_MASK                                        = 0x00000008,
          MAC_REG_RSP25_RSP25_GROUP_ADDRESS                                     = MAC_REG_RSP25,
          MAC_REG_RSP25_RSP25_GROUP_ADDRESS_SHIFT                               = 2,
          MAC_REG_RSP25_RSP25_GROUP_ADDRESS_MASK                                = 0x00000004,
          MAC_REG_RSP25_RSP25_OPERATION                                         = MAC_REG_RSP25,
          MAC_REG_RSP25_RSP25_OPERATION_SHIFT                                   = 1,
          MAC_REG_RSP25_RSP25_OPERATION_MASK                                    = 0x00000002,
          MAC_REG_RSP25_RSP25_RX_INFO_AGG                                       = MAC_REG_RSP25,
          MAC_REG_RSP25_RSP25_RX_INFO_AGG_SHIFT                                 = 0,
          MAC_REG_RSP25_RSP25_RX_INFO_AGG_MASK                                  = 0x00000001,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RSP26                                                               = 0x4008012c,
//-------------------------------------------------------------------------------------------------------------------------------,
          MAC_REG_RSP26_RSP26_VALID                                             = MAC_REG_RSP26,
          MAC_REG_RSP26_RSP26_VALID_SHIFT                                       = 31,
          MAC_REG_RSP26_RSP26_VALID_MASK                                        = 0x80000000,
          MAC_REG_RSP26_RSP26_CASE                                              = MAC_REG_RSP26,
          MAC_REG_RSP26_RSP26_CASE_SHIFT                                        = 26,
          MAC_REG_RSP26_RSP26_CASE_MASK                                         = 0x7c000000,
          MAC_REG_RSP26_RSP26_MASK_RX_INFO_OK                                   = MAC_REG_RSP26,
          MAC_REG_RSP26_RSP26_MASK_RX_INFO_OK_SHIFT                             = 25,
          MAC_REG_RSP26_RSP26_MASK_RX_INFO_OK_MASK                              = 0x02000000,
          MAC_REG_RSP26_RSP26_MASK_RX_INFO_NDP                                  = MAC_REG_RSP26,
          MAC_REG_RSP26_RSP26_MASK_RX_INFO_NDP_SHIFT                            = 24,
          MAC_REG_RSP26_RSP26_MASK_RX_INFO_NDP_MASK                             = 0x01000000,
          MAC_REG_RSP26_RSP26_MASK_RX_NDP_PSPOLL                                = MAC_REG_RSP26,
          MAC_REG_RSP26_RSP26_MASK_RX_NDP_PSPOLL_SHIFT                          = 23,
          MAC_REG_RSP26_RSP26_MASK_RX_NDP_PSPOLL_MASK                           = 0x00800000,
          MAC_REG_RSP26_RSP26_MASK_RX_PV0_TYPE                                  = MAC_REG_RSP26,
          MAC_REG_RSP26_RSP26_MASK_RX_PV0_TYPE_SHIFT                            = 21,
          MAC_REG_RSP26_RSP26_MASK_RX_PV0_TYPE_MASK                             = 0x00600000,
          MAC_REG_RSP26_RSP26_MASK_RX_PV0_SUBTYPE                               = MAC_REG_RSP26,
          MAC_REG_RSP26_RSP26_MASK_RX_PV0_SUBTYPE_SHIFT                         = 17,
          MAC_REG_RSP26_RSP26_MASK_RX_PV0_SUBTYPE_MASK                          = 0x001e0000,
          MAC_REG_RSP26_RSP26_MASK_RX_PV                                        = MAC_REG_RSP26,
          MAC_REG_RSP26_RSP26_MASK_RX_PV_SHIFT                                  = 16,
          MAC_REG_RSP26_RSP26_MASK_RX_PV_MASK                                   = 0x00010000,
          MAC_REG_RSP26_RSP26_MASK_GROUP_ADDRESS                                = MAC_REG_RSP26,
          MAC_REG_RSP26_RSP26_MASK_GROUP_ADDRESS_SHIFT                          = 15,
          MAC_REG_RSP26_RSP26_MASK_GROUP_ADDRESS_MASK                           = 0x00008000,
          MAC_REG_RSP26_RSP26_MASK_OPERATION                                    = MAC_REG_RSP26,
          MAC_REG_RSP26_RSP26_MASK_OPERATION_SHIFT                              = 14,
          MAC_REG_RSP26_RSP26_MASK_OPERATION_MASK                               = 0x00004000,
          MAC_REG_RSP26_RSP26_MASK_RX_INFO_AGG                                  = MAC_REG_RSP26,
          MAC_REG_RSP26_RSP26_MASK_RX_INFO_AGG_SHIFT                            = 13,
          MAC_REG_RSP26_RSP26_MASK_RX_INFO_AGG_MASK                             = 0x00002000,
          MAC_REG_RSP26_RSP26_RX_INFO_OK                                        = MAC_REG_RSP26,
          MAC_REG_RSP26_RSP26_RX_INFO_OK_SHIFT                                  = 12,
          MAC_REG_RSP26_RSP26_RX_INFO_OK_MASK                                   = 0x00001000,
          MAC_REG_RSP26_RSP26_RX_INFO_NDP                                       = MAC_REG_RSP26,
          MAC_REG_RSP26_RSP26_RX_INFO_NDP_SHIFT                                 = 11,
          MAC_REG_RSP26_RSP26_RX_INFO_NDP_MASK                                  = 0x00000800,
          MAC_REG_RSP26_RSP26_RX_NDP_PSPOLL                                     = MAC_REG_RSP26,
          MAC_REG_RSP26_RSP26_RX_NDP_PSPOLL_SHIFT                               = 10,
          MAC_REG_RSP26_RSP26_RX_NDP_PSPOLL_MASK                                = 0x00000400,
          MAC_REG_RSP26_RSP26_RX_PV0_TYPE                                       = MAC_REG_RSP26,
          MAC_REG_RSP26_RSP26_RX_PV0_TYPE_SHIFT                                 = 8,
          MAC_REG_RSP26_RSP26_RX_PV0_TYPE_MASK                                  = 0x00000300,
          MAC_REG_RSP26_RSP26_RX_PV0_SUBTYPE                                    = MAC_REG_RSP26,
          MAC_REG_RSP26_RSP26_RX_PV0_SUBTYPE_SHIFT                              = 4,
          MAC_REG_RSP26_RSP26_RX_PV0_SUBTYPE_MASK                               = 0x000000f0,
          MAC_REG_RSP26_RSP26_RX_PV                                             = MAC_REG_RSP26,
          MAC_REG_RSP26_RSP26_RX_PV_SHIFT                                       = 3,
          MAC_REG_RSP26_RSP26_RX_PV_MASK                                        = 0x00000008,
          MAC_REG_RSP26_RSP26_GROUP_ADDRESS                                     = MAC_REG_RSP26,
          MAC_REG_RSP26_RSP26_GROUP_ADDRESS_SHIFT                               = 2,
          MAC_REG_RSP26_RSP26_GROUP_ADDRESS_MASK                                = 0x00000004,
          MAC_REG_RSP26_RSP26_OPERATION                                         = MAC_REG_RSP26,
          MAC_REG_RSP26_RSP26_OPERATION_SHIFT                                   = 1,
          MAC_REG_RSP26_RSP26_OPERATION_MASK                                    = 0x00000002,
          MAC_REG_RSP26_RSP26_RX_INFO_AGG                                       = MAC_REG_RSP26,
          MAC_REG_RSP26_RSP26_RX_INFO_AGG_SHIFT                                 = 0,
          MAC_REG_RSP26_RSP26_RX_INFO_AGG_MASK                                  = 0x00000001,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RSP27                                                               = 0x40080130,
//-------------------------------------------------------------------------------------------------------------------------------,
          MAC_REG_RSP27_RSP27_VALID                                             = MAC_REG_RSP27,
          MAC_REG_RSP27_RSP27_VALID_SHIFT                                       = 31,
          MAC_REG_RSP27_RSP27_VALID_MASK                                        = 0x80000000,
          MAC_REG_RSP27_RSP27_CASE                                              = MAC_REG_RSP27,
          MAC_REG_RSP27_RSP27_CASE_SHIFT                                        = 26,
          MAC_REG_RSP27_RSP27_CASE_MASK                                         = 0x7c000000,
          MAC_REG_RSP27_RSP27_MASK_RX_INFO_OK                                   = MAC_REG_RSP27,
          MAC_REG_RSP27_RSP27_MASK_RX_INFO_OK_SHIFT                             = 25,
          MAC_REG_RSP27_RSP27_MASK_RX_INFO_OK_MASK                              = 0x02000000,
          MAC_REG_RSP27_RSP27_MASK_RX_INFO_NDP                                  = MAC_REG_RSP27,
          MAC_REG_RSP27_RSP27_MASK_RX_INFO_NDP_SHIFT                            = 24,
          MAC_REG_RSP27_RSP27_MASK_RX_INFO_NDP_MASK                             = 0x01000000,
          MAC_REG_RSP27_RSP27_MASK_RX_NDP_PSPOLL                                = MAC_REG_RSP27,
          MAC_REG_RSP27_RSP27_MASK_RX_NDP_PSPOLL_SHIFT                          = 23,
          MAC_REG_RSP27_RSP27_MASK_RX_NDP_PSPOLL_MASK                           = 0x00800000,
          MAC_REG_RSP27_RSP27_MASK_RX_PV0_TYPE                                  = MAC_REG_RSP27,
          MAC_REG_RSP27_RSP27_MASK_RX_PV0_TYPE_SHIFT                            = 21,
          MAC_REG_RSP27_RSP27_MASK_RX_PV0_TYPE_MASK                             = 0x00600000,
          MAC_REG_RSP27_RSP27_MASK_RX_PV0_SUBTYPE                               = MAC_REG_RSP27,
          MAC_REG_RSP27_RSP27_MASK_RX_PV0_SUBTYPE_SHIFT                         = 17,
          MAC_REG_RSP27_RSP27_MASK_RX_PV0_SUBTYPE_MASK                          = 0x001e0000,
          MAC_REG_RSP27_RSP27_MASK_RX_PV                                        = MAC_REG_RSP27,
          MAC_REG_RSP27_RSP27_MASK_RX_PV_SHIFT                                  = 16,
          MAC_REG_RSP27_RSP27_MASK_RX_PV_MASK                                   = 0x00010000,
          MAC_REG_RSP27_RSP27_MASK_GROUP_ADDRESS                                = MAC_REG_RSP27,
          MAC_REG_RSP27_RSP27_MASK_GROUP_ADDRESS_SHIFT                          = 15,
          MAC_REG_RSP27_RSP27_MASK_GROUP_ADDRESS_MASK                           = 0x00008000,
          MAC_REG_RSP27_RSP27_MASK_OPERATION                                    = MAC_REG_RSP27,
          MAC_REG_RSP27_RSP27_MASK_OPERATION_SHIFT                              = 14,
          MAC_REG_RSP27_RSP27_MASK_OPERATION_MASK                               = 0x00004000,
          MAC_REG_RSP27_RSP27_MASK_RX_INFO_AGG                                  = MAC_REG_RSP27,
          MAC_REG_RSP27_RSP27_MASK_RX_INFO_AGG_SHIFT                            = 13,
          MAC_REG_RSP27_RSP27_MASK_RX_INFO_AGG_MASK                             = 0x00002000,
          MAC_REG_RSP27_RSP27_RX_INFO_OK                                        = MAC_REG_RSP27,
          MAC_REG_RSP27_RSP27_RX_INFO_OK_SHIFT                                  = 12,
          MAC_REG_RSP27_RSP27_RX_INFO_OK_MASK                                   = 0x00001000,
          MAC_REG_RSP27_RSP27_RX_INFO_NDP                                       = MAC_REG_RSP27,
          MAC_REG_RSP27_RSP27_RX_INFO_NDP_SHIFT                                 = 11,
          MAC_REG_RSP27_RSP27_RX_INFO_NDP_MASK                                  = 0x00000800,
          MAC_REG_RSP27_RSP27_RX_NDP_PSPOLL                                     = MAC_REG_RSP27,
          MAC_REG_RSP27_RSP27_RX_NDP_PSPOLL_SHIFT                               = 10,
          MAC_REG_RSP27_RSP27_RX_NDP_PSPOLL_MASK                                = 0x00000400,
          MAC_REG_RSP27_RSP27_RX_PV0_TYPE                                       = MAC_REG_RSP27,
          MAC_REG_RSP27_RSP27_RX_PV0_TYPE_SHIFT                                 = 8,
          MAC_REG_RSP27_RSP27_RX_PV0_TYPE_MASK                                  = 0x00000300,
          MAC_REG_RSP27_RSP27_RX_PV0_SUBTYPE                                    = MAC_REG_RSP27,
          MAC_REG_RSP27_RSP27_RX_PV0_SUBTYPE_SHIFT                              = 4,
          MAC_REG_RSP27_RSP27_RX_PV0_SUBTYPE_MASK                               = 0x000000f0,
          MAC_REG_RSP27_RSP27_RX_PV                                             = MAC_REG_RSP27,
          MAC_REG_RSP27_RSP27_RX_PV_SHIFT                                       = 3,
          MAC_REG_RSP27_RSP27_RX_PV_MASK                                        = 0x00000008,
          MAC_REG_RSP27_RSP27_GROUP_ADDRESS                                     = MAC_REG_RSP27,
          MAC_REG_RSP27_RSP27_GROUP_ADDRESS_SHIFT                               = 2,
          MAC_REG_RSP27_RSP27_GROUP_ADDRESS_MASK                                = 0x00000004,
          MAC_REG_RSP27_RSP27_OPERATION                                         = MAC_REG_RSP27,
          MAC_REG_RSP27_RSP27_OPERATION_SHIFT                                   = 1,
          MAC_REG_RSP27_RSP27_OPERATION_MASK                                    = 0x00000002,
          MAC_REG_RSP27_RSP27_RX_INFO_AGG                                       = MAC_REG_RSP27,
          MAC_REG_RSP27_RSP27_RX_INFO_AGG_SHIFT                                 = 0,
          MAC_REG_RSP27_RSP27_RX_INFO_AGG_MASK                                  = 0x00000001,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RSP28                                                               = 0x40080134,
//-------------------------------------------------------------------------------------------------------------------------------,
          MAC_REG_RSP28_RSP28_VALID                                             = MAC_REG_RSP28,
          MAC_REG_RSP28_RSP28_VALID_SHIFT                                       = 31,
          MAC_REG_RSP28_RSP28_VALID_MASK                                        = 0x80000000,
          MAC_REG_RSP28_RSP28_CASE                                              = MAC_REG_RSP28,
          MAC_REG_RSP28_RSP28_CASE_SHIFT                                        = 26,
          MAC_REG_RSP28_RSP28_CASE_MASK                                         = 0x7c000000,
          MAC_REG_RSP28_RSP28_MASK_RX_INFO_OK                                   = MAC_REG_RSP28,
          MAC_REG_RSP28_RSP28_MASK_RX_INFO_OK_SHIFT                             = 25,
          MAC_REG_RSP28_RSP28_MASK_RX_INFO_OK_MASK                              = 0x02000000,
          MAC_REG_RSP28_RSP28_MASK_RX_INFO_NDP                                  = MAC_REG_RSP28,
          MAC_REG_RSP28_RSP28_MASK_RX_INFO_NDP_SHIFT                            = 24,
          MAC_REG_RSP28_RSP28_MASK_RX_INFO_NDP_MASK                             = 0x01000000,
          MAC_REG_RSP28_RSP28_MASK_RX_NDP_PSPOLL                                = MAC_REG_RSP28,
          MAC_REG_RSP28_RSP28_MASK_RX_NDP_PSPOLL_SHIFT                          = 23,
          MAC_REG_RSP28_RSP28_MASK_RX_NDP_PSPOLL_MASK                           = 0x00800000,
          MAC_REG_RSP28_RSP28_MASK_RX_PV0_TYPE                                  = MAC_REG_RSP28,
          MAC_REG_RSP28_RSP28_MASK_RX_PV0_TYPE_SHIFT                            = 21,
          MAC_REG_RSP28_RSP28_MASK_RX_PV0_TYPE_MASK                             = 0x00600000,
          MAC_REG_RSP28_RSP28_MASK_RX_PV0_SUBTYPE                               = MAC_REG_RSP28,
          MAC_REG_RSP28_RSP28_MASK_RX_PV0_SUBTYPE_SHIFT                         = 17,
          MAC_REG_RSP28_RSP28_MASK_RX_PV0_SUBTYPE_MASK                          = 0x001e0000,
          MAC_REG_RSP28_RSP28_MASK_RX_PV                                        = MAC_REG_RSP28,
          MAC_REG_RSP28_RSP28_MASK_RX_PV_SHIFT                                  = 16,
          MAC_REG_RSP28_RSP28_MASK_RX_PV_MASK                                   = 0x00010000,
          MAC_REG_RSP28_RSP28_MASK_GROUP_ADDRESS                                = MAC_REG_RSP28,
          MAC_REG_RSP28_RSP28_MASK_GROUP_ADDRESS_SHIFT                          = 15,
          MAC_REG_RSP28_RSP28_MASK_GROUP_ADDRESS_MASK                           = 0x00008000,
          MAC_REG_RSP28_RSP28_MASK_OPERATION                                    = MAC_REG_RSP28,
          MAC_REG_RSP28_RSP28_MASK_OPERATION_SHIFT                              = 14,
          MAC_REG_RSP28_RSP28_MASK_OPERATION_MASK                               = 0x00004000,
          MAC_REG_RSP28_RSP28_MASK_RX_INFO_AGG                                  = MAC_REG_RSP28,
          MAC_REG_RSP28_RSP28_MASK_RX_INFO_AGG_SHIFT                            = 13,
          MAC_REG_RSP28_RSP28_MASK_RX_INFO_AGG_MASK                             = 0x00002000,
          MAC_REG_RSP28_RSP28_RX_INFO_OK                                        = MAC_REG_RSP28,
          MAC_REG_RSP28_RSP28_RX_INFO_OK_SHIFT                                  = 12,
          MAC_REG_RSP28_RSP28_RX_INFO_OK_MASK                                   = 0x00001000,
          MAC_REG_RSP28_RSP28_RX_INFO_NDP                                       = MAC_REG_RSP28,
          MAC_REG_RSP28_RSP28_RX_INFO_NDP_SHIFT                                 = 11,
          MAC_REG_RSP28_RSP28_RX_INFO_NDP_MASK                                  = 0x00000800,
          MAC_REG_RSP28_RSP28_RX_NDP_PSPOLL                                     = MAC_REG_RSP28,
          MAC_REG_RSP28_RSP28_RX_NDP_PSPOLL_SHIFT                               = 10,
          MAC_REG_RSP28_RSP28_RX_NDP_PSPOLL_MASK                                = 0x00000400,
          MAC_REG_RSP28_RSP28_RX_PV0_TYPE                                       = MAC_REG_RSP28,
          MAC_REG_RSP28_RSP28_RX_PV0_TYPE_SHIFT                                 = 8,
          MAC_REG_RSP28_RSP28_RX_PV0_TYPE_MASK                                  = 0x00000300,
          MAC_REG_RSP28_RSP28_RX_PV0_SUBTYPE                                    = MAC_REG_RSP28,
          MAC_REG_RSP28_RSP28_RX_PV0_SUBTYPE_SHIFT                              = 4,
          MAC_REG_RSP28_RSP28_RX_PV0_SUBTYPE_MASK                               = 0x000000f0,
          MAC_REG_RSP28_RSP28_RX_PV                                             = MAC_REG_RSP28,
          MAC_REG_RSP28_RSP28_RX_PV_SHIFT                                       = 3,
          MAC_REG_RSP28_RSP28_RX_PV_MASK                                        = 0x00000008,
          MAC_REG_RSP28_RSP28_GROUP_ADDRESS                                     = MAC_REG_RSP28,
          MAC_REG_RSP28_RSP28_GROUP_ADDRESS_SHIFT                               = 2,
          MAC_REG_RSP28_RSP28_GROUP_ADDRESS_MASK                                = 0x00000004,
          MAC_REG_RSP28_RSP28_OPERATION                                         = MAC_REG_RSP28,
          MAC_REG_RSP28_RSP28_OPERATION_SHIFT                                   = 1,
          MAC_REG_RSP28_RSP28_OPERATION_MASK                                    = 0x00000002,
          MAC_REG_RSP28_RSP28_RX_INFO_AGG                                       = MAC_REG_RSP28,
          MAC_REG_RSP28_RSP28_RX_INFO_AGG_SHIFT                                 = 0,
          MAC_REG_RSP28_RSP28_RX_INFO_AGG_MASK                                  = 0x00000001,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RSP29                                                               = 0x40080138,
//-------------------------------------------------------------------------------------------------------------------------------,
          MAC_REG_RSP29_RSP29_VALID                                             = MAC_REG_RSP29,
          MAC_REG_RSP29_RSP29_VALID_SHIFT                                       = 31,
          MAC_REG_RSP29_RSP29_VALID_MASK                                        = 0x80000000,
          MAC_REG_RSP29_RSP29_CASE                                              = MAC_REG_RSP29,
          MAC_REG_RSP29_RSP29_CASE_SHIFT                                        = 26,
          MAC_REG_RSP29_RSP29_CASE_MASK                                         = 0x7c000000,
          MAC_REG_RSP29_RSP29_MASK_RX_INFO_OK                                   = MAC_REG_RSP29,
          MAC_REG_RSP29_RSP29_MASK_RX_INFO_OK_SHIFT                             = 25,
          MAC_REG_RSP29_RSP29_MASK_RX_INFO_OK_MASK                              = 0x02000000,
          MAC_REG_RSP29_RSP29_MASK_RX_INFO_NDP                                  = MAC_REG_RSP29,
          MAC_REG_RSP29_RSP29_MASK_RX_INFO_NDP_SHIFT                            = 24,
          MAC_REG_RSP29_RSP29_MASK_RX_INFO_NDP_MASK                             = 0x01000000,
          MAC_REG_RSP29_RSP29_MASK_RX_NDP_PSPOLL                                = MAC_REG_RSP29,
          MAC_REG_RSP29_RSP29_MASK_RX_NDP_PSPOLL_SHIFT                          = 23,
          MAC_REG_RSP29_RSP29_MASK_RX_NDP_PSPOLL_MASK                           = 0x00800000,
          MAC_REG_RSP29_RSP29_MASK_RX_PV0_TYPE                                  = MAC_REG_RSP29,
          MAC_REG_RSP29_RSP29_MASK_RX_PV0_TYPE_SHIFT                            = 21,
          MAC_REG_RSP29_RSP29_MASK_RX_PV0_TYPE_MASK                             = 0x00600000,
          MAC_REG_RSP29_RSP29_MASK_RX_PV0_SUBTYPE                               = MAC_REG_RSP29,
          MAC_REG_RSP29_RSP29_MASK_RX_PV0_SUBTYPE_SHIFT                         = 17,
          MAC_REG_RSP29_RSP29_MASK_RX_PV0_SUBTYPE_MASK                          = 0x001e0000,
          MAC_REG_RSP29_RSP29_MASK_RX_PV                                        = MAC_REG_RSP29,
          MAC_REG_RSP29_RSP29_MASK_RX_PV_SHIFT                                  = 16,
          MAC_REG_RSP29_RSP29_MASK_RX_PV_MASK                                   = 0x00010000,
          MAC_REG_RSP29_RSP29_MASK_GROUP_ADDRESS                                = MAC_REG_RSP29,
          MAC_REG_RSP29_RSP29_MASK_GROUP_ADDRESS_SHIFT                          = 15,
          MAC_REG_RSP29_RSP29_MASK_GROUP_ADDRESS_MASK                           = 0x00008000,
          MAC_REG_RSP29_RSP29_MASK_OPERATION                                    = MAC_REG_RSP29,
          MAC_REG_RSP29_RSP29_MASK_OPERATION_SHIFT                              = 14,
          MAC_REG_RSP29_RSP29_MASK_OPERATION_MASK                               = 0x00004000,
          MAC_REG_RSP29_RSP29_MASK_RX_INFO_AGG                                  = MAC_REG_RSP29,
          MAC_REG_RSP29_RSP29_MASK_RX_INFO_AGG_SHIFT                            = 13,
          MAC_REG_RSP29_RSP29_MASK_RX_INFO_AGG_MASK                             = 0x00002000,
          MAC_REG_RSP29_RSP29_RX_INFO_OK                                        = MAC_REG_RSP29,
          MAC_REG_RSP29_RSP29_RX_INFO_OK_SHIFT                                  = 12,
          MAC_REG_RSP29_RSP29_RX_INFO_OK_MASK                                   = 0x00001000,
          MAC_REG_RSP29_RSP29_RX_INFO_NDP                                       = MAC_REG_RSP29,
          MAC_REG_RSP29_RSP29_RX_INFO_NDP_SHIFT                                 = 11,
          MAC_REG_RSP29_RSP29_RX_INFO_NDP_MASK                                  = 0x00000800,
          MAC_REG_RSP29_RSP29_RX_NDP_PSPOLL                                     = MAC_REG_RSP29,
          MAC_REG_RSP29_RSP29_RX_NDP_PSPOLL_SHIFT                               = 10,
          MAC_REG_RSP29_RSP29_RX_NDP_PSPOLL_MASK                                = 0x00000400,
          MAC_REG_RSP29_RSP29_RX_PV0_TYPE                                       = MAC_REG_RSP29,
          MAC_REG_RSP29_RSP29_RX_PV0_TYPE_SHIFT                                 = 8,
          MAC_REG_RSP29_RSP29_RX_PV0_TYPE_MASK                                  = 0x00000300,
          MAC_REG_RSP29_RSP29_RX_PV0_SUBTYPE                                    = MAC_REG_RSP29,
          MAC_REG_RSP29_RSP29_RX_PV0_SUBTYPE_SHIFT                              = 4,
          MAC_REG_RSP29_RSP29_RX_PV0_SUBTYPE_MASK                               = 0x000000f0,
          MAC_REG_RSP29_RSP29_RX_PV                                             = MAC_REG_RSP29,
          MAC_REG_RSP29_RSP29_RX_PV_SHIFT                                       = 3,
          MAC_REG_RSP29_RSP29_RX_PV_MASK                                        = 0x00000008,
          MAC_REG_RSP29_RSP29_GROUP_ADDRESS                                     = MAC_REG_RSP29,
          MAC_REG_RSP29_RSP29_GROUP_ADDRESS_SHIFT                               = 2,
          MAC_REG_RSP29_RSP29_GROUP_ADDRESS_MASK                                = 0x00000004,
          MAC_REG_RSP29_RSP29_OPERATION                                         = MAC_REG_RSP29,
          MAC_REG_RSP29_RSP29_OPERATION_SHIFT                                   = 1,
          MAC_REG_RSP29_RSP29_OPERATION_MASK                                    = 0x00000002,
          MAC_REG_RSP29_RSP29_RX_INFO_AGG                                       = MAC_REG_RSP29,
          MAC_REG_RSP29_RSP29_RX_INFO_AGG_SHIFT                                 = 0,
          MAC_REG_RSP29_RSP29_RX_INFO_AGG_MASK                                  = 0x00000001,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RSP30                                                               = 0x4008013c,
//-------------------------------------------------------------------------------------------------------------------------------,
          MAC_REG_RSP30_RSP30_VALID                                             = MAC_REG_RSP30,
          MAC_REG_RSP30_RSP30_VALID_SHIFT                                       = 31,
          MAC_REG_RSP30_RSP30_VALID_MASK                                        = 0x80000000,
          MAC_REG_RSP30_RSP30_CASE                                              = MAC_REG_RSP30,
          MAC_REG_RSP30_RSP30_CASE_SHIFT                                        = 26,
          MAC_REG_RSP30_RSP30_CASE_MASK                                         = 0x7c000000,
          MAC_REG_RSP30_RSP30_MASK_RX_INFO_OK                                   = MAC_REG_RSP30,
          MAC_REG_RSP30_RSP30_MASK_RX_INFO_OK_SHIFT                             = 25,
          MAC_REG_RSP30_RSP30_MASK_RX_INFO_OK_MASK                              = 0x02000000,
          MAC_REG_RSP30_RSP30_MASK_RX_INFO_NDP                                  = MAC_REG_RSP30,
          MAC_REG_RSP30_RSP30_MASK_RX_INFO_NDP_SHIFT                            = 24,
          MAC_REG_RSP30_RSP30_MASK_RX_INFO_NDP_MASK                             = 0x01000000,
          MAC_REG_RSP30_RSP30_MASK_RX_NDP_PSPOLL                                = MAC_REG_RSP30,
          MAC_REG_RSP30_RSP30_MASK_RX_NDP_PSPOLL_SHIFT                          = 23,
          MAC_REG_RSP30_RSP30_MASK_RX_NDP_PSPOLL_MASK                           = 0x00800000,
          MAC_REG_RSP30_RSP30_MASK_RX_PV0_TYPE                                  = MAC_REG_RSP30,
          MAC_REG_RSP30_RSP30_MASK_RX_PV0_TYPE_SHIFT                            = 21,
          MAC_REG_RSP30_RSP30_MASK_RX_PV0_TYPE_MASK                             = 0x00600000,
          MAC_REG_RSP30_RSP30_MASK_RX_PV0_SUBTYPE                               = MAC_REG_RSP30,
          MAC_REG_RSP30_RSP30_MASK_RX_PV0_SUBTYPE_SHIFT                         = 17,
          MAC_REG_RSP30_RSP30_MASK_RX_PV0_SUBTYPE_MASK                          = 0x001e0000,
          MAC_REG_RSP30_RSP30_MASK_RX_PV                                        = MAC_REG_RSP30,
          MAC_REG_RSP30_RSP30_MASK_RX_PV_SHIFT                                  = 16,
          MAC_REG_RSP30_RSP30_MASK_RX_PV_MASK                                   = 0x00010000,
          MAC_REG_RSP30_RSP30_MASK_GROUP_ADDRESS                                = MAC_REG_RSP30,
          MAC_REG_RSP30_RSP30_MASK_GROUP_ADDRESS_SHIFT                          = 15,
          MAC_REG_RSP30_RSP30_MASK_GROUP_ADDRESS_MASK                           = 0x00008000,
          MAC_REG_RSP30_RSP30_MASK_OPERATION                                    = MAC_REG_RSP30,
          MAC_REG_RSP30_RSP30_MASK_OPERATION_SHIFT                              = 14,
          MAC_REG_RSP30_RSP30_MASK_OPERATION_MASK                               = 0x00004000,
          MAC_REG_RSP30_RSP30_MASK_RX_INFO_AGG                                  = MAC_REG_RSP30,
          MAC_REG_RSP30_RSP30_MASK_RX_INFO_AGG_SHIFT                            = 13,
          MAC_REG_RSP30_RSP30_MASK_RX_INFO_AGG_MASK                             = 0x00002000,
          MAC_REG_RSP30_RSP30_RX_INFO_OK                                        = MAC_REG_RSP30,
          MAC_REG_RSP30_RSP30_RX_INFO_OK_SHIFT                                  = 12,
          MAC_REG_RSP30_RSP30_RX_INFO_OK_MASK                                   = 0x00001000,
          MAC_REG_RSP30_RSP30_RX_INFO_NDP                                       = MAC_REG_RSP30,
          MAC_REG_RSP30_RSP30_RX_INFO_NDP_SHIFT                                 = 11,
          MAC_REG_RSP30_RSP30_RX_INFO_NDP_MASK                                  = 0x00000800,
          MAC_REG_RSP30_RSP30_RX_NDP_PSPOLL                                     = MAC_REG_RSP30,
          MAC_REG_RSP30_RSP30_RX_NDP_PSPOLL_SHIFT                               = 10,
          MAC_REG_RSP30_RSP30_RX_NDP_PSPOLL_MASK                                = 0x00000400,
          MAC_REG_RSP30_RSP30_RX_PV0_TYPE                                       = MAC_REG_RSP30,
          MAC_REG_RSP30_RSP30_RX_PV0_TYPE_SHIFT                                 = 8,
          MAC_REG_RSP30_RSP30_RX_PV0_TYPE_MASK                                  = 0x00000300,
          MAC_REG_RSP30_RSP30_RX_PV0_SUBTYPE                                    = MAC_REG_RSP30,
          MAC_REG_RSP30_RSP30_RX_PV0_SUBTYPE_SHIFT                              = 4,
          MAC_REG_RSP30_RSP30_RX_PV0_SUBTYPE_MASK                               = 0x000000f0,
          MAC_REG_RSP30_RSP30_RX_PV                                             = MAC_REG_RSP30,
          MAC_REG_RSP30_RSP30_RX_PV_SHIFT                                       = 3,
          MAC_REG_RSP30_RSP30_RX_PV_MASK                                        = 0x00000008,
          MAC_REG_RSP30_RSP30_GROUP_ADDRESS                                     = MAC_REG_RSP30,
          MAC_REG_RSP30_RSP30_GROUP_ADDRESS_SHIFT                               = 2,
          MAC_REG_RSP30_RSP30_GROUP_ADDRESS_MASK                                = 0x00000004,
          MAC_REG_RSP30_RSP30_OPERATION                                         = MAC_REG_RSP30,
          MAC_REG_RSP30_RSP30_OPERATION_SHIFT                                   = 1,
          MAC_REG_RSP30_RSP30_OPERATION_MASK                                    = 0x00000002,
          MAC_REG_RSP30_RSP30_RX_INFO_AGG                                       = MAC_REG_RSP30,
          MAC_REG_RSP30_RSP30_RX_INFO_AGG_SHIFT                                 = 0,
          MAC_REG_RSP30_RSP30_RX_INFO_AGG_MASK                                  = 0x00000001,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RSP31                                                               = 0x40080140,
//-------------------------------------------------------------------------------------------------------------------------------,
          MAC_REG_RSP31_RSP31_VALID                                             = MAC_REG_RSP31,
          MAC_REG_RSP31_RSP31_VALID_SHIFT                                       = 31,
          MAC_REG_RSP31_RSP31_VALID_MASK                                        = 0x80000000,
          MAC_REG_RSP31_RSP31_CASE                                              = MAC_REG_RSP31,
          MAC_REG_RSP31_RSP31_CASE_SHIFT                                        = 26,
          MAC_REG_RSP31_RSP31_CASE_MASK                                         = 0x7c000000,
          MAC_REG_RSP31_RSP31_MASK_RX_INFO_OK                                   = MAC_REG_RSP31,
          MAC_REG_RSP31_RSP31_MASK_RX_INFO_OK_SHIFT                             = 25,
          MAC_REG_RSP31_RSP31_MASK_RX_INFO_OK_MASK                              = 0x02000000,
          MAC_REG_RSP31_RSP31_MASK_RX_INFO_NDP                                  = MAC_REG_RSP31,
          MAC_REG_RSP31_RSP31_MASK_RX_INFO_NDP_SHIFT                            = 24,
          MAC_REG_RSP31_RSP31_MASK_RX_INFO_NDP_MASK                             = 0x01000000,
          MAC_REG_RSP31_RSP31_MASK_RX_NDP_PSPOLL                                = MAC_REG_RSP31,
          MAC_REG_RSP31_RSP31_MASK_RX_NDP_PSPOLL_SHIFT                          = 23,
          MAC_REG_RSP31_RSP31_MASK_RX_NDP_PSPOLL_MASK                           = 0x00800000,
          MAC_REG_RSP31_RSP31_MASK_RX_PV0_TYPE                                  = MAC_REG_RSP31,
          MAC_REG_RSP31_RSP31_MASK_RX_PV0_TYPE_SHIFT                            = 21,
          MAC_REG_RSP31_RSP31_MASK_RX_PV0_TYPE_MASK                             = 0x00600000,
          MAC_REG_RSP31_RSP31_MASK_RX_PV0_SUBTYPE                               = MAC_REG_RSP31,
          MAC_REG_RSP31_RSP31_MASK_RX_PV0_SUBTYPE_SHIFT                         = 17,
          MAC_REG_RSP31_RSP31_MASK_RX_PV0_SUBTYPE_MASK                          = 0x001e0000,
          MAC_REG_RSP31_RSP31_MASK_RX_PV                                        = MAC_REG_RSP31,
          MAC_REG_RSP31_RSP31_MASK_RX_PV_SHIFT                                  = 16,
          MAC_REG_RSP31_RSP31_MASK_RX_PV_MASK                                   = 0x00010000,
          MAC_REG_RSP31_RSP31_MASK_GROUP_ADDRESS                                = MAC_REG_RSP31,
          MAC_REG_RSP31_RSP31_MASK_GROUP_ADDRESS_SHIFT                          = 15,
          MAC_REG_RSP31_RSP31_MASK_GROUP_ADDRESS_MASK                           = 0x00008000,
          MAC_REG_RSP31_RSP31_MASK_OPERATION                                    = MAC_REG_RSP31,
          MAC_REG_RSP31_RSP31_MASK_OPERATION_SHIFT                              = 14,
          MAC_REG_RSP31_RSP31_MASK_OPERATION_MASK                               = 0x00004000,
          MAC_REG_RSP31_RSP31_MASK_RX_INFO_AGG                                  = MAC_REG_RSP31,
          MAC_REG_RSP31_RSP31_MASK_RX_INFO_AGG_SHIFT                            = 13,
          MAC_REG_RSP31_RSP31_MASK_RX_INFO_AGG_MASK                             = 0x00002000,
          MAC_REG_RSP31_RSP31_RX_INFO_OK                                        = MAC_REG_RSP31,
          MAC_REG_RSP31_RSP31_RX_INFO_OK_SHIFT                                  = 12,
          MAC_REG_RSP31_RSP31_RX_INFO_OK_MASK                                   = 0x00001000,
          MAC_REG_RSP31_RSP31_RX_INFO_NDP                                       = MAC_REG_RSP31,
          MAC_REG_RSP31_RSP31_RX_INFO_NDP_SHIFT                                 = 11,
          MAC_REG_RSP31_RSP31_RX_INFO_NDP_MASK                                  = 0x00000800,
          MAC_REG_RSP31_RSP31_RX_NDP_PSPOLL                                     = MAC_REG_RSP31,
          MAC_REG_RSP31_RSP31_RX_NDP_PSPOLL_SHIFT                               = 10,
          MAC_REG_RSP31_RSP31_RX_NDP_PSPOLL_MASK                                = 0x00000400,
          MAC_REG_RSP31_RSP31_RX_PV0_TYPE                                       = MAC_REG_RSP31,
          MAC_REG_RSP31_RSP31_RX_PV0_TYPE_SHIFT                                 = 8,
          MAC_REG_RSP31_RSP31_RX_PV0_TYPE_MASK                                  = 0x00000300,
          MAC_REG_RSP31_RSP31_RX_PV0_SUBTYPE                                    = MAC_REG_RSP31,
          MAC_REG_RSP31_RSP31_RX_PV0_SUBTYPE_SHIFT                              = 4,
          MAC_REG_RSP31_RSP31_RX_PV0_SUBTYPE_MASK                               = 0x000000f0,
          MAC_REG_RSP31_RSP31_RX_PV                                             = MAC_REG_RSP31,
          MAC_REG_RSP31_RSP31_RX_PV_SHIFT                                       = 3,
          MAC_REG_RSP31_RSP31_RX_PV_MASK                                        = 0x00000008,
          MAC_REG_RSP31_RSP31_GROUP_ADDRESS                                     = MAC_REG_RSP31,
          MAC_REG_RSP31_RSP31_GROUP_ADDRESS_SHIFT                               = 2,
          MAC_REG_RSP31_RSP31_GROUP_ADDRESS_MASK                                = 0x00000004,
          MAC_REG_RSP31_RSP31_OPERATION                                         = MAC_REG_RSP31,
          MAC_REG_RSP31_RSP31_OPERATION_SHIFT                                   = 1,
          MAC_REG_RSP31_RSP31_OPERATION_MASK                                    = 0x00000002,
          MAC_REG_RSP31_RSP31_RX_INFO_AGG                                       = MAC_REG_RSP31,
          MAC_REG_RSP31_RSP31_RX_INFO_AGG_SHIFT                                 = 0,
          MAC_REG_RSP31_RSP31_RX_INFO_AGG_MASK                                  = 0x00000001,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RSP_CASE0                                                           = 0x40080144,
//-------------------------------------------------------------------------------------------------------------------------------,
          MAC_REG_RSP_CASE0_CASE0_IRQ_NO                                        = MAC_REG_RSP_CASE0,
          MAC_REG_RSP_CASE0_CASE0_IRQ_NO_SHIFT                                  = 31,
          MAC_REG_RSP_CASE0_CASE0_IRQ_NO_MASK                                   = 0x80000000,
          MAC_REG_RSP_CASE0_CASE0_CF_TYPE_NO                                    = MAC_REG_RSP_CASE0,
          MAC_REG_RSP_CASE0_CASE0_CF_TYPE_NO_SHIFT                              = 24,
          MAC_REG_RSP_CASE0_CASE0_CF_TYPE_NO_MASK                               = 0x1f000000,
          MAC_REG_RSP_CASE0_CASE0_IRQ_NDP                                       = MAC_REG_RSP_CASE0,
          MAC_REG_RSP_CASE0_CASE0_IRQ_NDP_SHIFT                                 = 23,
          MAC_REG_RSP_CASE0_CASE0_IRQ_NDP_MASK                                  = 0x00800000,
          MAC_REG_RSP_CASE0_CASE0_CF_TYPE_NDP                                   = MAC_REG_RSP_CASE0,
          MAC_REG_RSP_CASE0_CASE0_CF_TYPE_NDP_SHIFT                             = 16,
          MAC_REG_RSP_CASE0_CASE0_CF_TYPE_NDP_MASK                              = 0x001f0000,
          MAC_REG_RSP_CASE0_CASE0_IRQ_NORMAL                                    = MAC_REG_RSP_CASE0,
          MAC_REG_RSP_CASE0_CASE0_IRQ_NORMAL_SHIFT                              = 15,
          MAC_REG_RSP_CASE0_CASE0_IRQ_NORMAL_MASK                               = 0x00008000,
          MAC_REG_RSP_CASE0_CASE0_CF_TYPE_NORMAL                                = MAC_REG_RSP_CASE0,
          MAC_REG_RSP_CASE0_CASE0_CF_TYPE_NORMAL_SHIFT                          = 8,
          MAC_REG_RSP_CASE0_CASE0_CF_TYPE_NORMAL_MASK                           = 0x00001f00,
          MAC_REG_RSP_CASE0_CASE0_IRQ_LONG                                      = MAC_REG_RSP_CASE0,
          MAC_REG_RSP_CASE0_CASE0_IRQ_LONG_SHIFT                                = 7,
          MAC_REG_RSP_CASE0_CASE0_IRQ_LONG_MASK                                 = 0x00000080,
          MAC_REG_RSP_CASE0_CASE0_CF_TYPE_LONG                                  = MAC_REG_RSP_CASE0,
          MAC_REG_RSP_CASE0_CASE0_CF_TYPE_LONG_SHIFT                            = 0,
          MAC_REG_RSP_CASE0_CASE0_CF_TYPE_LONG_MASK                             = 0x0000001f,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RSP_CASE1                                                           = 0x40080148,
//-------------------------------------------------------------------------------------------------------------------------------,
          MAC_REG_RSP_CASE1_CASE1_IRQ_NO                                        = MAC_REG_RSP_CASE1,
          MAC_REG_RSP_CASE1_CASE1_IRQ_NO_SHIFT                                  = 31,
          MAC_REG_RSP_CASE1_CASE1_IRQ_NO_MASK                                   = 0x80000000,
          MAC_REG_RSP_CASE1_CASE1_CF_TYPE_NO                                    = MAC_REG_RSP_CASE1,
          MAC_REG_RSP_CASE1_CASE1_CF_TYPE_NO_SHIFT                              = 24,
          MAC_REG_RSP_CASE1_CASE1_CF_TYPE_NO_MASK                               = 0x1f000000,
          MAC_REG_RSP_CASE1_CASE1_IRQ_NDP                                       = MAC_REG_RSP_CASE1,
          MAC_REG_RSP_CASE1_CASE1_IRQ_NDP_SHIFT                                 = 23,
          MAC_REG_RSP_CASE1_CASE1_IRQ_NDP_MASK                                  = 0x00800000,
          MAC_REG_RSP_CASE1_CASE1_CF_TYPE_NDP                                   = MAC_REG_RSP_CASE1,
          MAC_REG_RSP_CASE1_CASE1_CF_TYPE_NDP_SHIFT                             = 16,
          MAC_REG_RSP_CASE1_CASE1_CF_TYPE_NDP_MASK                              = 0x001f0000,
          MAC_REG_RSP_CASE1_CASE1_IRQ_NORMAL                                    = MAC_REG_RSP_CASE1,
          MAC_REG_RSP_CASE1_CASE1_IRQ_NORMAL_SHIFT                              = 15,
          MAC_REG_RSP_CASE1_CASE1_IRQ_NORMAL_MASK                               = 0x00008000,
          MAC_REG_RSP_CASE1_CASE1_CF_TYPE_NORMAL                                = MAC_REG_RSP_CASE1,
          MAC_REG_RSP_CASE1_CASE1_CF_TYPE_NORMAL_SHIFT                          = 8,
          MAC_REG_RSP_CASE1_CASE1_CF_TYPE_NORMAL_MASK                           = 0x00001f00,
          MAC_REG_RSP_CASE1_CASE1_IRQ_LONG                                      = MAC_REG_RSP_CASE1,
          MAC_REG_RSP_CASE1_CASE1_IRQ_LONG_SHIFT                                = 7,
          MAC_REG_RSP_CASE1_CASE1_IRQ_LONG_MASK                                 = 0x00000080,
          MAC_REG_RSP_CASE1_CASE1_CF_TYPE_LONG                                  = MAC_REG_RSP_CASE1,
          MAC_REG_RSP_CASE1_CASE1_CF_TYPE_LONG_SHIFT                            = 0,
          MAC_REG_RSP_CASE1_CASE1_CF_TYPE_LONG_MASK                             = 0x0000001f,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RSP_CASE2                                                           = 0x4008014c,
//-------------------------------------------------------------------------------------------------------------------------------,
          MAC_REG_RSP_CASE2_CASE2_IRQ_NO                                        = MAC_REG_RSP_CASE2,
          MAC_REG_RSP_CASE2_CASE2_IRQ_NO_SHIFT                                  = 31,
          MAC_REG_RSP_CASE2_CASE2_IRQ_NO_MASK                                   = 0x80000000,
          MAC_REG_RSP_CASE2_CASE2_CF_TYPE_NO                                    = MAC_REG_RSP_CASE2,
          MAC_REG_RSP_CASE2_CASE2_CF_TYPE_NO_SHIFT                              = 24,
          MAC_REG_RSP_CASE2_CASE2_CF_TYPE_NO_MASK                               = 0x1f000000,
          MAC_REG_RSP_CASE2_CASE2_IRQ_NDP                                       = MAC_REG_RSP_CASE2,
          MAC_REG_RSP_CASE2_CASE2_IRQ_NDP_SHIFT                                 = 23,
          MAC_REG_RSP_CASE2_CASE2_IRQ_NDP_MASK                                  = 0x00800000,
          MAC_REG_RSP_CASE2_CASE2_CF_TYPE_NDP                                   = MAC_REG_RSP_CASE2,
          MAC_REG_RSP_CASE2_CASE2_CF_TYPE_NDP_SHIFT                             = 16,
          MAC_REG_RSP_CASE2_CASE2_CF_TYPE_NDP_MASK                              = 0x001f0000,
          MAC_REG_RSP_CASE2_CASE2_IRQ_NORMAL                                    = MAC_REG_RSP_CASE2,
          MAC_REG_RSP_CASE2_CASE2_IRQ_NORMAL_SHIFT                              = 15,
          MAC_REG_RSP_CASE2_CASE2_IRQ_NORMAL_MASK                               = 0x00008000,
          MAC_REG_RSP_CASE2_CASE2_CF_TYPE_NORMAL                                = MAC_REG_RSP_CASE2,
          MAC_REG_RSP_CASE2_CASE2_CF_TYPE_NORMAL_SHIFT                          = 8,
          MAC_REG_RSP_CASE2_CASE2_CF_TYPE_NORMAL_MASK                           = 0x00001f00,
          MAC_REG_RSP_CASE2_CASE2_IRQ_LONG                                      = MAC_REG_RSP_CASE2,
          MAC_REG_RSP_CASE2_CASE2_IRQ_LONG_SHIFT                                = 7,
          MAC_REG_RSP_CASE2_CASE2_IRQ_LONG_MASK                                 = 0x00000080,
          MAC_REG_RSP_CASE2_CASE2_CF_TYPE_LONG                                  = MAC_REG_RSP_CASE2,
          MAC_REG_RSP_CASE2_CASE2_CF_TYPE_LONG_SHIFT                            = 0,
          MAC_REG_RSP_CASE2_CASE2_CF_TYPE_LONG_MASK                             = 0x0000001f,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RSP_CASE3                                                           = 0x40080150,
//-------------------------------------------------------------------------------------------------------------------------------,
          MAC_REG_RSP_CASE3_CASE3_IRQ_NO                                        = MAC_REG_RSP_CASE3,
          MAC_REG_RSP_CASE3_CASE3_IRQ_NO_SHIFT                                  = 31,
          MAC_REG_RSP_CASE3_CASE3_IRQ_NO_MASK                                   = 0x80000000,
          MAC_REG_RSP_CASE3_CASE3_CF_TYPE_NO                                    = MAC_REG_RSP_CASE3,
          MAC_REG_RSP_CASE3_CASE3_CF_TYPE_NO_SHIFT                              = 24,
          MAC_REG_RSP_CASE3_CASE3_CF_TYPE_NO_MASK                               = 0x1f000000,
          MAC_REG_RSP_CASE3_CASE3_IRQ_NDP                                       = MAC_REG_RSP_CASE3,
          MAC_REG_RSP_CASE3_CASE3_IRQ_NDP_SHIFT                                 = 23,
          MAC_REG_RSP_CASE3_CASE3_IRQ_NDP_MASK                                  = 0x00800000,
          MAC_REG_RSP_CASE3_CASE3_CF_TYPE_NDP                                   = MAC_REG_RSP_CASE3,
          MAC_REG_RSP_CASE3_CASE3_CF_TYPE_NDP_SHIFT                             = 16,
          MAC_REG_RSP_CASE3_CASE3_CF_TYPE_NDP_MASK                              = 0x001f0000,
          MAC_REG_RSP_CASE3_CASE3_IRQ_NORMAL                                    = MAC_REG_RSP_CASE3,
          MAC_REG_RSP_CASE3_CASE3_IRQ_NORMAL_SHIFT                              = 15,
          MAC_REG_RSP_CASE3_CASE3_IRQ_NORMAL_MASK                               = 0x00008000,
          MAC_REG_RSP_CASE3_CASE3_CF_TYPE_NORMAL                                = MAC_REG_RSP_CASE3,
          MAC_REG_RSP_CASE3_CASE3_CF_TYPE_NORMAL_SHIFT                          = 8,
          MAC_REG_RSP_CASE3_CASE3_CF_TYPE_NORMAL_MASK                           = 0x00001f00,
          MAC_REG_RSP_CASE3_CASE3_IRQ_LONG                                      = MAC_REG_RSP_CASE3,
          MAC_REG_RSP_CASE3_CASE3_IRQ_LONG_SHIFT                                = 7,
          MAC_REG_RSP_CASE3_CASE3_IRQ_LONG_MASK                                 = 0x00000080,
          MAC_REG_RSP_CASE3_CASE3_CF_TYPE_LONG                                  = MAC_REG_RSP_CASE3,
          MAC_REG_RSP_CASE3_CASE3_CF_TYPE_LONG_SHIFT                            = 0,
          MAC_REG_RSP_CASE3_CASE3_CF_TYPE_LONG_MASK                             = 0x0000001f,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RSP_CASE4                                                           = 0x40080154,
//-------------------------------------------------------------------------------------------------------------------------------,
          MAC_REG_RSP_CASE4_CASE4_IRQ_NO                                        = MAC_REG_RSP_CASE4,
          MAC_REG_RSP_CASE4_CASE4_IRQ_NO_SHIFT                                  = 31,
          MAC_REG_RSP_CASE4_CASE4_IRQ_NO_MASK                                   = 0x80000000,
          MAC_REG_RSP_CASE4_CASE4_CF_TYPE_NO                                    = MAC_REG_RSP_CASE4,
          MAC_REG_RSP_CASE4_CASE4_CF_TYPE_NO_SHIFT                              = 24,
          MAC_REG_RSP_CASE4_CASE4_CF_TYPE_NO_MASK                               = 0x1f000000,
          MAC_REG_RSP_CASE4_CASE4_IRQ_NDP                                       = MAC_REG_RSP_CASE4,
          MAC_REG_RSP_CASE4_CASE4_IRQ_NDP_SHIFT                                 = 23,
          MAC_REG_RSP_CASE4_CASE4_IRQ_NDP_MASK                                  = 0x00800000,
          MAC_REG_RSP_CASE4_CASE4_CF_TYPE_NDP                                   = MAC_REG_RSP_CASE4,
          MAC_REG_RSP_CASE4_CASE4_CF_TYPE_NDP_SHIFT                             = 16,
          MAC_REG_RSP_CASE4_CASE4_CF_TYPE_NDP_MASK                              = 0x001f0000,
          MAC_REG_RSP_CASE4_CASE4_IRQ_NORMAL                                    = MAC_REG_RSP_CASE4,
          MAC_REG_RSP_CASE4_CASE4_IRQ_NORMAL_SHIFT                              = 15,
          MAC_REG_RSP_CASE4_CASE4_IRQ_NORMAL_MASK                               = 0x00008000,
          MAC_REG_RSP_CASE4_CASE4_CF_TYPE_NORMAL                                = MAC_REG_RSP_CASE4,
          MAC_REG_RSP_CASE4_CASE4_CF_TYPE_NORMAL_SHIFT                          = 8,
          MAC_REG_RSP_CASE4_CASE4_CF_TYPE_NORMAL_MASK                           = 0x00001f00,
          MAC_REG_RSP_CASE4_CASE4_IRQ_LONG                                      = MAC_REG_RSP_CASE4,
          MAC_REG_RSP_CASE4_CASE4_IRQ_LONG_SHIFT                                = 7,
          MAC_REG_RSP_CASE4_CASE4_IRQ_LONG_MASK                                 = 0x00000080,
          MAC_REG_RSP_CASE4_CASE4_CF_TYPE_LONG                                  = MAC_REG_RSP_CASE4,
          MAC_REG_RSP_CASE4_CASE4_CF_TYPE_LONG_SHIFT                            = 0,
          MAC_REG_RSP_CASE4_CASE4_CF_TYPE_LONG_MASK                             = 0x0000001f,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RSP_CASE5                                                           = 0x40080158,
//-------------------------------------------------------------------------------------------------------------------------------,
          MAC_REG_RSP_CASE5_CASE5_IRQ_NO                                        = MAC_REG_RSP_CASE5,
          MAC_REG_RSP_CASE5_CASE5_IRQ_NO_SHIFT                                  = 31,
          MAC_REG_RSP_CASE5_CASE5_IRQ_NO_MASK                                   = 0x80000000,
          MAC_REG_RSP_CASE5_CASE5_CF_TYPE_NO                                    = MAC_REG_RSP_CASE5,
          MAC_REG_RSP_CASE5_CASE5_CF_TYPE_NO_SHIFT                              = 24,
          MAC_REG_RSP_CASE5_CASE5_CF_TYPE_NO_MASK                               = 0x1f000000,
          MAC_REG_RSP_CASE5_CASE5_IRQ_NDP                                       = MAC_REG_RSP_CASE5,
          MAC_REG_RSP_CASE5_CASE5_IRQ_NDP_SHIFT                                 = 23,
          MAC_REG_RSP_CASE5_CASE5_IRQ_NDP_MASK                                  = 0x00800000,
          MAC_REG_RSP_CASE5_CASE5_CF_TYPE_NDP                                   = MAC_REG_RSP_CASE5,
          MAC_REG_RSP_CASE5_CASE5_CF_TYPE_NDP_SHIFT                             = 16,
          MAC_REG_RSP_CASE5_CASE5_CF_TYPE_NDP_MASK                              = 0x001f0000,
          MAC_REG_RSP_CASE5_CASE5_IRQ_NORMAL                                    = MAC_REG_RSP_CASE5,
          MAC_REG_RSP_CASE5_CASE5_IRQ_NORMAL_SHIFT                              = 15,
          MAC_REG_RSP_CASE5_CASE5_IRQ_NORMAL_MASK                               = 0x00008000,
          MAC_REG_RSP_CASE5_CASE5_CF_TYPE_NORMAL                                = MAC_REG_RSP_CASE5,
          MAC_REG_RSP_CASE5_CASE5_CF_TYPE_NORMAL_SHIFT                          = 8,
          MAC_REG_RSP_CASE5_CASE5_CF_TYPE_NORMAL_MASK                           = 0x00001f00,
          MAC_REG_RSP_CASE5_CASE5_IRQ_LONG                                      = MAC_REG_RSP_CASE5,
          MAC_REG_RSP_CASE5_CASE5_IRQ_LONG_SHIFT                                = 7,
          MAC_REG_RSP_CASE5_CASE5_IRQ_LONG_MASK                                 = 0x00000080,
          MAC_REG_RSP_CASE5_CASE5_CF_TYPE_LONG                                  = MAC_REG_RSP_CASE5,
          MAC_REG_RSP_CASE5_CASE5_CF_TYPE_LONG_SHIFT                            = 0,
          MAC_REG_RSP_CASE5_CASE5_CF_TYPE_LONG_MASK                             = 0x0000001f,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RSP_CASE6                                                           = 0x4008015c,
//-------------------------------------------------------------------------------------------------------------------------------,
          MAC_REG_RSP_CASE6_CASE6_IRQ_NO                                        = MAC_REG_RSP_CASE6,
          MAC_REG_RSP_CASE6_CASE6_IRQ_NO_SHIFT                                  = 31,
          MAC_REG_RSP_CASE6_CASE6_IRQ_NO_MASK                                   = 0x80000000,
          MAC_REG_RSP_CASE6_CASE6_CF_TYPE_NO                                    = MAC_REG_RSP_CASE6,
          MAC_REG_RSP_CASE6_CASE6_CF_TYPE_NO_SHIFT                              = 24,
          MAC_REG_RSP_CASE6_CASE6_CF_TYPE_NO_MASK                               = 0x1f000000,
          MAC_REG_RSP_CASE6_CASE6_IRQ_NDP                                       = MAC_REG_RSP_CASE6,
          MAC_REG_RSP_CASE6_CASE6_IRQ_NDP_SHIFT                                 = 23,
          MAC_REG_RSP_CASE6_CASE6_IRQ_NDP_MASK                                  = 0x00800000,
          MAC_REG_RSP_CASE6_CASE6_CF_TYPE_NDP                                   = MAC_REG_RSP_CASE6,
          MAC_REG_RSP_CASE6_CASE6_CF_TYPE_NDP_SHIFT                             = 16,
          MAC_REG_RSP_CASE6_CASE6_CF_TYPE_NDP_MASK                              = 0x001f0000,
          MAC_REG_RSP_CASE6_CASE6_IRQ_NORMAL                                    = MAC_REG_RSP_CASE6,
          MAC_REG_RSP_CASE6_CASE6_IRQ_NORMAL_SHIFT                              = 15,
          MAC_REG_RSP_CASE6_CASE6_IRQ_NORMAL_MASK                               = 0x00008000,
          MAC_REG_RSP_CASE6_CASE6_CF_TYPE_NORMAL                                = MAC_REG_RSP_CASE6,
          MAC_REG_RSP_CASE6_CASE6_CF_TYPE_NORMAL_SHIFT                          = 8,
          MAC_REG_RSP_CASE6_CASE6_CF_TYPE_NORMAL_MASK                           = 0x00001f00,
          MAC_REG_RSP_CASE6_CASE6_IRQ_LONG                                      = MAC_REG_RSP_CASE6,
          MAC_REG_RSP_CASE6_CASE6_IRQ_LONG_SHIFT                                = 7,
          MAC_REG_RSP_CASE6_CASE6_IRQ_LONG_MASK                                 = 0x00000080,
          MAC_REG_RSP_CASE6_CASE6_CF_TYPE_LONG                                  = MAC_REG_RSP_CASE6,
          MAC_REG_RSP_CASE6_CASE6_CF_TYPE_LONG_SHIFT                            = 0,
          MAC_REG_RSP_CASE6_CASE6_CF_TYPE_LONG_MASK                             = 0x0000001f,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RSP_CASE7                                                           = 0x40080160,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RSP_CASE8                                                           = 0x40080164,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RSP_CASE9                                                           = 0x40080168,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RSP_CASE10                                                          = 0x4008016c,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RSP_CASE11                                                          = 0x40080170,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_WAIT_MODE_WR                                                        = 0x40080174,
//-------------------------------------------------------------------------------------------------------------------------------,
          MAC_REG_WAIT_MODE_WR_RXINFO_READ_SKIP                                 = MAC_REG_WAIT_MODE_WR,
          MAC_REG_WAIT_MODE_WR_RXINFO_READ_SKIP_SHIFT                           = 28,
          MAC_REG_WAIT_MODE_WR_RXINFO_READ_SKIP_MASK                            = 0x10000000,
          MAC_REG_WAIT_MODE_WR_RXINFO_WRITE_SKIP                                = MAC_REG_WAIT_MODE_WR,
          MAC_REG_WAIT_MODE_WR_RXINFO_WRITE_SKIP_SHIFT                          = 27,
          MAC_REG_WAIT_MODE_WR_RXINFO_WRITE_SKIP_MASK                           = 0x08000000,
          MAC_REG_WAIT_MODE_WR_RXINFO_4SET_ENABLE                               = MAC_REG_WAIT_MODE_WR,
          MAC_REG_WAIT_MODE_WR_RXINFO_4SET_ENABLE_SHIFT                         = 26,
          MAC_REG_WAIT_MODE_WR_RXINFO_4SET_ENABLE_MASK                          = 0x04000000,
          MAC_REG_WAIT_MODE_WR_AHB_WAIT_MODE_WR_ON                              = MAC_REG_WAIT_MODE_WR,
          MAC_REG_WAIT_MODE_WR_AHB_WAIT_MODE_WR_ON_SHIFT                        = 24,
          MAC_REG_WAIT_MODE_WR_AHB_WAIT_MODE_WR_ON_MASK                         = 0x01000000,
          MAC_REG_WAIT_MODE_WR_AHB_WR_WAIT_CLOCK                                = MAC_REG_WAIT_MODE_WR,
          MAC_REG_WAIT_MODE_WR_AHB_WR_WAIT_CLOCK_SHIFT                          = 8,
          MAC_REG_WAIT_MODE_WR_AHB_WR_WAIT_CLOCK_MASK                           = 0x00ffff00,
          MAC_REG_WAIT_MODE_WR_AHB_WR_WAIT_INTERVAL                             = MAC_REG_WAIT_MODE_WR,
          MAC_REG_WAIT_MODE_WR_AHB_WR_WAIT_INTERVAL_SHIFT                       = 0,
          MAC_REG_WAIT_MODE_WR_AHB_WR_WAIT_INTERVAL_MASK                        = 0x000000ff,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_WAIT_MODE_RD                                                        = 0x40080178,
//-------------------------------------------------------------------------------------------------------------------------------,
          MAC_REG_WAIT_MODE_RD_AHB_WAIT_MODE_RD_ON                              = MAC_REG_WAIT_MODE_RD,
          MAC_REG_WAIT_MODE_RD_AHB_WAIT_MODE_RD_ON_SHIFT                        = 24,
          MAC_REG_WAIT_MODE_RD_AHB_WAIT_MODE_RD_ON_MASK                         = 0x01000000,
          MAC_REG_WAIT_MODE_RD_AHB_RD_WAIT_CLOCK                                = MAC_REG_WAIT_MODE_RD,
          MAC_REG_WAIT_MODE_RD_AHB_RD_WAIT_CLOCK_SHIFT                          = 8,
          MAC_REG_WAIT_MODE_RD_AHB_RD_WAIT_CLOCK_MASK                           = 0x00ffff00,
          MAC_REG_WAIT_MODE_RD_AHB_RD_WAIT_INTERVAL                             = MAC_REG_WAIT_MODE_RD,
          MAC_REG_WAIT_MODE_RD_AHB_RD_WAIT_INTERVAL_SHIFT                       = 0,
          MAC_REG_WAIT_MODE_RD_AHB_RD_WAIT_INTERVAL_MASK                        = 0x000000ff,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_COMMAND_0                                                        = 0x4008017c,
//-------------------------------------------------------------------------------------------------------------------------------,
          MAC_REG_TX_COMMAND_0_BUFFER_WORD_OFFSET                               = MAC_REG_TX_COMMAND_0,
          MAC_REG_TX_COMMAND_0_BUFFER_WORD_OFFSET_SHIFT                         = 16,
          MAC_REG_TX_COMMAND_0_BUFFER_WORD_OFFSET_MASK                          = 0xffff0000,
          MAC_REG_TX_COMMAND_0_BANDWIDTH                                        = MAC_REG_TX_COMMAND_0,
          MAC_REG_TX_COMMAND_0_BANDWIDTH_SHIFT                                  = 14,
          MAC_REG_TX_COMMAND_0_BANDWIDTH_MASK                                   = 0x0000c000,
          MAC_REG_TX_COMMAND_0_AIFSN                                            = MAC_REG_TX_COMMAND_0,
          MAC_REG_TX_COMMAND_0_AIFSN_SHIFT                                      = 10,
          MAC_REG_TX_COMMAND_0_AIFSN_MASK                                       = 0x00003c00,
          MAC_REG_TX_COMMAND_0_CW_COUNT                                         = MAC_REG_TX_COMMAND_0,
          MAC_REG_TX_COMMAND_0_CW_COUNT_SHIFT                                   = 0,
          MAC_REG_TX_COMMAND_0_CW_COUNT_MASK                                    = 0x000003ff,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_COMMAND_1                                                        = 0x40080180,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_COMMAND_2                                                        = 0x40080184,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_COMMAND_3                                                        = 0x40080188,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_COMMAND_4                                                        = 0x4008018c,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_COMMAND_5                                                        = 0x40080190,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_COMMAND_6                                                        = 0x40080194,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_COMMAND_7                                                        = 0x40080198,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_COMMAND_8                                                        = 0x4008019c,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_COMMAND_9                                                        = 0x400801a0,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_COMMAND_10                                                       = 0x400801a4,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TXOP_COMMAND_0                                                      = 0x400801a8,
//-------------------------------------------------------------------------------------------------------------------------------,
          MAC_REG_TXOP_COMMAND_0_BUFFER_WORD_OFFSET                             = MAC_REG_TXOP_COMMAND_0,
          MAC_REG_TXOP_COMMAND_0_BUFFER_WORD_OFFSET_SHIFT                       = 16,
          MAC_REG_TXOP_COMMAND_0_BUFFER_WORD_OFFSET_MASK                        = 0xffff0000,
          MAC_REG_TXOP_COMMAND_0_TX_TIME                                        = MAC_REG_TXOP_COMMAND_0,
          MAC_REG_TXOP_COMMAND_0_TX_TIME_SHIFT                                  = 0,
          MAC_REG_TXOP_COMMAND_0_TX_TIME_MASK                                   = 0x0000ffff,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TXOP_COMMAND_1                                                      = 0x400801ac,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TXOP_COMMAND_2                                                      = 0x400801b0,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TXOP_COMMAND_3                                                      = 0x400801b4,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TXOP_COMMAND_4                                                      = 0x400801b8,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TXOP_COMMAND_5                                                      = 0x400801bc,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TXOP_COMMAND_6                                                      = 0x400801c0,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TXOP_COMMAND_7                                                      = 0x400801c4,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TXOP_COMMAND_8                                                      = 0x400801c8,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TXOP_COMMAND_9                                                      = 0x400801cc,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TXOP_COMMAND_10                                                     = 0x400801d0,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_GAIN_LOWER_0                                                     = 0x400801d4,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_GAIN_UPPER_0                                                     = 0x400801d8,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_GAIN_LOWER_1                                                     = 0x400801dc,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_GAIN_UPPER_1                                                     = 0x400801e0,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_GAIN_LOWER_2                                                     = 0x400801e4,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_GAIN_UPPER_2                                                     = 0x400801e8,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_GAIN_LOWER_3                                                     = 0x400801ec,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_GAIN_UPPER_3                                                     = 0x400801f0,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_GAIN_LOWER_4                                                     = 0x400801f4,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_GAIN_UPPER_4                                                     = 0x400801f8,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_GAIN_LOWER_5                                                     = 0x400801fc,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_GAIN_UPPER_5                                                     = 0x40080200,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_GAIN_LOWER_6                                                     = 0x40080204,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_GAIN_UPPER_6                                                     = 0x40080208,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_GAIN_LOWER_7                                                     = 0x4008020c,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_GAIN_UPPER_7                                                     = 0x40080210,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_GAIN_LOWER_8                                                     = 0x40080214,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_GAIN_UPPER_8                                                     = 0x40080218,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_GAIN_LOWER_9                                                     = 0x4008021c,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_GAIN_UPPER_9                                                     = 0x40080220,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_GAIN_LOWER_10                                                    = 0x40080224,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_GAIN_UPPER_10                                                    = 0x40080228,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_GAIN_LOWER_CF                                                    = 0x4008022c,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_GAIN_UPPER_CF                                                    = 0x40080230,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_RAW_EDCA_0                                                       = 0x40080234,
//-------------------------------------------------------------------------------------------------------------------------------,
          MAC_REG_TX_RAW_EDCA_0_TX_TIME                                         = MAC_REG_TX_RAW_EDCA_0,
          MAC_REG_TX_RAW_EDCA_0_TX_TIME_SHIFT                                   = 16,
          MAC_REG_TX_RAW_EDCA_0_TX_TIME_MASK                                    = 0xffff0000,
          MAC_REG_TX_RAW_EDCA_0_AIFSN_RAW                                       = MAC_REG_TX_RAW_EDCA_0,
          MAC_REG_TX_RAW_EDCA_0_AIFSN_RAW_SHIFT                                 = 10,
          MAC_REG_TX_RAW_EDCA_0_AIFSN_RAW_MASK                                  = 0x00003c00,
          MAC_REG_TX_RAW_EDCA_0_CW_COUNT_RAW                                    = MAC_REG_TX_RAW_EDCA_0,
          MAC_REG_TX_RAW_EDCA_0_CW_COUNT_RAW_SHIFT                              = 0,
          MAC_REG_TX_RAW_EDCA_0_CW_COUNT_RAW_MASK                               = 0x000003ff,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_RAW_EDCA_1                                                       = 0x40080238,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_RAW_EDCA_2                                                       = 0x4008023c,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_RAW_EDCA_3                                                       = 0x40080240,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_RAW_EDCA_4                                                       = 0x40080244,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_RAW_EDCA_5                                                       = 0x40080248,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_BASE_ADDRESS                                                     = 0x4008024c,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TSW_DATA_IN_WAIT                                                    = 0x40080250,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_SUPPRESS_COMMAND                                                 = 0x40080254,
//-------------------------------------------------------------------------------------------------------------------------------,
          MAC_REG_TX_SUPPRESS_COMMAND_REFERENC_TSF                              = MAC_REG_TX_SUPPRESS_COMMAND,
          MAC_REG_TX_SUPPRESS_COMMAND_REFERENC_TSF_SHIFT                        = 31,
          MAC_REG_TX_SUPPRESS_COMMAND_REFERENC_TSF_MASK                         = 0x80000000,
          MAC_REG_TX_SUPPRESS_COMMAND_XROSS_BOUNDARY                            = MAC_REG_TX_SUPPRESS_COMMAND,
          MAC_REG_TX_SUPPRESS_COMMAND_XROSS_BOUNDARY_SHIFT                      = 30,
          MAC_REG_TX_SUPPRESS_COMMAND_XROSS_BOUNDARY_MASK                       = 0x40000000,
          MAC_REG_TX_SUPPRESS_COMMAND_HOLD_AFTER_SUPPRESS                       = MAC_REG_TX_SUPPRESS_COMMAND,
          MAC_REG_TX_SUPPRESS_COMMAND_HOLD_AFTER_SUPPRESS_SHIFT                 = 29,
          MAC_REG_TX_SUPPRESS_COMMAND_HOLD_AFTER_SUPPRESS_MASK                  = 0x20000000,
          MAC_REG_TX_SUPPRESS_COMMAND_MYRAW_CMD_VALID                           = MAC_REG_TX_SUPPRESS_COMMAND,
          MAC_REG_TX_SUPPRESS_COMMAND_MYRAW_CMD_VALID_SHIFT                     = 15,
          MAC_REG_TX_SUPPRESS_COMMAND_MYRAW_CMD_VALID_MASK                      = 0x00008000,
          MAC_REG_TX_SUPPRESS_COMMAND_MYRAW_COMMAND                             = MAC_REG_TX_SUPPRESS_COMMAND,
          MAC_REG_TX_SUPPRESS_COMMAND_MYRAW_COMMAND_SHIFT                       = 8,
          MAC_REG_TX_SUPPRESS_COMMAND_MYRAW_COMMAND_MASK                        = 0x00000f00,
          MAC_REG_TX_SUPPRESS_COMMAND_SUPPRESS_CMD_VALID                        = MAC_REG_TX_SUPPRESS_COMMAND,
          MAC_REG_TX_SUPPRESS_COMMAND_SUPPRESS_CMD_VALID_SHIFT                  = 7,
          MAC_REG_TX_SUPPRESS_COMMAND_SUPPRESS_CMD_VALID_MASK                   = 0x00000080,
          MAC_REG_TX_SUPPRESS_COMMAND_SUPPRESS_COMMAND                          = MAC_REG_TX_SUPPRESS_COMMAND,
          MAC_REG_TX_SUPPRESS_COMMAND_SUPPRESS_COMMAND_SHIFT                    = 0,
          MAC_REG_TX_SUPPRESS_COMMAND_SUPPRESS_COMMAND_MASK                     = 0x0000000f,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_SUPPRESS_START_TSF                                               = 0x40080258,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_SUPPRESS_END_TSF                                                 = 0x4008025c,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_SUPPRESS_DURATION                                                = 0x40080260,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_MYRAW_START_TSF                                                  = 0x40080264,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_MYRAW_END_TSF                                                    = 0x40080268,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_MYRAW_DURATION                                                   = 0x4008026c,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_SUPPRESS_SETTING                                                 = 0x40080270,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_SUPPRESS_STATUS                                                  = 0x40080274,
//-------------------------------------------------------------------------------------------------------------------------------,
          MAC_REG_TX_SUPPRESS_STATUS_MYRAW_CMD                                  = MAC_REG_TX_SUPPRESS_STATUS,
          MAC_REG_TX_SUPPRESS_STATUS_MYRAW_CMD_SHIFT                            = 12,
          MAC_REG_TX_SUPPRESS_STATUS_MYRAW_CMD_MASK                             = 0x0000f000,
          MAC_REG_TX_SUPPRESS_STATUS_SUPPRESS_CMD                               = MAC_REG_TX_SUPPRESS_STATUS,
          MAC_REG_TX_SUPPRESS_STATUS_SUPPRESS_CMD_SHIFT                         = 8,
          MAC_REG_TX_SUPPRESS_STATUS_SUPPRESS_CMD_MASK                          = 0x00000f00,
          MAC_REG_TX_SUPPRESS_STATUS_REFERENCE_TSF                              = MAC_REG_TX_SUPPRESS_STATUS,
          MAC_REG_TX_SUPPRESS_STATUS_REFERENCE_TSF_SHIFT                        = 3,
          MAC_REG_TX_SUPPRESS_STATUS_REFERENCE_TSF_MASK                         = 0x00000008,
          MAC_REG_TX_SUPPRESS_STATUS_XROSS_BOUNDARY                             = MAC_REG_TX_SUPPRESS_STATUS,
          MAC_REG_TX_SUPPRESS_STATUS_XROSS_BOUNDARY_SHIFT                       = 2,
          MAC_REG_TX_SUPPRESS_STATUS_XROSS_BOUNDARY_MASK                        = 0x00000004,
          MAC_REG_TX_SUPPRESS_STATUS_TX_MYRAW_PERIOD                            = MAC_REG_TX_SUPPRESS_STATUS,
          MAC_REG_TX_SUPPRESS_STATUS_TX_MYRAW_PERIOD_SHIFT                      = 1,
          MAC_REG_TX_SUPPRESS_STATUS_TX_MYRAW_PERIOD_MASK                       = 0x00000002,
          MAC_REG_TX_SUPPRESS_STATUS_TX_SUPPRESS_PERIOD                         = MAC_REG_TX_SUPPRESS_STATUS,
          MAC_REG_TX_SUPPRESS_STATUS_TX_SUPPRESS_PERIOD_SHIFT                   = 0,
          MAC_REG_TX_SUPPRESS_STATUS_TX_SUPPRESS_PERIOD_MASK                    = 0x00000001,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_DATA_IN_WAIT                                                     = 0x40080278,
//-------------------------------------------------------------------------------------------------------------------------------,
          MAC_REG_TX_DATA_IN_WAIT_SECURITY_OFFLINE                              = MAC_REG_TX_DATA_IN_WAIT,
          MAC_REG_TX_DATA_IN_WAIT_SECURITY_OFFLINE_SHIFT                        = 31,
          MAC_REG_TX_DATA_IN_WAIT_SECURITY_OFFLINE_MASK                         = 0x80000000,
          MAC_REG_TX_DATA_IN_WAIT_TIKIP_DATA_IN_WAIT                            = MAC_REG_TX_DATA_IN_WAIT,
          MAC_REG_TX_DATA_IN_WAIT_TIKIP_DATA_IN_WAIT_SHIFT                      = 8,
          MAC_REG_TX_DATA_IN_WAIT_TIKIP_DATA_IN_WAIT_MASK                       = 0x0000ff00,
          MAC_REG_TX_DATA_IN_WAIT_CCMP_DATA_IN_WAIT                             = MAC_REG_TX_DATA_IN_WAIT,
          MAC_REG_TX_DATA_IN_WAIT_CCMP_DATA_IN_WAIT_SHIFT                       = 0,
          MAC_REG_TX_DATA_IN_WAIT_CCMP_DATA_IN_WAIT_MASK                        = 0x000000ff,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_PHY_TXFIFO_MAX_DEPTH                                                = 0x4008027c,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TXNAV_VALUE                                                         = 0x40080280,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RXNAV_VALUE                                                         = 0x40080284,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RID_VALUE                                                           = 0x40080288,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_NAV_RESET                                                           = 0x4008028c,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RID_RESET                                                           = 0x40080290,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_NAV_RID_CONTROL_MODE                                                = 0x40080294,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TXNAV_HW_SETTING_VALUE                                              = 0x40080298,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_PREAMBLE_TYPE                                                       = 0x4008029c,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_CF_FIX_MOREDATA                                                     = 0x400802a0,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_SET_PS_POLL_ACK_SW                                                  = 0x400802a4,
//-------------------------------------------------------------------------------------------------------------------------------,
          MAC_REG_SET_PS_POLL_ACK_SW_REG_SW_DURATION                            = MAC_REG_SET_PS_POLL_ACK_SW,
          MAC_REG_SET_PS_POLL_ACK_SW_REG_SW_DURATION_SHIFT                      = 16,
          MAC_REG_SET_PS_POLL_ACK_SW_REG_SW_DURATION_MASK                       = 0x3fff0000,
          MAC_REG_SET_PS_POLL_ACK_SW_REG_SW_MOREDATA                            = MAC_REG_SET_PS_POLL_ACK_SW,
          MAC_REG_SET_PS_POLL_ACK_SW_REG_SW_MOREDATA_SHIFT                      = 4,
          MAC_REG_SET_PS_POLL_ACK_SW_REG_SW_MOREDATA_MASK                       = 0x00000010,
          MAC_REG_SET_PS_POLL_ACK_SW_REG_SW_IDLE_INDICATION                     = MAC_REG_SET_PS_POLL_ACK_SW,
          MAC_REG_SET_PS_POLL_ACK_SW_REG_SW_IDLE_INDICATION_SHIFT               = 0,
          MAC_REG_SET_PS_POLL_ACK_SW_REG_SW_IDLE_INDICATION_MASK                = 0x00000001,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_SET_PS_POLL_ACK_DEFAULT                                             = 0x400802a8,
//-------------------------------------------------------------------------------------------------------------------------------,
          MAC_REG_SET_PS_POLL_ACK_DEFAULT_REG_DEFAULT_DURATION                  = MAC_REG_SET_PS_POLL_ACK_DEFAULT,
          MAC_REG_SET_PS_POLL_ACK_DEFAULT_REG_DEFAULT_DURATION_SHIFT            = 16,
          MAC_REG_SET_PS_POLL_ACK_DEFAULT_REG_DEFAULT_DURATION_MASK             = 0x3fff0000,
          MAC_REG_SET_PS_POLL_ACK_DEFAULT_REG_DEFAULT_MOREDATA                  = MAC_REG_SET_PS_POLL_ACK_DEFAULT,
          MAC_REG_SET_PS_POLL_ACK_DEFAULT_REG_DEFAULT_MOREDATA_SHIFT            = 4,
          MAC_REG_SET_PS_POLL_ACK_DEFAULT_REG_DEFAULT_MOREDATA_MASK             = 0x00000010,
          MAC_REG_SET_PS_POLL_ACK_DEFAULT_REG_DEFAULT_IDLE_INDICATION           = MAC_REG_SET_PS_POLL_ACK_DEFAULT,
          MAC_REG_SET_PS_POLL_ACK_DEFAULT_REG_DEFAULT_IDLE_INDICATION_SHIFT     = 0,
          MAC_REG_SET_PS_POLL_ACK_DEFAULT_REG_DEFAULT_IDLE_INDICATION_MASK      = 0x00000001,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_SET_RTSRID                                                          = 0x400802ac,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_CF_CHANNEL_WIDTH_SELECTION                                          = 0x400802b0,
//-------------------------------------------------------------------------------------------------------------------------------,
          MAC_REG_CF_CHANNEL_WIDTH_SELECTION_REG_1M_RES_PREAMBLE_SUPPORT        = MAC_REG_CF_CHANNEL_WIDTH_SELECTION,
          MAC_REG_CF_CHANNEL_WIDTH_SELECTION_REG_1M_RES_PREAMBLE_SUPPORT_SHIFT  = 4,
          MAC_REG_CF_CHANNEL_WIDTH_SELECTION_REG_1M_RES_PREAMBLE_SUPPORT_MASK   = 0x00000010,
          MAC_REG_CF_CHANNEL_WIDTH_SELECTION_REG_DUP_1M_SUPPORT                 = MAC_REG_CF_CHANNEL_WIDTH_SELECTION,
          MAC_REG_CF_CHANNEL_WIDTH_SELECTION_REG_DUP_1M_SUPPORT_SHIFT           = 0,
          MAC_REG_CF_CHANNEL_WIDTH_SELECTION_REG_DUP_1M_SUPPORT_MASK            = 0x00000001,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_SET_FLOW_CONTROL_INFO_0                                             = 0x400802b4,
//-------------------------------------------------------------------------------------------------------------------------------,
          MAC_REG_SET_FLOW_CONTROL_INFO_0_SET_TSF_INFO_0                        = MAC_REG_SET_FLOW_CONTROL_INFO_0,
          MAC_REG_SET_FLOW_CONTROL_INFO_0_SET_TSF_INFO_0_SHIFT                  = 16,
          MAC_REG_SET_FLOW_CONTROL_INFO_0_SET_TSF_INFO_0_MASK                   = 0xffff0000,
          MAC_REG_SET_FLOW_CONTROL_INFO_0_REG_PSPOLL_RES_MOREDATA               = MAC_REG_SET_FLOW_CONTROL_INFO_0,
          MAC_REG_SET_FLOW_CONTROL_INFO_0_REG_PSPOLL_RES_MOREDATA_SHIFT         = 10,
          MAC_REG_SET_FLOW_CONTROL_INFO_0_REG_PSPOLL_RES_MOREDATA_MASK          = 0x00000400,
          MAC_REG_SET_FLOW_CONTROL_INFO_0_REG_FLOW_CONTROL                      = MAC_REG_SET_FLOW_CONTROL_INFO_0,
          MAC_REG_SET_FLOW_CONTROL_INFO_0_REG_FLOW_CONTROL_SHIFT                = 9,
          MAC_REG_SET_FLOW_CONTROL_INFO_0_REG_FLOW_CONTROL_MASK                 = 0x00000200,
          MAC_REG_SET_FLOW_CONTROL_INFO_0_REG_NEXT_TWT_INFO_PRESENT             = MAC_REG_SET_FLOW_CONTROL_INFO_0,
          MAC_REG_SET_FLOW_CONTROL_INFO_0_REG_NEXT_TWT_INFO_PRESENT_SHIFT       = 8,
          MAC_REG_SET_FLOW_CONTROL_INFO_0_REG_NEXT_TWT_INFO_PRESENT_MASK        = 0x00000100,
          MAC_REG_SET_FLOW_CONTROL_INFO_0_REG_BEACON_SEQUENCE                   = MAC_REG_SET_FLOW_CONTROL_INFO_0,
          MAC_REG_SET_FLOW_CONTROL_INFO_0_REG_BEACON_SEQUENCE_SHIFT             = 0,
          MAC_REG_SET_FLOW_CONTROL_INFO_0_REG_BEACON_SEQUENCE_MASK              = 0x000000ff,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_SET_FLOW_CONTROL_INFO_1                                             = 0x400802b8,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_SET_ACK_SW                                                          = 0x400802bc,
//-------------------------------------------------------------------------------------------------------------------------------,
          MAC_REG_SET_ACK_SW_REG_SW_ACK_DURATION                                = MAC_REG_SET_ACK_SW,
          MAC_REG_SET_ACK_SW_REG_SW_ACK_DURATION_SHIFT                          = 16,
          MAC_REG_SET_ACK_SW_REG_SW_ACK_DURATION_MASK                           = 0x3fff0000,
          MAC_REG_SET_ACK_SW_REG_SW_ACK_RELAYED_FRAME                           = MAC_REG_SET_ACK_SW,
          MAC_REG_SET_ACK_SW_REG_SW_ACK_RELAYED_FRAME_SHIFT                     = 8,
          MAC_REG_SET_ACK_SW_REG_SW_ACK_RELAYED_FRAME_MASK                      = 0x00000100,
          MAC_REG_SET_ACK_SW_REG_SW_ACK_MOREDATA                                = MAC_REG_SET_ACK_SW,
          MAC_REG_SET_ACK_SW_REG_SW_ACK_MOREDATA_SHIFT                          = 4,
          MAC_REG_SET_ACK_SW_REG_SW_ACK_MOREDATA_MASK                           = 0x00000010,
          MAC_REG_SET_ACK_SW_REG_SW_ACK_IDLE_INDICATION                         = MAC_REG_SET_ACK_SW,
          MAC_REG_SET_ACK_SW_REG_SW_ACK_IDLE_INDICATION_SHIFT                   = 0,
          MAC_REG_SET_ACK_SW_REG_SW_ACK_IDLE_INDICATION_MASK                    = 0x00000001,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_SET_ACK_DEFAULT                                                     = 0x400802c0,
//-------------------------------------------------------------------------------------------------------------------------------,
          MAC_REG_SET_ACK_DEFAULT_REG_DEFAULT_ACK_DURATION                      = MAC_REG_SET_ACK_DEFAULT,
          MAC_REG_SET_ACK_DEFAULT_REG_DEFAULT_ACK_DURATION_SHIFT                = 16,
          MAC_REG_SET_ACK_DEFAULT_REG_DEFAULT_ACK_DURATION_MASK                 = 0x3fff0000,
          MAC_REG_SET_ACK_DEFAULT_REG_DEFAULT_ACK_RELAYED_FRAME                 = MAC_REG_SET_ACK_DEFAULT,
          MAC_REG_SET_ACK_DEFAULT_REG_DEFAULT_ACK_RELAYED_FRAME_SHIFT           = 8,
          MAC_REG_SET_ACK_DEFAULT_REG_DEFAULT_ACK_RELAYED_FRAME_MASK            = 0x00000100,
          MAC_REG_SET_ACK_DEFAULT_REG_DEFAULT_ACK_MOREDATA                      = MAC_REG_SET_ACK_DEFAULT,
          MAC_REG_SET_ACK_DEFAULT_REG_DEFAULT_ACK_MOREDATA_SHIFT                = 4,
          MAC_REG_SET_ACK_DEFAULT_REG_DEFAULT_ACK_MOREDATA_MASK                 = 0x00000010,
          MAC_REG_SET_ACK_DEFAULT_REG_DEFAULT_ACK_IDLE_INDICATION               = MAC_REG_SET_ACK_DEFAULT,
          MAC_REG_SET_ACK_DEFAULT_REG_DEFAULT_ACK_IDLE_INDICATION_SHIFT         = 0,
          MAC_REG_SET_ACK_DEFAULT_REG_DEFAULT_ACK_IDLE_INDICATION_MASK          = 0x00000001,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_BASIC_RATE_BITMAP                                                   = 0x400802c4,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_BASIC_RATE_BITMAP_2ND                                               = 0x400802c8,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_MCS_DIFFERENCE                                                      = 0x400802cc,
//-------------------------------------------------------------------------------------------------------------------------------,
          MAC_REG_MCS_DIFFERENCE_BA_MCS_DIFFERENCE                              = MAC_REG_MCS_DIFFERENCE,
          MAC_REG_MCS_DIFFERENCE_BA_MCS_DIFFERENCE_SHIFT                        = 12,
          MAC_REG_MCS_DIFFERENCE_BA_MCS_DIFFERENCE_MASK                         = 0x0000f000,
          MAC_REG_MCS_DIFFERENCE_MCS_DIFFERENCE_SWITCH                          = MAC_REG_MCS_DIFFERENCE,
          MAC_REG_MCS_DIFFERENCE_MCS_DIFFERENCE_SWITCH_SHIFT                    = 4,
          MAC_REG_MCS_DIFFERENCE_MCS_DIFFERENCE_SWITCH_MASK                     = 0x00000ff0,
          MAC_REG_MCS_DIFFERENCE_MCS_DIFFERENCE                                 = MAC_REG_MCS_DIFFERENCE,
          MAC_REG_MCS_DIFFERENCE_MCS_DIFFERENCE_SHIFT                           = 0,
          MAC_REG_MCS_DIFFERENCE_MCS_DIFFERENCE_MASK                            = 0x0000000f,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RESPONSE_TX_COMMAND                                                 = 0x400802d0,
//-------------------------------------------------------------------------------------------------------------------------------,
          MAC_REG_RESPONSE_TX_COMMAND_RESPONSE_TYPE                             = MAC_REG_RESPONSE_TX_COMMAND,
          MAC_REG_RESPONSE_TX_COMMAND_RESPONSE_TYPE_SHIFT                       = 5,
          MAC_REG_RESPONSE_TX_COMMAND_RESPONSE_TYPE_MASK                        = 0x00000020,
          MAC_REG_RESPONSE_TX_COMMAND_COMMAND                                   = MAC_REG_RESPONSE_TX_COMMAND,
          MAC_REG_RESPONSE_TX_COMMAND_COMMAND_SHIFT                             = 0,
          MAC_REG_RESPONSE_TX_COMMAND_COMMAND_MASK                              = 0x0000001f,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RSP_TX_VECTOR                                                       = 0x400802d4,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RSP_TX_SIG0                                                         = 0x400802d8,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RSP_TX_SIG1                                                         = 0x400802dc,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RSP_TX_INFO0                                                        = 0x400802e0,
//-------------------------------------------------------------------------------------------------------------------------------,
          MAC_REG_RSP_TX_INFO0_RSP_TXINFO_TIMESTAMP_POSITION                    = MAC_REG_RSP_TX_INFO0,
          MAC_REG_RSP_TX_INFO0_RSP_TXINFO_TIMESTAMP_POSITION_SHIFT              = 23,
          MAC_REG_RSP_TX_INFO0_RSP_TXINFO_TIMESTAMP_POSITION_MASK               = 0x1f800000,
          MAC_REG_RSP_TX_INFO0_RSP_TXINFO_TIMESTAMP_UPDATE                      = MAC_REG_RSP_TX_INFO0,
          MAC_REG_RSP_TX_INFO0_RSP_TXINFO_TIMESTAMP_UPDATE_SHIFT                = 22,
          MAC_REG_RSP_TX_INFO0_RSP_TXINFO_TIMESTAMP_UPDATE_MASK                 = 0x00400000,
          MAC_REG_RSP_TX_INFO0_RSP_TXINFO_CIPHER_TYPE                           = MAC_REG_RSP_TX_INFO0,
          MAC_REG_RSP_TX_INFO0_RSP_TXINFO_CIPHER_TYPE_SHIFT                     = 15,
          MAC_REG_RSP_TX_INFO0_RSP_TXINFO_CIPHER_TYPE_MASK                      = 0x00038000,
          MAC_REG_RSP_TX_INFO0_RSP_TXINFO_SINGLE_AMPDU                          = MAC_REG_RSP_TX_INFO0,
          MAC_REG_RSP_TX_INFO0_RSP_TXINFO_SINGLE_AMPDU_SHIFT                    = 14,
          MAC_REG_RSP_TX_INFO0_RSP_TXINFO_SINGLE_AMPDU_MASK                     = 0x00004000,
          MAC_REG_RSP_TX_INFO0_RSP_TXINFO_MPDU_LENGTH                           = MAC_REG_RSP_TX_INFO0,
          MAC_REG_RSP_TX_INFO0_RSP_TXINFO_MPDU_LENGTH_SHIFT                     = 0,
          MAC_REG_RSP_TX_INFO0_RSP_TXINFO_MPDU_LENGTH_MASK                      = 0x00003fff,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RSP_TX_INFO1                                                        = 0x400802e4,
//-------------------------------------------------------------------------------------------------------------------------------,
          MAC_REG_RSP_TX_INFO1_RSP_TXINFO_FORMAT                                = MAC_REG_RSP_TX_INFO1,
          MAC_REG_RSP_TX_INFO1_RSP_TXINFO_FORMAT_SHIFT                          = 21,
          MAC_REG_RSP_TX_INFO1_RSP_TXINFO_FORMAT_MASK                           = 0x00e00000,
          MAC_REG_RSP_TX_INFO1_RSP_TXINFO_AGGREGATION                           = MAC_REG_RSP_TX_INFO1,
          MAC_REG_RSP_TX_INFO1_RSP_TXINFO_AGGREGATION_SHIFT                     = 20,
          MAC_REG_RSP_TX_INFO1_RSP_TXINFO_AGGREGATION_MASK                      = 0x00100000,
          MAC_REG_RSP_TX_INFO1_RSP_TXINFO_PSDU_LENGTH                           = MAC_REG_RSP_TX_INFO1,
          MAC_REG_RSP_TX_INFO1_RSP_TXINFO_PSDU_LENGTH_SHIFT                     = 0,
          MAC_REG_RSP_TX_INFO1_RSP_TXINFO_PSDU_LENGTH_MASK                      = 0x000fffff,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RSP_TX_DATA0                                                        = 0x400802e8,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RSP_TX_DATA1                                                        = 0x400802ec,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RSP_TX_DATA2                                                        = 0x400802f0,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RSP_TX_DATA3                                                        = 0x400802f4,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RSP_TX_DATA4                                                        = 0x400802f8,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RSP_TX_DATA5                                                        = 0x400802fc,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RSP_TX_DATA6                                                        = 0x40080300,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RSP_TX_DATA7                                                        = 0x40080304,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RSP_TX_DATA8                                                        = 0x40080308,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RSP_TX_DATA9                                                        = 0x4008030c,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RSP_TX_DATA10                                                       = 0x40080310,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_SET_CF_TXVECTOR_SIG                                                 = 0x40080314,
//-------------------------------------------------------------------------------------------------------------------------------,
          MAC_REG_SET_CF_TXVECTOR_SIG_REG_SIG_UPLINK_IND                        = MAC_REG_SET_CF_TXVECTOR_SIG,
          MAC_REG_SET_CF_TXVECTOR_SIG_REG_SIG_UPLINK_IND_SHIFT                  = 17,
          MAC_REG_SET_CF_TXVECTOR_SIG_REG_SIG_UPLINK_IND_MASK                   = 0x00020000,
          MAC_REG_SET_CF_TXVECTOR_SIG_REG_SIG_DOPPLER                           = MAC_REG_SET_CF_TXVECTOR_SIG,
          MAC_REG_SET_CF_TXVECTOR_SIG_REG_SIG_DOPPLER_SHIFT                     = 16,
          MAC_REG_SET_CF_TXVECTOR_SIG_REG_SIG_DOPPLER_MASK                      = 0x00010000,
          MAC_REG_SET_CF_TXVECTOR_SIG_REG_TXPWR_LEVEL                           = MAC_REG_SET_CF_TXVECTOR_SIG,
          MAC_REG_SET_CF_TXVECTOR_SIG_REG_TXPWR_LEVEL_SHIFT                     = 8,
          MAC_REG_SET_CF_TXVECTOR_SIG_REG_TXPWR_LEVEL_MASK                      = 0x0000ff00,
          MAC_REG_SET_CF_TXVECTOR_SIG_REG_SCRAMBLER_EXIST                       = MAC_REG_SET_CF_TXVECTOR_SIG,
          MAC_REG_SET_CF_TXVECTOR_SIG_REG_SCRAMBLER_EXIST_SHIFT                 = 7,
          MAC_REG_SET_CF_TXVECTOR_SIG_REG_SCRAMBLER_EXIST_MASK                  = 0x00000080,
          MAC_REG_SET_CF_TXVECTOR_SIG_REG_SCRAMBLER_OR_CRC                      = MAC_REG_SET_CF_TXVECTOR_SIG,
          MAC_REG_SET_CF_TXVECTOR_SIG_REG_SCRAMBLER_OR_CRC_SHIFT                = 0,
          MAC_REG_SET_CF_TXVECTOR_SIG_REG_SCRAMBLER_OR_CRC_MASK                 = 0x0000007f,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_MONITOR_INTERVAL                                                    = 0x40080318,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_CCA_RANGE_VAR_SET0                                                  = 0x4008031c,
//-------------------------------------------------------------------------------------------------------------------------------,
          MAC_REG_CCA_RANGE_VAR_SET0_RANGE_VAR_1                                = MAC_REG_CCA_RANGE_VAR_SET0,
          MAC_REG_CCA_RANGE_VAR_SET0_RANGE_VAR_1_SHIFT                          = 16,
          MAC_REG_CCA_RANGE_VAR_SET0_RANGE_VAR_1_MASK                           = 0xffff0000,
          MAC_REG_CCA_RANGE_VAR_SET0_RANGE_VAR_0                                = MAC_REG_CCA_RANGE_VAR_SET0,
          MAC_REG_CCA_RANGE_VAR_SET0_RANGE_VAR_0_SHIFT                          = 0,
          MAC_REG_CCA_RANGE_VAR_SET0_RANGE_VAR_0_MASK                           = 0x0000ffff,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_CCA_RANGE_VAR_SET1                                                  = 0x40080320,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RX_BASE_ADDRESS                                                     = 0x40080324,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RX_DSC_NUM                                                          = 0x40080328,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RX_REG_DL_DESC0                                                     = 0x4008032c,
//-------------------------------------------------------------------------------------------------------------------------------,
          MAC_REG_RX_REG_DL_DESC0_BUFFER_LENGTH                                 = MAC_REG_RX_REG_DL_DESC0,
          MAC_REG_RX_REG_DL_DESC0_BUFFER_LENGTH_SHIFT                           = 15,
          MAC_REG_RX_REG_DL_DESC0_BUFFER_LENGTH_MASK                            = 0x03ff8000,
          MAC_REG_RX_REG_DL_DESC0_DATA_ADDRESS_OFFSET                           = MAC_REG_RX_REG_DL_DESC0,
          MAC_REG_RX_REG_DL_DESC0_DATA_ADDRESS_OFFSET_SHIFT                     = 0,
          MAC_REG_RX_REG_DL_DESC0_DATA_ADDRESS_OFFSET_MASK                      = 0x00007fff,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RX_REG_DL_DESC1                                                     = 0x40080330,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RX_REG_DL_DESC2                                                     = 0x40080334,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RX_REG_DL_DESC3                                                     = 0x40080338,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RX_REG_DL_DESC4                                                     = 0x4008033c,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RX_REG_DL_DESC5                                                     = 0x40080340,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RX_REG_DL_DESC6                                                     = 0x40080344,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RX_REG_DL_DESC7                                                     = 0x40080348,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RX_REG_DL_DESC8                                                     = 0x4008034c,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RX_REG_DL_DESC9                                                     = 0x40080350,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RX_REG_DL_DESC10                                                    = 0x40080354,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RX_REG_DL_DESC11                                                    = 0x40080358,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RX_REG_DL_DESC12                                                    = 0x4008035c,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RX_REG_DL_DESC13                                                    = 0x40080360,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RX_REG_DL_DESC14                                                    = 0x40080364,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RX_REG_DL_DESC15                                                    = 0x40080368,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RX_REG_DL_DESC16                                                    = 0x4008036c,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RX_REG_DL_DESC17                                                    = 0x40080370,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RX_REG_DL_DESC18                                                    = 0x40080374,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RX_REG_DL_DESC19                                                    = 0x40080378,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RX_REG_DL_DESC20                                                    = 0x4008037c,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RX_REG_DL_DESC21                                                    = 0x40080380,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RX_REG_DL_DESC22                                                    = 0x40080384,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RX_REG_DL_DESC23                                                    = 0x40080388,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RX_REG_DL_DESC24                                                    = 0x4008038c,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RX_REG_DL_DESC25                                                    = 0x40080390,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RX_REG_DL_DESC26                                                    = 0x40080394,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RX_REG_DL_DESC27                                                    = 0x40080398,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RX_REG_DL_DESC28                                                    = 0x4008039c,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RX_REG_DL_DESC29                                                    = 0x400803a0,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RX_REG_DL_DESC30                                                    = 0x400803a4,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RX_REG_DL_DESC31                                                    = 0x400803a8,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_SET_OWNER_ADDR                                                      = 0x400803ac,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RX_DATA_IN_WAIT                                                     = 0x400803b0,
//-------------------------------------------------------------------------------------------------------------------------------,
          MAC_REG_RX_DATA_IN_WAIT_SECURITY_OFFLINE                              = MAC_REG_RX_DATA_IN_WAIT,
          MAC_REG_RX_DATA_IN_WAIT_SECURITY_OFFLINE_SHIFT                        = 31,
          MAC_REG_RX_DATA_IN_WAIT_SECURITY_OFFLINE_MASK                         = 0x80000000,
          MAC_REG_RX_DATA_IN_WAIT_RX_WAIT_MODE                                  = MAC_REG_RX_DATA_IN_WAIT,
          MAC_REG_RX_DATA_IN_WAIT_RX_WAIT_MODE_SHIFT                            = 23,
          MAC_REG_RX_DATA_IN_WAIT_RX_WAIT_MODE_MASK                             = 0x00800000,
          MAC_REG_RX_DATA_IN_WAIT_CCMP_DATA_IN_WAIT                             = MAC_REG_RX_DATA_IN_WAIT,
          MAC_REG_RX_DATA_IN_WAIT_CCMP_DATA_IN_WAIT_SHIFT                       = 0,
          MAC_REG_RX_DATA_IN_WAIT_CCMP_DATA_IN_WAIT_MASK                        = 0x000000ff,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_DMA_SEG_THRESHOLD                                                   = 0x400803b4,
//-------------------------------------------------------------------------------------------------------------------------------,
          MAC_REG_DMA_SEG_THRESHOLD_DMA_CMD_QUEUE_THRESHOLD                     = MAC_REG_DMA_SEG_THRESHOLD,
          MAC_REG_DMA_SEG_THRESHOLD_DMA_CMD_QUEUE_THRESHOLD_SHIFT               = 12,
          MAC_REG_DMA_SEG_THRESHOLD_DMA_CMD_QUEUE_THRESHOLD_MASK                = 0x00007000,
          MAC_REG_DMA_SEG_THRESHOLD_ABORT_STOP_MODE                             = MAC_REG_DMA_SEG_THRESHOLD,
          MAC_REG_DMA_SEG_THRESHOLD_ABORT_STOP_MODE_SHIFT                       = 8,
          MAC_REG_DMA_SEG_THRESHOLD_ABORT_STOP_MODE_MASK                        = 0x00000700,
          MAC_REG_DMA_SEG_THRESHOLD_DMA_SEG_THRESHOLD                           = MAC_REG_DMA_SEG_THRESHOLD,
          MAC_REG_DMA_SEG_THRESHOLD_DMA_SEG_THRESHOLD_SHIFT                     = 0,
          MAC_REG_DMA_SEG_THRESHOLD_DMA_SEG_THRESHOLD_MASK                      = 0x000000ff,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_SEC_KEY_CMD                                                         = 0x400803b8,
//-------------------------------------------------------------------------------------------------------------------------------,
          MAC_REG_SEC_KEY_CMD_SEC_KEY_CMD_TYPE                                              = MAC_REG_SEC_KEY_CMD,
          MAC_REG_SEC_KEY_CMD_SEC_KEY_CMD_TYPE_SHIFT                                        = 28,
          MAC_REG_SEC_KEY_CMD_SEC_KEY_CMD_TYPE_MASK                                         = 0xf0000000,
          MAC_REG_SEC_KEY_CMD_SEC_KEY_CMD_KEY_ID                                            = MAC_REG_SEC_KEY_CMD,
          MAC_REG_SEC_KEY_CMD_SEC_KEY_CMD_KEY_ID_SHIFT                                      = 24,
          MAC_REG_SEC_KEY_CMD_SEC_KEY_CMD_KEY_ID_MASK                                       = 0x03000000,
          MAC_REG_SEC_KEY_CMD_SEC_KEY_CMD_KEY_TYPE                                          = MAC_REG_SEC_KEY_CMD,
          MAC_REG_SEC_KEY_CMD_SEC_KEY_CMD_KEY_TYPE_SHIFT                                    = 20,
          MAC_REG_SEC_KEY_CMD_SEC_KEY_CMD_KEY_TYPE_MASK                                     = 0x00100000,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_SEC_KEY_CMD_EN                                                      = 0x400803bc,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_SEC_KEY_VALUE0                                                      = 0x400803c0,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_SEC_KEY_VALUE1                                                      = 0x400803c4,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_SEC_KEY_VALUE2                                                      = 0x400803c8,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_SEC_KEY_VALUE3                                                      = 0x400803cc,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_SEC_STA_ADDRESS_0                                                    = 0x400803d0,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_SEC_STA_ADDRESS_1                                                    = 0x400803d4,
//-------------------------------------------------------------------------------------------------------------------------------,
          MAC_REG_SEC_STA_ADDRESS_1_AID                                          = MAC_REG_SEC_STA_ADDRESS_1,
          MAC_REG_SEC_STA_ADDRESS_1_AID_SHIFT                                    = 16,
          MAC_REG_SEC_STA_ADDRESS_1_AID_MASK                                     = 0x1fff0000,
          MAC_REG_SEC_STA_ADDRESS_1_MAC_ADDRESS                                  = MAC_REG_SEC_STA_ADDRESS_1,
          MAC_REG_SEC_STA_ADDRESS_1_MAC_ADDRESS_SHIFT                            = 0,
          MAC_REG_SEC_STA_ADDRESS_1_MAC_ADDRESS_MASK                             = 0x0000ffff,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_SEC_CCMP_UPDATE_INFO                                                = 0x400803d8,
//-------------------------------------------------------------------------------------------------------------------------------,
          MAC_REG_SEC_CCMP_UPDATE_INFO_MOREDATA                                 = MAC_REG_SEC_CCMP_UPDATE_INFO,
          MAC_REG_SEC_CCMP_UPDATE_INFO_MOREDATA_SHIFT                           = 31,
          MAC_REG_SEC_CCMP_UPDATE_INFO_MOREDATA_MASK                            = 0x80000000,
          MAC_REG_SEC_CCMP_UPDATE_INFO_TWT                                      = MAC_REG_SEC_CCMP_UPDATE_INFO,
          MAC_REG_SEC_CCMP_UPDATE_INFO_TWT_SHIFT                                = 30,
          MAC_REG_SEC_CCMP_UPDATE_INFO_TWT_MASK                                 = 0x40000000,
          MAC_REG_SEC_CCMP_UPDATE_INFO_KEY_ID                                   = MAC_REG_SEC_CCMP_UPDATE_INFO,
          MAC_REG_SEC_CCMP_UPDATE_INFO_KEY_ID_SHIFT                             = 4,
          MAC_REG_SEC_CCMP_UPDATE_INFO_KEY_ID_MASK                              = 0x00000030,
          MAC_REG_SEC_CCMP_UPDATE_INFO_TID                                      = MAC_REG_SEC_CCMP_UPDATE_INFO,
          MAC_REG_SEC_CCMP_UPDATE_INFO_TID_SHIFT                                = 0,
          MAC_REG_SEC_CCMP_UPDATE_INFO_TID_MASK                                 = 0x0000000f,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_SEC_CONFIG                                                          = 0x400803dc,
//-------------------------------------------------------------------------------------------------------------------------------,
          MAC_REG_SEC_CONFIG_SEC_PV0_MANAGEMENT_DEC_BYPASS                      = MAC_REG_SEC_CONFIG,
          MAC_REG_SEC_CONFIG_SEC_PV0_MANAGEMENT_DEC_BYPASS_SHIFT                = 31,
          MAC_REG_SEC_CONFIG_SEC_PV0_MANAGEMENT_DEC_BYPASS_MASK                 = 0x80000000,
          MAC_REG_SEC_CONFIG_SEC_PV0_MANAGEMENT_ENC_BYPASS                      = MAC_REG_SEC_CONFIG,
          MAC_REG_SEC_CONFIG_SEC_PV0_MANAGEMENT_ENC_BYPASS_SHIFT                = 30,
          MAC_REG_SEC_CONFIG_SEC_PV0_MANAGEMENT_ENC_BYPASS_MASK                 = 0x40000000,
          MAC_REG_SEC_CONFIG_SEC_SPP_ENABLE                                     = MAC_REG_SEC_CONFIG,
          MAC_REG_SEC_CONFIG_SEC_SPP_ENABLE_SHIFT                               = 29,
          MAC_REG_SEC_CONFIG_SEC_SPP_ENABLE_MASK                                = 0x20000000,
          MAC_REG_SEC_CONFIG_SEC_KEY_LOC_ENABLE                                 = MAC_REG_SEC_CONFIG,
          MAC_REG_SEC_CONFIG_SEC_KEY_LOC_ENABLE_SHIFT                           = 28,
          MAC_REG_SEC_CONFIG_SEC_KEY_LOC_ENABLE_MASK                            = 0x10000000,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_SEC_READ_BASE_ADDR                                                  = 0x400803e0,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_SEC_WRITE_BASE_ADDR                                                 = 0x400803e4,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_SEC_INFO_0                                                          = 0x400803e8,
//-------------------------------------------------------------------------------------------------------------------------------,
          MAC_REG_SEC_INFO_0_HEADER_EXTENSION_ENABLE                            = MAC_REG_SEC_INFO_0,
          MAC_REG_SEC_INFO_0_HEADER_EXTENSION_ENABLE_SHIFT                      = 31,
          MAC_REG_SEC_INFO_0_HEADER_EXTENSION_ENABLE_MASK                       = 0x80000000,
          MAC_REG_SEC_INFO_0_MAC_HEADER_LENGTH                                  = MAC_REG_SEC_INFO_0,
          MAC_REG_SEC_INFO_0_MAC_HEADER_LENGTH_SHIFT                            = 20,
          MAC_REG_SEC_INFO_0_MAC_HEADER_LENGTH_MASK                             = 0x7ff00000,
          MAC_REG_SEC_INFO_0_MPDU_LENGTH                                        = MAC_REG_SEC_INFO_0,
          MAC_REG_SEC_INFO_0_MPDU_LENGTH_SHIFT                                  = 4,
          MAC_REG_SEC_INFO_0_MPDU_LENGTH_MASK                                   = 0x0003fff0,
          MAC_REG_SEC_INFO_0_CIPHER_TYPE                                        = MAC_REG_SEC_INFO_0,
          MAC_REG_SEC_INFO_0_CIPHER_TYPE_SHIFT                                  = 1,
          MAC_REG_SEC_INFO_0_CIPHER_TYPE_MASK                                   = 0x0000000e,
          MAC_REG_SEC_INFO_0_ENCRYPTION                                         = MAC_REG_SEC_INFO_0,
          MAC_REG_SEC_INFO_0_ENCRYPTION_SHIFT                                   = 0,
          MAC_REG_SEC_INFO_0_ENCRYPTION_MASK                                    = 0x00000001,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_SEC_INFO_1                                                          = 0x400803ec,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_SEC_INFO_2                                                          = 0x400803f0,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_SEC_INFO_3                                                          = 0x400803f4,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_SEC_INFO_4                                                          = 0x400803f8,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_SEC_OFFSET                                                          = 0x400803fc,
//-------------------------------------------------------------------------------------------------------------------------------,
          MAC_REG_SEC_OFFSET_READ_OFFSET_ENCRYPT_3                              = MAC_REG_SEC_OFFSET,
          MAC_REG_SEC_OFFSET_READ_OFFSET_ENCRYPT_3_SHIFT                        = 26,
          MAC_REG_SEC_OFFSET_READ_OFFSET_ENCRYPT_3_MASK                         = 0x7c000000,
          MAC_REG_SEC_OFFSET_READ_OFFSET_ENCRYPT_2                              = MAC_REG_SEC_OFFSET,
          MAC_REG_SEC_OFFSET_READ_OFFSET_ENCRYPT_2_SHIFT                        = 21,
          MAC_REG_SEC_OFFSET_READ_OFFSET_ENCRYPT_2_MASK                         = 0x03e00000,
          MAC_REG_SEC_OFFSET_READ_OFFSET_DECRYPT                                = MAC_REG_SEC_OFFSET,
          MAC_REG_SEC_OFFSET_READ_OFFSET_DECRYPT_SHIFT                          = 16,
          MAC_REG_SEC_OFFSET_READ_OFFSET_DECRYPT_MASK                           = 0x001f0000,
          MAC_REG_SEC_OFFSET_READ_OFFSET_ENCRYPT_1                              = MAC_REG_SEC_OFFSET,
          MAC_REG_SEC_OFFSET_READ_OFFSET_ENCRYPT_1_SHIFT                        = 8,
          MAC_REG_SEC_OFFSET_READ_OFFSET_ENCRYPT_1_MASK                         = 0x00001f00,
          MAC_REG_SEC_OFFSET_READ_OFFSET_ENCRYPT_0                              = MAC_REG_SEC_OFFSET,
          MAC_REG_SEC_OFFSET_READ_OFFSET_ENCRYPT_0_SHIFT                        = 0,
          MAC_REG_SEC_OFFSET_READ_OFFSET_ENCRYPT_0_MASK                         = 0x0000001f,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_SEC_DATA_IN_WAIT_CNT                                                = 0x40080400,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_SEC_KEY_FLAG_IDX                                                    = 0x40080404,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_INDIR_REG_ADDR                                                   = 0x40080408,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RX_INDIR_REG_ADDR                                                   = 0x4008040c,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_SEC_INDIR_REG_ADDR                                                  = 0x40080410,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_DMA_INDIR_REG_ADDR                                                  = 0x40080414,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_IRQ_INDIR_REG_ADDR                                                  = 0x40080418,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_MEM_INDIR_REG_ADDR                                                  = 0x4008041c,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TSF_0_LOWER                                                         = 0x40080420,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TSF_0_UPPER                                                         = 0x40080424,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TSF_0_ALARM_LOWER                                                   = 0x40080428,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_BCN_INTERVAL_0                                                      = 0x4008042c,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TBTT_INTERRUPT_MARGIN_0                                             = 0x40080430,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TBTT_RESTART_RANGE_0                                                = 0x40080434,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TSF_1_LOWER                                                         = 0x40080438,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TSF_1_UPPER                                                         = 0x4008043c,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TSF_1_ALARM_LOWER                                                   = 0x40080440,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_BCN_INTERVAL_1                                                      = 0x40080444,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TBTT_INTERRUPT_MARGIN_1                                             = 0x40080448,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TBTT_RESTART_RANGE_1                                                = 0x4008044c,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_IRQ_MASK0                                                           = 0x40080450,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_IRQ_MASK1                                                           = 0x40080454,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_IRQ_SET_CLEAR0                                                      = 0x40080458,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_IRQ_SET_CLEAR1                                                      = 0x4008045c,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_CLOCK_GATING_CONFIG                                                 = 0x40080460,
//-------------------------------------------------------------------------------------------------------------------------------,
          MAC_REG_CLOCK_GATING_CONFIG_GLOBAL_CG_EN                              = MAC_REG_CLOCK_GATING_CONFIG,
          MAC_REG_CLOCK_GATING_CONFIG_GLOBAL_CG_EN_SHIFT                        = 31,
          MAC_REG_CLOCK_GATING_CONFIG_GLOBAL_CG_EN_MASK                         = 0x80000000,
          MAC_REG_CLOCK_GATING_CONFIG_LUT_CG_MODE                               = MAC_REG_CLOCK_GATING_CONFIG,
          MAC_REG_CLOCK_GATING_CONFIG_LUT_CG_MODE_SHIFT                         = 6,
          MAC_REG_CLOCK_GATING_CONFIG_LUT_CG_MODE_MASK                          = 0x000000c0,
          MAC_REG_CLOCK_GATING_CONFIG_CCMP_CG_MODE                              = MAC_REG_CLOCK_GATING_CONFIG,
          MAC_REG_CLOCK_GATING_CONFIG_CCMP_CG_MODE_SHIFT                        = 4,
          MAC_REG_CLOCK_GATING_CONFIG_CCMP_CG_MODE_MASK                         = 0x00000030,
          MAC_REG_CLOCK_GATING_CONFIG_BUS_CG_MODE                               = MAC_REG_CLOCK_GATING_CONFIG,
          MAC_REG_CLOCK_GATING_CONFIG_BUS_CG_MODE_SHIFT                         = 2,
          MAC_REG_CLOCK_GATING_CONFIG_BUS_CG_MODE_MASK                          = 0x0000000c,
          MAC_REG_CLOCK_GATING_CONFIG_MAC_CG_MODE                               = MAC_REG_CLOCK_GATING_CONFIG,
          MAC_REG_CLOCK_GATING_CONFIG_MAC_CG_MODE_SHIFT                         = 0,
          MAC_REG_CLOCK_GATING_CONFIG_MAC_CG_MODE_MASK                          = 0x00000003,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_RESULT_0                                                         = 0x40080464,
//-------------------------------------------------------------------------------------------------------------------------------,
          MAC_REG_TX_RESULT_0_FEEDBACK_VALID                                    = MAC_REG_TX_RESULT_0,
          MAC_REG_TX_RESULT_0_FEEDBACK_VALID_SHIFT                              = 31,
          MAC_REG_TX_RESULT_0_FEEDBACK_VALID_MASK                               = 0x80000000,
          MAC_REG_TX_RESULT_0_FEEDBACK_SNR                                      = MAC_REG_TX_RESULT_0,
          MAC_REG_TX_RESULT_0_FEEDBACK_SNR_SHIFT                                = 24,
          MAC_REG_TX_RESULT_0_FEEDBACK_SNR_MASK                                 = 0x7f000000,
          MAC_REG_TX_RESULT_0_RECEIVED_SNR                                      = MAC_REG_TX_RESULT_0,
          MAC_REG_TX_RESULT_0_RECEIVED_SNR_SHIFT                                = 16,
          MAC_REG_TX_RESULT_0_RECEIVED_SNR_MASK                                 = 0x00ff0000,
          MAC_REG_TX_RESULT_0_VALID_RESULT                                      = MAC_REG_TX_RESULT_0,
          MAC_REG_TX_RESULT_0_VALID_RESULT_SHIFT                                = 15,
          MAC_REG_TX_RESULT_0_VALID_RESULT_MASK                                 = 0x00008000,
          MAC_REG_TX_RESULT_0_SEQUENCE                                          = MAC_REG_TX_RESULT_0,
          MAC_REG_TX_RESULT_0_SEQUENCE_SHIFT                                    = 12,
          MAC_REG_TX_RESULT_0_SEQUENCE_MASK                                     = 0x00007000,
          MAC_REG_TX_RESULT_0_MORE_DATA                                         = MAC_REG_TX_RESULT_0,
          MAC_REG_TX_RESULT_0_MORE_DATA_SHIFT                                   = 11,
          MAC_REG_TX_RESULT_0_MORE_DATA_MASK                                    = 0x00000800,
          MAC_REG_TX_RESULT_0_LACK_TXTIME                                       = MAC_REG_TX_RESULT_0,
          MAC_REG_TX_RESULT_0_LACK_TXTIME_SHIFT                                 = 10,
          MAC_REG_TX_RESULT_0_LACK_TXTIME_MASK                                  = 0x00000400,
          MAC_REG_TX_RESULT_0_INSIDE_RAW                                        = MAC_REG_TX_RESULT_0,
          MAC_REG_TX_RESULT_0_INSIDE_RAW_SHIFT                                  = 9,
          MAC_REG_TX_RESULT_0_INSIDE_RAW_MASK                                   = 0x00000200,
          MAC_REG_TX_RESULT_0_SIFS_TIMEOUT                                      = MAC_REG_TX_RESULT_0,
          MAC_REG_TX_RESULT_0_SIFS_TIMEOUT_SHIFT                                = 8,
          MAC_REG_TX_RESULT_0_SIFS_TIMEOUT_MASK                                 = 0x00000100,
          MAC_REG_TX_RESULT_0_BW_MATCH_FAIL                                     = MAC_REG_TX_RESULT_0,
          MAC_REG_TX_RESULT_0_BW_MATCH_FAIL_SHIFT                               = 7,
          MAC_REG_TX_RESULT_0_BW_MATCH_FAIL_MASK                                = 0x00000080,
          MAC_REG_TX_RESULT_0_ACK_POLICY                                        = MAC_REG_TX_RESULT_0,
          MAC_REG_TX_RESULT_0_ACK_POLICY_SHIFT                                  = 6,
          MAC_REG_TX_RESULT_0_ACK_POLICY_MASK                                   = 0x00000040,
          MAC_REG_TX_RESULT_0_FAIL_REASON                                       = MAC_REG_TX_RESULT_0,
          MAC_REG_TX_RESULT_0_FAIL_REASON_SHIFT                                 = 3,
          MAC_REG_TX_RESULT_0_FAIL_REASON_MASK                                  = 0x00000038,
          MAC_REG_TX_RESULT_0_TXOP_END                                          = MAC_REG_TX_RESULT_0,
          MAC_REG_TX_RESULT_0_TXOP_END_SHIFT                                    = 2,
          MAC_REG_TX_RESULT_0_TXOP_END_MASK                                     = 0x00000004,
          MAC_REG_TX_RESULT_0_FAILED_BITMAP_VALID                               = MAC_REG_TX_RESULT_0,
          MAC_REG_TX_RESULT_0_FAILED_BITMAP_VALID_SHIFT                         = 1,
          MAC_REG_TX_RESULT_0_FAILED_BITMAP_VALID_MASK                          = 0x00000002,
          MAC_REG_TX_RESULT_0_ACK_SUCCESS                                       = MAC_REG_TX_RESULT_0,
          MAC_REG_TX_RESULT_0_ACK_SUCCESS_SHIFT                                 = 0,
          MAC_REG_TX_RESULT_0_ACK_SUCCESS_MASK                                  = 0x00000001,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_RESULT_1                                                         = 0x40080468,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_RESULT_2                                                         = 0x4008046c,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_RESULT_3                                                         = 0x40080470,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_RESULT_4                                                         = 0x40080474,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_RESULT_5                                                         = 0x40080478,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_RESULT_6                                                         = 0x4008047c,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_RESULT_7                                                         = 0x40080480,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_RESULT_8                                                         = 0x40080484,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_RESULT_9                                                         = 0x40080488,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_RESULT_10                                                        = 0x4008048c,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_RESULT_11                                                        = 0x40080490,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_RESULT_12                                                        = 0x40080494,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_RESULT_13                                                        = 0x40080498,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_RESULT_14                                                        = 0x4008049c,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_RESULT_15                                                        = 0x400804a0,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_RESULT_16                                                        = 0x400804a4,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_RESULT_17                                                        = 0x400804a8,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_RESULT_18                                                        = 0x400804ac,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_RESULT_19                                                        = 0x400804b0,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_RESULT_20                                                        = 0x400804b4,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_RESULT_21                                                        = 0x400804b8,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_FAILED_BITMAP_LOWER_0                                            = 0x400804bc,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_FAILED_BITMAP_UPPER_0                                            = 0x400804c0,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_FAILED_BITMAP_LOWER_1                                            = 0x400804c4,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_FAILED_BITMAP_UPPER_1                                            = 0x400804c8,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_FAILED_BITMAP_LOWER_2                                            = 0x400804cc,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_FAILED_BITMAP_UPPER_2                                            = 0x400804d0,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_FAILED_BITMAP_LOWER_3                                            = 0x400804d4,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_FAILED_BITMAP_UPPER_3                                            = 0x400804d8,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_FAILED_BITMAP_LOWER_4                                            = 0x400804dc,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_FAILED_BITMAP_UPPER_4                                            = 0x400804e0,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_FAILED_BITMAP_LOWER_5                                            = 0x400804e4,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_FAILED_BITMAP_UPPER_5                                            = 0x400804e8,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_FAILED_BITMAP_LOWER_6                                            = 0x400804ec,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_FAILED_BITMAP_UPPER_6                                            = 0x400804f0,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_FAILED_BITMAP_LOWER_7                                            = 0x400804f4,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_FAILED_BITMAP_UPPER_7                                            = 0x400804f8,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_FAILED_BITMAP_LOWER_8                                            = 0x400804fc,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_FAILED_BITMAP_UPPER_8                                            = 0x40080500,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_FAILED_BITMAP_LOWER_9                                            = 0x40080504,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_FAILED_BITMAP_UPPER_9                                            = 0x40080508,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_FAILED_BITMAP_LOWER_10                                           = 0x4008050c,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_FAILED_BITMAP_UPPER_10                                           = 0x40080510,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RESPONSE_TX_RESULT                                                  = 0x40080514,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RX_WRITE_EN_DL_DESC0                                                = 0x40080518,
//-------------------------------------------------------------------------------------------------------------------------------,
          MAC_REG_RX_WRITE_EN_DL_DESC0_OWNERSHIP                                = MAC_REG_RX_WRITE_EN_DL_DESC0,
          MAC_REG_RX_WRITE_EN_DL_DESC0_OWNERSHIP_SHIFT                          = 2,
          MAC_REG_RX_WRITE_EN_DL_DESC0_OWNERSHIP_MASK                           = 0x00000004,
          MAC_REG_RX_WRITE_EN_DL_DESC0_FRAGMENT                                 = MAC_REG_RX_WRITE_EN_DL_DESC0,
          MAC_REG_RX_WRITE_EN_DL_DESC0_FRAGMENT_SHIFT                           = 0,
          MAC_REG_RX_WRITE_EN_DL_DESC0_FRAGMENT_MASK                            = 0x00000003,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RX_WRITE_EN_DL_DESC1                                                = 0x4008051c,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RX_WRITE_EN_DL_DESC2                                                = 0x40080520,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RX_WRITE_EN_DL_DESC3                                                = 0x40080524,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RX_WRITE_EN_DL_DESC4                                                = 0x40080528,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RX_WRITE_EN_DL_DESC5                                                = 0x4008052c,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RX_WRITE_EN_DL_DESC6                                                = 0x40080530,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RX_WRITE_EN_DL_DESC7                                                = 0x40080534,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RX_WRITE_EN_DL_DESC8                                                = 0x40080538,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RX_WRITE_EN_DL_DESC9                                                = 0x4008053c,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RX_WRITE_EN_DL_DESC10                                               = 0x40080540,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RX_WRITE_EN_DL_DESC11                                               = 0x40080544,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RX_WRITE_EN_DL_DESC12                                               = 0x40080548,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RX_WRITE_EN_DL_DESC13                                               = 0x4008054c,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RX_WRITE_EN_DL_DESC14                                               = 0x40080550,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RX_WRITE_EN_DL_DESC15                                               = 0x40080554,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RX_WRITE_EN_DL_DESC16                                               = 0x40080558,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RX_WRITE_EN_DL_DESC17                                               = 0x4008055c,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RX_WRITE_EN_DL_DESC18                                               = 0x40080560,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RX_WRITE_EN_DL_DESC19                                               = 0x40080564,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RX_WRITE_EN_DL_DESC20                                               = 0x40080568,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RX_WRITE_EN_DL_DESC21                                               = 0x4008056c,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RX_WRITE_EN_DL_DESC22                                               = 0x40080570,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RX_WRITE_EN_DL_DESC23                                               = 0x40080574,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RX_WRITE_EN_DL_DESC24                                               = 0x40080578,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RX_WRITE_EN_DL_DESC25                                               = 0x4008057c,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RX_WRITE_EN_DL_DESC26                                               = 0x40080580,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RX_WRITE_EN_DL_DESC27                                               = 0x40080584,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RX_WRITE_EN_DL_DESC28                                               = 0x40080588,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RX_WRITE_EN_DL_DESC29                                               = 0x4008058c,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RX_WRITE_EN_DL_DESC30                                               = 0x40080590,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RX_WRITE_EN_DL_DESC31                                               = 0x40080594,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RXSIG0                                                              = 0x40080598,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RXSIG1                                                              = 0x4008059c,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RXVECTOR0                                                           = 0x400805a0,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RXVECTOR1                                                           = 0x400805a4,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RXVECTOR2                                                           = 0x400805a8,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RXINFO0                                                             = 0x400805ac,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RXINFO1                                                             = 0x400805b0,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RXINFO2                                                             = 0x400805b4,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RXINFO3                                                             = 0x400805b8,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RXHEADER0                                                           = 0x400805bc,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RXHEADER1                                                           = 0x400805c0,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RXHEADER2                                                           = 0x400805c4,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RXHEADER3                                                           = 0x400805c8,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RXHEADER4                                                           = 0x400805cc,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RXHEADER5                                                           = 0x400805d0,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RXHEADER6                                                           = 0x400805d4,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RXHEADER7                                                           = 0x400805d8,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RXHEADER8                                                           = 0x400805dc,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_AMPDU_BITMAP                                                        = 0x400805e0,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_KEY_CMD_RESULT_EN                                                   = 0x400805e4,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_KEY_CMD_RESULT                                                      = 0x400805e8,
//-------------------------------------------------------------------------------------------------------------------------------,
          MAC_REG_KEY_CMD_RESULT_COMMAND                                        = MAC_REG_KEY_CMD_RESULT,
          MAC_REG_KEY_CMD_RESULT_COMMAND_SHIFT                                  = 28,
          MAC_REG_KEY_CMD_RESULT_COMMAND_MASK                                   = 0xf0000000,
          MAC_REG_KEY_CMD_RESULT_RESULT                                         = MAC_REG_KEY_CMD_RESULT,
          MAC_REG_KEY_CMD_RESULT_RESULT_SHIFT                                   = 20,
          MAC_REG_KEY_CMD_RESULT_RESULT_MASK                                    = 0x0ff00000,
          MAC_REG_KEY_CMD_RESULT_ADDRESS                                        = MAC_REG_KEY_CMD_RESULT,
          MAC_REG_KEY_CMD_RESULT_ADDRESS_SHIFT                                  = 0,
          MAC_REG_KEY_CMD_RESULT_ADDRESS_MASK                                   = 0x00000007,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_SEC_REG_MIC_CHECK_FAIL                                              = 0x400805ec,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_SEC_KEY_FLAG                                                        = 0x400805f0,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_SEC_MIC_VALUE_RX_FAILED_0                                           = 0x400805f4,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_SEC_MIC_VALUE_RX_FAILED_1                                           = 0x400805f8,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TX_INDIR_REG_DATA                                                   = 0x400805fc,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RX_INDIR_REG_DATA                                                   = 0x40080600,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_SEC_INDIR_REG_DATA                                                  = 0x40080604,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_DMA_INDIR_REG_DATA                                                  = 0x40080608,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_IRQ_INDIR_REG_DATA                                                  = 0x4008060c,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TSF_0_LOWER_READONLY                                                = 0x40080610,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TSF_0_UPPER_READONLY                                                = 0x40080614,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TSF_1_LOWER_READONLY                                                = 0x40080618,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_TSF_1_UPPER_READONLY                                                = 0x4008061c,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_IRQ_SRC_NOCLEAR0                                                    = 0x40080620,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_IRQ_SRC_NOCLEAR1                                                    = 0x40080624,
//-------------------------------------------------------------------------------------------------------------------------------,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_IRQ_SRC0                                                            = 0x40080628,
//-------------------------------------------------------------------------------------------------------------------------------,
          MAC_REG_IRQ_SRC0_TSF1_ALARM                                           = MAC_REG_IRQ_SRC0,
          MAC_REG_IRQ_SRC0_TSF1_ALARM_SHIFT                                     = 31,
          MAC_REG_IRQ_SRC0_TSF1_ALARM_MASK                                      = 0x80000000,
          MAC_REG_IRQ_SRC0_TBTT_IRQ_TSF1                                        = MAC_REG_IRQ_SRC0,
          MAC_REG_IRQ_SRC0_TBTT_IRQ_TSF1_SHIFT                                  = 30,
          MAC_REG_IRQ_SRC0_TBTT_IRQ_TSF1_MASK                                   = 0x40000000,
          MAC_REG_IRQ_SRC0_RX_BUFFER_LOOKUP                                     = MAC_REG_IRQ_SRC0,
          MAC_REG_IRQ_SRC0_RX_BUFFER_LOOKUP_SHIFT                               = 29,
          MAC_REG_IRQ_SRC0_RX_BUFFER_LOOKUP_MASK                                = 0x20000000,
          MAC_REG_IRQ_SRC0_TSF0_ALARM                                           = MAC_REG_IRQ_SRC0,
          MAC_REG_IRQ_SRC0_TSF0_ALARM_SHIFT                                     = 28,
          MAC_REG_IRQ_SRC0_TSF0_ALARM_MASK                                      = 0x10000000,
          MAC_REG_IRQ_SRC0_TBTT_IRQ_TSF0                                        = MAC_REG_IRQ_SRC0,
          MAC_REG_IRQ_SRC0_TBTT_IRQ_TSF0_SHIFT                                  = 27,
          MAC_REG_IRQ_SRC0_TBTT_IRQ_TSF0_MASK                                   = 0x08000000,
          MAC_REG_IRQ_SRC0_AHB_SEC_IRQ                                          = MAC_REG_IRQ_SRC0,
          MAC_REG_IRQ_SRC0_AHB_SEC_IRQ_SHIFT                                    = 26,
          MAC_REG_IRQ_SRC0_AHB_SEC_IRQ_MASK                                     = 0x04000000,
          MAC_REG_IRQ_SRC0_DMA_ERROR                                            = MAC_REG_IRQ_SRC0,
          MAC_REG_IRQ_SRC0_DMA_ERROR_SHIFT                                      = 25,
          MAC_REG_IRQ_SRC0_DMA_ERROR_MASK                                       = 0x02000000,
          MAC_REG_IRQ_SRC0_TX_RESPONSE_TIMEOUT                                  = MAC_REG_IRQ_SRC0,
          MAC_REG_IRQ_SRC0_TX_RESPONSE_TIMEOUT_SHIFT                            = 24,
          MAC_REG_IRQ_SRC0_TX_RESPONSE_TIMEOUT_MASK                             = 0x01000000,
          MAC_REG_IRQ_SRC0_RX_DMA_DONE                                          = MAC_REG_IRQ_SRC0,
          MAC_REG_IRQ_SRC0_RX_DMA_DONE_SHIFT                                    = 23,
          MAC_REG_IRQ_SRC0_RX_DMA_DONE_MASK                                     = 0x00800000,
          MAC_REG_IRQ_SRC0_RX_DONE                                              = MAC_REG_IRQ_SRC0,
          MAC_REG_IRQ_SRC0_RX_DONE_SHIFT                                        = 22,
          MAC_REG_IRQ_SRC0_RX_DONE_MASK                                         = 0x00400000,
          MAC_REG_IRQ_SRC0_TX_DONE_BITMAP                                       = MAC_REG_IRQ_SRC0,
          MAC_REG_IRQ_SRC0_TX_DONE_BITMAP_SHIFT                                 = 11,
          MAC_REG_IRQ_SRC0_TX_DONE_BITMAP_MASK                                  = 0x003ff800,
          MAC_REG_IRQ_SRC0_WIN_AC_BITMAP                                        = MAC_REG_IRQ_SRC0,
          MAC_REG_IRQ_SRC0_WIN_AC_BITMAP_SHIFT                                  = 0,
          MAC_REG_IRQ_SRC0_WIN_AC_BITMAP_MASK                                   = 0x000007ff,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_IRQ_SRC1                                                            = 0x4008062c,
//-------------------------------------------------------------------------------------------------------------------------------,
          MAC_REG_IRQ_SRC1_RX_PAGING                                            = MAC_REG_IRQ_SRC1,
          MAC_REG_IRQ_SRC1_RX_PAGING_SHIFT                                      = 2,
          MAC_REG_IRQ_SRC1_RX_PAGING_MASK                                       = 0x00000004,
          MAC_REG_IRQ_SRC1_MYRAW_END                                            = MAC_REG_IRQ_SRC1,
          MAC_REG_IRQ_SRC1_MYRAW_END_SHIFT                                      = 1,
          MAC_REG_IRQ_SRC1_MYRAW_END_MASK                                       = 0x00000002,
          MAC_REG_IRQ_SRC1_SUPPRESS_END                                         = MAC_REG_IRQ_SRC1,
          MAC_REG_IRQ_SRC1_SUPPRESS_END_SHIFT                                   = 0,
          MAC_REG_IRQ_SRC1_SUPPRESS_END_MASK                                    = 0x00000001,
//-------------------------------------------------------------------------------------------------------------------------------,
    MAC_REG_RX_NDP_PAGING                                                       = 0x40080630,
//-------------------------------------------------------------------------------------------------------------------------------
};
static inline bool mac_register_ver_check(void)
{ return *(unsigned int volatile *)(0x4008fffc) == MAC_REG_VER; }
#endif
