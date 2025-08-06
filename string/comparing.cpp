#include <stdio.h>

// compare if two strings are equal
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
} // time complexity: O(n)

int main()
{
    char A[] = "Painter";
    char B[] = "Painter";

    printf("strings are equal?: %d\n", compare(A, B));

    return 0;
}