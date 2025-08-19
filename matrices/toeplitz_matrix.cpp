#include <stdio.h>
#include <stdlib.h>

struct Matrix
{
    int *A;
    int n;
};

/* INDEXING IN TOEPLITZ MATRIX
    if (i <= j) -> m.A[j-i]
    if (i > j) -> m.A[m.n + i-j-1]
*/
void set(struct Matrix *m, int i, int j, int x)
{
    if (i <= j)
        m->A[j - i] = x;
    else
        m->A[m->n + i - j - 1] = x;
}

int get(const struct Matrix m, int i, int j)
{
    if (i <= j)
        return m.A[j - i];
    else
        return m.A[m.n + i - j - 1];
}

void display(struct Matrix m)
{
    for (int i = 1; i <= m.n; i++)
    {
        for (int j = 1; j <= m.n; j++)
        {
            if (i <= j)
            {
                printf("%d ", m.A[j - i]);
            }
            else
            {
                printf("%d ", m.A[m.n + i - j - 1]);
            }
        }
        printf("\n");
    }
}

// toeplitz matrix property is that all elements in one diagonal are same
// M[i][j] = m[i-1][j-1]
// we can only store in memory the first column and first row of the matrix
// size for matrix n*n = n + n-1
int main()
{
    // use a single dimension array to dont waste time and space
    struct Matrix m;

    printf("Enter dimension: ");
    scanf("%d", &m.n);

    m.A = (int *)malloc((m.n + (m.n - 1)) * sizeof(int));

    printf("Enter all elements\n");
    int x;
    for (int i = 1; i <= m.n; i++)
    {
        for (int j = 1; j <= m.n; j++)
        {
            scanf("%d", &x);
            set(&m, i, j, x);
        }
    }

    printf("\n\n");
    display(m);

    return 0;
}