#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Core/Trees/AVL.h"

#include <stdio.h>

typedef struct AVLNode {
    AVLNode *left;
    int value;
    int height;
    AVLNode *right;
} AVLNode;

typedef struct AVL {
    AVLNode *root;
} AVL;

static AVLNode* findInorderSuccessor(AVLNode *p) {
    if(!p->right) {
        return p;
    }

    p = p->right;
    AVLNode *tail_ptr = p;
    
    while(p) {
        tail_ptr = p;
        p = p->left;
    }

    return tail_ptr;
}

static int nodeHeight(AVLNode *p) {

    int hl = p && p->left ? p->left->height : 0;
    int hr = p && p->right ? p->right->height : 0;

    return hl > hr ? hl + 1 : hr + 1;
}

static bool isLeaf(AVLNode *p) {
    if (p->left || p->right)
        return false;

    return true;
}

static int balanceFactor(AVLNode *p) {

    int hl = p && p->left ? p->left->height : 0;
    int hr = p && p->right ? p->right->height : 0;

    return hl - hr;
}

static AVLNode* llRotate(AVLNode *p) {
    AVLNode *pl = p->left;
    AVLNode *plr = pl->right;

    pl->right = p;
    p->left = plr;

    p->height = nodeHeight(p);
    pl->height = nodeHeight(pl);

    return pl;
}

static AVLNode* lrRotate(AVLNode *p) {
    AVLNode *pl = p->left;
    AVLNode *plr = pl->right;
    
    pl->right = plr->left;
    p->left = plr->right;

    plr->left = pl;
    plr->right = p;

    pl->height = nodeHeight(pl);
    p->height = nodeHeight(p);
    plr->height = nodeHeight(plr);

    return plr;
}

static AVLNode* rrRotate(AVLNode *p) {
    AVLNode *pr = p->right;
    AVLNode *prl = pr->left;

    pr->left = p;
    p->right = prl;
    p->height = nodeHeight(p);
    pr->height = nodeHeight(pr);

    return pr;
}

static AVLNode* rlRotate(AVLNode *p) {
    AVLNode *pr = p->right;
    AVLNode *prl = pr->left;
    
    pr->left = prl->right;
    p->right = prl->left;

    prl->left = p;
    prl->right = pr;

    pr->height = nodeHeight(pr);
    p->height = nodeHeight(p);
    prl->height = nodeHeight(prl);

    return prl;
}

static AVLNode* balanceNode(AVLNode *p) {
    int bf = balanceFactor(p);

    if (bf == 2) {
        if (balanceFactor(p->left) >= 0)
            return llRotate(p);

        return lrRotate(p);
    }

    if (bf == -2) {
        if (balanceFactor(p->right) <= 0) {
            return rrRotate(p);
        }

        return rlRotate(p);
    }

    return p;
}

static AVLNode* avlInsertHelper(AVLNode *p, const int key) {
    if (!p) {
        AVLNode *t = (AVLNode *) malloc(sizeof(AVLNode));
        t->value = key;
        t->height = 1;
        t->left=t->right=NULL;

        return t;
    }

    if (key < p->value) {
        p->left = avlInsertHelper(p->left, key);
    } else if (key > p->value) {
        p->right = avlInsertHelper(p->right, key);
    }

    p->height = nodeHeight(p);

    return balanceNode(p);
}

static AVLNode* avlDeleteHelper(AVLNode *p, const int key) {
    if (!p) {
        return NULL;
    }

    if (key < p->value) {
        p->left = avlDeleteHelper(p->left, key);
    } else if (key > p->value) {
        p->right = avlDeleteHelper(p->right, key);
    } else {
        if (isLeaf(p)) {
            free(p);
            return NULL;
        }

        AVLNode *q = findInorderSuccessor(p);
        p->value = q->value;
        p->right = avlDeleteHelper(p->right, q->value);
    }

    p->height = nodeHeight(p);

    return balanceNode(p);
}   

static AVLNode* avlSearchHelper(AVLNode *p, const int key) {
    if (!p) {return NULL;}

    if (key == p->value) {return p;}

    if (key < p->value) {return avlSearchHelper(p->left, key);}

    return avlSearchHelper(p->right, key);
}

void avlInsert(AVL* tree, const int key) {
    tree->root = avlInsertHelper(tree->root, key);
}

void avlDelete(AVL* tree, const int key) {
    tree->root = avlDeleteHelper(tree->root, key);
}

const int* avlSearch(AVL* tree, const int key) {
    AVLNode* p = avlSearchHelper(tree->root, key);

    if (p == NULL) {return NULL;}

    const int* result = &(p->value);

    return result;
}

static void avlInOrderHelper(AVLNode* p) {
    if (!p) {return;}

    avlInOrderHelper(p->left);
    printf("%d ", p->value);
    avlInOrderHelper(p->right);
}

void avlInOrder(AVL* tree) {
    avlInOrderHelper(tree->root);
}

AVL* avlCreate() {
    AVL* tree = (AVL *) malloc(sizeof(AVL));
    tree->root = NULL;
    return tree;
}

static void avlDestroyHelper(AVLNode* p) {
    if (!p) {return;}

    avlDestroyHelper(p->left);
    avlDestroyHelper(p->right);
    free(p);
}

void avlDestroy(AVL* tree) {
    if (!tree) {return;}

    AVLNode* root = tree->root;

    avlDestroyHelper(root);

    free(tree);
}