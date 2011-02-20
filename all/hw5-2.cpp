
/* --------------------------------------------
 * --- File     : hw5-2.cpp                 ---
 * --- Author   : Ahmet ARDAL               ---
 * --- Contact  : ardalahmet@hotmail.com    ---
 * --------------------------------------------
 */

#include <iostream>
#include <fstream>
#include <cstring>
#include "BTree.h"

using namespace std;

void printDictAscending(TNode *pRoot);
void printDictDescending(TNode *pRoot);

const int WORD_LEN_MAX = 64;
const int DEF_LEN_MAX  = 256;

struct WordDef
{
    char word[WORD_LEN_MAX];
    char definition[DEF_LEN_MAX];
};

int cmpWordDefsCb(const void *pData1, const void *pData2)
{
    return strcmp(((WordDef *) pData1)->word, ((WordDef *) pData2)->word);
}

void deleteWordDefsCb(void *pData, void *pCallbackData)
{
    delete (WordDef *) pData;
}

int main()
{
    char line[512];
    char *pcDef;
    WordDef *pWordDef;
    BTree *pTrDict;

    // open the file
    ifstream f("forex-terms-data.txt");

    if (!f)
    {
        cerr << "cannot open file..." << endl;
        return EXIT_FAILURE;
    }

    // create the dictionary tree
    pTrDict = BTreeCreate(cmpWordDefsCb);

    // read file and construct the dictionary
    while (true)
    {
        f.getline(line, 512);
        if (f.eof())
        {
            break;
        }

        // split the line into two tokens as the word and its definition
        pcDef  = strchr(line, ':');
        *pcDef = '\0';

        // create a WordDef object and insert it to the dictionary
        pWordDef = new WordDef;
        strcpy(pWordDef->word, line);
        strcpy(pWordDef->definition, (pcDef + 1));
        BTreeInsert(pTrDict, pWordDef);
    }
    // close the file
    f.close();

    cout << "Printing dictionary in ascending order:" << endl;
    printDictAscending(pTrDict->pRoot);
    cout << endl << "==================================" << endl << endl;
    cout << "Printing dictionary in descending order:" << endl;
    printDictDescending(pTrDict->pRoot);

    // delete WordDef objects and the tree
    BTreeForeachAsc(pTrDict, deleteWordDefsCb, NULL);
    BTreeDestroy(pTrDict);

    return 0;
}

void printDictAscending(TNode *pRoot)
{
    if (TNodeLeft(pRoot) != NULL)
    {
        printDictAscending(TNodeLeft(pRoot));
    }

    WordDef *pWd = (WordDef *) pRoot->pData;
    cout << pWd->word << ":\n" << pWd->definition << endl;
    cout << "-----------------------------------" << endl;

    if (TNodeRight(pRoot) != NULL)
    {
        printDictAscending(TNodeRight(pRoot));
    }
}

void printDictDescending(TNode *pRoot)
{
    if (TNodeRight(pRoot) != NULL)
    {
        printDictDescending(TNodeRight(pRoot));
    }

    WordDef *pWd = (WordDef *) pRoot->pData;
    cout << pWd->word << ":\n" << pWd->definition << endl;
    cout << "-----------------------------------" << endl;

    if (TNodeLeft(pRoot) != NULL)
    {
        printDictDescending(TNodeLeft(pRoot));
    }
}
