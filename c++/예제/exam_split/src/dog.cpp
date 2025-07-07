#include "../include/dog.h"
#include <iostream>
Dog::Dog()
{
    this->dogBark = "";
}
Dog::Dog(std::string name, int age, std::string dogBark) : Animal(name, age)
{
    this->dogBark = dogBark;
}
// {
//     setName(name);
//     setAge(age);
//     setBark(dogBark);
// }
Dog::Dog(const Dog &refd) : Animal(refd)
{
    // cout << "Dog 복사 생성자" << endl;
    this->dogBark = refd.getBark();
}
Dog::~Dog()
{
    std::cout << "Dog 소멸" << std::endl;
};

void Dog::setBark(std::string dogBark)
{
    this->dogBark = dogBark;
}
std::string Dog::getBark() const
{
    return this->dogBark;
}
void Dog::crying()
{
    std::cout << getName() << "는 " << getBark() << std::endl;
}