#include <iostream>
#include "myStack.hpp"

using namespace std;

bool isBalanced(char *exp)
{
    Stack<char> st;

    for(int i=0; exp[i] != '\0'; i++)
    {
        if(exp[i] == '(') 
        {
            st.push(exp[i]);
        } 
        else if(exp[i] == ')') 
        {
            if(st.isEmpty())
                return false;
            st.pop();
        }
    }
    if(st.isEmpty())
        return true;

    return false;
}

int main()
{
    char *exp = "((a+b)*(c-d)))";
    bool balancedExp = isBalanced(exp);
    
    if(balancedExp) {
        cout << exp << " is parenthesis balanced." << endl;
    } else {
        cout << exp << " is not parenthesis balanced." << endl;
    }

    return 0;
}