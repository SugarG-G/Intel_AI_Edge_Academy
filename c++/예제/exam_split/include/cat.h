#pragma once
#include "../include/animal.h"
class Cat : public Animal
{
    std::string catBark;

public:
    Cat();
    Cat(std::string name, int age, std::string catBark);
    Cat(const Cat &refc);
    virtual ~Cat();

    void setBark(std::string catBark);
    std::string getBark() const;
    virtual void crying();
};