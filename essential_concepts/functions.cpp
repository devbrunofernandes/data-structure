#include <iostream>

using namespace std;

// function is a block of code that group some instruction to do a especific task.
// functions can also be called modules or procedures.
// monolithic program is a program that dont use functions, all code is write in one module.
// modular or procedural programing is the style of programing that split the code in functions.

int add(int a, int b); // the compiler reads the code from top to bottom, so you need to write the prototype of your function on top of the code.

int main()
{
    int x, y;
    x = 10;
    y = 20;
    int z = add(x, y); // this is calling a function. a, b are the arguments or actual parameters to the function.
    printf("Sum of a and b: %d\n", z); 

    return 0;
}

/*
   int              add         (int a, int b)
(return type) (function name) (formal parameters)                                   
*/
int add(int a, int b) // --> this is called the prototype of a function. 
{                     
    int c = a + b;    // } this is called the definition of a function.
    return c;         // }
}