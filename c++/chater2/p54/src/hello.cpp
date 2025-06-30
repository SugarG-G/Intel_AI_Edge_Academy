#include <iostream>

using namespace std;

int num = 5;
int main(int argc, char* argv[])
{
    int num = 1;
    double db = 3.1415;
    std::cout << "hello" << std::endl;
    std::cout << num << std::endl;
    std::cout.precision(3);
    std::cout << db << std::endl;
    std::cout << ::num << std::endl; // 전역 변수를 출력

    cout << "using namespace std" << endl;

    return 0;
}