#include <stdio.h>
#include <cstdlib>

struct Stack
{
    int size;
    int top;
    int *s;
};

void create(struct Stack *st)
{
    printf("Enter size:");
    scanf("%d", &st->size);
    st->top = -1;
    st->s = (int *) malloc(st->size * sizeof(int));
}

bool isEmpty(struct Stack st)
{
    if(st.top == -1)
        return true;
    return false;
}

bool isFull(struct Stack st)
{
    return st.top == st.size-1;
}

void push(struct Stack *st, int x)
{
    if(isFull(*st))
        printf("Stack overflow\n");
    else
    {
        st->top++;
        st->s[st->top] = x;
    }
}

int pop(struct Stack *st)
{
    int x = -1;

    if(isEmpty(*st))
        printf("Stack underflow\n");
    else
    {
        x = st->s[st->top--];
    }

    return x;
}

void display(struct Stack st)
{
    printf("[");
    for(int i=st.top; i >= 0; i--)
    {
        if(i != 0)
            printf("%d, ", st.s[i]);
        else
            printf("%d", st.s[i]);
    }
    printf("]");
    printf("\n");
}

int peek(struct Stack st, int index)
{
    int x = -1;
    if(st.top-index+1 < 0)
        printf("Invalid index");
    else
        x = st.s[st.top-index+1];

    return x;
}

int stackTop(struct Stack st)
{
    if(!isEmpty(st))
        return st.s[st.top];
    return -1;
}

int main()
{
    struct Stack st;
    create(&st);

    push(&st, 10);
    push(&st, 20);
    push(&st, 30);
    push(&st, 40);
    push(&st, 50);

    printf("%d\n", peek(st, 2));

    display(st);

    return 0;
}