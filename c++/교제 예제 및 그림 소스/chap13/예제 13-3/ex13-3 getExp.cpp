#include <iostream>
using namespace std;

bool getExp(int base, int exp, int &ret) { // base의 exp 지수승을 계산하여 ret에 저장
	if(base <= 0 || exp <= 0) {
		return false; // 오류 리턴
	}
	int value=1;
	for(int n=0; n<exp; n++) 
		value = value * base; // base를 exp 만큼 곱하여 지수 값 계산
	ret = value; // 계산 값을 ret에 저장
	return true; // 정상 리턴. 계산된 값은 ret에 있음
}

int main() {
	int v=0;
	if(getExp(2, 3, v)) // v = 2의 3승 = 8. getExp()는 true 리턴
		cout << "2의 3승은 " << v << "입니다." << endl;
	else 
		cout << "오류. 2의 3승은 " << "계산할 수 없습니다." << endl;

	int e=0;
	if(getExp(2, -3, e)) // 2의 -3 승 ?. getExp()는 false 리턴
		cout << "2의 -3승은 " << v << "입니다." << endl;
	else
		cout << "오류. 2의 -3승은 " << "계산할 수 없습니다." << endl;
}