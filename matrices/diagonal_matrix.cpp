#include <stdio.h>

struct Matrix
{
    int A[10];
    int n;
};

void set(struct Matrix *m, int i, int j, int x)
{
    if (i==j)
        m->A[i-1]=x;
}

int get(const struct Matrix m, int i, int j)
{
    if (i==j)
        return m.A[i-1];
    else
        return 0;

}

void display(struct Matrix m)
{
    for (int i = 0; i < m.n; i++)
    {
        for (int j = 0; j < m.n; j++)
        {
            if (j == i)
            {
                printf("%d ", m.A[i]);
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
int main()
{
    // use a single dimension array to dont waste time and space
    struct Matrix m;
    m.n = 4;

    set(&m, 1,1,5);
    set(&m, 2,2,8);
    set(&m, 3,3,9);
    set(&m, 4,4,12);
    
    display(m);

    return 0;
}