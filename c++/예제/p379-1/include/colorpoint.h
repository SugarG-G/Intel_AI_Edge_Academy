#pragma once
#include "../include/point.h"
#include <string>
class ColorPoint : public Point
{
private:
    std::string color;

public:
    void setColor(std::string);
    void showColorPoint();
};