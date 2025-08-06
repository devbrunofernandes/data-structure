#include <stdio.h>
#include <ctype.h> // C lang header that have tolower and toupper functions

// loop for all characters of string 's' and check if the char is upper case in ASCII, if true then sum 32 to turn lower in ASCII values
void lower(char *s)
{
    // ASCII decimal representation of upper case charactes: A = 65, B = 66 ... Z = 90
    // ASCII decimal representation of lower case charactes: a = 97, b = 98 ... Z = 122
    int i = 0;

    while (s[i] != '\0')
    {
        if (s[i] >= 65 && s[i] <= 90)
        {
            // that is also a default function of C lang that is tolower(char) from <ctype.h> header.
            s[i] += 32;
        }
        i++;
    }
}

// loop for all characters of string 's' and check if the char is lower case in ASCII, if true then subtract 32 to turn upper in ASCII values
void upper(char *s)
{
    // ASCII decimal representation of upper case charactes: A = 65, B = 66 ... Z = 90
    // ASCII decimal representation of lower case charactes: a = 97, b = 98 ... Z = 122
    int i = 0;

    while (s[i] != '\0')
    {
        if (s[i] >= 97 && s[i] <= 122)
        {
            // that is also a default function of C lang that is toupper(char) from <ctype.h> header.
            s[i] -= 32;
        }
        i++;
    }
}

int main()
{
    char s[] = "WELCOME";

    lower(s); // turn to lower case
    printf("transforming in lower case: %s\n", s);

    upper(s); // turn to upper case
    printf("transforming in upper case: %s\n", s);

    return 0;
}