#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <iostream>

// circular linked list
// the last node points to the first node
struct Node
{
    int data;
    struct Node *next;
}*head;
/* 
Other way to represent circular linked lists is use a first no data head node
In this way the program can distinguish a null default list from a null circular list
*/
void create(int A[], int n)
{
    struct Node *t, *last;
    head = (struct Node *) malloc(sizeof(struct Node));
    head->data=A[0];
    head->next=head;
    last = head;

    for (int i=1; i<n; i++)
    {
        t = (struct Node *) malloc(sizeof(struct Node));
        t->data = A[i];
        t->next = last->next;
        last->next = t;
        last = t;
    }
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

void display(struct Node *h)
{
    do {
        printf("%d ", h->data);
        h = h->next;
    }while (h != head);
    printf("\n");
}

void insert(struct Node *p, int index, int x)
{
    struct Node *t;

    if(index<0 || index > length(p))
        return;

    if(index==0)
    {
        t = (struct Node *) malloc(sizeof(struct Node));
        t->data = x;
        if(head == NULL)
        {
            head = t;
            head->next = head;
        }
        else
        {
            while(p->next!=head)
            {
                p=p->next;
            }

            p->next = t;
            t->next = head;
            head = t;
        }
    }
    else
    {
        for(int i=0; i<index-1; i++)
        {
            p=p->next;
        }
        t = (struct Node *) malloc(sizeof(struct Node));
        t->data = x;
        t->next = p->next;
        p->next = t;
    }
}

int main() 
{
    int A[] = {2,3,4,5,6};
    create(A, 5);

    insert(head, 5, 10);
    display(head);

    return 0;
}