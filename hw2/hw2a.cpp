
/* --------------------------------------------
 * --- File     : hw2a.cpp                  ---
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

void printGrade(void *pData, void *pCallbackData)
{
    cout <<
        "id: " << ((Grade *) pData)->studId <<
        ", grade: " << ((Grade *) pData)->grade << endl;
}

void deleteGrade(void *pData, void *pCallbackData)
{
    delete (Grade *) pData;
}

void filterFailedGrades(void *pData, void *pCallbackData)
{
    if (((Grade *) pData)->grade < 30)
    {
        ListAppend((List *) pCallbackData, pData);
    }
}

void filterPassedGrades(void *pData, void *pCallbackData)
{
    if (((Grade *) pData)->grade >= 30)
    {
        ListAppend((List *) pCallbackData, pData);
    }
}

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

    // filter main list for failed and passed grades
    ListForeach(pListGrades, filterPassedGrades, pListPassed);
    ListForeach(pListGrades, filterFailedGrades, pListFailed);

    // print lists

    cout << "--- all grades ------------------" << endl;
    ListForeach(pListGrades, printGrade, NULL);

    cout << "--- passed grades ---------------" << endl;
    ListForeach(pListPassed, printGrade, NULL);

    cout << "--- failed grades ---------------" << endl;
    ListForeach(pListFailed, printGrade, NULL);

    // destroy failed and passed lists
    ListDestroy(pListPassed);
    ListDestroy(pListFailed);

    // delete all Grade objects pListGrades contains and destroy pListGrades
    ListForeach(pListGrades, deleteGrade, NULL);
    ListDestroy(pListGrades);

    return 0;
}
