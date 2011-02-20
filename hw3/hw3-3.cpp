
/* --------------------------------------------
 * --- File     : hw3-3.cpp                 ---
 * --- Author   : Ahmet ARDAL               ---
 * --- Contact  : ardalahmet@hotmail.com    ---
 * --------------------------------------------
 */

#include <iostream>
#include "Stack.h"

using namespace std;

void printWordsReverse(char *str);

int main()
{
    char inputStr[256];

    cout << "Enter a string: ";
    //cin >> inputStr;
    cin.getline(inputStr, 256);
    /*cout << ":" << inputStr << ":" << endl;
    return 0;*/

    printWordsReverse(inputStr);
    cout << endl << endl;

    return 0;
}

void printWordsReverse(char *str)
{
    // create a Stack to store words in it
    Stack *pStWords = StackCreate();

    // push first word onto Stack
    StackPush(pStWords, str);

    // traverse the string,
    // separate words with null characters
    // and push more words onto Stack
    while (*str != '\0')
    {
        if (*str == ' ')
        {
            *str++ = '\0';
            StackPush(pStWords, str);
        }

        ++str;
    }

    // pop words from Stack and print them until the Stack becomes empty

    // first method
    const char *pWord;
    while ((pWord = (const char *) StackPop(pStWords)) != NULL)
    {
        cout << pWord << " ";
    }

    //// second method
    //for (
    //    const char *pWord = (const char *) StackPop(pStWords);
    //    pWord != NULL;
    //    pWord = (const char *) StackPop(pStWords)
    //)
    //{
    //    cout << pWord << " ";
    //}

    StackDestroy(pStWords);
}
