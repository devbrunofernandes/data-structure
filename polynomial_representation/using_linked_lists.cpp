#include <cmath>
#include <iostream>

using namespace std;

class Node
{
public:
    int coeff;
    int exp;
    Node *next;
};

class Polynomial
{
public:
    Node *poly = NULL;

    Polynomial()
    {
        Node *t, *last;
        int num;

        cout << "Number of terms: ";
        cin >> num;

        cout << "Enter each term coeff and exp" << endl;
        for(int i=0; i<num; i++)
        {
            t = new Node;
            cin >> t->coeff >> t->exp;
            t->next = NULL;
            
            if(!poly)
            {
                poly = t;
                last = t;
            }
            else
            {
                last->next = t;
                last = t;
            }
        }
    }

    void display()
    {
        Node *p = poly;
        while(p)
        {
            if(p->next)
                cout << p->coeff << "X" << "^" << p->exp << " + ";
            else
                cout << p->coeff << "X" << "^" << p->exp;
            p=p->next;
        }
        cout << endl;
    }

    long evaluate(int x)
    {
        Node *p = poly;
        long val = 0;

        while(p)
        {
            val += p->coeff * pow(x, p->exp);
            p = p->next;
        }

        return val;
    }
};

int main()
{
    Polynomial p1;
    p1.display();
    cout << p1.evaluate(2) << endl;

    return 0;
}