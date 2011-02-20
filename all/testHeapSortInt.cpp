// ==================================================
// - File______: testHeapSortInt.cpp ________________
// - Author____: Ahmet Ardal ________________________
// - Contact___: ardalahmet@hotmail.com _____________
// __________________________________________________
// - Copyright (c) 2009, Some Rights Reserved _______
// ==================================================

#include <iostream>
#include "HeapSortInt.h"

using namespace std;

void printArr(const int *pArr, int arrSize);

int main()
{
    const int ARR_SIZE = 10;
    int arr[ARR_SIZE] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

    cout << "Unsorted: ";
    printArr(arr, ARR_SIZE);
    cout << endl;

    HeapSortInt((const int *) arr, ARR_SIZE);

    cout << "Sorted: ";
    printArr(arr, ARR_SIZE);
    cout << endl;

    return 0;
}

void printArr(const int *pArr, int arrSize)
{
    for (int i = 0; i < arrSize; ++i)
    {
        cout << pArr[i] << ", ";
    }
}
