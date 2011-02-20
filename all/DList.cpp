
/* --------------------------------------------
 * --- File     : DList.cpp                 ---
 * --- Author   : Ahmet ARDAL               ---
 * --- Contact  : ardalahmet@hotmail.com    ---
 * --------------------------------------------
 */

#include <cstdlib>
#include "DList.h"

DList *DListCreate()
{
    DList *pList = new DList;

    pList->pHead = NULL;
    pList->pTail = NULL;
    pList->size  = 0;

    return pList;
}

DNode *DListPrepend(DList *pList, const void *pData)
{
    DNode *pNode = new DNode;

    pNode->pData = (void *) pData;
    pNode->pPrev = NULL;
    pNode->pNext = pList->pHead;

    if (pList->size == 0)
    {
        pList->pTail = pNode;
    }
    else
    {
        pList->pHead->pPrev = pNode;
    }
    pList->pHead = pNode;

    ++pList->size;

    return pNode;
}

DNode *DListAppend(DList *pList, const void *pData)
{
    DNode *pNode = new DNode;

    pNode->pData = (void *) pData;
    pNode->pNext = NULL;

    if (pList->size == 0)
    {
        pList->pHead = pNode;
    }
    else
    {
        pList->pTail->pNext = pNode;
    }

    pNode->pPrev = pList->pTail;
    pList->pTail = pNode;
    ++pList->size;

    return pNode;
}

void *DListRemoveNode(DList *pList, const DNode *pNode)
{
    if (pList->size == 0)
    {
        return NULL;
    }

    if (pList->size == 1)
    {
        pList->pHead = NULL;
        pList->pTail = NULL;
    }
    else if (pList->pHead == pNode)
    {
        pNode->pNext->pPrev = NULL;
        pList->pHead        = pNode->pNext;
    }
    else if (pList->pTail == pNode)
    {
        pNode->pPrev->pNext = NULL;
        pList->pTail        = pNode->pPrev;
    }
    else
    {
        pNode->pPrev->pNext = pNode->pNext;
        pNode->pNext->pPrev = pNode->pPrev;
    }

    void *pData = pNode->pData;

    delete pNode;
    --pList->size;

    return pData;
}

DNode *DListFindNode(DList *pList, CmpFunc cmpFunc, const void *pCmpData, DListTraverseDirection td)
{
    switch (td)
    {
        case DLIST_TD_HEAD_TO_TAIL:
            for (DNode *pNode = pList->pHead; pNode != NULL; pNode = pNode->pNext)
            {
                if (cmpFunc((const void *) pNode->pData, pCmpData))
                {
                    return pNode;
                }
            }
            break;

        case DLIST_TD_TAIL_TO_HEAD:
            for (DNode *pNode = pList->pTail; pNode != NULL; pNode = pNode->pPrev)
            {
                if (cmpFunc((const void *) pNode->pData, pCmpData))
                {
                    return pNode;
                }
            }
            break;
    }

    return NULL;
}

void DListForeach(DList *pList, CallbackFunc cbFunc, void *pCallbackData, DListTraverseDirection td)
{
    switch (td)
    {
        case DLIST_TD_HEAD_TO_TAIL:
            for (DNode *pNode = pList->pHead; pNode != NULL; pNode = pNode->pNext)
            {
                cbFunc(pNode->pData, pCallbackData);
            }
            break;

        case DLIST_TD_TAIL_TO_HEAD:
            for (DNode *pNode = pList->pTail; pNode != NULL; pNode = pNode->pPrev)
            {
                cbFunc(pNode->pData, pCallbackData);
            }
            break;
    }
}

void DListTruncate(DList *pList)
{
    DNode *pNode, *pTmpNode;

    for (pNode = pList->pHead; pNode != NULL; pNode = pTmpNode)
    {
        pTmpNode = pNode->pNext;
        delete pNode;
    }

    pList->pHead = NULL;
    pList->pTail = NULL;
    pList->size  = 0;
}

void DListDestroy(DList *pList)
{
    DListTruncate(pList);
    delete pList;
}
