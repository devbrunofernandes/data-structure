#include "Core/Array/Array.h"
#include "Core/Array/Vector.h"

#include <stdio.h>

int main() {
    Vector* v = createVector(20);

    pushBackVector(v, 10);
    pushBackVector(v, 20);
    pushBackVector(v, 30);
    pushBackVector(v, 40);
    pushBackVector(v, 50);

    popBackVector(v);

    printArray(v->array, v->size);

    return 0;
}