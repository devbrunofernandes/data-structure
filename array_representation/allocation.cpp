#include <iostream>

using namespace std;

int main()
{
    int A[5]={2,4,6,8,10};
    int *p;

    p = new int[5]; // C++ syntax to alloc an array in heap memory
    p[0] = 3;
    p[1] = 5;
    p[2] = 7;
    p[3] = 9;
    p[4] = 11;

    for (int i = 0; i < 5; i++)
    {
        cout << A[i] << " " << p[i] << endl;
    }

    delete[] p; // C++ syntax for free the memory
}