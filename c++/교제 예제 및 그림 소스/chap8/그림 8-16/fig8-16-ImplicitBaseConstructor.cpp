#include <iostream>
using namespace std;

class  A {
public:
	A() { cout << "생성자 A" << endl; }
	A(int x) {
		cout << "매개변수생성자 A" << x << endl; 
	}
};

class  B : public A {
public:
	B() { // A() 호출하도록 컴파일됨
		cout << "생성자 B" << endl;
	}
	B(int x) { // A() 호출하도록 컴파일됨
		cout << "매개변수생성자 B" << x << endl;
	}
};

int main() {
	B b(5);
}