#include "circle.h"
#include <iostream>

using namespace std;

int main()
{
    Circle donut;
    Circle pizza(30);

    cout << donut.getArea() << endl;

    Circle *p;
    p = &donut;
    cout << "donut의 주소" << &donut << endl;
    cout << "p의 포인터 " << p << endl;
    cout << p->getArea() << endl; // cout << (*p).getArea() << endl;

    p = &pizza;
    cout << p << endl;
    cout << p->getArea() << endl;
    return 0;
}