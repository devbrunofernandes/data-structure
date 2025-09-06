#include <iostream>

using namespace std;

class Node
{
public:
    int data;
    Node *next;    
};

class LinkedList
{
private:
    Node *first;
    Node *last;
public:
    LinkedList()
    {
        first = NULL;
    }

    LinkedList(int A[], int n);
    ~LinkedList();
    void display();
    void insert(int index, int x);
    int remove(int index);
    int length();
};

LinkedList::LinkedList(int A[], int n)
{
    Node *t;
    int i=0;

    first = new Node;
    first->data = A[0];
    first->next=NULL;
    last=first;

    for(i=1;i<n;i++)
    {
        t = new Node;
        t->data = A[i];
        t->next = NULL;
        last->next=t;
        last=t;
    }
}

LinkedList::~LinkedList()
{
    Node *p=first;
    while (first)
    {
        first = first->next;
        delete p;
        p = first;
    }
}

void LinkedList::display()
{
    Node *p = first;

    while (p)
    {
        cout<<p->data<<" ";
        p=p->next;
    }
    cout<<endl;
}

int LinkedList::length()
{
    Node *p = first;
    int len = 0;

    while (p)
    {
        len++;
        p = p->next;
    }

    return len;
}

void LinkedList::insert(int index, int x)
{
    Node *t, *p = first;

    if (index < 0 || index > length())
        return;

    t = new Node;
    t->data = x;
    t->next = NULL;

    if (index==0)
    {
        first = t;
        t->next = p;
    }
    else 
    {
        for (int i=0; i < index-1; i++)
            p = p->next;

        t->next=p->next;
        p->next=t;
    }
}

int LinkedList::remove(int index)
{
    Node *p, *q=NULL;
    int x=-1;

    if (index < 1 || index > length())
        return -1;

    if (index==1)
    {
        p=first;
        first=first->next;
        x=p->data;
        delete p;
    }
    else 
    {
        p = first;
        for (int i=0; i < index-1; i++)
        {
            q=p;
            p=p->next;
        }
        q->next=p->next;
        x = p->data;
        delete p;
    }

    return x;
}

int main()
{
    int A[] = {1,2,3,4,5};
    LinkedList l(A, 5);

    l.insert(5, 6);
    cout << "Removed: " << l.remove(6) << endl;
    cout << "Length: " << l.length() << endl;
    l.display();

    return 0;
}