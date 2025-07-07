#pragma once
#include <string>

class Animal
{
    std::string name;
    int age;

public:
    Animal();
    Animal(std::string name, int age);
    Animal(const Animal &refa);
    virtual ~Animal();

    void setName(std::string name);
    void setAge(int age);
    std::string getName() const;
    int getAge() const;
    friend void running(Animal *ap);
    virtual void crying() = 0;
};

void running(Animal *ap);