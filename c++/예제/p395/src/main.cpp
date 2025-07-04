#include <iostream>
#include <string>
using namespace std;

class TV
{
    int size; // 스크린 크기

public:
    TV()
    {
        cout << "TV()" << endl;
        size = 20;
    }
    TV(int size)
    {
        cout << "TV(int size) 생성자" << endl;
        this->size = size;
    }
    ~TV() { cout << "TV() 소멸자" << endl; }
    int getSize() { return size; }
};

class WideTV : public TV
{ // TV를 상속받는 WideTV
    bool videoIn;

public:
    WideTV(int size, bool videoIn) : TV(size)
    {
        cout << "WideTV(int size, bool videoIn) 생성자" << endl;
        this->videoIn = videoIn;
    }
    ~WideTV() { cout << "WideTV() 소멸자" << endl; }
    bool getVideoIn() { return videoIn; }
};

class SmartTV : public WideTV
{                  // WideTV를 상속받는 SmartTV
    string ipAddr; // 인터넷 주소

public:
    SmartTV(string ipAddr, int size) : WideTV(size, true)
    {
        cout << "SmartTV(string ipAddr, int size) 생성자" << endl;
        this->ipAddr = ipAddr;
    }
    ~SmartTV() { cout << "SmartTV() 소멸자" << endl; }
    string getIpAddr() { return ipAddr; }
};

int main()
{
    // 32 인치 크기에 "192.0.0.1"의 인터넷 주소를 가지는 스마트 TV 객체 생성
    SmartTV htv("192.0.0.1", 32);
    cout << "size=" << htv.getSize() << endl;
    cout << "videoIn=" << boolalpha << htv.getVideoIn() << endl; // boolalpha bool 표시를 문자 true, false로 표시
    cout << "IP=" << htv.getIpAddr() << endl;
}
