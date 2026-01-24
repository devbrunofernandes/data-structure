#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "Core/Trees/RBT.h"

typedef struct RBTNode {
    int value;
    struct RBTNode* left;
    struct RBTNode* right;
    bool isRed;
} RBTNode;

RBTNode* initRBTNode(int key) {
    RBTNode* node = (RBTNode*) malloc(sizeof(RBTNode));

    node->left = NULL;
    node->right = NULL;
    node->value = key;
    node->isRed = true;

    return node;
}

// Helper structs
typedef struct Conflict {
    bool happened;
    RBTNode* parent;
    RBTNode* child;
} Conflict;

typedef struct Successor {
    RBTNode* node;
    RBTNode* subtree;
} Successor;

typedef struct Deletion {
    bool happened;
    RBTNode* child;
    bool deleteNode;
} Deletion;

typedef struct RBT {
    RBTNode* root;
} RBT;


static bool isBlack(RBTNode* node) {
    bool answer = true;
    if (node && node->isRed) {answer = false;}
    return answer;
}

static bool isLeaf(RBTNode* node) {
    return !node->left && !node->right;
}

static void recolor(RBTNode* grandparent) {
    grandparent->isRed = true;
    grandparent->left->isRed = false;
    grandparent->right->isRed = false;
}

static RBTNode* RR(RBTNode* node) {
    RBTNode* r = node->right;
    RBTNode* rl = r->left;

    node->right = rl;
    r->left = node;

    node->isRed = true;
    r->isRed = false;

    return r;
}

static RBTNode* LL(RBTNode* node) {
    RBTNode* l = node->left;
    RBTNode* lr = l->right;

    node->left = lr;
    l->right = node;

    node->isRed = true;
    l->isRed = false;

    return l;
}

static RBTNode* RL(RBTNode* node) {
    RBTNode* r = node->right;
    RBTNode* rl = r->left;

    node->right = rl->left;
    r->left = rl->right;

    rl->left = node;
    rl->right = r;

    rl->isRed = false;
    node->isRed = true;

    return rl;
}

static RBTNode* LR(RBTNode* node) {
    RBTNode* l = node->left;
    RBTNode* lr = l->right;

    node->left = lr->right;
    l->right = lr->left;

    lr->right = node;
    lr->left = l;

    lr->isRed = false;
    node->isRed = true;

    return lr;
}

static RBTNode* rotate(RBTNode* grandparent, RBTNode* parent, RBTNode* child) {
    if (parent == grandparent->right) {
        if (child == parent->right)
            return RR(grandparent);

        return RL(grandparent);
    }

    if (child == parent->right)
        return LR(grandparent);

    return LL(grandparent);
}

static Conflict insertHelper(RBTNode* node, const int key) {
    Conflict result = {false, NULL, node};

    if (node && node->value == key) return result;

    if (!node) {
        RBTNode* newNode = initRBTNode(key);
        result.child = newNode;
        return result;
    }

    Conflict c;

    if (key > node->value) {
        c = insertHelper(node->right, key);
        node->right = c.happened ? c.parent : c.child;
    } else {
        c = insertHelper(node->left, key);
        node->left = c.happened ? c.parent : c.child;
    }

    if (c.child->isRed && node->isRed) {
        result.happened = true;
        result.parent = node;
        result.child = c.child;
        return result;
    }

    if (c.happened) {
        RBTNode* uncle = c.parent == node->right ? node->left : node->right;

        if (isBlack(uncle)) {
            result.child = rotate(node, c.parent, c.child);
            result.happened = false;
            result.parent = NULL;
            return result;
        }

        recolor(node);
    }

    return c;
}

static Successor findSubstitute(RBTNode* node) {
    RBTNode* subtree = NULL;

    if (node->right) {
        subtree = node->right;
        node = node->right;

        while (node->left) node = node->left;
    } else {
        subtree = node->left;
        node = node->left;

        while (node->right) node = node->right;
    }

    const Successor s = {node, subtree};
    return s;
}

bool hasOneChild(RBTNode* node) {
    return (node->left && !node->right) || (node->right && !node->left);
}

static RBTNode* getChild(RBTNode* node) {
    RBTNode* child = NULL;

    if (node->left) {
        child = node->left;
    } else {
        child = node->right;
    }

    return child;
}

static RBTNode* getRedNephew(RBTNode* sibling) {
    if (sibling->left && sibling->left->isRed) return sibling->left;

    if (sibling->right && sibling->right->isRed) return sibling->right;

    return NULL;
}

static Deletion rebalance(RBTNode* node, Deletion d) {
    Deletion result = {false, node, false};

    const bool childInRight = (node->right == d.child);
    RBTNode* sibling =  childInRight ? node->left : node->right;

    if (!sibling) {
        result.happened = true;
        return result;
    }

    if (sibling->isRed) {
        RBTNode* newRoot = childInRight ? LL(node) : RR(node);

        RBTNode* originalParent = childInRight ? newRoot->right : newRoot->left;

        const Deletion subResult = rebalance(originalParent, d);

        if (childInRight) newRoot->right = subResult.child;
        else newRoot->left = subResult.child;

        result.child = newRoot;
        return result;
    }

    if (isBlack(sibling->left) && isBlack(sibling->right)) {
        sibling->isRed = true;

        if (node->isRed) {
            node->isRed = false;
        } else {
            result.happened = true;
        }

    } else {
        const bool originalParentColor = node->isRed;

        RBTNode* nephew = getRedNephew(sibling);

        RBTNode* newRoot = rotate(node, sibling, nephew);

        newRoot->isRed = originalParentColor;

        newRoot->left->isRed = false;
        newRoot->right->isRed = false;

        result.child = newRoot;
    }


    if (d.deleteNode) {
        free(d.child);
        if (childInRight) node->right = NULL;
        else node->left = NULL;
    }

    return result;
}

static Deletion removeHelper(RBTNode* node, const int key) {
    Deletion result = {false, node, false};

    if (!node) return result;

    if (node->value == key) {
        if (isLeaf(node) && node->isRed) {
            free(node);
            result.child = NULL;
            return result;
        }

        if (isLeaf(node) && isBlack(node)) {
            result.deleteNode = true;
            result.happened = true;
            return result;
        }

        if (hasOneChild(node) && node->isRed) {
            RBTNode* child = getChild(node);
            free(node);
            result.child = child;
            return result;
        }

        const Successor s = findSubstitute(node);

        node->value = s.node->value;

        const Deletion d = removeHelper(s.subtree, s.node->value);

        if (node->right == s.subtree)
            node->right = d.child;
        else
            node->left = d.child;

        if (d.happened) return rebalance(node, d);

        return result;
    }

    Deletion d;

    if (key > node->value) {
        d = removeHelper(node->right, key);
        node->right = d.child;
    } else {
        d = removeHelper(node->left, key);
        node->left = d.child;
    }

    if (d.happened) return rebalance(node,d);

    return result;
}

static void rbtInOrderHelper(RBTNode* p) {
    if (!p) {return;}

    rbtInOrderHelper(p->left);
    printf("%d ", p->value);
    rbtInOrderHelper(p->right);
}

static void rbtDestroyHelper(RBTNode* p) {
    if (!p) {return;}

    rbtDestroyHelper(p->left);
    rbtDestroyHelper(p->right);
    free(p);
}

// PUBLIC FUNCTIONS
RBT* rbtCreate() {
    RBT* tree = (RBT*) malloc(sizeof(RBT));
    tree->root = NULL;
    return tree;
}

void rbtInsert(RBT* tree, const int key) {
    if (!tree->root) {
        tree->root = initRBTNode(key);
        tree->root->isRed = false;
        return;
    }

    Conflict c = insertHelper(tree->root, key);
    tree->root = c.child;

    tree->root->isRed = false;
}

void rbtDelete(RBT* tree, const int key) {
    if (!tree->root) return;

    if (key == tree->root->value && isLeaf(tree->root)) {
        free(tree->root);
        tree->root = NULL;
        return;
    }

    Deletion d = removeHelper(tree->root, key);

    if (d.happened) {
        d = rebalance(tree->root, d);
    }

    tree->root = d.child;

    if (tree->root) tree->root->isRed = false;
}

const int* rbtSearch(RBT* tree, const int key) {
    RBTNode* node = tree->root;

    while (node) {
        if (key > node->value) {
            node = node->right;
        } else if (key < node->value) {
            node = node->left;
        } else {
            return &(node->value);
        }
    }

    return NULL;
}

void rbtInOrder(RBT* tree) {
    rbtInOrderHelper(tree->root);
}

void rbtDestroy(RBT* tree) {
    if (!tree) {return;}

    RBTNode* root = tree->root;

    rbtDestroyHelper(root);

    free(tree);
}

