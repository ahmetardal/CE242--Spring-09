
/* --------------------------------------------
 * --- File     : BTree.cpp                 ---
 * --- Author   : Ahmet ARDAL               ---
 * --- Contact  : ardalahmet@hotmail.com    ---
 * --------------------------------------------
 */

#include <cstdlib>
#include "BTree.h"

// -------------------------------------------------
// --- private functions ---------------------------
// -------------------------------------------------

static TNode *createNode(const void *pData);
static void   truncateTree(TNode *pNode);
static TNode *insertRecursive(TNode *pRoot, const void *pData, CompareFunc compare);
static TNode *getInorderSuccessor(const TNode *pRoot);
static TNode *getInorderPredecessor(const TNode *pRoot);
static TNode *removeRecursive(TNode *pRoot, const void *pKey, CompareFunc compare);
static TNode *removeRecursive2(TNode *pRoot, const void *pKey, CompareFunc compare);
static void insertRootRecursive(TNode **ppRoot, const void *pData, CompareFunc compare);
static void foreachAscRecursive(TNode *pRoot, CallbackFunc callback, void *pCallbackData);
static void foreachDescRecursive(TNode *pRoot, CallbackFunc callback, void *pCallbackData);

static TNode *createNode(const void *pData)
{
    TNode *pNode = new TNode;

    pNode->pData  = (void *) pData;
    pNode->pRight = NULL;
    pNode->pLeft  = NULL;

    return pNode;
}

static void truncateTree(TNode *pNode)
{
    if (pNode->pLeft != NULL)
    {
        truncateTree(pNode->pLeft);
    }

    if (pNode->pRight != NULL)
    {
        truncateTree(pNode->pRight);
    }

    delete pNode;
}

static TNode *insertRecursive(TNode *pRoot, const void *pData, CompareFunc compare)
{
    int result;

    if ((result = compare(pRoot->pData, pData)) > 0)
    {
        if (pRoot->pLeft == NULL)
        {
            pRoot->pLeft = createNode(pData);
            return pRoot->pLeft;
        }
        return insertRecursive(pRoot->pLeft, pData, compare);
    }
    else if (result < 0)
    {
        if (pRoot->pRight == NULL)
        {
            pRoot->pRight = createNode(pData);
            return pRoot->pRight;
        }
        return insertRecursive(pRoot->pRight, pData, compare);
    }
    else
    {
        return NULL;
    }
}

static TNode *getInorderSuccessor(const TNode *pRoot)
{
    TNode *pNodeTmp;

    for (TNode *pNode = (TNode *) pRoot; pNode != NULL; )
    {
        pNodeTmp = pNode;
        pNode = pNode->pLeft;
    }

    return pNodeTmp;
}

static TNode *getInorderPredecessor(const TNode *pRoot)
{
    TNode *pNodeTmp;

    for (TNode *pNode = (TNode *) pRoot; pNode != NULL; )
    {
        pNodeTmp = pNode;
        pNode = pNode->pRight;
    }

    return pNodeTmp;
}

static TNode *removeRecursive(TNode *pRoot, const void *pKey, CompareFunc compare)
{
    int result;
    TNode *pNodeSuccessor, *pNodeDelete;

    if (pRoot != NULL)
    {
        if ((result = compare(pRoot->pData, pKey)) > 0)
        {
            pRoot->pLeft = removeRecursive(pRoot->pLeft, pKey, compare);
        }
        else if (result < 0)
        {
            pRoot->pRight = removeRecursive(pRoot->pRight, pKey, compare);
        }
        else
        {
            if (pRoot->pLeft == NULL)
            {
                pNodeDelete = pRoot;
                pRoot = pRoot->pRight;
                delete pNodeDelete;
            }
            else if (pRoot->pRight == NULL)
            {
                pNodeDelete = pRoot;
                pRoot = pRoot->pLeft;
                delete pNodeDelete;
            }
            else
            {
                pNodeSuccessor = getInorderSuccessor(pRoot->pRight);
                pRoot->pData   = pNodeSuccessor->pData;
                pRoot->pRight  = removeRecursive(pRoot->pRight, pNodeSuccessor->pData, compare);
            }
        }
        return pRoot;
    }
    else
    {
        return NULL;
    }    
}

static TNode *removeRecursive2(TNode *pRoot, const void *pKey, CompareFunc compare)
{
    int result;
    TNode *pNodePredecessor, *pNodeDelete;

    if (pRoot != NULL)
    {
        if ((result = compare(pRoot->pData, pKey)) > 0)
        {
            pRoot->pLeft = removeRecursive2(pRoot->pLeft, pKey, compare);
        }
        else if (result < 0)
        {
            pRoot->pRight = removeRecursive2(pRoot->pRight, pKey, compare);
        }
        else
        {
            if (pRoot->pLeft == NULL)
            {
                pNodeDelete = pRoot;
                pRoot = pRoot->pRight;
                delete pNodeDelete;
            }
            else if (pRoot->pRight == NULL)
            {
                pNodeDelete = pRoot;
                pRoot = pRoot->pLeft;
                delete pNodeDelete;
            }
            else
            {
                pNodePredecessor = getInorderPredecessor(pRoot->pLeft);
                pRoot->pData   = pNodePredecessor->pData;
                pRoot->pLeft  = removeRecursive2(pRoot->pLeft, pNodePredecessor->pData, compare);
            }
        }
        return pRoot;
    }
    else
    {
        return NULL;
    }    
}

static void insertRootRecursive(TNode **ppRoot, const void *pData, CompareFunc compare)
{
    // base case
    if (*ppRoot == NULL)
    {
        *ppRoot = createNode(pData);
        return;
    }

    // general case
    if (compare((*ppRoot)->pData, pData) > 0)
    {
        insertRootRecursive(&(*ppRoot)->pLeft, pData, compare);
        BTreeRotateRight(ppRoot);
    }
    else
    {
        insertRootRecursive(&(*ppRoot)->pRight, pData, compare);
        BTreeRotateLeft(ppRoot);
    }
}

static void foreachAscRecursive(TNode *pRoot, CallbackFunc callback, void *pCallbackData)
{
    if (pRoot->pLeft != NULL)
    {
        foreachAscRecursive(pRoot->pLeft, callback, pCallbackData);
    }

    callback(pRoot->pData, pCallbackData);

    if (pRoot->pRight != NULL)
    {
        foreachAscRecursive(pRoot->pRight, callback, pCallbackData);
    }
}

static void foreachDescRecursive(TNode *pRoot, CallbackFunc callback, void *pCallbackData)
{
    if (pRoot->pRight != NULL)
    {
        foreachDescRecursive(pRoot->pRight, callback, pCallbackData);
    }

    callback(pRoot->pData, pCallbackData);

    if (pRoot->pLeft != NULL)
    {
        foreachDescRecursive(pRoot->pLeft, callback, pCallbackData);
    }
}

// -------------------------------------------------
// --- public functions ----------------------------
// -------------------------------------------------

BTree *BTreeCreate(CompareFunc compareCb)
{
    if (compareCb == NULL)
    {
        return NULL;
    }

    BTree *pTree   = new BTree;
    pTree->pRoot   = NULL;
    pTree->compare = compareCb;

    return pTree;
}

// -------------------------------------------------------
// --- iterative version ---------------------------------
// -------------------------------------------------------
//TNode *BTreeInsert(BTree *pTree, const void *pData)
//{
//    // if the tree is empty
//    if (pTree->pRoot == NULL)
//    {
//        pTree->pRoot = createNode(pData);
//        return pTree->pRoot;
//    }
//
//    // traverse the tree to find an appropriate position to insert the new node
//    int result;
//    TNode *pNodeTmp;
//    for (TNode *pNode = pTree->pRoot; pNode != NULL; )
//    {
//        if ((result = pTree->compare(pNode->pData, pData)) > 0)
//        {
//            pNodeTmp = pNode;
//            pNode    = pNode->pLeft;
//        }
//        else if (result < 0)
//        {
//            pNodeTmp = pNode;
//            pNode    = pNode->pRight;
//        }
//        else
//        {
//            // do not allow duplicate data
//            return NULL;
//        }
//    }
//
//    if (result > 0)
//    {
//        pNodeTmp->pLeft = createNode(pData);
//        return pNodeTmp->pLeft;
//    }
//    else
//    {
//        pNodeTmp->pRight = createNode(pData);
//        return pNodeTmp->pRight;
//    }
//}

// -------------------------------------------------------
// --- recursive version ---------------------------------
// -------------------------------------------------------
TNode *BTreeInsert(BTree *pTree, const void *pData)
{
    // if the tree is empty
    if (pTree->pRoot == NULL)
    {
        pTree->pRoot = createNode(pData);
        return pTree->pRoot;
    }

    return insertRecursive(pTree->pRoot, pData, pTree->compare);
}

TNode *BTreeSearch(BTree *pTree, const void *pKey)
{
    int result;

    for (TNode *pNode = pTree->pRoot; pNode != NULL; )
    {
        if ((result = pTree->compare(pNode->pData, pKey)) > 0)
        {
			pNode = pNode->pLeft;
        }
		else if (result < 0)
        {
			pNode = pNode->pRight;
        }
		else
        {
            return pNode;
        }
    }

    return NULL;
}

bool BTreeRemove(BTree *pTree, const void *pKey)
{
    return (removeRecursive(pTree->pRoot, pKey, pTree->compare) != NULL);
}

bool BTreeRemove2(BTree *pTree, const void *pKey)
{
    return (removeRecursive2(pTree->pRoot, pKey, pTree->compare) != NULL);
}

void BTreeRotateRight(TNode **ppRoot)
{
    TNode *pPivot = (*ppRoot)->pLeft;

    if (pPivot == NULL)
    {
        return;
    }

    (*ppRoot)->pLeft = pPivot->pRight;
    pPivot->pRight   = *ppRoot;
    *ppRoot          = pPivot;
}

void BTreeRotateLeft(TNode **ppRoot)
{
    TNode *pPivot = (*ppRoot)->pRight;

    if (pPivot == NULL)
    {
        return;
    }

    (*ppRoot)->pRight = pPivot->pLeft;
    pPivot->pLeft     = *ppRoot;
    *ppRoot           = pPivot;
}

TNode *BTreeInsertRoot(BTree *pTree, const void *pData)
{
    // check for duplicate key
    if (BTreeSearch(pTree, pData) != NULL)
    {
        return NULL;
    }

    insertRootRecursive(&pTree->pRoot, pData, pTree->compare);
    return pTree->pRoot;
}

void BTreeForeachAsc(BTree *pTree, CallbackFunc callback, void *pCallbackData)
{
    foreachAscRecursive(pTree->pRoot, callback, pCallbackData);
}

void BTreeForeachDesc(BTree *pTree, CallbackFunc callback, void *pCallbackData)
{
    foreachDescRecursive(pTree->pRoot, callback, pCallbackData);
}

void BTreeDestroy(BTree *pTree)
{
    truncateTree(pTree->pRoot);
    delete pTree;
}
