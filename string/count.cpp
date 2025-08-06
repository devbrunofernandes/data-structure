#include <stdio.h>
#include <ctype.h>

int count_words(const char *s)
{
    int i = 0, words = 0;
    while (s[i] != '\0')
    {
        if (s[i] == ' ' && s[i-1] != ' ')
        {
            words++;
        }
        i++;
    }

    return words + 1;
} // time complextity: O(n)

int count_consonants(const char *s)
{
    int i = 0, consonants = 0;
    char l;
    while (s[i] != '\0')
    {
        l = tolower(s[i]);
        if (!(l == 'a' || l == 'e' || l == 'i' || l == 'o' || l == 'u') && (l >= 97 && l <= 122))
        {
            consonants++;
        }
        i++;
    }

    return consonants;
} // time complextity: O(n)

int count_vowels(const char *s)
{
    int i = 0, vowels = 0;
    char l;
    while (s[i] != '\0')
    {
        l = tolower(s[i]);
        if (l == 'a' || l == 'e' || l == 'i' || l == 'o' || l == 'u')
        {
            vowels++;
        }
        i++;
    }

    return vowels;
} // time complextity: O(n)

int main()
{
    char s[] = "How are you";

    printf("Number of words in the string: %d\n", count_words(s));
    printf("Number of vowels in the string: %d\n", count_vowels(s));
    printf("Number of consonants in the string: %d\n", count_consonants(s));

    return 0;
}