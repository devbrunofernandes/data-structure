#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "stdbool.h"
#include "Core/Trees/BST.h"

typedef struct BSTNode {
    int value;
    BSTNode* left;
    BSTNode* right;
} BSTNode;

typedef struct BST {
    BSTNode* root;
} BST;

static bool isLeaf(BSTNode *p) {
    if (p->left || p->right)
        return false;

    return true;
}

static BSTNode* findInorderPredecessor(BSTNode* p) {
    if (!p->left) return p;

    p = p->left;
    BSTNode *tail_ptr = p;
    
    while(p) {
        tail_ptr = p;
        p = p->right;
    }

    return tail_ptr;
}

static BSTNode* findInorderSuccessor(BSTNode* p) {
    if(!p->right) return p;

    p = p->right;
    BSTNode* tail_ptr = p;
    
    while(p) {
        tail_ptr = p;
        p = p->left;
    }

    return tail_ptr;
}

static int height(BSTNode* p) {
    if(!p) return 0;

    int left_height = height(p->left) + 1;
    int right_height = height(p->right) + 1;

    return left_height > right_height ? left_height : right_height;
}

static BSTNode* bstInsertHelper(BSTNode* p, const int key) {
    if(!p) {
        BSTNode* t = (BSTNode*) malloc(sizeof(BSTNode));
        t->value = key;
        t->left=t->right=NULL;

        return t;
    }

    if(key < p->value) {
        p->left = bstInsertHelper(p->left, key);
    } else if(key > p->value) {
        p->right = bstInsertHelper(p->right, key);
    }

    return p;
}

void bstInsert(BST* tree, const int key) {

    tree->root = bstInsertHelper(tree->root, key);
}

static BSTNode* bstSearchHelper(BSTNode* current_node, const int value) {
    if(!current_node)
        return NULL;

    if(value == current_node->value)
        return current_node;

    if(value < current_node->value)
        return bstSearchHelper(current_node->left, value);

    return bstSearchHelper(current_node->right, value);
}

const int* bstSearch(BST* tree, const int key) {
    BSTNode* p = bstSearchHelper(tree->root, key);

    if (p == NULL) {return NULL;}

    return &(p->value);
}

static BSTNode* bstDeleteHelper(BSTNode* p, const int key) {
    if(!p) {return NULL;}

    if(key < p->value) {
        p->left = bstDeleteHelper(p->left, key);
    } else if(key > p->value) {
        p->right = bstDeleteHelper(p->right, key);
    } else {
        if(isLeaf(p)) {
            free(p);
            return NULL;
        }

        BSTNode* q = NULL;

        if(height(p->left) > height(p->right)) {
            q = findInorderPredecessor(p);
            p->value = q->value;
            p->left = bstDeleteHelper(p->left, q->value);
        } else {
            q = findInorderSuccessor(p);
            p->value = q->value;
            p->right = bstDeleteHelper(p->right, q->value);
        }
    }

    return p;
}

void bstDelete(BST* tree, const int key) {
    tree->root = bstDeleteHelper(tree->root, key);
}

static void bstInOrderHelper(BSTNode* p) {
    if (!p) {return;}

    bstInOrderHelper(p->left);
    printf("%d ", p->value);
    bstInOrderHelper(p->right);
}

void bstInOrder(BST* tree) {
    bstInOrderHelper(tree->root);
}

BST* bstCreate() {
    BST* tree = (BST *) malloc(sizeof(BST));
    tree->root = NULL;
    return tree;
}

static void bstDestroyHelper(BSTNode* p) {
    if (!p) {return;}

    bstDestroyHelper(p->left);
    bstDestroyHelper(p->right);
    free(p);
}

void bstDestroy(BST* tree) {
    if (!tree) {return;}

    BSTNode* root = tree->root;

    bstDestroyHelper(root);

    free(tree);
}