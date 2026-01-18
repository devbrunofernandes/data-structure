#include <iostream>

using namespace std;

class Queue
{
private:
    int front;
    int rear;
    int size;
    int *q;

public:
    Queue()
    {
        front = rear = -1;
        size = 10;
        q = new int[size];
    }

    Queue(int size)
    {
        front = rear = -1;
        this->size = size;
        q = new int[size];
    }

    bool isFull();
    bool isEmpty();
    void enqueue(int x);
    int dequeue();
    void display();
};

bool Queue::isFull()
{
    if(rear == size-1)
        return true;
    return false;
}

bool Queue::isEmpty()
{
    if(rear == front)
        return true;
    return false;
}

void Queue::enqueue(int x)
{
    if (isFull())
        cout << "Queue is full" << endl;
    else
        q[++rear] = x;
}

int Queue::dequeue()
{
    int x = -1;

    if(isEmpty())
        cout << "Queue is empty" << endl;
    else
        x = q[++front];

    return x;
}

void Queue::display()
{
    cout << "[";
    for(int i=front+1; i <= rear; i++)
        i == rear ? cout << q[i] : cout << q[i] << ", ";
        
    cout << "]" << endl;
}

int main()
{
    Queue q(5);

    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    q.enqueue(40);
    q.enqueue(50);

    q.display();

    q.dequeue();

    q.display();

    return 0;
}