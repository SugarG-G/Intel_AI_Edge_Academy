#include "../include/circle.h"
#include <iostream>

using namespace std;

Circle::Circle()
{
    radius = 1;
    cout << "생성자 실행 radius = " << radius << endl;
}
Circle::Circle(const Circle &c)
{
    this->radius = c.radius;
    cout << "복사 생선자 실행 radius = " << radius << endl;
}
Circle::Circle(int radius)
{
    this->radius = radius;
    cout << "생성자 실행 radius = " << radius << endl;
}
Circle::~Circle()
{
    cout << "소멸자 실행 radus = " << radius << endl;
}
double Circle::getArea()
{
    return 3.14 * radius * radius;
}