#include "../include/animal.h"
#include "../include/cat.h"
#include "../include/dog.h"
#include <iostream>
#include <string>

using namespace std;

class Animal;
void running(Animal);

void running(Animal *ap)
{
    cout << ap->getName() << "가 달린다" << endl;
}

void run(Animal *ap)
{
    running(ap);
    ap->crying();
}

int main()
{
    // Animal a;
    // Animal *ap = &a;
    // ap->setName("강아지");
    // ap->setAge(12);
    // cout << ap->getName() << " " << ap->getAge();
    // Dog *dog = new Dog("강아지", 4, "멍멍");
    // run(ap);
#if 1
    cout << "--추상클래스와 파생 클래스 구현--\n";
    Dog *dog = new Dog("강아지", 4, "멍멍");
    Cat *cat = new Cat("고양이", 2, "야옹");

    cout << "--매개 변수의 다형성 구현--\n";
    run(dog);
    run(cat);

    cout << "\n--복사생성자 직접 구현--\n";
    Dog copyDog(*dog);
    cout << copyDog.getName() << endl;
    cout << copyDog.getAge() << endl;
    cout << copyDog.getBark() << endl;

    cout << "\n--소멸자실행--\n";
    delete dog;
    delete cat;
#endif
    return 0;
}