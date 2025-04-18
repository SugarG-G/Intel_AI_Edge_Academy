
#include <stdio.h>
//두 정수의 평균을 구하는  프로그램
void intput_data(int *, int *);
double average(int, int);

int c = 100;

int main(void){

    int a, b;
    intput_data(&a, &b);
    double avg = average(a, b);
    printf("%d와 %d의 평균 : %.1lf", a, b, avg);

    return 0;
}