#include <iostream>
#include <limits>
#include <stdexcept>
#include "linked_list_queue.hpp"
 
template <typename T>
class PriorityQueue
{
private:
    Queue<T> **q;
    int maxPriority;

public:
    PriorityQueue<T>()
    {
        maxPriority = 10;
        q = new Queue<T>*[maxPriority];

        for(int i=0; i<maxPriority; i++)
            q[i] = nullptr;
    }

    PriorityQueue<T>(int priority)
    {
        maxPriority = priority;
        q = new Queue<T>*[maxPriority];

        for(int i=0; i<maxPriority; i++)
            q[i] = nullptr;
    }

    ~PriorityQueue<T>()
    {
        for(int i=0; i<maxPriority; i++) {
            if(q[i]) delete q[i];
        }

        delete []q;
    }

    void enqueue(T data, int priority)
    {
        if(priority < 1 || priority > maxPriority)
            throw out_of_range("priority out of range");

        if(!q[priority - 1])
            q[priority - 1] = new Queue<T>();
        q[priority - 1]->enqueue(data);
    }

    T dequeue()
    {
        T x = numeric_limits<T>::min();

        for(int i=0; i<maxPriority; i++) {
            if(!q[i]->isEmpty()) {
                x = q[i]->dequeue();
                break;
            }
        }

        return x;
    }

    bool isEmpty()
    {
        for(int i=0; i<maxPriority; i++) {
            if(q[i]) {return false;}   
        }

        return true;
    }
};

int main()
{
    PriorityQueue<char> *pq = new PriorityQueue<char>(3);

    pq->enqueue('a', 2);
    pq->enqueue('b', 1);
    pq->enqueue('c', 3);
    pq->enqueue('d', 1);

    cout << "Ordem de saida: ";
    for(int i=0; i<4; i++)
        cout << pq->dequeue() << " ";
    cout << endl;

    return 0;
}