#include <stdio.h>
#include <string.h>
#include <ctype.h>

bool is_anagram(const char *s1, const char *s2)
{
    if (strlen(s1) != strlen(s2))
        return false;

    int index_table[26] = {0};
    int i = 0;
    char l;

    while (s1[i] != '\0')
    {
        l = tolower(s1[i]);
        index_table[l - 97]++;
        i++;
    }

    i = 0;
    while (s2[i] != '\0')
    {
        l = tolower(s2[i]);
        index_table[l - 97]--;
        if (index_table[l - 97] < 0)
            return false;
        i++;
    }

    return true;
} // time complexity: O(n)

int main()
{
    char s1[] = "verbose";
    char s2[] = "observe";

    if (is_anagram(s1, s2))
        printf("is anagram");
    else
        printf("not anagram");

    return 0;
}