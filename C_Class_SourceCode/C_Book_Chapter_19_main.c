
#include <stdio.h>
//�� ������ ����� ���ϴ�  ���α׷�
void intput_data(int *, int *);
double average(int, int);

int c = 100;

int main(void){

    int a, b;
    intput_data(&a, &b);
    double avg = average(a, b);
    printf("%d�� %d�� ��� : %.1lf", a, b, avg);

    return 0;
}