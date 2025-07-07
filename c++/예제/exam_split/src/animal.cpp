#include "../include/animal.h"
#include <iostream>

Animal::Animal()
{
    this->name = "";
    this->age = 0;
}
Animal::Animal(std::string name, int age)
{
    // cout << "Animal 복사 생성자" << endl;
    this->name = name;
    this->age = age;
    // setName(name);
    // setAge(age);
}
Animal::Animal(const Animal &refa)
{
    this->name = refa.getName();
    this->age = refa.getAge();
}
Animal::~Animal()
{
    std::cout << "Animal 소멸" << std::endl;
}

void Animal::setName(std::string name)
{
    this->name = name;
}
void Animal::setAge(int age)
{
    this->age = age;
}
std::string Animal::getName() const
{
    return this->name;
}
int Animal::getAge() const
{
    return this->age;
}