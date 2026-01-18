#include <stdio.h>
#include <stdlib.h>

int len(const char *s)
{
    int i = 0;
    while (s[i] != '\0')
    {
        i++;
    }

    return i;
}

// create a reversed version of string and return it
char* reverse(const char *s)
{
    int length = len(s);
    char *reversed = (char *) malloc(sizeof(char) * length + 1);
    reversed[length] = '\0';

    int i = 0, j = length-1;

    while (s[i] != '\0')
    {
        reversed[j] = s[i];
        j--;
        i++;
    }

    return reversed;
} // time complexity: O(n)

int main()
{
    char s[] = "python";
    char *reversed = reverse(s);

    printf("reversed string: %s\n", reversed);
    free(reversed);

    return 0;
}