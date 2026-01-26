#include <stdlib.h>

#include "Core/LinkedLists/LinkedList.h"

#include "Core/Hash/OpenHashTable.h"

#define INITIAL_PRIME_SIZE 31

typedef struct OpenHashTable {
    LinkedList** table;
    int maxSize;
    int nonEmpty;
    OpenHashFunction hashFunction;
} OpenHashTable;

static unsigned int defaultOpenHashFunction(const int value) {
    return value;
}

static unsigned int getIndex(const OpenHashTable* ht, const int value) {
    return ht->hashFunction(value) % ht->maxSize;
}

static bool isPrime(const int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;

    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

static int nextPrime(const int n) {
    if (n <= 2) return 2;
    int prime = n;
    if (prime % 2 == 0) prime++;

    while (!isPrime(prime)) {
        prime += 2;
    }
    return prime;
}

static void resizeTable(OpenHashTable* ht) {
    if (ht->nonEmpty <= (ht->maxSize * 0.7)) return;

    // memory allocation
    const int newMaxSize = nextPrime(ht->maxSize * 2);
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

OpenHashTable* createOpenHashTableWithFunction(const OpenHashFunction function) {
    OpenHashTable* ht = (OpenHashTable*)malloc(sizeof(OpenHashTable));
    ht->maxSize = INITIAL_PRIME_SIZE;
    ht->nonEmpty = 0;
    ht->table = (LinkedList**)calloc(INITIAL_PRIME_SIZE, sizeof(LinkedList*));
    ht->hashFunction = function;
    return ht;
}

OpenHashTable* createOpenHashTable() {
    return createOpenHashTableWithFunction(defaultOpenHashFunction);
}

void destroyOpenHashTable(OpenHashTable* ht) {
    for (int i = 0; i < ht->maxSize; i++) {
        if (ht->table[i] != NULL)
            llDestroy(ht->table[i]);
    }

    free(ht->table);
    free(ht);
}

void insertOpenHashTable(OpenHashTable* ht, const int value) {
    const unsigned int index = getIndex(ht, value);

    if (ht->table[index] == NULL) {
        ht->table[index] = llCreate();
    }

    if (llSearch(ht->table[index], value) != NULL) return;

    ht->nonEmpty++;
    llPushBack(ht->table[index], value);

    resizeTable(ht);
}

const int* searchOpenHashTable(OpenHashTable* ht, const int value) {
    const unsigned int index = getIndex(ht, value);

    if (ht->table[index] == NULL)
        return NULL;

    return llSearch(ht->table[index], value);
}

void deleteOpenHashTable(OpenHashTable* ht, const int value) {
    const unsigned int index = getIndex(ht, value);

    if (ht->table[index] == NULL) return;

    const bool deletionHappened = llSearchDelete(ht->table[index], value);
    if (deletionHappened) ht->nonEmpty--;
}