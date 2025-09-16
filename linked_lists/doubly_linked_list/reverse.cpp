#include <cstdlib>
#include <stdio.h>

struct Node
{
    struct Node *prev;
    int data;
    struct Node *next;
}*first=NULL;

void create(int A[], int n)
{
    struct Node *t, *last;

    first = (struct Node *) malloc(sizeof(struct Node));
    first->data = A[0];
    first->prev = NULL;
    first->next = NULL;
    last = first;

    for(int i=1; i<n; i++) 
    {
        t = (struct Node *) malloc(sizeof(struct Node));
        t->data = A[i];
        t->next = NULL;
        t->prev = last;
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

int length(struct Node *p)
{
    int len = 0;
    while(p)
    {
        len++;
        p = p->next;
    }
    return len;
}

void reverse(struct Node *p)
{
    struct Node *temp;

    while(p)
    {
        temp = p->next;
        p->next = p->prev;
        p->prev = temp;

        p = p->prev;
        if(p && p->next == NULL)
            first = p;
    }
}

int main()
{
    int A[] = {10,20,30,40,50};
    create(A, 5);

    reverse(first);

    printf("length is %d\n", length(first));
    display(first);

    return 0;
}