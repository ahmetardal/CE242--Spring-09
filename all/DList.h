
/* --------------------------------------------
 * --- File     : DList.h                   ---
 * --- Author   : Ahmet ARDAL               ---
 * --- Contact  : ardalahmet@hotmail.com    ---
 * --------------------------------------------
 */

#ifndef DLIST_H_
#define DLIST_H_

struct DNode
{
    void  *pData;
    DNode *pPrev;
    DNode *pNext;
};

#define DNodePrev(pNode)    ((pNode)->pPrev)
#define DNodeNext(pNode)    ((pNode)->pNext)
#define DNodeData(pNode)    ((pNode)->pData)

struct DList
{
    DNode *pHead;
    DNode *pTail;
    int    size;
};

#define DListHead(pList)    ((pList)->pHead)
#define DListTail(pList)    ((pList)->pTail)
#define DListSize(pList)    ((pList)->size)

typedef bool (*CmpFunc)(const void *pData, const void *pCmpData);

#ifndef CALLBACKFUNC_DEFINED
# define CALLBACKFUNC_DEFINED
typedef void (*CallbackFunc)(void *pData, void *pCallbackData);
#endif

enum DListTraverseDirection
{
    DLIST_TD_HEAD_TO_TAIL,
    DLIST_TD_TAIL_TO_HEAD
};

DList *DListCreate();

DNode *DListPrepend(DList *pList, const void *pData);

DNode *DListAppend(DList *pList, const void *pData);

void  *DListRemoveNode(DList *pList, const DNode *pNode);

DNode *DListFindNode(DList *pList, CmpFunc cmpFunc, const void *pCmpData, DListTraverseDirection td);

void DListForeach(DList *pList, CallbackFunc cbFunc, void *pCallbackData, DListTraverseDirection td);

void DListTruncate(DList *pList);

void DListDestroy(DList *pList);

#endif  /* DLIST_H_ */
