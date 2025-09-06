#include <cstdlib>
#include <stdio.h>

// More flexible data structure than arrays, can decrease and increase in size easily.

// A NODE IN LINKED LIST TAKE THE DATA AND A POINTER TO THE NEXT NODE
struct Node
{
    int data;
    struct Node *next;
}*first = NULL,*last = NULL; // GLOBAL POINTER TO FIRST AND LAST ELEMENT IN LINKED LIST

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

void remove_duplicates(struct Node *p)
{
    struct Node *q = p->next;

    while (q)
    {
        if (q->data != p->data)
        {
            p = q;
            q = q->next;
        }
        else 
        {
            p->next = q->next;
            free(q);
            q = p->next;
        }
    }
}

int main()
{
    int A[] = {3,5,5,8,8,8};
    create(A, 6);

    remove_duplicates(first);
    display(first);

    return 0;
}