#include <queue>
#include <cstdio>
#include <cstdlib>

using namespace std;

class Node 
{
public:
    struct Node *lchild;
    int data;
    struct Node *rchild;
};

class Tree 
{
public:
    Node *root;

    Tree() {root = NULL;}
    void create();
    void preorder(Node *p);
    void postorder(Node *p);
    void inorder(Node *p);
    void levelorder(Node *p);
    int height(Node *p);
};

void Tree::create()
{
    Node *p, *t;
    int x;
    queue<Node*> q;

    printf("Enter root value: ");
    scanf("%d", &x);
    root = new Node;
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
            t = new Node;
            t->data = x;
            t->lchild = t->rchild = NULL;
            p->lchild = t;
            q.push(t);
        }

        printf("Enter right child of %d: ", p->data);
        scanf("%d", &x);
        if(x != -1)
        {
            t = new Node;
            t->data = x;
            t->lchild = t->rchild = NULL;
            p->rchild = t;
            q.push(t);
        }
    }
}

void Tree::preorder(Node *p)
{
    if(p)
    {
        printf("%d ", p->data);
        preorder(p->lchild);
        preorder(p->rchild);
    }
}

void Tree::inorder(Node *p)
{
    if(p)
    {
        preorder(p->lchild);
        printf("%d ", p->data);
        preorder(p->rchild);
    }
}

void Tree::postorder(Node *p)
{
    if(p)
    {
        preorder(p->lchild);
        preorder(p->rchild);
        printf("%d ", p->data);
    }
}

void Tree::levelorder(Node *root)
{
    queue<Node*> q;

    printf("%d ", root->data);
    q.push(root);

    while(!q.empty())
    {
        root = q.front();
        q.pop();
        if(root->lchild)
        {
            printf("%d ", root->lchild->data);
            q.push(root->lchild);
        }
        if(root->rchild)
        {
            printf("%d ", root->rchild->data);
            q.push(root->rchild);
        }
    }
}

int Tree::height(Node *root)
{
    int x=0, y=0;
    if(root == NULL)
        return 0;

    x = height(root->lchild);
    y = height(root->rchild);
    if(x > y)
        return x+1;
    else
        return y+1;
}

int main()
{
    Tree t;
    t.create();
    t.preorder(t.root);
    printf("\n");
    t.inorder(t.root);
    printf("\n");
    t.postorder(t.root);
    printf("\n");
    t.levelorder(t.root);
    printf("\n");
    printf("height: %d\n", t.height(t.root));

    return 0;
}