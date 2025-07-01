#include "circle.h"
#include <iostream>

using namespace std;

void increase(Circle c)
{
    int r = c.getRadius();
    c.setRadius(r + 1);
}

int main()
{
    Circle waffle(30);
    increase(waffle);
    cout << waffle.getRadius() << endl;
}