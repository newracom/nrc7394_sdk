/*********************************************************************/
/*    Newracom Library / IP Product                                  */
/*    Product Name :                                                 */
/*    Version      :                                                 */
/*    Author       :                                                 */
/*    Update       :                                                 */
/*********************************************************************/

#ifndef __REG_MAC_H__
#define __REG_MAC_H__

#ifdef __cplusplus
extern "C"{
#endif

// 0x40080000 register ------------------------------------
typedef struct {
    uint32_t                           RST_SW                             :1 ;
    uint32_t                           reserved0                          :31;
}   MAC_RST_SW;

typedef union {
    uint32_t                           w;
    MAC_RST_SW                         b;
}   MAC_RST_SW_U;


// 0x40080004 register ------------------------------------
typedef struct {
    uint32_t                           MAC_LOOPBACK                       :1 ;
    uint32_t                           CCA_IGNORE                         :1 ;
    uint32_t                           RX_DMA_PROMISCUOUS_MODE            :1 ;
    uint32_t                           reserved0                          :1 ;
    uint32_t                           PD_MAC_LOOPBACK                    :1 ;
    uint32_t                           PD_MAC_RX_TOP                      :1 ;
    uint32_t                           TX_PD_CONFIG                       :2 ;
    uint32_t                           AIFSN_UPPER                        :4 ;
    uint32_t                           RECV_MIC_REMAIN                    :1 ;
    uint32_t                           ENCR_MIC_SELECTED                  :1 ;
    uint32_t                           reserved1                          :2 ;
    uint32_t                           US_CLOCK                           :8 ;
    uint32_t                           RX_BUFFER_LOOKUP_EN                :1 ;
    uint32_t                           RX_BUFFER_LOOKUP_MODE_TYPE         :1 ;
    uint32_t                           RX_BUFFER_LOOKUP_IRQ_EN            :1 ;
    uint32_t                           reserved2                          :2 ;
    uint32_t                           BITMAP_PROTECT_EN                  :1 ;
    uint32_t                           PV1_PAYLOAD_SHIFT_RX               :1 ;
    uint32_t                           IRQ_CLEAR_MODE                     :1 ;
}   MAC_CONFIG;

typedef union {
    uint32_t                           w;
    MAC_CONFIG                         b;
}   MAC_CONFIG_U;


// 0x40080008 register ------------------------------------
typedef struct {
    uint32_t                           SIFS_DURATION                      :32;
}   MAC_SIFS_DURATION;

typedef union {
    uint32_t                           w;
    MAC_SIFS_DURATION                  b;
}   MAC_SIFS_DURATION_U;


// 0x4008000C register ------------------------------------
typedef struct {
    uint32_t                           SLOT_DURATION                      :32;
}   MAC_SLOT_DURATION;

typedef union {
    uint32_t                           w;
    MAC_SLOT_DURATION                  b;
}   MAC_SLOT_DURATION_U;


// 0x40080010 register ------------------------------------
typedef struct {
    uint32_t                           TXPWR_POST_DELAY_CLOCK             :32;
}   MAC_TXPWR_POST_DELAY_CLOCK;

typedef union {
    uint32_t                           w;
    MAC_TXPWR_POST_DELAY_CLOCK         b;
}   MAC_TXPWR_POST_DELAY_CLOCK_U;


// 0x40080014 register ------------------------------------
typedef struct {
    uint32_t                           CRASH                              :32;
}   MAC_CRASH;

typedef union {
    uint32_t                           w;
    MAC_CRASH                          b;
}   MAC_CRASH_U;


// 0x40080018 register ------------------------------------
typedef struct {
    uint32_t                           TX_RESPONSE_CONTROL                :32;
}   MAC_TX_RESPONSE_CONTROL;

typedef union {
    uint32_t                           w;
    MAC_TX_RESPONSE_CONTROL            b;
}   MAC_TX_RESPONSE_CONTROL_U;


// 0x4008001C register ------------------------------------
typedef struct {
    uint32_t                           OPERATION_BAND                     :32;
}   MAC_OPERATION_BAND;

typedef union {
    uint32_t                           w;
    MAC_OPERATION_BAND                 b;
}   MAC_OPERATION_BAND_U;


// 0x40080020 register ------------------------------------
typedef struct {
    uint32_t                           FILTER_DELAY0                      :10;
    uint32_t                           FILTER_DELAY1                      :10;
    uint32_t                           FILTER_DELAY2                      :10;
    uint32_t                           reserved0                          :2 ;
}   MAC_TXPPDU_DELAY_CLOCK;

typedef union {
    uint32_t                           w;
    MAC_TXPPDU_DELAY_CLOCK             b;
}   MAC_TXPPDU_DELAY_CLOCK_U;


// 0x40080024 register ------------------------------------
typedef struct {
    uint32_t                           READY_BEFORE_TXPPDU_CLOCK          :32;
}   MAC_READY_BEFORE_TXPPDU_CLOCK;

typedef union {
    uint32_t                           w;
    MAC_READY_BEFORE_TXPPDU_CLOCK      b;
}   MAC_READY_BEFORE_TXPPDU_CLOCK_U;


// 0x40080028 register ------------------------------------
typedef struct {
    uint32_t                           READY_TO_TXPOWER_CLOCK_4M          :10;
    uint32_t                           READY_TO_TXPOWER_CLOCK_2M          :10;
    uint32_t                           READY_TO_TXPOWER_CLOCK_1M          :10;
    uint32_t                           reserved0                          :2 ;
}   MAC_READY_TO_TXPOWER_CLOCK;

typedef union {
    uint32_t                           w;
    MAC_READY_TO_TXPOWER_CLOCK         b;
}   MAC_READY_TO_TXPOWER_CLOCK_U;


// 0x4008002C register ------------------------------------
typedef struct {
    uint32_t                           TXPOWER_TO_TXREQUEST_CLOCK         :32;
}   MAC_TXPOWER_TO_TXREQUEST_CLOCK;

typedef union {
    uint32_t                           w;
    MAC_TXPOWER_TO_TXREQUEST_CLOCK     b;
}   MAC_TXPOWER_TO_TXREQUEST_CLOCK_U;


// 0x40080030 register ------------------------------------
typedef struct {
    uint32_t                           RESPONSE_TIMEOUT_US                :32;
}   MAC_RESPONSE_TIMEOUT_US;

typedef union {
    uint32_t                           w;
    MAC_RESPONSE_TIMEOUT_US            b;
}   MAC_RESPONSE_TIMEOUT_US_U;


// 0x40080034 register ------------------------------------
typedef struct {
    uint32_t                           RX_REG_INTF_CTRL                   :4 ;
    uint32_t                           TWT_RESPONDER_EN                   :1 ;
    uint32_t                           NDP_PAGING_WAKEUP                  :1 ;
    uint32_t                           SNR_FEEDBACK_EN                    :2 ;
    uint32_t                           RESP_MOREDATA_MODE                 :4 ;
    uint32_t                           SIFS_TIMEOUT_EN                    :1 ;
    uint32_t                           MPDU_FCS                           :1 ;
    uint32_t                           BACKOFF_FINE_TUNE                  :1 ;
    uint32_t                           reserved0                          :1 ;
    uint32_t                           SEARCH_FIELD_TIMEOUT               :6 ;
    uint32_t                           reserved1                          :10;
}   MAC_CONFIG_EXT;

typedef union {
    uint32_t                           w;
    MAC_CONFIG_EXT                     b;
}   MAC_CONFIG_EXT_U;


// 0x40080038 register ------------------------------------
typedef struct {
    uint32_t                           RX_MY_PM_BIT_FRAME                 :1 ;
    uint32_t                           RX_MY_IDLE_INDICATION              :1 ;
    uint32_t                           RX_MY_ACK_FRAME                    :1 ;
    uint32_t                           RX_MY_NDP_FRAME                    :1 ;
    uint32_t                           RX_MY_CONTROL_FRAME                :1 ;
    uint32_t                           RX_ALL_NDP_FRAME                   :1 ;
    uint32_t                           RX_GROUP_ADDRESSED                 :1 ;
    uint32_t                           RX_MANAGEMENT_FRAME                :1 ;
    uint32_t                           RX_CONTROL_FRAME                   :1 ;
    uint32_t                           RX_PV1_FRAME                       :1 ;
    uint32_t                           RX_ALL                             :1 ;
    uint32_t                           RX_NDP_PROBE_REQ                   :1 ;
    uint32_t                           RX_MY_NDP_PAGING                   :1 ;
    uint32_t                           RX_MY_PS_POLL                      :1 ;
    uint32_t                           reserved0                          :1 ;
    uint32_t                           RX_ALL_BEACON                      :1 ;
    uint32_t                           reserved1                          :16;
}   MAC_STA_FILTER_MODE;

typedef union {
    uint32_t                           w;
    MAC_STA_FILTER_MODE                b;
}   MAC_STA_FILTER_MODE_U;


// 0x4008003C register ------------------------------------
typedef struct {
    uint32_t                           BSS_ENABLE                         :4 ;
    uint32_t                           MACADDR_ENABLE                     :4 ;
    uint32_t                           BSSID_MODE                         :4 ;
    uint32_t                           reserved0                          :4 ;
    uint32_t                           BSS_INTF_CFG                       :4 ;
    uint32_t                           MACADDR_INTF_CFG                   :4 ;
    uint32_t                           AID_INTF_CFG                       :4 ;
    uint32_t                           reserved1                          :4 ;
}   MAC_INTF_CFG_ACTIVE_BITMAP;

typedef union {
    uint32_t                           w;
    MAC_INTF_CFG_ACTIVE_BITMAP         b;
}   MAC_INTF_CFG_ACTIVE_BITMAP_U;


// 0x40080040 register ------------------------------------
typedef struct {
    uint32_t                           SIFS_TIMEOUT_US                    :16;
    uint32_t                           reserved0                          :16;
}   MAC_SIFS_TIMEOUT;

typedef union {
    uint32_t                           w;
    MAC_SIFS_TIMEOUT                   b;
}   MAC_SIFS_TIMEOUT_U;


// 0x40080044 register ------------------------------------
typedef struct {
    uint32_t                           STA_BSSID0_LOWER                   :32;
}   MAC_STA_BSSID0_LOWER;

typedef union {
    uint32_t                           w;
    MAC_STA_BSSID0_LOWER               b;
}   MAC_STA_BSSID0_LOWER_U;


// 0x40080048 register ------------------------------------
typedef struct {
    uint32_t                           STA_BSSID0_UPPER                   :32;
}   MAC_STA_BSSID0_UPPER;

typedef union {
    uint32_t                           w;
    MAC_STA_BSSID0_UPPER               b;
}   MAC_STA_BSSID0_UPPER_U;


// 0x4008004C register ------------------------------------
typedef struct {
    uint32_t                           STA_BSSID1_LOWER                   :32;
}   MAC_STA_BSSID1_LOWER;

typedef union {
    uint32_t                           w;
    MAC_STA_BSSID1_LOWER               b;
}   MAC_STA_BSSID1_LOWER_U;


// 0x40080050 register ------------------------------------
typedef struct {
    uint32_t                           STA_BSSID1_UPPER                   :32;
}   MAC_STA_BSSID1_UPPER;

typedef union {
    uint32_t                           w;
    MAC_STA_BSSID1_UPPER               b;
}   MAC_STA_BSSID1_UPPER_U;


// 0x40080054 register ------------------------------------
typedef struct {
    uint32_t                           STA_BSSID2_LOWER                   :32;
}   MAC_STA_BSSID2_LOWER;

typedef union {
    uint32_t                           w;
    MAC_STA_BSSID2_LOWER               b;
}   MAC_STA_BSSID2_LOWER_U;


// 0x40080058 register ------------------------------------
typedef struct {
    uint32_t                           STA_BSSID2_UPPER                   :32;
}   MAC_STA_BSSID2_UPPER;

typedef union {
    uint32_t                           w;
    MAC_STA_BSSID2_UPPER               b;
}   MAC_STA_BSSID2_UPPER_U;


// 0x4008005C register ------------------------------------
typedef struct {
    uint32_t                           STA_BSSID3_LOWER                   :32;
}   MAC_STA_BSSID3_LOWER;

typedef union {
    uint32_t                           w;
    MAC_STA_BSSID3_LOWER               b;
}   MAC_STA_BSSID3_LOWER_U;


// 0x40080060 register ------------------------------------
typedef struct {
    uint32_t                           STA_BSSID3_UPPER                   :32;
}   MAC_STA_BSSID3_UPPER;

typedef union {
    uint32_t                           w;
    MAC_STA_BSSID3_UPPER               b;
}   MAC_STA_BSSID3_UPPER_U;


// 0x40080064 register ------------------------------------
typedef struct {
    uint32_t                           MAC_ADDRESS0_LOWER                 :32;
}   MAC_MAC_ADDRESS0_LOWER;

typedef union {
    uint32_t                           w;
    MAC_MAC_ADDRESS0_LOWER             b;
}   MAC_MAC_ADDRESS0_LOWER_U;


// 0x40080068 register ------------------------------------
typedef struct {
    uint32_t                           MAC_ADDRESS0_UPPER                 :32;
}   MAC_MAC_ADDRESS0_UPPER;

typedef union {
    uint32_t                           w;
    MAC_MAC_ADDRESS0_UPPER             b;
}   MAC_MAC_ADDRESS0_UPPER_U;


// 0x4008006C register ------------------------------------
typedef struct {
    uint32_t                           MAC_ADDRESS1_LOWER                 :32;
}   MAC_MAC_ADDRESS1_LOWER;

typedef union {
    uint32_t                           w;
    MAC_MAC_ADDRESS1_LOWER             b;
}   MAC_MAC_ADDRESS1_LOWER_U;


// 0x40080070 register ------------------------------------
typedef struct {
    uint32_t                           MAC_ADDRESS1_UPPER                 :32;
}   MAC_MAC_ADDRESS1_UPPER;

typedef union {
    uint32_t                           w;
    MAC_MAC_ADDRESS1_UPPER             b;
}   MAC_MAC_ADDRESS1_UPPER_U;


// 0x40080074 register ------------------------------------
typedef struct {
    uint32_t                           MAC_ADDRESS2_LOWER                 :32;
}   MAC_MAC_ADDRESS2_LOWER;

typedef union {
    uint32_t                           w;
    MAC_MAC_ADDRESS2_LOWER             b;
}   MAC_MAC_ADDRESS2_LOWER_U;


// 0x40080078 register ------------------------------------
typedef struct {
    uint32_t                           MAC_ADDRESS2_UPPER                 :32;
}   MAC_MAC_ADDRESS2_UPPER;

typedef union {
    uint32_t                           w;
    MAC_MAC_ADDRESS2_UPPER             b;
}   MAC_MAC_ADDRESS2_UPPER_U;


// 0x4008007C register ------------------------------------
typedef struct {
    uint32_t                           MAC_ADDRESS3_LOWER                 :32;
}   MAC_MAC_ADDRESS3_LOWER;

typedef union {
    uint32_t                           w;
    MAC_MAC_ADDRESS3_LOWER             b;
}   MAC_MAC_ADDRESS3_LOWER_U;


// 0x40080080 register ------------------------------------
typedef struct {
    uint32_t                           MAC_ADDRESS3_UPPER                 :32;
}   MAC_MAC_ADDRESS3_UPPER;

typedef union {
    uint32_t                           w;
    MAC_MAC_ADDRESS3_UPPER             b;
}   MAC_MAC_ADDRESS3_UPPER_U;


// 0x40080084 register ------------------------------------
typedef struct {
    uint32_t                           STA_AID0_0                         :32;
}   MAC_STA_AID0_0;

typedef union {
    uint32_t                           w;
    MAC_STA_AID0_0                     b;
}   MAC_STA_AID0_0_U;


// 0x40080088 register ------------------------------------
typedef struct {
    uint32_t                           STA_AID0_1                         :32;
}   MAC_STA_AID0_1;

typedef union {
    uint32_t                           w;
    MAC_STA_AID0_1                     b;
}   MAC_STA_AID0_1_U;


// 0x4008008C register ------------------------------------
typedef struct {
    uint32_t                           STA_AID0_2                         :32;
}   MAC_STA_AID0_2;

typedef union {
    uint32_t                           w;
    MAC_STA_AID0_2                     b;
}   MAC_STA_AID0_2_U;


// 0x40080090 register ------------------------------------
typedef struct {
    uint32_t                           STA_AID1_0                         :32;
}   MAC_STA_AID1_0;

typedef union {
    uint32_t                           w;
    MAC_STA_AID1_0                     b;
}   MAC_STA_AID1_0_U;


// 0x40080094 register ------------------------------------
typedef struct {
    uint32_t                           STA_AID1_1                         :32;
}   MAC_STA_AID1_1;

typedef union {
    uint32_t                           w;
    MAC_STA_AID1_1                     b;
}   MAC_STA_AID1_1_U;


// 0x40080098 register ------------------------------------
typedef struct {
    uint32_t                           STA_AID1_2                         :32;
}   MAC_STA_AID1_2;

typedef union {
    uint32_t                           w;
    MAC_STA_AID1_2                     b;
}   MAC_STA_AID1_2_U;


// 0x4008009C register ------------------------------------
typedef struct {
    uint32_t                           STA_AID2_0                         :32;
}   MAC_STA_AID2_0;

typedef union {
    uint32_t                           w;
    MAC_STA_AID2_0                     b;
}   MAC_STA_AID2_0_U;


// 0x400800A0 register ------------------------------------
typedef struct {
    uint32_t                           STA_AID2_1                         :32;
}   MAC_STA_AID2_1;

typedef union {
    uint32_t                           w;
    MAC_STA_AID2_1                     b;
}   MAC_STA_AID2_1_U;


// 0x400800A4 register ------------------------------------
typedef struct {
    uint32_t                           STA_AID2_2                         :32;
}   MAC_STA_AID2_2;

typedef union {
    uint32_t                           w;
    MAC_STA_AID2_2                     b;
}   MAC_STA_AID2_2_U;


// 0x400800A8 register ------------------------------------
typedef struct {
    uint32_t                           STA_AID3_0                         :32;
}   MAC_STA_AID3_0;

typedef union {
    uint32_t                           w;
    MAC_STA_AID3_0                     b;
}   MAC_STA_AID3_0_U;


// 0x400800AC register ------------------------------------
typedef struct {
    uint32_t                           STA_AID3_1                         :32;
}   MAC_STA_AID3_1;

typedef union {
    uint32_t                           w;
    MAC_STA_AID3_1                     b;
}   MAC_STA_AID3_1_U;


// 0x400800B0 register ------------------------------------
typedef struct {
    uint32_t                           STA_AID3_2                         :32;
}   MAC_STA_AID3_2;

typedef union {
    uint32_t                           w;
    MAC_STA_AID3_2                     b;
}   MAC_STA_AID3_2_U;


// 0x400800B4 register ------------------------------------
typedef struct {
    uint32_t                           COMPR_BSSID                        :32;
}   MAC_COMPR_BSSID;

typedef union {
    uint32_t                           w;
    MAC_COMPR_BSSID                    b;
}   MAC_COMPR_BSSID_U;


// 0x400800B8 register ------------------------------------
typedef struct {
    uint32_t                           DMA_BURST_MIN                      :6 ;
    uint32_t                           DMA_BURST_MAX                      :6 ;
    uint32_t                           reserved0                          :20;
}   MAC_DMA_BURST;

typedef union {
    uint32_t                           w;
    MAC_DMA_BURST                      b;
}   MAC_DMA_BURST_U;


// 0x400800BC register ------------------------------------
typedef struct {
    uint32_t                           DMA_READ_FIFO_FULL_ADJUST          :8 ;
    uint32_t                           reserved0                          :12;
    uint32_t                           DMA_READ_FIFO_REFRESH_SIZE         :8 ;
    uint32_t                           reserved1                          :3 ;
    uint32_t                           DMA_READ_FIFO_REFRESH_SWITCH       :1 ;
}   MAC_DMA_READ_FIFO_ADJUST;

typedef union {
    uint32_t                           w;
    MAC_DMA_READ_FIFO_ADJUST           b;
}   MAC_DMA_READ_FIFO_ADJUST_U;


// 0x400800C0 register ------------------------------------
typedef struct {
    uint32_t                           CONCURRENT_CONFIG_BITMAP           :11;
    uint32_t                           PIFS_IDLE_MARGIN                   :5 ;
    uint32_t                           PIFS_IDLE_INDEX_1MHZ               :7 ;
    uint32_t                           PIFS_IDLE_INDEX_2MHZ               :7 ;
    uint32_t                           reserved0                          :1 ;
    uint32_t                           PIFS_IDLE_IGNORE                   :1 ;
}   MAC_CONCURRENT_CONFIG_BITMAP;

typedef union {
    uint32_t                           w;
    MAC_CONCURRENT_CONFIG_BITMAP       b;
}   MAC_CONCURRENT_CONFIG_BITMAP_U;


// 0x400800C4 register ------------------------------------
typedef struct {
    uint32_t                           RESPONSE_WAIT_TIME_US              :8 ;
    uint32_t                           FIRST_FRAG_DATA_WORD_OFFSET        :4 ;
    uint32_t                           OTHER_FRAG_DATA_WORD_OFFSET        :4 ;
    uint32_t                           VECTOR_WAIT_TIME                   :4 ;
    uint32_t                           VECTOR_TIMEOUT                     :8 ;
    uint32_t                           CCA_LATE_DETECTION                 :1 ;
    uint32_t                           TX_ERROR_RECOVERY                  :1 ;
    uint32_t                           RX_RESPONSE_CONTROL                :2 ;
}   MAC_TX_CONTROL_PARAMETER;

typedef union {
    uint32_t                           w;
    MAC_TX_CONTROL_PARAMETER           b;
}   MAC_TX_CONTROL_PARAMETER_U;


// 0x400800C8 register ------------------------------------
typedef struct {
    uint32_t                           RSP0_RX_INFO_AGG                   :1 ;
    uint32_t                           RSP0_OPERATION                     :1 ;
    uint32_t                           RSP0_GROUP_ADDRESS                 :1 ;
    uint32_t                           RSP0_RX_PV                         :1 ;
    uint32_t                           RSP0_RX_PV0_SUBTYPE                :4 ;
    uint32_t                           RSP0_RX_PV0_TYPE                   :2 ;
    uint32_t                           RSP0_RX_NDP_PSPOLL                 :1 ;
    uint32_t                           RSP0_RX_INFO_NDP                   :1 ;
    uint32_t                           RSP0_RX_INFO_OK                    :1 ;
    uint32_t                           RSP0_MASK_RX_INFO_AGG              :1 ;
    uint32_t                           RSP0_MASK_OPERATION                :1 ;
    uint32_t                           RSP0_MASK_GROUP_ADDRESS            :1 ;
    uint32_t                           RSP0_MASK_RX_PV                    :1 ;
    uint32_t                           RSP0_MASK_RX_PV0_SUBTYPE           :4 ;
    uint32_t                           RSP0_MASK_RX_PV0_TYPE              :2 ;
    uint32_t                           RSP0_MASK_RX_NDP_PSPOLL            :1 ;
    uint32_t                           RSP0_MASK_RX_INFO_NDP              :1 ;
    uint32_t                           RSP0_MASK_RX_INFO_OK               :1 ;
    uint32_t                           RSP0_CASE                          :5 ;
    uint32_t                           RSP0_VALID                         :1 ;
}   MAC_RSP0;

typedef union {
    uint32_t                           w;
    MAC_RSP0                           b;
}   MAC_RSP0_U;


// 0x400800CC register ------------------------------------
typedef struct {
    uint32_t                           RSP1_RX_INFO_AGG                   :1 ;
    uint32_t                           RSP1_OPERATION                     :1 ;
    uint32_t                           RSP1_GROUP_ADDRESS                 :1 ;
    uint32_t                           RSP1_RX_PV                         :1 ;
    uint32_t                           RSP1_RX_PV0_SUBTYPE                :4 ;
    uint32_t                           RSP1_RX_PV0_TYPE                   :2 ;
    uint32_t                           RSP1_RX_NDP_PSPOLL                 :1 ;
    uint32_t                           RSP1_RX_INFO_NDP                   :1 ;
    uint32_t                           RSP1_RX_INFO_OK                    :1 ;
    uint32_t                           RSP1_MASK_RX_INFO_AGG              :1 ;
    uint32_t                           RSP1_MASK_OPERATION                :1 ;
    uint32_t                           RSP1_MASK_GROUP_ADDRESS            :1 ;
    uint32_t                           RSP1_MASK_RX_PV                    :1 ;
    uint32_t                           RSP1_MASK_RX_PV0_SUBTYPE           :4 ;
    uint32_t                           RSP1_MASK_RX_PV0_TYPE              :2 ;
    uint32_t                           RSP1_MASK_RX_NDP_PSPOLL            :1 ;
    uint32_t                           RSP1_MASK_RX_INFO_NDP              :1 ;
    uint32_t                           RSP1_MASK_RX_INFO_OK               :1 ;
    uint32_t                           RSP1_CASE                          :5 ;
    uint32_t                           RSP1_VALID                         :1 ;
}   MAC_RSP1;

typedef union {
    uint32_t                           w;
    MAC_RSP1                           b;
}   MAC_RSP1_U;


// 0x400800D0 register ------------------------------------
typedef struct {
    uint32_t                           RSP2_RX_INFO_AGG                   :1 ;
    uint32_t                           RSP2_OPERATION                     :1 ;
    uint32_t                           RSP2_GROUP_ADDRESS                 :1 ;
    uint32_t                           RSP2_RX_PV                         :1 ;
    uint32_t                           RSP2_RX_PV0_SUBTYPE                :4 ;
    uint32_t                           RSP2_RX_PV0_TYPE                   :2 ;
    uint32_t                           RSP2_RX_NDP_PSPOLL                 :1 ;
    uint32_t                           RSP2_RX_INFO_NDP                   :1 ;
    uint32_t                           RSP2_RX_INFO_OK                    :1 ;
    uint32_t                           RSP2_MASK_RX_INFO_AGG              :1 ;
    uint32_t                           RSP2_MASK_OPERATION                :1 ;
    uint32_t                           RSP2_MASK_GROUP_ADDRESS            :1 ;
    uint32_t                           RSP2_MASK_RX_PV                    :1 ;
    uint32_t                           RSP2_MASK_RX_PV0_SUBTYPE           :4 ;
    uint32_t                           RSP2_MASK_RX_PV0_TYPE              :2 ;
    uint32_t                           RSP2_MASK_RX_NDP_PSPOLL            :1 ;
    uint32_t                           RSP2_MASK_RX_INFO_NDP              :1 ;
    uint32_t                           RSP2_MASK_RX_INFO_OK               :1 ;
    uint32_t                           RSP2_CASE                          :5 ;
    uint32_t                           RSP2_VALID                         :1 ;
}   MAC_RSP2;

typedef union {
    uint32_t                           w;
    MAC_RSP2                           b;
}   MAC_RSP2_U;


// 0x400800D4 register ------------------------------------
typedef struct {
    uint32_t                           RSP3_RX_INFO_AGG                   :1 ;
    uint32_t                           RSP3_OPERATION                     :1 ;
    uint32_t                           RSP3_GROUP_ADDRESS                 :1 ;
    uint32_t                           RSP3_RX_PV                         :1 ;
    uint32_t                           RSP3_RX_PV0_SUBTYPE                :4 ;
    uint32_t                           RSP3_RX_PV0_TYPE                   :2 ;
    uint32_t                           RSP3_RX_NDP_PSPOLL                 :1 ;
    uint32_t                           RSP3_RX_INFO_NDP                   :1 ;
    uint32_t                           RSP3_RX_INFO_OK                    :1 ;
    uint32_t                           RSP3_MASK_RX_INFO_AGG              :1 ;
    uint32_t                           RSP3_MASK_OPERATION                :1 ;
    uint32_t                           RSP3_MASK_GROUP_ADDRESS            :1 ;
    uint32_t                           RSP3_MASK_RX_PV                    :1 ;
    uint32_t                           RSP3_MASK_RX_PV0_SUBTYPE           :4 ;
    uint32_t                           RSP3_MASK_RX_PV0_TYPE              :2 ;
    uint32_t                           RSP3_MASK_RX_NDP_PSPOLL            :1 ;
    uint32_t                           RSP3_MASK_RX_INFO_NDP              :1 ;
    uint32_t                           RSP3_MASK_RX_INFO_OK               :1 ;
    uint32_t                           RSP3_CASE                          :5 ;
    uint32_t                           RSP3_VALID                         :1 ;
}   MAC_RSP3;

typedef union {
    uint32_t                           w;
    MAC_RSP3                           b;
}   MAC_RSP3_U;


// 0x400800D8 register ------------------------------------
typedef struct {
    uint32_t                           RSP4_RX_INFO_AGG                   :1 ;
    uint32_t                           RSP4_OPERATION                     :1 ;
    uint32_t                           RSP4_GROUP_ADDRESS                 :1 ;
    uint32_t                           RSP4_RX_PV                         :1 ;
    uint32_t                           RSP4_RX_PV0_SUBTYPE                :4 ;
    uint32_t                           RSP4_RX_PV0_TYPE                   :2 ;
    uint32_t                           RSP4_RX_NDP_PSPOLL                 :1 ;
    uint32_t                           RSP4_RX_INFO_NDP                   :1 ;
    uint32_t                           RSP4_RX_INFO_OK                    :1 ;
    uint32_t                           RSP4_MASK_RX_INFO_AGG              :1 ;
    uint32_t                           RSP4_MASK_OPERATION                :1 ;
    uint32_t                           RSP4_MASK_GROUP_ADDRESS            :1 ;
    uint32_t                           RSP4_MASK_RX_PV                    :1 ;
    uint32_t                           RSP4_MASK_RX_PV0_SUBTYPE           :4 ;
    uint32_t                           RSP4_MASK_RX_PV0_TYPE              :2 ;
    uint32_t                           RSP4_MASK_RX_NDP_PSPOLL            :1 ;
    uint32_t                           RSP4_MASK_RX_INFO_NDP              :1 ;
    uint32_t                           RSP4_MASK_RX_INFO_OK               :1 ;
    uint32_t                           RSP4_CASE                          :5 ;
    uint32_t                           RSP4_VALID                         :1 ;
}   MAC_RSP4;

typedef union {
    uint32_t                           w;
    MAC_RSP4                           b;
}   MAC_RSP4_U;


// 0x400800DC register ------------------------------------
typedef struct {
    uint32_t                           RSP5_RX_INFO_AGG                   :1 ;
    uint32_t                           RSP5_OPERATION                     :1 ;
    uint32_t                           RSP5_GROUP_ADDRESS                 :1 ;
    uint32_t                           RSP5_RX_PV                         :1 ;
    uint32_t                           RSP5_RX_PV0_SUBTYPE                :4 ;
    uint32_t                           RSP5_RX_PV0_TYPE                   :2 ;
    uint32_t                           RSP5_RX_NDP_PSPOLL                 :1 ;
    uint32_t                           RSP5_RX_INFO_NDP                   :1 ;
    uint32_t                           RSP5_RX_INFO_OK                    :1 ;
    uint32_t                           RSP5_MASK_RX_INFO_AGG              :1 ;
    uint32_t                           RSP5_MASK_OPERATION                :1 ;
    uint32_t                           RSP5_MASK_GROUP_ADDRESS            :1 ;
    uint32_t                           RSP5_MASK_RX_PV                    :1 ;
    uint32_t                           RSP5_MASK_RX_PV0_SUBTYPE           :4 ;
    uint32_t                           RSP5_MASK_RX_PV0_TYPE              :2 ;
    uint32_t                           RSP5_MASK_RX_NDP_PSPOLL            :1 ;
    uint32_t                           RSP5_MASK_RX_INFO_NDP              :1 ;
    uint32_t                           RSP5_MASK_RX_INFO_OK               :1 ;
    uint32_t                           RSP5_CASE                          :5 ;
    uint32_t                           RSP5_VALID                         :1 ;
}   MAC_RSP5;

typedef union {
    uint32_t                           w;
    MAC_RSP5                           b;
}   MAC_RSP5_U;


// 0x400800E0 register ------------------------------------
typedef struct {
    uint32_t                           RSP6_RX_INFO_AGG                   :1 ;
    uint32_t                           RSP6_OPERATION                     :1 ;
    uint32_t                           RSP6_GROUP_ADDRESS                 :1 ;
    uint32_t                           RSP6_RX_PV                         :1 ;
    uint32_t                           RSP6_RX_PV0_SUBTYPE                :4 ;
    uint32_t                           RSP6_RX_PV0_TYPE                   :2 ;
    uint32_t                           RSP6_RX_NDP_PSPOLL                 :1 ;
    uint32_t                           RSP6_RX_INFO_NDP                   :1 ;
    uint32_t                           RSP6_RX_INFO_OK                    :1 ;
    uint32_t                           RSP6_MASK_RX_INFO_AGG              :1 ;
    uint32_t                           RSP6_MASK_OPERATION                :1 ;
    uint32_t                           RSP6_MASK_GROUP_ADDRESS            :1 ;
    uint32_t                           RSP6_MASK_RX_PV                    :1 ;
    uint32_t                           RSP6_MASK_RX_PV0_SUBTYPE           :4 ;
    uint32_t                           RSP6_MASK_RX_PV0_TYPE              :2 ;
    uint32_t                           RSP6_MASK_RX_NDP_PSPOLL            :1 ;
    uint32_t                           RSP6_MASK_RX_INFO_NDP              :1 ;
    uint32_t                           RSP6_MASK_RX_INFO_OK               :1 ;
    uint32_t                           RSP6_CASE                          :5 ;
    uint32_t                           RSP6_VALID                         :1 ;
}   MAC_RSP6;

typedef union {
    uint32_t                           w;
    MAC_RSP6                           b;
}   MAC_RSP6_U;


// 0x400800E4 register ------------------------------------
typedef struct {
    uint32_t                           RSP7_RX_INFO_AGG                   :1 ;
    uint32_t                           RSP7_OPERATION                     :1 ;
    uint32_t                           RSP7_GROUP_ADDRESS                 :1 ;
    uint32_t                           RSP7_RX_PV                         :1 ;
    uint32_t                           RSP7_RX_PV0_SUBTYPE                :4 ;
    uint32_t                           RSP7_RX_PV0_TYPE                   :2 ;
    uint32_t                           RSP7_RX_NDP_PSPOLL                 :1 ;
    uint32_t                           RSP7_RX_INFO_NDP                   :1 ;
    uint32_t                           RSP7_RX_INFO_OK                    :1 ;
    uint32_t                           RSP7_MASK_RX_INFO_AGG              :1 ;
    uint32_t                           RSP7_MASK_OPERATION                :1 ;
    uint32_t                           RSP7_MASK_GROUP_ADDRESS            :1 ;
    uint32_t                           RSP7_MASK_RX_PV                    :1 ;
    uint32_t                           RSP7_MASK_RX_PV0_SUBTYPE           :4 ;
    uint32_t                           RSP7_MASK_RX_PV0_TYPE              :2 ;
    uint32_t                           RSP7_MASK_RX_NDP_PSPOLL            :1 ;
    uint32_t                           RSP7_MASK_RX_INFO_NDP              :1 ;
    uint32_t                           RSP7_MASK_RX_INFO_OK               :1 ;
    uint32_t                           RSP7_CASE                          :5 ;
    uint32_t                           RSP7_VALID                         :1 ;
}   MAC_RSP7;

typedef union {
    uint32_t                           w;
    MAC_RSP7                           b;
}   MAC_RSP7_U;


// 0x400800E8 register ------------------------------------
typedef struct {
    uint32_t                           RSP8_RX_INFO_AGG                   :1 ;
    uint32_t                           RSP8_OPERATION                     :1 ;
    uint32_t                           RSP8_GROUP_ADDRESS                 :1 ;
    uint32_t                           RSP8_RX_PV                         :1 ;
    uint32_t                           RSP8_RX_PV0_SUBTYPE                :4 ;
    uint32_t                           RSP8_RX_PV0_TYPE                   :2 ;
    uint32_t                           RSP8_RX_NDP_PSPOLL                 :1 ;
    uint32_t                           RSP8_RX_INFO_NDP                   :1 ;
    uint32_t                           RSP8_RX_INFO_OK                    :1 ;
    uint32_t                           RSP8_MASK_RX_INFO_AGG              :1 ;
    uint32_t                           RSP8_MASK_OPERATION                :1 ;
    uint32_t                           RSP8_MASK_GROUP_ADDRESS            :1 ;
    uint32_t                           RSP8_MASK_RX_PV                    :1 ;
    uint32_t                           RSP8_MASK_RX_PV0_SUBTYPE           :4 ;
    uint32_t                           RSP8_MASK_RX_PV0_TYPE              :2 ;
    uint32_t                           RSP8_MASK_RX_NDP_PSPOLL            :1 ;
    uint32_t                           RSP8_MASK_RX_INFO_NDP              :1 ;
    uint32_t                           RSP8_MASK_RX_INFO_OK               :1 ;
    uint32_t                           RSP8_CASE                          :5 ;
    uint32_t                           RSP8_VALID                         :1 ;
}   MAC_RSP8;

typedef union {
    uint32_t                           w;
    MAC_RSP8                           b;
}   MAC_RSP8_U;


// 0x400800EC register ------------------------------------
typedef struct {
    uint32_t                           RSP9_RX_INFO_AGG                   :1 ;
    uint32_t                           RSP9_OPERATION                     :1 ;
    uint32_t                           RSP9_GROUP_ADDRESS                 :1 ;
    uint32_t                           RSP9_RX_PV                         :1 ;
    uint32_t                           RSP9_RX_PV0_SUBTYPE                :4 ;
    uint32_t                           RSP9_RX_PV0_TYPE                   :2 ;
    uint32_t                           RSP9_RX_NDP_PSPOLL                 :1 ;
    uint32_t                           RSP9_RX_INFO_NDP                   :1 ;
    uint32_t                           RSP9_RX_INFO_OK                    :1 ;
    uint32_t                           RSP9_MASK_RX_INFO_AGG              :1 ;
    uint32_t                           RSP9_MASK_OPERATION                :1 ;
    uint32_t                           RSP9_MASK_GROUP_ADDRESS            :1 ;
    uint32_t                           RSP9_MASK_RX_PV                    :1 ;
    uint32_t                           RSP9_MASK_RX_PV0_SUBTYPE           :4 ;
    uint32_t                           RSP9_MASK_RX_PV0_TYPE              :2 ;
    uint32_t                           RSP9_MASK_RX_NDP_PSPOLL            :1 ;
    uint32_t                           RSP9_MASK_RX_INFO_NDP              :1 ;
    uint32_t                           RSP9_MASK_RX_INFO_OK               :1 ;
    uint32_t                           RSP9_CASE                          :5 ;
    uint32_t                           RSP9_VALID                         :1 ;
}   MAC_RSP9;

typedef union {
    uint32_t                           w;
    MAC_RSP9                           b;
}   MAC_RSP9_U;


// 0x400800F0 register ------------------------------------
typedef struct {
    uint32_t                           RSP10_RX_INFO_AGG                  :1 ;
    uint32_t                           RSP10_OPERATION                    :1 ;
    uint32_t                           RSP10_GROUP_ADDRESS                :1 ;
    uint32_t                           RSP10_RX_PV                        :1 ;
    uint32_t                           RSP10_RX_PV0_SUBTYPE               :4 ;
    uint32_t                           RSP10_RX_PV0_TYPE                  :2 ;
    uint32_t                           RSP10_RX_NDP_PSPOLL                :1 ;
    uint32_t                           RSP10_RX_INFO_NDP                  :1 ;
    uint32_t                           RSP10_RX_INFO_OK                   :1 ;
    uint32_t                           RSP10_MASK_RX_INFO_AGG             :1 ;
    uint32_t                           RSP10_MASK_OPERATION               :1 ;
    uint32_t                           RSP10_MASK_GROUP_ADDRESS           :1 ;
    uint32_t                           RSP10_MASK_RX_PV                   :1 ;
    uint32_t                           RSP10_MASK_RX_PV0_SUBTYPE          :4 ;
    uint32_t                           RSP10_MASK_RX_PV0_TYPE             :2 ;
    uint32_t                           RSP10_MASK_RX_NDP_PSPOLL           :1 ;
    uint32_t                           RSP10_MASK_RX_INFO_NDP             :1 ;
    uint32_t                           RSP10_MASK_RX_INFO_OK              :1 ;
    uint32_t                           RSP10_CASE                         :5 ;
    uint32_t                           RSP10_VALID                        :1 ;
}   MAC_RSP10;

typedef union {
    uint32_t                           w;
    MAC_RSP10                          b;
}   MAC_RSP10_U;


// 0x400800F4 register ------------------------------------
typedef struct {
    uint32_t                           RSP11_RX_INFO_AGG                  :1 ;
    uint32_t                           RSP11_OPERATION                    :1 ;
    uint32_t                           RSP11_GROUP_ADDRESS                :1 ;
    uint32_t                           RSP11_RX_PV                        :1 ;
    uint32_t                           RSP11_RX_PV0_SUBTYPE               :4 ;
    uint32_t                           RSP11_RX_PV0_TYPE                  :2 ;
    uint32_t                           RSP11_RX_NDP_PSPOLL                :1 ;
    uint32_t                           RSP11_RX_INFO_NDP                  :1 ;
    uint32_t                           RSP11_RX_INFO_OK                   :1 ;
    uint32_t                           RSP11_MASK_RX_INFO_AGG             :1 ;
    uint32_t                           RSP11_MASK_OPERATION               :1 ;
    uint32_t                           RSP11_MASK_GROUP_ADDRESS           :1 ;
    uint32_t                           RSP11_MASK_RX_PV                   :1 ;
    uint32_t                           RSP11_MASK_RX_PV0_SUBTYPE          :4 ;
    uint32_t                           RSP11_MASK_RX_PV0_TYPE             :2 ;
    uint32_t                           RSP11_MASK_RX_NDP_PSPOLL           :1 ;
    uint32_t                           RSP11_MASK_RX_INFO_NDP             :1 ;
    uint32_t                           RSP11_MASK_RX_INFO_OK              :1 ;
    uint32_t                           RSP11_CASE                         :5 ;
    uint32_t                           RSP11_VALID                        :1 ;
}   MAC_RSP11;

typedef union {
    uint32_t                           w;
    MAC_RSP11                          b;
}   MAC_RSP11_U;


// 0x400800F8 register ------------------------------------
typedef struct {
    uint32_t                           RSP12_RX_INFO_AGG                  :1 ;
    uint32_t                           RSP12_OPERATION                    :1 ;
    uint32_t                           RSP12_GROUP_ADDRESS                :1 ;
    uint32_t                           RSP12_RX_PV                        :1 ;
    uint32_t                           RSP12_RX_PV0_SUBTYPE               :4 ;
    uint32_t                           RSP12_RX_PV0_TYPE                  :2 ;
    uint32_t                           RSP12_RX_NDP_PSPOLL                :1 ;
    uint32_t                           RSP12_RX_INFO_NDP                  :1 ;
    uint32_t                           RSP12_RX_INFO_OK                   :1 ;
    uint32_t                           RSP12_MASK_RX_INFO_AGG             :1 ;
    uint32_t                           RSP12_MASK_OPERATION               :1 ;
    uint32_t                           RSP12_MASK_GROUP_ADDRESS           :1 ;
    uint32_t                           RSP12_MASK_RX_PV                   :1 ;
    uint32_t                           RSP12_MASK_RX_PV0_SUBTYPE          :4 ;
    uint32_t                           RSP12_MASK_RX_PV0_TYPE             :2 ;
    uint32_t                           RSP12_MASK_RX_NDP_PSPOLL           :1 ;
    uint32_t                           RSP12_MASK_RX_INFO_NDP             :1 ;
    uint32_t                           RSP12_MASK_RX_INFO_OK              :1 ;
    uint32_t                           RSP12_CASE                         :5 ;
    uint32_t                           RSP12_VALID                        :1 ;
}   MAC_RSP12;

typedef union {
    uint32_t                           w;
    MAC_RSP12                          b;
}   MAC_RSP12_U;


// 0x400800FC register ------------------------------------
typedef struct {
    uint32_t                           RSP13_RX_INFO_AGG                  :1 ;
    uint32_t                           RSP13_OPERATION                    :1 ;
    uint32_t                           RSP13_GROUP_ADDRESS                :1 ;
    uint32_t                           RSP13_RX_PV                        :1 ;
    uint32_t                           RSP13_RX_PV0_SUBTYPE               :4 ;
    uint32_t                           RSP13_RX_PV0_TYPE                  :2 ;
    uint32_t                           RSP13_RX_NDP_PSPOLL                :1 ;
    uint32_t                           RSP13_RX_INFO_NDP                  :1 ;
    uint32_t                           RSP13_RX_INFO_OK                   :1 ;
    uint32_t                           RSP13_MASK_RX_INFO_AGG             :1 ;
    uint32_t                           RSP13_MASK_OPERATION               :1 ;
    uint32_t                           RSP13_MASK_GROUP_ADDRESS           :1 ;
    uint32_t                           RSP13_MASK_RX_PV                   :1 ;
    uint32_t                           RSP13_MASK_RX_PV0_SUBTYPE          :4 ;
    uint32_t                           RSP13_MASK_RX_PV0_TYPE             :2 ;
    uint32_t                           RSP13_MASK_RX_NDP_PSPOLL           :1 ;
    uint32_t                           RSP13_MASK_RX_INFO_NDP             :1 ;
    uint32_t                           RSP13_MASK_RX_INFO_OK              :1 ;
    uint32_t                           RSP13_CASE                         :5 ;
    uint32_t                           RSP13_VALID                        :1 ;
}   MAC_RSP13;

typedef union {
    uint32_t                           w;
    MAC_RSP13                          b;
}   MAC_RSP13_U;


// 0x40080100 register ------------------------------------
typedef struct {
    uint32_t                           RSP14_RX_INFO_AGG                  :1 ;
    uint32_t                           RSP14_OPERATION                    :1 ;
    uint32_t                           RSP14_GROUP_ADDRESS                :1 ;
    uint32_t                           RSP14_RX_PV                        :1 ;
    uint32_t                           RSP14_RX_PV0_SUBTYPE               :4 ;
    uint32_t                           RSP14_RX_PV0_TYPE                  :2 ;
    uint32_t                           RSP14_RX_NDP_PSPOLL                :1 ;
    uint32_t                           RSP14_RX_INFO_NDP                  :1 ;
    uint32_t                           RSP14_RX_INFO_OK                   :1 ;
    uint32_t                           RSP14_MASK_RX_INFO_AGG             :1 ;
    uint32_t                           RSP14_MASK_OPERATION               :1 ;
    uint32_t                           RSP14_MASK_GROUP_ADDRESS           :1 ;
    uint32_t                           RSP14_MASK_RX_PV                   :1 ;
    uint32_t                           RSP14_MASK_RX_PV0_SUBTYPE          :4 ;
    uint32_t                           RSP14_MASK_RX_PV0_TYPE             :2 ;
    uint32_t                           RSP14_MASK_RX_NDP_PSPOLL           :1 ;
    uint32_t                           RSP14_MASK_RX_INFO_NDP             :1 ;
    uint32_t                           RSP14_MASK_RX_INFO_OK              :1 ;
    uint32_t                           RSP14_CASE                         :5 ;
    uint32_t                           RSP14_VALID                        :1 ;
}   MAC_RSP14;

typedef union {
    uint32_t                           w;
    MAC_RSP14                          b;
}   MAC_RSP14_U;


// 0x40080104 register ------------------------------------
typedef struct {
    uint32_t                           RSP15_RX_INFO_AGG                  :1 ;
    uint32_t                           RSP15_OPERATION                    :1 ;
    uint32_t                           RSP15_GROUP_ADDRESS                :1 ;
    uint32_t                           RSP15_RX_PV                        :1 ;
    uint32_t                           RSP15_RX_PV0_SUBTYPE               :4 ;
    uint32_t                           RSP15_RX_PV0_TYPE                  :2 ;
    uint32_t                           RSP15_RX_NDP_PSPOLL                :1 ;
    uint32_t                           RSP15_RX_INFO_NDP                  :1 ;
    uint32_t                           RSP15_RX_INFO_OK                   :1 ;
    uint32_t                           RSP15_MASK_RX_INFO_AGG             :1 ;
    uint32_t                           RSP15_MASK_OPERATION               :1 ;
    uint32_t                           RSP15_MASK_GROUP_ADDRESS           :1 ;
    uint32_t                           RSP15_MASK_RX_PV                   :1 ;
    uint32_t                           RSP15_MASK_RX_PV0_SUBTYPE          :4 ;
    uint32_t                           RSP15_MASK_RX_PV0_TYPE             :2 ;
    uint32_t                           RSP15_MASK_RX_NDP_PSPOLL           :1 ;
    uint32_t                           RSP15_MASK_RX_INFO_NDP             :1 ;
    uint32_t                           RSP15_MASK_RX_INFO_OK              :1 ;
    uint32_t                           RSP15_CASE                         :5 ;
    uint32_t                           RSP15_VALID                        :1 ;
}   MAC_RSP15;

typedef union {
    uint32_t                           w;
    MAC_RSP15                          b;
}   MAC_RSP15_U;


// 0x40080108 register ------------------------------------
typedef struct {
    uint32_t                           RSP16_RX_INFO_AGG                  :1 ;
    uint32_t                           RSP16_OPERATION                    :1 ;
    uint32_t                           RSP16_GROUP_ADDRESS                :1 ;
    uint32_t                           RSP16_RX_PV                        :1 ;
    uint32_t                           RSP16_RX_PV0_SUBTYPE               :4 ;
    uint32_t                           RSP16_RX_PV0_TYPE                  :2 ;
    uint32_t                           RSP16_RX_NDP_PSPOLL                :1 ;
    uint32_t                           RSP16_RX_INFO_NDP                  :1 ;
    uint32_t                           RSP16_RX_INFO_OK                   :1 ;
    uint32_t                           RSP16_MASK_RX_INFO_AGG             :1 ;
    uint32_t                           RSP16_MASK_OPERATION               :1 ;
    uint32_t                           RSP16_MASK_GROUP_ADDRESS           :1 ;
    uint32_t                           RSP16_MASK_RX_PV                   :1 ;
    uint32_t                           RSP16_MASK_RX_PV0_SUBTYPE          :4 ;
    uint32_t                           RSP16_MASK_RX_PV0_TYPE             :2 ;
    uint32_t                           RSP16_MASK_RX_NDP_PSPOLL           :1 ;
    uint32_t                           RSP16_MASK_RX_INFO_NDP             :1 ;
    uint32_t                           RSP16_MASK_RX_INFO_OK              :1 ;
    uint32_t                           RSP16_CASE                         :5 ;
    uint32_t                           RSP16_VALID                        :1 ;
}   MAC_RSP16;

typedef union {
    uint32_t                           w;
    MAC_RSP16                          b;
}   MAC_RSP16_U;


// 0x4008010C register ------------------------------------
typedef struct {
    uint32_t                           RSP17_RX_INFO_AGG                  :1 ;
    uint32_t                           RSP17_OPERATION                    :1 ;
    uint32_t                           RSP17_GROUP_ADDRESS                :1 ;
    uint32_t                           RSP17_RX_PV                        :1 ;
    uint32_t                           RSP17_RX_PV0_SUBTYPE               :4 ;
    uint32_t                           RSP17_RX_PV0_TYPE                  :2 ;
    uint32_t                           RSP17_RX_NDP_PSPOLL                :1 ;
    uint32_t                           RSP17_RX_INFO_NDP                  :1 ;
    uint32_t                           RSP17_RX_INFO_OK                   :1 ;
    uint32_t                           RSP17_MASK_RX_INFO_AGG             :1 ;
    uint32_t                           RSP17_MASK_OPERATION               :1 ;
    uint32_t                           RSP17_MASK_GROUP_ADDRESS           :1 ;
    uint32_t                           RSP17_MASK_RX_PV                   :1 ;
    uint32_t                           RSP17_MASK_RX_PV0_SUBTYPE          :4 ;
    uint32_t                           RSP17_MASK_RX_PV0_TYPE             :2 ;
    uint32_t                           RSP17_MASK_RX_NDP_PSPOLL           :1 ;
    uint32_t                           RSP17_MASK_RX_INFO_NDP             :1 ;
    uint32_t                           RSP17_MASK_RX_INFO_OK              :1 ;
    uint32_t                           RSP17_CASE                         :5 ;
    uint32_t                           RSP17_VALID                        :1 ;
}   MAC_RSP17;

typedef union {
    uint32_t                           w;
    MAC_RSP17                          b;
}   MAC_RSP17_U;


// 0x40080110 register ------------------------------------
typedef struct {
    uint32_t                           RSP18_RX_INFO_AGG                  :1 ;
    uint32_t                           RSP18_OPERATION                    :1 ;
    uint32_t                           RSP18_GROUP_ADDRESS                :1 ;
    uint32_t                           RSP18_RX_PV                        :1 ;
    uint32_t                           RSP18_RX_PV0_SUBTYPE               :4 ;
    uint32_t                           RSP18_RX_PV0_TYPE                  :2 ;
    uint32_t                           RSP18_RX_NDP_PSPOLL                :1 ;
    uint32_t                           RSP18_RX_INFO_NDP                  :1 ;
    uint32_t                           RSP18_RX_INFO_OK                   :1 ;
    uint32_t                           RSP18_MASK_RX_INFO_AGG             :1 ;
    uint32_t                           RSP18_MASK_OPERATION               :1 ;
    uint32_t                           RSP18_MASK_GROUP_ADDRESS           :1 ;
    uint32_t                           RSP18_MASK_RX_PV                   :1 ;
    uint32_t                           RSP18_MASK_RX_PV0_SUBTYPE          :4 ;
    uint32_t                           RSP18_MASK_RX_PV0_TYPE             :2 ;
    uint32_t                           RSP18_MASK_RX_NDP_PSPOLL           :1 ;
    uint32_t                           RSP18_MASK_RX_INFO_NDP             :1 ;
    uint32_t                           RSP18_MASK_RX_INFO_OK              :1 ;
    uint32_t                           RSP18_CASE                         :5 ;
    uint32_t                           RSP18_VALID                        :1 ;
}   MAC_RSP18;

typedef union {
    uint32_t                           w;
    MAC_RSP18                          b;
}   MAC_RSP18_U;


// 0x40080114 register ------------------------------------
typedef struct {
    uint32_t                           RSP19_RX_INFO_AGG                  :1 ;
    uint32_t                           RSP19_OPERATION                    :1 ;
    uint32_t                           RSP19_GROUP_ADDRESS                :1 ;
    uint32_t                           RSP19_RX_PV                        :1 ;
    uint32_t                           RSP19_RX_PV0_SUBTYPE               :4 ;
    uint32_t                           RSP19_RX_PV0_TYPE                  :2 ;
    uint32_t                           RSP19_RX_NDP_PSPOLL                :1 ;
    uint32_t                           RSP19_RX_INFO_NDP                  :1 ;
    uint32_t                           RSP19_RX_INFO_OK                   :1 ;
    uint32_t                           RSP19_MASK_RX_INFO_AGG             :1 ;
    uint32_t                           RSP19_MASK_OPERATION               :1 ;
    uint32_t                           RSP19_MASK_GROUP_ADDRESS           :1 ;
    uint32_t                           RSP19_MASK_RX_PV                   :1 ;
    uint32_t                           RSP19_MASK_RX_PV0_SUBTYPE          :4 ;
    uint32_t                           RSP19_MASK_RX_PV0_TYPE             :2 ;
    uint32_t                           RSP19_MASK_RX_NDP_PSPOLL           :1 ;
    uint32_t                           RSP19_MASK_RX_INFO_NDP             :1 ;
    uint32_t                           RSP19_MASK_RX_INFO_OK              :1 ;
    uint32_t                           RSP19_CASE                         :5 ;
    uint32_t                           RSP19_VALID                        :1 ;
}   MAC_RSP19;

typedef union {
    uint32_t                           w;
    MAC_RSP19                          b;
}   MAC_RSP19_U;


// 0x40080118 register ------------------------------------
typedef struct {
    uint32_t                           RSP20_RX_INFO_AGG                  :1 ;
    uint32_t                           RSP20_OPERATION                    :1 ;
    uint32_t                           RSP20_GROUP_ADDRESS                :1 ;
    uint32_t                           RSP20_RX_PV                        :1 ;
    uint32_t                           RSP20_RX_PV0_SUBTYPE               :4 ;
    uint32_t                           RSP20_RX_PV0_TYPE                  :2 ;
    uint32_t                           RSP20_RX_NDP_PSPOLL                :1 ;
    uint32_t                           RSP20_RX_INFO_NDP                  :1 ;
    uint32_t                           RSP20_RX_INFO_OK                   :1 ;
    uint32_t                           RSP20_MASK_RX_INFO_AGG             :1 ;
    uint32_t                           RSP20_MASK_OPERATION               :1 ;
    uint32_t                           RSP20_MASK_GROUP_ADDRESS           :1 ;
    uint32_t                           RSP20_MASK_RX_PV                   :1 ;
    uint32_t                           RSP20_MASK_RX_PV0_SUBTYPE          :4 ;
    uint32_t                           RSP20_MASK_RX_PV0_TYPE             :2 ;
    uint32_t                           RSP20_MASK_RX_NDP_PSPOLL           :1 ;
    uint32_t                           RSP20_MASK_RX_INFO_NDP             :1 ;
    uint32_t                           RSP20_MASK_RX_INFO_OK              :1 ;
    uint32_t                           RSP20_CASE                         :5 ;
    uint32_t                           RSP20_VALID                        :1 ;
}   MAC_RSP20;

typedef union {
    uint32_t                           w;
    MAC_RSP20                          b;
}   MAC_RSP20_U;


// 0x4008011C register ------------------------------------
typedef struct {
    uint32_t                           RSP21_RX_INFO_AGG                  :1 ;
    uint32_t                           RSP21_OPERATION                    :1 ;
    uint32_t                           RSP21_GROUP_ADDRESS                :1 ;
    uint32_t                           RSP21_RX_PV                        :1 ;
    uint32_t                           RSP21_RX_PV0_SUBTYPE               :4 ;
    uint32_t                           RSP21_RX_PV0_TYPE                  :2 ;
    uint32_t                           RSP21_RX_NDP_PSPOLL                :1 ;
    uint32_t                           RSP21_RX_INFO_NDP                  :1 ;
    uint32_t                           RSP21_RX_INFO_OK                   :1 ;
    uint32_t                           RSP21_MASK_RX_INFO_AGG             :1 ;
    uint32_t                           RSP21_MASK_OPERATION               :1 ;
    uint32_t                           RSP21_MASK_GROUP_ADDRESS           :1 ;
    uint32_t                           RSP21_MASK_RX_PV                   :1 ;
    uint32_t                           RSP21_MASK_RX_PV0_SUBTYPE          :4 ;
    uint32_t                           RSP21_MASK_RX_PV0_TYPE             :2 ;
    uint32_t                           RSP21_MASK_RX_NDP_PSPOLL           :1 ;
    uint32_t                           RSP21_MASK_RX_INFO_NDP             :1 ;
    uint32_t                           RSP21_MASK_RX_INFO_OK              :1 ;
    uint32_t                           RSP21_CASE                         :5 ;
    uint32_t                           RSP21_VALID                        :1 ;
}   MAC_RSP21;

typedef union {
    uint32_t                           w;
    MAC_RSP21                          b;
}   MAC_RSP21_U;


// 0x40080120 register ------------------------------------
typedef struct {
    uint32_t                           RSP22_RX_INFO_AGG                  :1 ;
    uint32_t                           RSP22_OPERATION                    :1 ;
    uint32_t                           RSP22_GROUP_ADDRESS                :1 ;
    uint32_t                           RSP22_RX_PV                        :1 ;
    uint32_t                           RSP22_RX_PV0_SUBTYPE               :4 ;
    uint32_t                           RSP22_RX_PV0_TYPE                  :2 ;
    uint32_t                           RSP22_RX_NDP_PSPOLL                :1 ;
    uint32_t                           RSP22_RX_INFO_NDP                  :1 ;
    uint32_t                           RSP22_RX_INFO_OK                   :1 ;
    uint32_t                           RSP22_MASK_RX_INFO_AGG             :1 ;
    uint32_t                           RSP22_MASK_OPERATION               :1 ;
    uint32_t                           RSP22_MASK_GROUP_ADDRESS           :1 ;
    uint32_t                           RSP22_MASK_RX_PV                   :1 ;
    uint32_t                           RSP22_MASK_RX_PV0_SUBTYPE          :4 ;
    uint32_t                           RSP22_MASK_RX_PV0_TYPE             :2 ;
    uint32_t                           RSP22_MASK_RX_NDP_PSPOLL           :1 ;
    uint32_t                           RSP22_MASK_RX_INFO_NDP             :1 ;
    uint32_t                           RSP22_MASK_RX_INFO_OK              :1 ;
    uint32_t                           RSP22_CASE                         :5 ;
    uint32_t                           RSP22_VALID                        :1 ;
}   MAC_RSP22;

typedef union {
    uint32_t                           w;
    MAC_RSP22                          b;
}   MAC_RSP22_U;


// 0x40080124 register ------------------------------------
typedef struct {
    uint32_t                           RSP23_RX_INFO_AGG                  :1 ;
    uint32_t                           RSP23_OPERATION                    :1 ;
    uint32_t                           RSP23_GROUP_ADDRESS                :1 ;
    uint32_t                           RSP23_RX_PV                        :1 ;
    uint32_t                           RSP23_RX_PV0_SUBTYPE               :4 ;
    uint32_t                           RSP23_RX_PV0_TYPE                  :2 ;
    uint32_t                           RSP23_RX_NDP_PSPOLL                :1 ;
    uint32_t                           RSP23_RX_INFO_NDP                  :1 ;
    uint32_t                           RSP23_RX_INFO_OK                   :1 ;
    uint32_t                           RSP23_MASK_RX_INFO_AGG             :1 ;
    uint32_t                           RSP23_MASK_OPERATION               :1 ;
    uint32_t                           RSP23_MASK_GROUP_ADDRESS           :1 ;
    uint32_t                           RSP23_MASK_RX_PV                   :1 ;
    uint32_t                           RSP23_MASK_RX_PV0_SUBTYPE          :4 ;
    uint32_t                           RSP23_MASK_RX_PV0_TYPE             :2 ;
    uint32_t                           RSP23_MASK_RX_NDP_PSPOLL           :1 ;
    uint32_t                           RSP23_MASK_RX_INFO_NDP             :1 ;
    uint32_t                           RSP23_MASK_RX_INFO_OK              :1 ;
    uint32_t                           RSP23_CASE                         :5 ;
    uint32_t                           RSP23_VALID                        :1 ;
}   MAC_RSP23;

typedef union {
    uint32_t                           w;
    MAC_RSP23                          b;
}   MAC_RSP23_U;


// 0x40080128 register ------------------------------------
typedef struct {
    uint32_t                           RSP24_RX_INFO_AGG                  :1 ;
    uint32_t                           RSP24_OPERATION                    :1 ;
    uint32_t                           RSP24_GROUP_ADDRESS                :1 ;
    uint32_t                           RSP24_RX_PV                        :1 ;
    uint32_t                           RSP24_RX_PV0_SUBTYPE               :4 ;
    uint32_t                           RSP24_RX_PV0_TYPE                  :2 ;
    uint32_t                           RSP24_RX_NDP_PSPOLL                :1 ;
    uint32_t                           RSP24_RX_INFO_NDP                  :1 ;
    uint32_t                           RSP24_RX_INFO_OK                   :1 ;
    uint32_t                           RSP24_MASK_RX_INFO_AGG             :1 ;
    uint32_t                           RSP24_MASK_OPERATION               :1 ;
    uint32_t                           RSP24_MASK_GROUP_ADDRESS           :1 ;
    uint32_t                           RSP24_MASK_RX_PV                   :1 ;
    uint32_t                           RSP24_MASK_RX_PV0_SUBTYPE          :4 ;
    uint32_t                           RSP24_MASK_RX_PV0_TYPE             :2 ;
    uint32_t                           RSP24_MASK_RX_NDP_PSPOLL           :1 ;
    uint32_t                           RSP24_MASK_RX_INFO_NDP             :1 ;
    uint32_t                           RSP24_MASK_RX_INFO_OK              :1 ;
    uint32_t                           RSP24_CASE                         :5 ;
    uint32_t                           RSP24_VALID                        :1 ;
}   MAC_RSP24;

typedef union {
    uint32_t                           w;
    MAC_RSP24                          b;
}   MAC_RSP24_U;


// 0x4008012C register ------------------------------------
typedef struct {
    uint32_t                           RSP25_RX_INFO_AGG                  :1 ;
    uint32_t                           RSP25_OPERATION                    :1 ;
    uint32_t                           RSP25_GROUP_ADDRESS                :1 ;
    uint32_t                           RSP25_RX_PV                        :1 ;
    uint32_t                           RSP25_RX_PV0_SUBTYPE               :4 ;
    uint32_t                           RSP25_RX_PV0_TYPE                  :2 ;
    uint32_t                           RSP25_RX_NDP_PSPOLL                :1 ;
    uint32_t                           RSP25_RX_INFO_NDP                  :1 ;
    uint32_t                           RSP25_RX_INFO_OK                   :1 ;
    uint32_t                           RSP25_MASK_RX_INFO_AGG             :1 ;
    uint32_t                           RSP25_MASK_OPERATION               :1 ;
    uint32_t                           RSP25_MASK_GROUP_ADDRESS           :1 ;
    uint32_t                           RSP25_MASK_RX_PV                   :1 ;
    uint32_t                           RSP25_MASK_RX_PV0_SUBTYPE          :4 ;
    uint32_t                           RSP25_MASK_RX_PV0_TYPE             :2 ;
    uint32_t                           RSP25_MASK_RX_NDP_PSPOLL           :1 ;
    uint32_t                           RSP25_MASK_RX_INFO_NDP             :1 ;
    uint32_t                           RSP25_MASK_RX_INFO_OK              :1 ;
    uint32_t                           RSP25_CASE                         :5 ;
    uint32_t                           RSP25_VALID                        :1 ;
}   MAC_RSP25;

typedef union {
    uint32_t                           w;
    MAC_RSP25                          b;
}   MAC_RSP25_U;


// 0x40080130 register ------------------------------------
typedef struct {
    uint32_t                           RSP26_RX_INFO_AGG                  :1 ;
    uint32_t                           RSP26_OPERATION                    :1 ;
    uint32_t                           RSP26_GROUP_ADDRESS                :1 ;
    uint32_t                           RSP26_RX_PV                        :1 ;
    uint32_t                           RSP26_RX_PV0_SUBTYPE               :4 ;
    uint32_t                           RSP26_RX_PV0_TYPE                  :2 ;
    uint32_t                           RSP26_RX_NDP_PSPOLL                :1 ;
    uint32_t                           RSP26_RX_INFO_NDP                  :1 ;
    uint32_t                           RSP26_RX_INFO_OK                   :1 ;
    uint32_t                           RSP26_MASK_RX_INFO_AGG             :1 ;
    uint32_t                           RSP26_MASK_OPERATION               :1 ;
    uint32_t                           RSP26_MASK_GROUP_ADDRESS           :1 ;
    uint32_t                           RSP26_MASK_RX_PV                   :1 ;
    uint32_t                           RSP26_MASK_RX_PV0_SUBTYPE          :4 ;
    uint32_t                           RSP26_MASK_RX_PV0_TYPE             :2 ;
    uint32_t                           RSP26_MASK_RX_NDP_PSPOLL           :1 ;
    uint32_t                           RSP26_MASK_RX_INFO_NDP             :1 ;
    uint32_t                           RSP26_MASK_RX_INFO_OK              :1 ;
    uint32_t                           RSP26_CASE                         :5 ;
    uint32_t                           RSP26_VALID                        :1 ;
}   MAC_RSP26;

typedef union {
    uint32_t                           w;
    MAC_RSP26                          b;
}   MAC_RSP26_U;


// 0x40080134 register ------------------------------------
typedef struct {
    uint32_t                           RSP27_RX_INFO_AGG                  :1 ;
    uint32_t                           RSP27_OPERATION                    :1 ;
    uint32_t                           RSP27_GROUP_ADDRESS                :1 ;
    uint32_t                           RSP27_RX_PV                        :1 ;
    uint32_t                           RSP27_RX_PV0_SUBTYPE               :4 ;
    uint32_t                           RSP27_RX_PV0_TYPE                  :2 ;
    uint32_t                           RSP27_RX_NDP_PSPOLL                :1 ;
    uint32_t                           RSP27_RX_INFO_NDP                  :1 ;
    uint32_t                           RSP27_RX_INFO_OK                   :1 ;
    uint32_t                           RSP27_MASK_RX_INFO_AGG             :1 ;
    uint32_t                           RSP27_MASK_OPERATION               :1 ;
    uint32_t                           RSP27_MASK_GROUP_ADDRESS           :1 ;
    uint32_t                           RSP27_MASK_RX_PV                   :1 ;
    uint32_t                           RSP27_MASK_RX_PV0_SUBTYPE          :4 ;
    uint32_t                           RSP27_MASK_RX_PV0_TYPE             :2 ;
    uint32_t                           RSP27_MASK_RX_NDP_PSPOLL           :1 ;
    uint32_t                           RSP27_MASK_RX_INFO_NDP             :1 ;
    uint32_t                           RSP27_MASK_RX_INFO_OK              :1 ;
    uint32_t                           RSP27_CASE                         :5 ;
    uint32_t                           RSP27_VALID                        :1 ;
}   MAC_RSP27;

typedef union {
    uint32_t                           w;
    MAC_RSP27                          b;
}   MAC_RSP27_U;


// 0x40080138 register ------------------------------------
typedef struct {
    uint32_t                           RSP28_RX_INFO_AGG                  :1 ;
    uint32_t                           RSP28_OPERATION                    :1 ;
    uint32_t                           RSP28_GROUP_ADDRESS                :1 ;
    uint32_t                           RSP28_RX_PV                        :1 ;
    uint32_t                           RSP28_RX_PV0_SUBTYPE               :4 ;
    uint32_t                           RSP28_RX_PV0_TYPE                  :2 ;
    uint32_t                           RSP28_RX_NDP_PSPOLL                :1 ;
    uint32_t                           RSP28_RX_INFO_NDP                  :1 ;
    uint32_t                           RSP28_RX_INFO_OK                   :1 ;
    uint32_t                           RSP28_MASK_RX_INFO_AGG             :1 ;
    uint32_t                           RSP28_MASK_OPERATION               :1 ;
    uint32_t                           RSP28_MASK_GROUP_ADDRESS           :1 ;
    uint32_t                           RSP28_MASK_RX_PV                   :1 ;
    uint32_t                           RSP28_MASK_RX_PV0_SUBTYPE          :4 ;
    uint32_t                           RSP28_MASK_RX_PV0_TYPE             :2 ;
    uint32_t                           RSP28_MASK_RX_NDP_PSPOLL           :1 ;
    uint32_t                           RSP28_MASK_RX_INFO_NDP             :1 ;
    uint32_t                           RSP28_MASK_RX_INFO_OK              :1 ;
    uint32_t                           RSP28_CASE                         :5 ;
    uint32_t                           RSP28_VALID                        :1 ;
}   MAC_RSP28;

typedef union {
    uint32_t                           w;
    MAC_RSP28                          b;
}   MAC_RSP28_U;


// 0x4008013C register ------------------------------------
typedef struct {
    uint32_t                           RSP29_RX_INFO_AGG                  :1 ;
    uint32_t                           RSP29_OPERATION                    :1 ;
    uint32_t                           RSP29_GROUP_ADDRESS                :1 ;
    uint32_t                           RSP29_RX_PV                        :1 ;
    uint32_t                           RSP29_RX_PV0_SUBTYPE               :4 ;
    uint32_t                           RSP29_RX_PV0_TYPE                  :2 ;
    uint32_t                           RSP29_RX_NDP_PSPOLL                :1 ;
    uint32_t                           RSP29_RX_INFO_NDP                  :1 ;
    uint32_t                           RSP29_RX_INFO_OK                   :1 ;
    uint32_t                           RSP29_MASK_RX_INFO_AGG             :1 ;
    uint32_t                           RSP29_MASK_OPERATION               :1 ;
    uint32_t                           RSP29_MASK_GROUP_ADDRESS           :1 ;
    uint32_t                           RSP29_MASK_RX_PV                   :1 ;
    uint32_t                           RSP29_MASK_RX_PV0_SUBTYPE          :4 ;
    uint32_t                           RSP29_MASK_RX_PV0_TYPE             :2 ;
    uint32_t                           RSP29_MASK_RX_NDP_PSPOLL           :1 ;
    uint32_t                           RSP29_MASK_RX_INFO_NDP             :1 ;
    uint32_t                           RSP29_MASK_RX_INFO_OK              :1 ;
    uint32_t                           RSP29_CASE                         :5 ;
    uint32_t                           RSP29_VALID                        :1 ;
}   MAC_RSP29;

typedef union {
    uint32_t                           w;
    MAC_RSP29                          b;
}   MAC_RSP29_U;


// 0x40080140 register ------------------------------------
typedef struct {
    uint32_t                           RSP30_RX_INFO_AGG                  :1 ;
    uint32_t                           RSP30_OPERATION                    :1 ;
    uint32_t                           RSP30_GROUP_ADDRESS                :1 ;
    uint32_t                           RSP30_RX_PV                        :1 ;
    uint32_t                           RSP30_RX_PV0_SUBTYPE               :4 ;
    uint32_t                           RSP30_RX_PV0_TYPE                  :2 ;
    uint32_t                           RSP30_RX_NDP_PSPOLL                :1 ;
    uint32_t                           RSP30_RX_INFO_NDP                  :1 ;
    uint32_t                           RSP30_RX_INFO_OK                   :1 ;
    uint32_t                           RSP30_MASK_RX_INFO_AGG             :1 ;
    uint32_t                           RSP30_MASK_OPERATION               :1 ;
    uint32_t                           RSP30_MASK_GROUP_ADDRESS           :1 ;
    uint32_t                           RSP30_MASK_RX_PV                   :1 ;
    uint32_t                           RSP30_MASK_RX_PV0_SUBTYPE          :4 ;
    uint32_t                           RSP30_MASK_RX_PV0_TYPE             :2 ;
    uint32_t                           RSP30_MASK_RX_NDP_PSPOLL           :1 ;
    uint32_t                           RSP30_MASK_RX_INFO_NDP             :1 ;
    uint32_t                           RSP30_MASK_RX_INFO_OK              :1 ;
    uint32_t                           RSP30_CASE                         :5 ;
    uint32_t                           RSP30_VALID                        :1 ;
}   MAC_RSP30;

typedef union {
    uint32_t                           w;
    MAC_RSP30                          b;
}   MAC_RSP30_U;


// 0x40080144 register ------------------------------------
typedef struct {
    uint32_t                           RSP31_RX_INFO_AGG                  :1 ;
    uint32_t                           RSP31_OPERATION                    :1 ;
    uint32_t                           RSP31_GROUP_ADDRESS                :1 ;
    uint32_t                           RSP31_RX_PV                        :1 ;
    uint32_t                           RSP31_RX_PV0_SUBTYPE               :4 ;
    uint32_t                           RSP31_RX_PV0_TYPE                  :2 ;
    uint32_t                           RSP31_RX_NDP_PSPOLL                :1 ;
    uint32_t                           RSP31_RX_INFO_NDP                  :1 ;
    uint32_t                           RSP31_RX_INFO_OK                   :1 ;
    uint32_t                           RSP31_MASK_RX_INFO_AGG             :1 ;
    uint32_t                           RSP31_MASK_OPERATION               :1 ;
    uint32_t                           RSP31_MASK_GROUP_ADDRESS           :1 ;
    uint32_t                           RSP31_MASK_RX_PV                   :1 ;
    uint32_t                           RSP31_MASK_RX_PV0_SUBTYPE          :4 ;
    uint32_t                           RSP31_MASK_RX_PV0_TYPE             :2 ;
    uint32_t                           RSP31_MASK_RX_NDP_PSPOLL           :1 ;
    uint32_t                           RSP31_MASK_RX_INFO_NDP             :1 ;
    uint32_t                           RSP31_MASK_RX_INFO_OK              :1 ;
    uint32_t                           RSP31_CASE                         :5 ;
    uint32_t                           RSP31_VALID                        :1 ;
}   MAC_RSP31;

typedef union {
    uint32_t                           w;
    MAC_RSP31                          b;
}   MAC_RSP31_U;


// 0x40080148 register ------------------------------------
typedef struct {
    uint32_t                           CASE0_CF_TYPE_LONG                 :5 ;
    uint32_t                           reserved0                          :2 ;
    uint32_t                           CASE0_IRQ_LONG                     :1 ;
    uint32_t                           CASE0_CF_TYPE_NORMAL               :5 ;
    uint32_t                           reserved1                          :2 ;
    uint32_t                           CASE0_IRQ_NORMAL                   :1 ;
    uint32_t                           CASE0_CF_TYPE_NDP                  :5 ;
    uint32_t                           reserved2                          :2 ;
    uint32_t                           CASE0_IRQ_NDP                      :1 ;
    uint32_t                           CASE0_CF_TYPE_NO                   :5 ;
    uint32_t                           reserved3                          :2 ;
    uint32_t                           CASE0_IRQ_NO                       :1 ;
}   MAC_RSP_CASE0;

typedef union {
    uint32_t                           w;
    MAC_RSP_CASE0                      b;
}   MAC_RSP_CASE0_U;


// 0x4008014C register ------------------------------------
typedef struct {
    uint32_t                           CASE1_CF_TYPE_LONG                 :5 ;
    uint32_t                           reserved0                          :2 ;
    uint32_t                           CASE1_IRQ_LONG                     :1 ;
    uint32_t                           CASE1_CF_TYPE_NORMAL               :5 ;
    uint32_t                           reserved1                          :2 ;
    uint32_t                           CASE1_IRQ_NORMAL                   :1 ;
    uint32_t                           CASE1_CF_TYPE_NDP                  :5 ;
    uint32_t                           reserved2                          :2 ;
    uint32_t                           CASE1_IRQ_NDP                      :1 ;
    uint32_t                           CASE1_CF_TYPE_NO                   :5 ;
    uint32_t                           reserved3                          :2 ;
    uint32_t                           CASE1_IRQ_NO                       :1 ;
}   MAC_RSP_CASE1;

typedef union {
    uint32_t                           w;
    MAC_RSP_CASE1                      b;
}   MAC_RSP_CASE1_U;


// 0x40080150 register ------------------------------------
typedef struct {
    uint32_t                           CASE2_CF_TYPE_LONG                 :5 ;
    uint32_t                           reserved0                          :2 ;
    uint32_t                           CASE2_IRQ_LONG                     :1 ;
    uint32_t                           CASE2_CF_TYPE_NORMAL               :5 ;
    uint32_t                           reserved1                          :2 ;
    uint32_t                           CASE2_IRQ_NORMAL                   :1 ;
    uint32_t                           CASE2_CF_TYPE_NDP                  :5 ;
    uint32_t                           reserved2                          :2 ;
    uint32_t                           CASE2_IRQ_NDP                      :1 ;
    uint32_t                           CASE2_CF_TYPE_NO                   :5 ;
    uint32_t                           reserved3                          :2 ;
    uint32_t                           CASE2_IRQ_NO                       :1 ;
}   MAC_RSP_CASE2;

typedef union {
    uint32_t                           w;
    MAC_RSP_CASE2                      b;
}   MAC_RSP_CASE2_U;


// 0x40080154 register ------------------------------------
typedef struct {
    uint32_t                           CASE3_CF_TYPE_LONG                 :5 ;
    uint32_t                           reserved0                          :2 ;
    uint32_t                           CASE3_IRQ_LONG                     :1 ;
    uint32_t                           CASE3_CF_TYPE_NORMAL               :5 ;
    uint32_t                           reserved1                          :2 ;
    uint32_t                           CASE3_IRQ_NORMAL                   :1 ;
    uint32_t                           CASE3_CF_TYPE_NDP                  :5 ;
    uint32_t                           reserved2                          :2 ;
    uint32_t                           CASE3_IRQ_NDP                      :1 ;
    uint32_t                           CASE3_CF_TYPE_NO                   :5 ;
    uint32_t                           reserved3                          :2 ;
    uint32_t                           CASE3_IRQ_NO                       :1 ;
}   MAC_RSP_CASE3;

typedef union {
    uint32_t                           w;
    MAC_RSP_CASE3                      b;
}   MAC_RSP_CASE3_U;


// 0x40080158 register ------------------------------------
typedef struct {
    uint32_t                           CASE4_CF_TYPE_LONG                 :5 ;
    uint32_t                           reserved0                          :2 ;
    uint32_t                           CASE4_IRQ_LONG                     :1 ;
    uint32_t                           CASE4_CF_TYPE_NORMAL               :5 ;
    uint32_t                           reserved1                          :2 ;
    uint32_t                           CASE4_IRQ_NORMAL                   :1 ;
    uint32_t                           CASE4_CF_TYPE_NDP                  :5 ;
    uint32_t                           reserved2                          :2 ;
    uint32_t                           CASE4_IRQ_NDP                      :1 ;
    uint32_t                           CASE4_CF_TYPE_NO                   :5 ;
    uint32_t                           reserved3                          :2 ;
    uint32_t                           CASE4_IRQ_NO                       :1 ;
}   MAC_RSP_CASE4;

typedef union {
    uint32_t                           w;
    MAC_RSP_CASE4                      b;
}   MAC_RSP_CASE4_U;


// 0x4008015C register ------------------------------------
typedef struct {
    uint32_t                           CASE5_CF_TYPE_LONG                 :5 ;
    uint32_t                           reserved0                          :2 ;
    uint32_t                           CASE5_IRQ_LONG                     :1 ;
    uint32_t                           CASE5_CF_TYPE_NORMAL               :5 ;
    uint32_t                           reserved1                          :2 ;
    uint32_t                           CASE5_IRQ_NORMAL                   :1 ;
    uint32_t                           CASE5_CF_TYPE_NDP                  :5 ;
    uint32_t                           reserved2                          :2 ;
    uint32_t                           CASE5_IRQ_NDP                      :1 ;
    uint32_t                           CASE5_CF_TYPE_NO                   :5 ;
    uint32_t                           reserved3                          :2 ;
    uint32_t                           CASE5_IRQ_NO                       :1 ;
}   MAC_RSP_CASE5;

typedef union {
    uint32_t                           w;
    MAC_RSP_CASE5                      b;
}   MAC_RSP_CASE5_U;


// 0x40080160 register ------------------------------------
typedef struct {
    uint32_t                           CASE6_CF_TYPE_LONG                 :5 ;
    uint32_t                           reserved0                          :2 ;
    uint32_t                           CASE6_IRQ_LONG                     :1 ;
    uint32_t                           CASE6_CF_TYPE_NORMAL               :5 ;
    uint32_t                           reserved1                          :2 ;
    uint32_t                           CASE6_IRQ_NORMAL                   :1 ;
    uint32_t                           CASE6_CF_TYPE_NDP                  :5 ;
    uint32_t                           reserved2                          :2 ;
    uint32_t                           CASE6_IRQ_NDP                      :1 ;
    uint32_t                           CASE6_CF_TYPE_NO                   :5 ;
    uint32_t                           reserved3                          :2 ;
    uint32_t                           CASE6_IRQ_NO                       :1 ;
}   MAC_RSP_CASE6;

typedef union {
    uint32_t                           w;
    MAC_RSP_CASE6                      b;
}   MAC_RSP_CASE6_U;


// 0x40080164 register ------------------------------------
typedef struct {
    uint32_t                           CASE7_CF_TYPE_LONG                 :5 ;
    uint32_t                           reserved0                          :2 ;
    uint32_t                           CASE7_IRQ_LONG                     :1 ;
    uint32_t                           CASE7_CF_TYPE_NORMAL               :5 ;
    uint32_t                           reserved1                          :2 ;
    uint32_t                           CASE7_IRQ_NORMAL                   :1 ;
    uint32_t                           CASE7_CF_TYPE_NDP                  :5 ;
    uint32_t                           reserved2                          :2 ;
    uint32_t                           CASE7_IRQ_NDP                      :1 ;
    uint32_t                           CASE7_CF_TYPE_NO                   :5 ;
    uint32_t                           reserved3                          :2 ;
    uint32_t                           CASE7_IRQ_NO                       :1 ;
}   MAC_RSP_CASE7;

typedef union {
    uint32_t                           w;
    MAC_RSP_CASE7                      b;
}   MAC_RSP_CASE7_U;


// 0x40080168 register ------------------------------------
typedef struct {
    uint32_t                           RSP_CASE8                          :32;
}   MAC_RSP_CASE8;

typedef union {
    uint32_t                           w;
    MAC_RSP_CASE8                      b;
}   MAC_RSP_CASE8_U;


// 0x4008016C register ------------------------------------
typedef struct {
    uint32_t                           RSP_CASE9                          :32;
}   MAC_RSP_CASE9;

typedef union {
    uint32_t                           w;
    MAC_RSP_CASE9                      b;
}   MAC_RSP_CASE9_U;


// 0x40080170 register ------------------------------------
typedef struct {
    uint32_t                           RSP_CASE10                         :32;
}   MAC_RSP_CASE10;

typedef union {
    uint32_t                           w;
    MAC_RSP_CASE10                     b;
}   MAC_RSP_CASE10_U;


// 0x40080174 register ------------------------------------
typedef struct {
    uint32_t                           RSP_CASE11                         :32;
}   MAC_RSP_CASE11;

typedef union {
    uint32_t                           w;
    MAC_RSP_CASE11                     b;
}   MAC_RSP_CASE11_U;


// 0x40080178 register ------------------------------------
typedef struct {
    uint32_t                           AHB_WR_WAIT_INTERVAL               :8 ;
    uint32_t                           AHB_WR_WAIT_CLOCK                  :16;
    uint32_t                           AHB_WAIT_MODE_WR_ON                :1 ;
    uint32_t                           reserved0                          :1 ;
    uint32_t                           RXINFO_4SET_ENABLE                 :1 ;
    uint32_t                           RXINFO_WRITE_SKIP                  :1 ;
    uint32_t                           RXINFO_READ_SKIP                   :1 ;
    uint32_t                           reserved1                          :3 ;
}   MAC_WAIT_MODE_WR;

typedef union {
    uint32_t                           w;
    MAC_WAIT_MODE_WR                   b;
}   MAC_WAIT_MODE_WR_U;


// 0x4008017C register ------------------------------------
typedef struct {
    uint32_t                           AHB_RD_WAIT_INTERVAL               :8 ;
    uint32_t                           AHB_RD_WAIT_CLOCK                  :16;
    uint32_t                           AHB_WAIT_MODE_RD_ON                :1 ;
    uint32_t                           reserved0                          :7 ;
}   MAC_WAIT_MODE_RD;

typedef union {
    uint32_t                           w;
    MAC_WAIT_MODE_RD                   b;
}   MAC_WAIT_MODE_RD_U;


// 0x40080180 register ------------------------------------
typedef struct {
    uint32_t                           CW_COUNT                           :10;
    uint32_t                           AIFSN                              :4 ;
    uint32_t                           BANDWIDTH                          :2 ;
    uint32_t                           BUFFER_WORD_OFFSET                 :16;
}   MAC_TX_COMMAND_0;

typedef union {
    uint32_t                           w;
    MAC_TX_COMMAND_0                   b;
}   MAC_TX_COMMAND_0_U;


// 0x40080184 register ------------------------------------
typedef struct {
    uint32_t                           TX_COMMAND_1                       :32;
}   MAC_TX_COMMAND_1;

typedef union {
    uint32_t                           w;
    MAC_TX_COMMAND_1                   b;
}   MAC_TX_COMMAND_1_U;


// 0x40080188 register ------------------------------------
typedef struct {
    uint32_t                           TX_COMMAND_2                       :32;
}   MAC_TX_COMMAND_2;

typedef union {
    uint32_t                           w;
    MAC_TX_COMMAND_2                   b;
}   MAC_TX_COMMAND_2_U;


// 0x4008018C register ------------------------------------
typedef struct {
    uint32_t                           TX_COMMAND_3                       :32;
}   MAC_TX_COMMAND_3;

typedef union {
    uint32_t                           w;
    MAC_TX_COMMAND_3                   b;
}   MAC_TX_COMMAND_3_U;


// 0x40080190 register ------------------------------------
typedef struct {
    uint32_t                           TX_COMMAND_4                       :32;
}   MAC_TX_COMMAND_4;

typedef union {
    uint32_t                           w;
    MAC_TX_COMMAND_4                   b;
}   MAC_TX_COMMAND_4_U;


// 0x40080194 register ------------------------------------
typedef struct {
    uint32_t                           TX_COMMAND_5                       :32;
}   MAC_TX_COMMAND_5;

typedef union {
    uint32_t                           w;
    MAC_TX_COMMAND_5                   b;
}   MAC_TX_COMMAND_5_U;


// 0x40080198 register ------------------------------------
typedef struct {
    uint32_t                           TX_COMMAND_6                       :32;
}   MAC_TX_COMMAND_6;

typedef union {
    uint32_t                           w;
    MAC_TX_COMMAND_6                   b;
}   MAC_TX_COMMAND_6_U;


// 0x4008019C register ------------------------------------
typedef struct {
    uint32_t                           TX_COMMAND_7                       :32;
}   MAC_TX_COMMAND_7;

typedef union {
    uint32_t                           w;
    MAC_TX_COMMAND_7                   b;
}   MAC_TX_COMMAND_7_U;


// 0x400801A0 register ------------------------------------
typedef struct {
    uint32_t                           TX_COMMAND_8                       :32;
}   MAC_TX_COMMAND_8;

typedef union {
    uint32_t                           w;
    MAC_TX_COMMAND_8                   b;
}   MAC_TX_COMMAND_8_U;


// 0x400801A4 register ------------------------------------
typedef struct {
    uint32_t                           TX_COMMAND_9                       :32;
}   MAC_TX_COMMAND_9;

typedef union {
    uint32_t                           w;
    MAC_TX_COMMAND_9                   b;
}   MAC_TX_COMMAND_9_U;


// 0x400801A8 register ------------------------------------
typedef struct {
    uint32_t                           TX_COMMAND_10                      :32;
}   MAC_TX_COMMAND_10;

typedef union {
    uint32_t                           w;
    MAC_TX_COMMAND_10                  b;
}   MAC_TX_COMMAND_10_U;


// 0x400801AC register ------------------------------------
typedef struct {
    uint32_t                           TX_TIME                            :16;
    uint32_t                           BUFFER_WORD_OFFSET                 :16;
}   MAC_TXOP_COMMAND_0;

typedef union {
    uint32_t                           w;
    MAC_TXOP_COMMAND_0                 b;
}   MAC_TXOP_COMMAND_0_U;


// 0x400801B0 register ------------------------------------
typedef struct {
    uint32_t                           TXOP_COMMAND_1                     :32;
}   MAC_TXOP_COMMAND_1;

typedef union {
    uint32_t                           w;
    MAC_TXOP_COMMAND_1                 b;
}   MAC_TXOP_COMMAND_1_U;


// 0x400801B4 register ------------------------------------
typedef struct {
    uint32_t                           TXOP_COMMAND_2                     :32;
}   MAC_TXOP_COMMAND_2;

typedef union {
    uint32_t                           w;
    MAC_TXOP_COMMAND_2                 b;
}   MAC_TXOP_COMMAND_2_U;


// 0x400801B8 register ------------------------------------
typedef struct {
    uint32_t                           TXOP_COMMAND_3                     :32;
}   MAC_TXOP_COMMAND_3;

typedef union {
    uint32_t                           w;
    MAC_TXOP_COMMAND_3                 b;
}   MAC_TXOP_COMMAND_3_U;


// 0x400801BC register ------------------------------------
typedef struct {
    uint32_t                           TXOP_COMMAND_4                     :32;
}   MAC_TXOP_COMMAND_4;

typedef union {
    uint32_t                           w;
    MAC_TXOP_COMMAND_4                 b;
}   MAC_TXOP_COMMAND_4_U;


// 0x400801C0 register ------------------------------------
typedef struct {
    uint32_t                           TXOP_COMMAND_5                     :32;
}   MAC_TXOP_COMMAND_5;

typedef union {
    uint32_t                           w;
    MAC_TXOP_COMMAND_5                 b;
}   MAC_TXOP_COMMAND_5_U;


// 0x400801C4 register ------------------------------------
typedef struct {
    uint32_t                           TXOP_COMMAND_6                     :32;
}   MAC_TXOP_COMMAND_6;

typedef union {
    uint32_t                           w;
    MAC_TXOP_COMMAND_6                 b;
}   MAC_TXOP_COMMAND_6_U;


// 0x400801C8 register ------------------------------------
typedef struct {
    uint32_t                           TXOP_COMMAND_7                     :32;
}   MAC_TXOP_COMMAND_7;

typedef union {
    uint32_t                           w;
    MAC_TXOP_COMMAND_7                 b;
}   MAC_TXOP_COMMAND_7_U;


// 0x400801CC register ------------------------------------
typedef struct {
    uint32_t                           TXOP_COMMAND_8                     :32;
}   MAC_TXOP_COMMAND_8;

typedef union {
    uint32_t                           w;
    MAC_TXOP_COMMAND_8                 b;
}   MAC_TXOP_COMMAND_8_U;


// 0x400801D0 register ------------------------------------
typedef struct {
    uint32_t                           TXOP_COMMAND_9                     :32;
}   MAC_TXOP_COMMAND_9;

typedef union {
    uint32_t                           w;
    MAC_TXOP_COMMAND_9                 b;
}   MAC_TXOP_COMMAND_9_U;


// 0x400801D4 register ------------------------------------
typedef struct {
    uint32_t                           TXOP_COMMAND_10                    :32;
}   MAC_TXOP_COMMAND_10;

typedef union {
    uint32_t                           w;
    MAC_TXOP_COMMAND_10                b;
}   MAC_TXOP_COMMAND_10_U;


// 0x400801D8 register ------------------------------------
typedef struct {
    uint32_t                           CW_COUNT_RAW                       :10;
    uint32_t                           AIFSN_RAW                          :4 ;
    uint32_t                           reserved0                          :2 ;
    uint32_t                           TX_TIME                            :16;
}   MAC_TX_RAW_EDCA_0;

typedef union {
    uint32_t                           w;
    MAC_TX_RAW_EDCA_0                  b;
}   MAC_TX_RAW_EDCA_0_U;


// 0x400801DC register ------------------------------------
typedef struct {
    uint32_t                           TX_RAW_EDCA_1                      :32;
}   MAC_TX_RAW_EDCA_1;

typedef union {
    uint32_t                           w;
    MAC_TX_RAW_EDCA_1                  b;
}   MAC_TX_RAW_EDCA_1_U;


// 0x400801E0 register ------------------------------------
typedef struct {
    uint32_t                           TX_RAW_EDCA_2                      :32;
}   MAC_TX_RAW_EDCA_2;

typedef union {
    uint32_t                           w;
    MAC_TX_RAW_EDCA_2                  b;
}   MAC_TX_RAW_EDCA_2_U;


// 0x400801E4 register ------------------------------------
typedef struct {
    uint32_t                           TX_RAW_EDCA_3                      :32;
}   MAC_TX_RAW_EDCA_3;

typedef union {
    uint32_t                           w;
    MAC_TX_RAW_EDCA_3                  b;
}   MAC_TX_RAW_EDCA_3_U;


// 0x400801E8 register ------------------------------------
typedef struct {
    uint32_t                           TX_RAW_EDCA_4                      :32;
}   MAC_TX_RAW_EDCA_4;

typedef union {
    uint32_t                           w;
    MAC_TX_RAW_EDCA_4                  b;
}   MAC_TX_RAW_EDCA_4_U;


// 0x400801EC register ------------------------------------
typedef struct {
    uint32_t                           TX_RAW_EDCA_5                      :32;
}   MAC_TX_RAW_EDCA_5;

typedef union {
    uint32_t                           w;
    MAC_TX_RAW_EDCA_5                  b;
}   MAC_TX_RAW_EDCA_5_U;


// 0x400801F0 register ------------------------------------
typedef struct {
    uint32_t                           TX_BASE_ADDRESS                    :32;
}   MAC_TX_BASE_ADDRESS;

typedef union {
    uint32_t                           w;
    MAC_TX_BASE_ADDRESS                b;
}   MAC_TX_BASE_ADDRESS_U;


// 0x400801F4 register ------------------------------------
typedef struct {
    uint32_t                           TSW_DATA_IN_WAIT                   :32;
}   MAC_TSW_DATA_IN_WAIT;

typedef union {
    uint32_t                           w;
    MAC_TSW_DATA_IN_WAIT               b;
}   MAC_TSW_DATA_IN_WAIT_U;


// 0x400801F8 register ------------------------------------
typedef struct {
    uint32_t                           SUPPRESS_COMMAND                   :4 ;
    uint32_t                           reserved0                          :3 ;
    uint32_t                           SUPPRESS_CMD_VALID                 :1 ;
    uint32_t                           MYRAW_COMMAND                      :4 ;
    uint32_t                           reserved1                          :3 ;
    uint32_t                           MYRAW_CMD_VALID                    :1 ;
    uint32_t                           reserved2                          :13;
    uint32_t                           HOLD_AFTER_SUPPRESS                :1 ;
    uint32_t                           XROSS_BOUNDARY                     :1 ;
    uint32_t                           REFERENC_TSF                       :1 ;
}   MAC_TX_SUPPRESS_COMMAND;

typedef union {
    uint32_t                           w;
    MAC_TX_SUPPRESS_COMMAND            b;
}   MAC_TX_SUPPRESS_COMMAND_U;


// 0x400801FC register ------------------------------------
typedef struct {
    uint32_t                           TX_SUPPRESS_START_TSF              :32;
}   MAC_TX_SUPPRESS_START_TSF;

typedef union {
    uint32_t                           w;
    MAC_TX_SUPPRESS_START_TSF          b;
}   MAC_TX_SUPPRESS_START_TSF_U;


// 0x40080200 register ------------------------------------
typedef struct {
    uint32_t                           TX_SUPPRESS_END_TSF                :32;
}   MAC_TX_SUPPRESS_END_TSF;

typedef union {
    uint32_t                           w;
    MAC_TX_SUPPRESS_END_TSF            b;
}   MAC_TX_SUPPRESS_END_TSF_U;


// 0x40080204 register ------------------------------------
typedef struct {
    uint32_t                           TX_SUPPRESS_DURATION               :32;
}   MAC_TX_SUPPRESS_DURATION;

typedef union {
    uint32_t                           w;
    MAC_TX_SUPPRESS_DURATION           b;
}   MAC_TX_SUPPRESS_DURATION_U;


// 0x40080208 register ------------------------------------
typedef struct {
    uint32_t                           TX_MYRAW_START_TSF                 :32;
}   MAC_TX_MYRAW_START_TSF;

typedef union {
    uint32_t                           w;
    MAC_TX_MYRAW_START_TSF             b;
}   MAC_TX_MYRAW_START_TSF_U;


// 0x4008020C register ------------------------------------
typedef struct {
    uint32_t                           TX_MYRAW_END_TSF                   :32;
}   MAC_TX_MYRAW_END_TSF;

typedef union {
    uint32_t                           w;
    MAC_TX_MYRAW_END_TSF               b;
}   MAC_TX_MYRAW_END_TSF_U;


// 0x40080210 register ------------------------------------
typedef struct {
    uint32_t                           TX_MYRAW_DURATION                  :32;
}   MAC_TX_MYRAW_DURATION;

typedef union {
    uint32_t                           w;
    MAC_TX_MYRAW_DURATION              b;
}   MAC_TX_MYRAW_DURATION_U;


// 0x40080214 register ------------------------------------
typedef struct {
    uint32_t                           TX_SUPPRESS_SETTING                :32;
}   MAC_TX_SUPPRESS_SETTING;

typedef union {
    uint32_t                           w;
    MAC_TX_SUPPRESS_SETTING            b;
}   MAC_TX_SUPPRESS_SETTING_U;


// 0x40080218 register ------------------------------------
typedef struct {
    uint32_t                           TX_SUPPRESS_PERIOD                 :1 ;
    uint32_t                           TX_MYRAW_PERIOD                    :1 ;
    uint32_t                           XROSS_BOUNDARY                     :1 ;
    uint32_t                           REFERENCE_TSF                      :1 ;
    uint32_t                           reserved0                          :4 ;
    uint32_t                           SUPPRESS_CMD                       :4 ;
    uint32_t                           MYRAW_CMD                          :4 ;
    uint32_t                           reserved1                          :16;
}   MAC_TX_SUPPRESS_STATUS;

typedef union {
    uint32_t                           w;
    MAC_TX_SUPPRESS_STATUS             b;
}   MAC_TX_SUPPRESS_STATUS_U;


// 0x4008021C register ------------------------------------
typedef struct {
    uint32_t                           CCMP_DATA_IN_WAIT                  :8 ;
    uint32_t                           TIKIP_DATA_IN_WAIT                 :8 ;
    uint32_t                           reserved0                          :15;
    uint32_t                           SECURITY_OFFLINE                   :1 ;
}   MAC_TX_DATA_IN_WAIT;

typedef union {
    uint32_t                           w;
    MAC_TX_DATA_IN_WAIT                b;
}   MAC_TX_DATA_IN_WAIT_U;


// 0x40080220 register ------------------------------------
typedef struct {
    uint32_t                           PHY_TXFIFO_MAX_DEPTH               :32;
}   MAC_PHY_TXFIFO_MAX_DEPTH;

typedef union {
    uint32_t                           w;
    MAC_PHY_TXFIFO_MAX_DEPTH           b;
}   MAC_PHY_TXFIFO_MAX_DEPTH_U;


// 0x40080224 register ------------------------------------
typedef struct {
    uint32_t                           TXNAV_VALUE                        :32;
}   MAC_TXNAV_VALUE;

typedef union {
    uint32_t                           w;
    MAC_TXNAV_VALUE                    b;
}   MAC_TXNAV_VALUE_U;


// 0x40080228 register ------------------------------------
typedef struct {
    uint32_t                           RXNAV_VALUE                        :32;
}   MAC_RXNAV_VALUE;

typedef union {
    uint32_t                           w;
    MAC_RXNAV_VALUE                    b;
}   MAC_RXNAV_VALUE_U;


// 0x4008022C register ------------------------------------
typedef struct {
    uint32_t                           RID_VALUE                          :32;
}   MAC_RID_VALUE;

typedef union {
    uint32_t                           w;
    MAC_RID_VALUE                      b;
}   MAC_RID_VALUE_U;


// 0x40080230 register ------------------------------------
typedef struct {
    uint32_t                           NAV_RESET                          :1 ;
    uint32_t                           reserved0                          :31;
}   MAC_NAV_RESET;

typedef union {
    uint32_t                           w;
    MAC_NAV_RESET                      b;
}   MAC_NAV_RESET_U;


// 0x40080234 register ------------------------------------
typedef struct {
    uint32_t                           RID_RESET                          :1 ;
    uint32_t                           reserved0                          :31;
}   MAC_RID_RESET;

typedef union {
    uint32_t                           w;
    MAC_RID_RESET                      b;
}   MAC_RID_RESET_U;


// 0x40080238 register ------------------------------------
typedef struct {
    uint32_t                           NAV_RID_CONTROL_MODE               :32;
}   MAC_NAV_RID_CONTROL_MODE;

typedef union {
    uint32_t                           w;
    MAC_NAV_RID_CONTROL_MODE           b;
}   MAC_NAV_RID_CONTROL_MODE_U;


// 0x4008023C register ------------------------------------
typedef struct {
    uint32_t                           TXNAV_HW_SETTING_VALUE             :32;
}   MAC_TXNAV_HW_SETTING_VALUE;

typedef union {
    uint32_t                           w;
    MAC_TXNAV_HW_SETTING_VALUE         b;
}   MAC_TXNAV_HW_SETTING_VALUE_U;


// 0x40080240 register ------------------------------------
typedef struct {
    uint32_t                           PREAMBLE_TYPE                      :1 ;
    uint32_t                           reserved0                          :31;
}   MAC_PREAMBLE_TYPE;

typedef union {
    uint32_t                           w;
    MAC_PREAMBLE_TYPE                  b;
}   MAC_PREAMBLE_TYPE_U;


// 0x40080244 register ------------------------------------
typedef struct {
    uint32_t                           FIX_MOREDATA                       :1 ;
    uint32_t                           ACK_BA_POWER_MANAGEMENT            :1 ;
    uint32_t                           ALLOW_DUP_1M_RTS_IN_4M             :1 ;
    uint32_t                           reserved0                          :29;
}   MAC_SET_CONTROL_FRAME;

typedef union {
    uint32_t                           w;
    MAC_SET_CONTROL_FRAME              b;
}   MAC_SET_CONTROL_FRAME_U;


// 0x40080248 register ------------------------------------
typedef struct {
    uint32_t                           REG_SW_IDLE_INDICATION             :1 ;
    uint32_t                           reserved0                          :3 ;
    uint32_t                           REG_SW_MOREDATA                    :1 ;
    uint32_t                           reserved1                          :3 ;
    uint32_t                           reserved2                          :8 ;
    uint32_t                           REG_SW_DURATION                    :14;
    uint32_t                           reserved3                          :2 ;
}   MAC_SET_PS_POLL_ACK_SW;

typedef union {
    uint32_t                           w;
    MAC_SET_PS_POLL_ACK_SW             b;
}   MAC_SET_PS_POLL_ACK_SW_U;


// 0x4008024C register ------------------------------------
typedef struct {
    uint32_t                           REG_DEFAULT_IDLE_INDICATION        :1 ;
    uint32_t                           reserved0                          :3 ;
    uint32_t                           REG_DEFAULT_MOREDATA               :1 ;
    uint32_t                           reserved1                          :3 ;
    uint32_t                           reserved2                          :8 ;
    uint32_t                           REG_DEFAULT_DURATION               :14;
    uint32_t                           reserved3                          :2 ;
}   MAC_SET_PS_POLL_ACK_DEFAULT;

typedef union {
    uint32_t                           w;
    MAC_SET_PS_POLL_ACK_DEFAULT        b;
}   MAC_SET_PS_POLL_ACK_DEFAULT_U;


// 0x40080250 register ------------------------------------
typedef struct {
    uint32_t                           SET_RTSRID                         :2 ;
    uint32_t                           reserved0                          :30;
}   MAC_SET_RTSRID;

typedef union {
    uint32_t                           w;
    MAC_SET_RTSRID                     b;
}   MAC_SET_RTSRID_U;


// 0x40080254 register ------------------------------------
typedef struct {
    uint32_t                           REG_DUP_1M_SUPPORT                 :1 ;
    uint32_t                           reserved0                          :3 ;
    uint32_t                           REG_1M_RES_PREAMBLE_SUPPORT        :1 ;
    uint32_t                           reserved1                          :3 ;
    uint32_t                           TIMESTAMP_COMPENSATE_ENABLE        :1 ;
    uint32_t                           reserved2                          :23;
}   MAC_CF_CHANNEL_WIDTH_SELECTION;

typedef union {
    uint32_t                           w;
    MAC_CF_CHANNEL_WIDTH_SELECTION     b;
}   MAC_CF_CHANNEL_WIDTH_SELECTION_U;


// 0x40080258 register ------------------------------------
typedef struct {
    uint32_t                           REG_BEACON_SEQUENCE                :8 ;
    uint32_t                           REG_NEXT_TWT_INFO_PRESENT          :1 ;
    uint32_t                           REG_FLOW_CONTROL                   :1 ;
    uint32_t                           REG_PSPOLL_RES_MOREDATA            :1 ;
    uint32_t                           reserved0                          :5 ;
    uint32_t                           SET_TSF_INFO_0                     :16;
}   MAC_SET_FLOW_CONTROL_INFO_0;

typedef union {
    uint32_t                           w;
    MAC_SET_FLOW_CONTROL_INFO_0        b;
}   MAC_SET_FLOW_CONTROL_INFO_0_U;


// 0x4008025C register ------------------------------------
typedef struct {
    uint32_t                           SET_FLOW_CONTROL_INFO_1            :32;
}   MAC_SET_FLOW_CONTROL_INFO_1;

typedef union {
    uint32_t                           w;
    MAC_SET_FLOW_CONTROL_INFO_1        b;
}   MAC_SET_FLOW_CONTROL_INFO_1_U;


// 0x40080260 register ------------------------------------
typedef struct {
    uint32_t                           REG_SW_ACK_IDLE_INDICATION         :1 ;
    uint32_t                           reserved0                          :3 ;
    uint32_t                           REG_SW_ACK_MOREDATA                :1 ;
    uint32_t                           reserved1                          :3 ;
    uint32_t                           REG_SW_ACK_RELAYED_FRAME           :1 ;
    uint32_t                           reserved2                          :3 ;
    uint32_t                           reserved3                          :4 ;
    uint32_t                           REG_SW_ACK_DURATION                :14;
    uint32_t                           reserved4                          :2 ;
}   MAC_SET_ACK_SW;

typedef union {
    uint32_t                           w;
    MAC_SET_ACK_SW                     b;
}   MAC_SET_ACK_SW_U;


// 0x40080264 register ------------------------------------
typedef struct {
    uint32_t                           REG_DEFAULT_ACK_IDLE_INDICATION    :1 ;
    uint32_t                           reserved0                          :3 ;
    uint32_t                           REG_DEFAULT_ACK_MOREDATA           :1 ;
    uint32_t                           reserved1                          :3 ;
    uint32_t                           REG_DEFAULT_ACK_RELAYED_FRAME      :1 ;
    uint32_t                           reserved2                          :3 ;
    uint32_t                           reserved3                          :4 ;
    uint32_t                           REG_DEFAULT_ACK_DURATION           :14;
    uint32_t                           reserved4                          :2 ;
}   MAC_SET_ACK_DEFAULT;

typedef union {
    uint32_t                           w;
    MAC_SET_ACK_DEFAULT                b;
}   MAC_SET_ACK_DEFAULT_U;


// 0x40080268 register ------------------------------------
typedef struct {
    uint32_t                           BASIC_RATE_BITMAP                  :32;
}   MAC_BASIC_RATE_BITMAP;

typedef union {
    uint32_t                           w;
    MAC_BASIC_RATE_BITMAP              b;
}   MAC_BASIC_RATE_BITMAP_U;


// 0x4008026C register ------------------------------------
typedef struct {
    uint32_t                           BASIC_RATE_BITMAP_2ND              :32;
}   MAC_BASIC_RATE_BITMAP_2ND;

typedef union {
    uint32_t                           w;
    MAC_BASIC_RATE_BITMAP_2ND          b;
}   MAC_BASIC_RATE_BITMAP_2ND_U;


// 0x40080270 register ------------------------------------
typedef struct {
    uint32_t                           MCS_DIFFERENCE                     :4 ;
    uint32_t                           MCS_DIFFERENCE_SWITCH              :8 ;
    uint32_t                           BA_MCS_DIFFERENCE                  :4 ;
    uint32_t                           reserved0                          :16;
}   MAC_MCS_DIFFERENCE;

typedef union {
    uint32_t                           w;
    MAC_MCS_DIFFERENCE                 b;
}   MAC_MCS_DIFFERENCE_U;


// 0x40080274 register ------------------------------------
typedef struct {
    uint32_t                           COMMAND                            :5 ;
    uint32_t                           RESPONSE_TYPE                      :1 ;
    uint32_t                           reserved0                          :26;
}   MAC_RESPONSE_TX_COMMAND;

typedef union {
    uint32_t                           w;
    MAC_RESPONSE_TX_COMMAND            b;
}   MAC_RESPONSE_TX_COMMAND_U;


// 0x40080278 register ------------------------------------
typedef struct {
    uint32_t                           RSP_TX_VECTOR                      :32;
}   MAC_RSP_TX_VECTOR;

typedef union {
    uint32_t                           w;
    MAC_RSP_TX_VECTOR                  b;
}   MAC_RSP_TX_VECTOR_U;


// 0x4008027C register ------------------------------------
typedef struct {
    uint32_t                           RSP_TX_SIG0                        :32;
}   MAC_RSP_TX_SIG0;

typedef union {
    uint32_t                           w;
    MAC_RSP_TX_SIG0                    b;
}   MAC_RSP_TX_SIG0_U;


// 0x40080280 register ------------------------------------
typedef struct {
    uint32_t                           RSP_TX_SIG1                        :32;
}   MAC_RSP_TX_SIG1;

typedef union {
    uint32_t                           w;
    MAC_RSP_TX_SIG1                    b;
}   MAC_RSP_TX_SIG1_U;


// 0x40080284 register ------------------------------------
typedef struct {
    uint32_t                           RSP_TXINFO_MPDU_LENGTH             :14;
    uint32_t                           RSP_TXINFO_SINGLE_AMPDU            :1 ;
    uint32_t                           RSP_TXINFO_CIPHER_TYPE             :3 ;
    uint32_t                           reserved0                          :4 ;
    uint32_t                           RSP_TXINFO_TIMESTAMP_UPDATE        :1 ;
    uint32_t                           RSP_TXINFO_TIMESTAMP_POSITION      :6 ;
    uint32_t                           reserved1                          :3 ;
}   MAC_RSP_TX_INFO0;

typedef union {
    uint32_t                           w;
    MAC_RSP_TX_INFO0                   b;
}   MAC_RSP_TX_INFO0_U;


// 0x40080288 register ------------------------------------
typedef struct {
    uint32_t                           RSP_TXINFO_PSDU_LENGTH             :20;
    uint32_t                           RSP_TXINFO_AGGREGATION             :1 ;
    uint32_t                           RSP_TXINFO_FORMAT                  :3 ;
    uint32_t                           reserved0                          :8 ;
}   MAC_RSP_TX_INFO1;

typedef union {
    uint32_t                           w;
    MAC_RSP_TX_INFO1                   b;
}   MAC_RSP_TX_INFO1_U;


// 0x4008028C register ------------------------------------
typedef struct {
    uint32_t                           RSP_TX_DATA0                       :32;
}   MAC_RSP_TX_DATA0;

typedef union {
    uint32_t                           w;
    MAC_RSP_TX_DATA0                   b;
}   MAC_RSP_TX_DATA0_U;


// 0x40080290 register ------------------------------------
typedef struct {
    uint32_t                           RSP_TX_DATA1                       :32;
}   MAC_RSP_TX_DATA1;

typedef union {
    uint32_t                           w;
    MAC_RSP_TX_DATA1                   b;
}   MAC_RSP_TX_DATA1_U;


// 0x40080294 register ------------------------------------
typedef struct {
    uint32_t                           RSP_TX_DATA2                       :32;
}   MAC_RSP_TX_DATA2;

typedef union {
    uint32_t                           w;
    MAC_RSP_TX_DATA2                   b;
}   MAC_RSP_TX_DATA2_U;


// 0x40080298 register ------------------------------------
typedef struct {
    uint32_t                           RSP_TX_DATA3                       :32;
}   MAC_RSP_TX_DATA3;

typedef union {
    uint32_t                           w;
    MAC_RSP_TX_DATA3                   b;
}   MAC_RSP_TX_DATA3_U;


// 0x4008029C register ------------------------------------
typedef struct {
    uint32_t                           RSP_TX_DATA4                       :32;
}   MAC_RSP_TX_DATA4;

typedef union {
    uint32_t                           w;
    MAC_RSP_TX_DATA4                   b;
}   MAC_RSP_TX_DATA4_U;


// 0x400802A0 register ------------------------------------
typedef struct {
    uint32_t                           RSP_TX_DATA5                       :32;
}   MAC_RSP_TX_DATA5;

typedef union {
    uint32_t                           w;
    MAC_RSP_TX_DATA5                   b;
}   MAC_RSP_TX_DATA5_U;


// 0x400802A4 register ------------------------------------
typedef struct {
    uint32_t                           RSP_TX_DATA6                       :32;
}   MAC_RSP_TX_DATA6;

typedef union {
    uint32_t                           w;
    MAC_RSP_TX_DATA6                   b;
}   MAC_RSP_TX_DATA6_U;


// 0x400802A8 register ------------------------------------
typedef struct {
    uint32_t                           RSP_TX_DATA7                       :32;
}   MAC_RSP_TX_DATA7;

typedef union {
    uint32_t                           w;
    MAC_RSP_TX_DATA7                   b;
}   MAC_RSP_TX_DATA7_U;


// 0x400802AC register ------------------------------------
typedef struct {
    uint32_t                           RSP_TX_DATA8                       :32;
}   MAC_RSP_TX_DATA8;

typedef union {
    uint32_t                           w;
    MAC_RSP_TX_DATA8                   b;
}   MAC_RSP_TX_DATA8_U;


// 0x400802B0 register ------------------------------------
typedef struct {
    uint32_t                           RSP_TX_DATA9                       :32;
}   MAC_RSP_TX_DATA9;

typedef union {
    uint32_t                           w;
    MAC_RSP_TX_DATA9                   b;
}   MAC_RSP_TX_DATA9_U;


// 0x400802B4 register ------------------------------------
typedef struct {
    uint32_t                           RSP_TX_DATA10                      :32;
}   MAC_RSP_TX_DATA10;

typedef union {
    uint32_t                           w;
    MAC_RSP_TX_DATA10                  b;
}   MAC_RSP_TX_DATA10_U;


// 0x400802B8 register ------------------------------------
typedef struct {
    uint32_t                           REG_SCRAMBLER_OR_CRC               :7 ;
    uint32_t                           REG_SCRAMBLER_EXIST                :1 ;
    uint32_t                           REG_TXPWR_LEVEL                    :8 ;
    uint32_t                           REG_SIG_DOPPLER                    :1 ;
    uint32_t                           REG_SIG_UPLINK_IND                 :1 ;
    uint32_t                           reserved0                          :14;
}   MAC_SET_CF_TXVECTOR_SIG;

typedef union {
    uint32_t                           w;
    MAC_SET_CF_TXVECTOR_SIG            b;
}   MAC_SET_CF_TXVECTOR_SIG_U;


// 0x400802BC register ------------------------------------
typedef struct {
    uint32_t                           MONITOR_INTERVAL                   :32;
}   MAC_MONITOR_INTERVAL;

typedef union {
    uint32_t                           w;
    MAC_MONITOR_INTERVAL               b;
}   MAC_MONITOR_INTERVAL_U;


// 0x400802C0 register ------------------------------------
typedef struct {
    uint32_t                           RANGE_VAR_0                        :16;
    uint32_t                           RANGE_VAR_1                        :16;
}   MAC_CCA_RANGE_VAR_SET0;

typedef union {
    uint32_t                           w;
    MAC_CCA_RANGE_VAR_SET0             b;
}   MAC_CCA_RANGE_VAR_SET0_U;


// 0x400802C4 register ------------------------------------
typedef struct {
    uint32_t                           CCA_RANGE_VAR_SET1                 :32;
}   MAC_CCA_RANGE_VAR_SET1;

typedef union {
    uint32_t                           w;
    MAC_CCA_RANGE_VAR_SET1             b;
}   MAC_CCA_RANGE_VAR_SET1_U;


// 0x400802C8 register ------------------------------------
typedef struct {
    uint32_t                           RX_BASE_ADDRESS                    :32;
}   MAC_RX_BASE_ADDRESS;

typedef union {
    uint32_t                           w;
    MAC_RX_BASE_ADDRESS                b;
}   MAC_RX_BASE_ADDRESS_U;


// 0x400802CC register ------------------------------------
typedef struct {
    uint32_t                           RX_DSC_NUM                         :32;
}   MAC_RX_DSC_NUM;

typedef union {
    uint32_t                           w;
    MAC_RX_DSC_NUM                     b;
}   MAC_RX_DSC_NUM_U;


// 0x400802D0 register ------------------------------------
typedef struct {
    uint32_t                           DATA_ADDRESS_OFFSET                :15;
    uint32_t                           BUFFER_LENGTH                      :11;
    uint32_t                           reserved0                          :6 ;
}   MAC_RX_REG_DL_DESC0;

typedef union {
    uint32_t                           w;
    MAC_RX_REG_DL_DESC0                b;
}   MAC_RX_REG_DL_DESC0_U;


// 0x400802D4 register ------------------------------------
typedef struct {
    uint32_t                           RX_REG_DL_DESC1                    :26;
    uint32_t                           reserved0                          :6 ;
}   MAC_RX_REG_DL_DESC1;

typedef union {
    uint32_t                           w;
    MAC_RX_REG_DL_DESC1                b;
}   MAC_RX_REG_DL_DESC1_U;


// 0x400802D8 register ------------------------------------
typedef struct {
    uint32_t                           RX_REG_DL_DESC2                    :26;
    uint32_t                           reserved0                          :6 ;
}   MAC_RX_REG_DL_DESC2;

typedef union {
    uint32_t                           w;
    MAC_RX_REG_DL_DESC2                b;
}   MAC_RX_REG_DL_DESC2_U;


// 0x400802DC register ------------------------------------
typedef struct {
    uint32_t                           RX_REG_DL_DESC3                    :26;
    uint32_t                           reserved0                          :6 ;
}   MAC_RX_REG_DL_DESC3;

typedef union {
    uint32_t                           w;
    MAC_RX_REG_DL_DESC3                b;
}   MAC_RX_REG_DL_DESC3_U;


// 0x400802E0 register ------------------------------------
typedef struct {
    uint32_t                           RX_REG_DL_DESC4                    :26;
    uint32_t                           reserved0                          :6 ;
}   MAC_RX_REG_DL_DESC4;

typedef union {
    uint32_t                           w;
    MAC_RX_REG_DL_DESC4                b;
}   MAC_RX_REG_DL_DESC4_U;


// 0x400802E4 register ------------------------------------
typedef struct {
    uint32_t                           RX_REG_DL_DESC5                    :26;
    uint32_t                           reserved0                          :6 ;
}   MAC_RX_REG_DL_DESC5;

typedef union {
    uint32_t                           w;
    MAC_RX_REG_DL_DESC5                b;
}   MAC_RX_REG_DL_DESC5_U;


// 0x400802E8 register ------------------------------------
typedef struct {
    uint32_t                           RX_REG_DL_DESC6                    :26;
    uint32_t                           reserved0                          :6 ;
}   MAC_RX_REG_DL_DESC6;

typedef union {
    uint32_t                           w;
    MAC_RX_REG_DL_DESC6                b;
}   MAC_RX_REG_DL_DESC6_U;


// 0x400802EC register ------------------------------------
typedef struct {
    uint32_t                           RX_REG_DL_DESC7                    :26;
    uint32_t                           reserved0                          :6 ;
}   MAC_RX_REG_DL_DESC7;

typedef union {
    uint32_t                           w;
    MAC_RX_REG_DL_DESC7                b;
}   MAC_RX_REG_DL_DESC7_U;


// 0x400802F0 register ------------------------------------
typedef struct {
    uint32_t                           RX_REG_DL_DESC8                    :26;
    uint32_t                           reserved0                          :6 ;
}   MAC_RX_REG_DL_DESC8;

typedef union {
    uint32_t                           w;
    MAC_RX_REG_DL_DESC8                b;
}   MAC_RX_REG_DL_DESC8_U;


// 0x400802F4 register ------------------------------------
typedef struct {
    uint32_t                           RX_REG_DL_DESC9                    :26;
    uint32_t                           reserved0                          :6 ;
}   MAC_RX_REG_DL_DESC9;

typedef union {
    uint32_t                           w;
    MAC_RX_REG_DL_DESC9                b;
}   MAC_RX_REG_DL_DESC9_U;


// 0x400802F8 register ------------------------------------
typedef struct {
    uint32_t                           RX_REG_DL_DESC10                   :26;
    uint32_t                           reserved0                          :6 ;
}   MAC_RX_REG_DL_DESC10;

typedef union {
    uint32_t                           w;
    MAC_RX_REG_DL_DESC10               b;
}   MAC_RX_REG_DL_DESC10_U;


// 0x400802FC register ------------------------------------
typedef struct {
    uint32_t                           RX_REG_DL_DESC11                   :26;
    uint32_t                           reserved0                          :6 ;
}   MAC_RX_REG_DL_DESC11;

typedef union {
    uint32_t                           w;
    MAC_RX_REG_DL_DESC11               b;
}   MAC_RX_REG_DL_DESC11_U;


// 0x40080300 register ------------------------------------
typedef struct {
    uint32_t                           RX_REG_DL_DESC12                   :26;
    uint32_t                           reserved0                          :6 ;
}   MAC_RX_REG_DL_DESC12;

typedef union {
    uint32_t                           w;
    MAC_RX_REG_DL_DESC12               b;
}   MAC_RX_REG_DL_DESC12_U;


// 0x40080304 register ------------------------------------
typedef struct {
    uint32_t                           RX_REG_DL_DESC13                   :26;
    uint32_t                           reserved0                          :6 ;
}   MAC_RX_REG_DL_DESC13;

typedef union {
    uint32_t                           w;
    MAC_RX_REG_DL_DESC13               b;
}   MAC_RX_REG_DL_DESC13_U;


// 0x40080308 register ------------------------------------
typedef struct {
    uint32_t                           RX_REG_DL_DESC14                   :26;
    uint32_t                           reserved0                          :6 ;
}   MAC_RX_REG_DL_DESC14;

typedef union {
    uint32_t                           w;
    MAC_RX_REG_DL_DESC14               b;
}   MAC_RX_REG_DL_DESC14_U;


// 0x4008030C register ------------------------------------
typedef struct {
    uint32_t                           RX_REG_DL_DESC15                   :26;
    uint32_t                           reserved0                          :6 ;
}   MAC_RX_REG_DL_DESC15;

typedef union {
    uint32_t                           w;
    MAC_RX_REG_DL_DESC15               b;
}   MAC_RX_REG_DL_DESC15_U;


// 0x40080310 register ------------------------------------
typedef struct {
    uint32_t                           RX_REG_DL_DESC16                   :26;
    uint32_t                           reserved0                          :6 ;
}   MAC_RX_REG_DL_DESC16;

typedef union {
    uint32_t                           w;
    MAC_RX_REG_DL_DESC16               b;
}   MAC_RX_REG_DL_DESC16_U;


// 0x40080314 register ------------------------------------
typedef struct {
    uint32_t                           RX_REG_DL_DESC17                   :26;
    uint32_t                           reserved0                          :6 ;
}   MAC_RX_REG_DL_DESC17;

typedef union {
    uint32_t                           w;
    MAC_RX_REG_DL_DESC17               b;
}   MAC_RX_REG_DL_DESC17_U;


// 0x40080318 register ------------------------------------
typedef struct {
    uint32_t                           RX_REG_DL_DESC18                   :26;
    uint32_t                           reserved0                          :6 ;
}   MAC_RX_REG_DL_DESC18;

typedef union {
    uint32_t                           w;
    MAC_RX_REG_DL_DESC18               b;
}   MAC_RX_REG_DL_DESC18_U;


// 0x4008031C register ------------------------------------
typedef struct {
    uint32_t                           RX_REG_DL_DESC19                   :26;
    uint32_t                           reserved0                          :6 ;
}   MAC_RX_REG_DL_DESC19;

typedef union {
    uint32_t                           w;
    MAC_RX_REG_DL_DESC19               b;
}   MAC_RX_REG_DL_DESC19_U;


// 0x40080320 register ------------------------------------
typedef struct {
    uint32_t                           RX_REG_DL_DESC20                   :26;
    uint32_t                           reserved0                          :6 ;
}   MAC_RX_REG_DL_DESC20;

typedef union {
    uint32_t                           w;
    MAC_RX_REG_DL_DESC20               b;
}   MAC_RX_REG_DL_DESC20_U;


// 0x40080324 register ------------------------------------
typedef struct {
    uint32_t                           RX_REG_DL_DESC21                   :26;
    uint32_t                           reserved0                          :6 ;
}   MAC_RX_REG_DL_DESC21;

typedef union {
    uint32_t                           w;
    MAC_RX_REG_DL_DESC21               b;
}   MAC_RX_REG_DL_DESC21_U;


// 0x40080328 register ------------------------------------
typedef struct {
    uint32_t                           RX_REG_DL_DESC22                   :26;
    uint32_t                           reserved0                          :6 ;
}   MAC_RX_REG_DL_DESC22;

typedef union {
    uint32_t                           w;
    MAC_RX_REG_DL_DESC22               b;
}   MAC_RX_REG_DL_DESC22_U;


// 0x4008032C register ------------------------------------
typedef struct {
    uint32_t                           RX_REG_DL_DESC23                   :26;
    uint32_t                           reserved0                          :6 ;
}   MAC_RX_REG_DL_DESC23;

typedef union {
    uint32_t                           w;
    MAC_RX_REG_DL_DESC23               b;
}   MAC_RX_REG_DL_DESC23_U;


// 0x40080330 register ------------------------------------
typedef struct {
    uint32_t                           RX_REG_DL_DESC24                   :26;
    uint32_t                           reserved0                          :6 ;
}   MAC_RX_REG_DL_DESC24;

typedef union {
    uint32_t                           w;
    MAC_RX_REG_DL_DESC24               b;
}   MAC_RX_REG_DL_DESC24_U;


// 0x40080334 register ------------------------------------
typedef struct {
    uint32_t                           RX_REG_DL_DESC25                   :26;
    uint32_t                           reserved0                          :6 ;
}   MAC_RX_REG_DL_DESC25;

typedef union {
    uint32_t                           w;
    MAC_RX_REG_DL_DESC25               b;
}   MAC_RX_REG_DL_DESC25_U;


// 0x40080338 register ------------------------------------
typedef struct {
    uint32_t                           RX_REG_DL_DESC26                   :26;
    uint32_t                           reserved0                          :6 ;
}   MAC_RX_REG_DL_DESC26;

typedef union {
    uint32_t                           w;
    MAC_RX_REG_DL_DESC26               b;
}   MAC_RX_REG_DL_DESC26_U;


// 0x4008033C register ------------------------------------
typedef struct {
    uint32_t                           RX_REG_DL_DESC27                   :26;
    uint32_t                           reserved0                          :6 ;
}   MAC_RX_REG_DL_DESC27;

typedef union {
    uint32_t                           w;
    MAC_RX_REG_DL_DESC27               b;
}   MAC_RX_REG_DL_DESC27_U;


// 0x40080340 register ------------------------------------
typedef struct {
    uint32_t                           RX_REG_DL_DESC28                   :26;
    uint32_t                           reserved0                          :6 ;
}   MAC_RX_REG_DL_DESC28;

typedef union {
    uint32_t                           w;
    MAC_RX_REG_DL_DESC28               b;
}   MAC_RX_REG_DL_DESC28_U;


// 0x40080344 register ------------------------------------
typedef struct {
    uint32_t                           RX_REG_DL_DESC29                   :26;
    uint32_t                           reserved0                          :6 ;
}   MAC_RX_REG_DL_DESC29;

typedef union {
    uint32_t                           w;
    MAC_RX_REG_DL_DESC29               b;
}   MAC_RX_REG_DL_DESC29_U;


// 0x40080348 register ------------------------------------
typedef struct {
    uint32_t                           RX_REG_DL_DESC30                   :26;
    uint32_t                           reserved0                          :6 ;
}   MAC_RX_REG_DL_DESC30;

typedef union {
    uint32_t                           w;
    MAC_RX_REG_DL_DESC30               b;
}   MAC_RX_REG_DL_DESC30_U;


// 0x4008034C register ------------------------------------
typedef struct {
    uint32_t                           RX_REG_DL_DESC31                   :26;
    uint32_t                           reserved0                          :6 ;
}   MAC_RX_REG_DL_DESC31;

typedef union {
    uint32_t                           w;
    MAC_RX_REG_DL_DESC31               b;
}   MAC_RX_REG_DL_DESC31_U;


// 0x40080350 register ------------------------------------
typedef struct {
    uint32_t                           SET_OWNER_ADDR                     :32;
}   MAC_SET_OWNER_ADDR;

typedef union {
    uint32_t                           w;
    MAC_SET_OWNER_ADDR                 b;
}   MAC_SET_OWNER_ADDR_U;


// 0x40080354 register ------------------------------------
typedef struct {
    uint32_t                           CCMP_DATA_IN_WAIT                  :8 ;
    uint32_t                           reserved0                          :15;
    uint32_t                           RX_WAIT_MODE                       :1 ;
    uint32_t                           reserved1                          :7 ;
    uint32_t                           SECURITY_OFFLINE                   :1 ;
}   MAC_RX_DATA_IN_WAIT;

typedef union {
    uint32_t                           w;
    MAC_RX_DATA_IN_WAIT                b;
}   MAC_RX_DATA_IN_WAIT_U;


// 0x40080358 register ------------------------------------
typedef struct {
    uint32_t                           DMA_SEG_THRESHOLD                  :8 ;
    uint32_t                           ABORT_STOP_MODE                    :3 ;
    uint32_t                           reserved0                          :1 ;
    uint32_t                           DMA_CMD_QUEUE_THRESHOLD            :3 ;
    uint32_t                           reserved1                          :17;
}   MAC_DMA_SEG_THRESHOLD;

typedef union {
    uint32_t                           w;
    MAC_DMA_SEG_THRESHOLD              b;
}   MAC_DMA_SEG_THRESHOLD_U;


// 0x4008035C register ------------------------------------
typedef struct {
    uint32_t                           reserved0                          :20;
    uint32_t                           KEY_TYPE                           :1 ;
    uint32_t                           reserved1                          :3 ;
    uint32_t                           KEY_ID                             :3 ;
    uint32_t                           reserved2                          :1 ;
    uint32_t                           TYPE                               :4 ;
}   MAC_SEC_KEY_CMD;

typedef union {
    uint32_t                           w;
    MAC_SEC_KEY_CMD                    b;
}   MAC_SEC_KEY_CMD_U;


// 0x40080360 register ------------------------------------
typedef struct {
    uint32_t                           SEC_KEY_CMD_EN                     :32;
}   MAC_SEC_KEY_CMD_EN;

typedef union {
    uint32_t                           w;
    MAC_SEC_KEY_CMD_EN                 b;
}   MAC_SEC_KEY_CMD_EN_U;


// 0x40080364 register ------------------------------------
typedef struct {
    uint32_t                           SEC_KEY_VALUE0                     :32;
}   MAC_SEC_KEY_VALUE0;

typedef union {
    uint32_t                           w;
    MAC_SEC_KEY_VALUE0                 b;
}   MAC_SEC_KEY_VALUE0_U;


// 0x40080368 register ------------------------------------
typedef struct {
    uint32_t                           SEC_KEY_VALUE1                     :32;
}   MAC_SEC_KEY_VALUE1;

typedef union {
    uint32_t                           w;
    MAC_SEC_KEY_VALUE1                 b;
}   MAC_SEC_KEY_VALUE1_U;


// 0x4008036C register ------------------------------------
typedef struct {
    uint32_t                           SEC_KEY_VALUE2                     :32;
}   MAC_SEC_KEY_VALUE2;

typedef union {
    uint32_t                           w;
    MAC_SEC_KEY_VALUE2                 b;
}   MAC_SEC_KEY_VALUE2_U;


// 0x40080370 register ------------------------------------
typedef struct {
    uint32_t                           SEC_KEY_VALUE3                     :32;
}   MAC_SEC_KEY_VALUE3;

typedef union {
    uint32_t                           w;
    MAC_SEC_KEY_VALUE3                 b;
}   MAC_SEC_KEY_VALUE3_U;


// 0x40080374 register ------------------------------------
typedef struct {
    uint32_t                           SEC_STA_ADDRESS0                   :32;
}   MAC_SEC_STA_ADDRESS0;

typedef union {
    uint32_t                           w;
    MAC_SEC_STA_ADDRESS0               b;
}   MAC_SEC_STA_ADDRESS0_U;


// 0x40080378 register ------------------------------------
typedef struct {
    uint32_t                           MAC_ADDRESS                        :16;
    uint32_t                           AID                                :13;
    uint32_t                           reserved0                          :3 ;
}   MAC_SEC_STA_ADDRESS1;

typedef union {
    uint32_t                           w;
    MAC_SEC_STA_ADDRESS1               b;
}   MAC_SEC_STA_ADDRESS1_U;


// 0x4008037C register ------------------------------------
typedef struct {
    uint32_t                           TID                                :4 ;
    uint32_t                           KEY_ID                             :2 ;
    uint32_t                           reserved0                          :24;
    uint32_t                           TWT                                :1 ;
    uint32_t                           MOREDATA                           :1 ;
}   MAC_SEC_CCMP_UPDATE_INFO;

typedef union {
    uint32_t                           w;
    MAC_SEC_CCMP_UPDATE_INFO           b;
}   MAC_SEC_CCMP_UPDATE_INFO_U;


// 0x40080380 register ------------------------------------
typedef struct {
    uint32_t                           reserved0                          :24;
    uint32_t                           SEC_BIP_INPUT_INTERVAL             :4 ;
    uint32_t                           SEC_KEY_LOC_ENABLE                 :1 ;
    uint32_t                           SEC_SPP_ENABLE                     :1 ;
    uint32_t                           SEC_PV0_MANAGEMENT_ENC_BYPASS      :1 ;
    uint32_t                           SEC_PV0_MANAGEMENT_DEC_BYPASS      :1 ;
}   MAC_SEC_CONFIG;

typedef union {
    uint32_t                           w;
    MAC_SEC_CONFIG                     b;
}   MAC_SEC_CONFIG_U;


// 0x40080384 register ------------------------------------
typedef struct {
    uint32_t                           SEC_OFFLINE_ENC_START_ADDR         :32;
}   MAC_SEC_OFFLINE_ENC_START_ADDR;

typedef union {
    uint32_t                           w;
    MAC_SEC_OFFLINE_ENC_START_ADDR     b;
}   MAC_SEC_OFFLINE_ENC_START_ADDR_U;


// 0x40080388 register ------------------------------------
typedef struct {
    uint32_t                           SEC_OFFLINE_DEC_START_DESC         :5 ;
    uint32_t                           reserved0                          :27;
}   MAC_SEC_OFFLINE_DEC_START_DESC;

typedef union {
    uint32_t                           w;
    MAC_SEC_OFFLINE_DEC_START_DESC     b;
}   MAC_SEC_OFFLINE_DEC_START_DESC_U;


// 0x4008038C register ------------------------------------
typedef struct {
    uint32_t                           SEC_OFFLINE_REQUEST_DEC            :1 ;
    uint32_t                           SEC_OFFLINE_REQUEST_ENC            :1 ;
    uint32_t                           reserved0                          :30;
}   MAC_SEC_OFFLINE_REQUEST;

typedef union {
    uint32_t                           w;
    MAC_SEC_OFFLINE_REQUEST            b;
}   MAC_SEC_OFFLINE_REQUEST_U;


// 0x40080390 register ------------------------------------
typedef struct {
    uint32_t                           SEC_INFO_1                         :32;
}   MAC_SEC_INFO_1;

typedef union {
    uint32_t                           w;
    MAC_SEC_INFO_1                     b;
}   MAC_SEC_INFO_1_U;


// 0x40080394 register ------------------------------------
typedef struct {
    uint32_t                           SEC_INFO_2                         :32;
}   MAC_SEC_INFO_2;

typedef union {
    uint32_t                           w;
    MAC_SEC_INFO_2                     b;
}   MAC_SEC_INFO_2_U;


// 0x40080398 register ------------------------------------
typedef struct {
    uint32_t                           SEC_INFO_3                         :32;
}   MAC_SEC_INFO_3;

typedef union {
    uint32_t                           w;
    MAC_SEC_INFO_3                     b;
}   MAC_SEC_INFO_3_U;


// 0x4008039C register ------------------------------------
typedef struct {
    uint32_t                           SEC_INFO_4                         :32;
}   MAC_SEC_INFO_4;

typedef union {
    uint32_t                           w;
    MAC_SEC_INFO_4                     b;
}   MAC_SEC_INFO_4_U;


// 0x400803A0 register ------------------------------------
typedef struct {
    uint32_t                           READ_OFFSET_ENCRYPT_0              :5 ;
    uint32_t                           READ_OFFSET_ENCRYPT_1              :5 ;
    uint32_t                           READ_OFFSET_DECRYPT                :5 ;
    uint32_t                           READ_OFFSET_ENCRYPT_2              :5 ;
    uint32_t                           READ_OFFSET_ENCRYPT_3              :5 ;
    uint32_t                           reserved0                          :7 ;
}   MAC_SEC_OFFSET;

typedef union {
    uint32_t                           w;
    MAC_SEC_OFFSET                     b;
}   MAC_SEC_OFFSET_U;


// 0x400803A4 register ------------------------------------
typedef struct {
    uint32_t                           SEC_DATA_IN_WAIT_CNT               :32;
}   MAC_SEC_DATA_IN_WAIT_CNT;

typedef union {
    uint32_t                           w;
    MAC_SEC_DATA_IN_WAIT_CNT           b;
}   MAC_SEC_DATA_IN_WAIT_CNT_U;


// 0x400803A8 register ------------------------------------
typedef struct {
    uint32_t                           SEC_KEY_FLAG_IDX                   :32;
}   MAC_SEC_KEY_FLAG_IDX;

typedef union {
    uint32_t                           w;
    MAC_SEC_KEY_FLAG_IDX               b;
}   MAC_SEC_KEY_FLAG_IDX_U;


// 0x400803AC register ------------------------------------
typedef struct {
    uint32_t                           TX_INDIR_REG_ADDR                  :32;
}   MAC_TX_INDIR_REG_ADDR;

typedef union {
    uint32_t                           w;
    MAC_TX_INDIR_REG_ADDR              b;
}   MAC_TX_INDIR_REG_ADDR_U;


// 0x400803B0 register ------------------------------------
typedef struct {
    uint32_t                           RX_INDIR_REG_ADDR                  :32;
}   MAC_RX_INDIR_REG_ADDR;

typedef union {
    uint32_t                           w;
    MAC_RX_INDIR_REG_ADDR              b;
}   MAC_RX_INDIR_REG_ADDR_U;


// 0x400803B4 register ------------------------------------
typedef struct {
    uint32_t                           SEC_INDIR_REG_ADDR                 :32;
}   MAC_SEC_INDIR_REG_ADDR;

typedef union {
    uint32_t                           w;
    MAC_SEC_INDIR_REG_ADDR             b;
}   MAC_SEC_INDIR_REG_ADDR_U;


// 0x400803B8 register ------------------------------------
typedef struct {
    uint32_t                           DMA_INDIR_REG_ADDR                 :32;
}   MAC_DMA_INDIR_REG_ADDR;

typedef union {
    uint32_t                           w;
    MAC_DMA_INDIR_REG_ADDR             b;
}   MAC_DMA_INDIR_REG_ADDR_U;


// 0x400803BC register ------------------------------------
typedef struct {
    uint32_t                           IRQ_INDIR_REG_ADDR                 :32;
}   MAC_IRQ_INDIR_REG_ADDR;

typedef union {
    uint32_t                           w;
    MAC_IRQ_INDIR_REG_ADDR             b;
}   MAC_IRQ_INDIR_REG_ADDR_U;


// 0x400803C0 register ------------------------------------
typedef struct {
    uint32_t                           MEM_INDIR_REG_ADDR                 :32;
}   MAC_MEM_INDIR_REG_ADDR;

typedef union {
    uint32_t                           w;
    MAC_MEM_INDIR_REG_ADDR             b;
}   MAC_MEM_INDIR_REG_ADDR_U;


// 0x400803C4 register ------------------------------------
typedef struct {
    uint32_t                           TSF_0_LOWER                        :32;
}   MAC_TSF_0_LOWER;

typedef union {
    uint32_t                           w;
    MAC_TSF_0_LOWER                    b;
}   MAC_TSF_0_LOWER_U;


// 0x400803C8 register ------------------------------------
typedef struct {
    uint32_t                           TSF_0_UPPER                        :32;
}   MAC_TSF_0_UPPER;

typedef union {
    uint32_t                           w;
    MAC_TSF_0_UPPER                    b;
}   MAC_TSF_0_UPPER_U;


// 0x400803CC register ------------------------------------
typedef struct {
    uint32_t                           TSF_0_ALARM_LOWER                  :32;
}   MAC_TSF_0_ALARM_LOWER;

typedef union {
    uint32_t                           w;
    MAC_TSF_0_ALARM_LOWER              b;
}   MAC_TSF_0_ALARM_LOWER_U;


// 0x400803D0 register ------------------------------------
typedef struct {
    uint32_t                           BCN_INTERVAL_0                     :32;
}   MAC_BCN_INTERVAL_0;

typedef union {
    uint32_t                           w;
    MAC_BCN_INTERVAL_0                 b;
}   MAC_BCN_INTERVAL_0_U;


// 0x400803D4 register ------------------------------------
typedef struct {
    uint32_t                           TBTT_INTERRUPT_MARGIN_0            :32;
}   MAC_TBTT_INTERRUPT_MARGIN_0;

typedef union {
    uint32_t                           w;
    MAC_TBTT_INTERRUPT_MARGIN_0        b;
}   MAC_TBTT_INTERRUPT_MARGIN_0_U;


// 0x400803D8 register ------------------------------------
typedef struct {
    uint32_t                           TBTT_RESTART_RANGE_0               :32;
}   MAC_TBTT_RESTART_RANGE_0;

typedef union {
    uint32_t                           w;
    MAC_TBTT_RESTART_RANGE_0           b;
}   MAC_TBTT_RESTART_RANGE_0_U;


// 0x400803DC register ------------------------------------
typedef struct {
    uint32_t                           TSF_1_LOWER                        :32;
}   MAC_TSF_1_LOWER;

typedef union {
    uint32_t                           w;
    MAC_TSF_1_LOWER                    b;
}   MAC_TSF_1_LOWER_U;


// 0x400803E0 register ------------------------------------
typedef struct {
    uint32_t                           TSF_1_UPPER                        :32;
}   MAC_TSF_1_UPPER;

typedef union {
    uint32_t                           w;
    MAC_TSF_1_UPPER                    b;
}   MAC_TSF_1_UPPER_U;


// 0x400803E4 register ------------------------------------
typedef struct {
    uint32_t                           TSF_1_ALARM_LOWER                  :32;
}   MAC_TSF_1_ALARM_LOWER;

typedef union {
    uint32_t                           w;
    MAC_TSF_1_ALARM_LOWER              b;
}   MAC_TSF_1_ALARM_LOWER_U;


// 0x400803E8 register ------------------------------------
typedef struct {
    uint32_t                           BCN_INTERVAL_1                     :32;
}   MAC_BCN_INTERVAL_1;

typedef union {
    uint32_t                           w;
    MAC_BCN_INTERVAL_1                 b;
}   MAC_BCN_INTERVAL_1_U;


// 0x400803EC register ------------------------------------
typedef struct {
    uint32_t                           TBTT_INTERRUPT_MARGIN_1            :32;
}   MAC_TBTT_INTERRUPT_MARGIN_1;

typedef union {
    uint32_t                           w;
    MAC_TBTT_INTERRUPT_MARGIN_1        b;
}   MAC_TBTT_INTERRUPT_MARGIN_1_U;


// 0x400803F0 register ------------------------------------
typedef struct {
    uint32_t                           TBTT_RESTART_RANGE_1               :32;
}   MAC_TBTT_RESTART_RANGE_1;

typedef union {
    uint32_t                           w;
    MAC_TBTT_RESTART_RANGE_1           b;
}   MAC_TBTT_RESTART_RANGE_1_U;


// 0x400803F4 register ------------------------------------
typedef struct {
    uint32_t                           IRQ_MASK0                          :32;
}   MAC_IRQ_MASK0;

typedef union {
    uint32_t                           w;
    MAC_IRQ_MASK0                      b;
}   MAC_IRQ_MASK0_U;


// 0x400803F8 register ------------------------------------
typedef struct {
    uint32_t                           IRQ_MASK1                          :32;
}   MAC_IRQ_MASK1;

typedef union {
    uint32_t                           w;
    MAC_IRQ_MASK1                      b;
}   MAC_IRQ_MASK1_U;


// 0x400803FC register ------------------------------------
typedef struct {
    uint32_t                           IRQ_SET_CLEAR0                     :32;
}   MAC_IRQ_SET_CLEAR0;

typedef union {
    uint32_t                           w;
    MAC_IRQ_SET_CLEAR0                 b;
}   MAC_IRQ_SET_CLEAR0_U;


// 0x40080400 register ------------------------------------
typedef struct {
    uint32_t                           IRQ_SET_CLEAR1                     :32;
}   MAC_IRQ_SET_CLEAR1;

typedef union {
    uint32_t                           w;
    MAC_IRQ_SET_CLEAR1                 b;
}   MAC_IRQ_SET_CLEAR1_U;


// 0x40080404 register ------------------------------------
typedef struct {
    uint32_t                           MAC_CG_MODE                        :2 ;
    uint32_t                           BUS_CG_MODE                        :2 ;
    uint32_t                           CCMP_CG_MODE                       :2 ;
    uint32_t                           LUT_CG_MODE                        :2 ;
    uint32_t                           reserved0                          :23;
    uint32_t                           GLOBAL_CG_EN                       :1 ;
}   MAC_CLOCK_GATING_CONFIG;

typedef union {
    uint32_t                           w;
    MAC_CLOCK_GATING_CONFIG            b;
}   MAC_CLOCK_GATING_CONFIG_U;


// 0x40080408 register ------------------------------------
typedef struct {
    uint32_t                           ACK_SUCCESS                        :1 ;
    uint32_t                           FAILED_BITMAP_VALID                :1 ;
    uint32_t                           TXOP_END                           :1 ;
    uint32_t                           FAIL_REASON                        :3 ;
    uint32_t                           ACK_POLICY                         :1 ;
    uint32_t                           BW_MATCH_FAIL                      :1 ;
    uint32_t                           SIFS_TIMEOUT                       :1 ;
    uint32_t                           INSIDE_RAW                         :1 ;
    uint32_t                           LACK_TXTIME                        :1 ;
    uint32_t                           MORE_DATA                          :1 ;
    uint32_t                           SEQUENCE                           :3 ;
    uint32_t                           VALID_RESULT                       :1 ;
    uint32_t                           RECEIVED_SNR                       :8 ;
    uint32_t                           FEEDBACK_SNR                       :7 ;
    uint32_t                           FEEDBACK_VALID                     :1 ;
}   MAC_TX_RESULT_0;

typedef union {
    uint32_t                           w;
    MAC_TX_RESULT_0                    b;
}   MAC_TX_RESULT_0_U;


// 0x4008040C register ------------------------------------
typedef struct {
    uint32_t                           TX_RESULT_1                        :32;
}   MAC_TX_RESULT_1;

typedef union {
    uint32_t                           w;
    MAC_TX_RESULT_1                    b;
}   MAC_TX_RESULT_1_U;


// 0x40080410 register ------------------------------------
typedef struct {
    uint32_t                           TX_RESULT_2                        :32;
}   MAC_TX_RESULT_2;

typedef union {
    uint32_t                           w;
    MAC_TX_RESULT_2                    b;
}   MAC_TX_RESULT_2_U;


// 0x40080414 register ------------------------------------
typedef struct {
    uint32_t                           TX_RESULT_3                        :32;
}   MAC_TX_RESULT_3;

typedef union {
    uint32_t                           w;
    MAC_TX_RESULT_3                    b;
}   MAC_TX_RESULT_3_U;


// 0x40080418 register ------------------------------------
typedef struct {
    uint32_t                           TX_RESULT_4                        :32;
}   MAC_TX_RESULT_4;

typedef union {
    uint32_t                           w;
    MAC_TX_RESULT_4                    b;
}   MAC_TX_RESULT_4_U;


// 0x4008041C register ------------------------------------
typedef struct {
    uint32_t                           TX_RESULT_5                        :32;
}   MAC_TX_RESULT_5;

typedef union {
    uint32_t                           w;
    MAC_TX_RESULT_5                    b;
}   MAC_TX_RESULT_5_U;


// 0x40080420 register ------------------------------------
typedef struct {
    uint32_t                           TX_RESULT_6                        :32;
}   MAC_TX_RESULT_6;

typedef union {
    uint32_t                           w;
    MAC_TX_RESULT_6                    b;
}   MAC_TX_RESULT_6_U;


// 0x40080424 register ------------------------------------
typedef struct {
    uint32_t                           TX_RESULT_7                        :32;
}   MAC_TX_RESULT_7;

typedef union {
    uint32_t                           w;
    MAC_TX_RESULT_7                    b;
}   MAC_TX_RESULT_7_U;


// 0x40080428 register ------------------------------------
typedef struct {
    uint32_t                           TX_RESULT_8                        :32;
}   MAC_TX_RESULT_8;

typedef union {
    uint32_t                           w;
    MAC_TX_RESULT_8                    b;
}   MAC_TX_RESULT_8_U;


// 0x4008042C register ------------------------------------
typedef struct {
    uint32_t                           TX_RESULT_9                        :32;
}   MAC_TX_RESULT_9;

typedef union {
    uint32_t                           w;
    MAC_TX_RESULT_9                    b;
}   MAC_TX_RESULT_9_U;


// 0x40080430 register ------------------------------------
typedef struct {
    uint32_t                           TX_RESULT_10                       :32;
}   MAC_TX_RESULT_10;

typedef union {
    uint32_t                           w;
    MAC_TX_RESULT_10                   b;
}   MAC_TX_RESULT_10_U;


// 0x40080434 register ------------------------------------
typedef struct {
    uint32_t                           TX_RESULT_11                       :32;
}   MAC_TX_RESULT_11;

typedef union {
    uint32_t                           w;
    MAC_TX_RESULT_11                   b;
}   MAC_TX_RESULT_11_U;


// 0x40080438 register ------------------------------------
typedef struct {
    uint32_t                           TX_RESULT_12                       :32;
}   MAC_TX_RESULT_12;

typedef union {
    uint32_t                           w;
    MAC_TX_RESULT_12                   b;
}   MAC_TX_RESULT_12_U;


// 0x4008043C register ------------------------------------
typedef struct {
    uint32_t                           TX_RESULT_13                       :32;
}   MAC_TX_RESULT_13;

typedef union {
    uint32_t                           w;
    MAC_TX_RESULT_13                   b;
}   MAC_TX_RESULT_13_U;


// 0x40080440 register ------------------------------------
typedef struct {
    uint32_t                           TX_RESULT_14                       :32;
}   MAC_TX_RESULT_14;

typedef union {
    uint32_t                           w;
    MAC_TX_RESULT_14                   b;
}   MAC_TX_RESULT_14_U;


// 0x40080444 register ------------------------------------
typedef struct {
    uint32_t                           TX_RESULT_15                       :32;
}   MAC_TX_RESULT_15;

typedef union {
    uint32_t                           w;
    MAC_TX_RESULT_15                   b;
}   MAC_TX_RESULT_15_U;


// 0x40080448 register ------------------------------------
typedef struct {
    uint32_t                           TX_RESULT_16                       :32;
}   MAC_TX_RESULT_16;

typedef union {
    uint32_t                           w;
    MAC_TX_RESULT_16                   b;
}   MAC_TX_RESULT_16_U;


// 0x4008044C register ------------------------------------
typedef struct {
    uint32_t                           TX_RESULT_17                       :32;
}   MAC_TX_RESULT_17;

typedef union {
    uint32_t                           w;
    MAC_TX_RESULT_17                   b;
}   MAC_TX_RESULT_17_U;


// 0x40080450 register ------------------------------------
typedef struct {
    uint32_t                           TX_RESULT_18                       :32;
}   MAC_TX_RESULT_18;

typedef union {
    uint32_t                           w;
    MAC_TX_RESULT_18                   b;
}   MAC_TX_RESULT_18_U;


// 0x40080454 register ------------------------------------
typedef struct {
    uint32_t                           TX_RESULT_19                       :32;
}   MAC_TX_RESULT_19;

typedef union {
    uint32_t                           w;
    MAC_TX_RESULT_19                   b;
}   MAC_TX_RESULT_19_U;


// 0x40080458 register ------------------------------------
typedef struct {
    uint32_t                           TX_RESULT_20                       :32;
}   MAC_TX_RESULT_20;

typedef union {
    uint32_t                           w;
    MAC_TX_RESULT_20                   b;
}   MAC_TX_RESULT_20_U;


// 0x4008045C register ------------------------------------
typedef struct {
    uint32_t                           TX_RESULT_21                       :32;
}   MAC_TX_RESULT_21;

typedef union {
    uint32_t                           w;
    MAC_TX_RESULT_21                   b;
}   MAC_TX_RESULT_21_U;


// 0x40080460 register ------------------------------------
typedef struct {
    uint32_t                           TX_FAILED_BITMAP_LOWER_0           :32;
}   MAC_TX_FAILED_BITMAP_LOWER_0;

typedef union {
    uint32_t                           w;
    MAC_TX_FAILED_BITMAP_LOWER_0       b;
}   MAC_TX_FAILED_BITMAP_LOWER_0_U;


// 0x40080464 register ------------------------------------
typedef struct {
    uint32_t                           TX_FAILED_BITMAP_UPPER_0           :32;
}   MAC_TX_FAILED_BITMAP_UPPER_0;

typedef union {
    uint32_t                           w;
    MAC_TX_FAILED_BITMAP_UPPER_0       b;
}   MAC_TX_FAILED_BITMAP_UPPER_0_U;


// 0x40080468 register ------------------------------------
typedef struct {
    uint32_t                           TX_FAILED_BITMAP_LOWER_1           :32;
}   MAC_TX_FAILED_BITMAP_LOWER_1;

typedef union {
    uint32_t                           w;
    MAC_TX_FAILED_BITMAP_LOWER_1       b;
}   MAC_TX_FAILED_BITMAP_LOWER_1_U;


// 0x4008046C register ------------------------------------
typedef struct {
    uint32_t                           TX_FAILED_BITMAP_UPPER_1           :32;
}   MAC_TX_FAILED_BITMAP_UPPER_1;

typedef union {
    uint32_t                           w;
    MAC_TX_FAILED_BITMAP_UPPER_1       b;
}   MAC_TX_FAILED_BITMAP_UPPER_1_U;


// 0x40080470 register ------------------------------------
typedef struct {
    uint32_t                           TX_FAILED_BITMAP_LOWER_2           :32;
}   MAC_TX_FAILED_BITMAP_LOWER_2;

typedef union {
    uint32_t                           w;
    MAC_TX_FAILED_BITMAP_LOWER_2       b;
}   MAC_TX_FAILED_BITMAP_LOWER_2_U;


// 0x40080474 register ------------------------------------
typedef struct {
    uint32_t                           TX_FAILED_BITMAP_UPPER_2           :32;
}   MAC_TX_FAILED_BITMAP_UPPER_2;

typedef union {
    uint32_t                           w;
    MAC_TX_FAILED_BITMAP_UPPER_2       b;
}   MAC_TX_FAILED_BITMAP_UPPER_2_U;


// 0x40080478 register ------------------------------------
typedef struct {
    uint32_t                           TX_FAILED_BITMAP_LOWER_3           :32;
}   MAC_TX_FAILED_BITMAP_LOWER_3;

typedef union {
    uint32_t                           w;
    MAC_TX_FAILED_BITMAP_LOWER_3       b;
}   MAC_TX_FAILED_BITMAP_LOWER_3_U;


// 0x4008047C register ------------------------------------
typedef struct {
    uint32_t                           TX_FAILED_BITMAP_UPPER_3           :32;
}   MAC_TX_FAILED_BITMAP_UPPER_3;

typedef union {
    uint32_t                           w;
    MAC_TX_FAILED_BITMAP_UPPER_3       b;
}   MAC_TX_FAILED_BITMAP_UPPER_3_U;


// 0x40080480 register ------------------------------------
typedef struct {
    uint32_t                           TX_FAILED_BITMAP_LOWER_4           :32;
}   MAC_TX_FAILED_BITMAP_LOWER_4;

typedef union {
    uint32_t                           w;
    MAC_TX_FAILED_BITMAP_LOWER_4       b;
}   MAC_TX_FAILED_BITMAP_LOWER_4_U;


// 0x40080484 register ------------------------------------
typedef struct {
    uint32_t                           TX_FAILED_BITMAP_UPPER_4           :32;
}   MAC_TX_FAILED_BITMAP_UPPER_4;

typedef union {
    uint32_t                           w;
    MAC_TX_FAILED_BITMAP_UPPER_4       b;
}   MAC_TX_FAILED_BITMAP_UPPER_4_U;


// 0x40080488 register ------------------------------------
typedef struct {
    uint32_t                           TX_FAILED_BITMAP_LOWER_5           :32;
}   MAC_TX_FAILED_BITMAP_LOWER_5;

typedef union {
    uint32_t                           w;
    MAC_TX_FAILED_BITMAP_LOWER_5       b;
}   MAC_TX_FAILED_BITMAP_LOWER_5_U;


// 0x4008048C register ------------------------------------
typedef struct {
    uint32_t                           TX_FAILED_BITMAP_UPPER_5           :32;
}   MAC_TX_FAILED_BITMAP_UPPER_5;

typedef union {
    uint32_t                           w;
    MAC_TX_FAILED_BITMAP_UPPER_5       b;
}   MAC_TX_FAILED_BITMAP_UPPER_5_U;


// 0x40080490 register ------------------------------------
typedef struct {
    uint32_t                           TX_FAILED_BITMAP_LOWER_6           :32;
}   MAC_TX_FAILED_BITMAP_LOWER_6;

typedef union {
    uint32_t                           w;
    MAC_TX_FAILED_BITMAP_LOWER_6       b;
}   MAC_TX_FAILED_BITMAP_LOWER_6_U;


// 0x40080494 register ------------------------------------
typedef struct {
    uint32_t                           TX_FAILED_BITMAP_UPPER_6           :32;
}   MAC_TX_FAILED_BITMAP_UPPER_6;

typedef union {
    uint32_t                           w;
    MAC_TX_FAILED_BITMAP_UPPER_6       b;
}   MAC_TX_FAILED_BITMAP_UPPER_6_U;


// 0x40080498 register ------------------------------------
typedef struct {
    uint32_t                           TX_FAILED_BITMAP_LOWER_7           :32;
}   MAC_TX_FAILED_BITMAP_LOWER_7;

typedef union {
    uint32_t                           w;
    MAC_TX_FAILED_BITMAP_LOWER_7       b;
}   MAC_TX_FAILED_BITMAP_LOWER_7_U;


// 0x4008049C register ------------------------------------
typedef struct {
    uint32_t                           TX_FAILED_BITMAP_UPPER_7           :32;
}   MAC_TX_FAILED_BITMAP_UPPER_7;

typedef union {
    uint32_t                           w;
    MAC_TX_FAILED_BITMAP_UPPER_7       b;
}   MAC_TX_FAILED_BITMAP_UPPER_7_U;


// 0x400804A0 register ------------------------------------
typedef struct {
    uint32_t                           TX_FAILED_BITMAP_LOWER_8           :32;
}   MAC_TX_FAILED_BITMAP_LOWER_8;

typedef union {
    uint32_t                           w;
    MAC_TX_FAILED_BITMAP_LOWER_8       b;
}   MAC_TX_FAILED_BITMAP_LOWER_8_U;


// 0x400804A4 register ------------------------------------
typedef struct {
    uint32_t                           TX_FAILED_BITMAP_UPPER_8           :32;
}   MAC_TX_FAILED_BITMAP_UPPER_8;

typedef union {
    uint32_t                           w;
    MAC_TX_FAILED_BITMAP_UPPER_8       b;
}   MAC_TX_FAILED_BITMAP_UPPER_8_U;


// 0x400804A8 register ------------------------------------
typedef struct {
    uint32_t                           TX_FAILED_BITMAP_LOWER_9           :32;
}   MAC_TX_FAILED_BITMAP_LOWER_9;

typedef union {
    uint32_t                           w;
    MAC_TX_FAILED_BITMAP_LOWER_9       b;
}   MAC_TX_FAILED_BITMAP_LOWER_9_U;


// 0x400804AC register ------------------------------------
typedef struct {
    uint32_t                           TX_FAILED_BITMAP_UPPER_9           :32;
}   MAC_TX_FAILED_BITMAP_UPPER_9;

typedef union {
    uint32_t                           w;
    MAC_TX_FAILED_BITMAP_UPPER_9       b;
}   MAC_TX_FAILED_BITMAP_UPPER_9_U;


// 0x400804B0 register ------------------------------------
typedef struct {
    uint32_t                           TX_FAILED_BITMAP_LOWER_10          :32;
}   MAC_TX_FAILED_BITMAP_LOWER_10;

typedef union {
    uint32_t                           w;
    MAC_TX_FAILED_BITMAP_LOWER_10      b;
}   MAC_TX_FAILED_BITMAP_LOWER_10_U;


// 0x400804B4 register ------------------------------------
typedef struct {
    uint32_t                           TX_FAILED_BITMAP_UPPER_10          :32;
}   MAC_TX_FAILED_BITMAP_UPPER_10;

typedef union {
    uint32_t                           w;
    MAC_TX_FAILED_BITMAP_UPPER_10      b;
}   MAC_TX_FAILED_BITMAP_UPPER_10_U;


// 0x400804B8 register ------------------------------------
typedef struct {
    uint32_t                           RESPONSE_TX_RESULT                 :16;
    uint32_t                           reserved0                          :16;
}   MAC_RESPONSE_TX_RESULT;

typedef union {
    uint32_t                           w;
    MAC_RESPONSE_TX_RESULT             b;
}   MAC_RESPONSE_TX_RESULT_U;


// 0x400804BC register ------------------------------------
typedef struct {
    uint32_t                           FRAGMENT                           :2 ;
    uint32_t                           OWNERSHIP                          :1 ;
    uint32_t                           reserved0                          :29;
}   MAC_RX_WRITE_EN_DL_DESC0;

typedef union {
    uint32_t                           w;
    MAC_RX_WRITE_EN_DL_DESC0           b;
}   MAC_RX_WRITE_EN_DL_DESC0_U;


// 0x400804C0 register ------------------------------------
typedef struct {
    uint32_t                           RX_WRITE_EN_DL_DESC1               :3 ;
    uint32_t                           reserved0                          :29;
}   MAC_RX_WRITE_EN_DL_DESC1;

typedef union {
    uint32_t                           w;
    MAC_RX_WRITE_EN_DL_DESC1           b;
}   MAC_RX_WRITE_EN_DL_DESC1_U;


// 0x400804C4 register ------------------------------------
typedef struct {
    uint32_t                           RX_WRITE_EN_DL_DESC2               :3 ;
    uint32_t                           reserved0                          :29;
}   MAC_RX_WRITE_EN_DL_DESC2;

typedef union {
    uint32_t                           w;
    MAC_RX_WRITE_EN_DL_DESC2           b;
}   MAC_RX_WRITE_EN_DL_DESC2_U;


// 0x400804C8 register ------------------------------------
typedef struct {
    uint32_t                           RX_WRITE_EN_DL_DESC3               :3 ;
    uint32_t                           reserved0                          :29;
}   MAC_RX_WRITE_EN_DL_DESC3;

typedef union {
    uint32_t                           w;
    MAC_RX_WRITE_EN_DL_DESC3           b;
}   MAC_RX_WRITE_EN_DL_DESC3_U;


// 0x400804CC register ------------------------------------
typedef struct {
    uint32_t                           RX_WRITE_EN_DL_DESC4               :3 ;
    uint32_t                           reserved0                          :29;
}   MAC_RX_WRITE_EN_DL_DESC4;

typedef union {
    uint32_t                           w;
    MAC_RX_WRITE_EN_DL_DESC4           b;
}   MAC_RX_WRITE_EN_DL_DESC4_U;


// 0x400804D0 register ------------------------------------
typedef struct {
    uint32_t                           RX_WRITE_EN_DL_DESC5               :3 ;
    uint32_t                           reserved0                          :29;
}   MAC_RX_WRITE_EN_DL_DESC5;

typedef union {
    uint32_t                           w;
    MAC_RX_WRITE_EN_DL_DESC5           b;
}   MAC_RX_WRITE_EN_DL_DESC5_U;


// 0x400804D4 register ------------------------------------
typedef struct {
    uint32_t                           RX_WRITE_EN_DL_DESC6               :3 ;
    uint32_t                           reserved0                          :29;
}   MAC_RX_WRITE_EN_DL_DESC6;

typedef union {
    uint32_t                           w;
    MAC_RX_WRITE_EN_DL_DESC6           b;
}   MAC_RX_WRITE_EN_DL_DESC6_U;


// 0x400804D8 register ------------------------------------
typedef struct {
    uint32_t                           RX_WRITE_EN_DL_DESC7               :3 ;
    uint32_t                           reserved0                          :29;
}   MAC_RX_WRITE_EN_DL_DESC7;

typedef union {
    uint32_t                           w;
    MAC_RX_WRITE_EN_DL_DESC7           b;
}   MAC_RX_WRITE_EN_DL_DESC7_U;


// 0x400804DC register ------------------------------------
typedef struct {
    uint32_t                           RX_WRITE_EN_DL_DESC8               :3 ;
    uint32_t                           reserved0                          :29;
}   MAC_RX_WRITE_EN_DL_DESC8;

typedef union {
    uint32_t                           w;
    MAC_RX_WRITE_EN_DL_DESC8           b;
}   MAC_RX_WRITE_EN_DL_DESC8_U;


// 0x400804E0 register ------------------------------------
typedef struct {
    uint32_t                           RX_WRITE_EN_DL_DESC9               :3 ;
    uint32_t                           reserved0                          :29;
}   MAC_RX_WRITE_EN_DL_DESC9;

typedef union {
    uint32_t                           w;
    MAC_RX_WRITE_EN_DL_DESC9           b;
}   MAC_RX_WRITE_EN_DL_DESC9_U;


// 0x400804E4 register ------------------------------------
typedef struct {
    uint32_t                           RX_WRITE_EN_DL_DESC10              :3 ;
    uint32_t                           reserved0                          :29;
}   MAC_RX_WRITE_EN_DL_DESC10;

typedef union {
    uint32_t                           w;
    MAC_RX_WRITE_EN_DL_DESC10          b;
}   MAC_RX_WRITE_EN_DL_DESC10_U;


// 0x400804E8 register ------------------------------------
typedef struct {
    uint32_t                           RX_WRITE_EN_DL_DESC11              :3 ;
    uint32_t                           reserved0                          :29;
}   MAC_RX_WRITE_EN_DL_DESC11;

typedef union {
    uint32_t                           w;
    MAC_RX_WRITE_EN_DL_DESC11          b;
}   MAC_RX_WRITE_EN_DL_DESC11_U;


// 0x400804EC register ------------------------------------
typedef struct {
    uint32_t                           RX_WRITE_EN_DL_DESC12              :3 ;
    uint32_t                           reserved0                          :29;
}   MAC_RX_WRITE_EN_DL_DESC12;

typedef union {
    uint32_t                           w;
    MAC_RX_WRITE_EN_DL_DESC12          b;
}   MAC_RX_WRITE_EN_DL_DESC12_U;


// 0x400804F0 register ------------------------------------
typedef struct {
    uint32_t                           RX_WRITE_EN_DL_DESC13              :3 ;
    uint32_t                           reserved0                          :29;
}   MAC_RX_WRITE_EN_DL_DESC13;

typedef union {
    uint32_t                           w;
    MAC_RX_WRITE_EN_DL_DESC13          b;
}   MAC_RX_WRITE_EN_DL_DESC13_U;


// 0x400804F4 register ------------------------------------
typedef struct {
    uint32_t                           RX_WRITE_EN_DL_DESC14              :3 ;
    uint32_t                           reserved0                          :29;
}   MAC_RX_WRITE_EN_DL_DESC14;

typedef union {
    uint32_t                           w;
    MAC_RX_WRITE_EN_DL_DESC14          b;
}   MAC_RX_WRITE_EN_DL_DESC14_U;


// 0x400804F8 register ------------------------------------
typedef struct {
    uint32_t                           RX_WRITE_EN_DL_DESC15              :3 ;
    uint32_t                           reserved0                          :29;
}   MAC_RX_WRITE_EN_DL_DESC15;

typedef union {
    uint32_t                           w;
    MAC_RX_WRITE_EN_DL_DESC15          b;
}   MAC_RX_WRITE_EN_DL_DESC15_U;


// 0x400804FC register ------------------------------------
typedef struct {
    uint32_t                           RX_WRITE_EN_DL_DESC16              :3 ;
    uint32_t                           reserved0                          :29;
}   MAC_RX_WRITE_EN_DL_DESC16;

typedef union {
    uint32_t                           w;
    MAC_RX_WRITE_EN_DL_DESC16          b;
}   MAC_RX_WRITE_EN_DL_DESC16_U;


// 0x40080500 register ------------------------------------
typedef struct {
    uint32_t                           RX_WRITE_EN_DL_DESC17              :3 ;
    uint32_t                           reserved0                          :29;
}   MAC_RX_WRITE_EN_DL_DESC17;

typedef union {
    uint32_t                           w;
    MAC_RX_WRITE_EN_DL_DESC17          b;
}   MAC_RX_WRITE_EN_DL_DESC17_U;


// 0x40080504 register ------------------------------------
typedef struct {
    uint32_t                           RX_WRITE_EN_DL_DESC18              :3 ;
    uint32_t                           reserved0                          :29;
}   MAC_RX_WRITE_EN_DL_DESC18;

typedef union {
    uint32_t                           w;
    MAC_RX_WRITE_EN_DL_DESC18          b;
}   MAC_RX_WRITE_EN_DL_DESC18_U;


// 0x40080508 register ------------------------------------
typedef struct {
    uint32_t                           RX_WRITE_EN_DL_DESC19              :3 ;
    uint32_t                           reserved0                          :29;
}   MAC_RX_WRITE_EN_DL_DESC19;

typedef union {
    uint32_t                           w;
    MAC_RX_WRITE_EN_DL_DESC19          b;
}   MAC_RX_WRITE_EN_DL_DESC19_U;


// 0x4008050C register ------------------------------------
typedef struct {
    uint32_t                           RX_WRITE_EN_DL_DESC20              :3 ;
    uint32_t                           reserved0                          :29;
}   MAC_RX_WRITE_EN_DL_DESC20;

typedef union {
    uint32_t                           w;
    MAC_RX_WRITE_EN_DL_DESC20          b;
}   MAC_RX_WRITE_EN_DL_DESC20_U;


// 0x40080510 register ------------------------------------
typedef struct {
    uint32_t                           RX_WRITE_EN_DL_DESC21              :3 ;
    uint32_t                           reserved0                          :29;
}   MAC_RX_WRITE_EN_DL_DESC21;

typedef union {
    uint32_t                           w;
    MAC_RX_WRITE_EN_DL_DESC21          b;
}   MAC_RX_WRITE_EN_DL_DESC21_U;


// 0x40080514 register ------------------------------------
typedef struct {
    uint32_t                           RX_WRITE_EN_DL_DESC22              :3 ;
    uint32_t                           reserved0                          :29;
}   MAC_RX_WRITE_EN_DL_DESC22;

typedef union {
    uint32_t                           w;
    MAC_RX_WRITE_EN_DL_DESC22          b;
}   MAC_RX_WRITE_EN_DL_DESC22_U;


// 0x40080518 register ------------------------------------
typedef struct {
    uint32_t                           RX_WRITE_EN_DL_DESC23              :3 ;
    uint32_t                           reserved0                          :29;
}   MAC_RX_WRITE_EN_DL_DESC23;

typedef union {
    uint32_t                           w;
    MAC_RX_WRITE_EN_DL_DESC23          b;
}   MAC_RX_WRITE_EN_DL_DESC23_U;


// 0x4008051C register ------------------------------------
typedef struct {
    uint32_t                           RX_WRITE_EN_DL_DESC24              :3 ;
    uint32_t                           reserved0                          :29;
}   MAC_RX_WRITE_EN_DL_DESC24;

typedef union {
    uint32_t                           w;
    MAC_RX_WRITE_EN_DL_DESC24          b;
}   MAC_RX_WRITE_EN_DL_DESC24_U;


// 0x40080520 register ------------------------------------
typedef struct {
    uint32_t                           RX_WRITE_EN_DL_DESC25              :3 ;
    uint32_t                           reserved0                          :29;
}   MAC_RX_WRITE_EN_DL_DESC25;

typedef union {
    uint32_t                           w;
    MAC_RX_WRITE_EN_DL_DESC25          b;
}   MAC_RX_WRITE_EN_DL_DESC25_U;


// 0x40080524 register ------------------------------------
typedef struct {
    uint32_t                           RX_WRITE_EN_DL_DESC26              :3 ;
    uint32_t                           reserved0                          :29;
}   MAC_RX_WRITE_EN_DL_DESC26;

typedef union {
    uint32_t                           w;
    MAC_RX_WRITE_EN_DL_DESC26          b;
}   MAC_RX_WRITE_EN_DL_DESC26_U;


// 0x40080528 register ------------------------------------
typedef struct {
    uint32_t                           RX_WRITE_EN_DL_DESC27              :3 ;
    uint32_t                           reserved0                          :29;
}   MAC_RX_WRITE_EN_DL_DESC27;

typedef union {
    uint32_t                           w;
    MAC_RX_WRITE_EN_DL_DESC27          b;
}   MAC_RX_WRITE_EN_DL_DESC27_U;


// 0x4008052C register ------------------------------------
typedef struct {
    uint32_t                           RX_WRITE_EN_DL_DESC28              :3 ;
    uint32_t                           reserved0                          :29;
}   MAC_RX_WRITE_EN_DL_DESC28;

typedef union {
    uint32_t                           w;
    MAC_RX_WRITE_EN_DL_DESC28          b;
}   MAC_RX_WRITE_EN_DL_DESC28_U;


// 0x40080530 register ------------------------------------
typedef struct {
    uint32_t                           RX_WRITE_EN_DL_DESC29              :3 ;
    uint32_t                           reserved0                          :29;
}   MAC_RX_WRITE_EN_DL_DESC29;

typedef union {
    uint32_t                           w;
    MAC_RX_WRITE_EN_DL_DESC29          b;
}   MAC_RX_WRITE_EN_DL_DESC29_U;


// 0x40080534 register ------------------------------------
typedef struct {
    uint32_t                           RX_WRITE_EN_DL_DESC30              :3 ;
    uint32_t                           reserved0                          :29;
}   MAC_RX_WRITE_EN_DL_DESC30;

typedef union {
    uint32_t                           w;
    MAC_RX_WRITE_EN_DL_DESC30          b;
}   MAC_RX_WRITE_EN_DL_DESC30_U;


// 0x40080538 register ------------------------------------
typedef struct {
    uint32_t                           RX_WRITE_EN_DL_DESC31              :3 ;
    uint32_t                           reserved0                          :29;
}   MAC_RX_WRITE_EN_DL_DESC31;

typedef union {
    uint32_t                           w;
    MAC_RX_WRITE_EN_DL_DESC31          b;
}   MAC_RX_WRITE_EN_DL_DESC31_U;


// 0x4008053C register ------------------------------------
typedef struct {
    uint32_t                           RXSIG0                             :32;
}   MAC_RXSIG0;

typedef union {
    uint32_t                           w;
    MAC_RXSIG0                         b;
}   MAC_RXSIG0_U;


// 0x40080540 register ------------------------------------
typedef struct {
    uint32_t                           RXSIG1                             :32;
}   MAC_RXSIG1;

typedef union {
    uint32_t                           w;
    MAC_RXSIG1                         b;
}   MAC_RXSIG1_U;


// 0x40080544 register ------------------------------------
typedef struct {
    uint32_t                           RXVECTOR0                          :32;
}   MAC_RXVECTOR0;

typedef union {
    uint32_t                           w;
    MAC_RXVECTOR0                      b;
}   MAC_RXVECTOR0_U;


// 0x40080548 register ------------------------------------
typedef struct {
    uint32_t                           RXVECTOR1                          :32;
}   MAC_RXVECTOR1;

typedef union {
    uint32_t                           w;
    MAC_RXVECTOR1                      b;
}   MAC_RXVECTOR1_U;


// 0x4008054C register ------------------------------------
typedef struct {
    uint32_t                           RXVECTOR2                          :32;
}   MAC_RXVECTOR2;

typedef union {
    uint32_t                           w;
    MAC_RXVECTOR2                      b;
}   MAC_RXVECTOR2_U;


// 0x40080550 register ------------------------------------
typedef struct {
    uint32_t                           RXINFO0                            :32;
}   MAC_RXINFO0;

typedef union {
    uint32_t                           w;
    MAC_RXINFO0                        b;
}   MAC_RXINFO0_U;


// 0x40080554 register ------------------------------------
typedef struct {
    uint32_t                           RXINFO1                            :32;
}   MAC_RXINFO1;

typedef union {
    uint32_t                           w;
    MAC_RXINFO1                        b;
}   MAC_RXINFO1_U;


// 0x40080558 register ------------------------------------
typedef struct {
    uint32_t                           RXINFO2                            :32;
}   MAC_RXINFO2;

typedef union {
    uint32_t                           w;
    MAC_RXINFO2                        b;
}   MAC_RXINFO2_U;


// 0x4008055C register ------------------------------------
typedef struct {
    uint32_t                           RXINFO3                            :32;
}   MAC_RXINFO3;

typedef union {
    uint32_t                           w;
    MAC_RXINFO3                        b;
}   MAC_RXINFO3_U;


// 0x40080560 register ------------------------------------
typedef struct {
    uint32_t                           RXHEADER0                          :32;
}   MAC_RXHEADER0;

typedef union {
    uint32_t                           w;
    MAC_RXHEADER0                      b;
}   MAC_RXHEADER0_U;


// 0x40080564 register ------------------------------------
typedef struct {
    uint32_t                           RXHEADER1                          :32;
}   MAC_RXHEADER1;

typedef union {
    uint32_t                           w;
    MAC_RXHEADER1                      b;
}   MAC_RXHEADER1_U;


// 0x40080568 register ------------------------------------
typedef struct {
    uint32_t                           RXHEADER2                          :32;
}   MAC_RXHEADER2;

typedef union {
    uint32_t                           w;
    MAC_RXHEADER2                      b;
}   MAC_RXHEADER2_U;


// 0x4008056C register ------------------------------------
typedef struct {
    uint32_t                           RXHEADER3                          :32;
}   MAC_RXHEADER3;

typedef union {
    uint32_t                           w;
    MAC_RXHEADER3                      b;
}   MAC_RXHEADER3_U;


// 0x40080570 register ------------------------------------
typedef struct {
    uint32_t                           RXHEADER4                          :32;
}   MAC_RXHEADER4;

typedef union {
    uint32_t                           w;
    MAC_RXHEADER4                      b;
}   MAC_RXHEADER4_U;


// 0x40080574 register ------------------------------------
typedef struct {
    uint32_t                           RXHEADER5                          :32;
}   MAC_RXHEADER5;

typedef union {
    uint32_t                           w;
    MAC_RXHEADER5                      b;
}   MAC_RXHEADER5_U;


// 0x40080578 register ------------------------------------
typedef struct {
    uint32_t                           RXHEADER6                          :32;
}   MAC_RXHEADER6;

typedef union {
    uint32_t                           w;
    MAC_RXHEADER6                      b;
}   MAC_RXHEADER6_U;


// 0x4008057C register ------------------------------------
typedef struct {
    uint32_t                           RXHEADER7                          :32;
}   MAC_RXHEADER7;

typedef union {
    uint32_t                           w;
    MAC_RXHEADER7                      b;
}   MAC_RXHEADER7_U;


// 0x40080580 register ------------------------------------
typedef struct {
    uint32_t                           RXHEADER8                          :32;
}   MAC_RXHEADER8;

typedef union {
    uint32_t                           w;
    MAC_RXHEADER8                      b;
}   MAC_RXHEADER8_U;


// 0x40080584 register ------------------------------------
typedef struct {
    uint32_t                           AMPDU_BITMAP                       :32;
}   MAC_AMPDU_BITMAP;

typedef union {
    uint32_t                           w;
    MAC_AMPDU_BITMAP                   b;
}   MAC_AMPDU_BITMAP_U;


// 0x40080588 register ------------------------------------
typedef struct {
    uint32_t                           KEY_CMD_RESULT_EN                  :1 ;
    uint32_t                           reserved0                          :31;
}   MAC_KEY_CMD_RESULT_EN;

typedef union {
    uint32_t                           w;
    MAC_KEY_CMD_RESULT_EN              b;
}   MAC_KEY_CMD_RESULT_EN_U;


// 0x4008058C register ------------------------------------
typedef struct {
    uint32_t                           ADDRESS                            :3 ;
    uint32_t                           reserved0                          :17;
    uint32_t                           RESULT                             :8 ;
    uint32_t                           COMMAND                            :4 ;
}   MAC_KEY_CMD_RESULT;

typedef union {
    uint32_t                           w;
    MAC_KEY_CMD_RESULT                 b;
}   MAC_KEY_CMD_RESULT_U;


// 0x40080590 register ------------------------------------
typedef struct {
    uint32_t                           MIC_FAIL                           :1 ;
    uint32_t                           reserved0                          :31;
}   MAC_SEC_REG_MIC_CHECK_FAIL;

typedef union {
    uint32_t                           w;
    MAC_SEC_REG_MIC_CHECK_FAIL         b;
}   MAC_SEC_REG_MIC_CHECK_FAIL_U;


// 0x40080594 register ------------------------------------
typedef struct {
    uint32_t                           SEC_KEY_FLAG                       :32;
}   MAC_SEC_KEY_FLAG;

typedef union {
    uint32_t                           w;
    MAC_SEC_KEY_FLAG                   b;
}   MAC_SEC_KEY_FLAG_U;


// 0x40080598 register ------------------------------------
typedef struct {
    uint32_t                           SEC_MIC_VALUE_RX_FAILED_0          :32;
}   MAC_SEC_MIC_VALUE_RX_FAILED_0;

typedef union {
    uint32_t                           w;
    MAC_SEC_MIC_VALUE_RX_FAILED_0      b;
}   MAC_SEC_MIC_VALUE_RX_FAILED_0_U;


// 0x4008059C register ------------------------------------
typedef struct {
    uint32_t                           SEC_MIC_VALUE_RX_FAILED_1          :32;
}   MAC_SEC_MIC_VALUE_RX_FAILED_1;

typedef union {
    uint32_t                           w;
    MAC_SEC_MIC_VALUE_RX_FAILED_1      b;
}   MAC_SEC_MIC_VALUE_RX_FAILED_1_U;


// 0x400805A0 register ------------------------------------
typedef struct {
    uint32_t                           TX_INDIR_REG_DATA                  :32;
}   MAC_TX_INDIR_REG_DATA;

typedef union {
    uint32_t                           w;
    MAC_TX_INDIR_REG_DATA              b;
}   MAC_TX_INDIR_REG_DATA_U;


// 0x400805A4 register ------------------------------------
typedef struct {
    uint32_t                           RX_INDIR_REG_DATA                  :32;
}   MAC_RX_INDIR_REG_DATA;

typedef union {
    uint32_t                           w;
    MAC_RX_INDIR_REG_DATA              b;
}   MAC_RX_INDIR_REG_DATA_U;


// 0x400805A8 register ------------------------------------
typedef struct {
    uint32_t                           SEC_INDIR_REG_DATA                 :32;
}   MAC_SEC_INDIR_REG_DATA;

typedef union {
    uint32_t                           w;
    MAC_SEC_INDIR_REG_DATA             b;
}   MAC_SEC_INDIR_REG_DATA_U;


// 0x400805AC register ------------------------------------
typedef struct {
    uint32_t                           DMA_INDIR_REG_DATA                 :32;
}   MAC_DMA_INDIR_REG_DATA;

typedef union {
    uint32_t                           w;
    MAC_DMA_INDIR_REG_DATA             b;
}   MAC_DMA_INDIR_REG_DATA_U;


// 0x400805B0 register ------------------------------------
typedef struct {
    uint32_t                           IRQ_INDIR_REG_DATA                 :32;
}   MAC_IRQ_INDIR_REG_DATA;

typedef union {
    uint32_t                           w;
    MAC_IRQ_INDIR_REG_DATA             b;
}   MAC_IRQ_INDIR_REG_DATA_U;


// 0x400805B4 register ------------------------------------
typedef struct {
    uint32_t                           TSF_0_LOWER_READONLY               :32;
}   MAC_TSF_0_LOWER_READONLY;

typedef union {
    uint32_t                           w;
    MAC_TSF_0_LOWER_READONLY           b;
}   MAC_TSF_0_LOWER_READONLY_U;


// 0x400805B8 register ------------------------------------
typedef struct {
    uint32_t                           TSF_0_UPPER_READONLY               :32;
}   MAC_TSF_0_UPPER_READONLY;

typedef union {
    uint32_t                           w;
    MAC_TSF_0_UPPER_READONLY           b;
}   MAC_TSF_0_UPPER_READONLY_U;


// 0x400805BC register ------------------------------------
typedef struct {
    uint32_t                           TSF_1_LOWER_READONLY               :32;
}   MAC_TSF_1_LOWER_READONLY;

typedef union {
    uint32_t                           w;
    MAC_TSF_1_LOWER_READONLY           b;
}   MAC_TSF_1_LOWER_READONLY_U;


// 0x400805C0 register ------------------------------------
typedef struct {
    uint32_t                           TSF_1_UPPER_READONLY               :32;
}   MAC_TSF_1_UPPER_READONLY;

typedef union {
    uint32_t                           w;
    MAC_TSF_1_UPPER_READONLY           b;
}   MAC_TSF_1_UPPER_READONLY_U;


// 0x400805C4 register ------------------------------------
typedef struct {
    uint32_t                           IRQ_SRC_NOCLEAR0                   :32;
}   MAC_IRQ_SRC_NOCLEAR0;

typedef union {
    uint32_t                           w;
    MAC_IRQ_SRC_NOCLEAR0               b;
}   MAC_IRQ_SRC_NOCLEAR0_U;


// 0x400805C8 register ------------------------------------
typedef struct {
    uint32_t                           IRQ_SRC_NOCLEAR1                   :32;
}   MAC_IRQ_SRC_NOCLEAR1;

typedef union {
    uint32_t                           w;
    MAC_IRQ_SRC_NOCLEAR1               b;
}   MAC_IRQ_SRC_NOCLEAR1_U;


// 0x400805CC register ------------------------------------
typedef struct {
    uint32_t                           WIN_AC_BITMAP                      :11;
    uint32_t                           TX_DONE_BITMAP                     :11;
    uint32_t                           RX_DONE                            :1 ;
    uint32_t                           RX_DMA_DONE                        :1 ;
    uint32_t                           TX_RESPONSE_TIMEOUT                :1 ;
    uint32_t                           DMA_ERROR                          :1 ;
    uint32_t                           AHB_SEC_IRQ                        :1 ;
    uint32_t                           TBTT_IRQ_TSF0                      :1 ;
    uint32_t                           TSF0_ALARM                         :1 ;
    uint32_t                           RX_BUFFER_LOOKUP                   :1 ;
    uint32_t                           TBTT_IRQ_TSF1                      :1 ;
    uint32_t                           TSF1_ALARM                         :1 ;
}   MAC_IRQ_SRC0;

typedef union {
    uint32_t                           w;
    MAC_IRQ_SRC0                       b;
}   MAC_IRQ_SRC0_U;


// 0x400805D0 register ------------------------------------
typedef struct {
    uint32_t                           SUPPRESS_END                       :1 ;
    uint32_t                           MYRAW_END                          :1 ;
    uint32_t                           RX_PAGING                          :1 ;
    uint32_t                           reserved0                          :29;
}   MAC_IRQ_SRC1;

typedef union {
    uint32_t                           w;
    MAC_IRQ_SRC1                       b;
}   MAC_IRQ_SRC1_U;


// 0x400805D4 register ------------------------------------
typedef struct {
    uint32_t                           RX_NDP_PAGING                      :32;
}   MAC_RX_NDP_PAGING;

typedef union {
    uint32_t                           w;
    MAC_RX_NDP_PAGING                  b;
}   MAC_RX_NDP_PAGING_U;


// 0x40080700 register ------------------------------------
typedef struct {
    uint32_t                           BUS_CLK_MODE                       :1 ;
    uint32_t                           reserved0                          :31;
}   MAC_BUS_CLK_MODE;

typedef union {
    uint32_t                           w;
    MAC_BUS_CLK_MODE                   b;
}   MAC_BUS_CLK_MODE_U;


// 0x40080704 register ------------------------------------
typedef struct {
    uint32_t                           TICK_CNT_ENABLE                    :1 ;
    uint32_t                           TICK_CNT_RST                       :1 ;
    uint32_t                           reserved0                          :30;
}   MAC_TICK_CNT_MODE;

typedef union {
    uint32_t                           w;
    MAC_TICK_CNT_MODE                  b;
}   MAC_TICK_CNT_MODE_U;


// 0x40080708 register ------------------------------------
typedef struct {
    uint32_t                           TICK_CNT_CAPT                      :32;
}   MAC_TICK_CNT_CAPT;

typedef union {
    uint32_t                           w;
    MAC_TICK_CNT_CAPT                  b;
}   MAC_TICK_CNT_CAPT_U;


// 0x40080800 register ------------------------------------
typedef struct {
    uint32_t                           TX_RF_PARAM_LOWER_0                :32;
}   MAC_TX_RF_PARAM_LOWER_0;

typedef union {
    uint32_t                           w;
    MAC_TX_RF_PARAM_LOWER_0            b;
}   MAC_TX_RF_PARAM_LOWER_0_U;


// 0x40080804 register ------------------------------------
typedef struct {
    uint32_t                           TX_RF_PARAM_MIDDLE_0               :32;
}   MAC_TX_RF_PARAM_MIDDLE_0;

typedef union {
    uint32_t                           w;
    MAC_TX_RF_PARAM_MIDDLE_0           b;
}   MAC_TX_RF_PARAM_MIDDLE_0_U;


// 0x40080808 register ------------------------------------
typedef struct {
    uint32_t                           TX_RF_PARAM_UPPER_0                :22;
    uint32_t                           reserved0                          :10;
}   MAC_TX_RF_PARAM_UPPER_0;

typedef union {
    uint32_t                           w;
    MAC_TX_RF_PARAM_UPPER_0            b;
}   MAC_TX_RF_PARAM_UPPER_0_U;


// 0x4008080C register ------------------------------------
typedef struct {
    uint32_t                           TX_DIG_GAIN_0                      :16;
    uint32_t                           reserved0                          :16;
}   MAC_TX_DIG_GAIN_0;

typedef union {
    uint32_t                           w;
    MAC_TX_DIG_GAIN_0                  b;
}   MAC_TX_DIG_GAIN_0_U;


// 0x40080810 register ------------------------------------
typedef struct {
    uint32_t                           DPD_INDEX_0                        :8 ;
    uint32_t                           reserved0                          :8 ;
    uint32_t                           TX_ANAGAIN_0                       :10;
    uint32_t                           reserved1                          :6 ;
}   MAC_TX_ANAGAIN_DPD_0;

typedef union {
    uint32_t                           w;
    MAC_TX_ANAGAIN_DPD_0               b;
}   MAC_TX_ANAGAIN_DPD_0_U;


// 0x40080814 register ------------------------------------
typedef struct {
    uint32_t                           TX_RF_PARAM_LOWER_1                :32;
}   MAC_TX_RF_PARAM_LOWER_1;

typedef union {
    uint32_t                           w;
    MAC_TX_RF_PARAM_LOWER_1            b;
}   MAC_TX_RF_PARAM_LOWER_1_U;


// 0x40080818 register ------------------------------------
typedef struct {
    uint32_t                           TX_RF_PARAM_MIDDLE_1               :32;
}   MAC_TX_RF_PARAM_MIDDLE_1;

typedef union {
    uint32_t                           w;
    MAC_TX_RF_PARAM_MIDDLE_1           b;
}   MAC_TX_RF_PARAM_MIDDLE_1_U;


// 0x4008081C register ------------------------------------
typedef struct {
    uint32_t                           TX_RF_PARAM_UPPER_1                :22;
    uint32_t                           reserved0                          :10;
}   MAC_TX_RF_PARAM_UPPER_1;

typedef union {
    uint32_t                           w;
    MAC_TX_RF_PARAM_UPPER_1            b;
}   MAC_TX_RF_PARAM_UPPER_1_U;


// 0x40080820 register ------------------------------------
typedef struct {
    uint32_t                           TX_DIG_GAIN_1                      :16;
    uint32_t                           reserved0                          :16;
}   MAC_TX_DIG_GAIN_1;

typedef union {
    uint32_t                           w;
    MAC_TX_DIG_GAIN_1                  b;
}   MAC_TX_DIG_GAIN_1_U;


// 0x40080824 register ------------------------------------
typedef struct {
    uint32_t                           DPD_INDEX_1                        :8 ;
    uint32_t                           reserved0                          :8 ;
    uint32_t                           TX_ANAGAIN_1                       :10;
    uint32_t                           reserved1                          :6 ;
}   MAC_TX_ANAGAIN_DPD_1;

typedef union {
    uint32_t                           w;
    MAC_TX_ANAGAIN_DPD_1               b;
}   MAC_TX_ANAGAIN_DPD_1_U;


// 0x40080828 register ------------------------------------
typedef struct {
    uint32_t                           TX_RF_PARAM_LOWER_2                :32;
}   MAC_TX_RF_PARAM_LOWER_2;

typedef union {
    uint32_t                           w;
    MAC_TX_RF_PARAM_LOWER_2            b;
}   MAC_TX_RF_PARAM_LOWER_2_U;


// 0x4008082C register ------------------------------------
typedef struct {
    uint32_t                           TX_RF_PARAM_MIDDLE_2               :32;
}   MAC_TX_RF_PARAM_MIDDLE_2;

typedef union {
    uint32_t                           w;
    MAC_TX_RF_PARAM_MIDDLE_2           b;
}   MAC_TX_RF_PARAM_MIDDLE_2_U;


// 0x40080830 register ------------------------------------
typedef struct {
    uint32_t                           TX_RF_PARAM_UPPER_2                :22;
    uint32_t                           reserved0                          :10;
}   MAC_TX_RF_PARAM_UPPER_2;

typedef union {
    uint32_t                           w;
    MAC_TX_RF_PARAM_UPPER_2            b;
}   MAC_TX_RF_PARAM_UPPER_2_U;


// 0x40080834 register ------------------------------------
typedef struct {
    uint32_t                           TX_DIG_GAIN_2                      :16;
    uint32_t                           reserved0                          :16;
}   MAC_TX_DIG_GAIN_2;

typedef union {
    uint32_t                           w;
    MAC_TX_DIG_GAIN_2                  b;
}   MAC_TX_DIG_GAIN_2_U;


// 0x40080838 register ------------------------------------
typedef struct {
    uint32_t                           DPD_INDEX_2                        :8 ;
    uint32_t                           reserved0                          :8 ;
    uint32_t                           TX_ANAGAIN_2                       :10;
    uint32_t                           reserved1                          :6 ;
}   MAC_TX_ANAGAIN_DPD_2;

typedef union {
    uint32_t                           w;
    MAC_TX_ANAGAIN_DPD_2               b;
}   MAC_TX_ANAGAIN_DPD_2_U;


// 0x4008083C register ------------------------------------
typedef struct {
    uint32_t                           TX_RF_PARAM_LOWER_3                :32;
}   MAC_TX_RF_PARAM_LOWER_3;

typedef union {
    uint32_t                           w;
    MAC_TX_RF_PARAM_LOWER_3            b;
}   MAC_TX_RF_PARAM_LOWER_3_U;


// 0x40080840 register ------------------------------------
typedef struct {
    uint32_t                           TX_RF_PARAM_MIDDLE_3               :32;
}   MAC_TX_RF_PARAM_MIDDLE_3;

typedef union {
    uint32_t                           w;
    MAC_TX_RF_PARAM_MIDDLE_3           b;
}   MAC_TX_RF_PARAM_MIDDLE_3_U;


// 0x40080844 register ------------------------------------
typedef struct {
    uint32_t                           TX_RF_PARAM_UPPER_3                :22;
    uint32_t                           reserved0                          :10;
}   MAC_TX_RF_PARAM_UPPER_3;

typedef union {
    uint32_t                           w;
    MAC_TX_RF_PARAM_UPPER_3            b;
}   MAC_TX_RF_PARAM_UPPER_3_U;


// 0x40080848 register ------------------------------------
typedef struct {
    uint32_t                           TX_DIG_GAIN_3                      :16;
    uint32_t                           reserved0                          :16;
}   MAC_TX_DIG_GAIN_3;

typedef union {
    uint32_t                           w;
    MAC_TX_DIG_GAIN_3                  b;
}   MAC_TX_DIG_GAIN_3_U;


// 0x4008084C register ------------------------------------
typedef struct {
    uint32_t                           DPD_INDEX_3                        :8 ;
    uint32_t                           reserved0                          :8 ;
    uint32_t                           TX_ANAGAIN_3                       :10;
    uint32_t                           reserved1                          :6 ;
}   MAC_TX_ANAGAIN_DPD_3;

typedef union {
    uint32_t                           w;
    MAC_TX_ANAGAIN_DPD_3               b;
}   MAC_TX_ANAGAIN_DPD_3_U;


// 0x40080850 register ------------------------------------
typedef struct {
    uint32_t                           TX_RF_PARAM_LOWER_4                :32;
}   MAC_TX_RF_PARAM_LOWER_4;

typedef union {
    uint32_t                           w;
    MAC_TX_RF_PARAM_LOWER_4            b;
}   MAC_TX_RF_PARAM_LOWER_4_U;


// 0x40080854 register ------------------------------------
typedef struct {
    uint32_t                           TX_RF_PARAM_MIDDLE_4               :32;
}   MAC_TX_RF_PARAM_MIDDLE_4;

typedef union {
    uint32_t                           w;
    MAC_TX_RF_PARAM_MIDDLE_4           b;
}   MAC_TX_RF_PARAM_MIDDLE_4_U;


// 0x40080858 register ------------------------------------
typedef struct {
    uint32_t                           TX_RF_PARAM_UPPER_4                :22;
    uint32_t                           reserved0                          :10;
}   MAC_TX_RF_PARAM_UPPER_4;

typedef union {
    uint32_t                           w;
    MAC_TX_RF_PARAM_UPPER_4            b;
}   MAC_TX_RF_PARAM_UPPER_4_U;


// 0x4008085C register ------------------------------------
typedef struct {
    uint32_t                           TX_DIG_GAIN_4                      :16;
    uint32_t                           reserved0                          :16;
}   MAC_TX_DIG_GAIN_4;

typedef union {
    uint32_t                           w;
    MAC_TX_DIG_GAIN_4                  b;
}   MAC_TX_DIG_GAIN_4_U;


// 0x40080860 register ------------------------------------
typedef struct {
    uint32_t                           DPD_INDEX_4                        :8 ;
    uint32_t                           reserved0                          :8 ;
    uint32_t                           TX_ANAGAIN_4                       :10;
    uint32_t                           reserved1                          :6 ;
}   MAC_TX_ANAGAIN_DPD_4;

typedef union {
    uint32_t                           w;
    MAC_TX_ANAGAIN_DPD_4               b;
}   MAC_TX_ANAGAIN_DPD_4_U;


// 0x40080864 register ------------------------------------
typedef struct {
    uint32_t                           TX_RF_PARAM_LOWER_5                :32;
}   MAC_TX_RF_PARAM_LOWER_5;

typedef union {
    uint32_t                           w;
    MAC_TX_RF_PARAM_LOWER_5            b;
}   MAC_TX_RF_PARAM_LOWER_5_U;


// 0x40080868 register ------------------------------------
typedef struct {
    uint32_t                           TX_RF_PARAM_MIDDLE_5               :32;
}   MAC_TX_RF_PARAM_MIDDLE_5;

typedef union {
    uint32_t                           w;
    MAC_TX_RF_PARAM_MIDDLE_5           b;
}   MAC_TX_RF_PARAM_MIDDLE_5_U;


// 0x4008086C register ------------------------------------
typedef struct {
    uint32_t                           TX_RF_PARAM_UPPER_5                :22;
    uint32_t                           reserved0                          :10;
}   MAC_TX_RF_PARAM_UPPER_5;

typedef union {
    uint32_t                           w;
    MAC_TX_RF_PARAM_UPPER_5            b;
}   MAC_TX_RF_PARAM_UPPER_5_U;


// 0x40080870 register ------------------------------------
typedef struct {
    uint32_t                           TX_DIG_GAIN_5                      :16;
    uint32_t                           reserved0                          :16;
}   MAC_TX_DIG_GAIN_5;

typedef union {
    uint32_t                           w;
    MAC_TX_DIG_GAIN_5                  b;
}   MAC_TX_DIG_GAIN_5_U;


// 0x40080874 register ------------------------------------
typedef struct {
    uint32_t                           DPD_INDEX_5                        :8 ;
    uint32_t                           reserved0                          :8 ;
    uint32_t                           TX_ANAGAIN_5                       :10;
    uint32_t                           reserved1                          :6 ;
}   MAC_TX_ANAGAIN_DPD_5;

typedef union {
    uint32_t                           w;
    MAC_TX_ANAGAIN_DPD_5               b;
}   MAC_TX_ANAGAIN_DPD_5_U;


// 0x40080878 register ------------------------------------
typedef struct {
    uint32_t                           TX_RF_PARAM_LOWER_6                :32;
}   MAC_TX_RF_PARAM_LOWER_6;

typedef union {
    uint32_t                           w;
    MAC_TX_RF_PARAM_LOWER_6            b;
}   MAC_TX_RF_PARAM_LOWER_6_U;


// 0x4008087C register ------------------------------------
typedef struct {
    uint32_t                           TX_RF_PARAM_MIDDLE_6               :32;
}   MAC_TX_RF_PARAM_MIDDLE_6;

typedef union {
    uint32_t                           w;
    MAC_TX_RF_PARAM_MIDDLE_6           b;
}   MAC_TX_RF_PARAM_MIDDLE_6_U;


// 0x40080880 register ------------------------------------
typedef struct {
    uint32_t                           TX_RF_PARAM_UPPER_6                :22;
    uint32_t                           reserved0                          :10;
}   MAC_TX_RF_PARAM_UPPER_6;

typedef union {
    uint32_t                           w;
    MAC_TX_RF_PARAM_UPPER_6            b;
}   MAC_TX_RF_PARAM_UPPER_6_U;


// 0x40080884 register ------------------------------------
typedef struct {
    uint32_t                           TX_DIG_GAIN_6                      :16;
    uint32_t                           reserved0                          :16;
}   MAC_TX_DIG_GAIN_6;

typedef union {
    uint32_t                           w;
    MAC_TX_DIG_GAIN_6                  b;
}   MAC_TX_DIG_GAIN_6_U;


// 0x40080888 register ------------------------------------
typedef struct {
    uint32_t                           DPD_INDEX_6                        :8 ;
    uint32_t                           reserved0                          :8 ;
    uint32_t                           TX_ANAGAIN_6                       :10;
    uint32_t                           reserved1                          :6 ;
}   MAC_TX_ANAGAIN_DPD_6;

typedef union {
    uint32_t                           w;
    MAC_TX_ANAGAIN_DPD_6               b;
}   MAC_TX_ANAGAIN_DPD_6_U;


// 0x4008088C register ------------------------------------
typedef struct {
    uint32_t                           TX_RF_PARAM_LOWER_7                :32;
}   MAC_TX_RF_PARAM_LOWER_7;

typedef union {
    uint32_t                           w;
    MAC_TX_RF_PARAM_LOWER_7            b;
}   MAC_TX_RF_PARAM_LOWER_7_U;


// 0x40080890 register ------------------------------------
typedef struct {
    uint32_t                           TX_RF_PARAM_MIDDLE_7               :32;
}   MAC_TX_RF_PARAM_MIDDLE_7;

typedef union {
    uint32_t                           w;
    MAC_TX_RF_PARAM_MIDDLE_7           b;
}   MAC_TX_RF_PARAM_MIDDLE_7_U;


// 0x40080894 register ------------------------------------
typedef struct {
    uint32_t                           TX_RF_PARAM_UPPER_7                :22;
    uint32_t                           reserved0                          :10;
}   MAC_TX_RF_PARAM_UPPER_7;

typedef union {
    uint32_t                           w;
    MAC_TX_RF_PARAM_UPPER_7            b;
}   MAC_TX_RF_PARAM_UPPER_7_U;


// 0x40080898 register ------------------------------------
typedef struct {
    uint32_t                           TX_DIG_GAIN_7                      :16;
    uint32_t                           reserved0                          :16;
}   MAC_TX_DIG_GAIN_7;

typedef union {
    uint32_t                           w;
    MAC_TX_DIG_GAIN_7                  b;
}   MAC_TX_DIG_GAIN_7_U;


// 0x4008089C register ------------------------------------
typedef struct {
    uint32_t                           DPD_INDEX_7                        :8 ;
    uint32_t                           reserved0                          :8 ;
    uint32_t                           TX_ANAGAIN_7                       :10;
    uint32_t                           reserved1                          :6 ;
}   MAC_TX_ANAGAIN_DPD_7;

typedef union {
    uint32_t                           w;
    MAC_TX_ANAGAIN_DPD_7               b;
}   MAC_TX_ANAGAIN_DPD_7_U;


// 0x400808A0 register ------------------------------------
typedef struct {
    uint32_t                           TX_RF_PARAM_LOWER_8                :32;
}   MAC_TX_RF_PARAM_LOWER_8;

typedef union {
    uint32_t                           w;
    MAC_TX_RF_PARAM_LOWER_8            b;
}   MAC_TX_RF_PARAM_LOWER_8_U;


// 0x400808A4 register ------------------------------------
typedef struct {
    uint32_t                           TX_RF_PARAM_MIDDLE_8               :32;
}   MAC_TX_RF_PARAM_MIDDLE_8;

typedef union {
    uint32_t                           w;
    MAC_TX_RF_PARAM_MIDDLE_8           b;
}   MAC_TX_RF_PARAM_MIDDLE_8_U;


// 0x400808A8 register ------------------------------------
typedef struct {
    uint32_t                           TX_RF_PARAM_UPPER_8                :22;
    uint32_t                           reserved0                          :10;
}   MAC_TX_RF_PARAM_UPPER_8;

typedef union {
    uint32_t                           w;
    MAC_TX_RF_PARAM_UPPER_8            b;
}   MAC_TX_RF_PARAM_UPPER_8_U;


// 0x400808AC register ------------------------------------
typedef struct {
    uint32_t                           TX_DIG_GAIN_8                      :16;
    uint32_t                           reserved0                          :16;
}   MAC_TX_DIG_GAIN_8;

typedef union {
    uint32_t                           w;
    MAC_TX_DIG_GAIN_8                  b;
}   MAC_TX_DIG_GAIN_8_U;


// 0x400808B0 register ------------------------------------
typedef struct {
    uint32_t                           DPD_INDEX_8                        :8 ;
    uint32_t                           reserved0                          :8 ;
    uint32_t                           TX_ANAGAIN_8                       :10;
    uint32_t                           reserved1                          :6 ;
}   MAC_TX_ANAGAIN_DPD_8;

typedef union {
    uint32_t                           w;
    MAC_TX_ANAGAIN_DPD_8               b;
}   MAC_TX_ANAGAIN_DPD_8_U;


// 0x400808B4 register ------------------------------------
typedef struct {
    uint32_t                           TX_RF_PARAM_LOWER_9                :32;
}   MAC_TX_RF_PARAM_LOWER_9;

typedef union {
    uint32_t                           w;
    MAC_TX_RF_PARAM_LOWER_9            b;
}   MAC_TX_RF_PARAM_LOWER_9_U;


// 0x400808B8 register ------------------------------------
typedef struct {
    uint32_t                           TX_RF_PARAM_MIDDLE_9               :32;
}   MAC_TX_RF_PARAM_MIDDLE_9;

typedef union {
    uint32_t                           w;
    MAC_TX_RF_PARAM_MIDDLE_9           b;
}   MAC_TX_RF_PARAM_MIDDLE_9_U;


// 0x400808BC register ------------------------------------
typedef struct {
    uint32_t                           TX_RF_PARAM_UPPER_9                :22;
    uint32_t                           reserved0                          :10;
}   MAC_TX_RF_PARAM_UPPER_9;

typedef union {
    uint32_t                           w;
    MAC_TX_RF_PARAM_UPPER_9            b;
}   MAC_TX_RF_PARAM_UPPER_9_U;


// 0x400808C0 register ------------------------------------
typedef struct {
    uint32_t                           TX_DIG_GAIN_9                      :16;
    uint32_t                           reserved0                          :16;
}   MAC_TX_DIG_GAIN_9;

typedef union {
    uint32_t                           w;
    MAC_TX_DIG_GAIN_9                  b;
}   MAC_TX_DIG_GAIN_9_U;


// 0x400808C4 register ------------------------------------
typedef struct {
    uint32_t                           DPD_INDEX_9                        :8 ;
    uint32_t                           reserved0                          :8 ;
    uint32_t                           TX_ANAGAIN_9                       :10;
    uint32_t                           reserved1                          :6 ;
}   MAC_TX_ANAGAIN_DPD_9;

typedef union {
    uint32_t                           w;
    MAC_TX_ANAGAIN_DPD_9               b;
}   MAC_TX_ANAGAIN_DPD_9_U;


// 0x400808C8 register ------------------------------------
typedef struct {
    uint32_t                           TX_RF_PARAM_LOWER_10               :32;
}   MAC_TX_RF_PARAM_LOWER_10;

typedef union {
    uint32_t                           w;
    MAC_TX_RF_PARAM_LOWER_10           b;
}   MAC_TX_RF_PARAM_LOWER_10_U;


// 0x400808CC register ------------------------------------
typedef struct {
    uint32_t                           TX_RF_PARAM_MIDDLE_10              :32;
}   MAC_TX_RF_PARAM_MIDDLE_10;

typedef union {
    uint32_t                           w;
    MAC_TX_RF_PARAM_MIDDLE_10          b;
}   MAC_TX_RF_PARAM_MIDDLE_10_U;


// 0x400808D0 register ------------------------------------
typedef struct {
    uint32_t                           TX_RF_PARAM_UPPER_10               :22;
    uint32_t                           reserved0                          :10;
}   MAC_TX_RF_PARAM_UPPER_10;

typedef union {
    uint32_t                           w;
    MAC_TX_RF_PARAM_UPPER_10           b;
}   MAC_TX_RF_PARAM_UPPER_10_U;


// 0x400808D4 register ------------------------------------
typedef struct {
    uint32_t                           TX_DIG_GAIN_10                     :16;
    uint32_t                           reserved0                          :16;
}   MAC_TX_DIG_GAIN_10;

typedef union {
    uint32_t                           w;
    MAC_TX_DIG_GAIN_10                 b;
}   MAC_TX_DIG_GAIN_10_U;


// 0x400808D8 register ------------------------------------
typedef struct {
    uint32_t                           DPD_INDEX_10                       :8 ;
    uint32_t                           reserved0                          :8 ;
    uint32_t                           TX_ANAGAIN_10                      :10;
    uint32_t                           reserved1                          :6 ;
}   MAC_TX_ANAGAIN_DPD_10;

typedef union {
    uint32_t                           w;
    MAC_TX_ANAGAIN_DPD_10              b;
}   MAC_TX_ANAGAIN_DPD_10_U;


// 0x400808DC register ------------------------------------
typedef struct {
    uint32_t                           TX_RF_PARAM_LOWER_CF               :32;
}   MAC_TX_RF_PARAM_LOWER_CF;

typedef union {
    uint32_t                           w;
    MAC_TX_RF_PARAM_LOWER_CF           b;
}   MAC_TX_RF_PARAM_LOWER_CF_U;


// 0x400808E0 register ------------------------------------
typedef struct {
    uint32_t                           TX_RF_PARAM_MIDDLE_CF              :32;
}   MAC_TX_RF_PARAM_MIDDLE_CF;

typedef union {
    uint32_t                           w;
    MAC_TX_RF_PARAM_MIDDLE_CF          b;
}   MAC_TX_RF_PARAM_MIDDLE_CF_U;


// 0x400808E4 register ------------------------------------
typedef struct {
    uint32_t                           TX_RF_PARAM_UPPER_CF               :22;
    uint32_t                           reserved0                          :10;
}   MAC_TX_RF_PARAM_UPPER_CF;

typedef union {
    uint32_t                           w;
    MAC_TX_RF_PARAM_UPPER_CF           b;
}   MAC_TX_RF_PARAM_UPPER_CF_U;


// 0x400808E8 register ------------------------------------
typedef struct {
    uint32_t                           TX_DIG_GAIN_CF                     :16;
    uint32_t                           reserved0                          :16;
}   MAC_TX_DIG_GAIN_CF;

typedef union {
    uint32_t                           w;
    MAC_TX_DIG_GAIN_CF                 b;
}   MAC_TX_DIG_GAIN_CF_U;


// 0x400808EC register ------------------------------------
typedef struct {
    uint32_t                           DPD_INDEX_CF                       :8 ;
    uint32_t                           reserved0                          :8 ;
    uint32_t                           TX_ANAGAIN_CF                      :10;
    uint32_t                           reserved1                          :6 ;
}   MAC_TX_ANAGAIN_DPD_CF;

typedef union {
    uint32_t                           w;
    MAC_TX_ANAGAIN_DPD_CF              b;
}   MAC_TX_ANAGAIN_DPD_CF_U;


//---------------------------------------------------------
// MAC Register Map
//---------------------------------------------------------
typedef struct {
    volatile MAC_RST_SW_U                              RST_SW                            ; // 0x000
    volatile MAC_CONFIG_U                              CONFIG                            ; // 0x004
    volatile MAC_SIFS_DURATION_U                       SIFS_DURATION                     ; // 0x008
    volatile MAC_SLOT_DURATION_U                       SLOT_DURATION                     ; // 0x00c
    volatile MAC_TXPWR_POST_DELAY_CLOCK_U              TXPWR_POST_DELAY_CLOCK            ; // 0x010
    volatile MAC_CRASH_U                               CRASH                             ; // 0x014
    volatile MAC_TX_RESPONSE_CONTROL_U                 TX_RESPONSE_CONTROL               ; // 0x018
    volatile MAC_OPERATION_BAND_U                      OPERATION_BAND                    ; // 0x01c
    volatile MAC_TXPPDU_DELAY_CLOCK_U                  TXPPDU_DELAY_CLOCK                ; // 0x020
    volatile MAC_READY_BEFORE_TXPPDU_CLOCK_U           READY_BEFORE_TXPPDU_CLOCK         ; // 0x024
    volatile MAC_READY_TO_TXPOWER_CLOCK_U              READY_TO_TXPOWER_CLOCK            ; // 0x028
    volatile MAC_TXPOWER_TO_TXREQUEST_CLOCK_U          TXPOWER_TO_TXREQUEST_CLOCK        ; // 0x02c
    volatile MAC_RESPONSE_TIMEOUT_US_U                 RESPONSE_TIMEOUT_US               ; // 0x030
    volatile MAC_CONFIG_EXT_U                          CONFIG_EXT                        ; // 0x034
    volatile MAC_STA_FILTER_MODE_U                     STA_FILTER_MODE                   ; // 0x038
    volatile MAC_INTF_CFG_ACTIVE_BITMAP_U              INTF_CFG_ACTIVE_BITMAP            ; // 0x03c
    volatile MAC_SIFS_TIMEOUT_U                        SIFS_TIMEOUT                      ; // 0x040
    volatile MAC_STA_BSSID0_LOWER_U                    STA_BSSID0_LOWER                  ; // 0x044
    volatile MAC_STA_BSSID0_UPPER_U                    STA_BSSID0_UPPER                  ; // 0x048
    volatile MAC_STA_BSSID1_LOWER_U                    STA_BSSID1_LOWER                  ; // 0x04c
    volatile MAC_STA_BSSID1_UPPER_U                    STA_BSSID1_UPPER                  ; // 0x050
    volatile MAC_STA_BSSID2_LOWER_U                    STA_BSSID2_LOWER                  ; // 0x054
    volatile MAC_STA_BSSID2_UPPER_U                    STA_BSSID2_UPPER                  ; // 0x058
    volatile MAC_STA_BSSID3_LOWER_U                    STA_BSSID3_LOWER                  ; // 0x05c
    volatile MAC_STA_BSSID3_UPPER_U                    STA_BSSID3_UPPER                  ; // 0x060
    volatile MAC_MAC_ADDRESS0_LOWER_U                  MAC_ADDRESS0_LOWER                ; // 0x064
    volatile MAC_MAC_ADDRESS0_UPPER_U                  MAC_ADDRESS0_UPPER                ; // 0x068
    volatile MAC_MAC_ADDRESS1_LOWER_U                  MAC_ADDRESS1_LOWER                ; // 0x06c
    volatile MAC_MAC_ADDRESS1_UPPER_U                  MAC_ADDRESS1_UPPER                ; // 0x070
    volatile MAC_MAC_ADDRESS2_LOWER_U                  MAC_ADDRESS2_LOWER                ; // 0x074
    volatile MAC_MAC_ADDRESS2_UPPER_U                  MAC_ADDRESS2_UPPER                ; // 0x078
    volatile MAC_MAC_ADDRESS3_LOWER_U                  MAC_ADDRESS3_LOWER                ; // 0x07c
    volatile MAC_MAC_ADDRESS3_UPPER_U                  MAC_ADDRESS3_UPPER                ; // 0x080
    volatile MAC_STA_AID0_0_U                          STA_AID0_0                        ; // 0x084
    volatile MAC_STA_AID0_1_U                          STA_AID0_1                        ; // 0x088
    volatile MAC_STA_AID0_2_U                          STA_AID0_2                        ; // 0x08c
    volatile MAC_STA_AID1_0_U                          STA_AID1_0                        ; // 0x090
    volatile MAC_STA_AID1_1_U                          STA_AID1_1                        ; // 0x094
    volatile MAC_STA_AID1_2_U                          STA_AID1_2                        ; // 0x098
    volatile MAC_STA_AID2_0_U                          STA_AID2_0                        ; // 0x09c
    volatile MAC_STA_AID2_1_U                          STA_AID2_1                        ; // 0x0a0
    volatile MAC_STA_AID2_2_U                          STA_AID2_2                        ; // 0x0a4
    volatile MAC_STA_AID3_0_U                          STA_AID3_0                        ; // 0x0a8
    volatile MAC_STA_AID3_1_U                          STA_AID3_1                        ; // 0x0ac
    volatile MAC_STA_AID3_2_U                          STA_AID3_2                        ; // 0x0b0
    volatile MAC_COMPR_BSSID_U                         COMPR_BSSID                       ; // 0x0b4
    volatile MAC_DMA_BURST_U                           DMA_BURST                         ; // 0x0b8
    volatile MAC_DMA_READ_FIFO_ADJUST_U                DMA_READ_FIFO_ADJUST              ; // 0x0bc
    volatile MAC_CONCURRENT_CONFIG_BITMAP_U            CONCURRENT_CONFIG_BITMAP          ; // 0x0c0
    volatile MAC_TX_CONTROL_PARAMETER_U                TX_CONTROL_PARAMETER              ; // 0x0c4
    volatile MAC_RSP0_U                                RSP0                              ; // 0x0c8
    volatile MAC_RSP1_U                                RSP1                              ; // 0x0cc
    volatile MAC_RSP2_U                                RSP2                              ; // 0x0d0
    volatile MAC_RSP3_U                                RSP3                              ; // 0x0d4
    volatile MAC_RSP4_U                                RSP4                              ; // 0x0d8
    volatile MAC_RSP5_U                                RSP5                              ; // 0x0dc
    volatile MAC_RSP6_U                                RSP6                              ; // 0x0e0
    volatile MAC_RSP7_U                                RSP7                              ; // 0x0e4
    volatile MAC_RSP8_U                                RSP8                              ; // 0x0e8
    volatile MAC_RSP9_U                                RSP9                              ; // 0x0ec
    volatile MAC_RSP10_U                               RSP10                             ; // 0x0f0
    volatile MAC_RSP11_U                               RSP11                             ; // 0x0f4
    volatile MAC_RSP12_U                               RSP12                             ; // 0x0f8
    volatile MAC_RSP13_U                               RSP13                             ; // 0x0fc
    volatile MAC_RSP14_U                               RSP14                             ; // 0x100
    volatile MAC_RSP15_U                               RSP15                             ; // 0x104
    volatile MAC_RSP16_U                               RSP16                             ; // 0x108
    volatile MAC_RSP17_U                               RSP17                             ; // 0x10c
    volatile MAC_RSP18_U                               RSP18                             ; // 0x110
    volatile MAC_RSP19_U                               RSP19                             ; // 0x114
    volatile MAC_RSP20_U                               RSP20                             ; // 0x118
    volatile MAC_RSP21_U                               RSP21                             ; // 0x11c
    volatile MAC_RSP22_U                               RSP22                             ; // 0x120
    volatile MAC_RSP23_U                               RSP23                             ; // 0x124
    volatile MAC_RSP24_U                               RSP24                             ; // 0x128
    volatile MAC_RSP25_U                               RSP25                             ; // 0x12c
    volatile MAC_RSP26_U                               RSP26                             ; // 0x130
    volatile MAC_RSP27_U                               RSP27                             ; // 0x134
    volatile MAC_RSP28_U                               RSP28                             ; // 0x138
    volatile MAC_RSP29_U                               RSP29                             ; // 0x13c
    volatile MAC_RSP30_U                               RSP30                             ; // 0x140
    volatile MAC_RSP31_U                               RSP31                             ; // 0x144
    volatile MAC_RSP_CASE0_U                           RSP_CASE0                         ; // 0x148
    volatile MAC_RSP_CASE1_U                           RSP_CASE1                         ; // 0x14c
    volatile MAC_RSP_CASE2_U                           RSP_CASE2                         ; // 0x150
    volatile MAC_RSP_CASE3_U                           RSP_CASE3                         ; // 0x154
    volatile MAC_RSP_CASE4_U                           RSP_CASE4                         ; // 0x158
    volatile MAC_RSP_CASE5_U                           RSP_CASE5                         ; // 0x15c
    volatile MAC_RSP_CASE6_U                           RSP_CASE6                         ; // 0x160
    volatile MAC_RSP_CASE7_U                           RSP_CASE7                         ; // 0x164
    volatile MAC_RSP_CASE8_U                           RSP_CASE8                         ; // 0x168
    volatile MAC_RSP_CASE9_U                           RSP_CASE9                         ; // 0x16c
    volatile MAC_RSP_CASE10_U                          RSP_CASE10                        ; // 0x170
    volatile MAC_RSP_CASE11_U                          RSP_CASE11                        ; // 0x174
    volatile MAC_WAIT_MODE_WR_U                        WAIT_MODE_WR                      ; // 0x178
    volatile MAC_WAIT_MODE_RD_U                        WAIT_MODE_RD                      ; // 0x17c
    volatile MAC_TX_COMMAND_0_U                        TX_COMMAND_0                      ; // 0x180
    volatile MAC_TX_COMMAND_1_U                        TX_COMMAND_1                      ; // 0x184
    volatile MAC_TX_COMMAND_2_U                        TX_COMMAND_2                      ; // 0x188
    volatile MAC_TX_COMMAND_3_U                        TX_COMMAND_3                      ; // 0x18c
    volatile MAC_TX_COMMAND_4_U                        TX_COMMAND_4                      ; // 0x190
    volatile MAC_TX_COMMAND_5_U                        TX_COMMAND_5                      ; // 0x194
    volatile MAC_TX_COMMAND_6_U                        TX_COMMAND_6                      ; // 0x198
    volatile MAC_TX_COMMAND_7_U                        TX_COMMAND_7                      ; // 0x19c
    volatile MAC_TX_COMMAND_8_U                        TX_COMMAND_8                      ; // 0x1a0
    volatile MAC_TX_COMMAND_9_U                        TX_COMMAND_9                      ; // 0x1a4
    volatile MAC_TX_COMMAND_10_U                       TX_COMMAND_10                     ; // 0x1a8
    volatile MAC_TXOP_COMMAND_0_U                      TXOP_COMMAND_0                    ; // 0x1ac
    volatile MAC_TXOP_COMMAND_1_U                      TXOP_COMMAND_1                    ; // 0x1b0
    volatile MAC_TXOP_COMMAND_2_U                      TXOP_COMMAND_2                    ; // 0x1b4
    volatile MAC_TXOP_COMMAND_3_U                      TXOP_COMMAND_3                    ; // 0x1b8
    volatile MAC_TXOP_COMMAND_4_U                      TXOP_COMMAND_4                    ; // 0x1bc
    volatile MAC_TXOP_COMMAND_5_U                      TXOP_COMMAND_5                    ; // 0x1c0
    volatile MAC_TXOP_COMMAND_6_U                      TXOP_COMMAND_6                    ; // 0x1c4
    volatile MAC_TXOP_COMMAND_7_U                      TXOP_COMMAND_7                    ; // 0x1c8
    volatile MAC_TXOP_COMMAND_8_U                      TXOP_COMMAND_8                    ; // 0x1cc
    volatile MAC_TXOP_COMMAND_9_U                      TXOP_COMMAND_9                    ; // 0x1d0
    volatile MAC_TXOP_COMMAND_10_U                     TXOP_COMMAND_10                   ; // 0x1d4
    volatile MAC_TX_RAW_EDCA_0_U                       TX_RAW_EDCA_0                     ; // 0x1d8
    volatile MAC_TX_RAW_EDCA_1_U                       TX_RAW_EDCA_1                     ; // 0x1dc
    volatile MAC_TX_RAW_EDCA_2_U                       TX_RAW_EDCA_2                     ; // 0x1e0
    volatile MAC_TX_RAW_EDCA_3_U                       TX_RAW_EDCA_3                     ; // 0x1e4
    volatile MAC_TX_RAW_EDCA_4_U                       TX_RAW_EDCA_4                     ; // 0x1e8
    volatile MAC_TX_RAW_EDCA_5_U                       TX_RAW_EDCA_5                     ; // 0x1ec
    volatile MAC_TX_BASE_ADDRESS_U                     TX_BASE_ADDRESS                   ; // 0x1f0
    volatile MAC_TSW_DATA_IN_WAIT_U                    TSW_DATA_IN_WAIT                  ; // 0x1f4
    volatile MAC_TX_SUPPRESS_COMMAND_U                 TX_SUPPRESS_COMMAND               ; // 0x1f8
    volatile MAC_TX_SUPPRESS_START_TSF_U               TX_SUPPRESS_START_TSF             ; // 0x1fc
    volatile MAC_TX_SUPPRESS_END_TSF_U                 TX_SUPPRESS_END_TSF               ; // 0x200
    volatile MAC_TX_SUPPRESS_DURATION_U                TX_SUPPRESS_DURATION              ; // 0x204
    volatile MAC_TX_MYRAW_START_TSF_U                  TX_MYRAW_START_TSF                ; // 0x208
    volatile MAC_TX_MYRAW_END_TSF_U                    TX_MYRAW_END_TSF                  ; // 0x20c
    volatile MAC_TX_MYRAW_DURATION_U                   TX_MYRAW_DURATION                 ; // 0x210
    volatile MAC_TX_SUPPRESS_SETTING_U                 TX_SUPPRESS_SETTING               ; // 0x214
    volatile MAC_TX_SUPPRESS_STATUS_U                  TX_SUPPRESS_STATUS                ; // 0x218
    volatile MAC_TX_DATA_IN_WAIT_U                     TX_DATA_IN_WAIT                   ; // 0x21c
    volatile MAC_PHY_TXFIFO_MAX_DEPTH_U                PHY_TXFIFO_MAX_DEPTH              ; // 0x220
    volatile MAC_TXNAV_VALUE_U                         TXNAV_VALUE                       ; // 0x224
    volatile MAC_RXNAV_VALUE_U                         RXNAV_VALUE                       ; // 0x228
    volatile MAC_RID_VALUE_U                           RID_VALUE                         ; // 0x22c
    volatile MAC_NAV_RESET_U                           NAV_RESET                         ; // 0x230
    volatile MAC_RID_RESET_U                           RID_RESET                         ; // 0x234
    volatile MAC_NAV_RID_CONTROL_MODE_U                NAV_RID_CONTROL_MODE              ; // 0x238
    volatile MAC_TXNAV_HW_SETTING_VALUE_U              TXNAV_HW_SETTING_VALUE            ; // 0x23c
    volatile MAC_PREAMBLE_TYPE_U                       PREAMBLE_TYPE                     ; // 0x240
    volatile MAC_SET_CONTROL_FRAME_U                   SET_CONTROL_FRAME                 ; // 0x244
    volatile MAC_SET_PS_POLL_ACK_SW_U                  SET_PS_POLL_ACK_SW                ; // 0x248
    volatile MAC_SET_PS_POLL_ACK_DEFAULT_U             SET_PS_POLL_ACK_DEFAULT           ; // 0x24c
    volatile MAC_SET_RTSRID_U                          SET_RTSRID                        ; // 0x250
    volatile MAC_CF_CHANNEL_WIDTH_SELECTION_U          CF_CHANNEL_WIDTH_SELECTION        ; // 0x254
    volatile MAC_SET_FLOW_CONTROL_INFO_0_U             SET_FLOW_CONTROL_INFO_0           ; // 0x258
    volatile MAC_SET_FLOW_CONTROL_INFO_1_U             SET_FLOW_CONTROL_INFO_1           ; // 0x25c
    volatile MAC_SET_ACK_SW_U                          SET_ACK_SW                        ; // 0x260
    volatile MAC_SET_ACK_DEFAULT_U                     SET_ACK_DEFAULT                   ; // 0x264
    volatile MAC_BASIC_RATE_BITMAP_U                   BASIC_RATE_BITMAP                 ; // 0x268
    volatile MAC_BASIC_RATE_BITMAP_2ND_U               BASIC_RATE_BITMAP_2ND             ; // 0x26c
    volatile MAC_MCS_DIFFERENCE_U                      MCS_DIFFERENCE                    ; // 0x270
    volatile MAC_RESPONSE_TX_COMMAND_U                 RESPONSE_TX_COMMAND               ; // 0x274
    volatile MAC_RSP_TX_VECTOR_U                       RSP_TX_VECTOR                     ; // 0x278
    volatile MAC_RSP_TX_SIG0_U                         RSP_TX_SIG0                       ; // 0x27c
    volatile MAC_RSP_TX_SIG1_U                         RSP_TX_SIG1                       ; // 0x280
    volatile MAC_RSP_TX_INFO0_U                        RSP_TX_INFO0                      ; // 0x284
    volatile MAC_RSP_TX_INFO1_U                        RSP_TX_INFO1                      ; // 0x288
    volatile MAC_RSP_TX_DATA0_U                        RSP_TX_DATA0                      ; // 0x28c
    volatile MAC_RSP_TX_DATA1_U                        RSP_TX_DATA1                      ; // 0x290
    volatile MAC_RSP_TX_DATA2_U                        RSP_TX_DATA2                      ; // 0x294
    volatile MAC_RSP_TX_DATA3_U                        RSP_TX_DATA3                      ; // 0x298
    volatile MAC_RSP_TX_DATA4_U                        RSP_TX_DATA4                      ; // 0x29c
    volatile MAC_RSP_TX_DATA5_U                        RSP_TX_DATA5                      ; // 0x2a0
    volatile MAC_RSP_TX_DATA6_U                        RSP_TX_DATA6                      ; // 0x2a4
    volatile MAC_RSP_TX_DATA7_U                        RSP_TX_DATA7                      ; // 0x2a8
    volatile MAC_RSP_TX_DATA8_U                        RSP_TX_DATA8                      ; // 0x2ac
    volatile MAC_RSP_TX_DATA9_U                        RSP_TX_DATA9                      ; // 0x2b0
    volatile MAC_RSP_TX_DATA10_U                       RSP_TX_DATA10                     ; // 0x2b4
    volatile MAC_SET_CF_TXVECTOR_SIG_U                 SET_CF_TXVECTOR_SIG               ; // 0x2b8
    volatile MAC_MONITOR_INTERVAL_U                    MONITOR_INTERVAL                  ; // 0x2bc
    volatile MAC_CCA_RANGE_VAR_SET0_U                  CCA_RANGE_VAR_SET0                ; // 0x2c0
    volatile MAC_CCA_RANGE_VAR_SET1_U                  CCA_RANGE_VAR_SET1                ; // 0x2c4
    volatile MAC_RX_BASE_ADDRESS_U                     RX_BASE_ADDRESS                   ; // 0x2c8
    volatile MAC_RX_DSC_NUM_U                          RX_DSC_NUM                        ; // 0x2cc
    volatile MAC_RX_REG_DL_DESC0_U                     RX_REG_DL_DESC0                   ; // 0x2d0
    volatile MAC_RX_REG_DL_DESC1_U                     RX_REG_DL_DESC1                   ; // 0x2d4
    volatile MAC_RX_REG_DL_DESC2_U                     RX_REG_DL_DESC2                   ; // 0x2d8
    volatile MAC_RX_REG_DL_DESC3_U                     RX_REG_DL_DESC3                   ; // 0x2dc
    volatile MAC_RX_REG_DL_DESC4_U                     RX_REG_DL_DESC4                   ; // 0x2e0
    volatile MAC_RX_REG_DL_DESC5_U                     RX_REG_DL_DESC5                   ; // 0x2e4
    volatile MAC_RX_REG_DL_DESC6_U                     RX_REG_DL_DESC6                   ; // 0x2e8
    volatile MAC_RX_REG_DL_DESC7_U                     RX_REG_DL_DESC7                   ; // 0x2ec
    volatile MAC_RX_REG_DL_DESC8_U                     RX_REG_DL_DESC8                   ; // 0x2f0
    volatile MAC_RX_REG_DL_DESC9_U                     RX_REG_DL_DESC9                   ; // 0x2f4
    volatile MAC_RX_REG_DL_DESC10_U                    RX_REG_DL_DESC10                  ; // 0x2f8
    volatile MAC_RX_REG_DL_DESC11_U                    RX_REG_DL_DESC11                  ; // 0x2fc
    volatile MAC_RX_REG_DL_DESC12_U                    RX_REG_DL_DESC12                  ; // 0x300
    volatile MAC_RX_REG_DL_DESC13_U                    RX_REG_DL_DESC13                  ; // 0x304
    volatile MAC_RX_REG_DL_DESC14_U                    RX_REG_DL_DESC14                  ; // 0x308
    volatile MAC_RX_REG_DL_DESC15_U                    RX_REG_DL_DESC15                  ; // 0x30c
    volatile MAC_RX_REG_DL_DESC16_U                    RX_REG_DL_DESC16                  ; // 0x310
    volatile MAC_RX_REG_DL_DESC17_U                    RX_REG_DL_DESC17                  ; // 0x314
    volatile MAC_RX_REG_DL_DESC18_U                    RX_REG_DL_DESC18                  ; // 0x318
    volatile MAC_RX_REG_DL_DESC19_U                    RX_REG_DL_DESC19                  ; // 0x31c
    volatile MAC_RX_REG_DL_DESC20_U                    RX_REG_DL_DESC20                  ; // 0x320
    volatile MAC_RX_REG_DL_DESC21_U                    RX_REG_DL_DESC21                  ; // 0x324
    volatile MAC_RX_REG_DL_DESC22_U                    RX_REG_DL_DESC22                  ; // 0x328
    volatile MAC_RX_REG_DL_DESC23_U                    RX_REG_DL_DESC23                  ; // 0x32c
    volatile MAC_RX_REG_DL_DESC24_U                    RX_REG_DL_DESC24                  ; // 0x330
    volatile MAC_RX_REG_DL_DESC25_U                    RX_REG_DL_DESC25                  ; // 0x334
    volatile MAC_RX_REG_DL_DESC26_U                    RX_REG_DL_DESC26                  ; // 0x338
    volatile MAC_RX_REG_DL_DESC27_U                    RX_REG_DL_DESC27                  ; // 0x33c
    volatile MAC_RX_REG_DL_DESC28_U                    RX_REG_DL_DESC28                  ; // 0x340
    volatile MAC_RX_REG_DL_DESC29_U                    RX_REG_DL_DESC29                  ; // 0x344
    volatile MAC_RX_REG_DL_DESC30_U                    RX_REG_DL_DESC30                  ; // 0x348
    volatile MAC_RX_REG_DL_DESC31_U                    RX_REG_DL_DESC31                  ; // 0x34c
    volatile MAC_SET_OWNER_ADDR_U                      SET_OWNER_ADDR                    ; // 0x350
    volatile MAC_RX_DATA_IN_WAIT_U                     RX_DATA_IN_WAIT                   ; // 0x354
    volatile MAC_DMA_SEG_THRESHOLD_U                   DMA_SEG_THRESHOLD                 ; // 0x358
    volatile MAC_SEC_KEY_CMD_U                         SEC_KEY_CMD                       ; // 0x35c
    volatile MAC_SEC_KEY_CMD_EN_U                      SEC_KEY_CMD_EN                    ; // 0x360
    volatile MAC_SEC_KEY_VALUE0_U                      SEC_KEY_VALUE0                    ; // 0x364
    volatile MAC_SEC_KEY_VALUE1_U                      SEC_KEY_VALUE1                    ; // 0x368
    volatile MAC_SEC_KEY_VALUE2_U                      SEC_KEY_VALUE2                    ; // 0x36c
    volatile MAC_SEC_KEY_VALUE3_U                      SEC_KEY_VALUE3                    ; // 0x370
    volatile MAC_SEC_STA_ADDRESS0_U                    SEC_STA_ADDRESS0                  ; // 0x374
    volatile MAC_SEC_STA_ADDRESS1_U                    SEC_STA_ADDRESS1                  ; // 0x378
    volatile MAC_SEC_CCMP_UPDATE_INFO_U                SEC_CCMP_UPDATE_INFO              ; // 0x37c
    volatile MAC_SEC_CONFIG_U                          SEC_CONFIG                        ; // 0x380
    volatile MAC_SEC_OFFLINE_ENC_START_ADDR_U          SEC_OFFLINE_ENC_START_ADDR        ; // 0x384
    volatile MAC_SEC_OFFLINE_DEC_START_DESC_U          SEC_OFFLINE_DEC_START_DESC        ; // 0x388
    volatile MAC_SEC_OFFLINE_REQUEST_U                 SEC_OFFLINE_REQUEST               ; // 0x38c
    volatile MAC_SEC_INFO_1_U                          SEC_INFO_1                        ; // 0x390
    volatile MAC_SEC_INFO_2_U                          SEC_INFO_2                        ; // 0x394
    volatile MAC_SEC_INFO_3_U                          SEC_INFO_3                        ; // 0x398
    volatile MAC_SEC_INFO_4_U                          SEC_INFO_4                        ; // 0x39c
    volatile MAC_SEC_OFFSET_U                          SEC_OFFSET                        ; // 0x3a0
    volatile MAC_SEC_DATA_IN_WAIT_CNT_U                SEC_DATA_IN_WAIT_CNT              ; // 0x3a4
    volatile MAC_SEC_KEY_FLAG_IDX_U                    SEC_KEY_FLAG_IDX                  ; // 0x3a8
    volatile MAC_TX_INDIR_REG_ADDR_U                   TX_INDIR_REG_ADDR                 ; // 0x3ac
    volatile MAC_RX_INDIR_REG_ADDR_U                   RX_INDIR_REG_ADDR                 ; // 0x3b0
    volatile MAC_SEC_INDIR_REG_ADDR_U                  SEC_INDIR_REG_ADDR                ; // 0x3b4
    volatile MAC_DMA_INDIR_REG_ADDR_U                  DMA_INDIR_REG_ADDR                ; // 0x3b8
    volatile MAC_IRQ_INDIR_REG_ADDR_U                  IRQ_INDIR_REG_ADDR                ; // 0x3bc
    volatile MAC_MEM_INDIR_REG_ADDR_U                  MEM_INDIR_REG_ADDR                ; // 0x3c0
    volatile MAC_TSF_0_LOWER_U                         TSF_0_LOWER                       ; // 0x3c4
    volatile MAC_TSF_0_UPPER_U                         TSF_0_UPPER                       ; // 0x3c8
    volatile MAC_TSF_0_ALARM_LOWER_U                   TSF_0_ALARM_LOWER                 ; // 0x3cc
    volatile MAC_BCN_INTERVAL_0_U                      BCN_INTERVAL_0                    ; // 0x3d0
    volatile MAC_TBTT_INTERRUPT_MARGIN_0_U             TBTT_INTERRUPT_MARGIN_0           ; // 0x3d4
    volatile MAC_TBTT_RESTART_RANGE_0_U                TBTT_RESTART_RANGE_0              ; // 0x3d8
    volatile MAC_TSF_1_LOWER_U                         TSF_1_LOWER                       ; // 0x3dc
    volatile MAC_TSF_1_UPPER_U                         TSF_1_UPPER                       ; // 0x3e0
    volatile MAC_TSF_1_ALARM_LOWER_U                   TSF_1_ALARM_LOWER                 ; // 0x3e4
    volatile MAC_BCN_INTERVAL_1_U                      BCN_INTERVAL_1                    ; // 0x3e8
    volatile MAC_TBTT_INTERRUPT_MARGIN_1_U             TBTT_INTERRUPT_MARGIN_1           ; // 0x3ec
    volatile MAC_TBTT_RESTART_RANGE_1_U                TBTT_RESTART_RANGE_1              ; // 0x3f0
    volatile MAC_IRQ_MASK0_U                           IRQ_MASK0                         ; // 0x3f4
    volatile MAC_IRQ_MASK1_U                           IRQ_MASK1                         ; // 0x3f8
    volatile MAC_IRQ_SET_CLEAR0_U                      IRQ_SET_CLEAR0                    ; // 0x3fc
    volatile MAC_IRQ_SET_CLEAR1_U                      IRQ_SET_CLEAR1                    ; // 0x400
    volatile MAC_CLOCK_GATING_CONFIG_U                 CLOCK_GATING_CONFIG               ; // 0x404
    volatile MAC_TX_RESULT_0_U                         TX_RESULT_0                       ; // 0x408
    volatile MAC_TX_RESULT_1_U                         TX_RESULT_1                       ; // 0x40c
    volatile MAC_TX_RESULT_2_U                         TX_RESULT_2                       ; // 0x410
    volatile MAC_TX_RESULT_3_U                         TX_RESULT_3                       ; // 0x414
    volatile MAC_TX_RESULT_4_U                         TX_RESULT_4                       ; // 0x418
    volatile MAC_TX_RESULT_5_U                         TX_RESULT_5                       ; // 0x41c
    volatile MAC_TX_RESULT_6_U                         TX_RESULT_6                       ; // 0x420
    volatile MAC_TX_RESULT_7_U                         TX_RESULT_7                       ; // 0x424
    volatile MAC_TX_RESULT_8_U                         TX_RESULT_8                       ; // 0x428
    volatile MAC_TX_RESULT_9_U                         TX_RESULT_9                       ; // 0x42c
    volatile MAC_TX_RESULT_10_U                        TX_RESULT_10                      ; // 0x430
    volatile MAC_TX_RESULT_11_U                        TX_RESULT_11                      ; // 0x434
    volatile MAC_TX_RESULT_12_U                        TX_RESULT_12                      ; // 0x438
    volatile MAC_TX_RESULT_13_U                        TX_RESULT_13                      ; // 0x43c
    volatile MAC_TX_RESULT_14_U                        TX_RESULT_14                      ; // 0x440
    volatile MAC_TX_RESULT_15_U                        TX_RESULT_15                      ; // 0x444
    volatile MAC_TX_RESULT_16_U                        TX_RESULT_16                      ; // 0x448
    volatile MAC_TX_RESULT_17_U                        TX_RESULT_17                      ; // 0x44c
    volatile MAC_TX_RESULT_18_U                        TX_RESULT_18                      ; // 0x450
    volatile MAC_TX_RESULT_19_U                        TX_RESULT_19                      ; // 0x454
    volatile MAC_TX_RESULT_20_U                        TX_RESULT_20                      ; // 0x458
    volatile MAC_TX_RESULT_21_U                        TX_RESULT_21                      ; // 0x45c
    volatile MAC_TX_FAILED_BITMAP_LOWER_0_U            TX_FAILED_BITMAP_LOWER_0          ; // 0x460
    volatile MAC_TX_FAILED_BITMAP_UPPER_0_U            TX_FAILED_BITMAP_UPPER_0          ; // 0x464
    volatile MAC_TX_FAILED_BITMAP_LOWER_1_U            TX_FAILED_BITMAP_LOWER_1          ; // 0x468
    volatile MAC_TX_FAILED_BITMAP_UPPER_1_U            TX_FAILED_BITMAP_UPPER_1          ; // 0x46c
    volatile MAC_TX_FAILED_BITMAP_LOWER_2_U            TX_FAILED_BITMAP_LOWER_2          ; // 0x470
    volatile MAC_TX_FAILED_BITMAP_UPPER_2_U            TX_FAILED_BITMAP_UPPER_2          ; // 0x474
    volatile MAC_TX_FAILED_BITMAP_LOWER_3_U            TX_FAILED_BITMAP_LOWER_3          ; // 0x478
    volatile MAC_TX_FAILED_BITMAP_UPPER_3_U            TX_FAILED_BITMAP_UPPER_3          ; // 0x47c
    volatile MAC_TX_FAILED_BITMAP_LOWER_4_U            TX_FAILED_BITMAP_LOWER_4          ; // 0x480
    volatile MAC_TX_FAILED_BITMAP_UPPER_4_U            TX_FAILED_BITMAP_UPPER_4          ; // 0x484
    volatile MAC_TX_FAILED_BITMAP_LOWER_5_U            TX_FAILED_BITMAP_LOWER_5          ; // 0x488
    volatile MAC_TX_FAILED_BITMAP_UPPER_5_U            TX_FAILED_BITMAP_UPPER_5          ; // 0x48c
    volatile MAC_TX_FAILED_BITMAP_LOWER_6_U            TX_FAILED_BITMAP_LOWER_6          ; // 0x490
    volatile MAC_TX_FAILED_BITMAP_UPPER_6_U            TX_FAILED_BITMAP_UPPER_6          ; // 0x494
    volatile MAC_TX_FAILED_BITMAP_LOWER_7_U            TX_FAILED_BITMAP_LOWER_7          ; // 0x498
    volatile MAC_TX_FAILED_BITMAP_UPPER_7_U            TX_FAILED_BITMAP_UPPER_7          ; // 0x49c
    volatile MAC_TX_FAILED_BITMAP_LOWER_8_U            TX_FAILED_BITMAP_LOWER_8          ; // 0x4a0
    volatile MAC_TX_FAILED_BITMAP_UPPER_8_U            TX_FAILED_BITMAP_UPPER_8          ; // 0x4a4
    volatile MAC_TX_FAILED_BITMAP_LOWER_9_U            TX_FAILED_BITMAP_LOWER_9          ; // 0x4a8
    volatile MAC_TX_FAILED_BITMAP_UPPER_9_U            TX_FAILED_BITMAP_UPPER_9          ; // 0x4ac
    volatile MAC_TX_FAILED_BITMAP_LOWER_10_U           TX_FAILED_BITMAP_LOWER_10         ; // 0x4b0
    volatile MAC_TX_FAILED_BITMAP_UPPER_10_U           TX_FAILED_BITMAP_UPPER_10         ; // 0x4b4
    volatile MAC_RESPONSE_TX_RESULT_U                  RESPONSE_TX_RESULT                ; // 0x4b8
    volatile MAC_RX_WRITE_EN_DL_DESC0_U                RX_WRITE_EN_DL_DESC0              ; // 0x4bc
    volatile MAC_RX_WRITE_EN_DL_DESC1_U                RX_WRITE_EN_DL_DESC1              ; // 0x4c0
    volatile MAC_RX_WRITE_EN_DL_DESC2_U                RX_WRITE_EN_DL_DESC2              ; // 0x4c4
    volatile MAC_RX_WRITE_EN_DL_DESC3_U                RX_WRITE_EN_DL_DESC3              ; // 0x4c8
    volatile MAC_RX_WRITE_EN_DL_DESC4_U                RX_WRITE_EN_DL_DESC4              ; // 0x4cc
    volatile MAC_RX_WRITE_EN_DL_DESC5_U                RX_WRITE_EN_DL_DESC5              ; // 0x4d0
    volatile MAC_RX_WRITE_EN_DL_DESC6_U                RX_WRITE_EN_DL_DESC6              ; // 0x4d4
    volatile MAC_RX_WRITE_EN_DL_DESC7_U                RX_WRITE_EN_DL_DESC7              ; // 0x4d8
    volatile MAC_RX_WRITE_EN_DL_DESC8_U                RX_WRITE_EN_DL_DESC8              ; // 0x4dc
    volatile MAC_RX_WRITE_EN_DL_DESC9_U                RX_WRITE_EN_DL_DESC9              ; // 0x4e0
    volatile MAC_RX_WRITE_EN_DL_DESC10_U               RX_WRITE_EN_DL_DESC10             ; // 0x4e4
    volatile MAC_RX_WRITE_EN_DL_DESC11_U               RX_WRITE_EN_DL_DESC11             ; // 0x4e8
    volatile MAC_RX_WRITE_EN_DL_DESC12_U               RX_WRITE_EN_DL_DESC12             ; // 0x4ec
    volatile MAC_RX_WRITE_EN_DL_DESC13_U               RX_WRITE_EN_DL_DESC13             ; // 0x4f0
    volatile MAC_RX_WRITE_EN_DL_DESC14_U               RX_WRITE_EN_DL_DESC14             ; // 0x4f4
    volatile MAC_RX_WRITE_EN_DL_DESC15_U               RX_WRITE_EN_DL_DESC15             ; // 0x4f8
    volatile MAC_RX_WRITE_EN_DL_DESC16_U               RX_WRITE_EN_DL_DESC16             ; // 0x4fc
    volatile MAC_RX_WRITE_EN_DL_DESC17_U               RX_WRITE_EN_DL_DESC17             ; // 0x500
    volatile MAC_RX_WRITE_EN_DL_DESC18_U               RX_WRITE_EN_DL_DESC18             ; // 0x504
    volatile MAC_RX_WRITE_EN_DL_DESC19_U               RX_WRITE_EN_DL_DESC19             ; // 0x508
    volatile MAC_RX_WRITE_EN_DL_DESC20_U               RX_WRITE_EN_DL_DESC20             ; // 0x50c
    volatile MAC_RX_WRITE_EN_DL_DESC21_U               RX_WRITE_EN_DL_DESC21             ; // 0x510
    volatile MAC_RX_WRITE_EN_DL_DESC22_U               RX_WRITE_EN_DL_DESC22             ; // 0x514
    volatile MAC_RX_WRITE_EN_DL_DESC23_U               RX_WRITE_EN_DL_DESC23             ; // 0x518
    volatile MAC_RX_WRITE_EN_DL_DESC24_U               RX_WRITE_EN_DL_DESC24             ; // 0x51c
    volatile MAC_RX_WRITE_EN_DL_DESC25_U               RX_WRITE_EN_DL_DESC25             ; // 0x520
    volatile MAC_RX_WRITE_EN_DL_DESC26_U               RX_WRITE_EN_DL_DESC26             ; // 0x524
    volatile MAC_RX_WRITE_EN_DL_DESC27_U               RX_WRITE_EN_DL_DESC27             ; // 0x528
    volatile MAC_RX_WRITE_EN_DL_DESC28_U               RX_WRITE_EN_DL_DESC28             ; // 0x52c
    volatile MAC_RX_WRITE_EN_DL_DESC29_U               RX_WRITE_EN_DL_DESC29             ; // 0x530
    volatile MAC_RX_WRITE_EN_DL_DESC30_U               RX_WRITE_EN_DL_DESC30             ; // 0x534
    volatile MAC_RX_WRITE_EN_DL_DESC31_U               RX_WRITE_EN_DL_DESC31             ; // 0x538
    volatile MAC_RXSIG0_U                              RXSIG0                            ; // 0x53c
    volatile MAC_RXSIG1_U                              RXSIG1                            ; // 0x540
    volatile MAC_RXVECTOR0_U                           RXVECTOR0                         ; // 0x544
    volatile MAC_RXVECTOR1_U                           RXVECTOR1                         ; // 0x548
    volatile MAC_RXVECTOR2_U                           RXVECTOR2                         ; // 0x54c
    volatile MAC_RXINFO0_U                             RXINFO0                           ; // 0x550
    volatile MAC_RXINFO1_U                             RXINFO1                           ; // 0x554
    volatile MAC_RXINFO2_U                             RXINFO2                           ; // 0x558
    volatile MAC_RXINFO3_U                             RXINFO3                           ; // 0x55c
    volatile MAC_RXHEADER0_U                           RXHEADER0                         ; // 0x560
    volatile MAC_RXHEADER1_U                           RXHEADER1                         ; // 0x564
    volatile MAC_RXHEADER2_U                           RXHEADER2                         ; // 0x568
    volatile MAC_RXHEADER3_U                           RXHEADER3                         ; // 0x56c
    volatile MAC_RXHEADER4_U                           RXHEADER4                         ; // 0x570
    volatile MAC_RXHEADER5_U                           RXHEADER5                         ; // 0x574
    volatile MAC_RXHEADER6_U                           RXHEADER6                         ; // 0x578
    volatile MAC_RXHEADER7_U                           RXHEADER7                         ; // 0x57c
    volatile MAC_RXHEADER8_U                           RXHEADER8                         ; // 0x580
    volatile MAC_AMPDU_BITMAP_U                        AMPDU_BITMAP                      ; // 0x584
    volatile MAC_KEY_CMD_RESULT_EN_U                   KEY_CMD_RESULT_EN                 ; // 0x588
    volatile MAC_KEY_CMD_RESULT_U                      KEY_CMD_RESULT                    ; // 0x58c
    volatile MAC_SEC_REG_MIC_CHECK_FAIL_U              SEC_REG_MIC_CHECK_FAIL            ; // 0x590
    volatile MAC_SEC_KEY_FLAG_U                        SEC_KEY_FLAG                      ; // 0x594
    volatile MAC_SEC_MIC_VALUE_RX_FAILED_0_U           SEC_MIC_VALUE_RX_FAILED_0         ; // 0x598
    volatile MAC_SEC_MIC_VALUE_RX_FAILED_1_U           SEC_MIC_VALUE_RX_FAILED_1         ; // 0x59c
    volatile MAC_TX_INDIR_REG_DATA_U                   TX_INDIR_REG_DATA                 ; // 0x5a0
    volatile MAC_RX_INDIR_REG_DATA_U                   RX_INDIR_REG_DATA                 ; // 0x5a4
    volatile MAC_SEC_INDIR_REG_DATA_U                  SEC_INDIR_REG_DATA                ; // 0x5a8
    volatile MAC_DMA_INDIR_REG_DATA_U                  DMA_INDIR_REG_DATA                ; // 0x5ac
    volatile MAC_IRQ_INDIR_REG_DATA_U                  IRQ_INDIR_REG_DATA                ; // 0x5b0
    volatile MAC_TSF_0_LOWER_READONLY_U                TSF_0_LOWER_READONLY              ; // 0x5b4
    volatile MAC_TSF_0_UPPER_READONLY_U                TSF_0_UPPER_READONLY              ; // 0x5b8
    volatile MAC_TSF_1_LOWER_READONLY_U                TSF_1_LOWER_READONLY              ; // 0x5bc
    volatile MAC_TSF_1_UPPER_READONLY_U                TSF_1_UPPER_READONLY              ; // 0x5c0
    volatile MAC_IRQ_SRC_NOCLEAR0_U                    IRQ_SRC_NOCLEAR0                  ; // 0x5c4
    volatile MAC_IRQ_SRC_NOCLEAR1_U                    IRQ_SRC_NOCLEAR1                  ; // 0x5c8
    volatile MAC_IRQ_SRC0_U                            IRQ_SRC0                          ; // 0x5cc
    volatile MAC_IRQ_SRC1_U                            IRQ_SRC1                          ; // 0x5d0
    volatile MAC_RX_NDP_PAGING_U                       RX_NDP_PAGING                     ; // 0x5d4
    volatile uint32_t                                     RESERVED0[74]                     ; // 
    volatile MAC_BUS_CLK_MODE_U                        BUS_CLK_MODE                      ; // 0x700
    volatile MAC_TICK_CNT_MODE_U                       TICK_CNT_MODE                     ; // 0x704
    volatile MAC_TICK_CNT_CAPT_U                       TICK_CNT_CAPT                     ; // 0x708
    volatile uint32_t                                     RESERVED1[61]                     ; // 
    volatile MAC_TX_RF_PARAM_LOWER_0_U                 TX_RF_PARAM_LOWER_0               ; // 0x800
    volatile MAC_TX_RF_PARAM_MIDDLE_0_U                TX_RF_PARAM_MIDDLE_0              ; // 0x804
    volatile MAC_TX_RF_PARAM_UPPER_0_U                 TX_RF_PARAM_UPPER_0               ; // 0x808
    volatile MAC_TX_DIG_GAIN_0_U                       TX_DIG_GAIN_0                     ; // 0x80c
    volatile MAC_TX_ANAGAIN_DPD_0_U                    TX_ANAGAIN_DPD_0                  ; // 0x810
    volatile MAC_TX_RF_PARAM_LOWER_1_U                 TX_RF_PARAM_LOWER_1               ; // 0x814
    volatile MAC_TX_RF_PARAM_MIDDLE_1_U                TX_RF_PARAM_MIDDLE_1              ; // 0x818
    volatile MAC_TX_RF_PARAM_UPPER_1_U                 TX_RF_PARAM_UPPER_1               ; // 0x81c
    volatile MAC_TX_DIG_GAIN_1_U                       TX_DIG_GAIN_1                     ; // 0x820
    volatile MAC_TX_ANAGAIN_DPD_1_U                    TX_ANAGAIN_DPD_1                  ; // 0x824
    volatile MAC_TX_RF_PARAM_LOWER_2_U                 TX_RF_PARAM_LOWER_2               ; // 0x828
    volatile MAC_TX_RF_PARAM_MIDDLE_2_U                TX_RF_PARAM_MIDDLE_2              ; // 0x82c
    volatile MAC_TX_RF_PARAM_UPPER_2_U                 TX_RF_PARAM_UPPER_2               ; // 0x830
    volatile MAC_TX_DIG_GAIN_2_U                       TX_DIG_GAIN_2                     ; // 0x834
    volatile MAC_TX_ANAGAIN_DPD_2_U                    TX_ANAGAIN_DPD_2                  ; // 0x838
    volatile MAC_TX_RF_PARAM_LOWER_3_U                 TX_RF_PARAM_LOWER_3               ; // 0x83c
    volatile MAC_TX_RF_PARAM_MIDDLE_3_U                TX_RF_PARAM_MIDDLE_3              ; // 0x840
    volatile MAC_TX_RF_PARAM_UPPER_3_U                 TX_RF_PARAM_UPPER_3               ; // 0x844
    volatile MAC_TX_DIG_GAIN_3_U                       TX_DIG_GAIN_3                     ; // 0x848
    volatile MAC_TX_ANAGAIN_DPD_3_U                    TX_ANAGAIN_DPD_3                  ; // 0x84c
    volatile MAC_TX_RF_PARAM_LOWER_4_U                 TX_RF_PARAM_LOWER_4               ; // 0x850
    volatile MAC_TX_RF_PARAM_MIDDLE_4_U                TX_RF_PARAM_MIDDLE_4              ; // 0x854
    volatile MAC_TX_RF_PARAM_UPPER_4_U                 TX_RF_PARAM_UPPER_4               ; // 0x858
    volatile MAC_TX_DIG_GAIN_4_U                       TX_DIG_GAIN_4                     ; // 0x85c
    volatile MAC_TX_ANAGAIN_DPD_4_U                    TX_ANAGAIN_DPD_4                  ; // 0x860
    volatile MAC_TX_RF_PARAM_LOWER_5_U                 TX_RF_PARAM_LOWER_5               ; // 0x864
    volatile MAC_TX_RF_PARAM_MIDDLE_5_U                TX_RF_PARAM_MIDDLE_5              ; // 0x868
    volatile MAC_TX_RF_PARAM_UPPER_5_U                 TX_RF_PARAM_UPPER_5               ; // 0x86c
    volatile MAC_TX_DIG_GAIN_5_U                       TX_DIG_GAIN_5                     ; // 0x870
    volatile MAC_TX_ANAGAIN_DPD_5_U                    TX_ANAGAIN_DPD_5                  ; // 0x874
    volatile MAC_TX_RF_PARAM_LOWER_6_U                 TX_RF_PARAM_LOWER_6               ; // 0x878
    volatile MAC_TX_RF_PARAM_MIDDLE_6_U                TX_RF_PARAM_MIDDLE_6              ; // 0x87c
    volatile MAC_TX_RF_PARAM_UPPER_6_U                 TX_RF_PARAM_UPPER_6               ; // 0x880
    volatile MAC_TX_DIG_GAIN_6_U                       TX_DIG_GAIN_6                     ; // 0x884
    volatile MAC_TX_ANAGAIN_DPD_6_U                    TX_ANAGAIN_DPD_6                  ; // 0x888
    volatile MAC_TX_RF_PARAM_LOWER_7_U                 TX_RF_PARAM_LOWER_7               ; // 0x88c
    volatile MAC_TX_RF_PARAM_MIDDLE_7_U                TX_RF_PARAM_MIDDLE_7              ; // 0x890
    volatile MAC_TX_RF_PARAM_UPPER_7_U                 TX_RF_PARAM_UPPER_7               ; // 0x894
    volatile MAC_TX_DIG_GAIN_7_U                       TX_DIG_GAIN_7                     ; // 0x898
    volatile MAC_TX_ANAGAIN_DPD_7_U                    TX_ANAGAIN_DPD_7                  ; // 0x89c
    volatile MAC_TX_RF_PARAM_LOWER_8_U                 TX_RF_PARAM_LOWER_8               ; // 0x8a0
    volatile MAC_TX_RF_PARAM_MIDDLE_8_U                TX_RF_PARAM_MIDDLE_8              ; // 0x8a4
    volatile MAC_TX_RF_PARAM_UPPER_8_U                 TX_RF_PARAM_UPPER_8               ; // 0x8a8
    volatile MAC_TX_DIG_GAIN_8_U                       TX_DIG_GAIN_8                     ; // 0x8ac
    volatile MAC_TX_ANAGAIN_DPD_8_U                    TX_ANAGAIN_DPD_8                  ; // 0x8b0
    volatile MAC_TX_RF_PARAM_LOWER_9_U                 TX_RF_PARAM_LOWER_9               ; // 0x8b4
    volatile MAC_TX_RF_PARAM_MIDDLE_9_U                TX_RF_PARAM_MIDDLE_9              ; // 0x8b8
    volatile MAC_TX_RF_PARAM_UPPER_9_U                 TX_RF_PARAM_UPPER_9               ; // 0x8bc
    volatile MAC_TX_DIG_GAIN_9_U                       TX_DIG_GAIN_9                     ; // 0x8c0
    volatile MAC_TX_ANAGAIN_DPD_9_U                    TX_ANAGAIN_DPD_9                  ; // 0x8c4
    volatile MAC_TX_RF_PARAM_LOWER_10_U                TX_RF_PARAM_LOWER_10              ; // 0x8c8
    volatile MAC_TX_RF_PARAM_MIDDLE_10_U               TX_RF_PARAM_MIDDLE_10             ; // 0x8cc
    volatile MAC_TX_RF_PARAM_UPPER_10_U                TX_RF_PARAM_UPPER_10              ; // 0x8d0
    volatile MAC_TX_DIG_GAIN_10_U                      TX_DIG_GAIN_10                    ; // 0x8d4
    volatile MAC_TX_ANAGAIN_DPD_10_U                   TX_ANAGAIN_DPD_10                 ; // 0x8d8
    volatile MAC_TX_RF_PARAM_LOWER_CF_U                TX_RF_PARAM_LOWER_CF              ; // 0x8dc
    volatile MAC_TX_RF_PARAM_MIDDLE_CF_U               TX_RF_PARAM_MIDDLE_CF             ; // 0x8e0
    volatile MAC_TX_RF_PARAM_UPPER_CF_U                TX_RF_PARAM_UPPER_CF              ; // 0x8e4
    volatile MAC_TX_DIG_GAIN_CF_U                      TX_DIG_GAIN_CF                    ; // 0x8e8
    volatile MAC_TX_ANAGAIN_DPD_CF_U                   TX_ANAGAIN_DPD_CF                 ; // 0x8ec
} MAC_Type;

#ifdef __cplusplus
}
#endif

#endif /* __REG_MAC_H__ */
