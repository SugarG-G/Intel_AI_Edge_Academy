#include <iostream>

using namespace std;

class Power
{
private:
    int kick;
    int punch;

public:
    Power(int kick = 0, int punch = 0)
    {
        this->kick = kick;
        this->punch = punch;
    }
    // 복사 생성자
    Power(const Power &p);
    void show();
    // Power operator+(Power op2);
    Power operator+(const Power &op2);
    Power operator+(const int &a); // 응
};

void Power::show()
{
    cout << "kick = " << kick << ',' << "punch = " << punch << endl;
}

Power::Power(const Power &p)
{
    cout << "복사 생성자 호출, " << "kick = " << p.kick << " punch = " << p.punch << endl;
    this->kick = kick;
    this->punch = punch;
}
// Power Power::operator+(Power op2)
// {
//     Power tmp;
//     tmp.kick = this->kick + op2.kick;
//     tmp.punch = this->punch + op2.punch;

//     return tmp;
// }

// 참조 타입으로 구현
Power Power::operator+(const Power &op2)
{
    Power tmp;
    tmp.kick = this->kick + op2.kick;
    tmp.punch = this->punch + op2.punch;

    return tmp;
}
// 응용
Power Power::operator+(const int &a)
{
    // cout << "a : " << a;
    cout << "this->kick : " << this->kick;
    cout << " this->punch : " << this->punch << endl;
    Power tmp;
    tmp.kick = this->kick + a;
    tmp.punch = this->punch + a;

    return tmp;
}

int main()
{
    Power a(3, 5), b(4, 6), c;
    c = a + b;
    a.show();
    b.show();
    c.show();

    // 응용
    c = c + 2;
    c.show();
}