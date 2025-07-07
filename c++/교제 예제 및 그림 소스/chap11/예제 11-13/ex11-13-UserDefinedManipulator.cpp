#include <iostream>
#include <string>
using namespace std;

istream& question(istream& ins) {
	cout << "거울아 거울아 누가 제일 이쁘니?";
	return ins;
}

int main() {
	string answer;
	cin >> question >> answer;
	cout << "세상에서 제일 이쁜 사람은 " << answer << "입니다." << endl;
}