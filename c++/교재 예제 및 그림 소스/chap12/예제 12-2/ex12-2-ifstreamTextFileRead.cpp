#include <fstream>
#include <iostream>

using namespace std;

int main()
{
    // 스트림 객체 생성 및 파일 열기
    // ifstream fin;
    fstream filetest;
    filetest.open("c:\\temp\\student.txt", ios::in | ios::out | ios::trunc | ios::binary);
    if (!filetest)
    { // 파일 열기 실패
        cout << "파일을 열 수 없다";
        return 0;
    }

    char name[10], dept[20];
    int sid;

    // 테스트 코드 작성
    filetest << "aaaa" << endl;
    filetest << "1234" << endl;
    filetest << "c++" << endl;

    filetest.seekg(ios::beg);

    // 파일 읽기
    filetest >> name; // 파일에 있는 문자열을 읽어서 name 배열에 저장
    filetest >> sid;  // 정수를 읽어서 sid 정수형 변수에 저장
    filetest >> dept; // 문자열을 읽고 dept 배열에 저장

    // 읽은 텍스트를 화면에 출력
    cout << name << endl;
    cout << sid << endl;
    cout << dept << endl;

    filetest.close(); // 파일 읽기를 마치고 파일을 닫는다.
}