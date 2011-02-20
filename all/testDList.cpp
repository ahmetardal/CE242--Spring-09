
/* --------------------------------------------
 * --- File     : testDList.cpp             ---
 * --- Author   : Ahmet ARDAL               ---
 * --- Contact  : ardalahmet@hotmail.com    ---
 * --------------------------------------------
 */

#include <iostream>
#include "DList.h"

using namespace std;

void printStrCb(void *pData, void *pCallbackData)
{
    cout << (const char *) pData << endl;
}

int main()
{
    DList *pList = DListCreate();

    DListAppend(pList, "adana");
    DListAppend(pList, "ankara");
    DListAppend(pList, "izmir");
    DListAppend(pList, "istanbul");
    DListAppend(pList, "bilecik");

    for (DNode *pNode = DListHead(pList); pNode != NULL; pNode = DNodeNext(pNode))
    {
        cout << (const char *) DNodeData(pNode) << endl;
    }
    cout << "------------------------------------------" << endl;
    for (DNode *pNode = DListTail(pList); pNode != NULL; pNode = DNodePrev(pNode))
    {
        cout << (const char *) DNodeData(pNode) << endl;
    }

    cout << "------------------------------------------" << endl;

    DListForeach(pList, printStrCb, NULL, DLIST_TD_HEAD_TO_TAIL);
    cout << "------------------------------------------" << endl;
    DListForeach(pList, printStrCb, NULL, DLIST_TD_TAIL_TO_HEAD);

    DListRemoveNode(pList, DListHead(pList));
    DListRemoveNode(pList, DListTail(pList));
    cout << "------------------------------------------" << endl;
    DListForeach(pList, printStrCb, NULL, DLIST_TD_HEAD_TO_TAIL);

    DListRemoveNode(pList, DListHead(pList));
    DListRemoveNode(pList, DListTail(pList));
    cout << "------------------------------------------" << endl;
    DListForeach(pList, printStrCb, NULL, DLIST_TD_HEAD_TO_TAIL);

    DListRemoveNode(pList, DListHead(pList));
    DListRemoveNode(pList, DListTail(pList));
    cout << "------------------------------------------" << endl;
    DListForeach(pList, printStrCb, NULL, DLIST_TD_HEAD_TO_TAIL);

    DListDestroy(pList);

    return 0;
}
