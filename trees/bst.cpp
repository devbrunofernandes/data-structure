#include <cmath>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <stack>

struct Node {
    int value;
    struct Node* left;
    struct Node* right;
} *bst_root = NULL;

bool is_leaf(struct Node *p) {
    if(p->left || p->right) {
        return false;
    }

    return true;
}

struct Node* find_inorder_predecessor(struct Node *p) {
    if(!p->left) {
        return p;
    }

    p = p->left;
    struct Node *tail_ptr;
    
    while(p) {
        tail_ptr = p;
        p = p->right;
    }

    return tail_ptr;
}

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

int height(struct Node *p) {
    if(!p) {
        return 0;
    }

    int left_height = height(p->left) + 1;
    int right_height = height(p->right) + 1;

    return left_height > right_height ? left_height : right_height;
}

// recursive functions
struct Node* recursive_insert(struct Node *p, const int key) {
    if(!p) {
        struct Node *t = (struct Node *) malloc(sizeof(struct Node));
        t->value = key;
        t->left=t->right=NULL;

        return t;
    }

    if(key < p->value) {
        p->left = recursive_insert(p->left, key);
    } else if(key > p->value) {
        p->right = recursive_insert(p->right, key);
    }

    return p;
}

struct Node* recursive_search(struct Node *current_node, const int value) {
    if(!current_node) {
        return NULL;
    }

    if(value == current_node->value) {
        return current_node;
    } else if(value < current_node->value) {
        return recursive_search(current_node->left, value);
    } else {
        return recursive_search(current_node->right, value);
    }
}

void inorder(struct Node *current_node) {
    if(current_node) {
        inorder(current_node->left);
        printf("%d ", current_node->value);
        inorder(current_node->right);
    }
}

struct Node* recursive_delete(struct Node *p, const int key) {
    if(!p) {
        return NULL;
    }

    if(key < p->value) {
        p->left = recursive_delete(p->left, key);
    } else if(key > p->value) {
        p->right = recursive_delete(p->right, key);
    } else {
        if(is_leaf(p)) {
            if(p == bst_root) {
                bst_root = NULL;
            }

            free(p);
            return NULL;
        }

        struct Node *q = NULL;

        if(height(p->left) > height(p->right)) {
            q = find_inorder_predecessor(p->left);
            p->value = q->value;
            p->left = recursive_delete(p->left, q->value);
        } else {
            q = find_inorder_successor(p->right);
            p->value = q->value;
            p->right = recursive_delete(p->right, q->value);
        }
    }

    return p;
}

// iteractive funcions
void iteractive_insert(struct Node *t, const int key) {
    struct Node *r = NULL, *p;
    
    if(bst_root == NULL) {
        p = (struct Node *) malloc(sizeof(struct Node));
        p->value = key;
        p->left = NULL;
        p->right = NULL;
        bst_root = p;
        return;
    }

    while(t) {
        r = t;
        if(t->value == key) {
            return;
        } else if(t->value < key) {
            t = t->right;
        } else {
            t = t->left;
        }
    }

    p = (struct Node *) malloc(sizeof(struct Node));
    p->value = key;
    p->left = NULL;
    p->right = NULL;

    if(r) {
        if(r->value > key) {
            r->left = p;
        } else {
            r->right = p;
        }
    }
}

struct Node* iteractive_search(struct Node *t, const int key) {    
    while(t) {
        if(t->value == key) {
            return t;
        } else if(t->value < key) {
            t = t->right;
        } else {
            t = t->left;
        }
    }

    return NULL;
}

void create_preorder(int pre[], int size) {
    std::stack<Node *> stk;
    Node *p, *t;
    int i = 0;

    bst_root = new Node;
    bst_root->value = pre[i++];
    bst_root->left = bst_root->right = nullptr;
    p = bst_root;

    while(i < size) {
        if(pre[i] < p->value) {
            t = new Node;
            t->value = pre[i++];
            t->right = t->left = nullptr;
            p->left = t;
            stk.push(p);
            p = t;
        } else {
            int stk_top = stk.top()->value ? stk.top()->value : INFINITY;
            if(pre[i] > p->value && pre[i] < stk_top) {
                t = new Node;
                t->value = pre[i++];
                t->right = t->left = nullptr;
                p->right = t;
                p = t;
            } else {
                p = stk.top();
                stk.pop();
            }
        }
    }
}

int main() {
    bst_root = recursive_insert(bst_root, 20);
    recursive_insert(bst_root, 10);
    recursive_insert(bst_root, 25);
    recursive_insert(bst_root, 40);
    recursive_insert(bst_root, 35);
    recursive_insert(bst_root, 50);

    recursive_delete(bst_root, 25);

    inorder(bst_root);

    return 0;
}