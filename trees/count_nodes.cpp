#include <queue>
#include <cstdio>
#include <stdlib.h>

struct Node 
{
    struct Node *lchild;
    int data;
    struct Node *rchild;
} *root = NULL;

void create()
{
    struct Node *p, *t;
    int x;
    std::queue<struct Node*> q;

    printf("Enter root value: ");
    scanf("%d", &x);
    root = (struct Node *) malloc(sizeof(struct Node));
    root->data = x;
    root->lchild = root->rchild = NULL;
    q.push(root);

    while(!q.empty())
    {
        p = q.front();
        q.pop();

        printf("Enter left child of %d: ", p->data);
        scanf("%d", &x);
        if(x != -1)
        {
            t = (struct Node *) malloc(sizeof(struct Node));
            t->data = x;
            t->lchild = t->rchild = NULL;
            p->lchild = t;
            q.push(t);
        }

        printf("Enter right child of %d: ", p->data);
        scanf("%d", &x);
        if(x != -1)
        {
            t = (struct Node *) malloc(sizeof(struct Node));
            t->data = x;
            t->lchild = t->rchild = NULL;
            p->rchild = t;
            q.push(t);
        }
    }
}

int count(struct Node *root) 
{
    if(root)
        return count(root->lchild) + count(root->rchild) + 1;

    return 0;
}

int height(struct Node *root)
{
    int x=0,y=0;
    if(!root)
        return 0;
    x = height(root->lchild);
    y = height(root->rchild);

    if(x > y)
        return x + 1;
    else
        return y + 1;
}

int countLeaf(struct Node *root)
{
    if(!root)
        return 0;
    
    if(!root->lchild && !root->rchild)
        return countLeaf(root->lchild) + countLeaf(root->rchild) + 1;
    return countLeaf(root->lchild) + countLeaf(root->rchild);
}

int main()
{
    create();
    printf("Total of nodes: %d\n", count(root));
    printf("Height of tree: %d\n", height(root));
    printf("Leaf nodes: %d\n", countLeaf(root));

    return 0;
}