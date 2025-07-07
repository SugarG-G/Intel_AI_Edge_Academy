#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
    int width;
    int height;

    /*
    cout << "너비를 입력하세요 >>";
    cin >> width;

    cout << "높이를 입력하세요 >>";
    cin >> height;
    */

    cout << "너비와 높이를 입력 하세요 >>";
    cin >> width >> height;
    int area = width * height;
    cout << "면적은 " << area << "\n";

    return 0;
}