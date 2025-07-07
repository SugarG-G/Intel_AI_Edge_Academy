/***********************************************************/
// [15-1] ���� ������
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
    int a = 10;
    int *pi = &a;
    int **ppi = &pi;

    printf("%d\n", a);
    printf("%d\n", pi); //a�� �ּ�
    printf("%d\n", *pi); // 10 : a�� �ּҸ� ã�� ���� ����
    printf("%d\n", ppi); //pi�� �ּ�
    printf("%d\n", *ppi); //a�� �ּ�

	//10 : pi �ּ� ������ ã�ư��� ���� ����
    printf("%d\n", **ppi);
	
	return 0;
}
#endif

/***********************************************************/
// [15-2] ���� �����͸� Ȱ���� ���ڿ� ��ȯ
/***********************************************************/

#if 0
#include <stdio.h>

void swpa_pointer(char **ppa, char **ppb){
	int *temp;
	temp = *ppa;
	*ppa = *ppb;
	*ppb = temp;
}

int main(void)
{
	char *pa = "success";
	char *pb = "failure";

	printf("pa -> %s, pb -> %s\n", pa, pb);

	swap_pointer(&pa, &pb);
	printf("pa -> %s, pb -> %s\n", pa, pb);

	return 0;
}
#endif

/***********************************************************/
// [15-3] �迭 ������
/***********************************************************/

#if 0
#include <stdio.h>

void print_string(char **animals, int size){
	for(int i = 0; i < size; i++){
		printf("%s\n", animals[i]);
	}
}

int main(void)
{
	char *animal = {"dog"};

	printf("%s\n", animal);

	char *animals[4] = {"dog", "cat", "rabiit", "hippo"};
	// animals : ���ڿ� �迭, ���ڿ� ��ü�� �迭
	
	print_string(animals, 4);
	
	return 0;
}
#endif

/***********************************************************/
// [15-4] �迭�� �ּ�
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
	int array[5];
	printf("%d\n", array); // 0�� �ε��� �ּ�
	printf("%d\n", &array); // array�� �ּ҃�
	printf("%d\n", array + 1); // 1�� �ε��� �ּ�

	return 0;
}
#endif

/***********************************************************/
// [15-5] �迭 �����ͷ� 5 x 5 ���
/***********************************************************/

#if 0
#include <stdio.h>

void print_array(int (*ppa)[5])
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			printf("%3d", ppa[i][j]);
		}
		printf("\n");
	}
}

int main(void)
{
	int array[5][5];
	int count = 1;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			array[i][j] = count++;
		}
	}

	print_array(array);
	return 0;
}
#endif

/***********************************************************/
// [15-0] Ÿ��Ʋ
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
	
	return 0;
}
#endif

/***********************************************************/
// [15-7] �Լ� �����͸� ����� �Լ� ȣ��
/***********************************************************/

#if 0
#include <stdio.h>

int sum(int a, int b){
	return a + b;
}

int main(void)
{
	int result = 0;
	result =  sum(10, 20);

	printf("%d\n", result);

	int (*fp)(int, int);
	fp = sum;

	int result2 = fp(20, 30);
	printf("%d\n", result2);

	int result3 = (*sum)(30,40);
	printf("%d\n", result3);


	return 0;
}
#endif

/***********************************************************/
// [15-8] ����� ��� ���α׷� �����
/***********************************************************/

#if 0
#include <stdio.h>

int sum(int a, int b){
	return a + b;
}

int mul(int a, int b){
	return a * b;
}

int max(int a, int b){
	return a > b ? a : b;
}

//�Լ��� ����Ű�� �Լ�
void func(int (*fp)(int a, int b)){
	// sum�� �ѱ�� fp�� sumó�� �� �� �ִ�.
	int a = 0, b = 0;
	int result = 0;

	printf("�� ������ ���� �Է� �ϼ��� : ");
	scanf("%d %d", &a, &b);
	
	result = fp(a, b);

	printf("�ᱣ���� : %d\n", result);
}

int main(void)
{
	int menu = 0;

	printf("1 �� ������ ��\n");
	printf("2 �� ������ ��\n");
	printf("3 �� �������� ū �� ���\n");
	printf("���ϴ� ������ �����ϼ��� : ");
	scanf("%d", &menu);
	
	switch(menu){
		case 1 : func(sum); break;
		case 2 : func(mul); break;
		case 3 : func(max); break;
		default : return -1; break;
	}

	return 0;
}
#endif

/***********************************************************/
// [15-9] void ������ ���
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
	int a = 10;
	double b = 3.14;

	void *vp;
	vp = &a;

	printf("%d\n", *(int *)vp);

	vp = &b;
	printf("%.2lf\n", *(double *)vp);
	
	return 0;
}
#endif

