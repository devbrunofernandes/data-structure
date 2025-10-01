#include "myStack.hpp"
#include <string.h>

int precedence(char x)
{
    if(x == '+' || x == '-')
        return 1;
    else if(x == '*' || x == '/')
        return 2;

    return 0;
}

bool isOperand(char x)
{
    if(x == '+' || x == '-' || x == '*' || x == '/')
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
            if(precedence(infix[i]) > precedence(stk.stackTop()))
                stk.push(infix[i++]);
            else
                postfix[j++] = stk.pop();
        }
    }

    while(!stk.isEmpty())
        postfix[j++] = stk.pop();

    postfix[j] = '\0';

    return postfix;
}

int main()
{
    char *infix = "a+b*c-d/e";

    char *postfix = infixToPostfix(infix);

    printf("%s\n", postfix);

    return 0;
}