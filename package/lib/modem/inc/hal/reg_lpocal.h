/*********************************************************************/
/*    Newracom Library / IP Product                                  */
/*    Product Name :                                                 */
/*    Version      :                                                 */
/*    Author       :                                                 */
/*    Update       :                                                 */
/*********************************************************************/

#ifndef __REG_LPOCAL_H__
#define __REG_LPOCAL_H__

#ifdef __cplusplus
extern "C"{
#endif

// 0x4004B000 register ------------------------------------
typedef struct {
    uint32_t           EN          :1 ;
    uint32_t           DUR         :2 ;
    uint32_t           INTEN       :1 ;
    uint32_t           WAIT_DUR    :4 ;
    uint32_t           reserved0   :7 ;
    uint32_t           FST_EN      :1 ;
    uint32_t           reserved1   :16;
}   LPOCAL_CTRL;

typedef union {
    uint32_t           w;
    LPOCAL_CTRL        b;
}   LPOCAL_CTRL_U;


// 0x4004B004 register ------------------------------------
typedef struct {
    uint32_t           LOCKCMP     :13;
    uint32_t           reserved0   :19;
}   LPOCAL_LOCKCMP;

typedef union {
    uint32_t           w;
    LPOCAL_LOCKCMP     b;
}   LPOCAL_LOCKCMP_U;


// 0x4004B008 register ------------------------------------
typedef struct {
    uint32_t           MANCAL      :13;
    uint32_t           MANLD       :1 ;
    uint32_t           reserved0   :18;
}   LPOCAL_LOAD;

typedef union {
    uint32_t           w;
    LPOCAL_LOAD        b;
}   LPOCAL_LOAD_U;


// 0x4004B00C register ------------------------------------
typedef struct {
    uint32_t           INT         :1 ;
    uint32_t           BUSY        :1 ;
    uint32_t           reserved0   :30;
}   LPOCAL_STATUS;

typedef union {
    uint32_t           w;
    LPOCAL_STATUS      b;
}   LPOCAL_STATUS_U;


//---------------------------------------------------------
// LPOCAL Register Map
//---------------------------------------------------------
typedef struct {
    volatile LPOCAL_CTRL_U             CTRL           ; // 0x000
    volatile LPOCAL_LOCKCMP_U          LOCKCMP        ; // 0x004
    volatile LPOCAL_LOAD_U             LOAD           ; // 0x008
    volatile LPOCAL_STATUS_U           STATUS         ; // 0x00c
} LPOCAL_Type;

#ifdef __cplusplus
}
#endif

#endif /* __REG_LPOCAL_H__ */
