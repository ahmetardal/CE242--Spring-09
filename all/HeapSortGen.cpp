// ==================================================
// - File______: HeapSortGen.cpp ____________________
// - Author____: Ahmet Ardal ________________________
// - Contact___: ardalahmet@hotmail.com _____________
// __________________________________________________
// - Copyright (c) 2009, Some Rights Reserved _______
// ==================================================

#include <iostream>
#include <cstring>
#include "HeapSortGen.h"

#define LeftChildIdx(i)     (2 * (i) + 1)
#define RightChildIdx(i)    (2 * (i) + 2)

// private function declarations
static void buildHeap(void *pArr, int arrLen, size_t itemLen, void *pTempBuf, CompareFunc compareCb);
static void heapify(void *pArr, int rootIdx, int endIdx, size_t itemLen, void *pTempBuf, CompareFunc compareCb);
static void swap(void *p1, void *p2, void *pTempBuf, size_t bufLen);

// private function definitions
static void buildHeap(void *pArr, int arrLen, size_t itemLen, void *pTempBuf, CompareFunc compareCb)
{
    // startIdx is assigned the index in pArr of the last parent node
    int startIdx = (arrLen - 2) / 2;

    while (startIdx >= 0)
    {
        // sift down the node at index startIdx to the proper place such that all nodes below
        // the startIdx index are in heap order
        heapify(pArr, startIdx, (arrLen - 1), itemLen, pTempBuf, compareCb);
        --startIdx;
        // after sifting down the root all nodes/elements are in heap order
    }
}

static void heapify(void *pArr, int rootIdx, int endIdx, size_t itemLen, void *pTempBuf, CompareFunc compareCb)
{
    // assume left child exists and it is the maximum of childs
    int maxChildIdx = LeftChildIdx(rootIdx);
    // if left child does not exist then exit
    if (maxChildIdx > endIdx)
    {
        return;
    }

    // if right child exists and it is bigger than the left child then make it the max child
    if (
        ((maxChildIdx + 1) <= endIdx) &&
        (compareCb(((byte *) pArr + itemLen * (maxChildIdx + 1)), ((byte *) pArr + itemLen * maxChildIdx)) > 0)
    )
    {
        ++maxChildIdx;
    }

    // if root has a child bigger than itself then swap them and recurse
    if (compareCb(((byte *) pArr + itemLen * maxChildIdx), ((byte *) pArr + itemLen * rootIdx)) > 0)
    {
        swap(((byte *) pArr + itemLen * maxChildIdx), ((byte *) pArr + itemLen * rootIdx), pTempBuf, itemLen);
        heapify((byte *) pArr, maxChildIdx, endIdx, itemLen, pTempBuf, compareCb);
    }
}

static void swap(void *p1, void *p2, void *pTempBuf, size_t bufLen)
{
    memcpy(pTempBuf, p1, bufLen);
    memcpy(p1, p2, bufLen);
    memcpy(p2, pTempBuf, bufLen);
}

// public function definitions
void HeapSort(void *pArr, size_t arrLen, size_t itemLen, CompareFunc compareCb)
{
    int endIdx = arrLen - 1;
    byte *pTempBuf = new (std::nothrow) byte[itemLen];

    // first place pArr in max-heap order
    buildHeap(pArr, arrLen, itemLen, pTempBuf, compareCb);

    while (endIdx > 0)
    {
        // swap the root(maximum value) of the heap with the last element of the heap
        swap(((byte *) pArr + endIdx * itemLen), pArr, pTempBuf, itemLen);

        // decrease the size of the heap by one so that the previous max value will
        // stay in its proper placement
        --endIdx;
        // put the heap back in max-heap order
        heapify(pArr, 0, endIdx, itemLen, pTempBuf, compareCb);
    }

    delete [] pTempBuf;
}
