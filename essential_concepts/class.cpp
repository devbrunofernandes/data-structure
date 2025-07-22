#include <iostream>

using namespace std;

// CLASS AND OOP FEATURES ONLY IN C++, NOT IN C LANGUAGE.
class Rectangle 
{
    private:
    int length;
    int breadth;

    public:
    // this is a constructor, a function that initializate the object of the class.
    Rectangle(int l, int b) // class name followed by the parameters for variable/attributes initialization in object declaration.
    {
        length = l;
        breadth = b;
    }

    int area() 
    {
        return length * breadth;
    }

    void changeLength(int l) 
    {
        length = l;
    }
};

int main() 
{
    Rectangle r(10,5); // declaration and initialization of object r of class Rectangle.

    r.area();
    r.changeLength(20);

    return 0;
}