// ==================================================
// - File______: HeapSortStr.cpp ____________________
// - Author____: Ahmet Ardal ________________________
// - Contact___: ardalahmet@hotmail.com _____________
// __________________________________________________
// - Copyright (c) 2009, Some Rights Reserved _______
// ==================================================

#include <cstring>
#include "HeapSortStr.h"

// macro definitions
#define LeftChildIdx(i)     (2 * (i) + 1)
#define RightChildIdx(i)    (2 * (i) + 2)

// private function declarations
static void buildHeap(char **pArr, int arrSize);
static void heapify(char **pArr, int rootIdx, int endIdx);
static void swap(char **p1, char **p2);

// private function definitions
static void buildHeap(char **pArr, int arrSize)
{
    // startIdx is assigned the index in pArr of the last parent node
    int startIdx = (arrSize - 2) / 2;

    while (startIdx >= 0)
    {
        // sift down the node at index startIdx to the proper place such that all nodes below
        // the startIdx index are in heap order
        heapify(pArr, startIdx, (arrSize - 1));
        --startIdx;
        // after sifting down the root all nodes/elements are in heap order
    }
}

//static void heapify(int *pArr, int rootIdx, int endIdx)
//{
//    while ((rootIdx * 2 + 1) <= endIdx)   // While the root has at least one child
//    {
//        int childIdx = rootIdx * 2 + 1; // root*2+1 points to the left child
//
//        // If the child has a sibling and the child's value is less than its sibling's...
//        if (((childIdx + 1) <= endIdx) && (pArr[childIdx] < pArr[childIdx + 1]))
//        {
//            ++childIdx;    // then point to the right child instead
//        }
//
//        if (pArr[rootIdx] < pArr[childIdx]) // out of max-heap order
//        {
//            swap(&pArr[rootIdx], &pArr[childIdx]);
//            rootIdx = childIdx;   // repeat to continue sifting down the child now
//        }
//        else
//        {
//            return;
//        }
//    }
//}

static void heapify(char **pArr, int rootIdx, int endIdx)
{
    // assume left child exists and it is the maximum of childs
    int maxChildIdx = LeftChildIdx(rootIdx);
    // if left child does not exist then exit
    if (maxChildIdx > endIdx)
    {
        return;
    }

    // if right child exists and it is bigger than the left child then make it the max child
    if (((maxChildIdx + 1) <= endIdx) && (strcmp(pArr[maxChildIdx + 1], pArr[maxChildIdx]) > 0))
    {
        ++maxChildIdx;
    }

    // if root has a child bigger than itself then swap them and recurse
    if (strcmp(pArr[maxChildIdx], pArr[rootIdx]) > 0)
    {
        swap(&pArr[maxChildIdx], &pArr[rootIdx]);
        heapify(pArr, maxChildIdx, endIdx);
    }
}

static void swap(char **p1, char **p2)
{
    char *tmp = *p1;

    *p1 = *p2;
    *p2 = tmp;
}

// public function definitions
void HeapSortStr(char **pArr, int arrSize)
{
    int endIdx = arrSize - 1;

    // first place pArr in max-heap order
    buildHeap(pArr, arrSize);

    while (endIdx > 0)
    {
        // swap the root(maximum value) of the heap with the last element of the heap
        swap(&pArr[endIdx], &pArr[0]);

        // decrease the size of the heap by one so that the previous max value will
        // stay in its proper placement
        --endIdx;
        // put the heap back in max-heap order
        heapify(pArr, 0, endIdx);
    }
}
