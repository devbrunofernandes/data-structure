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

void insert(struct Node *p, int index, int data)
{
    if (index < 0)
        index = 0;
    
    int counter = 1;
    struct Node *t = (struct Node *) malloc(sizeof(struct Node));
    t->data = data;
    t->next = NULL;

    if (first == NULL)
    {
        first = t;
        return;
    }

    if (index == 0)
    {
        t->next = p;
        p = t;
    }
    else 
    {
        while (counter < index && p->next)
        {
            p = p->next;
            counter++;
        }

        t->next = p->next;
        p->next = t;
    }
}

/*  APPEND FUNCTION - LAST GLOBAL VARIABLE MUST BE USED FOR CONSTANT TIME
    void append(struct Node *p, int data)
    {
        struct Node *t = (struct Node *) malloc(sizeof(struct Node));
        t->data = data;
        t->next = NULL;

        if (!first)
            first = last = t;
        else
        {
            last->next = t;
            last = t;
        }
    }
*/


void insert_sorted(struct Node *p, int data)
{
    struct Node *q = NULL, *t = (struct Node *) malloc(sizeof(struct Node));
    t->data = data;
    t->next = NULL;

    if (first == NULL)
    {
        first = t;
    }
    else 
    {
        while (p && p->data < data) 
        {
            q = p;
            p = p->next;
        }

        if (p == first) 
        {
            t->next = first;
            first = t;
        } 
        else 
        {
            t->next = q->next;
            q->next = t;  
        }
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

int main()
{
    int A[] = {3,5,7,10,15,8,12,2};
    create(A, 8);
    printf("Linked list before inserting: ");
    display(first);

    insert(first, 4, 33);
    printf("Linked list after inserting 33 at position 4:  ");
    display(first);

    int sorted[] = {2,4,6,8,10,12,14,16,18,20};
    create(sorted, 10);
    printf("Sorted linked list: ");
    display(first);

    insert_sorted(first, 5);
    printf("Sorted linked list after insert(5): ");
    display(first);

    return 0;
}