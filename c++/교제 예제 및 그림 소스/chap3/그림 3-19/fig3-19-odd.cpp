#include <iostream>
using namespace std;

int odd(int x) {
   return (x%2);
}

int main() {
	int sum = 0;

	for(int i=1; i<=10000; i++) {
		if(odd(i))
			sum += i;
	}
	cout << sum;
}