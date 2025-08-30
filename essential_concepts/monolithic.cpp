#include <iostream>

using namespace std;

// program to calculate area and perimeter of a quadrilateral.
// this is an example of monolithic program. all code in one block without modules.
int main()
{
    int length=0, breadth=0;

    cout << "Type length and breadth:" << endl;
    cin >> length >> breadth;

    int area = length * breadth;
    int peri = 2 * (length + breadth);

    cout << "Area = " << area << endl;
    cout << "Perimeter = " << peri << endl;

    return 0;
}