#ifndef _DYNAMIC_STRING_H_
#define _DYNAMIC_STRING_H_

#include <stdint.h>

uint8_t dynamicStr_backspace(uint8_t cursor, char **targetStr);
uint8_t dynamicStr_strcat(char *str, char **targetStr, uint8_t cursor, uint8_t maxLen_str0);



#endif