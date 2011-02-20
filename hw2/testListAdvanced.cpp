
/* --------------------------------------------
 * --- File     : testListAdvanced.cpp      ---
 * --- Author   : Ahmet ARDAL               ---
 * --- Contact  : ardalahmet@hotmail.com    ---
 * --------------------------------------------
 */

#include <iostream>
#include <cstring>
#include "List.h"

using namespace std;

// List data structure advanced test code

struct Point
{
    int x;
    int y;
};

void filterNegativeGrades(void *pData, void *pCallbackData)
{
    Point *p = (Point *) pData;

    if ((p->x < 0) && (p->y < 0))
    {
        ListAppend((List *) pCallbackData, p);
    }
}

int main()
{
    const int N_POINTS = 12;

    // create a linked list
    List *pListPoints = ListCreate();
    Point *pPoint;

    // create Points dynamically and insert them to the list
    for (int i = 0; i < N_POINTS; ++i)
    {
        pPoint = new Point;
        pPoint->x = i - 8;
        pPoint->y = pPoint->x;
        ListAppend(pListPoints, pPoint);
    }

    // create a new linked list
    List *pListNegativePoints = ListCreate();

    // filter negative points and add them to the list pListNegativePoints
    ListForeach(pListPoints, filterNegativeGrades, pListNegativePoints);

    cout << "--- all points ------------------" << endl;
    // traverse the list and print all items
    for (Node *pNode = pListPoints->pHead; pNode != NULL; pNode = pNode->pNext)
    {
        pPoint = (Point *) pNode->pData;
        cout << "x: " << pPoint->x << ", y: " << pPoint->y << endl;
    }

    cout << "--- negative points -------------" << endl;
    // traverse the list and print all items
    for (Node *pNode = pListNegativePoints->pHead; pNode != NULL; pNode = pNode->pNext)
    {
        pPoint = (Point *) pNode->pData;
        cout << "x: " << pPoint->x << ", y: " << pPoint->y << endl;
    }

    // delete all dynamically allocated Point objects and destroy the list
    for (Node *pNode = pListPoints->pHead; pNode != NULL; pNode = pNode->pNext)
    {
        delete (Point *) pNode->pData;
    }

    ListDestroy(pListNegativePoints);
    ListDestroy(pListPoints);

    return 0;
}
