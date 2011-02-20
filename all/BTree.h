
/* --------------------------------------------
 * --- File     : BTree.h                   ---
 * --- Author   : Ahmet ARDAL               ---
 * --- Contact  : ardalahmet@hotmail.com    ---
 * --------------------------------------------
 */

#ifndef BTREE_H_
#define BTREE_H_

struct TNode
{
    void  *pData;
    TNode *pRight;
    TNode *pLeft;
};

#define TNodeData(pNode)    (pNode)->pData
#define TNodeRight(pNode)   (pNode)->pRight
#define TNodeLeft(pNode)    (pNode)->pLeft

#ifndef CALLBACKFUNC_DEFINED
# define CALLBACKFUNC_DEFINED
typedef void (*CallbackFunc)(void *pData, void *pCallbackData);
#endif

typedef int (*CompareFunc)(const void *pData1, const void *pData2);

struct BTree
{
    TNode *pRoot;
    CompareFunc compare;
};

#define BTreeRoot(pTree)    (pTree)->pRoot

BTree *BTreeCreate(CompareFunc compare);
TNode *BTreeInsert(BTree *pTree, const void *pData);
TNode *BTreeSearch(BTree *pTree, const void *pKey);
bool   BTreeRemove(BTree *pTree, const void *pKey);
bool   BTreeRemove2(BTree *pTree, const void *pKey);
void   BTreeRotateRight(TNode **ppRoot);
void   BTreeRotateLeft(TNode **ppRoot);
TNode *BTreeInsertRoot(BTree *pTree, const void *pData);
void   BTreeForeachAsc(BTree *pTree, CallbackFunc callback, void *pCallbackData);
void   BTreeForeachDesc(BTree *pTree, CallbackFunc callback, void *pCallbackData);
void   BTreeDestroy(BTree *pTree);

#endif  // BTREE_H_
