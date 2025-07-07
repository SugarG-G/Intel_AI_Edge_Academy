/***********************************************************/
// [9-1] ������ �޸� �ּ� Ȯ��
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
	int a;
    double b;
    char c;

    printf("int�� ������ �ּ� : %u\n", &a);
    printf("double�� ������ �ּ� : %u\n", &b);
    printf("char�� ������ �ּ� : %u\n", &c);

	return 0;
}
#endif

/***********************************************************/
// [9-2] ������ ����� ���
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
	int a;
    int *pa;

    pa = &a;

    printf("pa�� ��� �ִ� �� : %d\n", pa);

    a = 10;
    printf("�����ͷ� a �� ��� : %d\n", a);

    *pa = 20; // * : ���� ���� ������
    printf("���������� a �� ��� : %d\n", a);

	return 0;
}
#endif

/***********************************************************/
// [9-3] �����͸� ����� �� ������ �հ� ��� ���
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
	int a = 10, b = 15;
    int *pa, *pb;

    int total;
    int *pt;
    
    double avg;
    double *pg;


    // 1. pa, pb, pt, pg�� �ʱ�ȭ.
    pa = &a, pb = &b, pt = &total, pg = &avg;
    // total�� a+b����
    *pt = *pa + *pb;
    *pg = (double)*pt / 2;
    printf("�� ������ �� : %d, %d\n", *pa, *pb);
    printf("�� ������ ���� : %d\n", *pt);
    printf("�� ������ ��� : %.1lf\n", *pg);
    

	return 0;
}
#endif

/***********************************************************/
// [9-4] �����Ϳ� const ���
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
    const int num = 10; // const ���� ������ ����� ���ÿ� �ʱ�ȭ!!!
    int a = 10, b = 20;
    const int *pa = &a;

    printf("a�� �� : %d\n", *pa);

    pa = &b; // pa�� b�� �ּҸ� ����Ų��!!
    printf("b�� �� : %d\n", *pa);

    pa = &a;
    a = 7;
    printf("a�� �� : %d\n", *pa);
    
    // *pa = 77; // const�� ������ ���� �� ���� ���� �Ұ�!!
    // printf("a�� �� : %d\n", *pa);

    return 0;
}
#endif

/***********************************************************/
// [9-5] �ּҿ� �������� ũ��
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
    char c;
    int a;
    double b;

    // �����ʹ� �ݵ�� ������ ������ �ڷ��� ��ġ
    char *pc = &c;
    int *pa = &a;
    double *pb = &b;

    // �ּ��� ũ��
    printf("a�ּ� : %d, b�ּ� : %d, c�ּ� : %d\n", sizeof(&a), sizeof(&b), sizeof(&c));
    // �������� ũ��
    printf("a������ : %d, b������ : %d, c������ : %d\n", sizeof(a), sizeof(b), sizeof(c));
    // �����Ͱ� ����Ű�� ������ ũ��
    printf("a�� : %d, b�� : %d, c�� : %d\n", sizeof(*pa), sizeof(*pb), sizeof(*pc));

    return 0;
}
#endif

/***********************************************************/
// [9-6] ������ ���� �������� ����
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
    int a = 10;
    int *pa = &a;
    
    double *pd;

    // pa�� a�� ����Ű�� int�� ������
    // pd�� double���� ����ų �� �ִ� ������

    // //����) �� ��ȯó�� ��� �� �ּ� ���� Ȯ���ʿ�
    // pd = pa; //a�� �ּҸ� ����ų �� �ְ� pd�� ����
    // printf("%lf\n", *pd);

    int *pb;
    pb = pa;
    printf("%d\n", *pa);
    printf("%d\n", *pb);

	return 0;
}
#endif

/***********************************************************/
// [9-7] �����͸� ����� �� ������ �� ��ȯ
/***********************************************************/

#if 0
#include <stdio.h>

void swap(int *pa, int *pb){
    int temp;

    //�� ���� ġȯ�� ���;
    temp = *pa;
    *pa = *pb;
    *pb = temp;
    printf("%d, %d", *pa, *pb);
}

int main(void)
{
    int a = 10, b = 20;
    
    swap(a, b);

	return 0;
}
#endif

/***********************************************************/
// [9-8, 9] �ٸ� �Լ��� ���� ����ϱ�
/***********************************************************/

#if 0
#include <stdio.h>

void swap(int a, int b){
    int temp;
    temp = a;
    a = b;
    b = temp;
}

int main(void)
{
	int a = 10, b = 20;
    swap(a,b);
    printf("a : %d, b : %d", a, b);
	return 0;
}


#endif

/***********************************************************/
// [9-����] Ÿ��Ʋ
/***********************************************************/

#if 0
#include <stdio.h>

void swap(int *pa, int *pb){
    int temp;

    temp = *pa;
    *pa = *pb;
    *pb = temp;
}

void descending(int *max, int *mid, int *min){

    if(*max < *mid){
        swap(max, mid);
    }
    if(*max < *min){
        swap(max, min);
    }
    if(*mid < *min){
        swap(mid, min);
    }
}

int main(void)
{
	// �� ���� ���� �Է�
    int max, mid, min;
    // 10 20 30
    scanf("%d %d %d", &max, &mid, &min);

    // �� 3�� �ѱ� �� ���� ū ���� max
    // �߰� ���� mid
    // ���� ���� ���� min���� �ٲٴ� �Լ�
    descending(&max, &mid, &min);

    printf("%d %d %d\n", max, mid, min); // 30 20 10 ���


	return 0;
}

#endif