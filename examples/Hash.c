#include <stdio.h>
#include "Core/Hash/OpenHashTable.h"
#include "Core/Hash/ClosedHashTable.h"


int main() {
    ClosedHashTable* ht = createClosedHashTable();

    insertClosedHashTable(ht, 10);
    insertClosedHashTable(ht, 20);
    insertClosedHashTable(ht, 30);
    insertClosedHashTable(ht, 40);
    insertClosedHashTable(ht, 50);
    insertClosedHashTable(ht, 60);

    if (searchClosedHashTable(ht, 40))
        printf("40 is in hash table\n");
    else
        printf("40 is not in hash table\n");

    printf("deleting 40...\n");
    deleteClosedHashTable(ht, 40);

    if (searchClosedHashTable(ht, 40))
        printf("40 is in hash table\n");
    else
        printf("40 is not in hash table\n");

    return 0;
}