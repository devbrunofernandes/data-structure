#include <iostream>

using namespace std;

void recursive(int n) // recursive function.
{
    if (n > 0)
    {
        printf("%d ", n);
        recursive(n - 1); // this is a tail recursion because the recursive call is last statement of the function and there is no other operation in the line.
    }
} // every processing in the function is executed in calling/ascending phase.
// Time O(n) - Space O(n)

void iterative(int n) // iterative version of recursive function, using while loop.
{
    while (n > 0)
    {
        printf("%d ", n);
        n--;
    }
} // iterative versions are more efficient in space complexity. Have no risk of stack memory overflow.
// Time O(n) - Space O(1)

int main()
{
    //recursive(100000);
    printf("\n");
    iterative(100000);

    return 0;
}