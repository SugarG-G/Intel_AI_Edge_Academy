#include <iostream>
using namespace std;

#include "MyStack.h"

int main() {
	MyStack intStack;
	try {
		intStack.push(100); // 100 Çª½Ã
		intStack.push(200); // 200 Çª½Ã
		cout << intStack.pop() << endl; // ÆË 200
		cout << intStack.pop() << endl; // ÆË 100
		cout << intStack.pop() << endl; // "Stack Empty" ¿¹¿Ü ¹ß»ý
	}
	catch(const char* s) {
		cout << "¿¹¿Ü ¹ß»ý : " << s << endl;
	}
}