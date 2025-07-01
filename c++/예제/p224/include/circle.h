#pragma once
#include <iostream>
using namespace std;

class Circle
{
private:
    int radius;

public:
    Circle();
    Circle(const Circle &c);
    Circle(int r);
    ~Circle();
    void setRadius(int r) { radius = r; }
    int getRadius() { return radius; }
    double getArea();
};