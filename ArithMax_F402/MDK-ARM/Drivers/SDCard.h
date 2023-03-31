#ifndef _SDCARD_H_
#define _SDCARD_H_

#include <main.h>

#define BLOCK_SIZE            512            // SD卡块大小     
#define NUMBER_OF_BLOCKS      1              // 测试块数量(小于15)
#define WRITE_READ_ADDRESS    0x00000000     // 测试读写地址


void SD_RW_Test(void);
void SD_FF_RW_Test(void);


#endif