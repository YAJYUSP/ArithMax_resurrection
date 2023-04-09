#include "dynamic_string.h"
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

/******************************************************************************
* @brief  Backspace in string buffer at cursor pos
* @param  cursor: expected backspace position
					**targetStr: pointer that point to "target string" pointer
* @retval 0:success
					1:string empty 
******************************************************************************/
uint8_t dynamicStr_backspace(uint8_t cursor, char **targetStr)
{
		if(cursor>0)
		{
				//new Line0 buffer size
				uint8_t Line0_newsize = strlen(*targetStr);
			
				//copy the content on right side of old Line0 buffer to a cache
				uint8_t RightCacheSize = strlen(*targetStr)-cursor+1;
				char *RightCache = (char *)malloc(RightCacheSize);
				memset(RightCache,0,RightCacheSize);		//significant step
				memcpy(RightCache, *targetStr + cursor,RightCacheSize-1);

				//copy the content on left side of old Line0 buffer to a cache
				uint8_t LeftCacheSize = cursor;							//strlen of LeftCacheSize = cursor-1
				char *LeftCache = (char *)malloc(LeftCacheSize);
				memset(LeftCache,0,LeftCacheSize);				//significant step
				memcpy(LeftCache, *targetStr, LeftCacheSize-1);

				//release memory of old Line0 buffer
				free(*targetStr);		
				*targetStr = (char *)malloc(Line0_newsize);		
				memset(*targetStr, 0, Line0_newsize);		//important step
			
				memcpy(*targetStr, LeftCache, strlen(LeftCache));
				memcpy(*targetStr + strlen(LeftCache), RightCache, strlen(RightCache));	

				free(RightCache);
				free(LeftCache);
				RightCache = NULL;
				LeftCache = NULL;
				return 0;
		}
		else
				return 1;
}


/******************************************************************************
* @brief  add string "str" to target string
* @param  *str: pointer that point to "str"
					**targetStr: pointer that point to "target string" pointer
					cursor: expected string insert position
					maxLen_str0: max length of "targetStr"
* @retval 0:success
				  1:str0 buffer full
******************************************************************************/
uint8_t dynamicStr_strcat(char *str, char **targetStr, uint8_t cursor, uint8_t maxLen_str0)
{
		//new Line0 buffer size
		uint8_t str0_newsize = strlen(*targetStr)+strlen(str)+1;
		//if meet the requirment,continue the operations
		if(str0_newsize <= maxLen_str0)
		{				
				//copy the content on right side of old Line0 buffer to a cache
				uint8_t RightCacheSize = strlen(*targetStr)-cursor+1;
				char *RightCache = (char *)malloc(RightCacheSize);
				memset(RightCache,0,RightCacheSize);		//significant step
				memcpy(RightCache,*targetStr+cursor,RightCacheSize-1);
		
				//copy the content on left side of old Line0 buffer to a cache
				uint8_t LeftCacheSize = cursor+1;					//cursor and left string len is equal in num
				char *LeftCache = (char *)malloc(LeftCacheSize);
				memset(LeftCache,0,LeftCacheSize);		//significant step
				memcpy(LeftCache,*targetStr,LeftCacheSize-1);
	
				//release memory of old Line0 buffer
				free(*targetStr);		
			  *targetStr = (char *)malloc(str0_newsize);		
				memset(*targetStr,0,str0_newsize);		//important step
			
				memcpy(*targetStr,LeftCache,LeftCacheSize-1);			
				memcpy(*targetStr+LeftCacheSize-1,str,strlen(str));	
				memcpy(*targetStr+(LeftCacheSize-1)+strlen(str),RightCache,RightCacheSize-1);	
			
				free(RightCache);
				RightCache = NULL;
				free(LeftCache);
				LeftCache = NULL;
				return 0;
		}
		return 1;
}