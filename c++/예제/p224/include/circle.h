#pragma once
#include <iostream>
using namespace std;

class Circle
{
private:
    int radius;

public:
    Circle(const Circle &c);
    Circle(int radius = 1);
    ~Circle();
    void setRadius(int r) { radius = r; }
    int getRadius() { return radius; }
    double getArea();
};