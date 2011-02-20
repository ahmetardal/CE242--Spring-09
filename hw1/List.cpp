
/* --------------------------------------------
 * --- File     : List.cpp                  ---
 * --- Author   : Ahmet ARDAL               ---
 * --- Contact  : ardalahmet@hotmail.com    ---
 * --------------------------------------------
 */

#include <cstdlib>
#include "List.h"

List *ListCreate()
{
    List *pList;

    pList = new List;

    pList->pHead = NULL;
    pList->pTail = NULL;
    pList->size  = 0;

    return pList;
}

Node *ListPrepend(List *pList, const void *pData)
{
    Node *pNode;

    pNode = new Node;
    pNode->pData = (void *) pData;
    pNode->pNext = pList->pHead;

    pList->pHead = pNode;

    if (pList->size == 0)
    {
        pList->pTail = pNode;
    }

    ++pList->size;

    return pNode;
}

Node *ListAppend(List *pList, const void *pData)
{
    Node *pNode;

    pNode = new Node;
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

    pList->pTail = pNode;
    ++pList->size;

    return pNode;
}

void *ListDeleteHead(List *pList)
{
    Node *pNode;
    void *pData;

    if (pList->size == 0)
    {
        return NULL;
    }

    pNode = pList->pHead;
    pData = pNode->pData;
    pList->pHead = pNode->pNext;
    delete pNode;
    --pList->size;

    if (pList->size <= 1)
    {
        pList->pTail = pList->pHead;
    }

    return pData;
}

void *ListDeleteNth(List *pList, int idx)
{
    if ((idx < 0) || (idx >= pList->size))
    {
        return NULL;
    }

    if (idx == 0)
    {
        return ListDeleteHead(pList);
    }

    int i;
    void *pData;
    Node *pCur, *pPrev;

    for (
       pPrev = pList->pHead, pCur = pPrev->pNext, i = 1;
       pCur != NULL;
       pPrev = pCur, pCur = pCur->pNext, ++i
    )
    {
        if (i == idx)
        {
            pPrev->pNext = pCur->pNext;
            pData = pCur->pData;
            delete pCur;
            --pList->size;
            
            return pData;
        }
    }

    return NULL;
}

Node *ListFindNode(List *pList, bool (*compare)(const void *, const void *), const void *pCmpData)
{
    for (Node *pNode = pList->pHead; pNode != NULL; pNode = pNode->pNext)
    {
        if (compare(pNode->pData, pCmpData))
        {
            return pNode;
        }
    }

    return NULL;
}

void *ListDeleteNode(List *pList, bool (*compare)(const void *, const void *), const void *pCmpData)
{
    Node *pCur, *pPrev;
    void *pData;

    /* handle first item outside of the loop */
    if ((pPrev = pList->pHead) == NULL)
    {
        return NULL;
    }

    if (compare(pPrev->pData, pCmpData))
    {
        pList->pHead = pPrev->pNext;
        pData = pPrev->pData;
        delete pPrev;
        --pList->size;

        return pData;
    }

    /* first item is not what we are looking for, so traverse the entire list */
    for (
       pCur = pPrev->pNext;
       pCur != NULL;
       pPrev = pCur, pCur = pCur->pNext
    )
    {
        if (compare(pCur->pData, pCmpData))
        {
            pPrev->pNext = pCur->pNext;
            pData = pCur->pData;
            delete pCur;
            --pList->size;
            
            return pData;
        }
    }
    
    return NULL;
}

void  ListForeach(List *pList, void (*callback)(void *, void *), void *pCallbackData)
{
    for (Node *pNode = pList->pHead; pNode != NULL; pNode = pNode->pNext)
    {
        callback(pNode->pData, pCallbackData);
    }
}

void ListTruncate(List *pList)
{
    Node *pNode, *pNodeTmp;

    for (pNode = pList->pHead; pNode != NULL; pNode = pNodeTmp)
    {
        pNodeTmp = pNode->pNext;
        delete pNode;
    }

    pList->pHead = NULL;
    pList->pTail = NULL;
    pList->size = 0;
}

int ListGetSize(List *pList)
{
    return pList->size;
}

bool ListIsEmpty(List *pList)
{
    return (pList->size == 0);
}

void ListDestroy(List *pList)
{
    ListTruncate(pList);
    delete pList;
}
