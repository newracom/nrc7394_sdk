#ifndef __DRV_UART_H__
#define __DRV_UART_H__

#ifdef __cplusplus
extern "C"{
#endif

#define DRV_UART_IOCTL_OPT_STARTUP								0x0
#define DRV_UART_IOCTL_OPT_SHUTDOWN								0x1
#define DRV_UART_IOCTL_OPT_REGISTER_HANLDE_IRQ					0x10

#define DRV_UART_IOCTL_OPT_TX_IRQ_CTRL							0x100
#define DRV_UART_IOCTL_OPT_RX_IRQ_CTRL							0x101

#define DRV_UART_IOCTL_OPT_GPIO_TX								0x300
#define DRV_UART_IOCTL_OPT_GPIO_RX								0x301
#define DRV_UART_IOCTL_OPT_GPIO_CTS								0x302
#define DRV_UART_IOCTL_OPT_GPIO_RTS								0x303
/*****************************************************************************/


enum drv_uart_id_t{
	drv_uart_id0,
	drv_uart_id1,
	drv_uart_id_MAX
};

struct drv_uart_ops_t;
struct drv_uart_port_t;
struct drv_uart_ioctl_t;

struct drv_uart_gpio_t{
	uint32_t tx;
	uint32_t rx;
};

struct drv_uart_ioctl_t{
	uint32_t enable;
	uint32_t cts_enable;
	uint32_t rts_enable;
	uint32_t tx_irq_enable;
	uint32_t rx_irq_enable;
	uint32_t clk;
	uint32_t clk_div;
	uint32_t baudrate;
	uint32_t gp_txgroup : 16;
	uint32_t gp_txpin : 16;
	uint32_t gp_rxgroup : 16;
	uint32_t gp_rxpin : 16;
	uint32_t gp_ctsgroup : 16;
	uint32_t gp_ctspin : 16;
	uint32_t gp_rtsgroup : 16;
	uint32_t gp_rtspin : 16;
};

struct drv_uart_ops_t{
	uint32_t	(*close)(struct drv_uart_port_t *);
	uint32_t	(*startup)(struct drv_uart_port_t *);
	void		(*shutdown)(struct drv_uart_port_t *);
	void		(*ioctl)(struct drv_uart_port_t *, uint32_t, unsigned int );
	void		(*poll_put_char)(struct drv_uart_port_t *, uint32_t);
	uint32_t	(*poll_get_char)(struct drv_uart_port_t *);
	void		(*enable_irq)(struct drv_uart_port_t *,uint32_t opt, uint32_t enabled);
};

struct drv_uart_port_t{
	uint32_t 	line;
	struct 		drv_uart_ioctl_t ioctl;
	const	 	struct drv_uart_ops_t	*ops;
	void		(*handle_irq)(void);
};

/** 
  \brief		uart commnunication driver open function
  \details		
  \param [in]	id
  \return		ret
*/
uint32_t drv_uart_open( enum drv_uart_id_t id);

/** 
  \brief		uart commnunication driver close function
  \details		
  \param [in]	id
  \return		ret
*/
uint32_t drv_uart_close( enum drv_uart_id_t id);

/** 
  \brief		uart commnunication driver read function
  \details		
  \param [in]	id
  \param [in]	addr
  \param [in]	buf
  \return		ret
*/
uint32_t drv_uart_read( enum drv_uart_id_t id, uint32_t *dat);

/** 
  \brief		uart commnunication driver write function
  \details		
  \param [in]	id
  \param [in]	addr
  \param [in]	buf
  \return		ret
*/
uint32_t drv_uart_write( enum drv_uart_id_t id, uint32_t dat);

/** 
  \brief		uart commnunication driver input output control function
  \details		critical section
  \param [in]	id
  \param [in]	opt This parameter can be one or multiple of the following values:
				@arg @ref DRV_UART_IOCTL_OPT_STARTUP			
				@arg @ref DRV_UART_IOCTL_OPT_SHUTDOWN			
				@arg @ref DRV_UART_IOCTL_OPT_REGISTER_HANLDE_IRQ
				@arg @ref DRV_UART_IOCTL_OPT_TX_IRQ_CTRL		
				@arg @ref DRV_UART_IOCTL_OPT_RX_IRQ_CTRL		
				@arg @ref DRV_UART_IOCTL_OPT_GPIO_TX			
				@arg @ref DRV_UART_IOCTL_OPT_GPIO_RX			
 				@arg @ref DRV_UART_IOCTL_OPT_GPIO_CTS			
 				@arg @ref DRV_UART_IOCTL_OPT_GPIO_RTS			
  \param [in]	val
  \return		ret
*/
struct drv_uart_ioctl_t drv_uart_ioctl( enum drv_uart_id_t id, uint32_t opt, unsigned int val);

/** 
  \brief		uart commnunication driver registration function
  \details		
  \param [in]	uart_port
  \return		ret
*/
uint32_t drv_uart_register_driver( struct drv_uart_port_t *uart_port );

#ifdef __cplusplus
}
#endif

#endif

