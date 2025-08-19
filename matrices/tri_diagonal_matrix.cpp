#include <stdio.h>
#include <stdlib.h>

struct Matrix
{
    int *A;
    int n;
};

/* INDEXING IN TRIDIAGONAL MATRIX (i,j starting from 1)
    if (i - j == 1)  -> A[i - 2]
    if (i - j == 0)  -> A[(m->n - 1) + (i - 1)]
    if (i - j == -1) -> A[(2 * m->n - 1) + (i - 1)]
*/
void set(struct Matrix *m, int i, int j, int x)
{
    if (i - j == 1)
        m->A[i - 2] = x;
    else if (i - j == 0)
        m->A[(m->n - 1) + (i - 1)] = x;
    else if (i - j == -1)
        m->A[(2 * m->n - 1) + (i - 1)] = x;
}

int get(const struct Matrix m, int i, int j)
{
    if (i - j == 1)
        return m.A[i - 2];
    else if (i - j == 0)
        return m.A[(m.n - 1) + (i - 1)];
    else if (i - j == -1)
        return m.A[(2 * m.n - 1) + (i - 1)];
    else
        return 0;
}

void display(struct Matrix m)
{
    for (int i = 1; i <= m.n; i++)
    {
        for (int j = 1; j <= m.n; j++)
        {
            if (i - j == 1)
            {
                printf("%d ", m.A[i - 2]);
            }
            else if (i - j == 0)
            {
                printf("%d ", m.A[(m.n - 1) + (i - 1)]);
            }
            else if (i - j == -1)
            {
                printf("%d ", m.A[(2 * m.n - 1) + (i - 1)]);
            }
            else
            {
                printf("0 ");
            }
        }
        printf("\n");
    }
}
// all elements that isnt in diagonal of the matrix is equal to 0
// TriDiagonal means that the main diagonal of the matrix is filled but also the diagonal lines below and above the main diagonal

// main diagonal i-j = 0
// lower diagonal i-j = 1
// upper diagonal i-j = -1

// M[i][j] = non-zero if |i-j| <= 1
// M[i][j] = 0 if |i-j| > 1

// size of array = non-zero elements -> for matrix n*n: non-zero elements = 3n-2
int main()
{
    // use a single dimension array to dont waste time and space
    struct Matrix m;

    printf("Enter dimension: ");
    scanf("%d", &m.n);

    m.A = (int *)malloc(((3 * m.n) - 2) * sizeof(int));

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
// Other option of matrix following the same logic is Square Band Matrix
// the difference is that in square band matrix it has more than one extra diagonals lines below and above of main diagonal