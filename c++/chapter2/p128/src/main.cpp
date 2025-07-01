#include <iostream>

using namespace std;

class Circle
{
private:
    int radius;

public:
    Circle();
    Circle(int r);
    double getArea();
    int getRadius();
    void setRadius(int);
};

Circle::Circle()
{
    radius = 1;
}
Circle::Circle(int r)
{
    radius = r;
}
int Circle::getRadius()
{
    return radius;
}

void Circle::setRadius(int r)
{
    radius = r;
}

int main()
{
    Circle waffle(5);
    cout << waffle.getRadius() << endl;
    // waffle.radius = 5;
    // cout << waffle.radius << endl;
    waffle.setRadius(10);
    cout << waffle.getRadius() << endl;
    return 0;
}