#include <cmath>
#include <cstddef>
#include <cstdio>
#include <cstdlib>

struct Node {
    struct Node *left;
    int value;
    int height;
    struct Node *right;
};

struct Node* find_inorder_successor(struct Node *p) {
    if(!p->right) {
        return p;
    }

    p = p->right;
    struct Node *tail_ptr;
    
    while(p) {
        tail_ptr = p;
        p = p->left;
    }

    return tail_ptr;
}

int node_height(struct Node *p) {
    int hl, hr;
    hl = p && p->left ? p->left->height : 0;
    hr = p && p->right ? p->right->height : 0;

    return hl > hr ? hl + 1 : hr + 1;
}

bool is_leaf(struct Node *p) {
    if (p->left || p->right) {
        return false;
    }

    return true;
}

int balance_factor(struct Node *p) {
    int hl, hr;
    hl = p && p->left ? p->left->height : 0;
    hr = p && p->right ? p->right->height : 0;

    return hl - hr;
}

struct Node* LL_rotate(struct Node *p) {
    struct Node *pl = p->left;
    struct Node *plr = pl->right;

    pl->right = p;
    p->left = plr;

    p->height = node_height(p);
    pl->height = node_height(pl);

    return pl;
}

struct Node* LR_rotate(struct Node *p) {
    struct Node *pl = p->left;
    struct Node *plr = pl->right;
    
    pl->right = plr->left;
    p->left = plr->right;

    plr->left = pl;
    plr->right = p;

    pl->height = node_height(pl);
    p->height = node_height(p);
    plr->height = node_height(plr);

    return plr;
}

struct Node* RR_rotate(struct Node *p) {
    struct Node *pr = p->right;
    struct Node *prl = pr->left;

    pr->left = p;
    p->right = prl;
    p->height = node_height(p);
    pr->height = node_height(pr);

    return pr;
}

struct Node* RL_rotate(struct Node *p) {
    struct Node *pr = p->right;
    struct Node *prl = pr->left;
    
    pr->left = prl->right;
    p->right = prl->left;

    prl->left = p;
    prl->right = pr;

    pr->height = node_height(pr);
    p->height = node_height(p);
    prl->height = node_height(prl);

    return prl;
}

struct Node* balance_node(struct Node *p) {
    int bf = balance_factor(p);

    if (bf == 2) {
        if (balance_factor(p->left) >= 0) {
            return LL_rotate(p);
        } else {
            return LR_rotate(p);
        }
    } else if (bf == -2) {
        if (balance_factor(p->right) <= 0) {
            return RR_rotate(p);
        } else {
            return RL_rotate(p);
        }
    }

    return p;
}

struct Node* recursive_insert(struct Node *p, const int key) {
    if (!p) {
        struct Node *t = (struct Node *) malloc(sizeof(struct Node));
        t->value = key;
        t->height = 1;
        t->left=t->right=NULL;

        return t;
    }

    if (key < p->value) {
        p->left = recursive_insert(p->left, key);
    } else if (key > p->value) {
        p->right = recursive_insert(p->right, key);
    }

    p->height = node_height(p);

    return balance_node(p);
}

struct Node* recursive_delete(struct Node *p, const int key) {
    if (!p) {
        return NULL;
    }

    if (key < p->value) {
        p->left = recursive_delete(p->left, key);
    } else if (key > p->value) {
        p->right = recursive_delete(p->right, key);
    } else {
        if (is_leaf(p)) {
            free(p);
            return NULL;
        }

        struct Node *q = find_inorder_successor(p);
        p->value = q->value;
        p->right = recursive_delete(p->right, q->value);
    }

    p->height = node_height(p);

    return balance_node(p);
}   

int main() {
    struct Node *root = NULL;

    root = recursive_insert(root, 50);
    root = recursive_insert(root, 10);
    root = recursive_insert(root, 20);

    return 0;
}