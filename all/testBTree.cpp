
/* --------------------------------------------
 * --- File     : testBTree.cpp             ---
 * --- Author   : Ahmet ARDAL               ---
 * --- Contact  : ardalahmet@hotmail.com    ---
 * --------------------------------------------
 */

#include <iostream>
#include "BTree.h"

using namespace std;

#define TEST1
//#define TEST2

void traverseAsc(TNode *pNode);
void traverseDesc(TNode *pNode);

int compareInts(const void *pData1, const void *pData2)
{
    return *((const int *) pData1) - *((const int *) pData2);
}

int main()
{
#if defined(TEST1)
    int arr[] = {10, 5, 12, 11};
    BTree *pTree = BTreeCreate(compareInts);

    BTreeInsert(pTree, &arr[0]);
    BTreeInsert(pTree, &arr[1]);
    BTreeInsert(pTree, &arr[2]);

    cout << *((int *) pTree->pRoot->pLeft->pData) << ", " << *((int *) pTree->pRoot->pData) << ", " << *((int *) pTree->pRoot->pRight->pData) << endl;
    BTreeInsertRoot(pTree, &arr[3]);
    cout << *((int *) pTree->pRoot->pLeft->pData) << ", " << *((int *) pTree->pRoot->pData) << ", " << *((int *) pTree->pRoot->pRight->pData) << endl;

    cout << "----------------------------" << endl;
    traverseAsc(pTree->pRoot);
    cout << "----------------------------" << endl;
    traverseDesc(pTree->pRoot);
    cout << "----------------------------" << endl;
    BTreeDestroy(pTree);
    return 0;
#endif  // #if TEST1

#if defined(TEST2)
    int arr[] = {10, 7, 6, 8, 13, 11, 14, 5, 9, 9, 1};
    BTree *pTree = BTreeCreate(compareInts);

    BTreeInsert(pTree, &arr[0]);
    BTreeInsert(pTree, &arr[1]);
    BTreeInsert(pTree, &arr[2]);
    BTreeInsert(pTree, &arr[3]);
    BTreeInsert(pTree, &arr[4]);
    BTreeInsert(pTree, &arr[5]);

    BTreeInsert(pTree, &arr[6]);
    BTreeInsert(pTree, &arr[7]);
    BTreeInsert(pTree, &arr[8]);
    BTreeInsert(pTree, &arr[9]);

    cout << "root: " << *((int *) pTree->pRoot->pData) << endl;
    BTreeInsertRoot(pTree, &arr[10]);
    cout << "root: " << *((int *) pTree->pRoot->pData) << endl;

    cout << "root: " << *((int *) pTree->pRoot->pData) << endl;
    //BTreeRotateRight(&pTree->pRoot);
    BTreeRotateLeft(&pTree->pRoot);
    cout << "root: " << *((int *) pTree->pRoot->pData) << endl;

    traverseAsc(pTree->pRoot);
    cout << "----------------------------" << endl;
    traverseDesc(pTree->pRoot);
    cout << "----------------------------" << endl;

    TNode *pNode = BTreeSearch(pTree, &arr[6]);
    if (pNode == NULL)
    {
        cout << "not found..." << endl;
    }
    else
    {
        cout << "data found: " << *((int *) pNode->pData) << endl;
    }
    cout << "----------------------------" << endl;

    if (BTreeRemove(pTree, &arr[0]))
    {
        cout << "removed..." << endl;
    }
    else
    {
        cout << "cannot remove..." << endl;
    }
    cout << "----------------------------" << endl;

    traverseAsc(pTree->pRoot);
    cout << "----------------------------" << endl;

    BTreeDestroy(pTree);
    return 0;
#endif  // #if TEST2
}

void traverseAsc(TNode *pNode)
{
    if (TNodeLeft(pNode) != NULL)
    {
        traverseAsc(TNodeLeft(pNode));
    }

    cout << *((int *) TNodeData(pNode)) << endl;

    if (TNodeRight(pNode) != NULL)
    {
        traverseAsc(TNodeRight(pNode));
    }
}

void traverseDesc(TNode *pNode)
{
    if (TNodeRight(pNode) != NULL)
    {
        traverseDesc(TNodeRight(pNode));
    }

    cout << *((int *) TNodeData(pNode)) << endl;

    if (TNodeLeft(pNode) != NULL)
    {
        traverseDesc(TNodeLeft(pNode));
    }
}
