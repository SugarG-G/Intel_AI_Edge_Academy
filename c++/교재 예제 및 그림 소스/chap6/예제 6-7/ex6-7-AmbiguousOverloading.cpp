#include <iostream>
using namespace std;

float square(float a) {
	return a*a;
}

double square(double a) {
	return a*a;
}

int main() {
	cout << square(3.0); // square(double a); 호출
	cout << square(3); // 중복된 함수에 대한 모호한 호출로서, 컴파일 오류
}