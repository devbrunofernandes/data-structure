#include "myStack.hpp"
#include <cstdio>
#include <string.h>

int precedenceOutStack(char x)
{
    if(x == '+' || x == '-')
        return 1;
    else if(x == '*' || x == '/')
        return 3;
    else if(x == '^')
        return 6;
    else if(x == '(')
        return 7;

    return 0;
}

int precedenceInStack(char x)
{
    if(x == '+' || x == '-')
        return 2;
    else if(x == '*' || x == '/')
        return 4;
    else if(x == '^')
        return 5;
    else if(x == '(')
        return 0;

    return 0;
}

bool isOperand(char x)
{
    if(x == '+' || x == '-' || x == '*' || x == '/' || x == '^')
        return false;
    else if(x == '(' || x == ')')
        return false;
    else
        return true;
}

// C language style string
char *infixToPostfix(char *infix)
{
    int i=0, j=0, len = strlen(infix);
    char *postfix = (char *) malloc(len+1 * sizeof(char));
    Stack<char> stk;

    while(infix[i] != '\0')
    {
        if(isOperand(infix[i]))
        {
            postfix[j++] = infix[i++];
        }
        else 
        {
            if(precedenceOutStack(infix[i]) > precedenceInStack(stk.stackTop()))
                stk.push(infix[i++]);
            else
                if(precedenceOutStack(infix[i]) != precedenceInStack(stk.stackTop()))
                    postfix[j++] = stk.pop();
                else {
                    stk.pop();
                    i++;
                }
        }
    }

    while(!stk.isEmpty())
        postfix[j++] = stk.pop();

    postfix[j] = '\0';

    return postfix;
}

/*
    evaluate only work for some especific operation with especific operators.
    @operations -> +,*,-,/
    @operators  -> only single digits positive numbers
*/
int evaluate(char *postfix)
{
    int x1,x2,r;
    Stack<int> stk;

    for(int i=0; postfix[i]!='\0'; i++)
    {
        if(isOperand(postfix[i]))
        {
            stk.push(postfix[i] - '0');
        }
        else
        {
            x2 = stk.pop();
            x1 = stk.pop();

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
            stk.push(r);
        }
    }
    return stk.pop();
}

int main()
{
    char infix[256];

    printf("Digit a valid operation: ");
    scanf("%s", infix);


    char *postfix = infixToPostfix(infix);
    printf("%s\n", postfix);

    printf("Result of '234*+82/-' --> %d\n", evaluate("234*+82/-"));

    return 0;
}