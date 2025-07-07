#include <iostream>
using namespace std;

class Power {
	int kick;
	int punch;
public:
	Power(int kick=0, int punch=0) {
		this->kick = kick; this->punch = punch;
	}
	void show();
	friend Power operator+(Power op1, Power op2); // 프렌드 선언
};

void Power::show() {
	cout << "kick=" << kick << ',' << "punch=" << punch << endl;
}

Power operator+(Power op1, Power op2) {
	Power tmp; // 임시 객체 생성
	tmp.kick = op1.kick + op2.kick; // kick 더하기
	tmp.punch = op1.punch + op2.punch; // punch 더하기
	return tmp; // 임시 객체 리턴
}

int main() {
	Power a(3,5), b(4,6), c;
	c = a + b; // 파워 객체 더하기 연산
	a.show();
	b.show();
	c.show();
}