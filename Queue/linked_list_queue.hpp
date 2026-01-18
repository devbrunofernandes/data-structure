#ifndef linked_list_queue
#define  linked_list_queue

#include <iostream>
#include <limits>

using namespace std;

template <typename T>
class Node
{
public:
    T data;
    Node *next;
};

template <typename T>
class Queue
{
private:
    Node<T> *front;
    Node<T> *rear;

public:
    Queue()
    {
        front = rear = nullptr;
    }

    ~Queue()
    {
        Node<T> *p = front;

        while(p) {
            front = front->next;
            delete p;
            p = front;
        }
    }

    bool isEmpty()
    {
        if(!front)
            return true;
        return false;
    }

    void enqueue(T x)
    {
        Node<T> *p = new Node<T>();
        p->next = nullptr;
        p->data = x;

        if (isEmpty()) {
            rear = front = p;
        } else {
            rear->next = p;
            rear = p;
        }
    }

    T dequeue()
    {
        T x = numeric_limits<T>::min();

        if(!isEmpty()) {
            x = front->data;

            if(front == rear) {
                delete front;
                front = rear = nullptr;
            } else {
                Node<T> *p = front;
                front = front->next;
                delete p;
            }
        }

        return x;
    }

    void display()
    {
        Node<T> *p = front;

        cout << "[";
        while(p) {
            p->next ? cout << p->data << ", " : cout << p->data;
            p = p->next;
        }
            
        cout << "]" << endl;
    }

    T first()
    {
        if(isEmpty())
            throw out_of_range("The queue is empty");

        return front->data;
    }

    T  last()
    {
        if(isEmpty())
            throw out_of_range("The queue is empty");

        return rear->data;
    }
};

#endif