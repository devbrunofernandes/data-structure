#ifndef DATASTRUCTURES_OPENHASHTABLE_H
#define DATASTRUCTURES_OPENHASHTABLE_H

typedef unsigned int (*HashFunction)(int);

typedef struct HashTable HashTable;

HashTable* createHashTableSizeFunction(int maxSize, HashFunction function);

HashTable* createHashTableWithFunction(HashFunction function);

HashTable* createHashTableWithSize(int size);

HashTable* createHashTable();

void destroyHashTable(HashTable* ht);

void insertHashTable(HashTable* ht, int value);

const int* searchHashTable(HashTable* ht, int value);

void deleteHashTable(HashTable* ht, int value);

#endif //DATASTRUCTURES_OPENHASHTABLE_H