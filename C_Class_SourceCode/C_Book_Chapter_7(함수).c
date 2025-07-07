/***********************************************************/
// [7-1]�� ������ ���� ��ȯ�ϴ� ���α׷�
/***********************************************************/

#if 0
#include <stdio.h>

// �Լ� ���� : �������� ���α׷��ֿ��� �޸� ������ �̸� �Ҵ�
//			  ���� �״�� �ۼ�, ���� ����
int function_sum(int a, int b);

int main(void)
{	

	printf("%d", function_sum(3,5));// �Լ� ȣ�� : �Լ���(��������, ��������)

	return 0;
}

//�Լ� ����
//- �Լ���
//- �Ű�����
//- ��ȯ��
int function_sum(int a, int b){
	return a + b;
}

#endif

/***********************************************************/
// [7-Ȯ��]	�� �Ǽ��� ����� ��ȯ�ϴ� �Լ�
/***********************************************************/

#if 0
#include <stdio.h>

double func_Average(double a, double b){
	return (a+b)/2;
}

int main(void)
{
	printf("%.2lf\n", func_Average(1.5, 3.4));
	return 0;
}
#endif

/***********************************************************/
// [7-2] �Ű������� ���� �Լ�
/***********************************************************/

#if 0
#include <stdio.h>

int get_num(void){
	int num;

	printf("��� �Է� : ");
	scanf("%d", &num);

	return num;
}

int main(void)
{
	int result;

	result = get_num();
	printf("��ȯ�� : %d\n", result);

	return 0;
}
#endif

/***********************************************************/
// [7-3] ��ȯ ���� ���� �Լ�
/***********************************************************/

#if 0
#include <stdio.h>

//���ڿ� ������ �����ϸ� ���η� ����ϴ� �Լ�!!
void print_char(char ch, int count){
	for(int i = 0; i < count; i++){
		printf("%c", ch);
	}
	printf("\n");
}

int main(void)
{
	for(int i = 1; i <= 5; i++){
		print_char('*', i);
	}

	return 0;
}
#endif

/***********************************************************/
// [7-4] �Ű������� ��ȯ���� ��� ���� �Լ�
/***********************************************************/

#if 0
#include <stdio.h>

void print_line(void);

int main(void)
{
	print_line();
	printf("�й�	�̸�	����	����\n");
	print_line();

	return 0;
}

void print_line(void){
	int i;
	for(int i = 0; i < 50; i++){
		printf("-");
	}
	printf("\n");
}


#endif

/***********************************************************/
// [7-5] ���ȣ�� �Լ�
/***********************************************************/

#if 0
#include <stdio.h>

int fibonacci(int num);

int main(void)
{
	// ����Լ��� �Լ� ȣ��Ƚ���� ���� ����
	// ���� �ӵ�, ���귮�� ���ϱ޼������� �þ��.
	printf("%d", fibonacci(20));
	return 0;
}

//�Ǻ���ġ ������ ���ϴ� �Լ�
//f(3) = f(1) + f(2)
//f(10) = f(8) + f(9)
int fibonacci(int num){
	if(num <= 2){
		return 1;
	}

	return fibonacci(num-1) + fibonacci(num-2);
}

#endif

/***********************************************************/
// [7-6] �Լ� ����1
/***********************************************************/

#if 0
#include <stdio.h>

int abs(int num);

int main(void)
{
	printf("%d", abs(-20));
	return 0;
}

// ������ ��ȯ�ϴ� abs �Լ�
int abs(int num){
	return num > 0 ? num : -num;
}

#endif

/***********************************************************/
// [7-7] ������ ���ϱ�.
/***********************************************************/

#if 1
#include <stdio.h>

int is_divisor(int num1, int num2);
void print_divisors(int num);
int get_sum_of_divisors(int num);
int is_perfect_number(int num);

int main(void)
{
	//step1
	// printf("%d\n", is_divisor(10,2));
	// printf("%d\n", is_divisor(10,3));

	//step2
	// print_divisors(10);
	// print_divisors(30);

	//step3
	// printf("%d\n", get_sum_of_divisors(10));
	// printf("%d\n", get_sum_of_divisors(28));

	//step4
	// printf("%d\n", is_perfect_number(10));
	// printf("%d\n", is_perfect_number(28));

	//end ù��° ������ 6, �ι�° ������ 28, ����° ?, �׹�°?
	for(int i = 2; i < 1000; i++){
		if(is_perfect_number(i))
		printf("%d\n", i);
	}// ������ ������ : 496

	for(int i = 1000; i < 10000; i++){
		if(is_perfect_number(i)){
			printf("%d\n", i);
		}
	}// �׹�° ������ : 8128

	return 0;
}

//������ ���ϱ� 
//step1
int is_divisor(int num1, int num2){
	return (num1 % num2 == 0 ? 1 : 0);
}

//step2
void print_divisors(int num){
	printf("%d�� ��� : ", num);
	for(int i = 1; i <= num / 2; i++){
		if(is_divisor(num,i)){
			printf("%d ", i);
		}
	}
	printf("%d\n", num);
}

//step3
int get_sum_of_divisors(int num){
	int result = 0;
	for(int i = 1; i <= num / 2; i++){
		if(is_divisor(num,i)){
			result += i;
		}
	}
	result += num;
	return result;
}

//step4
int is_perfect_number(int num){
	return num == (get_sum_of_divisors(num) - num) ? 1 : 0;
}

#endif
