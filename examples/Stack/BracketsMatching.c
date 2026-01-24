#include "Core/Stack/StackLinked.h"
#include <stdbool.h>
#include <stdio.h>

bool isBalanced(const char* exp) {
    StackLinked* stk = stlCreate();

    for(int i = 0; exp[i] != '\0'; i++) {
        char c = exp[i];

        if(c == '(' || c == '[' || c == '{') {
            stlPush(stk, c);
        } else if(c == ')' || c == ']' || c == '}') {
            if(stlIsEmpty(stk))
                return false;

            char bracket = *(stlTop(stk));
            stlPop(stk);
            if(bracket != c-2 && bracket != c-1)
                return false;
        }
    }

    if(stlIsEmpty(stk))
        return true;

    return false;
}

int main()
{
    char* exp = "{([a + b] * [c - d]) / e}";
    bool balancedExp = isBalanced(exp);
    
    if(balancedExp) {
        printf("%s Balanced Exp\n", exp);
    } else {
        printf("%s Not Balanced Exp\n", exp);
    }

    return 0;
}