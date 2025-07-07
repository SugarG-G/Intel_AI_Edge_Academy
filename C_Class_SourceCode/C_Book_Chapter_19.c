/***********************************************************/
// [0-0] Ÿ��Ʋ
/***********************************************************/
#include <stdio.h>
#include "student.h" // ������ ����� ��� ��밡��

// ��ũ��
#define PI 3.141592
#define UNIT "cm^2"
#define SUCCESS_PRINT printf("���� ���ϱ� ���� \n")

#define SUM(a, b) (a + b)
#define MUL(a, b) (a * b)

#define NAME_CAT(x, y) (x##y)

#define VER 7 //����
#define BIT16 // ���� ǥ�� ����


int main(void)
{

#if VER >= 6
    printf("���� %d�Դϴ�.\n", VER);
#endif

    int max;

#ifdef BIT16
    max = 32767;
#else
    max = 2147483647;
#endif

    printf("��������  �ִ� ���� : %d\n", max);

    //�̹� ������� �ִ� ��ũ��
    printf("������ ��¥ : %s\n", __DATE__);
    printf("������ ��¥ : %s\n", __TIME__);
    printf("���ϸ� : %s\n", __FILE__);
    printf("�Լ��� : %s\n", __FUNCTION__);
    printf("���ȣ : %d\n", __LINE__);

#line 2025 "macro.c"
    printf("���ϸ� : %s\n", __FILE__);
    printf("���ȣ : %d\n", __LINE__);

    for (int i = 1; i <= 3; i++)
    {
        int NAME_CAT(score, i);
        NAME_CAT(score, i) = i * 10;
        printf("%d\n", NAME_CAT(score, i));
    }

    int score1 = 10;
    int score2 = 20;
    int score3 = 30;

    int result = SUM(2, 5);
    printf("%d\n", result);

    int result2 = 30 / MUL(2, 5);
    printf("%d\n", result2);

    int r;
    printf("�������� �Է��ϼ��� : ");
    scanf("%d", &r);

    double area = PI * r * r;

    printf("���� ���̴� %.2lf%s\n", area, UNIT);
    SUCCESS_PRINT;

    Student s1;

    s1.num = 315;
    s1.grade = 3.7;

    return 0;
}
