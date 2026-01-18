#include <cstdlib>
#include <stdio.h>

struct Node
{
    int data;
    struct Node *next;
}*front = NULL, *rear = NULL;

bool isFull()
{
    struct Node *t;
    t = (struct Node *) malloc(sizeof(struct Node));
    if(t == NULL)
        return true;

    return false;
}

bool isEmpty()
{
    if(front == NULL)
        return true;
    return false;
}

void enqueue(int x)
{
    if(isFull())
        printf("Queue is full\n");
    else
    {
        struct Node *t = (struct Node *) malloc(sizeof(struct Node));
        t->data = x;
        t->next = NULL;
        if(isEmpty())
            front = rear = t;
        else
        {
            rear->next = t;
            rear = t;
        }
    }
}

int dequeue()
{
    int x = -1;
    struct Node *t;

    if(isEmpty())
        printf("Queue is empty\n");
    else
    {
        x = front->data;
        t = front;
        front = front->next;
        free(t);
    }

    return x;
}

void display()
{
    struct Node *p = front;
    while(p)
    {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

int main()
{
    enqueue(10);
    enqueue(20);
    enqueue(30);
    enqueue(40);
    enqueue(50);

    display();

    printf("Dequeued value: %d\n", dequeue());

    return 0;
}