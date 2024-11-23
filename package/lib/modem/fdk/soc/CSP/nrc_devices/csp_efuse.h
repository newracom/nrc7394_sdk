#ifndef __CSP_EFUSE_H__
#define __CSP_EFUSE_H__

#ifdef __cplusplus
extern "C"{
#endif

#define EFUSE_CHECK_MAX			4

typedef struct{
	uint8_t CLDO				: 4;
	uint8_t VREFIO				: 4;
}st_efuse00_t;

typedef union{
	st_efuse00_t	b;
	uint8_t			w;
}un_efuse00_t;

typedef struct{
	uint8_t VMREF07				: 5;
	uint8_t VER					: 3;
}st_efuse01_t;

typedef union{
	st_efuse01_t	b;
	uint8_t			w;
}un_efuse01_t;

typedef struct{
	uint8_t IBIAS				: 4;
	uint8_t VSLREF07			: 4;
}st_efuse02_t;

typedef union{
	st_efuse02_t	b;
	uint8_t			w;
}un_efuse02_t;

typedef struct{
	uint8_t VSLREF06			: 4;
	uint8_t VSLIOLDO			: 4;
}st_efuse03_t;

typedef union{
	st_efuse03_t	b;
	uint8_t			w;
}un_efuse03_t;

typedef struct{
	uint8_t VSLCLDO				: 4;
	uint8_t RRF					: 4;
}st_efuse04_t;

typedef union{
	st_efuse04_t	b;
	uint8_t			w;
}un_efuse04_t;

typedef struct{
	uint8_t BCLK				: 5;
	uint8_t reserved0			: 3;
}st_efuse05_t;

typedef union{
	st_efuse05_t	b;
	uint8_t			w;
}un_efuse05_t;

typedef struct{
	uint8_t VBUCK				: 4;
	uint8_t RFLDO_TR			: 4;
}st_efuse06_t;

typedef union{
	st_efuse06_t	b;
	uint8_t			w;
}un_efuse06_t;

typedef struct{
	uint8_t VCOLDO_TR			: 4;
	uint8_t CPLDO_TR			: 4;
}st_efuse07_t;

typedef union{
	st_efuse07_t	b;
	uint8_t			w;
}un_efuse07_t;


typedef struct{
	uint8_t XTLDO_TR			: 4;
	uint8_t BGR_TR_MAN			: 4;
}st_efuse08_t;

typedef union{
	st_efuse08_t	b;
	uint8_t			w;
}un_efuse08_t;


typedef struct{
	uint8_t BGR_LDO_TR			: 4;
	uint8_t ALDO_TR				: 4;
}st_efuse09_t;

typedef union{
	st_efuse09_t	b;
	uint8_t			w;
}un_efuse09_t;


typedef struct{
	uint8_t AUXADC_TEMP			: 2;
	uint8_t AUXADC_200			: 6;
}st_efuse0B_t;

typedef union{
	st_efuse0B_t	b;
	uint8_t			w;
}un_efuse0B_t;


typedef struct{
	uint8_t	AUXADC_200			: 4;
	uint8_t AUXADC_500			: 4;
}st_efuse0C_t;

typedef union{
	st_efuse0C_t	b;
	uint8_t			w;
}un_efuse0C_t;


typedef struct{
	uint8_t AUXADC_500			: 6;
	uint8_t AUXADC_800			: 2;
}st_efuse0D_t;

typedef union{
	st_efuse0D_t	b;
	uint8_t			w;
}un_efuse0D_t;





typedef struct{
	un_efuse00_t			efuse00;
	un_efuse01_t			efuse01;
	un_efuse02_t			efuse02;
	un_efuse03_t			efuse03;
	un_efuse04_t			efuse04;
	un_efuse05_t			efuse05;
	un_efuse06_t			efuse06;
	un_efuse07_t			efuse07;
	un_efuse08_t			efuse08;
	un_efuse09_t			efuse09;
	uint8_t					efuse0A;
	un_efuse0B_t			efuse0B;
	un_efuse0C_t			efuse0C;
	un_efuse0D_t			efuse0D;
	uint8_t					efuse0E;
	uint8_t					efuse0F;
}st_efuse_t;

void __csp_efuse_Initialize(void);


#ifdef __cplusplus
}
#endif

#endif

