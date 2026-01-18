#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

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

void reverseElements(struct Node *p, const int size)
{
    int i = 0, aux[size];
    struct Node *q = p;

    while (q) 
    {
        aux[i++] = q->data;
        q = q->next;
    }

    while (p)
    {
        p->data = aux[--i];
        p = p->next;
    }
}

void reverseLinks(struct Node *p)
{
    struct Node *q = NULL, *r = NULL;

    while (p)
    {
        // Sliding pointers algorithm
        r = q;
        q = p;
        p = p->next;
        // ===========================
        q->next = r;
    }
    first = q;
}

void reverseRecursive(struct Node *q, struct Node *p)
{
    if (p)
    {
        reverseRecursive(p, p->next);
        p->next = q;
    }
    else
    {
        first = q;
    }
}

int main()
{
    int A[] = {2,4,6,8,10,12,14,16,18,20};
    create(A, 10);

    reverseRecursive(NULL, first);
    display(first);

    return 0;
}