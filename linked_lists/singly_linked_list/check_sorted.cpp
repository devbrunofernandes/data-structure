#include <cstdint>
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

void display(struct Node *p)
{
    while(p)
    {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

bool is_sorted(struct Node *p)
{
    int x = INT32_MIN;

    while (p)
    {
        if (p->data < x)
            return false;

        x = p->data;
        p = p->next;
    }

    return true;
}

int main()
{
    int A[] = {2,4,6,8,10,2};
    create(A, 6);
    display(first);

    is_sorted(first)? printf("The list is sorted\n"):printf("The list is not sorted\n");

    return 0;
}