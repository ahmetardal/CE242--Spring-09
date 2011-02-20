// ==================================================
// - File______: testHeapSortGen.cpp ________________
// - Author____: Ahmet Ardal ________________________
// - Contact___: ardalahmet@hotmail.com _____________
// __________________________________________________
// - Copyright (c) 2009, Some Rights Reserved _______
// ==================================================

#include <iostream>
#include <cstring>
#include "HeapSortGen.h"

using namespace std;

int cmpInts(const void *p1, const void *p2);
int cmpStrs(const void *p1, const void *p2);
void printIntArr(const int *pArr, int arrSize);
void printStrArr(const char **pArr, int arrSize);

// test code for generic HeapSort() function with traditional void pointers
int main()
{
    const int ARR_SIZE = 10;
    int arrInt[ARR_SIZE] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

    cout << "Unsorted: ";
    printIntArr(arrInt, ARR_SIZE);
    cout << endl;

    HeapSort(arrInt, ARR_SIZE, sizeof(int), cmpInts);

    cout << "Sorted: ";
    printIntArr(arrInt, ARR_SIZE);
    cout << endl;

    // _____________________________________________________
    char *arrStr[ARR_SIZE] =
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
    printStrArr((const char **) arrStr, ARR_SIZE);
    cout << endl;

    HeapSort(arrStr, ARR_SIZE, sizeof(char *), cmpStrs);

    cout << "Sorted: ";
    printStrArr((const char **) arrStr, ARR_SIZE);
    cout << endl;

    return 0;
}

int cmpStrs(const void *p1, const void *p2)
{
    return strcmp(*((const char **) p1), *((const char **) p2));
}

int cmpInts(const void *p1, const void *p2)
{
    return *((const int *) p1) - *((const int *) p2);
}

void printIntArr(const int *pArr, int arrSize)
{
    for (int i = 0; i < arrSize; ++i)
    {
        cout << pArr[i] << ", ";
    }
}

void printStrArr(const char **pArr, int arrSize)
{
    for (int i = 0; i < arrSize; ++i)
    {
        cout << pArr[i] << ", ";
    }
}
