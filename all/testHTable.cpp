
/* --------------------------------------------
 * --- File     : testBTree.cpp             ---
 * --- Author   : Ahmet ARDAL               ---
 * --- Contact  : ardalahmet@hotmail.com    ---
 * --------------------------------------------
 */

#include <iostream>
#include <cstring>
#include "HTable.h"

using namespace std;

struct Data
{
    const char *key;
    int val;
};

int compareDatas(const void *p1, const void *p2)
{
    return strcmp(((const Data *) p1)->key, ((const Data *) p2)->key);
}

#define NUM_ENTRIES     100
#define NUM_BUCKETS     (NUM_ENTRIES / 10)

int main(void)
{
    Data arr[] =
    {
        {"Ali",   0},
        {"Veli",  1},
        {"Hasan", 22},
        {"Cemal", 3},
        {"Kemal", 4},
        {"Temel", 5}
    };
    HTable *pTable;

    pTable = HTableCreate(HTableGetSuggestedSize(NUM_BUCKETS), NULL, compareDatas);

    for (int i = 0; i < (sizeof(arr) / sizeof(arr[0])); ++i)
    {
        HTableInsert(pTable, arr[i].key, &arr[i]);
    }

    Data key = {"Temel"};
    Data *pData = (Data *) HTableLookup(pTable, key.key, &key);

    if (pData != NULL)
    {
        cout << "data found: " << pData->val << endl;
    }
    else
    {
        cout << "data not found..." << endl;
    }

    HTableDestroy(pTable, NULL);
    puts("All Success!..");

    return 0;
}
