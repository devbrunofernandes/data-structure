#include <stdlib.h>

#include "Core/LinkedLists/LinkedList.h"

#include "Core/Hash/OpenHashTable.h"

typedef struct HashTable {
    LinkedList** table;
    int maxSize;
    int currentSize;
    HashFunction hashFunction;
} HashTable;

static unsigned int defaultHashFunction(const int value) {
    return value;
}

static unsigned int getIndex(const HashTable* ht, const int value) {
    return ht->hashFunction(value) % ht->maxSize;
}

static void resizeTable(HashTable* ht) {
    if (ht->currentSize <= (ht->maxSize * 0.7)) return;

    // memory allocation
    const int newMaxSize = ht->maxSize * 2;
    LinkedList** newTable = (LinkedList**)calloc(newMaxSize, sizeof(LinkedList*));

    if (!newTable) return;

    // re-hashing
    for (int i = 0; i < ht->maxSize; i++) {
        if (ht->table[i] == NULL) continue;

        while (!llIsEmpty(ht->table[i])) {
            const int* front = llFront(ht->table[i]);
            const unsigned int index = ht->hashFunction(*front) % newMaxSize;

            if (newTable[index] == NULL) {
                newTable[index] = llCreate();
            }

            llPushBack(newTable[index], *front);
            llPopFront(ht->table[i]);
        }

        llDestroy(ht->table[i]);
    }

    free(ht->table);
    ht->maxSize = newMaxSize;
    ht->table = newTable;
}

HashTable* createHashTableSizeFunction(const int maxSize, const HashFunction function) {
    HashTable* ht = (HashTable*)malloc(sizeof(HashTable));
    ht->maxSize = maxSize;
    ht->currentSize = 0;
    ht->table = (LinkedList**)calloc(maxSize, sizeof(LinkedList*));
    ht->hashFunction = function;
    return ht;
}

HashTable* createHashTableWithFunction(const HashFunction function) {
    return createHashTableSizeFunction(31, function);
}

HashTable* createHashTableWithSize(const int size) {
    return createHashTableSizeFunction(size, defaultHashFunction);
}

HashTable* createHashTable() {
    return createHashTableSizeFunction(31, defaultHashFunction);
}

void destroyHashTable(HashTable* ht) {
    for (int i = 0; i < ht->maxSize; i++) {
        if (ht->table[i] != NULL)
            llDestroy(ht->table[i]);
    }

    free(ht->table);
    free(ht);
}

void insertHashTable(HashTable* ht, const int value) {
    const unsigned int index = getIndex(ht, value);

    if (ht->table[index] == NULL) {
        ht->table[index] = llCreate();
    }

    if (llSearch(ht->table[index], value) != NULL) return;

    ht->currentSize++;
    llPushBack(ht->table[index], value);

    resizeTable(ht);
}

const int* searchHashTable(HashTable* ht, const int value) {
    const unsigned int index = getIndex(ht, value);

    if (ht->table[index] == NULL)
        return NULL;

    return llSearch(ht->table[index], value);
}

void deleteHashTable(HashTable* ht, const int value) {
    const unsigned int index = getIndex(ht, value);

    if (ht->table[index] == NULL) return;

    const bool deletionHappened = llSearchDelete(ht->table[index], value);
    if (deletionHappened) ht->currentSize--;
}