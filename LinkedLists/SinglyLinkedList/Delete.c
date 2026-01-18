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

int deleteNode(int index)
{
    int x, counter = 1;
    struct Node *p = first, *q = NULL;

    if (first == NULL) return -1;
    if (index < 1) {index = 1;}

    if (index == 1)
    {
        first = first->next;

        x = p->data;
        free(p);
    }
    else 
    {
        while (p->next && counter < index)
        {
            q = p;
            p = p->next;
            counter++;
        }

        q->next = p->next;
        x = p->data;
        free(p);
    }

    return x;
}

int main()
{
    int A[] = {3,5,7,10,15,8,12,2};
    create(A, 8);
    printf("Linked list before deleting: ");
    display(first);

    deleteNode(2);
    printf("Linked list after deleting:  ");
    display(first);

    return 0;
}