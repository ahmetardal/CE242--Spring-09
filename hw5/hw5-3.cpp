
/* --------------------------------------------
 * --- File     : hw5-3.cpp                 ---
 * --- Author   : Ahmet ARDAL               ---
 * --- Contact  : ardalahmet@hotmail.com    ---
 * --------------------------------------------
 */

#include <iostream>
#include <fstream>
#include <cstring>
#include "BTree.h"

using namespace std;

const int WORD_LEN_MAX = 64;
const int DEF_LEN_MAX  = 256;

struct WordDef
{
    char word[WORD_LEN_MAX];
    char definition[DEF_LEN_MAX];
};

struct WordInterval
{
    char *word1;
    char *word2;
};

int cmpWordDefsCb(const void *pData1, const void *pData2)
{
    return strcmp(((WordDef *) pData1)->word, ((WordDef *) pData2)->word);
}

void printIntervalCb(void *pData, void *pCallbackData)
{
    WordDef      *pWd = (WordDef *)      pData;
    WordInterval *pWi = (WordInterval *) pCallbackData;

    // check whether or not the word is between word1 and word2
    if ((strcmp(pWd->word, pWi->word1) >= 0) && (strcmp(pWd->word, pWi->word2) <= 0))
    {
        cout << pWd->word << endl;
    }
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

    //WordInterval wi = {"Arbitration", "Envelope"};
    WordInterval wi = {"Cabinet Crowd", "Efficiency"};
    BTreeForeachAsc(pTrDict, printIntervalCb, &wi);

    // delete WordDef objects and the tree
    BTreeForeachAsc(pTrDict, deleteWordDefsCb, NULL);
    BTreeDestroy(pTrDict);

    return 0;
}
