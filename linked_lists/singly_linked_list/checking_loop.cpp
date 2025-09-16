#include <cstdlib>
#include <stdio.h>

// More flexible data structure than arrays, can decrease and increase in size easily.

// A NODE IN LINKED LIST TAKE THE DATA AND A POINTER TO THE NEXT NODE
struct Node
{
    int data;
    struct Node *next;
}; // GLOBAL POINTER TO FIRST AND LAST ELEMENT IN LINKED LIST

// CREATION OF LINKED LIST USING AN ARRAY AS PARAMETER
struct Node *create(int A[], int n)
{
    int i;
    struct Node *t, *last, *first;

    first = (struct Node *) malloc(sizeof(struct Node));
    first->data = A[0];
    first->next = NULL;
    last = first;

    for (i=1; i<n;i++)
    {
        t = (struct Node *) malloc(sizeof(struct Node));
        t->data = A[i];
        t->next = NULL;
        last->next = t;
        last = t;
    }

    return first;
}

void display(struct Node *p)
{
    while(p)
    {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

// uses two pointers to check if the list has loop
// one pointers move 1 step and the other 2 steps. if the pointers meet at the same value means the list has loop
bool is_loop_2pointers(struct Node *p)
{
    struct Node *q;

    do
    {
        p = p->next;
        q = q->next;
        q=q?q->next:q;
    } while (p && q && p!=q);

    if (q == p)
        return true;
    return false;
}

int main()
{
    int A[] = {1,2,3,4,5};
    struct Node *first = create(A, 5), *t1, *t2;

    // setting loop
    t1=first->next->next;
    t2=first->next->next->next->next;
    t2->next = t1;

    is_loop_2pointers(first)?printf("The list has loop\n"):printf("The list has no loop\n");

    return 0;
}