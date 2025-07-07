#include <iostream>
using namespace std;

class Base {
public:
	virtual void success() { cout << "Base::success() called" << endl; }
	virtual void fail() { cout << "Base::fail() called" << endl; }
	virtual void g(int x) { cout << "Base::g(int) called" << endl; }
};

class Derived : public Base {
public:
	virtual void success() { cout << "Derived::f() called" << endl; }
	virtual int fail() { cout << "Base::fail() called" << endl; }
	virtual void g(int x, double d) { cout << "Derived::g(int, double) called" << endl; }
};