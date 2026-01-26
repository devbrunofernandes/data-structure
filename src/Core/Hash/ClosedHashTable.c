#include <stdlib.h>

#include "Core/LinkedLists/LinkedList.h"

#include "Core/Hash/ClosedHashTable.h"

#define INITIAL_PRIME_SIZE 31

typedef enum { EMPTY, OCCUPIED, DELETED } State;

typedef struct ClosedHashTable {
    int* table;
    State* states;
    int maxSize;
    int nonEmpty;
    ClosedHashFunction hashFunction;
} ClosedHashTable;

static unsigned int defaultClosedHashFunction(const int value) {
    return value;
}

static unsigned int secClosedHashFunction(ClosedHashFunction func, const int value, const int size) {
    return size - (func(value) % size);
}

static unsigned int getIndex(ClosedHashFunction func, const int i, const int value, const int size) {
    return (func(value) + (i * secClosedHashFunction(func, value, size))) % size;
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

static void resizeTable(ClosedHashTable* ht) {
    if (ht->nonEmpty < (ht->maxSize * 0.5)) return;

    // memory allocation
    int newNonEmpty = 0;
    const int newMaxSize = nextPrime(ht->maxSize * 2);
    int* newTable = (int*) calloc(newMaxSize, sizeof(int));
    State* newStates = (State*) calloc(newMaxSize, sizeof(State));

    if (!newTable || !newStates) return;

    // re-hashing
    for (int i = 0; i < ht->maxSize; i++) {
        if (ht->states[i] != OCCUPIED) continue;

        const int value = ht->table[i];

        int attempt = 0;
        unsigned int index = 0;

        while (attempt < ht->maxSize) {
            index = getIndex(ht->hashFunction, attempt, value, newMaxSize);

            if (newStates[index] == EMPTY) break;

            attempt++;
        }

        newStates[index] = OCCUPIED;
        newTable[index] = value;
        newNonEmpty++;
    }

    free(ht->table);
    free(ht->states);

    ht->maxSize = newMaxSize;
    ht->table = newTable;
    ht->states = newStates;
    ht->nonEmpty = newNonEmpty;
}

ClosedHashTable* createClosedHashTableWithFunction(const ClosedHashFunction function) {
    ClosedHashTable* ht = (ClosedHashTable*)malloc(sizeof(ClosedHashTable));
    ht->maxSize = INITIAL_PRIME_SIZE;
    ht->nonEmpty = 0;
    ht->table = (int*) calloc(INITIAL_PRIME_SIZE, sizeof(int));
    ht->states = (State*) calloc(INITIAL_PRIME_SIZE, sizeof(State));
    ht->hashFunction = function;
    return ht;
}

ClosedHashTable* createClosedHashTable() {
    return createClosedHashTableWithFunction(defaultClosedHashFunction);
}

void destroyClosedHashTable(ClosedHashTable* ht) {
    free(ht->states);
    free(ht->table);
    free(ht);
}

void insertClosedHashTable(ClosedHashTable* ht, const int value) {
    int attempt = 0;
    unsigned int index = 0;

    if (searchClosedHashTable(ht, value)) return;

    while (attempt < ht->maxSize) {
        index = getIndex(ht->hashFunction, attempt, value, ht->maxSize);

        if (ht->states[index] != OCCUPIED) break;

        attempt++;
    }

    if (ht->states[index] == EMPTY) ht->nonEmpty++;
    ht->states[index] = OCCUPIED;
    ht->table[index] = value;

    resizeTable(ht);
}

const int* searchClosedHashTable(ClosedHashTable* ht, const int value) {
    int attempt = 0;

    while (attempt < ht->maxSize) {
        const unsigned int index = getIndex(ht->hashFunction, attempt, value, ht->maxSize);

        if (ht->states[index] == EMPTY) break;

        if (ht->states[index] == OCCUPIED && ht->table[index] == value)
            return &(ht->table[index]);

        attempt++;
    }

    return NULL;
}

void deleteClosedHashTable(ClosedHashTable* ht, const int value) {
    int attempt = 0;
    unsigned int index = 0;

    while (attempt < ht->maxSize) {
        index = getIndex(ht->hashFunction, attempt, value, ht->maxSize);

        if (ht->states[index] == EMPTY) return;

        if (ht->states[index] == OCCUPIED && ht->table[index] == value) {
            ht->states[index] = DELETED;
            return;
        }

        attempt++;
    }
}