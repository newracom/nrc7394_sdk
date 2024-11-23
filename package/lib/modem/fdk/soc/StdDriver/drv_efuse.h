#ifndef __DRV_EFUSE_H__
#define __DRV_EFUSE_H__

#ifdef __cplusplus
extern "C"{
#endif

#define DRV_EFUSE_IOCTL_OPT_GET_SETUP						0
#define DRV_EFUSE_IOCTL_OPT_CONTROL_MODE					1
#define DRV_EFUSE_IOCTL_OPT_STARTUP							2
#define DRV_EFUSE_IOCTL_OPT_SHUTDOWN						3

/******************************************************************************/

#define DRV_EFUSE_IOCTL_OPT_CONTROL_MODE_AUTO				0xBA
#define DRV_EFUSE_IOCTL_OPT_CONTROL_MODE_MANUAL				0xAB
uint8_t drv_efuse_compute_crc7(const uint8_t * data, uint8_t len);

enum drv_efuse_id_t{
	drv_efuse_id0,
	drv_efuse_id_max,
};
	
struct drv_efuse_t;
struct drv_efuse_ops_t;
struct drv_efuse_ioctl_t;

struct drv_efuse_ops_t
{
	uint32_t (*close)(struct drv_efuse_t *);
	void (*read)(struct drv_efuse_t *, uint32_t , uint32_t *);
	void (*write)(struct drv_efuse_t *, uint32_t, uint32_t *);
	void (*startup)(struct drv_efuse_t *);
	void (*shutdown)(struct drv_efuse_t *);
	void (*ioctl)(struct drv_efuse_t *, uint32_t, unsigned int );
};

struct drv_efuse_ioctl_t
{
	int32_t enable;
	uint32_t control_mode;
};

struct drv_efuse_t
{
	int32_t	id;
	struct drv_efuse_ioctl_t ioctl;
	const struct drv_efuse_ops_t *ops;
};

/** 
  \brief		efuse driver open function
  \details		
  \param [in]	id
  \return		ret
*/
uint32_t drv_efuse_open(enum drv_efuse_id_t id);

/** 
  \brief		efuse driver close function
  \details		
  \param [in]	id
  \return		ret
*/
uint32_t drv_efuse_close(enum drv_efuse_id_t id);

/** 
  \brief		efuse driver read function
  \details		
  \param [in]	id
  \param [in]	addr
  \param [in]	buf
  \return		ret
*/
uint32_t drv_efuse_read(enum drv_efuse_id_t id, uint32_t addr, uint32_t *buf);

/** 
  \brief		efuse driver write function
  \details		
  \param [in]	id
  \param [in]	addr
  \param [in]	buf
  \return		ret
*/
uint32_t drv_efuse_write(enum drv_efuse_id_t id, uint32_t addr, uint32_t *buf);


/** 
  \brief		efuse driver input output control function
  \details		critical section
  \param [in]	id
  \param [in]	opt This parameter can be one or multiple of the following values:
				@arg @ref DRV_EFUSE_IOCTL_OPT_GET_SETUP	
				@arg @ref DRV_EFUSE_IOCTL_OPT_CONTROL_MODE
				@arg @ref DRV_EFUSE_IOCTL_OPT_STARTUP		
				@arg @ref DRV_EFUSE_IOCTL_OPT_SHUTDOWN	
  \param [in]	val
  \return		ret
*/
struct drv_efuse_ioctl_t drv_efuse_ioctl(enum drv_efuse_id_t id, uint32_t opt, unsigned int val);


/** 
  \brief		efuse driver registration function
  \details		
  \param [in]	efuse
  \return		ret
*/
uint32_t drv_efuse_register_driver(struct drv_efuse_t * efuse);

#ifdef __cplusplus
}
#endif

#endif


