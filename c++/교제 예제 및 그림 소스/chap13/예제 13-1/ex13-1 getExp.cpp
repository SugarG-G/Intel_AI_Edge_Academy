#include <iostream>
using namespace std;

int getExp(int base, int exp) { // base의 exp 지수승을 계산하여 리턴
	int value=1;
	for(int n=0; n<exp; n++) 
		value = value * base; // base를 exp번 곱하여 지수 값 계산
	return value;
}

int main() {
	int v= getExp(2, 3); // 2의 3승 = 8
	cout << "2의 3승은 " << v << "입니다." << endl;
	int e = getExp(2, -3); // 2의 -3승은 ?
	cout << "2의 -3승은 " << e << "입니다." << endl;
}