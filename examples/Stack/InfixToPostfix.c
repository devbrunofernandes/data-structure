#include "Core/Stack/StackLinked.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

int precedenceOutStack(char x) {
    if(x == '+' || x == '-')
        return 1;
    if(x == '*' || x == '/')
        return 3;
    if(x == '^')
        return 6;
    if(x == '(')
        return 7;

    if (x == '#')
        return -1;

    return 0;
}

int precedenceInStack(char x) {
    if(x == '+' || x == '-')
        return 2;
    if(x == '*' || x == '/')
        return 4;
    if(x == '^')
        return 5;
    if(x == '(')
        return 0;

    if (x == '#')
        return -1;

    return 0;
}

bool isOperand(char x) {
    if(x == '+' || x == '-' || x == '*' || x == '/' || x == '^')
        return false;
    if(x == '(' || x == ')')
        return false;

    return true;
}

char* infixToPostfix(char* infix) {
    int i=0, j=0, len = strlen(infix);
    char *postfix = (char *) malloc(len+1 * sizeof(char));
    StackLinked* stk = stlCreate();
    stlPush(stk, '#');

    while(infix[i] != '\0') {
        if(isOperand(infix[i])) {
            postfix[j++] = infix[i++];
        } else {
            if(precedenceOutStack(infix[i]) > precedenceInStack(*stlTop(stk))) {
                stlPush(stk, infix[i++]);
            } else {
                if(precedenceOutStack(infix[i]) != precedenceInStack(*stlTop(stk))) {
                    postfix[j++] = *stlTop(stk);
                    stlPop(stk);
                } else {
                    stlPop(stk);
                    i++;
                }
            }
        }
    }

    while(!stlIsEmpty(stk)) {
        const char c = *stlTop(stk);
        if (c != '#') postfix[j++] = c;
        stlPop(stk);
    }

    postfix[j] = '\0';

    return postfix;
}

/*
    evaluate only work for some specific operation with specific operators.
    @operations -> +,*,-,/
    @operators  -> only single digits positive numbers
*/
int evaluate(char* postfix) {
    int x1,x2,r;
    StackLinked* stk = stlCreate();

    for(int i=0; postfix[i]!='\0'; i++) {
        if(isOperand(postfix[i])) {
            stlPush(stk, postfix[i] - '0');
        } else {
            x2 = *stlTop(stk);
            stlPop(stk);
            x1 = *stlTop(stk);
            stlPop(stk);

            switch (postfix[i]) 
            {
                case '+':
                    r = x1 + x2;
                    break;
                case '-':
                    r = x1 - x2;
                    break;
                case '*':
                    r = x1 * x2;
                    break;
                case '/':
                    r = x1 / x2;
                    break;
            }
            stlPush(stk, r);
        }
    }
    int result = *stlTop(stk);
    stlPop(stk);

    return result;
}

int main() {
    char infix[256];

    printf("Digit a valid operation: ");
    scanf("%s", infix);


    char *postfix = infixToPostfix(infix);
    printf("%s\n", postfix);

    printf("Result of '234*+82/-' --> %d\n", evaluate("234*+82/-"));

    free(postfix);

    return 0;
}