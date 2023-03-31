#ifndef _ARITHMATIC_H_
#define _ARITHMATIC_H_

#include <stdint.h>
#include "stack.h"

void arithInit(void);
uint8_t inputStack_push(Type input_type, OP input_opr, float num);
uint8_t input2RPN_conv(void);





#endif