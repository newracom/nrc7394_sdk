#ifndef __DRV_SDIO_H__
#define __DRV_SDIO_H__

#ifdef __cplusplus
extern "C"{
#endif

#define DRV_SDIO_IOCTL_OPT_GET								0
#define DRV_SDIO_IOCTL_OPT_REGISTER_IRQ_HANDLER				1

#define DRV_SDIO_IOCTL_OPT_SET_ADMA_SYS_ADDR				10
#define DRV_SDIO_IOCTL_OPT_SET_AHB_TRANSCOUNT				11
#define DRV_SDIO_IOCTL_OPT_SET_RDDATRDY						12
#define DRV_SDIO_IOCTL_OPT_SET_IOR							13
#define DRV_SDIO_IOCTL_OPT_SET_ARM_GP_REG					14
#define DRV_SDIO_IOCTL_OPT_GET_ARM_GP_REG					15

//#define DRV_SDIO_IOCTL_OPT_IRQ_FLAG_FN0_INT					100		
#define DRV_SDIO_IOCTL_OPT_IRQ_FLAG_FN0_ADMA_ERR			101
#define DRV_SDIO_IOCTL_OPT_IRQ_FLAG_FN0_ADMA_INT			102
#define DRV_SDIO_IOCTL_OPT_IRQ_FLAG_FN0_ADMA_END			103
#define DRV_SDIO_IOCTL_OPT_IRQ_FLAG_FN0_RD_ERR				104
#define DRV_SDIO_IOCTL_OPT_IRQ_FLAG_FN0_RD_OVR				105
#define DRV_SDIO_IOCTL_OPT_IRQ_FLAG_FN0_RD_START			106
#define DRV_SDIO_IOCTL_OPT_IRQ_FLAG_FN0_WR_OVR				107
#define DRV_SDIO_IOCTL_OPT_IRQ_FLAG_FN0_WR_START			108
//#define DRV_SDIO_IOCTL_OPT_IRQ_FLAG_CMD19_RD_OVR			109
//#define DRV_SDIO_IOCTL_OPT_IRQ_FLAG_CMD19_RD_START			110
#define DRV_SDIO_IOCTL_OPT_IRQ_FLAG_VOLT_SW_CMD				111
#define DRV_SDIO_IOCTL_OPT_IRQ_FLAG_CMD52_SOFT_RST			112

//#define DRV_SDIO_IOCTL_OPT_IRQ_FLAG_FN1_INT					113
#define DRV_SDIO_IOCTL_OPT_IRQ_FLAG_FN1_EN					114
#define DRV_SDIO_IOCTL_OPT_IRQ_FLAG_ADMA_ERR				115
#define DRV_SDIO_IOCTL_OPT_IRQ_FLAG_ADMA_INT				116
#define DRV_SDIO_IOCTL_OPT_IRQ_FLAG_RESUME					117
#define DRV_SDIO_IOCTL_OPT_IRQ_FLAG_FN1_SUSPENDED			118
#define DRV_SDIO_IOCTL_OPT_IRQ_FLAG_ADMA_END_INT			119
#define DRV_SDIO_IOCTL_OPT_IRQ_FLAG_FN1_WR_START			120
#define DRV_SDIO_IOCTL_OPT_IRQ_FLAG_FN1_RD_START			121
#define DRV_SDIO_IOCTL_OPT_IRQ_FLAG_FN1_ACK					122
#define DRV_SDIO_IOCTL_OPT_IRQ_FLAG_FN1_MSG_RDY				123
#define DRV_SDIO_IOCTL_OPT_IRQ_FLAG_FN1_RST					124
#define DRV_SDIO_IOCTL_OPT_IRQ_FLAG_FN1_RD_ERR				125
#define DRV_SDIO_IOCTL_OPT_IRQ_FLAG_FN1_RD_OVR				126
#define DRV_SDIO_IOCTL_OPT_IRQ_FLAG_FN1_WR_OVR				127
/******************************************************************************/
#define DRV_SDIO_IOCTL_OPT_IRQ_FLAG_RESET					  1
/****************************************************************************/

enum drv_sdio_id_t{
	drv_sdio_id0,
	drv_sdio_id_max,
};

typedef struct DRV_SDIO_HANDLE_T * drv_sdio_handle_t;
struct drv_sdio_t;
struct drv_sdio_ops_t;
struct drv_sdio_ioctl_t;

struct drv_sdio_ops_t{
	int32_t (*close)(struct drv_sdio_t* );
	int32_t (*ioctl)(struct drv_sdio_t*, uint32_t, unsigned int);
};

union drv_sdio_ioctl_flag_t{
	uint32_t w;
	struct{
		uint32_t ior					: 1;
		uint32_t rddatready				: 1;
	//	uint32_t fn0_int				: 1;
		uint32_t fn0_adma_err			: 1;
		uint32_t fn0_adma_int			: 1;
		uint32_t fn0_adma_end			: 1;
		uint32_t fn0_rd_err				: 1;
		uint32_t fn0_rd_ovr				: 1;
		uint32_t fn0_rd_start			: 1;
		uint32_t fn0_wr_ovr				: 1;
		uint32_t fn0_wr_start			: 1;
	//	uint32_t cmd19_rd_ovr			: 1;
	//	uint32_t cmd19_rd_start			: 1;
		uint32_t volt_sw_cmd			: 1;
		uint32_t cmd52_soft_rst			: 1;
		
	//	uint32_t fn1_int				: 1;
		uint32_t fn1_en					: 1;
		uint32_t adma_err				: 1;
		uint32_t adma_int				: 1;
		uint32_t resume					: 1;
		uint32_t fn1_suspended			: 1;
		uint32_t adma_end_int			: 1;
		uint32_t fn1_wr_start			: 1;
		uint32_t fn1_rd_start			: 1;
		uint32_t fn1_ack				: 1;
		uint32_t fn1_msg_rdy			: 1;
		uint32_t fn1_rst				: 1;
		uint32_t fn1_rd_err				: 1;
		uint32_t fn1_rd_ovr				: 1;
		uint32_t fn1_wr_ovr				: 1;

	}b;
};

struct drv_sdio_ioctl_t{
	uint32_t adma_sys_addr;
	uint32_t ahb_transcount;
	uint32_t arg_bcnt;
	uint32_t blksize;
	uint32_t arm_gp_reg;
	uint32_t sdhost_gp_reg;
	
	union drv_sdio_ioctl_flag_t flag;
};

struct DRV_SDIO_HANDLE_T{
	enum drv_sdio_id_t id;
	struct drv_sdio_ioctl_t ioctl;
};

struct drv_sdio_t{
	drv_sdio_handle_t handle;
	const struct drv_sdio_ops_t *ops;
	void (*handle_irq)(void);
};

int32_t drv_sdio_open( enum drv_sdio_id_t id, drv_sdio_handle_t *handle );
int32_t drv_sdio_ioctl( drv_sdio_handle_t handle, uint32_t opt, unsigned int val );

int32_t drv_sdio_register_driver( struct drv_sdio_t *sdio );


#ifdef __cplusplus
}
#endif

#endif

