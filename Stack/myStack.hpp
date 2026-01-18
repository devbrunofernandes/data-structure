#pragma once

#include <iostream>

using namespace std;

template <typename T>
class Node
{
public:
    T data;
    Node *next;
};

template <typename T>
class Stack
{
private:
    Node<T> *top;

public:
    Stack()
    {
        top = NULL;
    }

    void push(T x);
    T pop();
    void display();
    bool isEmpty();
    T peek(int index);
    T stackTop();
};

template <typename T>
void Stack<T>::push(T x)
{
    Node<T> *t = new Node<T>;
    if(t!=NULL)
    {
        t->data = x;
        t->next = top;
        top = t;
    }
}

template <typename T>
T Stack<T>::pop()
{
    T x = NULL;

    if(top!=NULL)
    {
        x = top->data;
        Node<T> *t = top;
        top = top->next;
        delete t;
    }

    return x;
}

template <typename T>
void Stack<T>::display()
{
    Node<T> *p = top;

    cout << '[';
    while(p)
    {
        if(p->next)
            cout << p->data << ", ";
        else
            cout << p->data;
        p = p->next;
    }
    cout << ']' << endl;
}

template <typename T>
bool Stack<T>::isEmpty()
{
    if(!top)
        return true;
    return false;
}

template <typename T>
T Stack<T>::peek(int index)
{
    Node<T> *t = top;

    for(int i=0; t && i<index; i++)
        t = t->next;

    if(t) {
        return t->data;
    }
        
    return NULL;
}

template <typename T>
T Stack<T>::stackTop()
{
    if(!isEmpty())
        return top->data;
    return NULL;
}