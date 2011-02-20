
/* --------------------------------------------
 * --- File     : testStack.cpp             ---
 * --- Author   : Ahmet ARDAL               ---
 * --- Contact  : ardalahmet@hotmail.com    ---
 * --------------------------------------------
 */

#include <iostream>
#include "Stack.h"

using namespace std;

// ====================================================================
// Stack data structure test code
int main()
{
    // create a new stack
    Stack *pStack = StackCreate();

    // push strings to the stack
    StackPush(pStack, "ankara");
    StackPush(pStack, "istanbul");
    StackPush(pStack, "izmir");
    StackPush(pStack, "yozgat");
    StackPush(pStack, "bilecik");

    // pop strings from the stack and print them
    const char *str;
    while ((str = (const char *) StackPop(pStack)) != NULL)
    {
        cout << str << endl;
    }

    // destroy the stack
    StackDestroy(pStack);

    return 0;
}
