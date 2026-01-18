#include <stdio.h>
#include <stdlib.h>

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

int erase(struct Node *p, int index)
{
    struct Node *q;
    int x;
    
    if(index < 1 || index > length(p))
        return -1;

    if(index==1)
    {
        while(p->next != head)
        {
            p = p->next;
        }

        x = head->data;
        if(head==p)
        {
            free(head);
            head = NULL;
        }
        else
        {
            p->next = head->next;
            free(head);
            head = p->next;
        }
    }
    else
    {
        for(int i=0; i < index-2; i++)
            p = p->next;

        q = p->next;
        p->next = q->next;
        x = q->data;
        free(q);
    }

    return x;
}

int main() 
{
    int A[] = {2,3,4,5,6};
    create(A, 5);

    erase(head, 5);
    display(head);

    return 0;
}