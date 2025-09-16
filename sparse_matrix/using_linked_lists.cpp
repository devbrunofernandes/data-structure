#include <iostream>

using namespace std;

class Node
{
public:
    int column;
    int data;
    Node *next;
};

class SparseMatrix
{
private:
    int rows;
    int columns;
    Node **a;

public:
    SparseMatrix(int rows, int columns)
    {
        this->columns = columns;
        this->rows = rows;
        this->a = new Node*[rows];
    }

    void display()
    {
        Node *p;
        for(int i=0; i<this->rows; i++)
        {
            p = this->a[i];
            for(int j=0; j<this->columns; j++)
            {
                if(p && p->column == j)
                {
                    cout << p->data << ' ';
                    p =p->next;
                }
                else
                {
                    cout << '0' << ' ';
                }
            }
            cout << endl;
        }
    }

    void add(int row, int column, int data)
    {
        if(row > this->rows || column > this->columns)
            return;

        Node *p = this->a[row], *newNode = new Node, *q;
        newNode->column = column;
        newNode->data = data;

        if(!p)
        {
            this->a[row] = newNode;
            return;
        }

        if(column < p->column)
        {
            newNode->next = p;
            this->a[row] = newNode;
        }
        else
        {
            while(p && p->column < column)
            {
                q = p;
                p = p->next;
            }
                
            newNode->next = p;
            if(q)
                q->next = newNode;
        }
    }
};

int main()
{
    SparseMatrix s(4, 4);
    s.add(0, 0, 1);
    s.add(1, 1, 1);
    s.add(2, 2, 1);
    s.add(3, 3, 1);
    s.add(4, 4, 1);

    s.display();

    return 0;
}