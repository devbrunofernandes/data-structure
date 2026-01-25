#ifndef DATASTRUCTURES_DYNAMIC_ARRAY_H
#define DATASTRUCTURES_DYNAMIC_ARRAY_H

typedef struct Vector {
    int* array; // public
    int size; // public read-only
    int capacity; // private
} Vector;

Vector* createVectorCapacity(int capacity);

Vector* createVector();

void pushBackVector(Vector* v, const int value);

void insertVector(Vector* v, int index, int value);

void deleteVector(Vector* v, int index);

void popBackVector(Vector* v);

void shrinkVector(Vector* v);

void destroyVector(Vector* v);

int* getVector(const Vector* v, int index);

void clearVector(Vector* v);

int searchVector(Vector* v, const int value);

Vector*  copyVector(Vector* v);

#endif //DATASTRUCTURES_DYNAMIC_ARRAY_H