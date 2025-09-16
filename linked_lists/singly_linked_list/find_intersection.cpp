#include <algorithm>
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

struct Node* find_intersection(struct Node *p, struct Node *q)
{
    struct Node *stack1[100], *stack2[100], *intersec_point;
    int i=0, j=0;

    while(p)
    {
        stack1[i] = p;
        i++;
        p=p->next;
    }

    while(q)
    {
        stack2[j] = q;
        j++;
        q=q->next;
    }

    while(stack1[i] == stack2[j])
    {
        intersec_point = stack1[i];
        i--;
        j--;
    }

    return intersec_point;
}

int main()
{
    int A[] = {1,2,3,4,5};
    int B[] = {6,7,8,9,10};
    struct Node *first = create(A, 5), *second = create(B, 5);
    
    second->next->next = first->next->next->next;
    struct Node *m = find_intersection(first, second);

    printf("intersection node data: %d\n", m->data);

    return 0;
}