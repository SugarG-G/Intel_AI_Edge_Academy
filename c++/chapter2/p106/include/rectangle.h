#pragma once
class Rectangle
{
private:
    int width;
    int height;

public:
    Rectangle();
    Rectangle(int w, int h);
    void setter(int w, int h);
    int getArea();
    ~Rectangle();
};