
/* --------------------------------------------
 * --- File     : HTable.h                  ---
 * --- Author   : Ahmet ARDAL               ---
 * --- Contact  : ardalahmet@hotmail.com    ---
 * --------------------------------------------
 */

#ifndef HTABLE_H_
#define HTABLE_H_

#include "List.h"

/* type definitions */

typedef unsigned int (*HashFunc)(const void *);
typedef int (*CompareFunc)(const void *pData1, const void *pData2);
typedef void (*DestroyFunc)(void *);

struct HTable
{
    Node **bucketList;   /* pointer to buckets list              */
    int    nBuckets;     /* number of buckets in the hash table  */
    int    nItems;       /* number of items in the hash table    */

    HashFunc    hash;      /* pointer to hash function             */
    CompareFunc compare;   /* pointer to comparison function       */
};

/* public function declarations */

unsigned int HTableGetSuggestedSize(unsigned int size);

HTable *HTableCreate(unsigned int nBuckets, HashFunc hash, CompareFunc compare);
Node   *HTableInsert(HTable *pTable, const void *pKey, const void *pData);
void   *HTableRemove(HTable *pTable, const void *pKey, const void *pCmpData);
void   *HTableLookup(HTable *pTable, const void *pKey, const void *pCmpData);
void    HTableTruncate(HTable *pTable, DestroyFunc destroy);
void    HTableDestroy(HTable *pTable, DestroyFunc destroy);

#endif  /* HTABLE_H_ */
