#include "../include/colorpoint.h"
#include <iostream>

void ColorPoint::setColor(std::string color)
{
    this->color = color;
}

void ColorPoint::showColorPoint()
{
    std::cout << color << ":";
    showPoint();
}