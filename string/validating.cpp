#include <stdio.h>

// validate if the string contains only characters and numbers
bool validate(const char *s)
{
    bool is_valid = true;
    int i = 0;

    while (s[i] != '\0' && is_valid == true)
    {
        if (!(s[i] >= 65 && s[i] <= 90) && !(s[i] >= 97 && s[i] <= 122) && !(s[i] >= 48 && s[i] <= 57))
            is_valid = false;
        i++;
    }

    return is_valid;
} // time complexity: O(n)

int main()
{
    char s[] = "Ani321";

    printf("string is valid: %d\n", validate(s));

    return 0;
}