#include <stdio.h>
#include <string> // C++ header file for strings

int main()
{
    // string is the same as array of char delimited with \0 character to represent text.
    char a[20] = {'a', 'b', 'c', 'd', '\0'}; // declaration as normal array
    char s[] = "john"; // classic declaration of strings with double quotes
    std::string cpp_string = "Hello, C++"; // C++ string object by <string> header file

    printf("%s\n", s); // %s for printing string.
    printf("%s\n", a); // %s for printing string.

    char t[50];
    char t2[50];
    printf("Type your text two times\n");
    printf("first: ");
    gets(t); // read from keyboard input all text typed
    printf("second: ");
    scanf("%s", t2); // reads only the first word of keyboard input

    printf("Read with gets: %s\n", t);
    printf("Read with scanf: %s\n", t2);

    return 0;
}