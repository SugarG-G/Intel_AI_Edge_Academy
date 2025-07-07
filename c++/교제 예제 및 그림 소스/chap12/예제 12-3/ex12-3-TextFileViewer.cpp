#include <iostream>
#include <fstream>
using namespace std;

int main() {
	const char* file = "c:\\windows\\system.ini"; // 읽을 파일
	ifstream fin(file);
	if(!fin) {
		cout << file << " 열기 오류" << endl;
		return 0;
	}
	int count = 0;
	int c;
	while((c=fin.get()) != EOF) { // EOF를 만날때까지 읽음
		cout << (char)c; // 읽은 문자를 화면에 출력
		count++;
	}

	cout << "읽은 바이트 수는 " << count << endl;
	fin.close(); // 파일 닫기
}