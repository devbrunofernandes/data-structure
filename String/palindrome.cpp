#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// reverse function for use in palindrome
char *reverse(const char *s)
{
    int length = strlen(s);
    char *reversed = (char *)malloc(sizeof(char) * length + 1);
    reversed[length] = '\0';

    int i = 0, j = length - 1;

    while (s[i] != '\0')
    {
        reversed[j] = s[i];
        j--;
        i++;
    }

    return reversed;
}

// compare for use in palindrome
bool compare(const char *a, const char *b)
{
    int i = 0, j = 0;
    int is_equal = true;

    while (is_equal == true && !(a[i] == '\0' && b[j] == '\0'))
    {
        if (a[i] == b[i])
        {
            i++;
            j++;
        }
        else
        {
            is_equal = false;
        }
    }

    return is_equal;
}

// check if string is palindrome. palindrome is a word that in his reverse form is equal to original form
bool is_palindrome(const char *s)
{
    char *reversed = reverse(s);
    bool result = compare(s, reversed);
    free(reversed);

    return result;
} // time complexity: O(n)

int main()
{
    char s[] = "madam";

    printf("string is palindrome?: %d\n", is_palindrome(s));

    return 0;
}