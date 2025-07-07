/***********************************************************/
// [15-1] 이중 포인터
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
    int a = 10;
    int *pi = &a;
    int **ppi = &pi;

    printf("%d\n", a);
    printf("%d\n", pi); //a의 주소
    printf("%d\n", *pi); // 10 : a의 주소를 찾아 값을 참조
    printf("%d\n", ppi); //pi의 주소
    printf("%d\n", *ppi); //a의 주소

	//10 : pi 주소 번지를 찾아가서 값을 참조
    printf("%d\n", **ppi);
	
	return 0;
}
#endif

/***********************************************************/
// [15-2] 이중 포인터를 활용한 문자열 교환
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
// [15-3] 배열 포인터
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
	// animals : 문자열 배열, 문자열 자체도 배열
	
	print_string(animals, 4);
	
	return 0;
}
#endif

/***********************************************************/
// [15-4] 배열의 주소
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
	int array[5];
	printf("%d\n", array); // 0번 인덱스 주소
	printf("%d\n", &array); // array의 주소깂
	printf("%d\n", array + 1); // 1번 인덱스 주소

	return 0;
}
#endif

/***********************************************************/
// [15-5] 배열 포인터로 5 x 5 출력
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
// [15-0] 타이틀
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
	
	return 0;
}
#endif

/***********************************************************/
// [15-7] 함수 포인터를 사용한 함수 호출
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
// [15-8] 깔끔한 계산 프로그램 만들기
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

//함수를 가리키는 함수
void func(int (*fp)(int a, int b)){
	// sum을 넘기면 fp를 sum처럼 쓸 수 있다.
	int a = 0, b = 0;
	int result = 0;

	printf("두 정수의 값을 입력 하세요 : ");
	scanf("%d %d", &a, &b);
	
	result = fp(a, b);

	printf("결괏값은 : %d\n", result);
}

int main(void)
{
	int menu = 0;

	printf("1 두 정수의 합\n");
	printf("2 두 정수의 곱\n");
	printf("3 두 정수에서 큰 값 계산\n");
	printf("원하는 연산을 선택하세요 : ");
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
// [15-9] void 포인터 사용
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

