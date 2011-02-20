
/* --------------------------------------------
 * --- File     : List.h                    ---
 * --- Author   : Ahmet ARDAL               ---
 * --- Contact  : ardalahmet@hotmail.com    ---
 * --------------------------------------------
 */

#ifndef LIST_H_
#define LIST_H_

/* type definitions */

struct Node
{
    void *pData;
    Node *pNext;
};

struct List
{
    Node *pHead;
    Node *pTail;
    int   size;
};

/* Function declarations */

List *ListCreate();

Node *ListPrepend(List *pList, const void *pData);

Node *ListAppend(List *pList, const void *pData);

void *ListDeleteHead(List *pList);

void *ListDeleteNth(List *pList, int idx);

Node *ListFindNode(List *pList, bool (*compare)(const void *, const void *), const void *pCmpData);

void *ListDeleteNode(List *pList, bool (*compare)(const void *, const void *), const void *pCmpData);

void  ListForeach(List *pList, void (*callback)(void *, void *), void *pCallbackData);

void  ListTruncate(List *pList);

int   ListGetSize(List *pList);

bool  ListIsEmpty(List *pList);

void  ListDestroy(List *pList);

#endif  /* LIST_H_ */
