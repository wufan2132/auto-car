/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2014        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include "diskio.h"		/* FatFs lower layer API */
//#include "usbdisk.h"	/* Example: Header file of existing USB MSD control module */
//#include "atadrive.h"	/* Example: Header file of existing ATA harddisk control module */
#include "sdcard.h"		/* Example: Header file of existing MMC/SDC contorl module */

/* Definitions of physical drive number for each drive */
#define ATA		0	/* Example: Map ATA harddisk to physical drive 0 */
#define MMC		1	/* Example: Map MMC/SD card to physical drive 1 */
#define USB		2	/* Example: Map USB MSD to physical drive 2 */

#define MMC_disk_initialize SD_Init
#define MMC_disk_status SD_DET()
/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber to identify the drive */
)
{

	if(pdrv) return STA_NOINIT;
	
	if(!MMC_disk_status) return STA_NODISK;
	else return 0;

}



/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive nmuber to identify the drive */
)
{
	int result;

	if(pdrv) return STA_NOINIT;
	
	result = MMC_disk_initialize();
	if(result == STA_NODISK) return STA_NODISK;
	else if(result != 0) return STA_NOINIT;
	else return 0;
		
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber to identify the drive */
	BYTE *buff,		/* Data buffer to store read data */
	DWORD sector,	/* Sector address in LBA */
	UINT count		/* Number of sectors to read */
)
{
	u8 res;

	if(pdrv || !count) return RES_PARERR;
	if(!SD_DET()) return RES_NOTRDY;
	
	if(count == 1)
		res = SD_ReadSingleBlock(sector, buff); 
	if(res == 0X00)
		return RES_OK;
	else
		return RES_ERROR;
		
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if _USE_WRITE
DRESULT disk_write (
	BYTE pdrv,			/* Physical drive nmuber to identify the drive */
	const BYTE *buff,	/* Data to be written */
	DWORD sector,		/* Sector address in LBA */
	UINT count			/* Number of sectors to write */
)
{
	u8 res;
	if(pdrv || !count) return RES_PARERR;
	if(!SD_DET()) return RES_NOTRDY;
	
	if(count == 1)
		res = SD_WriteSingleBlock(sector, buff); 

	if(res == 0X00)
		return RES_OK;
	else
		return RES_ERROR;
}
#endif


/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

#if _USE_IOCTL
DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
	DRESULT res;
	
	if(pdrv) return RES_PARERR;
	
	switch(cmd)
	{
		case CTRL_SYNC:
			SD_CS_ENABLE();
			if(SD_WaitReady()==0) res = RES_OK;
			else res = RES_ERROR;
			SD_CS_DISABLE();
			break;
		case GET_BLOCK_SIZE:
			*(WORD*)buff = 512;
			res = RES_OK;
			break;
		case GET_SECTOR_COUNT:
			*(DWORD*)buff = SD_GetCapacity();
			res = RES_OK;
			break;
		default:
			res = RES_PARERR;
			break;
	}
	
	return res;
}
#endif


