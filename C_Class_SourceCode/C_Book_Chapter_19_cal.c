#include <stdio.h>

extern int c; //다른 C파일의 전역 변수를 참조할때 extern

void intput_data(int *pa, int *pb)
{
    printf("정수 두 개를 입력하세요 : ");
    scanf("%d %d", pa, pb);
    printf("현재 C의 값은 %d\n", c);
}

double average(int a, int b)
{
    return (a + b) / 2.0;
}