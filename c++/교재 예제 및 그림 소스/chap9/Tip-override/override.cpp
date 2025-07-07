#include <iostream>
using namespace std;

class Shape {
public:
	virtual void draw(){
		cout << "shape";
	}
};

class Rect : public Shape {
public:
	void draw() override { // override는 draw()가 Shape의 가상 함수를 오버라이딩하고 있는지 확인하라는 지시
		cout << "rect";
	}
	// 아래 코드와 같이 하면, 컴파일러가 Shape 클래스에 가상함수로 선언된
	// drow() 함수를 찾을 수 없어 컴파일 오류를 발생시킨다.
	/* void drow()  override { 
		cout << "rect";
	} */
};

int main() {
	Rect r;
	r.draw();
}