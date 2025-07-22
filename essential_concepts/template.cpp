#include <iostream>

using namespace std;

/* This is a default Arithmetic class for add and sub operations.
class Arithmetic
{
    private:
        int a;
        int b;
    public:
        Arithmetic(int a, int b);
        int add();
        int sub();

};

Arithmetic::Arithmetic(T a, T b)
{
    this->a = a;
    this->b = b;
}

int Arithmetic::add()
{
    int c;
    c = a + b;
    return c;
}

int Arithmetic::sub()
{
    int c;
    c = a - b;
    return c;
}
*/

// This is a generic/template class for the same Arithmetic, with the same operations.
// The difference is that in template class you can work with different variable data types with the same methods.
template <class T> // for each template class or function you need to declare: template <class (template variable name)>
class Arithmetic
{
private:
    T a; // use the generic template type you declared for class attributes.
    T b;

public:
    Arithmetic(T a, T b);
    T add(); // use the generic template type you declared as return type also.
    T sub();
};

template <class T>
Arithmetic<T>::Arithmetic(T a, T b) // in the function header after class name you need to write <template variable name> 
{
    this->a = a; // "this" is a pointer for current class object.
    this->b = b;
}

template <class T>
T Arithmetic<T>::add()
{
    T c;
    c = a + b;
    return c;
}

template <class T>
T Arithmetic<T>::sub()
{
    T c;
    c = a - b;
    return c;
}

int main()
{
    Arithmetic<int> a(10,5);
    cout << a.add()<<endl;

    Arithmetic<float> af(1.5, 1.2);
    cout << af.add()<<endl;
}