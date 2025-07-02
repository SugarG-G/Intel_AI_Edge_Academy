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
    // Power(const Power &p)
    // {
    //     cout << "복사 생성자 호출, " << "kick = " << p.kick << " punch = " << p.punch << endl;
    //     this->kick = p.kick;
    //     this->punch = p.punch;
    // }
    void show();
    // Power operator+(Power op2);
    Power operator+(Power &op2);
};

void Power::show()
{
    cout << "kick = " << kick << ',' << "punch = " << punch << endl;
}

// Power Power::operator+(Power op2)
// {
//     Power tmp;
//     tmp.kick = this->kick + op2.kick;
//     tmp.punch = this->punch + op2.punch;

//     return tmp;
// }

// 참조 타입으로 구현
Power Power::operator+(Power &op2)
{
    Power tmp;
    tmp.kick = this->kick + op2.kick;
    tmp.punch = this->punch + op2.punch;

    return tmp;
}

int main()
{
    Power a(3, 5), b(4, 6), c;
    c = a + b;
    a.show();
    b.show();
    c.show();
}