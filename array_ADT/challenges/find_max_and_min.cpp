#include <stdio.h>
#include <stdlib.h>
#include <utility>

using namespace std;

struct Array
{
    int A[30];
    int size;
    int length;
};

void display(struct Array arr)
{
    for (int i = 0; i < arr.length; i++)
        printf("%d ", arr.A[i]);
    printf("\n");
}

// find the MAX and MIN from array in a single scan
pair<int, int> max_min(struct Array arr)
{
    pair<int, int> max_and_min;

    if (arr.length == 0)
        return max_and_min;

    int max = arr.A[0], min = arr.A[0];

    for (int i = 1; i < arr.length; i++)
    {
        if (arr.A[i] < min)
            min = arr.A[i];
        else if (arr.A[i] > max)
            max = arr.A[i];
    }

    max_and_min = make_pair(max, min);
    return max_and_min;
} // time complexity: O(n)

int main()
{
    struct Array arr = {{6, 7, 8, 9, 11, 12, 15, 16, 17, 18, 19}, 15, 11};

    pair<int, int> max_and_min = max_min(arr);
    printf("Max: %d\nMin: %d\n", max_and_min.first, max_and_min.second);
    display(arr);

    return 0;
}