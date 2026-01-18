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

// append one linked list into the end of another list
struct Node *append(struct Node *first, struct Node *second)
{
    struct Node *n = first;

    while (first->next)
        first = first->next;

    first->next = second;

    return n;
}

// merge two sorted lists into a new sorted list with values of the others
struct Node *merge(struct Node *first, struct Node *second)
{
    struct Node *third, *last, *new_pointer;

    if (first->data < second->data) 
    {
        third = last = first;
        first = first->next;
        last->next = NULL;
    } 
    else 
    {
        third = last = second;
        second = second->next;
        last->next = NULL;
    }

    while (first && second)
    {
        if (first->data < second->data) 
        {
            last->next = first;
            last = first;
            first = first->next;
            last->next = NULL;
        }
        else 
        {
            last->next = second;
            last = second;
            second = second->next;
            last->next = NULL;
        }
    }

    if (first)
        last->next = first;
    else
        last->next = second;

    return third;
}

int main()
{
    int A[] = {1,2,3,4,5};
    int B[] = {6,7,8,9,10};
    struct Node *first = create(A, 5), *second = create(B, 5);

    // struct Node *appended = append(first, second);

    // printf("Appended lists: ");
    // display(appended);

    struct Node *m = merge(first, second);

    printf("Merged lists:   ");
    display(m);

    return 0;
}