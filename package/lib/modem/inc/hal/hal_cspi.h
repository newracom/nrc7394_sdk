#ifndef __HAL_CSPI_NRC7392_H__
#define __HAL_CSPI_NRC7392_H__

struct host_interface_ops *hal_cspi_7394_ops();
#if defined(NRC_ROMLIB)
void cspi_reset(int que);
#endif

#endif //__HAL_CSPI_NRC7392_H__
