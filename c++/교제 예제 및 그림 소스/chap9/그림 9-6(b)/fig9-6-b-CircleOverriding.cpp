#include <iostream>
using namespace std;

class Shape {
public:
	void paint() { 
		draw(); 
	}
	virtual void draw() { 
		cout << "Shape::draw() called" << endl; 
	}
};

class Circle : public Shape {
public:
	virtual void draw() { 
		cout << "Circle::draw() called" << endl; 
	}
};

int main() {
	Shape *pShape = new Circle();
	pShape->paint(); 
	delete pShape;
}