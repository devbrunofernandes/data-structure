#include "../queue/array_queue.hpp"
#include <cstdio>
#include <cstdlib>

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
    Queue<struct Node*> q;

    printf("Enter root value: ");
    scanf("%d", &x);
    root = (struct Node *) malloc(sizeof(struct Node));
    root->data = x;
    root->lchild = root->rchild = NULL;
    q.enqueue(root);

    while(!q.isEmpty())
    {
        p = q.dequeue();

        printf("Enter left child of %d: ", p->data);
        scanf("%d", &x);
        if(x != -1)
        {
            t = (struct Node *) malloc(sizeof(struct Node));
            t->data = x;
            t->lchild = t->rchild = NULL;
            p->lchild = t;
            q.enqueue(t);
        }

        printf("Enter right child of %d: ", p->data);
        scanf("%d", &x);
        if(x != -1)
        {
            t = (struct Node *) malloc(sizeof(struct Node));
            t->data = x;
            t->lchild = t->rchild = NULL;
            p->rchild = t;
            q.enqueue(t);
        }
    }
}

void preorder(struct Node *p)
{
    if(p)
    {
        printf("%d ", p->data);
        preorder(p->lchild);
        preorder(p->rchild);
    }
}

void inorder(struct Node *p)
{
    if(p)
    {
        preorder(p->lchild);
        printf("%d ", p->data);
        preorder(p->rchild);
    }
}

void postorder(struct Node *p)
{
    if(p)
    {
        preorder(p->lchild);
        preorder(p->rchild);
        printf("%d ", p->data);
    }
}

int main()
{
    create();
    printf("Preorder:");
    preorder(root);
    printf("Inorder:");
    inorder(root);
    printf("Postorder:");
    postorder(root);

    return 0;
}