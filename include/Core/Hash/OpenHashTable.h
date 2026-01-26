#ifndef DATASTRUCTURES_OPEN_HASHTABLE_H
#define DATASTRUCTURES_OPEN_HASHTABLE_H

typedef unsigned int (*OpenHashFunction)(int);

typedef struct OpenHashTable OpenHashTable;

OpenHashTable* createOpenHashTableWithFunction(OpenHashFunction function);

OpenHashTable* createOpenHashTable();

void destroyOpenHashTable(OpenHashTable* ht);

void insertOpenHashTable(OpenHashTable* ht, int value);

const int* searchOpenHashTable(OpenHashTable* ht, int value);

void deleteOpenHashTable(OpenHashTable* ht, int value);

#endif //DATASTRUCTURES_OPEN_HASHTABLE_H