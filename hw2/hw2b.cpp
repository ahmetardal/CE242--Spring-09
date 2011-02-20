
/* --------------------------------------------
 * --- File     : hw2b.cpp                  ---
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

const int LIST_FAILED_IDX = 0;
const int LIST_PASSED_IDX = 1;

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

void filterFailedAndPassedGrades(void *pData, void *pCallbackData)
{
    List **pListArr = (List **) pCallbackData;
    Grade *pGrade   = (Grade *) pData;

    if (pGrade->grade < 30)
    {
        ListAppend(pListArr[LIST_FAILED_IDX], pGrade);
    }
    else
    {
        ListAppend(pListArr[LIST_PASSED_IDX], pGrade);
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
    List *listArr[2];

    listArr[LIST_FAILED_IDX] = pListFailed;
    listArr[LIST_PASSED_IDX] = pListPassed;

    // filter main list for failed and passed grades
    ListForeach(pListGrades, filterFailedAndPassedGrades, listArr);

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
