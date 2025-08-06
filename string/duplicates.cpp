#include <stdio.h>
#include <ctype.h>

// find letters that appears more than one time, print and show how many times it appears
void duplicates(const char *s)
{
    int i = 0;
    int hash_table[26] = {0};
    char letter;

    while (s[i] != '\0')
    {
        letter = tolower(s[i]);
        if (letter >= 97 && letter <= 122)
            hash_table[letter-97]++;
        i++;
    }

    for (int j = 0; j < 26; j++)
    {
        if (hash_table[j] > 1)
            printf("Letter '%c' has %d copies\n", j + 97, hash_table[j]);
    }
} // time complexity: O(n)

// find duplicates using bitwise operations
void duplicates_with_bit(const char *s)
{
    int bits32 = 0, i = 0, helper = 1;
    char letter;

    while (s[i] != '\0')
    {
        letter = tolower(s[i]);
        if (letter >= 97 && letter <= 122)
        {
            helper = 1;
            helper = helper << (letter - 97);
            if ((helper & bits32) > 0)
            {
                printf("%c is duplicated\n", s[i]);
            }
            else
            {
                bits32 = bits32 | helper;
            }   
        }
        i++;
    }
} // time complexity: O(n)

int main()
{
    char s[] = "finding";

    duplicates(s);
    printf("=======================\n");
    duplicates_with_bit(s);

    return 0;
}