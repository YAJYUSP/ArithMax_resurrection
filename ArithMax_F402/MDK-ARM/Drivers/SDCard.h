#ifndef _SDCARD_H_
#define _SDCARD_H_

#include <main.h>

#define BLOCK_SIZE            512            // SD�����С     
#define NUMBER_OF_BLOCKS      1              // ���Կ�����(С��15)
#define WRITE_READ_ADDRESS    0x00000000     // ���Զ�д��ַ


void SD_RW_Test(void);
void SD_FF_RW_Test(void);


#endif