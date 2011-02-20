
/* --------------------------------------------
 * --- File     : hw5-1.cpp                 ---
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

    // search for words in the dictionary
    WordDef wd;
    while (true)
    {
        // get input
        cout << "Enter a word to search(enter \"---\" to exit): ";
        cin.getline(wd.word, 64);

        // if "---" is entered then exit
        if (!strcmp(wd.word, "---"))
        {
            break;
        }

        // search the word in the dictionary
        TNode *pNode = BTreeSearch(pTrDict, &wd);

        cout << endl;
        if (pNode != NULL)
        {
            cout << ((WordDef *) TNodeData(pNode))->definition << endl;
        }
        else
        {
            cout << "not found..." << endl;
        }
    }

    // delete WordDef objects and the tree
    BTreeForeachAsc(pTrDict, deleteWordDefsCb, NULL);
    BTreeDestroy(pTrDict);

    return 0;
}
