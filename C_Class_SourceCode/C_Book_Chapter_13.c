/***********************************************************/
// [13-1] 두 함수에서 같은 이르므이 지역 변수를 사용한 경우
/***********************************************************/

#if 0
#include <stdio.h>

// 컴파일러
// C언어를 사용할 수 있는 프로그램

// Vistual Studio
// -> IDE (Intergrated Development Envornment) 통합개발환경

// 프로그래밍 언어 -> C
// IDE -> VS

// 에러 2가지 카테고리
// 1. 컴파일 전 알 수 있는 에러 -> IDE가 빨간펜
// 2. 컴파일 후 알 수 있는 에러

void assign(void){
    auto int a = 20;
    printf("assign 함수 내 a의  값 : %d\n");
}

int main(void)
{
	auto int a = 10;
    printf("a의 값 : %d\n", a);

    assign();
    printf("a의 값 : %d\n", a);

	return 0;
}
#endif

/***********************************************************/
// [13-2] 블록 안에서 사용하는 지역 변수
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
    int a = 10;
    printf("here1 a의 값 : %d\n", a); // 10
    {
        int a = 20;
        printf("here2 a의 값 : %d\n", a);
        {
            int a = 30;
            printf("here3 a의 값 : %d\n", a);
        }
    }
    return 0;
}
#endif

/***********************************************************/
// [13-3] 전역 변수의 사용
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
    // 지역 변수 -> 초기화가 안되어 있으면 사용 안됨
    // int b;
    // printf("%d", b);

    //전역 변수는 컴파일러가 자동으로 초기화
    // int > 0, double > 0.0, char > 0
    printf("함수 호출 전 전역 변수 a의 값 : %d\n", a);
    assign10();
    assign20();
    printf("함수 호출 전 전역 변수 a의 값 : %d\n", a);
	
	return 0;
}
#endif

/***********************************************************/
// [13-4] 정적 지역 변수
/***********************************************************/

#if 0
#include <stdio.h>

void print_star(){
    // static 함수 블럭이 살아지더라도 메모리에 존재
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
// [13-5] 레지스터 변수
/***********************************************************/

#if 0
#include <stdio.h>
#include <time.h> // clock()

int main(void)
{
    // 약수의 합
    // 100 > 100의 약수의 합 sum에 저장

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
    printf("%d의 약수의 합 : %lld\n", num, sum);
    long end = clock();

    // time : for문 실행 시간 (s)
    double time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("소요 시간 : %lfs\n", time);

    return 0;
}
#endif

/***********************************************************/
// [13-6] 값을 복사해서 전달
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
    
    printf("함수 호출 전 a : %d\n", a);
    a = add_ten(a);
    printf("함수 호출 후 a : %d\n", a);
	
	return 0;
}
#endif

/***********************************************************/
// [13-7] 주소를 전달
/***********************************************************/

#if 0
#include <stdio.h>

void add_ten(int *pa){
    *pa = *pa + 10;
}

int main(void)
{
    int a = 10;
    printf("함수 호출 전 a : %d\n", a);
    add_ten(&a);
	printf("함수 호출 후 a : %d\n", a);
	return 0;
}
#endif

/***********************************************************/
// [13-8] 주소를 반환하는 함수
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
    printf("두 정수의 합 : %d\n", *presult);
	
	return 0;
}
#endif

/***********************************************************/
// [13-도전] 전역 변수 교환 프로그램
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

