#ifndef __NRF24L01_REGISTER_H__
#define __NRF24L01_REGISTER_H__
#define NRF_READ_REG    0x00  // Define read command to register
#define NRF_WRITE_REG   0x20  // Define write command to register
#define RD_RX_PLOAD_WID 0x60  // Define RX payload length register
#define RD_RX_PLOAD 0x61  // Define RX payload register address
#define WR_TX_PLOAD 0xA0  // Define TX payload register address
#define FLUSH_TX    0xE1  // Define flush TX register command
#define FLUSH_RX    0xE2  // Define flush RX register command
#define REUSE_TX_PL 0xE3  // Define reuse TX payload register command
#define NOP         0xFF  // Define No Operation, might be used to read status register

#define NRF_CONFIG  0x00  // 'Config' register address
#define EN_AA       0x01  // 'Enable Auto Acknowledgment' register address
#define EN_RXADDR   0x02  // 'Enabled RX addresses' register address
#define SETUP_AW    0x03  // 'Setup address width' register address
#define SETUP_RETR  0x04  // 'Setup Auto. Retrans' register address
#define RF_CH       0x05  // 'RF channel' register address
#define RF_SETUP    0x06  // 'RF setup' register address
#define STATUS      0x07  // 'Status' register address
#define OBSERVE_TX  0x08  // 'Observe TX' register address
#define CD          0x09  // 'Carrier Detect' register address
#define RX_ADDR_P0  0x0A  // 'RX address pipe0' register address
#define RX_ADDR_P1  0x0B  // 'RX address pipe1' register address
#define RX_ADDR_P2  0x0C  // 'RX address pipe2' register address
#define RX_ADDR_P3  0x0D  // 'RX address pipe3' register address
#define RX_ADDR_P4  0x0E  // 'RX address pipe4' register address
#define RX_ADDR_P5  0x0F  // 'RX address pipe5' register address
#define TX_ADDR     0x10  // 'TX address' register address
#define RX_PW_P0    0x11  // 'RX payload width, pipe0' register address
#define RX_PW_P1    0x12  // 'RX payload width, pipe1' register address
#define RX_PW_P2    0x13  // 'RX payload width, pipe2' register address
#define RX_PW_P3    0x14  // 'RX payload width, pipe3' register address
#define RX_PW_P4    0x15  // 'RX payload width, pipe4' register address
#define RX_PW_P5    0x16  // 'RX payload width, pipe5' register address
#define FIFO_STATUS 0x17  // 'FIFO Status Register' register address

#define  NRF_FEATURE 0x1D//only for 24L01+
#define  NRF_DYNPD  0x1C//only for 24L01+
#define  NRF_ACTIVATE 0x50  // only for 24L01+
#define  NRD_EN_DPL         0x04
#define  NRF_EN_ACK_PAYLOAD 0x02
#define  WR_ACK_PAYLOAD     0xA8
#define  NRF_DPL_P0         0x01
#define  NRF_DPL_P1         0x02
#define  NRF_DPL_P2         0x04
#define  NRF_DPL_P3         0x08
#define  NRF_DPL_P4         0x10
#define  NRF_DPL_P5         0x20


#define NRF_ARD(us)      ( (( (us-1)/250  )&0x0f)<<4 )
#define NRF_ARC( arc_count )            ((arc_count) & 0x0f)
#define NRF_PWR_0dBm          (0x3<<1)
#define NRF_DR_2Mbps          (1<<3)
#define NRF_EN_ALL_IRQ      0x00
#define NRF_EN_CRC          0x08
#define NRF_CRC_2B          0x04
#define NRF_POWER_UP        0x02
#define NRF_PRIM_TX         0x00
#define NRD_EN_DPL          0x04

typedef enum
{
  MAX_RT = 0x10,  //最大发射次数
	TX_DS = 0x20,   //发送完成 
	RX_DR = 0x40,   //接收完成
	RX_Null =0x60,  //没有接收
	Err_RX = 0x41,
	Err_TX = 0x42,
	TXMode = 1,
	RXMode = 2,
}NRF_State;

#endif
