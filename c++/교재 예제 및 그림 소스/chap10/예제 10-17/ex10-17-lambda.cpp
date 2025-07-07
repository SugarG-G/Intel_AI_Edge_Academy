#include <iostream>  
using namespace std;

int main() {
	double pi = 3.14; // 지역 변수

	auto calc = [pi](int r) -> double { return pi*r*r; }; // 반지름이 r인 원 면적을 리턴하는 람다 함수 작성

	cout << "면적은 " << calc(3); // 람다식 호출. 28.26출력
}