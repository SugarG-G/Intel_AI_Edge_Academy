#include <iostream>
#include <string>
using namespace std;

#define apply

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
    virtual void drivedShow()
    {
        cout << "drivedShow" << endl;
        showPoint();
    }
};

class ColorPoint : public Point
{
private:
    string color;

public:
    void setColor(string color) { this->color = color; }
    virtual void drivedShow();
    // void showPoint(); // 재정의
};

void ColorPoint::drivedShow()
{
    cout << color << ":";
    showPoint();
}

// void ColorPoint::showPoint() // 재정의
// {
//     cout << "재정의 " << "(" << x << "," << y << ")" << endl;
// }
#ifdef apply
// 응용 //
class LinePoint : public Point
{
private:
    string line;

public:
    void setLine(string line) { this->line = line; }
    virtual void drivedShow();
    // void showPoint(); // 재정의
};

void LinePoint::drivedShow()
{
    cout << line << ":";
    showPoint();
}

// void LinePoint::showPoint() // 재정의
// {
//     cout << "재정의 " << "(" << x << "," << y << ")" << endl;
// }
// 응용 end //
#endif
#ifdef apply
// 응용 //
void testshow(Point *p)
{
    cout << "----------testshow---------" << endl;
    // p->set(7, 9);
    // p->showPoint();
    // cout << typeid(ColorPoint).name() << endl;
    // cout << typeid(*p).name() << endl;

    // if (typeid(*p) == typeid(ColorPoint))
    // {
    //     ColorPoint *pDer = (ColorPoint *)p;
    //     cout << "pDer->showColorPoint()" << endl;
    //     pDer->showColorPoint();
    // }
    // else if (typeid(*p) == typeid(LinePoint))
    // {
    //     LinePoint *pLin = (LinePoint *)p;
    //     cout << "LinePoint *pLin = (LinePoint *)p" << endl;
    //     pLin->showLinePoint();
    // }
    p->drivedShow();
    cout << "----------testshow---------" << endl;
}
// 응용 end //
#endif
int main()
{
    // Point p;
    // ColorPoint cp;
    // cp.set(3, 4);
    // cp.setColor("Red");
    // cp.showColorPoint();

    // 업 캐스팅 예제
    // ColorPoint cp;
    // ColorPoint *pDer = &cp;

    // Point *pBase = pDer; // <- 업캐스팅, Point *pBase = (Point *)pDer;
    // pBase->set(3, 4);
    // pBase->showPoint();

    // // 다운 캐스팅 예제
    // pDer = (ColorPoint *)pBase; // 다운 캐스팅
    // pDer->setColor("Red");
    // pDer->showColorPoint();
#ifdef apply
    // 응용 //
    ColorPoint cp;
    ColorPoint *pDer = &cp;
    pDer->set(3, 4);
    pDer->setColor("red");
    pDer->drivedShow();

    testshow(pDer);

    cout << "---------------------------------" << endl;

    LinePoint lp;
    LinePoint *pLin = &lp;
    pLin->set(5, 7);
    pLin->setLine("test");
    pLin->drivedShow();
    testshow(pLin);
    // 응용 end //
#endif
}