#include <iostream>

using namespace std;

class Node
{
public:
    int data;
    Node *next;
    Node *prev;
};

class Deque
{
private:
    Node *front;
    Node *rear;

public:
    Deque()
    {
        front = nullptr;
        rear = nullptr;
    }

    ~Deque()
    {
        Node *t = front;
        while(t) {
            front = front->next;
            delete t;
            t = front;
        }
    }

    bool isEmpty()
    {
        if(front == nullptr)
            return true;
        return false;
    }

    void enqueueFront(int x)
    {
        Node *p = new Node();

        if(isEmpty()) {
            rear = p;
        } else {
            front->prev = p;
        }

        p->data = x;
        p->next = front;
        p->prev = nullptr;
        front = p;
    }

    void enqueueRear(int x)
    {
        if(isEmpty()) {
            enqueueFront(x);
        } else {
            Node *p = new Node();
            
            p->data = x;
            p->next = nullptr;
            p->prev = rear;

            rear->next = p;
            rear = p;
        }
    }

    int dequeueFront()
    {
        int x = -1;

        if(!isEmpty()) {
            if(front == rear) {
                x = front->data;
                delete front;
                front = rear = nullptr;
            } else {
                x = front->data;
                Node *t = front;
                front->next->prev = nullptr;
                front = front->next;
                delete t;
            }
        }

        return x;
    }

    int dequeueRear()
    {
        int x = -1;

        if(!isEmpty()) {
            if(front == rear) {
                x = rear->data;
                delete rear;
                front = rear = nullptr;
            } else {
                x = rear->data;
                Node *t = rear;
                rear->prev->next = nullptr;
                rear = rear->prev;
                delete t;
            }
        }

        return x;
    }

    void display()
    {
        Node *t = front;
        cout << "[";
        while(t) {
            if(t->next)
                cout << t->data << ", "; 
            else
                cout << t->data;
            t = t->next;
        }
        cout << "]" << endl;
    }
};

/*
    Doesn't follow FIFO
    Can insert and delete from both sides of the queue

    Deque has some variants. They can be Input restrict (don't insert from front) and output restrict (don't delete from rear).
*/
int main()
{
    Deque *d = new Deque();

    d->enqueueFront(10);
    d->enqueueFront(20);
    d->enqueueRear(30);
    d->enqueueFront(99);

    d->dequeueFront();
    d->dequeueRear();

    d->display();

    return 0;
}