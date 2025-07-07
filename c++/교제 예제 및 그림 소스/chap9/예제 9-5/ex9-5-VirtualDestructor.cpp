#include <iostream>
using namespace std;

class Base {
public:
	virtual ~Base() { cout << "~Base()" << endl; }
};

class Derived: public Base {
public:
	virtual ~Derived() { cout << "~Derived()" << endl; }
};

int main() {
	Derived *dp  = new Derived();
	Base *bp = new Derived();

	delete dp; // Derived의 포인터로 소멸
	delete bp; // Base의 포인터로 소멸
}
