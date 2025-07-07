#pragma once
#include "../include/animal.h"

class Dog : public Animal
{
    std::string dogBark;

public:
    Dog();
    Dog(std::string name, int age, std::string dogBark);

    Dog(const Dog &refd);

    virtual ~Dog();

    void setBark(std::string dogBark);
    std::string getBark() const;
    virtual void crying();
};