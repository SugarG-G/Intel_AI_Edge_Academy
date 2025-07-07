#include <iostream>
using namespace std;

int multiply(int x, int y){
	if(x < 0 || y < 0)
		throw "음수 불가능";
	else
		return x*y;
}

int main() {
	try {
		int n = multiply(2, -3);
		cout << "곱은 " << n << endl;
	}
	catch(const char* negative) {
		cout << "exception happened : " << negative;
	}
}