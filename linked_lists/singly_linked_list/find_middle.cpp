#include <cstdlib>
#include <stdio.h>

// More flexible data structure than arrays, can decrease and increase in size easily.

// A NODE IN LINKED LIST TAKE THE DATA AND A POINTER TO THE NEXT NODE
struct Node
{
    int data;
    struct Node *next;
}*first = NULL; // GLOBAL POINTER TO FIRST ELEMENT IN LINKED LIST

// CREATION OF LINKED LIST USING AN ARRAY AS PARAMETER
void create(int A[], int n)
{
    int i;
    struct Node *t, *last;

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

int find_middle(struct Node *p)
{
    struct Node *q = p;

    while (q)
    {
        q=q->next;
        if (q)
            q = q->next;
        if (q)
            p =p->next;
    }

    return p->data;
}

int main()
{
    int A[] = {3,5,7,10,15,8,12,2};
    create(A, 8);

    printf("middle value: %d\n", find_middle(first));
    display(first);

    return 0;
}