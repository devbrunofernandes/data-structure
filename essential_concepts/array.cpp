#include <iostream>

using namespace std;

int main()
{
    int n;
    cout << "Enter size";
    cin >> n;

    // array is a linear memory allocation.
    // the IDE show an error message but this inicialization of an variable size array works in some compilers.
    int A[n] = {1, 2, 3, 4};
    

    for (int x:A) {
        cout << x << endl;
    }

    return 0;
}
