#include <iostream>  
using namespace std;

int main() {
	// 람다 함수 선언과 동시에 호출(x=2, y=3 전달)
	[](int x, int y) { cout << "합은 " << x + y; } (2, 3); // 5 출력
}