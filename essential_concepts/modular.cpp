#include <iostream>

using namespace std;

// program to calculate area and perimeter of a quadrilateral.
// this is an example of modular/procedural program. code in separate blocks with modules.
int area(int l, int b)
{
    return l * b;
}

int perimeter(int l, int b)
{
    return 2 * (l + b);
}

int main()
{
    int length = 0, breadth = 0;

    cout << "Type length and breadth:" << endl;
    cin >> length >> breadth;

    int a = area(length, breadth);
    int p = perimeter(length, breadth);

    cout << "Area = " << a << endl;
    cout << "Perimeter = " << p << endl;

    return 0;
}