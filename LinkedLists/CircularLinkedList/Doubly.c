#include <stdlib.h>
#include <stdio.h>

struct Node
{
    struct Node *prev;
    int data;
    struct Node *next;
}*head=NULL;

void create(int A[], int n)
{
    struct Node *t, *last;

    head = (struct Node *) malloc(sizeof(struct Node));
    head->data=A[0];
    head->next=head;
    head->prev=head;
    last = head;

    for (int i=1; i<n; i++)
    {
        t = (struct Node *) malloc(sizeof(struct Node));
        t->data = A[i];
        t->next = last->next;
        t->prev = last;

        head->prev = t;
        last->next = t;
        last = t;
    }
}

void display(struct Node *h)
{
    do {
        printf("%d ", h->data);
        h = h->next;
    }while (h != head);
    printf("\n");
}

int length(struct Node *p)
{
    int count = 0;
    if(!p)
        return 0;

    do
    {
        count++;
        p = p->next;
    } while(p != head);

    return count;
}

void insert(struct Node *p, int index, int x)
{
    struct Node *t;

    if(index<0 || index>length(p))
        return;

    t = (struct Node *) malloc(sizeof(struct Node));
    t->data = x;

    if(index==0)
    {
        if(head)
        {
            t->next = head;
            t->prev = head->prev;

            head->prev->next = t;
            head->prev = t;
        }
        else
        {
            t->prev = t;
            t->next = t;
        } 
        head = t;
    }
    else
    {
        for(int i=0; i<index-1; i++)
            p=p->next;

        t->next = p->next;
        t->prev = p;
        if(p->next)
            p->next->prev = t;
        p->next = t;
    }
}

int erase(struct Node *p, int index)
{
    int x = -1;

    if(index<1 || index>length(p))
        return x;

    if(index==1)
    {
        head->prev->next = head->next;
        head->next->prev = head->prev;
        head=head->next;

        x = p->data;
        free(p);
    }
    else
    {
        for(int i=0; i<index-1; i++)
            p=p->next;

        p->prev->next = p->next;
        p->next->prev = p->prev;
        free(p);
    }

    return x;
}

int main()
{
    int A[] = {10,20,30,40,50};
    create(A, 5);

    insert(head, 2, 25);
    erase(head, 4);
    insert(head, 0, 5);

    display(head);
        
    return 0;
}