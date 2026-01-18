#include <iostream>

using namespace std;

// used for group some variables in one.
// by the exemple an rectangle needs its lenght and its breadth to be represented.
struct Rectangle {
    int lenght;
    int breadth;
};

int main() {
    struct Rectangle r1={10, 5}; // declaration with: struct {struct type name} {variable name}
    r1.lenght = 15;
    r1.breadth = 7;

    cout << r1.lenght << endl;
    cout << r1.breadth << endl;

    return 0;
}