#include "sdcard.h"
//#include "fatfs.h"

//void SD_RW_Test(void)
//{
//		extern SD_HandleTypeDef hsd;
//		
//		__align(4) uint32_t Buffer_Block_Tx[BLOCK_SIZE*NUMBER_OF_BLOCKS/4];    //将要写入的数据放在这里，__align(4)是四字节对齐关键词
//		__align(4) uint32_t Buffer_Block_Rx[BLOCK_SIZE*NUMBER_OF_BLOCKS/4];    //将读出的数据放在此数组
//	
//		HAL_SD_InitCard(&hsd);
//		if(HAL_SD_Erase(&hsd,WRITE_READ_ADDRESS,WRITE_READ_ADDRESS + 0x00000200) == HAL_OK)
//		{
//				printf("Erase Successful\r\n");
//				HAL_Delay(400);    //如果不延时可能到值写操作失败
//				if(HAL_SD_WriteBlocks(&hsd, (uint8_t *)Buffer_Block_Tx, WRITE_READ_ADDRESS, NUMBER_OF_BLOCKS, 0xFFFF) == HAL_OK )
//				{
//						printf("Write Successful\r\n");
//						HAL_Delay(200);
//						if(HAL_SD_ReadBlocks(&hsd, (uint8_t *)Buffer_Block_Rx, WRITE_READ_ADDRESS, NUMBER_OF_BLOCKS, 0xFFFF) == HAL_OK)
//						{
//								printf("Read Successful\r\n");
//								uint8_t j = 0;
//								for(uint16_t i=0;i<BLOCK_SIZE*NUMBER_OF_BLOCKS/4;i++)   //这个循环是为了让读数组里的数组个打印到电脑上
//								{
//										if(j==8)
//										{
//												printf("\r\n");
//												j=0;
//										}
//										printf("%d  ",Buffer_Block_Rx[i]);
//										j++;
//								}
//						}
//						else
//						{
//							printf("Read Error\r\n");
//						}
//				}
//				else
//				{
//					printf("Write Error\r\n");
//				}
//		}
//		else
//		{
//			printf("Erase Error\r\n");
//		}
//}


//void SD_FF_RW_Test(void)
//{
//		FATFS fs;													/* FatFs文件系统对象 */
//		FIL file;													/* 文件对象 */
//		FRESULT f_res;                    /* 文件操作结果 */
//		UINT fnum;            					  /* 文件成功读写数量 */
//		BYTE MkfsBuffer[512]={0};        	/* 格式化缓冲区 */
//		BYTE ReadBuffer[1024]={0};        /* 读缓冲区 */
//		BYTE WriteBuffer[]= "Welcome to the wildfire STM32 development board. Today is a good day to create new file system test files\r\n";

//		printf("\r\r\n****** This is a SD card file system experiment ******\r\n");
//  	// 默认已经注册了FatFS设备：SD卡 //

//		//在SD卡挂载文件系统，文件系统挂载时会对SD卡初始化
//		f_res = f_mount(&fs,(TCHAR const*)SDPath,1);
//		printf("%d\n",f_res);
//		//----------------------- 格式化测试 ---------------------------//
//		// 如果没有文件系统就格式化创建创建文件系统 */
//		if(f_res == FR_NO_FILESYSTEM)
//		{
//				printf("The SD card does not have a file system yet and will be formatted...\r\n");
//				// 格式化 //
//				f_res=f_mkfs((TCHAR const*)SDPath,FM_FAT,512,MkfsBuffer,sizeof(MkfsBuffer));
//				printf("%d\n",f_res);
//				if(f_res == FR_OK)
//				{
//						printf("The SD card has successfully formatted the file system\r\n");
//						// 格式化后，先取消挂载 //
//						f_res = f_mount(NULL,(TCHAR const*)SDPath,1);
//						// 重新挂载	//
//						f_res = f_mount(&fs,(TCHAR const*)SDPath,1);
//				}
//				else
//				{
//						printf("Format failed\r\n");
//						while(1);
//				}
//		}
//		else if(f_res!=FR_OK)
//		{
//				printf("The SD card failed to mount the file system.(%d)\r\n",f_res);
//				printf("%d\n",f_res);
//				while(1);
//		}
//		else
//		{
//				printf("The file system is mounted successfully and can be read and written\r\n");
//		}

//		//----------------------- 文件系统测试：写测试 -----------------------------//
//		// 打开文件，如果文件不存在则创建它 //
//		printf("****** A file write test will be performed... ******\r\n");
//		f_res = f_open(&file, "unit_sd_rw_test.txt",FA_CREATE_ALWAYS | FA_WRITE );
//		if ( f_res == FR_OK )
//		{
//				printf("Open / create FatFs read / write test file. TXT file successfully, write data to the file.\r\n");
//				// 将指定存储区内容写入到文件内 //
//				f_res=f_write(&file,WriteBuffer,sizeof(WriteBuffer),&fnum);
//				if(f_res==FR_OK)
//				{
//						printf("File write success, write byte data:%d\r\n",fnum);
//						printf("The data written to the file is: \r\n%s\r\n",WriteBuffer);
//				}
//				else
//				{
//						printf(" File write failure:(%d)\r\n",f_res);
//				}
//				// 不再读写，关闭文件 //
//				f_close(&file);
//		}
//		else
//		{
//				printf("Failed to open / create file.\r\n");
//		}

//		//------------------- 文件系统测试：读测试 ------------------------------------//
//		printf("****** File read test is about to take place... ******\r\n");
//		f_res = f_open(&file, "unit_sd_rw_test.txt", FA_OPEN_EXISTING | FA_READ);
//		if(f_res == FR_OK)
//		{
//				printf("File opened successfully.\r\n");
//				f_res = f_read(&file, ReadBuffer, sizeof(ReadBuffer), &fnum);
//				if(f_res==FR_OK)
//				{
//						printf("File read successfully, read byte data: %d\r\n",fnum);
//						printf("The obtained file data are as follows:\r\n%s \r\n", ReadBuffer);
//				}
//				else
//				{
//						printf("File read failure:(%d)\r\n",f_res);
//				}
//		}
//		else
//		{
//				printf("Failed to open file.\r\n");
//		}
//		// 不再读写，关闭文件 //
//		f_close(&file);

//		// 不再使用，取消挂载 //
//		f_res = f_mount(NULL,(TCHAR const*)SDPath,1);
//    
//    // 注销一个FatFS设备：SD卡 //
//    FATFS_UnLinkDriver(SDPath);
//}