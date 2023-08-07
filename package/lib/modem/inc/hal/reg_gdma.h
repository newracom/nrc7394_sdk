/*********************************************************************/
/*    Newracom Library / IP Product                                  */
/*    Product Name :                                                 */
/*    Version      :                                                 */
/*    Author       :                                                 */
/*    Update       :                                                 */
/*********************************************************************/

#ifndef __REG_GDMA_H__
#define __REG_GDMA_H__

#ifdef __cplusplus
extern "C"{
#endif

// 0x40091000 register ------------------------------------
typedef struct {
    uint32_t                   IntStatus00            :1 ;
    uint32_t                   IntStatus01            :1 ;
    uint32_t                   IntStatus02            :1 ;
    uint32_t                   IntStatus03            :1 ;
    uint32_t                   IntStatus04            :1 ;
    uint32_t                   IntStatus05            :1 ;
    uint32_t                   IntStatus06            :1 ;
    uint32_t                   IntStatus07            :1 ;
    uint32_t                   reserved0              :24;
}   GDMA_IntStatus;

typedef union {
    uint32_t                   w;
    GDMA_IntStatus             b;
}   GDMA_IntStatus_U;


// 0x40091004 register ------------------------------------
typedef struct {
    uint32_t                   IntTCStatus00          :1 ;
    uint32_t                   IntTCStatus01          :1 ;
    uint32_t                   IntTCStatus02          :1 ;
    uint32_t                   IntTCStatus03          :1 ;
    uint32_t                   IntTCStatus04          :1 ;
    uint32_t                   IntTCStatus05          :1 ;
    uint32_t                   IntTCStatus06          :1 ;
    uint32_t                   IntTCStatus07          :1 ;
    uint32_t                   reserved0              :24;
}   GDMA_IntTCStatus;

typedef union {
    uint32_t                   w;
    GDMA_IntTCStatus           b;
}   GDMA_IntTCStatus_U;


// 0x40091008 register ------------------------------------
typedef struct {
    uint32_t                   IntTCClear00           :1 ;
    uint32_t                   IntTCClear01           :1 ;
    uint32_t                   IntTCClear02           :1 ;
    uint32_t                   IntTCClear03           :1 ;
    uint32_t                   IntTCClear04           :1 ;
    uint32_t                   IntTCClear05           :1 ;
    uint32_t                   IntTCClear06           :1 ;
    uint32_t                   IntTCClear07           :1 ;
    uint32_t                   reserved0              :24;
}   GDMA_IntTCClear;

typedef union {
    uint32_t                   w;
    GDMA_IntTCClear            b;
}   GDMA_IntTCClear_U;


// 0x4009100C register ------------------------------------
typedef struct {
    uint32_t                   IntErrorStatus00       :1 ;
    uint32_t                   IntErrorStatus01       :1 ;
    uint32_t                   IntErrorStatus02       :1 ;
    uint32_t                   IntErrorStatus03       :1 ;
    uint32_t                   IntErrorStatus04       :1 ;
    uint32_t                   IntErrorStatus05       :1 ;
    uint32_t                   IntErrorStatus06       :1 ;
    uint32_t                   IntErrorStatus07       :1 ;
    uint32_t                   reserved0              :24;
}   GDMA_IntErrorStatus;

typedef union {
    uint32_t                   w;
    GDMA_IntErrorStatus        b;
}   GDMA_IntErrorStatus_U;


// 0x40091010 register ------------------------------------
typedef struct {
    uint32_t                   IntErrorClr00          :1 ;
    uint32_t                   IntErrorClr01          :1 ;
    uint32_t                   IntErrorClr02          :1 ;
    uint32_t                   IntErrorClr03          :1 ;
    uint32_t                   IntErrorClr04          :1 ;
    uint32_t                   IntErrorClr05          :1 ;
    uint32_t                   IntErrorClr06          :1 ;
    uint32_t                   IntErrorClr07          :1 ;
    uint32_t                   reserved0              :24;
}   GDMA_IntErrorClr;

typedef union {
    uint32_t                   w;
    GDMA_IntErrorClr           b;
}   GDMA_IntErrorClr_U;


// 0x40091014 register ------------------------------------
typedef struct {
    uint32_t                   RawIntTCStatus00       :1 ;
    uint32_t                   RawIntTCStatus01       :1 ;
    uint32_t                   RawIntTCStatus02       :1 ;
    uint32_t                   RawIntTCStatus03       :1 ;
    uint32_t                   RawIntTCStatus04       :1 ;
    uint32_t                   RawIntTCStatus05       :1 ;
    uint32_t                   RawIntTCStatus06       :1 ;
    uint32_t                   RawIntTCStatus07       :1 ;
    uint32_t                   reserved0              :24;
}   GDMA_RawIntTCStatus;

typedef union {
    uint32_t                   w;
    GDMA_RawIntTCStatus        b;
}   GDMA_RawIntTCStatus_U;


// 0x40091018 register ------------------------------------
typedef struct {
    uint32_t                   RawIntErrorStatus00    :1 ;
    uint32_t                   RawIntErrorStatus01    :1 ;
    uint32_t                   RawIntErrorStatus02    :1 ;
    uint32_t                   RawIntErrorStatus03    :1 ;
    uint32_t                   RawIntErrorStatus04    :1 ;
    uint32_t                   RawIntErrorStatus05    :1 ;
    uint32_t                   RawIntErrorStatus06    :1 ;
    uint32_t                   RawIntErrorStatus07    :1 ;
    uint32_t                   reserved0              :24;
}   GDMA_RawIntErrorStatus;

typedef union {
    uint32_t                   w;
    GDMA_RawIntErrorStatus     b;
}   GDMA_RawIntErrorStatus_U;


// 0x4009101C register ------------------------------------
typedef struct {
    uint32_t                   EnbldChns00            :1 ;
    uint32_t                   EnbldChns01            :1 ;
    uint32_t                   EnbldChns02            :1 ;
    uint32_t                   EnbldChns03            :1 ;
    uint32_t                   EnbldChns04            :1 ;
    uint32_t                   EnbldChns05            :1 ;
    uint32_t                   EnbldChns06            :1 ;
    uint32_t                   EnbldChns07            :1 ;
    uint32_t                   reserved0              :24;
}   GDMA_EnbldChns;

typedef union {
    uint32_t                   w;
    GDMA_EnbldChns             b;
}   GDMA_EnbldChns_U;


// 0x40091020 register ------------------------------------
typedef struct {
    uint32_t                   SoftBReq00             :1 ;
    uint32_t                   SoftBReq01             :1 ;
    uint32_t                   SoftBReq02             :1 ;
    uint32_t                   SoftBReq03             :1 ;
    uint32_t                   SoftBReq04             :1 ;
    uint32_t                   SoftBReq05             :1 ;
    uint32_t                   SoftBReq06             :1 ;
    uint32_t                   SoftBReq07             :1 ;
    uint32_t                   reserved0              :24;
}   GDMA_SoftBReq;

typedef union {
    uint32_t                   w;
    GDMA_SoftBReq              b;
}   GDMA_SoftBReq_U;


// 0x40091024 register ------------------------------------
typedef struct {
    uint32_t                   SoftSReq00             :1 ;
    uint32_t                   SoftSReq01             :1 ;
    uint32_t                   SoftSReq02             :1 ;
    uint32_t                   SoftSReq03             :1 ;
    uint32_t                   SoftSReq04             :1 ;
    uint32_t                   SoftSReq05             :1 ;
    uint32_t                   SoftSReq06             :1 ;
    uint32_t                   SoftSReq07             :1 ;
    uint32_t                   reserved0              :24;
}   GDMA_SoftSReq;

typedef union {
    uint32_t                   w;
    GDMA_SoftSReq              b;
}   GDMA_SoftSReq_U;


// 0x40091028 register ------------------------------------
typedef struct {
    uint32_t                   SoftLBReq00            :1 ;
    uint32_t                   SoftLBReq01            :1 ;
    uint32_t                   SoftLBReq02            :1 ;
    uint32_t                   SoftLBReq03            :1 ;
    uint32_t                   SoftLBReq04            :1 ;
    uint32_t                   SoftLBReq05            :1 ;
    uint32_t                   SoftLBReq06            :1 ;
    uint32_t                   SoftLBReq07            :1 ;
    uint32_t                   reserved0              :24;
}   GDMA_SoftLBReq;

typedef union {
    uint32_t                   w;
    GDMA_SoftLBReq             b;
}   GDMA_SoftLBReq_U;


// 0x4009102C register ------------------------------------
typedef struct {
    uint32_t                   SoftLSReq00            :1 ;
    uint32_t                   SoftLSReq01            :1 ;
    uint32_t                   SoftLSReq02            :1 ;
    uint32_t                   SoftLSReq03            :1 ;
    uint32_t                   SoftLSReq04            :1 ;
    uint32_t                   SoftLSReq05            :1 ;
    uint32_t                   SoftLSReq06            :1 ;
    uint32_t                   SoftLSReq07            :1 ;
    uint32_t                   reserved0              :24;
}   GDMA_SoftLSReq;

typedef union {
    uint32_t                   w;
    GDMA_SoftLSReq             b;
}   GDMA_SoftLSReq_U;


// 0x40091030 register ------------------------------------
typedef struct {
    uint32_t                   EN                     :1 ;
    uint32_t                   M1                     :1 ;
    uint32_t                   M2                     :1 ;
    uint32_t                   reserved0              :29;
}   GDMA_Configuration;

typedef union {
    uint32_t                   w;
    GDMA_Configuration         b;
}   GDMA_Configuration_U;


// 0x40091034 register ------------------------------------
typedef struct {
    uint32_t                   Sync                   :16;
    uint32_t                   reserved0              :16;
}   GDMA_Sync;

typedef union {
    uint32_t                   w;
    GDMA_Sync                  b;
}   GDMA_Sync_U;


// 0x40091100 register ------------------------------------
typedef struct {
    uint32_t                   SrcAddr                :32;
}   GDMA_C0SrcAddr;

typedef union {
    uint32_t                   w;
    GDMA_C0SrcAddr             b;
}   GDMA_C0SrcAddr_U;


// 0x40091104 register ------------------------------------
typedef struct {
    uint32_t                   DstAddr                :32;
}   GDMA_C0DestAddr;

typedef union {
    uint32_t                   w;
    GDMA_C0DestAddr            b;
}   GDMA_C0DestAddr_U;


// 0x40091108 register ------------------------------------
typedef struct {
    uint32_t                   LD                     :1 ;
    uint32_t                   reserved0              :1 ;
    uint32_t                   ADDR                   :30;
}   GDMA_C0LLI;

typedef union {
    uint32_t                   w;
    GDMA_C0LLI                 b;
}   GDMA_C0LLI_U;


// 0x4009110C register ------------------------------------
typedef struct {
    uint32_t                   TranSize               :12;
    uint32_t                   SBSize                 :3 ;
    uint32_t                   DBSize                 :3 ;
    uint32_t                   SWidth                 :3 ;
    uint32_t                   DWidth                 :3 ;
    uint32_t                   S                      :1 ;
    uint32_t                   D                      :1 ;
    uint32_t                   SI                     :1 ;
    uint32_t                   DI                     :1 ;
    uint32_t                   Prot                   :3 ;
    uint32_t                   I                      :1 ;
}   GDMA_C0Control;

typedef union {
    uint32_t                   w;
    GDMA_C0Control             b;
}   GDMA_C0Control_U;


// 0x40091110 register ------------------------------------
typedef struct {
    uint32_t                   E                      :1 ;
    uint32_t                   SrcPeri                :4 ;
    uint32_t                   reserved0              :1 ;
    uint32_t                   DestPeri               :4 ;
    uint32_t                   reserved1              :1 ;
    uint32_t                   FLOWC                  :3 ;
    uint32_t                   IE                     :1 ;
    uint32_t                   ITC                    :1 ;
    uint32_t                   L                      :1 ;
    uint32_t                   A                      :1 ;
    uint32_t                   H                      :1 ;
    uint32_t                   reserved2              :13;
}   GDMA_C0Configuration;

typedef union {
    uint32_t                   w;
    GDMA_C0Configuration       b;
}   GDMA_C0Configuration_U;


// 0x40091120 register ------------------------------------
typedef struct {
    uint32_t                   SrcAddr                :32;
}   GDMA_C1SrcAddr;

typedef union {
    uint32_t                   w;
    GDMA_C1SrcAddr             b;
}   GDMA_C1SrcAddr_U;


// 0x40091124 register ------------------------------------
typedef struct {
    uint32_t                   DstAddr                :32;
}   GDMA_C1DestAddr;

typedef union {
    uint32_t                   w;
    GDMA_C1DestAddr            b;
}   GDMA_C1DestAddr_U;


// 0x40091128 register ------------------------------------
typedef struct {
    uint32_t                   LD                     :1 ;
    uint32_t                   reserved0              :1 ;
    uint32_t                   ADDR                   :30;
}   GDMA_C1LLI;

typedef union {
    uint32_t                   w;
    GDMA_C1LLI                 b;
}   GDMA_C1LLI_U;


// 0x4009112C register ------------------------------------
typedef struct {
    uint32_t                   TranSize               :12;
    uint32_t                   SBSize                 :3 ;
    uint32_t                   DBSize                 :3 ;
    uint32_t                   SWidth                 :3 ;
    uint32_t                   DWidth                 :3 ;
    uint32_t                   S                      :1 ;
    uint32_t                   D                      :1 ;
    uint32_t                   SI                     :1 ;
    uint32_t                   DI                     :1 ;
    uint32_t                   Prot                   :3 ;
    uint32_t                   I                      :1 ;
}   GDMA_C1Control;

typedef union {
    uint32_t                   w;
    GDMA_C1Control             b;
}   GDMA_C1Control_U;


// 0x40091130 register ------------------------------------
typedef struct {
    uint32_t                   E                      :1 ;
    uint32_t                   SrcPeri                :4 ;
    uint32_t                   reserved0              :1 ;
    uint32_t                   DestPeri               :4 ;
    uint32_t                   reserved1              :1 ;
    uint32_t                   FLOWC                  :3 ;
    uint32_t                   IE                     :1 ;
    uint32_t                   ITC                    :1 ;
    uint32_t                   L                      :1 ;
    uint32_t                   A                      :1 ;
    uint32_t                   H                      :1 ;
    uint32_t                   reserved2              :13;
}   GDMA_C1Configuration;

typedef union {
    uint32_t                   w;
    GDMA_C1Configuration       b;
}   GDMA_C1Configuration_U;


// 0x40091140 register ------------------------------------
typedef struct {
    uint32_t                   SrcAddr                :32;
}   GDMA_C2SrcAddr;

typedef union {
    uint32_t                   w;
    GDMA_C2SrcAddr             b;
}   GDMA_C2SrcAddr_U;


// 0x40091144 register ------------------------------------
typedef struct {
    uint32_t                   DstAddr                :32;
}   GDMA_C2DestAddr;

typedef union {
    uint32_t                   w;
    GDMA_C2DestAddr            b;
}   GDMA_C2DestAddr_U;


// 0x40091148 register ------------------------------------
typedef struct {
    uint32_t                   LD                     :1 ;
    uint32_t                   reserved0              :1 ;
    uint32_t                   ADDR                   :30;
}   GDMA_C2LLI;

typedef union {
    uint32_t                   w;
    GDMA_C2LLI                 b;
}   GDMA_C2LLI_U;


// 0x4009114C register ------------------------------------
typedef struct {
    uint32_t                   TranSize               :12;
    uint32_t                   SBSize                 :3 ;
    uint32_t                   DBSize                 :3 ;
    uint32_t                   SWidth                 :3 ;
    uint32_t                   DWidth                 :3 ;
    uint32_t                   S                      :1 ;
    uint32_t                   D                      :1 ;
    uint32_t                   SI                     :1 ;
    uint32_t                   DI                     :1 ;
    uint32_t                   Prot                   :3 ;
    uint32_t                   I                      :1 ;
}   GDMA_C2Control;

typedef union {
    uint32_t                   w;
    GDMA_C2Control             b;
}   GDMA_C2Control_U;


// 0x40091150 register ------------------------------------
typedef struct {
    uint32_t                   E                      :1 ;
    uint32_t                   SrcPeri                :4 ;
    uint32_t                   reserved0              :1 ;
    uint32_t                   DestPeri               :4 ;
    uint32_t                   reserved1              :1 ;
    uint32_t                   FLOWC                  :3 ;
    uint32_t                   IE                     :1 ;
    uint32_t                   ITC                    :1 ;
    uint32_t                   L                      :1 ;
    uint32_t                   A                      :1 ;
    uint32_t                   H                      :1 ;
    uint32_t                   reserved2              :13;
}   GDMA_C2Configuration;

typedef union {
    uint32_t                   w;
    GDMA_C2Configuration       b;
}   GDMA_C2Configuration_U;


// 0x40091160 register ------------------------------------
typedef struct {
    uint32_t                   SrcAddr                :32;
}   GDMA_C3SrcAddr;

typedef union {
    uint32_t                   w;
    GDMA_C3SrcAddr             b;
}   GDMA_C3SrcAddr_U;


// 0x40091164 register ------------------------------------
typedef struct {
    uint32_t                   DstAddr                :32;
}   GDMA_C3DestAddr;

typedef union {
    uint32_t                   w;
    GDMA_C3DestAddr            b;
}   GDMA_C3DestAddr_U;


// 0x40091168 register ------------------------------------
typedef struct {
    uint32_t                   LD                     :1 ;
    uint32_t                   reserved0              :1 ;
    uint32_t                   ADDR                   :30;
}   GDMA_C3LLI;

typedef union {
    uint32_t                   w;
    GDMA_C3LLI                 b;
}   GDMA_C3LLI_U;


// 0x4009116C register ------------------------------------
typedef struct {
    uint32_t                   TranSize               :12;
    uint32_t                   SBSize                 :3 ;
    uint32_t                   DBSize                 :3 ;
    uint32_t                   SWidth                 :3 ;
    uint32_t                   DWidth                 :3 ;
    uint32_t                   S                      :1 ;
    uint32_t                   D                      :1 ;
    uint32_t                   SI                     :1 ;
    uint32_t                   DI                     :1 ;
    uint32_t                   Prot                   :3 ;
    uint32_t                   I                      :1 ;
}   GDMA_C3Control;

typedef union {
    uint32_t                   w;
    GDMA_C3Control             b;
}   GDMA_C3Control_U;


// 0x40091170 register ------------------------------------
typedef struct {
    uint32_t                   E                      :1 ;
    uint32_t                   SrcPeri                :4 ;
    uint32_t                   reserved0              :1 ;
    uint32_t                   DestPeri               :4 ;
    uint32_t                   reserved1              :1 ;
    uint32_t                   FLOWC                  :3 ;
    uint32_t                   IE                     :1 ;
    uint32_t                   ITC                    :1 ;
    uint32_t                   L                      :1 ;
    uint32_t                   A                      :1 ;
    uint32_t                   H                      :1 ;
    uint32_t                   reserved2              :13;
}   GDMA_C3Configuration;

typedef union {
    uint32_t                   w;
    GDMA_C3Configuration       b;
}   GDMA_C3Configuration_U;


// 0x40091180 register ------------------------------------
typedef struct {
    uint32_t                   SrcAddr                :32;
}   GDMA_C4SrcAddr;

typedef union {
    uint32_t                   w;
    GDMA_C4SrcAddr             b;
}   GDMA_C4SrcAddr_U;


// 0x40091184 register ------------------------------------
typedef struct {
    uint32_t                   DstAddr                :32;
}   GDMA_C4DestAddr;

typedef union {
    uint32_t                   w;
    GDMA_C4DestAddr            b;
}   GDMA_C4DestAddr_U;


// 0x40091188 register ------------------------------------
typedef struct {
    uint32_t                   LD                     :1 ;
    uint32_t                   reserved0              :1 ;
    uint32_t                   ADDR                   :30;
}   GDMA_C4LLI;

typedef union {
    uint32_t                   w;
    GDMA_C4LLI                 b;
}   GDMA_C4LLI_U;


// 0x4009118C register ------------------------------------
typedef struct {
    uint32_t                   TranSize               :12;
    uint32_t                   SBSize                 :3 ;
    uint32_t                   DBSize                 :3 ;
    uint32_t                   SWidth                 :3 ;
    uint32_t                   DWidth                 :3 ;
    uint32_t                   S                      :1 ;
    uint32_t                   D                      :1 ;
    uint32_t                   SI                     :1 ;
    uint32_t                   DI                     :1 ;
    uint32_t                   Prot                   :3 ;
    uint32_t                   I                      :1 ;
}   GDMA_C4Control;

typedef union {
    uint32_t                   w;
    GDMA_C4Control             b;
}   GDMA_C4Control_U;


// 0x40091190 register ------------------------------------
typedef struct {
    uint32_t                   E                      :1 ;
    uint32_t                   SrcPeri                :4 ;
    uint32_t                   reserved0              :1 ;
    uint32_t                   DestPeri               :4 ;
    uint32_t                   reserved1              :1 ;
    uint32_t                   FLOWC                  :3 ;
    uint32_t                   IE                     :1 ;
    uint32_t                   ITC                    :1 ;
    uint32_t                   L                      :1 ;
    uint32_t                   A                      :1 ;
    uint32_t                   H                      :1 ;
    uint32_t                   reserved2              :13;
}   GDMA_C4Configuration;

typedef union {
    uint32_t                   w;
    GDMA_C4Configuration       b;
}   GDMA_C4Configuration_U;


// 0x400911A0 register ------------------------------------
typedef struct {
    uint32_t                   SrcAddr                :32;
}   GDMA_C5SrcAddr;

typedef union {
    uint32_t                   w;
    GDMA_C5SrcAddr             b;
}   GDMA_C5SrcAddr_U;


// 0x400911A4 register ------------------------------------
typedef struct {
    uint32_t                   DstAddr                :32;
}   GDMA_C5DestAddr;

typedef union {
    uint32_t                   w;
    GDMA_C5DestAddr            b;
}   GDMA_C5DestAddr_U;


// 0x400911A8 register ------------------------------------
typedef struct {
    uint32_t                   LD                     :1 ;
    uint32_t                   reserved0              :1 ;
    uint32_t                   ADDR                   :30;
}   GDMA_C5LLI;

typedef union {
    uint32_t                   w;
    GDMA_C5LLI                 b;
}   GDMA_C5LLI_U;


// 0x400911AC register ------------------------------------
typedef struct {
    uint32_t                   TranSize               :12;
    uint32_t                   SBSize                 :3 ;
    uint32_t                   DBSize                 :3 ;
    uint32_t                   SWidth                 :3 ;
    uint32_t                   DWidth                 :3 ;
    uint32_t                   S                      :1 ;
    uint32_t                   D                      :1 ;
    uint32_t                   SI                     :1 ;
    uint32_t                   DI                     :1 ;
    uint32_t                   Prot                   :3 ;
    uint32_t                   I                      :1 ;
}   GDMA_C5Control;

typedef union {
    uint32_t                   w;
    GDMA_C5Control             b;
}   GDMA_C5Control_U;


// 0x400911B0 register ------------------------------------
typedef struct {
    uint32_t                   E                      :1 ;
    uint32_t                   SrcPeri                :4 ;
    uint32_t                   reserved0              :1 ;
    uint32_t                   DestPeri               :4 ;
    uint32_t                   reserved1              :1 ;
    uint32_t                   FLOWC                  :3 ;
    uint32_t                   IE                     :1 ;
    uint32_t                   ITC                    :1 ;
    uint32_t                   L                      :1 ;
    uint32_t                   A                      :1 ;
    uint32_t                   H                      :1 ;
    uint32_t                   reserved2              :13;
}   GDMA_C5Configuration;

typedef union {
    uint32_t                   w;
    GDMA_C5Configuration       b;
}   GDMA_C5Configuration_U;


// 0x400911C0 register ------------------------------------
typedef struct {
    uint32_t                   SrcAddr                :32;
}   GDMA_C6SrcAddr;

typedef union {
    uint32_t                   w;
    GDMA_C6SrcAddr             b;
}   GDMA_C6SrcAddr_U;


// 0x400911C4 register ------------------------------------
typedef struct {
    uint32_t                   DstAddr                :32;
}   GDMA_C6DestAddr;

typedef union {
    uint32_t                   w;
    GDMA_C6DestAddr            b;
}   GDMA_C6DestAddr_U;


// 0x400911C8 register ------------------------------------
typedef struct {
    uint32_t                   LD                     :1 ;
    uint32_t                   reserved0              :1 ;
    uint32_t                   ADDR                   :30;
}   GDMA_C6LLI;

typedef union {
    uint32_t                   w;
    GDMA_C6LLI                 b;
}   GDMA_C6LLI_U;


// 0x400911CC register ------------------------------------
typedef struct {
    uint32_t                   TranSize               :12;
    uint32_t                   SBSize                 :3 ;
    uint32_t                   DBSize                 :3 ;
    uint32_t                   SWidth                 :3 ;
    uint32_t                   DWidth                 :3 ;
    uint32_t                   S                      :1 ;
    uint32_t                   D                      :1 ;
    uint32_t                   SI                     :1 ;
    uint32_t                   DI                     :1 ;
    uint32_t                   Prot                   :3 ;
    uint32_t                   I                      :1 ;
}   GDMA_C6Control;

typedef union {
    uint32_t                   w;
    GDMA_C6Control             b;
}   GDMA_C6Control_U;


// 0x400911D0 register ------------------------------------
typedef struct {
    uint32_t                   E                      :1 ;
    uint32_t                   SrcPeri                :4 ;
    uint32_t                   reserved0              :1 ;
    uint32_t                   DestPeri               :4 ;
    uint32_t                   reserved1              :1 ;
    uint32_t                   FLOWC                  :3 ;
    uint32_t                   IE                     :1 ;
    uint32_t                   ITC                    :1 ;
    uint32_t                   L                      :1 ;
    uint32_t                   A                      :1 ;
    uint32_t                   H                      :1 ;
    uint32_t                   reserved2              :13;
}   GDMA_C6Configuration;

typedef union {
    uint32_t                   w;
    GDMA_C6Configuration       b;
}   GDMA_C6Configuration_U;


// 0x400911E0 register ------------------------------------
typedef struct {
    uint32_t                   SrcAddr                :32;
}   GDMA_C7SrcAddr;

typedef union {
    uint32_t                   w;
    GDMA_C7SrcAddr             b;
}   GDMA_C7SrcAddr_U;


// 0x400911E4 register ------------------------------------
typedef struct {
    uint32_t                   DstAddr                :32;
}   GDMA_C7DestAddr;

typedef union {
    uint32_t                   w;
    GDMA_C7DestAddr            b;
}   GDMA_C7DestAddr_U;


// 0x400911E8 register ------------------------------------
typedef struct {
    uint32_t                   LD                     :1 ;
    uint32_t                   reserved0              :1 ;
    uint32_t                   ADDR                   :30;
}   GDMA_C7LLI;

typedef union {
    uint32_t                   w;
    GDMA_C7LLI                 b;
}   GDMA_C7LLI_U;


// 0x400911EC register ------------------------------------
typedef struct {
    uint32_t                   TranSize               :12;
    uint32_t                   SBSize                 :3 ;
    uint32_t                   DBSize                 :3 ;
    uint32_t                   SWidth                 :3 ;
    uint32_t                   DWidth                 :3 ;
    uint32_t                   S                      :1 ;
    uint32_t                   D                      :1 ;
    uint32_t                   SI                     :1 ;
    uint32_t                   DI                     :1 ;
    uint32_t                   Prot                   :3 ;
    uint32_t                   I                      :1 ;
}   GDMA_C7Control;

typedef union {
    uint32_t                   w;
    GDMA_C7Control             b;
}   GDMA_C7Control_U;


// 0x400911F0 register ------------------------------------
typedef struct {
    uint32_t                   E                      :1 ;
    uint32_t                   SrcPeri                :4 ;
    uint32_t                   reserved0              :1 ;
    uint32_t                   DestPeri               :4 ;
    uint32_t                   reserved1              :1 ;
    uint32_t                   FLOWC                  :3 ;
    uint32_t                   IE                     :1 ;
    uint32_t                   ITC                    :1 ;
    uint32_t                   L                      :1 ;
    uint32_t                   A                      :1 ;
    uint32_t                   H                      :1 ;
    uint32_t                   reserved2              :13;
}   GDMA_C7Configuration;

typedef union {
    uint32_t                   w;
    GDMA_C7Configuration       b;
}   GDMA_C7Configuration_U;


//---------------------------------------------------------
// GDMA Register Map
//---------------------------------------------------------
typedef struct {
    volatile GDMA_IntStatus_U                  IntStatus                ; // 0x000
    volatile GDMA_IntTCStatus_U                IntTCStatus              ; // 0x004
    volatile GDMA_IntTCClear_U                 IntTCClear               ; // 0x008
    volatile GDMA_IntErrorStatus_U             IntErrorStatus           ; // 0x00c
    volatile GDMA_IntErrorClr_U                IntErrorClr              ; // 0x010
    volatile GDMA_RawIntTCStatus_U             RawIntTCStatus           ; // 0x014
    volatile GDMA_RawIntErrorStatus_U          RawIntErrorStatus        ; // 0x018
    volatile GDMA_EnbldChns_U                  EnbldChns                ; // 0x01c
    volatile GDMA_SoftBReq_U                   SoftBReq                 ; // 0x020
    volatile GDMA_SoftSReq_U                   SoftSReq                 ; // 0x024
    volatile GDMA_SoftLBReq_U                  SoftLBReq                ; // 0x028
    volatile GDMA_SoftLSReq_U                  SoftLSReq                ; // 0x02c
    volatile GDMA_Configuration_U              Configuration            ; // 0x030
    volatile GDMA_Sync_U                       Sync                     ; // 0x034
    volatile uint32_t                            RESERVED0[50]            ; // 
    volatile GDMA_C0SrcAddr_U                  C0SrcAddr                ; // 0x100
    volatile GDMA_C0DestAddr_U                 C0DestAddr               ; // 0x104
    volatile GDMA_C0LLI_U                      C0LLI                    ; // 0x108
    volatile GDMA_C0Control_U                  C0Control                ; // 0x10c
    volatile GDMA_C0Configuration_U            C0Configuration          ; // 0x110
    volatile uint32_t                            RESERVED1[3]             ; // 
    volatile GDMA_C1SrcAddr_U                  C1SrcAddr                ; // 0x120
    volatile GDMA_C1DestAddr_U                 C1DestAddr               ; // 0x124
    volatile GDMA_C1LLI_U                      C1LLI                    ; // 0x128
    volatile GDMA_C1Control_U                  C1Control                ; // 0x12c
    volatile GDMA_C1Configuration_U            C1Configuration          ; // 0x130
    volatile uint32_t                            RESERVED2[3]             ; // 
    volatile GDMA_C2SrcAddr_U                  C2SrcAddr                ; // 0x140
    volatile GDMA_C2DestAddr_U                 C2DestAddr               ; // 0x144
    volatile GDMA_C2LLI_U                      C2LLI                    ; // 0x148
    volatile GDMA_C2Control_U                  C2Control                ; // 0x14c
    volatile GDMA_C2Configuration_U            C2Configuration          ; // 0x150
    volatile uint32_t                            RESERVED3[3]             ; // 
    volatile GDMA_C3SrcAddr_U                  C3SrcAddr                ; // 0x160
    volatile GDMA_C3DestAddr_U                 C3DestAddr               ; // 0x164
    volatile GDMA_C3LLI_U                      C3LLI                    ; // 0x168
    volatile GDMA_C3Control_U                  C3Control                ; // 0x16c
    volatile GDMA_C3Configuration_U            C3Configuration          ; // 0x170
    volatile uint32_t                            RESERVED4[3]             ; // 
    volatile GDMA_C4SrcAddr_U                  C4SrcAddr                ; // 0x180
    volatile GDMA_C4DestAddr_U                 C4DestAddr               ; // 0x184
    volatile GDMA_C4LLI_U                      C4LLI                    ; // 0x188
    volatile GDMA_C4Control_U                  C4Control                ; // 0x18c
    volatile GDMA_C4Configuration_U            C4Configuration          ; // 0x190
    volatile uint32_t                            RESERVED5[3]             ; // 
    volatile GDMA_C5SrcAddr_U                  C5SrcAddr                ; // 0x1a0
    volatile GDMA_C5DestAddr_U                 C5DestAddr               ; // 0x1a4
    volatile GDMA_C5LLI_U                      C5LLI                    ; // 0x1a8
    volatile GDMA_C5Control_U                  C5Control                ; // 0x1ac
    volatile GDMA_C5Configuration_U            C5Configuration          ; // 0x1b0
    volatile uint32_t                            RESERVED6[3]             ; // 
    volatile GDMA_C6SrcAddr_U                  C6SrcAddr                ; // 0x1c0
    volatile GDMA_C6DestAddr_U                 C6DestAddr               ; // 0x1c4
    volatile GDMA_C6LLI_U                      C6LLI                    ; // 0x1c8
    volatile GDMA_C6Control_U                  C6Control                ; // 0x1cc
    volatile GDMA_C6Configuration_U            C6Configuration          ; // 0x1d0
    volatile uint32_t                            RESERVED7[3]             ; // 
    volatile GDMA_C7SrcAddr_U                  C7SrcAddr                ; // 0x1e0
    volatile GDMA_C7DestAddr_U                 C7DestAddr               ; // 0x1e4
    volatile GDMA_C7LLI_U                      C7LLI                    ; // 0x1e8
    volatile GDMA_C7Control_U                  C7Control                ; // 0x1ec
    volatile GDMA_C7Configuration_U            C7Configuration          ; // 0x1f0
} GDMA_Type;

#ifdef __cplusplus
}
#endif

#endif /* __REG_GDMA_H__ */
