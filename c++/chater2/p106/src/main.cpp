#include <iostream>

using namespace std;

class Rectangle
{
private:
    int width;
    int height;

public:
    Rectangle();
    Rectangle(int w, int h);
    void setter(int w, int h);
    int getArea();
};

/*
Rectangle::Rectangle()// 디폴트 생성자
{
    width = 0;
    height = 0;
}
*/
/*
Rectangle::Rectangle() : Rectangle(0, 0) // 위임 생성자
{
}
*/
/*
Rectangle::Rectangle() : width(0), height(0) // 생성자 서두에 초깃값으로 초기화
{
}
*/

Rectangle::Rectangle(int w, int h)
{
    width = w;
    height = h;
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

int main(int, char**)
{
    Rectangle rect;
    Rectangle rect(3, 5);
    int width = 0;
    int height = 0;
    // Rectangle rect();
    // rect.width = 3;
    // rect.height = 5;
    cout << "사각형의 폭과 높이를 입력하세요 >>" << endl;
    cin >> width >> height;
    rect.setter(width, height);
    cout << "사각형의 면적은" << rect.getArea() << endl;
}
