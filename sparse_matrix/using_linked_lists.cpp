#include <algorithm>
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

        for(int i=0; i<rows; i++)
            this->a[i] = NULL;
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

    void insert(int row, int column, int data)
    {
        if(row >= this->rows || column >= this->columns)
            return;

        Node *p = this->a[row], *newNode = new Node, *q;
        newNode->column = column;
        newNode->data = data;

        if(p == NULL)
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

    SparseMatrix add(SparseMatrix s2)
    {
        SparseMatrix s1 = *this;
        Node *p, *q;
        int rows = max(s1.rows, s2.rows), columns = max(s1.columns, s2.columns);
        int i=0, j=0;
        SparseMatrix addMatrix(rows, columns);

        while(i < s1.rows && i < s2.rows)
        {
            p = s1.a[i];
            q = s2.a[i];

            while(p && q)
            {
                if(p->column == q->column) {
                    addMatrix.insert(i, p->column, p->data + q->data);
                    p=p->next;
                    q=q->next;
                } else if(p->column < q->column) {
                    addMatrix.insert(i, p->column, p->data);
                    p=p->next;
                } else {
                    addMatrix.insert(i, q->column, q->data);
                    q=q->next;
                }
            }

            while(p) {
                addMatrix.insert(i, p->column, p->data);
                p=p->next;
            }

            while(q) {
                addMatrix.insert(i, q->column, q->data);
                q=q->next;
            }

            i++;
        }

        while(i < s1.rows) {
            p = s1.a[i];

            while(p) {
                addMatrix.insert(i, p->column, p->data);
                p=p->next;
            }

            i++;
        }

        while(i < s2.rows) {
            q = s2.a[i];
            
            while(q) {
                addMatrix.insert(i, q->column, q->data);
                q=q->next;
            }

            i++;
        }

        return addMatrix;
    }
};

int main()
{
    SparseMatrix s(4, 4);
    s.insert(0, 0, 1);
    s.insert(1, 1, 1);
    s.insert(2, 2, 1);
    s.insert(3, 3, 1);

    SparseMatrix s2(5, 5);
    s2.insert(0, 0, 1);
    s2.insert(1, 1, 1);
    s2.insert(2, 2, 1);
    s2.insert(3, 3, 1);
    s2.insert(4, 4, 1);
    

    SparseMatrix s3 = s.add(s2);
    s3.display();

    return 0;
}