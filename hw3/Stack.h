
/* --------------------------------------------
 * --- File     : Stack.h                   ---
 * --- Author   : Ahmet ARDAL               ---
 * --- Contact  : ardalahmet@hotmail.com    ---
 * --------------------------------------------
 */

#ifndef STACK_H_
#define STACK_H_

#include "List.h"

struct Stack
{
    List *pList;
};

Stack *StackCreate();

Node  *StackPush(Stack *pStack, const void *pData);

void  *StackPop(Stack *pStack);

void  *StackTop(Stack *pStack);

int    StackGetSize(Stack *pStack);

bool   StackIsEmpty(Stack *pStack);

void   StackDestroy(Stack *pStack);

#endif  /* STACK_H_ */
