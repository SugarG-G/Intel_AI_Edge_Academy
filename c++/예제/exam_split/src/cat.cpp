#include "../include/cat.h"
#include <iostream>

Cat::Cat()
{
    this->catBark = "";
}
Cat::Cat(std::string name, int age, std::string catBark) : Animal(name, age)
{
    this->catBark = catBark;
}
Cat::Cat(const Cat &refc) : Animal(refc)
{
    // cout << "Cat 복사 생성자" << endl;
    this->catBark = refc.getBark();
}
Cat::~Cat()
{
    std::cout << "Cat 소멸" << std::endl;
}

void Cat::setBark(std::string catBark)
{
    this->catBark = catBark;
}
std::string Cat::getBark() const
{
    return this->catBark;
}
void Cat::crying()
{
    std::cout << getName() << "는 " << getBark() << std::endl;
}