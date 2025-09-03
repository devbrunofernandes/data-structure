#include <cstdint>
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

/* 
    LINKED LIST TRAVERSE
    while (p) or while (p != NULL)
    {
        p->next;
    }
    
    while p value is not null, that means that the list is not in the end and p will become the next node of the list.
*/

// FUNCTIONS TO DISPLAY ELEMENTS IN LINKED LIST
void display(struct Node *p)
{
    while(p)
    {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

void recursive_display(struct Node *p)
{
    if(p) 
    {
        printf("%d ", p->data);
        recursive_display(p->next);
    } else 
    {
        printf("\n");
    }
}

// FUNCTIONS TO COUNT THE NUMBER OF NODES
int count(struct Node *p)
{
    int c = 0;
    while(p)
    {
        c++;
        p = p->next;
    }
    return c;
}

int recursive_count(struct Node *p)
{
    if (p == NULL)
        return 0;
    return recursive_count(p->next) + 1;
}

// FUNCTIONS TO SUM ALL NODE DATA VALUES
int sum(struct Node *p)
{
    int s = 0;
    while(p)
    {
        s += p->data;
        p = p->next;
    }
    return s;
}

int recursive_sum(struct Node *p)
{
    if (p == NULL)
        return 0;
    return recursive_sum(p->next) + p->data;
}

// FUNCTIONS TO FIND THE GREATER ELEMENT IN THE LIST
int max(struct Node *p)
{
    int m = INT32_MIN;
    while(p)
    {
        if (p->data > m)
            m = p->data;
        p = p->next;
    }
    return m;
}

int recursive_max(struct Node *p)
{
    static int m = INT32_MIN;
    if (p == NULL)
        return m;

    if (p->data > m)
        m = p->data;
    return recursive_max(p->next);
}

// FUNCTIONS TO SEARCH SOME VALUE IN LINKED LIST
struct Node* search(struct Node *p, int key)
{
    while(p)
    {
        if (p->data == key)
            return p;
        p = p->next;
    }
    return NULL;
}

struct Node* recursive_search(struct Node *p, int key)
{
    if (p == NULL)
        return NULL;

    if (p->data == key)
        return p;
    return recursive_search(p->next, key);
}

// IMPROVING LINEAR SEARCH OPERATION
// MOVE TO HEAD - brings the found key value to the beginning of the list to be accessed earlier in another search for the same value.
struct Node* search_head(struct Node *p, int key)
{
    struct Node *q = NULL; // tail pointer -> will follow p pointer so we can access the node before p.
    while(p)
    {
        if (p->data == key)
        {
            q->next = p->next;
            p->next = first;
            first = p;
            return p;
        }

        q = p;
        p = p->next;
    }
    return NULL;
}

int main()
{
    int A[] = {3,5,7,10,15,8,12,2};
    create(A, 8);

    display(first);
    printf("list number of nodes: %d\n", recursive_count(first));
    printf("sum of node values: %d\n", sum(first));
    printf("maximum value in the list: %d\n\n", max(first));

    int key = 2;
    struct Node *temp = search_head(first, key);
    temp? printf("%d is in the list.\n", key):printf("%d is not in the list.\n", key);
    display(first);

    

    return 0;
}