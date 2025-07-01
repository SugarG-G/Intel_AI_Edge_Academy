#include "circle.h"
#include <iostream>

using namespace std;

int main()
{
    // Circle circleArray[3];
    Circle circleArray[3] = {Circle(10), Circle(20), Circle(30)};
    int num[3] = {10, 20, 30};
    // for (int i = 0; i < 3; i++)
    // {
    //     circleArray[i].setRadius(num[i]);
    // }
    // circleArray[0].setRadius(10);
    // circleArray[1].setRadius(20);
    // circleArray[2].setRadius(30);

    for (int i = 0; i < 3; i++)
    {
        cout << "Circle " << i << "의 면적은 " << circleArray[i].getArea() << endl;
    }

    Circle *p;
    p = circleArray;
    for (int i = 0; i < 3; i++)
    {
        cout << "Circle " << i << "의 면적은 " << p->getArea() << endl;
        p++;
    }

    return 0;
}