#include <iostream>
using namespace std;

void sendMessage(const char* msg) { cout << msg << endl; }

class Window {
public:
	void sendMessage(const char* msg) { cout << "window msg : " << msg << endl; }
	void run() {
		::sendMessage("Glocal Hello"); // 전역 함수 호출
		sendMessage("Local Hello"); // 멤버 함수 호출
	}
};

int main() {
	Window window;
	window.run();
}
