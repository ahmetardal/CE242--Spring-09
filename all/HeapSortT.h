// ==================================================
// - File______: HeapSortT.h ________________________
// - Author____: Ahmet Ardal ________________________
// - Contact___: ardalahmet@hotmail.com _____________
// __________________________________________________
// - Copyright (c) 2009, Some Rights Reserved _______
// ==================================================

// generic HeapSort module with C++'s template mechanism

#ifndef HEAP_SORT_T_H_
#define HEAP_SORT_T_H_

// macro definitions
#define LeftChildIdx(i)     (2 * (i) + 1)
#define RightChildIdx(i)    (2 * (i) + 2)

// private function declarations
template <class T>
static void buildHeap(T *pArr, int arrSize);

template <class T>
static void heapify(T *pArr, int rootIdx, int endIdx);

template <class T>
static void swap(T *p1, T *p2);

// private function definitions
template <class T>
static void buildHeap(T *pArr, int arrSize)
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

template <class T>
static void heapify(T *pArr, int rootIdx, int endIdx)
{
    // assume left child exists and it is the maximum of childs
    int maxChildIdx = LeftChildIdx(rootIdx);
    // if left child does not exist then exit
    if (maxChildIdx > endIdx)
    {
        return;
    }

    // if right child exists and it is bigger than the left child then make it the max child
    if (((maxChildIdx + 1) <= endIdx) && (pArr[maxChildIdx + 1] > pArr[maxChildIdx]))
    {
        ++maxChildIdx;
    }

    // if root has a child bigger than itself then swap them and recurse
    if (pArr[maxChildIdx] > pArr[rootIdx])
    {
        swap(&pArr[maxChildIdx], &pArr[rootIdx]);
        heapify(pArr, maxChildIdx, endIdx);
    }
}

template <class T>
static void swap(T *p1, T *p2)
{
    T tmp = *p1;

    *p1 = *p2;
    *p2 = tmp;
}

// public function definitions
template <class T>
void HeapSort(T *pArr, int arrLen)
{
    int endIdx = arrLen - 1;

    // first place pArr in max-heap order
    buildHeap(pArr, arrLen);

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

#endif  // HEAP_SORT_T_H_
