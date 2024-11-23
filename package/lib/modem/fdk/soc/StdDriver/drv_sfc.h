#ifndef __DRV_SFC_H__
#define __DRV_SFC_H__

#ifdef __cplusplus
extern "C"{
#endif

#define DRV_SFC_IOCTL_OPT_GET										0
#define DRV_SFC_IOCTL_OPT_READ_MODE									1
#define DRV_SFC_IOCTL_OPT_BUS_READY_CTRL							2
#define DRV_SFC_IOCTL_OPT_CLOCK										3
#define DRV_SFC_IOCTL_OPT_CHIPSELECT_PULSEWIDTH						4
#define DRV_SFC_IOCTL_OPT_WIP_PERIOD								5
#define DRV_SFC_IOCTL_OPT_PAGEWRITE									6

#define DRV_SFC_IOCTL_OPT_ERASE										10
#define DRV_SFC_IOCTL_OPT_ERASE_SIZE								11

#define DRV_SFC_IOCTL_OPT_POWERDOWN									20
#define DRV_SFC_IOCTL_OPT_POWERUP									21
/******************************************************************************/
#define DRV_SFC_IOCTL_OPT_READ_MODE_SINGLE							0
#define DRV_SFC_IOCTL_OPT_READ_MODE_DUAL							1
#define DRV_SFC_IOCTL_OPT_READ_MODE_QUAD							2

#define DRV_SFC_IOCTL_OPT_BUS_READY_CTRL_AUTO						0
#define DRV_SFC_IOCTL_OPT_BUS_READY_CTRL_MANUAL						1

//#define DRV_SFC_IOCTL_OPT_CLOCK_32Mhz								32000000

#define DRV_SFC_IOCTL_OPT_CHIPSELECT_PULSEWIDTH_CLOCK_16			0xF

#define DRV_SFC_IOCTL_OPT_PAGEWRITE_DISABLE							0
#define DRV_SFC_IOCTL_OPT_PAGEWRITE_ENABLE							1

#define DRV_SFC_IOCTL_OPT_ERASE_SIZE_SECTOR							0
#define DRV_SFC_IOCTL_OPT_ERASE_SIZE_BLOCK							1
#define DRV_SFC_IOCTL_OPT_ERASE_SIZE_ALL							2

struct drv_sfc_ioctl_t;
struct drv_sfc_ops_t;
struct drv_sfc_t;

enum drv_sfc_id_t{
	drv_sfc_id0,
	drv_sfc_id_max,
};

struct drv_sfc_ioctl_t{
	uint32_t jadecid;
	uint32_t size;
	uint32_t read_mode;
	uint32_t bus_ready_control;
	uint32_t clock;
	uint32_t chipselect_pulsewidth;
	uint32_t wip_period;
	uint32_t page_write;
	uint32_t erase_size;
};

struct drv_sfc_ops_t{
	uint32_t (*close)(struct drv_sfc_t *);
	void (*write)(struct drv_sfc_t *, uint32_t , uint8_t *, uint32_t );
	void (*erase)(struct drv_sfc_t *, uint32_t , uint32_t );
	void (*ioctl)(struct drv_sfc_t *, uint32_t , unsigned int );
};

struct drv_sfc_t{
	int32_t id;
	struct drv_sfc_ioctl_t ioctl;
	const struct drv_sfc_ops_t *ops;
};

/** 
  \brief		serial flash controller driver open function
  \details		
  \param [in]	id
  \return		ret
*/
uint32_t drv_sfc_open( enum drv_sfc_id_t id );

/** 
  \brief		serial flash controller driver close function
  \details		
  \param [in]	id
  \return		ret
*/
uint32_t drv_sfc_close( enum drv_sfc_id_t id );

/** 
  \brief		serial flash controller driver write function
  \details		
  \param [in]	id
  \param [in]	addr
  \param [in]	buf
  \return		ret
*/
uint32_t drv_sfc_write(enum drv_sfc_id_t id , uint32_t addr, uint8_t *buf, uint32_t size);

/** 
  \brief		serial flash controller driver input output control function
  \details		critical section
  \param [in]	id
  \param [in]	opt This parameter can be one or multiple of the following values:
				@arg @ref DRV_SFC_IOCTL_OPT_READ_MODE
				@arg @ref DRV_SFC_IOCTL_OPT_BUS_READY_CTRL
				@arg @ref DRV_SFC_IOCTL_OPT_CLOCK
				@arg @ref DRV_SFC_IOCTL_OPT_CHIPSELECT_PULSEWIDTH
				@arg @ref DRV_SFC_IOCTL_OPT_WIP_PERIOD
				@arg @ref DRV_SFC_IOCTL_OPT_PAGEWRITE
				@arg @ref DRV_SFC_IOCTL_OPT_ERASE_SIZE
   \param [in]	val
  \return		ret
*/
struct drv_sfc_ioctl_t drv_sfc_ioctl(enum drv_sfc_id_t id, uint32_t opt, unsigned int val);

/** 
  \brief		serial flash controller driver registration function
  \details		
  \param [in]	sfc
  \return		ret
*/
uint32_t drv_sfc_register_driver(struct drv_sfc_t *sfc);

#ifdef __cplusplus
}
#endif

#endif
