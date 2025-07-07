#include <iostream>
using namespace std;

int g(int x, int y);

extern "C" int f(int x, int y);

int main() {
	cout << f(2, 5) << endl;
	cout << g(2, 5) << endl;
}
