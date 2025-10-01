#include <stdio.h>
#include <cstdlib>

struct Node
{
    int data;
    struct Node *next;
};

struct Stack
{
    struct Node *top = NULL;
};

bool isEmpty(struct Stack st)
{
    if(!st.top)
        return true;
    return false;
}

bool isFull()
{
    struct Node *t;
    t = (struct Node *) malloc(sizeof(struct Node));
    if(!t) {
        free(t);
        return true;
    }
    free(t);
    return false;
}

void push(struct Stack *st, int x)
{
    struct Node *t;
    t = (struct Node *) malloc(sizeof(struct Node));
    
    if(isFull())
        printf("Stack overflow\n");
    else
    {
        t->data = x;
        t->next = st->top;
        st->top = t;
    }
}

int pop(struct Stack *st)
{
    int x = -1;
    struct Node *t;

    if(isEmpty(*st))
        printf("Stack underflow\n");
    else
    {
        t = st->top;
        st->top = st->top->next;
        x = t->data;
        free(t);
    }

    return x;
}

void display(struct Stack st)
{
    struct Node *t = st.top;
    printf("[");
    while(t)
    {
        if(t->next)
            printf("%d, ", t->data);
        else
            printf("%d", t->data);

        t=t->next;
    }
    printf("]");
    printf("\n");
}

int peek(struct Stack st, int index)
{
    struct Node *t = st.top;
    int x = -1;

    for(int i=0; t && i<index; i++)
        t = t->next;

    if(t)
        x = t->data;

    return x;
}

int stackTop(struct Stack st)
{
    if(!isEmpty(st))
        return st.top->data;
    return -1;
}

int main()
{
    struct Stack st;

    push(&st, 10);
    push(&st, 20);
    push(&st, 30);
    push(&st, 40);
    push(&st, 50);

    printf("%d\n", peek(st, 2));

    display(st);

    return 0;
}