// row-major representation program
#include <iostream>

class LowerTri
{
private:
    int n;
    int *A;

public:
    LowerTri()
    {
        n = 2;
        A = new int[n * (n + 1) / 2];
    }

    LowerTri(int n)
    {
        this->n = n;
        A = new int[n * (n + 1) / 2];
    }

    ~LowerTri()
    {
        delete[] A;
    }

    void set(int row, int column, int valor);
    int get(int row, int column);
    void display();
    int get_dimension() { return n; }
};

void LowerTri::set(int row, int column, int valor)
{
    if (row >= column)
    {
        A[row * (row - 1) / 2 + column - 1] = valor;
    }
}

int LowerTri::get(int row, int column)
{
    if (row >= column)
    {
        return A[row * (row - 1) / 2 + column - 1];
    }
    else
    {
        return 0;
    }
}

void LowerTri::display()
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (i >= j)
                std::cout << A[i*(i-1)/2+j-1] << " ";
            else
                std::cout << "0 ";
        }
        std::cout << std::endl;
    }
}

int main()
{
    int d;
    std::cout << "Enter dimensions" << std::endl;
    std::cin >> d;

    LowerTri m(d);

    int x;
    std::cout << "Enter all elements" << std::endl;
    for (int i = 1; i <= d; i++)
    {
        for (int j = 1; j <= d; j++)
        {
            std::cin >> x;
            m.set(i, j, x);
        }
    }

    std::cout << std::endl << std::endl;
    m.display();

    return 0;
}