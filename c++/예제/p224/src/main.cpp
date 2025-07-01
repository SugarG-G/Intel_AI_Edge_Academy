#include "../include/circle.h"
#include <iostream>

using namespace std;

// void increase(Circle c)
// {
//     int r = c.getRadius();
//     c.setRadius(r + 1);
// }

// void increase(Circle *c)
// {
//     int r = (*c).getRadius();
//     (*c).setRadius(r + 1);
// }

void increase(Circle &c)
{
    int r = c.getRadius();
    c.setRadius(r + 1);
}

Circle getCircle()
{
    Circle tmp(30);
    return tmp;
}

void readRadius(Circle &c)
{
    int r = 0;
    cout << "정수의 값으로 반지름을 입력하세요>>";
    cin >> r;
    c.setRadius(r);
}

int main()
{
    // Circle waffle(30);
    // increase(waffle);
    // cout << waffle.getRadius() << endl;

    // Circle waffle(30);
    // increase(&waffle);
    // cout << waffle.getRadius() << endl;

    // Circle c;
    // cout << c.getArea() << endl;
    // c = getCircle();
    // cout << c.getArea() << endl;

    // Circle circle;
    // Circle &refc = circle;
    // refc.setRadius(10);
    // cout << refc.getArea() << " " << circle.getArea() << endl;

    // cout << &circle << endl << &refc << endl;

    // Circle donut;
    // readRadius(donut);
    // cout << "donut의 면적 = " << donut.getArea() << endl;

    // 예제 5-9
    Circle src(30);
    Circle dest(src);

    cout << "원본의 면적 = " << src.getArea() << endl;
    cout << "사본의 면적 = " << dest.getArea() << endl;
    return 0;
}