#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "Core/Trees/RadixTree.h"

#define ALPHABET_SIZE 26

typedef struct RadixTreeNode {
    bool complete;
    int filledChilds;
    char* word;
    struct RadixTreeNode* childs[ALPHABET_SIZE];
} RadixTreeNode;

typedef struct RadixTree {
    RadixTreeNode* root;
} RadixTree;


static RadixTreeNode* initRadixTreeNode() {
    RadixTreeNode* node = (RadixTreeNode*) malloc(sizeof(RadixTreeNode));

    for (int i = 0; i < ALPHABET_SIZE; i++)
        node->childs[i] = NULL;

    node->complete = false;
    node->filledChilds = 0;
    node->word = NULL;

    return node;
}

static RadixTreeNode* radixInsertRecursion(RadixTreeNode* node, const char* s, int index) {
    if (s[index] == '\0') {return NULL;}

    if (!node) {
        node = initRadixTreeNode();

        node->word = strdup(s + index);
        node->complete = true;

        return node;
    }

    if (node->word) {
        int inNodeIndex = 0;

        while (s[index] != '\0' && node->word[inNodeIndex] != '\0') {
            if (s[index] != node->word[inNodeIndex]) {
                char* oldSuffix = strdup(node->word + inNodeIndex);
                bool oldComplete = node->complete;

                node->word[inNodeIndex] = '\0';
                node->complete = false;

                RadixTreeNode* suffixChild = initRadixTreeNode();
                suffixChild->word = oldSuffix;
                suffixChild->complete = oldComplete;

                for (int i = 0; i < ALPHABET_SIZE; i++) {
                    suffixChild->childs[i] = node->childs[i];
                    node->childs[i] = NULL;
                }
                suffixChild->filledChilds = node->filledChilds;

                int oldIdx = toupper(oldSuffix[0]) - 65;
                node->childs[oldIdx] = suffixChild;

                int newIdx = toupper(s[index]) - 65;
                node->childs[newIdx] = radixInsertRecursion(node->childs[newIdx], s, index);

                node->filledChilds = 2;

                return node;
            }   

            index++;
            inNodeIndex++;
        }

        if (node->word[inNodeIndex] != '\0' && s[index] == '\0') {
            const int childIndex = toupper(node->word[inNodeIndex]) - 65;
            if (node->childs[childIndex] == NULL) {node->filledChilds++;}
            node->childs[childIndex] = radixInsertRecursion(node->childs[childIndex], node->word, inNodeIndex);

            node->word[inNodeIndex] = '\0';

            return node;
        }

        if (node->word[inNodeIndex] == '\0' && s[index] != '\0') {
            const int childIndex = toupper(s[index]) - 65;
            if (node->childs[childIndex] == NULL) {node->filledChilds++;}
            node->childs[childIndex] = radixInsertRecursion(node->childs[childIndex], s, index);

            return node;
        }

        return node;
    }

    int childIndex = toupper(s[index]) - 65;
    bool wasEmpty = node->childs[childIndex] == NULL;

    node->childs[childIndex] = radixInsertRecursion(node->childs[childIndex], s, index + 1);

    if (node->childs[childIndex] == NULL) {node->complete = true;}
    else if (wasEmpty) {node->filledChilds++;}

    return node;
}

static RadixTreeNode* radixInsertHelper(RadixTreeNode* root, const char* s) {
    int i;
    for (i = 0; s[i] != '\0'; i++)
        if (!isalpha(s[i])) {return root;}


    if (i < 2) {return root;}

    if (!root) {root = initRadixTreeNode();}

    int childIndex = toupper(s[0]) - 65;
    bool wasEmpty = root->childs[childIndex] == NULL;

    root->childs[childIndex] = radixInsertRecursion(root->childs[childIndex], s, 0);
    
    if (wasEmpty) {root->filledChilds++;}

    return root;
}

void radixInsert(RadixTree* tree, const char* s) {

    tree->root = radixInsertHelper(tree->root, s);
}

static bool radixSearchHelper(RadixTreeNode* root, const char* s) {
    int i = 0;

    while (s[i] != '\0') {
        const int index = toupper(s[i]) - 65;
        
        root = root->childs[index];
        if (!root) {return false;}

        if (root->word) {
            int j = 0;

            while (s[i] != '\0' && root->word[j] != '\0') {
                if (s[i] != root->word[j]) {return false;}

                j++;
                i++;
            }

            if (s[i] == '\0' && root->word[j] != '\0') {return false;}

            i--;
        }

        i++;
    } 

    if (root->complete) {return true;}

    return false;
}

bool radixSearch(RadixTree* tree, const char* s) {

    return radixSearchHelper(tree->root, s);
}

static RadixTreeNode* radixDeleteHelper(RadixTreeNode* node, const char* s, int index) {
    if (!node) return NULL;

    int inNodeIndex = 0;
    if (node->word) {
        while (s[index] != '\0' && node->word[inNodeIndex] != '\0') {
            if (s[index] != node->word[inNodeIndex]) return node;

            index++;
            inNodeIndex++;
        }
    }

    if (s[index] == '\0') {
        if (node->word && node->word[inNodeIndex] != '\0') return node;

        node->complete = false;
        if (node->filledChilds == 0) {
            if (node->word) free(node->word);
            free(node);
            return NULL;
        }

        if (node->filledChilds == 1) {
            if (node->word == NULL) return node;

            int i = 0;
            while (!node->childs[i]) {i++;}
            RadixTreeNode* child = node->childs[i];

            node->complete = child->complete;
            node->filledChilds = child->filledChilds;
            for (int j = 0; j < ALPHABET_SIZE; j++)
                node->childs[j] = child->childs[j];

            // append
            int newSize = strlen(node->word) + strlen(child->word) + 2;
            char* newWord = (char*) malloc(newSize);

            if (newWord) {
                strcpy(newWord, node->word);
                strcat(newWord, child->word);
                free(node->word);
                node->word = newWord;
            }

            if (node->word) free(child->word);
            free(child);
        }

        return node;
    }

    int childIndex = toupper(s[index]) - 65;
    node->childs[childIndex] = radixDeleteHelper(node->childs[childIndex], s, index);

    if (!node->childs[childIndex]) {node->filledChilds--;}

    if (!node->complete && node->filledChilds == 0) {
        if (node->word) free(node->word);
        free(node);
        return NULL;
    }

    return node;
}

void radixDelete(RadixTree* tree, const char* s) {

    tree->root = radixDeleteHelper(tree->root, s, 0);
}

RadixTree* radixCreate() {
    RadixTree* tree = (RadixTree*) malloc(sizeof(RadixTree));
    tree->root = NULL;
    return tree;
}

static void radixDestroyHelper(RadixTreeNode* node) {
    int visited = 0;
    int index = 0;

    while (index < ALPHABET_SIZE && visited < node->filledChilds) {
        if (node->childs[index]) {
            radixDestroyHelper(node->childs[index]);
            visited++;
        }

        index++;
    }

    if (node->word) free(node->word);
    free(node);
}

void radixDestroy(RadixTree* tree) {

    radixDestroyHelper(tree->root);

    free(tree);
}