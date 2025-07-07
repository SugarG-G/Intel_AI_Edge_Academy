#include "../include/point.h"
#include <iostream>

void Point::set(int x, int y)
{
    this->x = x;
    this->y = y;
}

void Point::showPoint()
{
    std::cout << "(" << x << "," << y << ")" << std::endl;
}