#ifndef __ADS1118_H__
#define __ADS1118_H__
#include "stm32f4xx.h"
#include "Common.h"
//ÅäÖÃ¼Ä´æÆ÷
#define     CONFIG_BIT_OS       		(1<<15)    //Operational status/single-shot conversion start
#define     CONFIG_BIT_MUX    		  (7<<12)    //MUX[2:0]: Input multiplexer configuration
#define     CONFIG_BIT_PGA      		(7<<9)     //PGA[2:0]: Programmable gain amplifier configuration
#define     CONFIG_BIT_MODE    		  (1<<8)     //MODE: Device operating mode
#define     CONFIG_BIT_DR      		  (7<<5)     //DR[2:0]: Data rate
#define     CONFIG_BIT_TS_MODE  		(1<<4)     //TS_MODE: Temperature sensor mode
#define     CONFIG_BIT_PULLUP_EN    (1<<3) 		 //PULL_UP_EN: Pull-up enable
#define     CONFIG_BIT_NOP      		(3<<1)     //NOP: No operation
#define     CONFIG_BIT_CNV_RDY_FL   (1<<0) 		 //CNV_RDY_FL: Conversion ready flag
typedef union
{
	struct
	{
		u8    RDY				  :1;   //low
		u8    NOP_        :2;
		u8    PULLUP      :1;
		u8    TS          :1;
		u8    DR          :3;
		u8    MODE        :1;
		u8    PGA         :3;
		u8    MUX         :3;
		u8    OS          :1;   //high
	}stru;
    u16 word;
}ADS_InitTypeDef;

typedef enum
{
	CONVERING = 0x0,
	SINGLE_CONVER = 0x1
 
} ADS_OS_TypeDef;
typedef enum
{
	AINPN_0_1 = 0x0,
	AINPN_0_3 =   0x1,
	AINPN_1_3 =   0x2,
	AINPN_2_3 =   0x3,
	AINPN_0_GND=  0x4,
	AINPN_1_GND=  0x5,
	AINPN_2_GND=  0x6,
	AINPN_3_GND=  0x7
 
}ADS_MUX_TypeDef;
typedef enum
{
	PGA_6144 = 0x0,
	PGA_4096 = 0x1,
	PGA_2048 = 0x2,
	PGA_1024 = 0x3,
	PGA_512 = 0x4,
	PGA_256 = 0x5
 
}ADS_PGA_TypeDef;
typedef enum
{
 
	CONTIOUS  =  0x0,
	SINGLE_SHOT = 0x1
 
}ADS_MODE_TypeDef;
typedef enum
{
 
	DR_8_SPS   =   0x0,
	DR_16_SPS  =   0x1,
	DR_32_SPS  =   0x2,
	DR_64_SPS  =   0x3,
	DR_128_SPS =   0x4,
	DR_250_SPS =   0x5,
	DR_475_SPS =   0x6,
	DR_860_SPS =   0x7
 
}ADS_DATARATE_TypeDef;
typedef enum
{
	ADC_MODE    =   0x0,
	TEMPERATURE_MODE =  0x1
}ADS_TSMODE_TypeDef;
typedef enum
{
	PULL_UP_DIS = 0x0,
	PULL_UP_EN  = 0x1
}ADS_PULL_TypeDef;
 
typedef enum
{
	DATA_VALID      = 0x1,
	DATA_INVALID    = 0x0
}ADS_NOP_TypeDef;
typedef enum
{
	DATA_READY = 0x0,
	DATA_NREADY = 0x1
 
}ADS_RDY_TypeDef;

extern struct ADS1118_
{
	void (*Init)(void);
	float (*Updata)(u8 Channel);
}ADS1118;
#endif

