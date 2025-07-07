#include <iostream>
using namespace std;

class Base
{
public:
    // void f() { cout << "Base::f() called" << endl; } // 재정의
    virtual void f() { cout << "Base::f() called" << endl; } // 오버라이딩
};

class Derived : public Base
{
public:
    // void f() { cout << "Base::f() called" << endl; }    // 재정의
    virtual void f() { cout << "Derived::f() called" << endl; } // 오버라이딩
};

int main()
{
    Derived d, *pDer;
    pDer = &d; // 객체 d를 가리킨다.
    pDer->f(); // Derived::f() 호출

    Base *pBase;
    pBase = pDer; // 업캐스팅. 객체 d를 가리킨다.
    pBase->f();   // 동적 바인딩 발생!! Derived::f() 실행
}