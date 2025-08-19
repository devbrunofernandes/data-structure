#include <iostream>

class Diagonal
{
private:
    int n;
    int *A;

public:
    Diagonal()
    {
        n = 2;
        A = new int[n];
    }

    Diagonal(int n)
    {
        this->n = n;
        A = new int[n];
    }

    ~Diagonal()
    {
        delete[] A;
    }

    void set(int row, int column, int valor);
    int get(int row, int column);
    void display();
};

void Diagonal::set(int row, int column, int valor)
{
    if (row == column)
    {
        A[row - 1] = valor;
    }
}

int Diagonal::get(int row, int column)
{
    if (row == column)
    {
        return A[row - 1];
    }
    else
    {
        return 0;
    }
}

void Diagonal::display()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == j)
                std::cout << A[i] << " ";
            else
                std::cout << "0 ";
        }
    }
    std::cout << std::endl;
}

int main()
{
    Diagonal m(5);
    m.set(1, 1, 10);
    m.set(2, 2, 20);
    m.set(3, 3, 30);
    m.set(4, 4, 40);
    m.set(5, 5, 50);

    m.display();

    return 0;
}