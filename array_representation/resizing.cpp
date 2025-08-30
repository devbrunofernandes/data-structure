#include <iostream>

int main()
{
    int *p = new int[5];
    p[0] = 5;
    p[1] = 8;
    p[2] = 9;
    p[3] = 6;
    p[4] = 4;

    int *q = new int[10];

    for (int i = 0; i < 5; i++)
        q[i] = p[i];

    delete[] p;

    p = q;
    q = nullptr;

    for (int i = 0; i < 10; i++)
        std::cout << p[i] << std::endl;
}