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

void display(struct Node *h)
{
    do {
        printf("%d ", h->data);
        h = h->next;
    }while (h != head);
    printf("\n");
}

void recursive_display(struct Node *h)
{
    static int flag = 0;
    
    if(h != head || flag == 0) {
        flag = 1;
        printf("%d ", h->data);
        recursive_display(h->next);
    }

    flag = 0;
}

int main() 
{
    int A[] = {2,3,4,5,6};
    create(A, 5);

    display(head);
    recursive_display(head);

    return 0;
}