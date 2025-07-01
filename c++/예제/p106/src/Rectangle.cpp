#include "rectangle.h"
#include <iostream>

using namespace std;
/*
Rectangle::Rectangle() // 디폴트 생성자
{
}
*/
Rectangle::~Rectangle()
{
    cout << "소멸자" << width << " " << height << endl;
}
/*
Rectangle::Rectangle() : Rectangle(0, 0) // 위임 생성자
{
}
*/

Rectangle::Rectangle() : width(0), height(0) // 생성자 서두에 초깃값으로 초기화
{
    cout << "생성자()" << width << " " << height << endl;
}

Rectangle::Rectangle(int w, int h)
{
    width = w;
    height = h;
    cout << "생성자(int int)" << width << " " << height << endl;
}

void Rectangle::setter(int w, int h)
{
    width = w;
    height = h;
}

int Rectangle::getArea()
{
    return width * height;
}