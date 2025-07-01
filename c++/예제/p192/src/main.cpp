#include <iostream>
#include <string>

using namespace std;

int main()
{
    // 문자열 생성
    string str; // 빈 문자열을 가진 스트링 객체 생성
    cout << str.capacity() << endl;
    string address("서울시 성북구 삼선동 389");
    cout << address.capacity();
    string copyAddress(address); // address의 문자열을 복사한 스트링 객체 생성

    char text[] = {'L', 'o', 'v', 'e', ' ', 'C', '+', '+', '\0'}; // C-스트링
    string title(text);                                           // "Love C++" 문자열을 가진 스트링 객체 생성

    // 문자열 출력
    cout << str << endl; // 빈 문자열. 아무 값도 출력되지 않음
    cout << address << endl;
    cout << copyAddress << endl;
    cout << title << endl;

    return 0;
}