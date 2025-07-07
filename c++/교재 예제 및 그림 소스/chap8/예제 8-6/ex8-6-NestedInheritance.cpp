#include <iostream>
using namespace std;

class Base {
	int a;
protected:
	void setA(int a) { this->a = a; }
public:
	void showA() { cout << a; }
};

class Derived : private Base {
	int b;
protected:
	void setB(int b) { this->b = b; }
public:
	void showB() {
		setA(5); 		// ¨ç
		showA(); 		// ¨è
		cout << b;
	}
};

class GrandDerived : private Derived {
	int c;
protected:
	void setAB(int x) {
		setA(x); 		// ¨é
		showA(); 		// ¨ê 
		setB(x); 		// ¨ë
	}
};