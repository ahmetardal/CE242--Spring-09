// ==================================================
// - File______: testHeapSortStr.cpp ________________
// - Author____: Ahmet Ardal ________________________
// - Contact___: ardalahmet@hotmail.com _____________
// __________________________________________________
// - Copyright (c) 2009, Some Rights Reserved _______
// ==================================================

#include <iostream>
#include "HeapSortStr.h"

using namespace std;

void printArr(const char **pArr, int arrSize);

int main()
{
    const int ARR_SIZE = 10;
    char *arr[ARR_SIZE] =
    {
        "Zonguldak",
        "Rize",
        "Mardin",
        "Konya",
        "Kayseri",
        "Hatay",
        "Bursa",
        "Bitlis",
        "Antalya",
        "Ankara"
    };

    cout << "Unsorted: ";
    printArr((const char **) arr, ARR_SIZE);
    cout << endl;

    HeapSortStr(arr, ARR_SIZE);

    cout << "Sorted: ";
    printArr((const char **) arr, ARR_SIZE);
    cout << endl;

    return 0;
}

void printArr(const char **pArr, int arrSize)
{
    for (int i = 0; i < arrSize; ++i)
    {
        cout << pArr[i] << ", ";
    }
}
