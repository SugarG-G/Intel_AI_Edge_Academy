/***********************************************************/
// [7-1]두 정수의 합을 반환하는 프로그램
/***********************************************************/

#if 0
#include <stdio.h>

// 함수 선언 : 절차지향 프로그래밍에서 메모리 공간을 미리 할당
//			  정의 그대로 작성, 몸통 없이
int function_sum(int a, int b);

int main(void)
{	

	printf("%d", function_sum(3,5));// 함수 호출 : 함수명(전달인자, 전달인자)

	return 0;
}

//함수 정의
//- 함수명
//- 매개변수
//- 반환형
int function_sum(int a, int b){
	return a + b;
}

#endif

/***********************************************************/
// [7-확인]	두 실수의 평균을 반환하는 함수
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
// [7-2] 매개변수가 없는 함수
/***********************************************************/

#if 0
#include <stdio.h>

int get_num(void){
	int num;

	printf("양수 입력 : ");
	scanf("%d", &num);

	return num;
}

int main(void)
{
	int result;

	result = get_num();
	printf("반환값 : %d\n", result);

	return 0;
}
#endif

/***********************************************************/
// [7-3] 반환 값이 없는 함수
/***********************************************************/

#if 0
#include <stdio.h>

//문자와 개수를 전달하면 가로로 출력하는 함수!!
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
// [7-4] 매개변수와 반환값이 모두 없는 함수
/***********************************************************/

#if 0
#include <stdio.h>

void print_line(void);

int main(void)
{
	print_line();
	printf("학번	이름	전공	학점\n");
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
// [7-5] 재귀호출 함수
/***********************************************************/

#if 0
#include <stdio.h>

int fibonacci(int num);

int main(void)
{
	// 재귀함수는 함수 호출횟수가 많을 수록
	// 연산 속도, 연산량이 기하급수적으로 늘어난다.
	printf("%d", fibonacci(20));
	return 0;
}

//피보나치 수열을 구하는 함수
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
// [7-6] 함수 연습1
/***********************************************************/

#if 0
#include <stdio.h>

int abs(int num);

int main(void)
{
	printf("%d", abs(-20));
	return 0;
}

// 절댓값을 반환하는 abs 함수
int abs(int num){
	return num > 0 ? num : -num;
}

#endif

/***********************************************************/
// [7-7] 완전수 구하기.
/***********************************************************/

#if 1
#include <stdio.h>

int is_divisor(int num1, int num2);
void print_divisors(int num);
int get_sum_of_divisors(int num);

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


	return 0;
}

//완전수 구하기 step1
int is_divisor(int num1, int num2){
	return (num1 % num2 == 0 ? 1 : 0);
}

//step2
void print_divisors(int num){
	printf("%d의 약수 : ", num);
	for(int i = 1; i <= num / 2; i++){
		if(num % i == 0){
			printf("%d ", i);
		}
	}
	printf("%d\n", num);
}

//step3 get_sum_of_divisors()
int get_sum_of_divisors(int num){
	int result = 0;
	for(int i = 1; i <= num / 2; i++){
		if(num % i == 0){
			result += i;
		}
	}
	result += num;
	return result;
}

//step4


#endif

/***********************************************************/
// [0-0] 타이틀
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
	
	return 0;
}
#endif

/***********************************************************/
// [0-0] 타이틀
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
	
	return 0;
}
#endif

/***********************************************************/
// [0-0] 타이틀
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
	
	return 0;
}
#endif

/***********************************************************/
// [0-0] 타이틀
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
	
	return 0;
}
#endif

/***********************************************************/
// [0-0] 타이틀
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
	
	return 0;
}
#endif

/***********************************************************/
// [0-0] 타이틀
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
	
	return 0;
}
#endif

/***********************************************************/
// [0-0] 타이틀
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
	
	return 0;
}
#endif

/***********************************************************/
// [0-0] 타이틀
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
	
	return 0;
}
#endif

/***********************************************************/
// [0-0] 타이틀
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
	
	return 0;
}
#endif

/***********************************************************/
// [0-0] 타이틀
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
	
	return 0;
}
#endif

/***********************************************************/
// [0-0] 타이틀
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
	
	return 0;
}
#endif

/***********************************************************/
// [0-0] 타이틀
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
	
	return 0;
}
#endif

/***********************************************************/
// [0-0] 타이틀
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
	
	return 0;
}
#endif
