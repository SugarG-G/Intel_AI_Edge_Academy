#include "circle.h"
#include <cstring>
#include <iostream>

using namespace std;

int main()
{
    Circle *p, *q;
    p = new Circle;
    q = new Circle(30);
    cout << p->getArea() << endl << q->getArea() << endl;

    int *pArray = new int[10];

    memset(pArray, 0, sizeof(int) * 10);
    for (int i = 0; i < 10; i++)
    {
        cout << pArray[i] << endl;
    }
    delete p;
    delete q;
    delete[] pArray;
    return 0;
}