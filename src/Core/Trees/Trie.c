#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include "Core/Trees/Trie.h"

#define ALPHABET_SIZE 26

typedef struct TrieNode {
    bool complete;
    int filledChilds;
    struct TrieNode *childs[ALPHABET_SIZE];
} TrieNode;

typedef struct Trie {
    TrieNode* root;
} Trie;

static TrieNode* initTrieNode() {
    TrieNode* node = (TrieNode*) malloc(sizeof(TrieNode));

    for (int i = 0; i < ALPHABET_SIZE; i++)
        node->childs[i] = NULL;

    node->complete = false;
    node->filledChilds = 0;

    return node;
}

static TrieNode* trieInsertHelper(TrieNode *root, const char s[]) {
    if (!root) {root = initTrieNode();}

    TrieNode *node = root;

    for (int i = 0; s[i] != '\0'; i++) {
        int index = toupper(s[i]) - 65;

        if (!node->childs[index]) {
            node->childs[index] = initTrieNode();
            node->filledChilds++;
        }

        node = node->childs[index];
    }

    node->complete = true;

    return root;
}

void trieInsert(Trie* tree, const char* key) {

    for (int i = 0; key[i] != '\0'; i++)
        if (!isalpha(key[i])) return;

    tree->root = trieInsertHelper(tree->root, key);
}

static bool trieSearchHelper(TrieNode *root, const char* key) {
    int i = 0;

    while (key[i] != '\0') {
        const int index = toupper(key[i]) - 65;
        root = root->childs[index];

        if (!root) { return false; }

        i++;
    }

    if (root->complete) { return true; }

    return false;
}

bool trieSearch(Trie* tree, const char* s) {
    if (!tree->root) return false;

    return trieSearchHelper(tree->root, s);
}

static TrieNode* trieDeleteHelper(TrieNode *node, const char s[], const int index) {
    if (!node) {return NULL;}

    if (s[index] == '\0') {
        node->complete = false;
        if (node->filledChilds == 0) {
            free(node);
            return NULL;
        }

        return node;
    }

    const int childIndex = toupper(s[index]) - 65;
    node->childs[childIndex] = trieDeleteHelper(node->childs[childIndex], s, index + 1);

    if (!node->childs[childIndex]) {node->filledChilds--;}

    if (!node->complete && node->filledChilds == 0) {
        free(node);
        return NULL;
    }

    return node;
}

void trieDelete(Trie* tree, const char s[]) {

    tree->root = trieDeleteHelper(tree->root, s, 0);
}

Trie* trieCreate() {
    Trie* tree = (Trie *) malloc(sizeof(Trie));
    tree->root = NULL;
    return tree;
}

static void trieDestroyHelper(TrieNode* p) {
    if (!p) {return;}

    if (p->filledChilds > 0) {
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            if (p->childs[i]) trieDestroyHelper(p->childs[i]);
        }
    }

    free(p);
}

void trieDestroy(Trie* tree) {
    if (!tree) {return;}

    trieDestroyHelper(tree->root);

    free(tree);
}