#ifndef __DRV_PMSSPI_H__
#define __DRV_PMSSPI_H__

#ifdef __cplusplus
extern "C"{
#endif

#define DRV_PMSSPI_IOCTL_OPT_GET_SETUP					0
#define DRV_PMSSPI_IOCTL_OPT_SHUTDOWN					1
#define DRV_PMSSPI_IOCTL_OPT_STARTUP					2

enum drv_pmsspi_id_t{
	drv_pmsspi_id0,
	drv_pmsspi_id_max,
};

struct drv_pmsspi_t;
struct drv_pmsspi_ops_t;
struct drv_pmsspi_ioctl_t;

struct drv_pmsspi_ioctl_t{
	uint32_t enable;
};

struct drv_pmsspi_t{
	uint32_t id;
	struct drv_pmsspi_ioctl_t ioctl;
	const struct drv_pmsspi_ops_t *ops;
};

struct drv_pmsspi_ops_t{
	uint32_t (*close)(struct drv_pmsspi_t *);
	void (*write)(struct drv_pmsspi_t *, uint32_t, uint32_t *);
	void (*read)(struct drv_pmsspi_t *, uint32_t, uint32_t *);
	void (*startup)(struct drv_pmsspi_t *);
	void (*shutdown)(struct drv_pmsspi_t *);
};


/** 
  \brief		pmsspi driver open function
  \details		
  \param [in]	id
  \return		ret
*/
uint32_t drv_pmsspi_open(enum drv_pmsspi_id_t id);

/** 
  \brief		pmsspi driver close function
  \details		
  \param [in]	id
  \return		ret
*/
uint32_t drv_pmsspi_close(enum drv_pmsspi_id_t id);

/** 
  \brief		pmsspi driver read function
  \details		
  \param [in]	id
  \param [in]	addr
  \param [in]	buf
  \return		ret
 */

uint32_t drv_pmsspi_read(enum drv_pmsspi_id_t id, uint32_t addr, uint32_t *buf);

/** 
  \brief		pmsspi driver write function
  \details		
  \param [in]	id
  \param [in]	addr
  \param [in]	buf
  \return		ret
 */
uint32_t drv_pmsspi_write(enum drv_pmsspi_id_t id, uint32_t addr, uint32_t *buf);

/** 
  \brief		pmsspi driver input output control function
  \details		critical section
  \param [in]	id
  \param [in]	opt This parameter can be one or multiple of the following values:
				@arg @ref DRV_PMSSPI_IOCTL_OPT_GET_SETUP
				@arg @ref DRV_PMSSPI_IOCTL_OPT_SHUTDOWN	
				@arg @ref DRV_PMSSPI_IOCTL_OPT_STARTUP	
   \param [in]	val
  \return		ret
*/
struct drv_pmsspi_ioctl_t drv_pmsspi_ioctl(enum drv_pmsspi_id_t id, uint32_t opt, unsigned int val);


/** 
  \brief		pmsspi driver registration function
  \details		
  \param [in]	pmsspi
  \return		ret
*/
uint32_t drv_pmsspi_register_driver(struct drv_pmsspi_t * pmsspi);


#ifdef __cplusplus
}
#endif

#endif


