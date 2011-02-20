
/* --------------------------------------------
 * --- File     : Stack.cpp                 ---
 * --- Author   : Ahmet ARDAL               ---
 * --- Contact  : ardalahmet@hotmail.com    ---
 * --------------------------------------------
 */

#include <cstdlib>
#include "Stack.h"

Stack *StackCreate()
{
    Stack *pStack = new Stack;

    pStack->pList = ListCreate();

    return pStack;
}

Node *StackPush(Stack *pStack, const void *pData)
{
    return ListPrepend(pStack->pList, pData);
}

void *StackPop(Stack *pStack)
{
    return ListDeleteHead(pStack->pList);
}

void *StackTop(Stack *pStack)
{
    if (ListIsEmpty(pStack->pList))
    {
        return NULL;
    }

    return pStack->pList->pHead->pData;
}

int StackGetSize(Stack *pStack)
{
    return ListGetSize(pStack->pList);
}

bool StackIsEmpty(Stack *pStack)
{
    return ListIsEmpty(pStack->pList);
}

void StackDestroy(Stack *pStack)
{
    ListDestroy(pStack->pList);
    delete pStack;
}
