#include "Core/Trees/AVL.h"
#include "Core/Trees/BST.h"
#include "Core/Trees/BTree.h"
#include "Core/Trees/BPlusTree.h"
#include "Core/Trees/RadixTree.h"
#include "Core/Trees/Trie.h"
#include "Core/Trees/RBT.h"

#include <stdio.h>

int main() {
    Trie* tree= trieCreate();

    trieInsert(tree, "test");

    trieSearch(tree, "test") ? printf("Test in trie\n") : printf("Test not in trie\n");

    trieDelete(tree, "test");

    trieSearch(tree, "test") ? printf("Test in trie\n") : printf("Test not in trie\n");

    return 0;
}