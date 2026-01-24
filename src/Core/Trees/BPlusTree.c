#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "Core/Trees/BPlusTree.h"

#define KEYS 5
#define MIN_KEYS (KEYS / 2)
#define CHILDS (KEYS + 1)

typedef struct BPlusTreeNode {
    bool isLeaf;
    int keys[KEYS];
    int usedKeys;

    // Internal node values
    struct BPlusTreeNode* childs[CHILDS];

    // Leaf node values
    struct BPlusTreeNode* nextLeaf;
} BPlusTreeNode;

typedef struct BPlusTree {
    BPlusTreeNode* root;
} BPlusTree;

static BPlusTreeNode* initNode(const bool isLeaf) {
    BPlusTreeNode* node = (BPlusTreeNode*)malloc(sizeof(BPlusTreeNode));

    for (int i = 0; i < CHILDS; i++) {node->childs[i] = NULL;}
    for (int i = 0; i < KEYS; i++) {node->keys[i] = 0;}

    node->usedKeys = 0;
    node->nextLeaf = NULL;
    node->isLeaf = isLeaf;

    return node;
}

typedef struct Split {
    bool happened;
    BPlusTreeNode* newNode;
    int upperKey;
} Split;

typedef struct Underflow {
    bool happened;
    BPlusTreeNode* node;
} Underflow;

static void bplusDisplayHelper(BPlusTreeNode* root) {
    while (!root->isLeaf) 
        root = root->childs[0];

    while (root) {
        for (int i = 0; i < root->usedKeys; i++) 
            printf("%d ", root->keys[i]);;

        root = root->nextLeaf;
    }

    printf("\n");
}

static int findIndex(const int array[], const int size, const int key) {
    int left = 0;
    int right = size - 1;
    int mid;

    while (left <= right) {
        mid = ((right - left) / 2) + left;

        if (array[mid] == key) return mid;
        else if (array[mid] < key) left = mid + 1;
        else right = mid - 1;
    }

    return left;
}

static bool isFull(BPlusTreeNode* node) {
    if (node->usedKeys >= KEYS) return true;

    return false;
}

static void insertInLeaf(BPlusTreeNode* leaf, const int key) {
    const int index = findIndex(leaf->keys, leaf->usedKeys, key);

    for (int i = leaf->usedKeys; i > index; i--) 
        leaf->keys[i] = leaf->keys[i - 1];

    leaf->keys[index] = key;
    leaf->usedKeys++;
}

static void insertInInternalNode(BPlusTreeNode* node, const int key, BPlusTreeNode* child) {
    const int index = findIndex(node->keys, node->usedKeys, key);

    for (int i = node->usedKeys; i > index; i--) {
        node->keys[i] = node->keys[i - 1];
        node->childs[i + 1] = node->childs[i];
    }
        
    node->keys[index] = key;
    node->childs[index + 1] = child;
    node->usedKeys++;
}

static void cleanNode(BPlusTreeNode* node) {
    for (int i = node->usedKeys; i < KEYS; i++) {
        node->keys[i] = 0;
        node->childs[i + 1] = NULL;
    }
}

static Split split(BPlusTreeNode* node, const int key, BPlusTreeNode* child) {
    BPlusTreeNode* newNode = initNode(node->isLeaf);
    
    int keysBuffer[KEYS + 2];
    BPlusTreeNode* childsBuffer[CHILDS + 2];

    if (node->isLeaf) {
        newNode->nextLeaf = node->nextLeaf;
        node->nextLeaf = newNode;
    }

    childsBuffer[0] = node->childs[0];
    int j = 0;
    int i = 0;

    for (i = 0; i < node->usedKeys; i++) {
        if (j == i && key < node->keys[i]) {
            keysBuffer[j] = key;
            childsBuffer[j + 1] = child;
            j++;
        }

        keysBuffer[j] = node->keys[i];
        childsBuffer[j + 1] = node->childs[i + 1];
        j++;
    }

    if (i == j) {
        keysBuffer[j] = key;
        childsBuffer[j + 1] = child;
    }

    const int totalKeys = node->usedKeys + 1;
    const int mid = (node->usedKeys + 1) / 2;

    node->childs[0] = childsBuffer[0];
    for (int i = 0; i < mid; i++) {
        node->keys[i] = keysBuffer[i];
        node->childs[i + 1] = childsBuffer[i + 1];
    }

    node->usedKeys = mid;
    cleanNode(node);

    int upperKey = keysBuffer[mid];
    int start = node->isLeaf ? mid : mid + 1;

    if (!node->isLeaf)
        newNode->childs[0] = childsBuffer[mid + 1];
    else
        newNode->childs[0] = NULL;

    for (int i = start; i < totalKeys; i++) {
        newNode->keys[newNode->usedKeys] = keysBuffer[i];
        newNode->childs[newNode->usedKeys + 1] = childsBuffer[i + 1];
        newNode->usedKeys++;
    }

    const Split result = {true, newNode, upperKey};
    return result;
}

static Split insertRecursion(BPlusTreeNode* node, const int key) {
    const Split result = {false, NULL, 0};

    if (node->isLeaf) {
        if (!isFull(node)) {
            insertInLeaf(node, key);

            return result;
        }

        const Split s = split(node, key, NULL);

        return s;
    }

    const int index = findIndex(node->keys, node->usedKeys, key);

    if (node->keys[index] == key) return result;

    const Split s = insertRecursion(node->childs[index], key);

    if (s.happened) {
        if (!isFull(node)) {
            insertInInternalNode(node, s.upperKey, s.newNode);

            return result;
        }

        const Split parentSplit = split(node, s.upperKey, s.newNode);

        return parentSplit;
    }

    return result;
}

static BPlusTreeNode* bplusInsertHelper(BPlusTreeNode* root, const int key) {
    if (!root) {
        BPlusTreeNode* newNode = initNode(true);
        newNode->keys[0] = key;
        newNode->usedKeys++;
        
        return newNode;
    }

    const Split s = insertRecursion(root, key);

    if (s.happened) {
        BPlusTreeNode* newRoot = initNode(false);

        newRoot->keys[0] = s.upperKey;
        newRoot->childs[0] = root;
        newRoot->childs[1] = s.newNode;
        newRoot->usedKeys++;

        root = newRoot;
    }

    return root;
}

static void deleteInLeaf(BPlusTreeNode* node, const int key) {
    const int index = findIndex(node->keys, node->usedKeys, key);

    if (node->keys[index] != key) return;

    for (int i = index; i < node->usedKeys - 1; i++) {
        node->keys[i] = node->keys[i + 1];
    }

    node->keys[node->usedKeys - 1] = 0;
    node->usedKeys--;
}

static bool borrow(BPlusTreeNode* parent, BPlusTreeNode* child, const int childIndex) {
    if (childIndex - 1 >= 0 && parent->childs[childIndex - 1]->usedKeys > MIN_KEYS) {
        BPlusTreeNode*  sibling = parent->childs[childIndex - 1];
        const int siblingIndex = sibling->usedKeys - 1;

        if (child->isLeaf) {
            // inserting in child
            for (int i = child->usedKeys - 1; i >= 0; i--)
                child->keys[i + 1] = child->keys[i];
            
            child->keys[0] = sibling->keys[siblingIndex];
            child->usedKeys++;

            // removing from sibling
            sibling->keys[siblingIndex] = 0;
            sibling->usedKeys--;

            // adjust key in parent
            parent->keys[childIndex - 1] = child->keys[0];
        } else {
            // inserting in child
            for (int i = child->usedKeys - 1; i >= 0; i--) {
                child->keys[i + 1] = child->keys[i];
                child->childs[i + 2] = child->childs[i + 1];
            }
            child->childs[1] = child->childs[0];
            child->keys[0] = parent->keys[childIndex - 1];
            child->childs[0] = sibling->childs[siblingIndex + 1];
            child->usedKeys++;

            // adjust key in parent
            parent->keys[childIndex - 1] = sibling->keys[siblingIndex];

            // removing from sibling
            sibling->childs[siblingIndex + 1] = NULL;
            sibling->keys[siblingIndex] = 0;
            sibling->usedKeys--;
        }

        return true;
    }

    if (childIndex + 1 <= parent->usedKeys && parent->childs[childIndex + 1]->usedKeys > MIN_KEYS) {
        BPlusTreeNode* sibling = parent->childs[childIndex + 1];

        if (child->isLeaf) {
            // inserting in child
            child->keys[child->usedKeys] = sibling->keys[0];
            child->usedKeys++;

            // removing from sibling
            for (int i = 0; i < sibling->usedKeys - 1; i++)
                sibling->keys[i] = sibling->keys[i + 1];
            
            sibling->keys[sibling->usedKeys - 1] = 0;
            sibling->usedKeys--;
        
            // adjust key in parent
            parent->keys[childIndex] = sibling->keys[0];
        } else {
            // inserting in child
            child->keys[child->usedKeys] = parent->keys[childIndex];
            child->childs[child->usedKeys + 1] = sibling->childs[0];
            child->usedKeys++;

            // adjust key in parent
            parent->keys[childIndex] = sibling->keys[0];

            // removing from sibling
            for (int i = 0; i < sibling->usedKeys - 1; i++) {
                sibling->keys[i] = sibling->keys[i + 1];
                sibling->childs[i] = sibling->childs[i + 1];
            }
            sibling->childs[sibling->usedKeys - 1] = sibling->childs[sibling->usedKeys];
            sibling->keys[sibling->usedKeys - 1] = 0;
            sibling->childs[sibling->usedKeys] = NULL;
            sibling->usedKeys--;
        }

        return true;
    }

    return false;
}

static Underflow merge(BPlusTreeNode* parent, BPlusTreeNode* child, const int childIndex) {
    BPlusTreeNode* right;
    BPlusTreeNode* left;
    int rightIndex;

    if (childIndex - 1 >= 0) {
        right = child;
        left = parent->childs[childIndex - 1];
        rightIndex = childIndex;
    } else {
        right = parent->childs[childIndex + 1];
        left = child;
        rightIndex = childIndex + 1;
    }

    if (child->isLeaf) {
        left->nextLeaf = right->nextLeaf;

        for (int i = 0; i < right->usedKeys; i++) {
            left->keys[left->usedKeys] = right->keys[i];
            left->usedKeys++;
        }

    } else {
        left->keys[left->usedKeys] = parent->keys[rightIndex - 1];
        left->childs[left->usedKeys + 1] = right->childs[0];
        left->usedKeys++;

        for (int i = 0; i < right->usedKeys; i++) {
            left->keys[left->usedKeys] = right->keys[i];
            left->childs[left->usedKeys + 1] = right->childs[i + 1];
            left->usedKeys++;
        }
    }

    // cleaning parent
    for (int i = rightIndex - 1; i < parent->usedKeys - 1; i++) {
        parent->keys[i] = parent->keys[i + 1];
        parent->childs[i + 1] = parent->childs[i + 2];
    }

    parent->keys[parent->usedKeys - 1] = 0;
    parent->childs[parent->usedKeys] = NULL;
    parent->usedKeys--;

    free(right);

    if (parent->usedKeys < MIN_KEYS) {
        const Underflow result = {true, parent};
        return result;
    }

    const Underflow result = {false, NULL};

    return result;
}

static Underflow deleteRecursion(BPlusTreeNode* node, const int key) {
    Underflow result = {false, NULL};

    if (node->isLeaf) {
        deleteInLeaf(node, key);

        if (node->usedKeys < MIN_KEYS) {
            result.happened = true;
            result.node = node;
            return result;
        }

        return result;
    }

    int index = findIndex(node->keys, node->usedKeys, key);

    index = index < node->usedKeys && node->keys[index] == key ? index + 1 : index;

    Underflow u = deleteRecursion(node->childs[index], key);

    if (u.happened) {
        if (borrow(node, u.node, index)) return result;

        return merge(node, u.node, index);
    }

    return result;
}

static BPlusTreeNode* bplusDeleteHelper(BPlusTreeNode* root, const int key) {
    if (!root) return NULL;

    Underflow u = deleteRecursion(root, key);

    if (u.happened) {
        if (root->usedKeys == 0) {
            BPlusTreeNode* newRoot = root->childs[0];
            free(root);
            root =  newRoot;
        }
    }

    return root;
}

static void bplusDestroyHelper(BPlusTreeNode* root) {

    if (!root->isLeaf) {
        for (int i = 0; i < root->usedKeys; i++)
            bplusDestroyHelper(root->childs[i]);
    }

    free(root);
}

// PUBLIC FUNCTIONS
BPlusTree* bplusCreate() {

    BPlusTree* tree = (BPlusTree*) malloc(sizeof(BPlusTree));
    tree->root = NULL;
    return tree;
}

void bplusDestroy(BPlusTree* tree) {

    bplusDestroyHelper(tree->root);
    free(tree);
}

void bplusDelete(BPlusTree* tree, const int key) {

    tree->root = bplusDeleteHelper(tree->root, key);
}

void bplusInsert(BPlusTree* tree, const int key) {

    tree->root = bplusInsertHelper(tree->root, key);
}

void bplusDisplay(BPlusTree* tree) {

    bplusDisplayHelper(tree->root);
}

const int* bplusSearch(BPlusTree* tree, const int key) {
    if (!tree->root) return NULL;

    BPlusTreeNode* node = tree->root;

    while (!node->isLeaf) {
        const int index = findIndex(node->keys, node->usedKeys, key);

        if (index < node->usedKeys && node->keys[index] == key) node = node->childs[index + 1];
        else node = node->childs[index];
    }

    const int index = findIndex(node->keys, node->usedKeys, key);
    if (node->keys[index] == key) return &(node->keys[index]);

    return NULL;
}

void bplusIntervalSearch(BPlusTree* tree, const int minor, const int greater, BPlusCallback action) {
    if (!tree->root) return;

    BPlusTreeNode* node = tree->root;

    while (!node->isLeaf) {
        int index = findIndex(node->keys, node->usedKeys, minor);
        index = index < node->usedKeys && node->keys[index] == minor ? index + 1 : index;

        node = node->childs[index];
    }

    while (node) {
        for (int i = 0; i < node->usedKeys; i++) {
            if (node->keys[i] > greater) return;

            if (node->keys[i] >= minor) action(node->keys[i]);
        }

        node = node->nextLeaf;
    }
}