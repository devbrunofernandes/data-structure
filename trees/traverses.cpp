#include <cstdio>
#include <stack>
#include <queue>

using namespace std;

struct Node
{
    Node *lchild;
    int data;
    Node *rchild;
} *root;

/* 
    TYPES OF TRAVERSE:
    Preorder traverse -> Use current node -> go to the left child -> go to the right child.
    Inorder traverse -> go to the left child -> Use current node -> go to the right child. 
    Postorder traverse -> go to the left child -> go to the right child -> Use current node.
    Levelorder -> Traverse top to bottom, left to right for each level of the tree.
*/

// RECURSIVE TRAVERSES ==============================================
void preorder(Node *p)
{
    if(p)
    {
        printf("%d ", p->data);
        preorder(p->lchild);
        preorder(p->rchild);
    }
}

void inorder(Node *p)
{
    if(p)
    {
        preorder(p->lchild);
        printf("%d ", p->data);
        preorder(p->rchild);
    }
}

void postorder(Node *p)
{
    if(p)
    {
        preorder(p->lchild);
        preorder(p->rchild);
        printf("%d ", p->data);
    }
}
// =====================================================================

// ITERATIVE TRAVERSES ==============================================
void levelorder(Node *root)
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

void preorderIt(Node *p)
{
    stack<Node*> s;

    while(!s.empty() || p) 
    {
        if(p) {
            printf("%d ", p->data);
            s.push(p);
            p = p->lchild;
        } else {
            p = s.top();
            s.pop();
            p = p->rchild;
        }
    }
}

void inorderIt(Node *p)
{
    stack<Node*> s;

    while(!s.empty() || p) 
    {
        if(p) {
            s.push(p);
            p = p->lchild;
        } else {
            p = s.top();
            s.pop();
            printf("%d ", p->data);
            p = p->rchild;
        }
    }
}

void postorderIt(Node *p)
{
    stack<long int> s;
    long int temp;

    while(!s.empty() || p) 
    {
        if(p) {
            s.push((long int) p);
            p = p->lchild;
        } else {
            temp = s.top();
            s.pop();
            if(temp > 0) {
                s.push(-temp);
                p = ((Node *) temp)->rchild;
            }
            else {
                printf("%d ", ((Node *) -temp)->data);
                p = NULL;
            } 
        }
    }
}
// =====================================================================

int main()
{
    Node *root = new Node();
    root->data = 20;
    root->lchild = new Node();
    root->lchild->data = 10;
    root->rchild = new Node();
    root->rchild->data = 30;

    preorderIt(root);
    printf("\n");
    inorderIt(root);
    printf("\n");
    postorderIt(root);
    printf("\n");
    levelorder(root);
    printf("\n");

    return 0;
}