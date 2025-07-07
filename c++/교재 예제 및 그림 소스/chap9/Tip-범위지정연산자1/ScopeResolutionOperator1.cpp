#include <iostream>
using namespace std;

int n=11; // 전역 변수

int main() {
	int n=3; // 지역 변수
	cout << ::n << endl; // 전역 변수 n(11)을 출력
	cout << n << endl;  // 지역 변수 n(3)을 출력
}