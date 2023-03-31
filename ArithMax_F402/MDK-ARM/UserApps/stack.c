#include <main.h>
#include <stdlib.h>
#include "stack.h"


//Create a new stack head node
Stack Stack_Create(Stack S)
{
		S = (Stack)malloc(sizeof(struct SNode));
		S->Next = NULL;
		return S;	
}

//assert stack is empty or not
uint8_t Stack_isEmpty(Stack S)
{
		return(S->Next == NULL);
}

//push one item to stack
void Stack_Push(Stack_Element item,Stack S)
{
		struct SNode *TmpCell;
		TmpCell=(struct SNode *)malloc(sizeof(struct SNode));
		TmpCell->elem=item;
		TmpCell->Next=S->Next;
		S->Next=TmpCell;
}

//delete and return top element of stack
Stack_Element Stack_Pop(Stack S)
{
		struct SNode *FirstCell;
		Stack_Element TopElem;
		if(Stack_isEmpty(S))
				return NULL;//stack is empty, do nothing
		FirstCell=S->Next;
		S->Next=FirstCell->Next;
		TopElem=FirstCell->elem;
		free(FirstCell);
		return TopElem;
}





