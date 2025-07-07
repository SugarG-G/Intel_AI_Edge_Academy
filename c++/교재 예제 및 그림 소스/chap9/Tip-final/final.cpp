#include <iostream>
using namespace std;

// 1. 오버라이딩을 금지하는 final 사용 사례
class Shape1 {
public:
	virtual void draw() final { // draw()의 오버라이딩 금지 선언
		cout << "shape";
	}
};

class Rect1 : public Shape1 {
public:
	void draw() { // Shape의 draw()를 오버라이딩할 수 없어 컴파일 오류 발행
		cout << "rect";
	}
};

// 2. 클래스의 상속을 금지하는 final 사용 사례
class Shape2 final { // Shape2의 상속 금지 선언

};

class Rect2 : public Shape2 { // 상속받을 수 없는 Shape2를 상속받으려고 하여 컴파일 오류

};

// 3. 클래스의 상속을 금지하는 final 사용 사례
class Shape3 { 

};

class Rect2 final : public Shape3 { // Rect2의 상속 금지 선언

};

class RoundRect : public Rect2 { // Rect2를 상속받으려고 하여 컴파일 오류

};
int main() {
}