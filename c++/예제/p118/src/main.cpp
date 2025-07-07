#include <iostream>

using namespace std;

class Rectangle
{
private:
    int w;
    int h;

public:
    Rectangle();
    Rectangle(int x, int y);
    Rectangle(int x);
    bool isSquare();
};

Rectangle::Rectangle()
{
    w = 0;
    h = 0;
}

Rectangle::Rectangle(int x, int y)
{
    w = x;
    h = y;
}

Rectangle::Rectangle(int x)
{
    w = x;
    h = x;
}

bool Rectangle::isSquare()
{
    if (w == h)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int main()
{
    Rectangle rect1;
    Rectangle rect2(3, 5);
    Rectangle rect3(3);

    if (rect1.isSquare())
    {
        cout << "rect1은 정사각형이다." << endl;
    }
    if (rect2.isSquare())
    {
        cout << "rect2은 정사각형이다." << endl;
    }
    if (rect3.isSquare())
    {
        cout << "rect3은 정사각형이다." << endl;
    }
}