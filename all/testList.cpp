
/* --------------------------------------------
 * --- File     : testList.cpp              ---
 * --- Author   : Ahmet ARDAL               ---
 * --- Contact  : ardalahmet@hotmail.com    ---
 * --------------------------------------------
 */

#include <iostream>
#include <cstring>
#include "List.h"

using namespace std;

// List data structure test code

struct Point
{
    int x;
    int y;
};

int main()
{
    const int N_POINTS = 7;

    // create a new linked list
    List *pListStrings = ListCreate();

    // append strings to the list
    ListAppend(pListStrings, "ankara");
    ListAppend(pListStrings, "istanbul");
    ListAppend(pListStrings, "izmir");

    // prepend strings to the list
    ListPrepend(pListStrings, "bilecik");
    ListPrepend(pListStrings, "yozgat");
    ListPrepend(pListStrings, "ordu");

    cout << "--- strings -----------------" << endl;
    // print list size
    cout << "list size: " << ListGetSize(pListStrings) << endl;
    // traverse the list and print all items
    for (Node *pNode = pListStrings->pHead; pNode != NULL; pNode = pNode->pNext)
    {
        cout << (const char *) pNode->pData << endl;
    }

    // destroy the list
    ListDestroy(pListStrings);

    // create a new linked list
    List *pListPoints = ListCreate();
    Point *pPoint;

    // create Points dynamically and insert them to the list
    for (int i = 0; i < N_POINTS; ++i)
    {
        pPoint = new Point;
        pPoint->x = i;
        pPoint->y = i * i;
        ListAppend(pListPoints, pPoint);
    }

    cout << "--- points ------------------" << endl;
    // print list size
    cout << "list size: " << ListGetSize(pListPoints) << endl;
    // traverse the list and print all items
    for (Node *pNode = pListPoints->pHead; pNode != NULL; pNode = pNode->pNext)
    {
        pPoint = (Point *) pNode->pData;
        cout << "x: " << pPoint->x << ", y: " << pPoint->y << endl;
    }

    // delete all dynamically allocated Point objects and destroy the list
    for (Node *pNode = pListPoints->pHead; pNode != NULL; pNode = pNode->pNext)
    {
        delete (Point *) pNode->pData;
    }
    ListDestroy(pListPoints);

    return 0;
}
