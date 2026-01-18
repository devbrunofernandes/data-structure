#include "myStack.hpp"

bool isBalanced(string exp)
{
    Stack<char> stk;
    char bracket;

    for(char c: exp)
    {
        if(c == '(' || c == '[' || c == '{')
        {
            stk.push(c);
        }
        else if(c == ')' || c == ']' || c == '}')
        {
            if(stk.isEmpty())
                return false;

            bracket = stk.pop();
            if(bracket != c-2 && bracket != c-1)
                return false;
        }
    }

    if(stk.isEmpty())
        return true;

    return false;
}

int main()
{
    string exp = "{([a + b] * [c - d]) / e}";
    bool balancedExp = isBalanced(exp);
    
    if(balancedExp) {
        cout << exp << " is balanced." << endl;
    } else {
        cout << exp << " is not balanced." << endl;
    }

    return 0;
}