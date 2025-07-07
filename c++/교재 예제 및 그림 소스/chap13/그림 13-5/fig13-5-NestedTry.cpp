#include <iostream>
using namespace std;

int main() {
	int x = 3;
	try {
		if(x < 0)
			throw 3; // catch(int outer) { } 블록에서 처리
		try {
			//throw 5; // catch(int inner) { } 블록에서 처리
			throw "abc";
		}
		catch(int inner) {
			cout << inner; // 5 출력
		}	
	}
	catch(const char* s) { 
		cout << s; 
	}
	catch(int outer) { 
		cout << outer; // 3 출력
	}
}