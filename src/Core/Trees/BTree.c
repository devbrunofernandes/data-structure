#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "Core/Trees/BTree.h"

#define KEYS 3
#define MIN_KEYS (KEYS / 2)
#define CHILDS (KEYS + 1)

// MAIN STRUCTS
typedef struct BTreeNode {
    int keys[KEYS];
    struct BTreeNode* childs[CHILDS];
    int usedKeys;
} BTreeNode;

typedef struct BTree {
    BTreeNode* root;
} BTree;

// INITIALIZE NODES
static BTreeNode* initNode() {
    BTreeNode* node = (BTreeNode*) malloc(sizeof(BTreeNode));

    for (int i = 0; i < CHILDS; i++) {node->childs[i] = NULL;}
    for (int i = 0; i < KEYS; i++) {node->keys[i] = 0;}
    node->usedKeys = 0;

    return node;
}

static BTreeNode* initNodeKey(const int key) {
    BTreeNode* node = (BTreeNode*) malloc(sizeof(BTreeNode));

    for (int i = 0; i < CHILDS; i++) {node->childs[i] = NULL;}
    for (int i = 1; i < KEYS; i++) {node->keys[i] = 0;}
    node->keys[0] = key;
    node->usedKeys = 1;

    return node;
}

// HELPER STRUCTS
typedef struct Empty {
    BTreeNode* deletedNode;
    bool happened;
} Empty;

typedef struct Successor {
    BTreeNode* node;
    BTreeNode* subtree;
} Successor;


static bool isLeaf(BTreeNode* root) {
    if (!root) {return false;}

    if (root->childs[0])
        return false;

    return true;
}

static int findIndex(const int array[], const int size, const int key) {
    int left = 0;
    int right = size - 1;

    while (left <= right) {
        int mid = ((right - left) / 2) + left;

        if (array[mid] == key)
            return mid;

        if (array[mid] < key) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return left;
}

static BTreeNode* findNext(BTreeNode* root, const int key) {
    int index = findIndex(root->keys, root->usedKeys, key);

    BTreeNode* targetChild = root->childs[index];

    return targetChild;
}

static bool isFull(BTreeNode* root) {
    if (root->usedKeys == KEYS) return true;

    return false;
}

static void insertCombined(BTreeNode* node, const int key, BTreeNode* child) {
    int i = node->usedKeys - 1;

    while (i >= 0 && key < node->keys[i]) {
        node->keys[i + 1] = node->keys[i];
        node->childs[i + 2] = node->childs[i + 1];
        i--;
    }

    node->keys[i + 1] = key;
    node->childs[i + 2] = child;
    node->usedKeys++;
}

static void cleanNodeGarbage(BTreeNode* node) {
    for (int i = node->usedKeys; i < KEYS; i++) {
        node->keys[i] = 0;
        node->childs[i + 1] = NULL;
    }
}

static void split(BTreeNode* node, BTreeNode* child) {
    BTreeNode* newNode = initNode();
    int mid = child->usedKeys / 2;

    newNode->childs[0] = child->childs[mid + 1];

    for (int i = mid + 1; i < child->usedKeys; i++) {
        int index = i - mid - 1;
        newNode->keys[index] = child->keys[i];
        newNode->childs[index + 1] = child->childs[i + 1];
        newNode->usedKeys++; 
    }

    cleanNodeGarbage(child);

    child->usedKeys = mid;

    insertCombined(node, child->keys[mid], newNode);
}

static BTreeNode* insert(BTreeNode* root, const int key) {
    if (!root) {
        return initNodeKey(key);
    }

    if (isFull(root)) {
        BTreeNode* newRoot = initNode();
        newRoot->childs[0] = root;
        split(newRoot, root);

        root = newRoot;
    }

    BTreeNode* curr = root;
    while (!isLeaf(curr)) {
        int index = findIndex(curr->keys, curr->usedKeys, key);
        BTreeNode* child = curr->childs[index];

        if (isFull(child)) {
            split(curr, child);

            if (key > curr->keys[index]) {
                child = curr->childs[index + 1];
            }
        }

        curr = child;
    }

    insertCombined(curr, key, NULL);

    return root;
}

static Successor findSuccessor(BTreeNode* root, const int key) {
    BTreeNode* node = NULL;
    BTreeNode* subtree = NULL;

    int index = findIndex(root->keys, root->usedKeys, key);

    subtree = root->childs[index + 1];

    node = subtree;
    while (node->childs[0]) {
        node = node->childs[0];
    }

    const Successor s = {node, subtree};
    return s;
}

static bool boundCheck(const int index, const int limit) {
    return index >= 0 && index < limit;
}

static BTreeNode* popRight(BTreeNode* node) {
    BTreeNode* removedChild = node->childs[node->usedKeys];

    node->childs[node->usedKeys] = NULL;
    node->keys[node->usedKeys - 1] = 0;

    node->usedKeys--;
    return removedChild;
}

static BTreeNode* popLeft(BTreeNode* node) {
    BTreeNode* removedChild = node->childs[0];

    for (int i = 0; i < node->usedKeys - 1; i++) {
        node->keys[i] = node->keys[i + 1];
        node->childs[i] = node->childs[i + 1];
    }

    node->childs[node->usedKeys - 1] = node->childs[node->usedKeys];
    node->childs[node->usedKeys] = NULL;
    node->keys[node->usedKeys - 1] = 0;

    node->usedKeys--;
    return removedChild;
}

static void insertLeft(BTreeNode* node, const int key, BTreeNode* child) {
    for (int i = node->usedKeys; i > 0; i--) {
        node->keys[i] = node->keys[i - 1];
        node->childs[i + 1] = node->childs[i];
    }

    node->childs[1] = node->childs[0];
    node->childs[0] = child;
    node->keys[0] = key;

    node->usedKeys++;
}

static bool borrow(BTreeNode* node, BTreeNode* child) {
    int i = 0;
    while (i <= node->usedKeys && node->childs[i] != child) {i++;}

    int upperLimit = node->usedKeys + 1;
    BTreeNode* currChild = NULL;

    if (boundCheck(i + 1, upperLimit) && node->childs[i + 1]->usedKeys >= MIN_KEYS) {
        currChild = node->childs[i + 1];

        insertCombined(child, node->keys[i], currChild->childs[0]);
        node->keys[i] = currChild->keys[0];
        popLeft(currChild);

        return true;
    }

    if (boundCheck(i - 1, upperLimit) && node->childs[i - 1]->usedKeys >= MIN_KEYS) {
        currChild = node->childs[i - 1];

        insertLeft(child, node->keys[i - 1], currChild->childs[currChild->usedKeys]);
        node->keys[i - 1] = currChild->keys[currChild->usedKeys - 1];
        popRight(currChild);

        return true;
    }

    return false;
}

static bool merge(BTreeNode* node, BTreeNode* child) {
    bool childSurvived = true;

    int i = 0;
    while (i <= node->usedKeys && node->childs[i] != child) {i++;}

    BTreeNode* left = NULL;
    BTreeNode* right = NULL;
    int parentIndex = 0;
    
    if (i < node->usedKeys) {
        left = child;
        right = node->childs[i + 1];
        parentIndex = i;
    } else {
        left = node->childs[i - 1];
        right = child;
        parentIndex = i - 1;
        childSurvived = false;
    }

    left->keys[left->usedKeys] = node->keys[parentIndex];
    left->childs[left->usedKeys + 1] = right->childs[0];
    left->usedKeys++;

    for (int j = 0; j < right->usedKeys; j++) {
        left->keys[left->usedKeys] = right->keys[j];
        left->childs[left->usedKeys + 1] = right->childs[j + 1];
        left->usedKeys++;
    }

    for (int j = parentIndex; j < node->usedKeys - 1; j++) {
        node->keys[j] = node->keys[j + 1];
        node->childs[j + 1] = node->childs[j + 2];
    }
    
    node->keys[node->usedKeys - 1] = 0;
    node->childs[node->usedKeys] = NULL;
    node->usedKeys--;

    free(right);

    return childSurvived;
}

static void removeKeyInLeaf(BTreeNode* node, const int key) {
    int index = findIndex(node->keys, node->usedKeys, key);

    if (!(node->keys[index] == key) || !isLeaf(node)) {return;}

    for (int i = index; i < node->usedKeys - 1; i++) {
        node->keys[i] = node->keys[i + 1];
    }

    node->keys[node->usedKeys - 1] = 0;
    node->usedKeys--;
}

static BTreeNode* btreeDeleteHelper(BTreeNode* root, int key) {
    if (!root) {return NULL;}

    if (root->usedKeys == 1 && !isLeaf(root)) {
        BTreeNode* left = root->childs[0];
        BTreeNode* right = root->childs[1];

        if (left->usedKeys < MIN_KEYS && right->usedKeys < MIN_KEYS) {
            merge(root, left);
            BTreeNode* newRoot = left;
            free(root);
            root = newRoot;
        }
    }

    BTreeNode* curr = root;

    while (!isLeaf(curr)) {
        int index = findIndex(curr->keys, curr->usedKeys, key);

        if (index < curr->usedKeys && curr->keys[index] == key) {
            Successor s = findSuccessor(curr, key);
            curr->keys[index] = s.node->keys[0];
            key = s.node->keys[0];

            index++;
        }

        BTreeNode* child = curr->childs[index];
        
        if (child->usedKeys < MIN_KEYS) {
            if (!borrow(curr, child)) {
                merge(curr, child);
            }

            index = findIndex(curr->keys, curr->usedKeys, key);
            if (index < curr->usedKeys && curr->keys[index] == key) {index++;}
            child = curr->childs[index];
        }

        curr = child;
    }

    removeKeyInLeaf(curr, key);

    if (root->usedKeys == 0) {
        BTreeNode* temp = NULL;
        if (!isLeaf(root)) {
            temp = root->childs[0];
        }
        free(root);
        return temp;
    }

    return root;
}

static void deleteTree(BTreeNode* root) {
    if (!root) {return;}

    for (int i = 0; i <= root->usedKeys; i++) {
        if (root->childs[i]) deleteTree(root->childs[i]);
    }

    free(root);
}

static void btreeInOrderHelper(BTreeNode* root) {
    if (!root) {return;}

    for (int i = 0; i < root->usedKeys; i++) {
        btreeInOrderHelper(root->childs[i]);
        printf("%d ", root->keys[i]);
    }

    btreeInOrderHelper(root->childs[root->usedKeys]);
}

// PUBLIC FUNCTIONS

BTree* btreeCreate() {
    BTree* tree = (BTree*) malloc(sizeof(BTree));
    tree->root = NULL;
    return tree;
}

void btreeDestroy(BTree* tree) {
    deleteTree(tree->root);
    free(tree);
}

void btreeInOrder(BTree* tree) {
    btreeInOrderHelper(tree->root);
}

const int* btreeSearch(BTree* tree, const int key) {
    BTreeNode* curr = tree->root;

    while (curr) {
        int index = findIndex(curr->keys, curr->usedKeys, key);

        if (index < curr->usedKeys && curr->keys[index] == key)
            return &(curr->keys[index]);

        curr = curr->childs[index];
    }

    return NULL;
}

void btreeInsert(BTree* tree, const int key) {
    tree->root = insert(tree->root, key);
}

void btreeDelete(BTree* tree, const int key) {
    tree->root = btreeDeleteHelper(tree->root, key);
}