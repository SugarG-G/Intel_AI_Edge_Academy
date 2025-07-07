/***********************************************************/
// [13-1] �� �Լ����� ���� �̸����� ���� ������ ����� ���
/***********************************************************/

#if 0
#include <stdio.h>

// �����Ϸ�
// C�� ����� �� �ִ� ���α׷�

// Vistual Studio
// -> IDE (Intergrated Development Envornment) ���հ���ȯ��

// ���α׷��� ��� -> C
// IDE -> VS

// ���� 2���� ī�װ�
// 1. ������ �� �� �� �ִ� ���� -> IDE�� ������
// 2. ������ �� �� �� �ִ� ����

void assign(void){
    auto int a = 20;
    printf("assign �Լ� �� a��  �� : %d\n");
}

int main(void)
{
	auto int a = 10;
    printf("a�� �� : %d\n", a);

    assign();
    printf("a�� �� : %d\n", a);

	return 0;
}
#endif

/***********************************************************/
// [13-2] ��� �ȿ��� ����ϴ� ���� ����
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
    int a = 10;
    printf("here1 a�� �� : %d\n", a); // 10
    {
        int a = 20;
        printf("here2 a�� �� : %d\n", a);
        {
            int a = 30;
            printf("here3 a�� �� : %d\n", a);
        }
    }
    return 0;
}
#endif

/***********************************************************/
// [13-3] ���� ������ ���
/***********************************************************/

#if 0
#include <stdio.h>

int a;

void assign10(void){
    a = 10;
}

void assign20(void){
    auto int a;
    a = 20;
}

int main(void)
{
    // ���� ���� -> �ʱ�ȭ�� �ȵǾ� ������ ��� �ȵ�
    // int b;
    // printf("%d", b);

    //���� ������ �����Ϸ��� �ڵ����� �ʱ�ȭ
    // int > 0, double > 0.0, char > 0
    printf("�Լ� ȣ�� �� ���� ���� a�� �� : %d\n", a);
    assign10();
    assign20();
    printf("�Լ� ȣ�� �� ���� ���� a�� �� : %d\n", a);
	
	return 0;
}
#endif

/***********************************************************/
// [13-4] ���� ���� ����
/***********************************************************/

#if 0
#include <stdio.h>

void print_star(){
    // static �Լ� ���� ��������� �޸𸮿� ����
    static int a = 1;
    for(int i = 0 ; i < a; i++){
        printf("*");
    }
    printf("\n");
    a++;
}

int main(void)
{
    for(int i = 0; i < 5; i++){
        print_star();
    }
	return 0;
}
#endif

/***********************************************************/
// [13-5] �������� ����
/***********************************************************/

#if 0
#include <stdio.h>
#include <time.h> // clock()

int main(void)
{
    // ����� ��
    // 100 > 100�� ����� �� sum�� ����

    register int num = 2000000000;
    register long sum = 0;

    long start = clock();

    for (int i = 1; i <= num; i++)
    {
        if (num % i == 0)
        {
            sum += i;
        }
    }
    printf("%d�� ����� �� : %lld\n", num, sum);
    long end = clock();

    // time : for�� ���� �ð� (s)
    double time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("�ҿ� �ð� : %lfs\n", time);

    return 0;
}
#endif

/***********************************************************/
// [13-6] ���� �����ؼ� ����
/***********************************************************/

#if 0
#include <stdio.h>

int add_ten(int a){
    a = a + 10;

    return a;
}

int main(void)
{
    int a = 10;
    
    printf("�Լ� ȣ�� �� a : %d\n", a);
    a = add_ten(a);
    printf("�Լ� ȣ�� �� a : %d\n", a);
	
	return 0;
}
#endif

/***********************************************************/
// [13-7] �ּҸ� ����
/***********************************************************/

#if 0
#include <stdio.h>

void add_ten(int *pa){
    *pa = *pa + 10;
}

int main(void)
{
    int a = 10;
    printf("�Լ� ȣ�� �� a : %d\n", a);
    add_ten(&a);
	printf("�Լ� ȣ�� �� a : %d\n", a);
	return 0;
}
#endif

/***********************************************************/
// [13-8] �ּҸ� ��ȯ�ϴ� �Լ�
/***********************************************************/

#if 0
#include <stdio.h>

int *sum(int a, int b){
    static int result;
    result = a + b;
    return &result;
}

int main(void)
{
    int a = 10, b = 20;

    int *presult = sum(a, b);
    printf("�� ������ �� : %d\n", *presult);
	
	return 0;
}
#endif

/***********************************************************/
// [13-����] ���� ���� ��ȯ ���α׷�
/***********************************************************/

#if 1
#include <stdio.h>

int a, b;

void swap(){
    int temp;
    temp = a;
    a = b;
    b = temp;
}

int main(void)
{
	a = 10, b = 20;
    printf("%d %d\n", a, b);

    swap(a, b);
    printf("%d %d\n", a, b);

	return 0;
}
#endif

