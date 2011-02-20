
/* --------------------------------------------
 * --- File     : hw1.cpp                   ---
 * --- Author   : Ahmet ARDAL               ---
 * --- Contact  : ardalahmet@hotmail.com    ---
 * --------------------------------------------
 */

#include <iostream>
#include "List.h"

using namespace std;

struct Grade
{
    int studId;
    int grade;
};

int main()
{
    List *pListGrades = ListCreate();
    int id, grade;
    Grade *pGrade;

    // read input
    while (true)
    {
        cout << "id: ";
        cin >> id;
        if (id < 0)
        {
            break;
        }
        cout << "grade: ";
        cin >> grade;

        pGrade = new Grade;
        pGrade->studId = id;
        pGrade->grade  = grade;
        ListAppend(pListGrades, pGrade);
    }

    // create failed and passed lists
    List *pListPassed = ListCreate();
    List *pListFailed = ListCreate();

    // filter main list
    for (Node *pNode = pListGrades->pHead; pNode != NULL; pNode = pNode->pNext)
    {
        Grade *pGrade = (Grade *) pNode->pData;

        if (pGrade->grade < 30)
        {
            ListAppend(pListFailed, pGrade);
        }
        else
        {
            ListAppend(pListPassed, pGrade);
        }
    }

    // print lists
    
    cout << "--- all grades ------------------" << endl;
    for (Node *pNode = pListGrades->pHead; pNode != NULL; pNode = pNode->pNext)
    {
        Grade *pGrade = (Grade *) pNode->pData;
        cout << "id: " << pGrade->studId << ", grade: " << pGrade->grade << endl;
    }

    cout << "--- passed grades ---------------" << endl;
    for (Node *pNode = pListPassed->pHead; pNode != NULL; pNode = pNode->pNext)
    {
        Grade *pGrade = (Grade *) pNode->pData;
        cout << "id: " << pGrade->studId << ", grade: " << pGrade->grade << endl;
    }

    cout << "--- failed grades ---------------" << endl;
    for (Node *pNode = pListFailed->pHead; pNode != NULL; pNode = pNode->pNext)
    {
        Grade *pGrade = (Grade *) pNode->pData;
        cout << "id: " << pGrade->studId << ", grade: " << pGrade->grade << endl;
    }

    // destroy passed and failed lists
    ListDestroy(pListPassed);
    ListDestroy(pListFailed);

    // delete all Grade objects pListGrades contains and destroy pListGrades
    for (Node *pNode = pListGrades->pHead; pNode != NULL; pNode = pNode->pNext)
    {
        delete (Grade *) pNode->pData;
    }
    ListDestroy(pListGrades);

    return 0;
}
