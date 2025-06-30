#include "rectangle.h"
#include <iostream>

using namespace std;

int main(int, char**)
{
    Rectangle rect1;
    Rectangle rect2(3, 5);
    int width = 0;
    int height = 0;
    // Rectangle rect();
    // rect.width = 3;
    // rect.height = 5;
    cout << "사각형의 면적은 " << rect2.getArea() << endl;
    cout << "사각형의 폭과 높이를 입력하세요 >>" << endl;
    cin >> width >> height;
    rect1.setter(width, height);
    cout << "사각형의 면적은 " << rect1.getArea() << endl;

    return 0;
}
