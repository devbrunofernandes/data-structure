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
        return 0;
}

void display(struct Matrix m)
{
    for (int i = 1; i <= m.n; i++)
    {
        for (int j = 1; j <= m.n; j++)
        {
            if (i >= j)
            {
                printf("%d ", m.A[i*(i-1)/2 + j-1]);
            }
            else
            {
                printf("0 ");
            }
        }
        printf("\n");
    }
}
// M[i][j] = 0 if i < j
// non-zero elements = (n * (n + 1))/2

// this program uses row-major mapping for the matrix
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