#include <stdio.h>
#include <stdlib.h>

struct Matrix
{
    int *A;
    int n;
};

// formula for row-major representation -> i * (i - 1) / 2 + j - 1
// formula for column-major representation -> m->n * (j-1) + (j-2) * (j-1) / 2 + i-j
void set(struct Matrix *m, int i, int j, int x)
{
    if (i >= j)
        m->A[i * (i - 1) / 2 + j - 1] = x;
}

int get(const struct Matrix m, int i, int j)
{
    if (i >= j)
        return m.A[i * (i - 1) / 2 + j - 1];
    else
        return m.A[j * (j - 1) / 2 + i - 1];
}

void display(struct Matrix m)
{
    for (int i = 1; i <= m.n; i++)
    {
        for (int j = 1; j <= m.n; j++)
        {
            if (i >= j)
            {
                printf("%d ", m.A[i * (i - 1) / 2 + j - 1]);
            }
            else
            {
                printf("%d ", m.A[j * (j - 1) / 2 + i - 1]);
            }
        }
        printf("\n");
    }
}

// to be a symmetric matrix element M[i][j] must be equal to M[j][i]
// to store symmetric matrices use lower or upper triangle matrices but instead of zeros the not used part of matrix will be mirrored values from the triangle
int main()
{
    // use a single dimension array to dont waste time and space
    struct Matrix m;

    printf("Enter dimension: ");
    scanf("%d", &m.n);

    m.A = (int *)malloc(m.n * (m.n + 1) / 2 * sizeof(int));

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