#include <ctype.h>
#include <stdbool.h>
#include <string.h>

#include "Core/StringLib.h"

int lengthString(const char* s) {
    int i = 0;

    while (s[i] != '\0')
        i++;

    return i;
}

bool compareString(const char *a, const char *b) {
    int i = 0, j = 0;
    int is_equal = true;

    while (is_equal == true && !(a[i] == '\0' && b[j] == '\0')) {
        if (a[i] == b[i]) {
            i++;
            j++;
        } else {
            is_equal = false;
        }
    }

    return is_equal;
}

void lowerString(char* s) {
    int i = 0;

    while (s[i] != '\0') {
        if (s[i] >= 'A' && s[i] <= 'Z')
            s[i] += 32;

        i++;
    }
}

void upperString(char *s) {
    int i = 0;

    while (s[i] != '\0') {
        if (s[i] >= 'a' && s[i] <= 'z')
            s[i] -= 32;

        i++;
    }
}

bool isAnagramString(const char *s1, const char *s2) {
    if (lengthString(s1) != lengthString(s2)) return false;

    int index_table[26] = {0};
    int i = 0;

    while (s1[i] != '\0') {
        const char l = tolower(s1[i]);
        index_table[l - 'a']++;
        i++;
    }

    i = 0;
    while (s2[i] != '\0') {
        const char  l = tolower(s2[i]);
        index_table[l - 'a']--;
        if (index_table[l - 'a'] < 0)
            return false;
        i++;
    }

    return true;
}

int countWords(const char *s) {
    int i = 0, words = 0;

    while (s[i] != '\0') {
        if (s[i] == ' ' && i > 0 && s[i - 1] != ' ')
            words++;

        i++;
    }

    if (i > 0 && s[i - 1] != isspace(s[i])) words++;

    return words;
}

int countConsonants(const char *s) {
    int i = 0, consonants = 0;

    while (s[i] != '\0') {
        const char l = tolower(s[i]);
        if (!(l == 'a' || l == 'e' || l == 'i' || l == 'o' || l == 'u') && (l >= 97 && l <= 122))
            consonants++;

        i++;
    }

    return consonants;
}

int countVowels(const char *s) {
    int i = 0, vowels = 0;

    while (s[i] != '\0') {
        const char l = tolower(s[i]);
        if (l == 'a' || l == 'e' || l == 'i' || l == 'o' || l == 'u')
            vowels++;

        i++;
    }

    return vowels;
}

void reverseString(char* s) {
    int i = 0;
    int j = lengthString(s) - 1;

    while (i < j) {
        const char temp = s[j];
        s[j] = s[i];
        s[i] = temp;

        j--;
        i++;
    }
}

bool isPalindrome(const char *s) {
    int i = 0;
    int j = lengthString(s) - 1;

    while (i < j) {
        if (s[i] != s[j]) return false;
        j--;
        i++;
    }

    return true;
}

