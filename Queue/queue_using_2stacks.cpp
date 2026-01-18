#include <limits>
#include <stack>
#include <iostream>

using namespace std;

template <typename T>
class Queue
{
private:
    stack<T> s1;
    stack<T> s2;

public:
    Queue() {
    }

    bool isEmpty()
    {
        if(s1.empty() && s2.empty())
            return true;
        return false;
    }

    void enqueue(T data)
    {
        s1.push(data);
    }

    T dequeue()
    {
        T x = numeric_limits<T>::min();

        if(s2.empty()) {
            while(!s1.empty()) {
                s2.push(s1.top());
                s1.pop();
            }
        }

        if(!s2.empty()) {
            x = s2.top();
            s2.pop();
        }

        return x;
    }
};

int main()
{
    Queue<int> q;
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    q.enqueue(40);
    q.enqueue(50);

    cout << "Dequeue: " << q.dequeue() << endl;
    cout << "Dequeue: " << q.dequeue() << endl;

    return 0;
}
