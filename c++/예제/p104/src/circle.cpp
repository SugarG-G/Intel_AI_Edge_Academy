#include <iostream>

using namespace std;

class Circle
{
private:
    int radius;

public:
    Circle(int val); // 생성자
    // int radius;
    double getArea();
};

Circle::Circle(int val) // 생성자
{
    radius = val;
}

double Circle::getArea()
{
    return 3.14 * radius * radius;
}

int main()
{
    Circle donut(1);
    double area = donut.getArea();
    cout << "dount 면적은" << area << "\n";

    /*
    Circle donut;
    donut.radius = 1;
    double area = donut.getArea();
    cout << "dount 면적은" << area << "\n";

    Circle pizza;
    pizza.radius = 30;
    area = pizza.getArea();
    cout << "pizza 면적은" << area << "\n";
    */
}