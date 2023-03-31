#ifndef _STACK_H_
#define _STACK_H_

#include <stdint.h>



//definition of operation num and operator
typedef enum
{
		NUMBER,
		OPERATOR
}Type;
 
//definition of operations
typedef enum{
		ADD, SUB, MUL, DIV, EXPO, LOG, REV, LBRAC, RBRAC, NOUSE
}OP;



//item in stack
typedef struct Element *Stack_Element;
struct Element{
		Type type;
		float  Number;
		OP   Operator;
};


//define a stack type
typedef struct SNode *Stack;
struct SNode
{
		Stack_Element elem;
		struct SNode *Next;
};


Stack Stack_Create(Stack S);
uint8_t Stack_isEmpty(Stack S);
void Stack_Push(Stack_Element item,Stack S);
Stack_Element Stack_Pop(Stack S);



#endif