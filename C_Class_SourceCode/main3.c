#include <stdio.h>
#include "point.h"
#include "line.h"

int main(){
    Line a = {{1,2}, {5,6}};

    //���� ��� ��ǥ!!
    Point b;
    b.x = (a.first.x + a.second.x) / 2;
    b.y = (a.first.y + a.second.y) / 2;

    printf("���� ��� ��ǥ %d %d",b.x, b.y);
}