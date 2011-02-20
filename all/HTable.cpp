
/* --------------------------------------------
 * --- File     : HTable.c                  ---
 * --- Author   : Ahmet ARDAL               ---
 * --- Contact  : ardalahmet@hotmail.com    ---
 * --------------------------------------------
 */

#include <string.h>
#include "HTable.h"

/* -------------------------------------------------------------------------------------- */
/* private function declarations                                                          */
/* -------------------------------------------------------------------------------------- */

static unsigned int stdHashFunc(const void *pKey);
static unsigned int PJWHash(const char *pKey, int length);
static bool         isPrime(int num);


/* -------------------------------------------------------------------------------------- */
/* private function definitions                                                           */
/* -------------------------------------------------------------------------------------- */
static unsigned int stdHashFunc(const void *pKey)
{
    return PJWHash((const char *) pKey, strlen((const char *) pKey));
}

static unsigned int PJWHash(const char *pKey, int length)
{
    unsigned int val = 0;

    for (int i = 0; i < length; ++i)
    {
        unsigned int tmp;

        val = (val << 4) + pKey[i];

        if ((tmp = (val & 0xF0000000UL)))
        {
            val ^= (tmp >> 24);
            val ^= tmp;
        }
    }

    return val;
}

static bool isPrime(int num)
{
    if (num == 0 || num == 1)
    {
        return false;
    }
    if (num % 2 == 0)
    {
        return num == 2;
    }
    if (num % 3 == 0)
    {
        return num == 3;
    }
    if (num % 5 == 0)
    {
        return num == 5;
    }

    for (int i = 7; (i * i) <= num; i += 2)
    {
        if (num % i == 0)
        {
            return false;
        }
    }

    return true;
}

/* -------------------------------------------------------------------------------------- */
/* public function definitions                                                            */
/* -------------------------------------------------------------------------------------- */

unsigned int HTableGetSuggestedSize(unsigned int size)
{
    while (!isPrime((int) size))
    {
        ++size;
    }

    return size;
}

HTable *HTableCreate(unsigned int nBuckets, HashFunc hash, CompareFunc compare)
{
    HTable *pTable = NULL;

    /* allocate memory for HTable_t */
    pTable = new HTable;

    /* allocate memory for bucket list */
    pTable->bucketList = new Node*[nBuckets];

    /* init table data */
    pTable->nBuckets = nBuckets;
    pTable->nItems   = 0;
    pTable->hash     = (hash == NULL) ? stdHashFunc : hash;
    pTable->compare  = compare;

    /* init bucketList with NULL */
    for (int i = 0; i < pTable->nBuckets; ++i)
    {
        pTable->bucketList[i] = NULL;
    }

    return pTable;
}

Node *HTableInsert(HTable *pTable, const void *pKey, const void *pData)
{
    unsigned int idx;
    Node *pNode;

    /* allocate memory for node */
    pNode = new Node;

    /* hash the key and generate the index */
    idx = pTable->hash(pKey) % pTable->nBuckets;
    
    /* insert data to the node and insert the node to the head of the bucketlist at the index "idx" */
    pNode->pData = (void *) pData;
    pNode->pNext = pTable->bucketList[idx];
    pTable->bucketList[idx] = pNode;
    ++pTable->nItems;

    return pNode;
}

void *HTableRemove(HTable *pTable, const void *pKey, const void *pCmpData)
{
    void *pData = NULL;
    Node *pCur, *pPrev;
    unsigned int idx = pTable->hash(pKey) % pTable->nBuckets;

    /* handle first item outside of the loop */
    if ((pPrev = pTable->bucketList[idx]) == NULL)
    {
        return NULL;
    }

    if (pTable->compare(NodeData(pPrev), pCmpData) == 0)
    {
        pTable->bucketList[idx] = NodeNext(pTable->bucketList[idx]);
        pData = NodeData(pPrev);

        delete pPrev;
        --pTable->nItems;

        return pData;
    }

    for (pCur = NodeNext(pPrev); pCur != NULL; pPrev = pCur, pCur = NodeNext(pCur))
    {
        if (pTable->compare(NodeData(pCur), pCmpData) == 0)
        {
            pPrev->pNext = NodeNext(pCur);
            pData = NodeData(pPrev);

            delete pCur;
            --pTable->nItems;

            return pData;
        }
    }

    return NULL;
}

void *HTableLookup(HTable *pTable, const void *pKey, const void *pCmpData)
{
    unsigned int idx = pTable->hash(pKey) % pTable->nBuckets;

    for (Node *pNode = pTable->bucketList[idx]; pNode != NULL; pNode = NodeNext(pNode))
    {
        if (pTable->compare(pCmpData, NodeData(pNode)) == 0)
        {
            return NodeData(pNode);
        }
    }

    return NULL;
}

void HTableTruncate(HTable *pTable, DestroyFunc destroy)
{
    Node *pNode, *pNodeTmp;

    /* if node data will be freed */
    if (destroy != NULL)
    {
        /* iterate buckets */
        for (int i = 0; i < pTable->nBuckets; ++i)
        {
            /* iterate nodes */
            for (pNode = pTable->bucketList[i]; pNode != NULL; pNode = pNodeTmp)
            {
                pNodeTmp = NodeNext(pNode);
                destroy(NodeData(pNode));
                delete pNode;
            }
            pTable->bucketList[i] = NULL;
        }
    }
    else    /* if node data will not be freed */
    {
        /* iterate buckets */
        for (int i = 0; i < pTable->nBuckets; ++i)
        {
            /* iterate nodes */
            for (pNode = pTable->bucketList[i]; pNode != NULL; pNode = pNodeTmp)
            {
                pNodeTmp = NodeNext(pNode);
                delete pNode;
            }
            pTable->bucketList[i] = NULL;
        }
    }   /* end else */

    pTable->nItems = 0;
}

void HTableDestroy(HTable *pTable, DestroyFunc destroy)
{
    HTableTruncate(pTable, destroy);

    /* free bucketlist and table */
    delete [] pTable->bucketList;
    delete pTable;
}
