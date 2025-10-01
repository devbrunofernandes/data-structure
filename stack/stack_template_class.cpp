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
};

template <typename T>
void Stack<T>::push(T x)
{
    Node<T> *t = new Node<T>;
    if(t==NULL)
        cout << "Stack is full ";
    else
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

    if(top==NULL)
        cout << "Stack is empty ";
    else
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


int main()
{
    Stack<char> stk;
    stk.push('a');
    stk.push('b');
    stk.push('c');

    stk.display();
    cout << "Popping out -> " << stk.pop() << endl;
    stk.display();
    cout << "Popping out -> " << stk.pop() << endl;
    stk.display();
    cout << "Popping out -> " << stk.pop() << endl;
    stk.display();
    cout << "Popping out -> " << stk.pop() << endl;
    stk.display();

    return 0;
}