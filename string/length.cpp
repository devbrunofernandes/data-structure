#include <stdio.h>
#include <cstring> // C language header file for strings
#include <string> // C++ header file for strings

// count the length of string
int len(const char *s)
{
    int i = 0;
    while (s[i] != '\0')
    {
        i++;
    }

    return i;
} // time complexity: O(n)

int main()
{
    char s[] = "welcome";
    std::string cpp_string = "welcome";

    printf("length of string: %d\n", len(s)); // %s for printing string.
    printf("length of string by default strlen: %d\n", strlen(s)); // strlen() is a C lang default function from <cstring> header.
    printf("length of string by C++ length: %d\n", cpp_string.length()); // call .length() method for C++ string objects

    return 0;
}