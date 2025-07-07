#include <iostream>
using namespace std;

int getExp(int base, int exp) { // base의 exp 지수승을 계산하여 ret에 저장
	if(base <= 0 || exp <= 0) {
		return -1; // 오류 리턴
	}
	int value=1;
	for(int n=0; n<exp; n++) 
		value = value * base; // base를 exp번 곱하여 지수 값 계산
	return value; // 정상 리턴. 계산된 값 리턴
}

int main() {
	int v=0;
	v = getExp(2, 3); // v = 2의 3승 = 8. getExp()는 8 리턴
	if(v != -1)
		cout << "2의 3승은 " << v << "입니다." << endl;
	else 
		cout << "오류. 2의 3승은 " << "계산할 수 없습니다." << endl;

	int e=0;
	e = getExp(2, -3); // 2의 -3 승 ?. getExp()는 -1 리턴
	if(e != -1)
		cout << "2의 -3승은 " << v << "입니다." << endl;
	else
		cout << "오류. 2의 -3승은 " << "계산할 수 없습니다." << endl;
}