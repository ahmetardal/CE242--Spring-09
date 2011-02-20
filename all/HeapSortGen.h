// ==================================================
// - File______: HeapSortGen.h ______________________
// - Author____: Ahmet Ardal ________________________
// - Contact___: ardalahmet@hotmail.com _____________
// __________________________________________________
// - Copyright (c) 2009, Some Rights Reserved _______
// ==================================================

#ifndef HEAP_SORT_H_
#define HEAP_SORT_H_

typedef int (*CompareFunc)(const void *, const void *);
typedef unsigned char   byte;

// generic HeapSort() function with traditional void pointers
void HeapSort(void *pArr, size_t nItems, size_t itemLen, CompareFunc compareCb);

#endif  // HEAP_SORT_H_
