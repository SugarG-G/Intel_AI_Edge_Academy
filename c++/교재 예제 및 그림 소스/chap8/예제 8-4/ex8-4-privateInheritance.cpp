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
	void showB() { cout << b; }
};

int main() {
	Derived x;
	x.a = 5; 		// ¨ç
	x.setA(10);		// ¨è
	x.showA(); 		// ¨é
	x.b = 10; 		// ¨ê
	x.setB(10);		// ¨ë
	x.showB(); 		// ¨ì
} 