#ifndef array_queue
#define  array_queue

#include <iostream>

using namespace std;

template <typename T>
class Queue
{
private:
    int front;
    int rear;
    int size;
    T *q;

public:
    Queue()
    {
        front = rear = -1;
        size = 10;
        q = new T[size];
    }

    Queue(int size)
    {
        front = rear = -1;
        this->size = size;
        q = new T[size];
    }

    ~Queue()
    {
        delete q;
    }

    bool isFull()
    {
        if(rear == size-1)
            return true;
        return false;
    }

    bool isEmpty()
    {
        if(rear == front) {
            rear = front = -1; // reseting pointers to save space
            return true;
        } else {
            return false;
        }
        
    }

    void enqueue(T x)
    {
        if (isFull())
            cout << "Queue is full" << endl;
        else
            q[++rear] = x;
    }

    T dequeue()
    {
        T x = NULL;

        if(isEmpty())
            cout << "Queue is empty" << endl;
        else
            x = q[++front];

        return x;
    }

    void display()
    {
        cout << "[";
        for(int i=front+1; i <= rear; i++)
            i == rear ? cout << q[i] : cout << q[i] << ", ";
            
        cout << "]" << endl;
    }

    T first()
    {
        if(isEmpty())
            throw out_of_range("The queue is empty");

        return q[front+1];
    }

    T  last()
    {
        if(isEmpty())
            throw out_of_range("The queue is empty");

        return q[rear];
    }
};

#endif