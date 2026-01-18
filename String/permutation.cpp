#include <stdio.h>

// this function uses backtracking recursion, using static variables we can keep a track of some values to make function go in some permutation and return back to other permutation case
// print permutations of the given string
void permutations(const char *s, int k)
{
    static int a[10] = {0}; // check if the letter of string was already used im permutation
    static char res[10]; // stores the result string

    if (s[k] == '\0')
    {
        res[k] = '\0';
        printf("%s\n", res);
    }
    else
    {
        int i = 0;
        while (s[i] != '\0')
        {
            if (a[i] == 0)
            {
                res[k] = s[i];
                a[i] = 1;
                permutations(s, k+1);
                a[i] = 0;
            }
            i++;
        }
    }
} // time complexity: O(n!)

void swap(char *a, char *b)
{
    char tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

void permutations_swap(char s[], int l, int h)
{
    if (l==h)
    {
        printf("%s\n", s);
    }
    else
    {
        int i = 0;
        for (i = l; i <= h; i++)
        {
            swap(&s[l], &s[i]);
            permutations_swap(s, l + 1, h);
            swap(&s[l], &s[i]);
        }
    }
} // time complexity: O(n!)

int main()
{
    char s[] = "ABC";

    printf("Permutation with backtracking: \n");
    permutations(s, 0);
    printf("\nPermutations with swapping: \n");
    permutations_swap(s, 0, 2);

    return 0;
}