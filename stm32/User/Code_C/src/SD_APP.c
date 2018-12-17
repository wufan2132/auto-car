#include "SD_APP.h"
void sd_init(void);


FATFS fs;
FRESULT F_RET;
struct SD_APP_ SD_APP =
{
 sd_init
};

FIL SD_User_Data;
void sd_set_title(FIL* Data,const char* Path,const char* Tttle)
{
	UINT P;

	f_open(Data,Path,FA_CREATE_ALWAYS | FA_WRITE);
	f_write(Data,Tttle,strlen(Tttle),&P);	
	f_close(Data);	
}

void sd_init(void)
{
		F_RET = f_mount(&fs,"0:",1);
	if(F_RET != FR_OK) return;
	
	sd_set_title(&SD_User_Data,"0:/User_Data.txt","Data1\tData2\tData3\r\n");

}


