#include "sdcard.h"
//#include "fatfs.h"

//void SD_RW_Test(void)
//{
//		extern SD_HandleTypeDef hsd;
//		
//		__align(4) uint32_t Buffer_Block_Tx[BLOCK_SIZE*NUMBER_OF_BLOCKS/4];    //��Ҫд������ݷ������__align(4)�����ֽڶ���ؼ���
//		__align(4) uint32_t Buffer_Block_Rx[BLOCK_SIZE*NUMBER_OF_BLOCKS/4];    //�����������ݷ��ڴ�����
//	
//		HAL_SD_InitCard(&hsd);
//		if(HAL_SD_Erase(&hsd,WRITE_READ_ADDRESS,WRITE_READ_ADDRESS + 0x00000200) == HAL_OK)
//		{
//				printf("Erase Successful\r\n");
//				HAL_Delay(400);    //�������ʱ���ܵ�ֵд����ʧ��
//				if(HAL_SD_WriteBlocks(&hsd, (uint8_t *)Buffer_Block_Tx, WRITE_READ_ADDRESS, NUMBER_OF_BLOCKS, 0xFFFF) == HAL_OK )
//				{
//						printf("Write Successful\r\n");
//						HAL_Delay(200);
//						if(HAL_SD_ReadBlocks(&hsd, (uint8_t *)Buffer_Block_Rx, WRITE_READ_ADDRESS, NUMBER_OF_BLOCKS, 0xFFFF) == HAL_OK)
//						{
//								printf("Read Successful\r\n");
//								uint8_t j = 0;
//								for(uint16_t i=0;i<BLOCK_SIZE*NUMBER_OF_BLOCKS/4;i++)   //���ѭ����Ϊ���ö���������������ӡ��������
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
//		FATFS fs;													/* FatFs�ļ�ϵͳ���� */
//		FIL file;													/* �ļ����� */
//		FRESULT f_res;                    /* �ļ�������� */
//		UINT fnum;            					  /* �ļ��ɹ���д���� */
//		BYTE MkfsBuffer[512]={0};        	/* ��ʽ�������� */
//		BYTE ReadBuffer[1024]={0};        /* �������� */
//		BYTE WriteBuffer[]= "Welcome to the wildfire STM32 development board. Today is a good day to create new file system test files\r\n";

//		printf("\r\r\n****** This is a SD card file system experiment ******\r\n");
//  	// Ĭ���Ѿ�ע����FatFS�豸��SD�� //

//		//��SD�������ļ�ϵͳ���ļ�ϵͳ����ʱ���SD����ʼ��
//		f_res = f_mount(&fs,(TCHAR const*)SDPath,1);
//		printf("%d\n",f_res);
//		//----------------------- ��ʽ������ ---------------------------//
//		// ���û���ļ�ϵͳ�͸�ʽ�����������ļ�ϵͳ */
//		if(f_res == FR_NO_FILESYSTEM)
//		{
//				printf("The SD card does not have a file system yet and will be formatted...\r\n");
//				// ��ʽ�� //
//				f_res=f_mkfs((TCHAR const*)SDPath,FM_FAT,512,MkfsBuffer,sizeof(MkfsBuffer));
//				printf("%d\n",f_res);
//				if(f_res == FR_OK)
//				{
//						printf("The SD card has successfully formatted the file system\r\n");
//						// ��ʽ������ȡ������ //
//						f_res = f_mount(NULL,(TCHAR const*)SDPath,1);
//						// ���¹���	//
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

//		//----------------------- �ļ�ϵͳ���ԣ�д���� -----------------------------//
//		// ���ļ�������ļ��������򴴽��� //
//		printf("****** A file write test will be performed... ******\r\n");
//		f_res = f_open(&file, "unit_sd_rw_test.txt",FA_CREATE_ALWAYS | FA_WRITE );
//		if ( f_res == FR_OK )
//		{
//				printf("Open / create FatFs read / write test file. TXT file successfully, write data to the file.\r\n");
//				// ��ָ���洢������д�뵽�ļ��� //
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
//				// ���ٶ�д���ر��ļ� //
//				f_close(&file);
//		}
//		else
//		{
//				printf("Failed to open / create file.\r\n");
//		}

//		//------------------- �ļ�ϵͳ���ԣ������� ------------------------------------//
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
//		// ���ٶ�д���ر��ļ� //
//		f_close(&file);

//		// ����ʹ�ã�ȡ������ //
//		f_res = f_mount(NULL,(TCHAR const*)SDPath,1);
//    
//    // ע��һ��FatFS�豸��SD�� //
//    FATFS_UnLinkDriver(SDPath);
//}