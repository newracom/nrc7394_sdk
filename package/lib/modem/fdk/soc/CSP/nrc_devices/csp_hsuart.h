#ifndef __CSP_HSUART_H__
#define __CSP_HSUART_H__

#ifdef __cplusplus
extern "C"{
#endif

typedef enum{
	eHSUART_ID0,
	eHSUART_ID1,
	eHSUART_MAX
}eHSUART_ID_t;

void __csp_HSUART_Initialize(void);
__RAM_FUNC void __csp_HSUART_TransferData(eHSUART_ID_t eID, uint8_t ucData);
__RAM_FUNC void __csp_HSUART_TransferString(eHSUART_ID_t eID, uint8_t * ucData);


#ifdef __cplusplus
}
#endif

#endif
