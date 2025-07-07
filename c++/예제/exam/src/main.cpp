#include <iostream>
#include <string>

using namespace std;

class Animal;
void running(Animal);

class Animal
{
    string name;
    int age;

public:
    Animal()
    {
        this->name = "";
        this->age = 0;
    }
    Animal(string name, int age)
    {
        // cout << "Animal 복사 생성자" << endl;
        this->name = name;
        this->age = age;
        // setName(name);
        // setAge(age);
    }
    Animal(const Animal &refa)
    {
        this->name = refa.getName();
        this->age = refa.getAge();
    }
    virtual ~Animal() { cout << "Animal 소멸" << endl; }

    void setName(string name) { this->name = name; }
    void setAge(int age) { this->age = age; }
    string getName() const { return this->name; }
    int getAge() const { return this->age; }
    friend void running(Animal *ap);
    virtual void crying() = 0;
};

void running(Animal *ap)
{
    cout << ap->getName() << "가 달린다" << endl;
}

class Dog : public Animal
{
    string dogBark;

public:
    Dog() { this->dogBark = ""; }
    Dog(string name, int age, string dogBark) : Animal(name, age) { this->dogBark = dogBark; }
    // {
    //     setName(name);
    //     setAge(age);
    //     setBark(dogBark);
    // }
    Dog(const Dog &refd) : Animal(refd)
    {
        // cout << "Dog 복사 생성자" << endl;
        this->dogBark = refd.getBark();
    }
    virtual ~Dog() { cout << "Dog 소멸" << endl; };

    void setBark(string dogBark) { this->dogBark = dogBark; }
    string getBark() const { return this->dogBark; }
    virtual void crying() { cout << getName() << "는 " << getBark() << endl; }
};

class Cat : public Animal
{
    string catBark;

public:
    Cat() { this->catBark = ""; }
    Cat(string name, int age, string catBark) : Animal(name, age) { this->catBark = catBark; }
    Cat(const Cat &refc) : Animal(refc)
    {
        // cout << "Cat 복사 생성자" << endl;
        this->catBark = refc.getBark();
    }
    virtual ~Cat() { cout << "Cat 소멸" << endl; }

    void setBark(string catBark) { this->catBark = catBark; }
    string getBark() const { return this->catBark; }
    virtual void crying() { cout << getName() << "는 " << getBark() << endl; }
};

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