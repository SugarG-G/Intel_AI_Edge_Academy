#include <iostream>
#include <string>

using namespace std;

class Point
{
protected: // 상속 관계에서는 접근가능
    int x, y;

public:
    void set(int x, int y)
    {
        this->x = x;
        this->y = y;
    }
    void showPoint() { cout << "(" << x << "," << y << ")" << endl; }
};

class ColorPoint : public Point
{
private:
    string color;

public:
    void setColor(string color) { this->color = color; }
    void showColorPoint();
    void showPoint(); // 재정의
};

void ColorPoint::showColorPoint()
{
    cout << color << ":";
    showPoint();
}

void ColorPoint::showPoint() // 재정의
{
    cout << "재정의 " << "(" << x << "," << y << ")" << endl;
}

int main()
{
    // Point p;
    // ColorPoint cp;
    // cp.set(3, 4);
    // cp.setColor("Red");
    // cp.showColorPoint();

    // 업 캐스팅 예제
    ColorPoint cp;
    ColorPoint *pDer = &cp;

    Point *pBase = pDer; // <- 업캐스팅, Point *pBase = (Point *)pDer;
    pBase->set(3, 4);
    pBase->showPoint();

    // Point &pRef = cp;
    // pRef.set(6, 7);
    // pRef.showPoint();

    pDer = (ColorPoint *)pBase; // 다운 캐스팅
    pDer->setColor("Red");
    pDer->showColorPoint();
}