#include <iostream> 
using namespace std; 

class PrivateAccessError {
private:
	int a;
	void f();
	PrivateAccessError();
public:
	int b;
	PrivateAccessError(int x);
	void g();
};

PrivateAccessError::PrivateAccessError() {
	a = 1; // (1)
	b = 1; // (2)
}

PrivateAccessError::PrivateAccessError(int x) {
	a = x; // (3)
	b = x; // (4)
}

void PrivateAccessError::f() {
	a = 5; // (5)
	b = 5; // (6)
}

void PrivateAccessError::g() {
	a = 6; // (7)
	b = 6; // (8)
}

int main() {
	PrivateAccessError objA; // (9)
	PrivateAccessError objB(100); // (10)
	objB.a = 10; // (11)
	objB.b = 20; // (12)
	objB.f(); // (13)
	objB.g(); // (14)
}