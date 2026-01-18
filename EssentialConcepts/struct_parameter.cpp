#include <iostream>

using namespace std;

int areaByValue(struct Rectangle r);
void changeLength(struct Rectangle *r, int n);
int areaByReference(struct Rectangle &r);
void testFunction(struct Test t1);

struct Rectangle
{
    int length;
    int breadth;
};

struct Test
{
    int array[5];
    int n;
};

int main() 
{
    struct Rectangle y = {10, 5};
    changeLength(&y, 20);
    printf("Area: %d\n", areaByValue(y));

    struct Test t = {{2, 4, 6, 8, 10}, 5};
    testFunction(t);
    for (int i:t.array)
    {
        printf("%d ", i);
    }

    return 0;
}

int areaByValue(struct Rectangle r) // passing struct by value as a parameter. a copy of struct will be created for function objective.
{
    return r.length * r.breadth; // in this parameter calling if function change struct variable it will not be changed in main.
}

void changeLength(struct Rectangle *r, int n) // passing struct by address as a parameter. create a pointer to the original struct variable.
{
    r->length = n; // in this parameter calling if function change struct variable it will be changed in main.
}

int areaByReference(struct Rectangle &r) // passing struct by reference as a parameter. create a nickname to the struct in main and modify its values.
{
    return r.length * r.breadth; // in this parameter calling if function change struct variable it will be changed in main.
}

void testFunction(struct Test t1) // normally arrays cant be passed as parameter by value, but if its array inside struct it can be passed.
{
    t1.array[0] = 10; // this modifications dont apply in main module.
    t1.array[1] = 9; // proving that the array in struct has been coppied in function.
}