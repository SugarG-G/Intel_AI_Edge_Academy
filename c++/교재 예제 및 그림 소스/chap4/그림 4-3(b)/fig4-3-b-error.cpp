#include <iostream>
using namespace std;

class Circle {
	int radius; 
public:
	Circle(int r)  { radius = r; }
	double getArea()  {
		return 3.14*radius*radius;
	}
}; 

int main() {
	Circle waffle(15);
	Circle circleArray[3]; 
}