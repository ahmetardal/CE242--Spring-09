
/* --------------------------------------------
 * --- File     : testListAdvanced2.cpp     ---
 * --- Author   : Ahmet ARDAL               ---
 * --- Contact  : ardalahmet@hotmail.com    ---
 * --------------------------------------------
 */

#include <iostream>
#include "List.h"

using namespace std;

// List data structure advanced test code

struct Point
{
    int x;
    int y;
};

void printPoint(void *pData, void *pCallbackData)
{
    Point *p = (Point *) pData;

    cout << "x: " << p->x << ", y: " << p->y << endl;
}

void printString(void *pData, void *pCallbackData)
{
    cout << (const char *) pData << endl;
}

void deletePoint(void *pData, void *pCallbackData)
{
    delete (Point *) pData;
}

int main()
{
    const int N_POINTS = 12;

    // create a linked list for points
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

    // print points
    ListForeach(pListPoints, printPoint, NULL);
    cout << "--------------------------------" << endl;

    // delete all dynamically allocated Point objects
    /*for (Node *pNode = pListPoints->pHead; pNode != NULL; pNode = pNode->pNext)
    {
        delete (Point *) pNode->pData;
    }*/

    // delete all dynamically allocated Point objects using ListForeach
    ListForeach(pListPoints, deletePoint, NULL);

    ListDestroy(pListPoints);

    // -------------------------------------------------------
    // create a linked list for strings
    List *pListStrings = ListCreate();

    ListAppend(pListStrings, "adana");
    ListAppend(pListStrings, "ankara");
    ListAppend(pListStrings, "izmir");
    ListAppend(pListStrings, "bilecik");
    ListAppend(pListStrings, "istanbul");

    // print strings
    ListForeach(pListStrings, printString, NULL);
    cout << "--------------------------------" << endl;

    ListDestroy(pListStrings);

    return 0;
}
