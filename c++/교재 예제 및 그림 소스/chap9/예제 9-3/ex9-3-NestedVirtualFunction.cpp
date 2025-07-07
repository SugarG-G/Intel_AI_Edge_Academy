#include <iostream>
using namespace std;

class Base {
public: virtual void f() { cout << "Base::f() called" << endl; }
};

class Derived : public Base {
public: void f() { cout << "Derived::f() called" << endl; }
};

class GrandDerived  : public Derived {
public: void f()  { cout << "GrandDerived::f() called" << endl; }
};

int main() {
	GrandDerived g;
	Base *bp;
	Derived *dp;
	GrandDerived *gp;

	bp = dp = gp = &g; // 모든 포인터가 객체 g를 가리킴

	bp->f(); // Base의 멤버 f() 호출 --> 결과는?
	dp->f(); // Derived의 멤버 f() 호출 --> 결과는?
	gp->f(); // GrandDerived의 멤버 f() 호출 --> 결과는?
}
