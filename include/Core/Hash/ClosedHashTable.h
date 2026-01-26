#ifndef DATASTRUCTURES_CLOSED_HASHTABLE_H
#define DATASTRUCTURES_CLOSED_HASHTABLE_H

typedef unsigned int (*ClosedHashFunction)(int);

typedef struct ClosedHashTable ClosedHashTable;

ClosedHashTable* createClosedHashTableWithFunction(ClosedHashFunction function);

ClosedHashTable* createClosedHashTable();

void destroyClosedHashTable(ClosedHashTable* ht);

void insertClosedHashTable(ClosedHashTable* ht, int value);

const int* searchClosedHashTable(ClosedHashTable* ht, int value);

void deleteClosedHashTable(ClosedHashTable* ht, int value);

#endif //DATASTRUCTURES_CLOSED_HASHTABLE_H