#include <stdio.h>
#include <stdbool.h>
#include "Core/Stack/StackLinked.h"

bool isBalanced(char *exp) {
    StackLinked* st = stlCreate();

    for(int i=0; exp[i] != '\0'; i++) {
        if(exp[i] == '(')  {
            stlPush(st, exp[i]);
        } else if(exp[i] == ')') {
            if(stlIsEmpty(st))
                return false;
            stlPop(st);
        }
    }
    if(stlIsEmpty(st))
        return true;

    return false;
}

int main() {
    char *exp = "((a+b)*(c-d)))";
    bool balancedExp = isBalanced(exp);
    
    if(balancedExp) {
        printf("%s is parenthesis balanced.", exp);
    } else {
        printf("%s is not parenthesis balanced.", exp);
    }

    return 0;
}