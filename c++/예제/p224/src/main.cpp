#include "../include/circle.h"
#include <iostream>

using namespace std;

void increase(Circle c)
{
    int r = c.getRadius();
    c.setRadius(r + 1);
}

Circle getCircle()
{
    Circle tmp(30);
    return tmp;
}

int main()
{
    // Circle waffle(30);
    // increase(waffle);
    // cout << waffle.getRadius() << endl;

    Circle c;
    cout << c.getArea() << endl;
    c = getCircle();
    cout << c.getArea() << endl;
}