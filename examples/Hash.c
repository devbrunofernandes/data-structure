#include <stdio.h>
#include "Core/Hash/OpenHashTable.h"


int main() {
    HashTable* ht = createHashTable();

    insertHashTable(ht, 10);
    insertHashTable(ht, 20);
    insertHashTable(ht, 30);
    insertHashTable(ht, 40);
    insertHashTable(ht, 50);
    insertHashTable(ht, 60);

    if (searchHashTable(ht, 40))
        printf("40 is in hash table\n");
    else
        printf("40 is not in hash table\n");

    printf("deleting 40...\n");
    deleteHashTable(ht, 40);

    if (searchHashTable(ht, 40))
        printf("40 is in hash table\n");
    else
        printf("40 is not in hash table\n");

    return 0;
}