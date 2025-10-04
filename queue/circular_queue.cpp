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
    q->front = q->rear = 0;
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
    if((q->rear + 1) % q->size == q->front)
        return true;
    return false;
}

void enqueue(struct Queue *q, int x)
{
    if(isFull(q))
        printf("Queue is full\n");
    else
    {
        q->rear = (q->rear + 1) % q->size;
        q->q[q->rear] = x;
    }
}

int dequeue(struct Queue *q)
{
    int x = -1;

    if(isEmpty(q))
        printf("Queue is empty");
    else
    {
        q->front = (q->front + 1) % q->size;
        x = q->q[q->front];
    }
    return x;
}

void display(struct Queue q)
{
    int i = q.front + 1;
    do {
        printf("%d ", q.q[i]);
        i = (i + 1) % q.size;
    } while(i != (q.rear + 1) % q.size);

    printf("\n");
}

/*
    Circular queue is the best way to implement queue using array
    It prevents the waste of spacing caused by two pointers method
    The total numbers of elements that can be inserted into the circular queue is equal to the size of array - 1
 */
int main()
{
    struct Queue q;
    create(&q, 5);

    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);
    enqueue(&q, 40);
    enqueue(&q, 50);

    display(q);

    printf("dequeue: %d\n", dequeue(&q));

    return 0;
}