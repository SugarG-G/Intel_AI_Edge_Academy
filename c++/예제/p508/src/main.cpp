#include <iostream>
#include <map>
#include <string>

using namespace std;

int main()
{
    map<string, string> dic;

    /// pair 템플릿 클래스///
    pair<int, int> p = {2, 3}; // 선언과 동시에 초기화 방법
    p.first = 5;
    p.second = 10;

    cout << p.first << ' ' << p.second << endl;
    /////////////////////////

    dic.insert(make_pair("love", "사랑"));
    dic.insert(make_pair("apple", "사과"));
    dic["cherry"] = "체리";

    cout << "저장된 단어 개수" << dic.size() << endl;

    string eng;
    while (1)
    {
        cout << "찾고 싶은 단어 >> ";
        getline(cin, eng);

        if (eng == "exit")
            break;

        if (dic.find(eng) == dic.end())
            cout << "없음" << endl;
        else
            cout << dic[eng] << endl;
    }
    cout << "종료합니다." << endl;
}