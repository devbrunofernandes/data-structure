#include "Core/Trees/AVL.h"
#include "Core/Trees/BST.h"
#include "Core/Trees/BTree.h"
#include "Core/Trees/BPlusTree.h"
#include "Core/Trees/RadixTree.h"
#include "Core/Trees/Trie.h"
#include "Core/Trees/RBT.h"
#include "Core/Trees/SegmentTree.h"

#include <stdio.h>

int main() {
    const int array[] = {2, 4, 6, 8, 9, 10, 4, 9, 0};

    SegTree* tree= segTreeCreate(array, 9);

    printf("0-8 -> %d\n", segTreeQuery(tree, 0, 8));

    printf("3-5 -> %d\n", segTreeQuery(tree, 3, 5));

    printf("7-8 -> %d\n", segTreeQuery(tree, 7, 8));

    printf("updating tree at index 4 to value 10\n");

    segTreeUpdate(tree, 4, 10);

    printf("3-5 -> %d\n", segTreeQuery(tree, 3, 5));

    printf("0-8 -> %d\n", segTreeQuery(tree, 0, 8));

    segTreeDestroy(tree);

    return 0;
}