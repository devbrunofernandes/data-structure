#include <cstdlib>
#include <stdio.h>

struct Queue
{
    int size;
    int front;
    int rear;
    int *q;
};

void create(struct Queue *q, int size)
{
    q->size = size;
    q->front = q->rear = -1;
    q->q = (int *) malloc(sizeof(int) * size);
}

bool isEmpty(struct Queue *q)
{
    if(q->rear == q->front)
        return true;
    return false;
}

bool isFull(struct Queue *q)
{
    if(q->rear == q->size-1)
        return true;
    return false;
}

void enqueue(struct Queue *q, int x)
{
    if(isFull(q))
        printf("Queue is full\n");
    else
    {
        q->q[++q->rear] = x;
    }
}

int dequeue(struct Queue *q)
{
    int x = -1;

    if(isEmpty(q))
        printf("Queue is empty");
    else
    {
        x = q->q[++q->front];
    }
    return x;
}

void display(struct Queue q)
{
    for(int i=q.front+1; i <= q.rear; i++)
        printf("%d ", q.q[i]);
    printf("\n");
}

int main()
{
    struct Queue q;
    create(&q, 5);

    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);
    enqueue(&q, 40);

    display(q);

    printf("dequeue: %d\n", dequeue(&q));

    return 0;
}