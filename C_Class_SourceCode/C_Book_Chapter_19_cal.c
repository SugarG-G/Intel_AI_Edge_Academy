#include <stdio.h>

extern int c; //�ٸ� C������ ���� ������ �����Ҷ� extern

void intput_data(int *pa, int *pb)
{
    printf("���� �� ���� �Է��ϼ��� : ");
    scanf("%d %d", pa, pb);
    printf("���� C�� ���� %d\n", c);
}

double average(int a, int b)
{
    return (a + b) / 2.0;
}