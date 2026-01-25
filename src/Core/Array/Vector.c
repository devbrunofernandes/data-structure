#include "Core/Array/Vector.h"

#include <string.h>
#include <stdlib.h>

Vector* createVectorCapacity(const int capacity) {
    Vector* v = (Vector*) malloc(sizeof(Vector));
    v->size = 0;
    v->capacity = capacity;
    v->array = (int*) calloc(v->capacity, sizeof(int));
    return v;
}


Vector* createVector() {
    return createVectorCapacity(50);
}

static void resizeVector(Vector* v) {
    const int newCapacity = v->capacity * 2;
    int* temp = realloc(v->array, newCapacity * sizeof(int));

    if (temp) {
        v->array = temp;
        v->capacity = newCapacity;
    }
 }

void pushBackVector(Vector* v, const int value) {
    if (v->capacity == v->size) resizeVector(v);

    v->array[v->size++] = value;
}

void insertVector(Vector* v, const int index, const int value) {
    if (index < 0 || index > v->size) return;

    if (v->capacity == v->size) resizeVector(v);

    memmove(v->array + index + 1, v->array + index, (v->size - index) * sizeof(int));

    v->array[index] = value;
    v->size++;
}

void popBackVector(Vector* v) {
    if (v->size == 0) return;

    v->size--;
    v->array[v->size] = 0;

    if (v->size > 0 && v->size < v->capacity / 4) shrinkVector(v);
}

void deleteVector(Vector* v, const int index) {
    if (v->size == 0) return;
    if (index < 0 || index >= v->size) return;

    memmove(v->array + index, v->array + index + 1, (v->size - index - 1) * sizeof(int));

    v->array[v->size - 1] = 0;
    v->size--;

    if (v->size > 0 && v->size < v->capacity / 4) shrinkVector(v);
}

void shrinkVector(Vector* v) {
    if (v->size == 0) return;

    const int newCapacity = v->size;
    int* temp = realloc(v->array, newCapacity * sizeof(int));

    if (temp) {
        v->array = temp;
        v->capacity = newCapacity;
    }
}

void destroyVector(Vector* v) {
    if (!v) return;

    free(v->array);
    free(v);
}

int* getVector(const Vector* v, const int index) {
    if (index < 0 || index >= v->size) return NULL;

    return &(v->array[index]);
}

void clearVector(Vector* v) {
    if (!v) return;
    if (v->size > 0 && v->size < v->capacity / 4) shrinkVector(v);

    v->size = 0;
}

int searchVector(Vector* v, const int value) {
    if (!v) return -1;

    for (int i = 0; i < v->size; i++) {
        if (v->array[i] == value) return i;
    }

    return -1;
}

Vector* copyVector(Vector* v) {
    if (!v) return NULL;

    Vector* temp = createVectorCapacity(v->capacity);

    if (temp) {
        temp->size = v->size;
        memcpy(temp->array, v->array, sizeof(int) * temp->size);
    }

    return temp;
}