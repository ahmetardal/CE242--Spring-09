
/* --------------------------------------------
 * --- File     : hw3-2a.cpp                ---
 * --- Author   : Ahmet ARDAL               ---
 * --- Contact  : ardalahmet@hotmail.com    ---
 * --------------------------------------------
 */

#include <iostream>
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
    Stack *pStParenth = StackCreate();

    // iterate through the characters of str
    while (*str != '\0')
    {
        switch (*str)
        {
            // when an opening paranthesis is encountered, push it to the stack
            case '(':
            case '{':
            case '[':
                StackPush(pStParenth, str);
                break;

            // when a closing paranthesis is encountered,
            // pop a character from the stack and check it
            case ')':
            case '}':
            case ']':
            {
                const char *pc = (const char *) StackPop(pStParenth);
                if (pc == NULL)
                {
                    StackDestroy(pStParenth);
                    return false;
                }

                if ((*str == ')') && (*pc != '('))
                {
                    StackDestroy(pStParenth);
                    return false;
                }

                if ((*str == '}') && (*pc != '{'))
                {
                    StackDestroy(pStParenth);
                    return false;
                }

                if ((*str == ']') && (*pc != '['))
                {
                    StackDestroy(pStParenth);
                    return false;
                }
            }
                break;

            default:
                break;
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
