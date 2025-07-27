#include <iostream>

int main()
{
    // declaration in stack memory
    int A[3][4] = {0}; // 2 dimensions array or matrix. (array name)[(lines)][(columns)]
    A[1][2] = 15;
    /*
          0   1   2   3
         =================
     0   |   |   |   |   |
     1   |   |   | 15|   |
     2   |   |   |   |   |
         =================
    */

    // declaration using a array of pointers inside stack memory and each pointer points for a array in heap memory
    int *B[3];
    for (int i = 0; i < 3; i++)
    {
        B[i] = new int[4];
        for (int j = 0; j < 4; j++)
        {
            B[i][j] = 0;
        }
    }
    B[1][2] = 15;

    // declaration using a pointer that points to a array of pointers that points to a array of int. only the pointer inside stack, all others inside heap
    int **C;
    C = new int *[3];
    for (int i = 0; i < 3; i++)
    {
        C[i] = new int[4];
        for (int j = 0; j < 4; j++)
        {
            C[i][j] = 0;
        }
    }
    C[1][2] = 15;

    // use nested for loops for acessing all members of 2D arrays
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            std::cout << "A[" << i << "][" << j << "] = " << A[i][j] << ", ";
            std::cout << "B[" << i << "][" << j << "] = " << B[i][j] << ", ";
            std::cout << "C[" << i << "][" << j << "] = " << C[i][j] << std::endl;
        }
        std::cout << "------------------------------------" << std::endl;
    }
         
    // remember to free memory ofter use the data structures
    for (int i = 0; i < 3; i++)
    {
        delete[] B[i];
    }

    for (int i = 0; i < 3; i++)
    {
        delete[] C[i];
    }
    delete[] C;

    return 0;
}