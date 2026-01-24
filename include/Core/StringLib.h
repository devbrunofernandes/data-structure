#ifndef DATASTRUCTURES_STRINGLIB_H
#define DATASTRUCTURES_STRINGLIB_H

#include <stdbool.h>

int lengthString(const char* s);

bool compareString(const char *a, const char *b);

void lowerString(char* s);

void upperString(char *s);

bool isAnagramString(const char *s1, const char *s2);

int countWords(const char *s);

int countConsonants(const char *s);

int countVowels(const char *s);

void reverseString(char* s);

bool isPalindrome(const char *s);

#endif //DATASTRUCTURES_STRINGLIB_H