#include <iostream>

int y = 0; // global variable is accessible by all functions and files.

int fun(int n) 
{
    static int x = 0; // static variable keep its value between recursive calls. differ from a global variable because its in fun() scope only.
    if (n > 0)
    {
        x++;
        y++;
        return fun(n - 1) + x;
    }
    return 0;
}

int main() 
{
    int r;
    r = fun(5);
    std::cout << r << std::endl;

    r = fun(5);
    std::cout << r << std::endl;

    return 0;
}