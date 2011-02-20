// ==================================================
// - File______: testHeapSortT.cpp __________________
// - Author____: Ahmet Ardal ________________________
// - Contact___: ardalahmet@hotmail.com _____________
// __________________________________________________
// - Copyright (c) 2009, Some Rights Reserved _______
// ==================================================

#include <iostream>
#include "HeapSortT.h"
#include "Point2D.h"

using namespace std;

template <class T>
void printArr(const T *pArr, int arrSize);

// test code for generic HeapSort() function with C++ templates
int main()
{
    const int ARR_SIZE = 10;
    int arrInt[ARR_SIZE] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

    cout << "Unsorted: ";
    printArr(arrInt, ARR_SIZE);
    cout << endl;

    HeapSort(arrInt, ARR_SIZE);

    cout << "Sorted: ";
    printArr(arrInt, ARR_SIZE);
    cout << endl << endl;
    
    // =============================================
    Point2D arrPt[5];

    arrPt[0].setXY(9, 8);
    arrPt[1].setXY(7, 6);
    arrPt[2].setXY(5, 4);
    arrPt[3].setXY(3, 2);
    arrPt[4].setXY(1, 0);

    cout << "Unsorted: ";
    printArr(arrPt, 5);
    cout << endl;

    HeapSort(arrPt, 5);

    cout << "Sorted: ";
    printArr(arrPt, 5);
    cout << endl << endl;

    return 0;
}

template <class T>
void printArr(const T *pArr, int arrSize)
{
    for (int i = 0; i < arrSize; ++i)
    {
        cout << pArr[i] << ", ";
    }
}
