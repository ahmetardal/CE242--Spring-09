
/* --------------------------------------------
 * --- File     : hw3-2b.cpp                ---
 * --- Author   : Ahmet ARDAL               ---
 * --- Contact  : ardalahmet@hotmail.com    ---
 * --------------------------------------------
 */

#include <iostream>
#include <cstring>
#include "Stack.h"

using namespace std;

bool isParenthesesWellFormed(const char *str);

int main()
{
    char inputStr[256];

    cout << "Enter a string: ";
    cin.getline(inputStr, 256);

    if (isParenthesesWellFormed(inputStr))
    {
        cout << "parentheses are well-formed..." << endl;
    }
    else
    {
        cout << "parentheses are not well-formed..." << endl;
    }
    cout << endl;

    return 0;
}

bool isParenthesesWellFormed(const char *str)
{
    const char opening[] = "({[";
    const char closing[] = ")}]";
    const char *pcFound;
    const char *pcPopped;

    Stack *pStParenth = StackCreate();

    // iterate through the characters of str
    while (*str != '\0')
    {
        if (strchr(opening, *str) != NULL)
        {
            StackPush(pStParenth, str);
        }
        else if ((pcFound = strchr(closing, *str)) != NULL)
        {
            if ((pcPopped = (const char *) StackPop(pStParenth)) == NULL)
            {
                StackDestroy(pStParenth);
                return false;
            }

            if (opening[pcFound - closing] != *pcPopped)
            {
                StackDestroy(pStParenth);
                return false;
            }
        }

        // advance the pointer to the next character
        ++str;
    }   // while (*str != '\0')

    // check whether any closing parenthesis is missing
    if (!StackIsEmpty(pStParenth))
    {
        StackDestroy(pStParenth);
        return false;
    }

    // string is well-formed, return true
    StackDestroy(pStParenth);
    return true;
}
