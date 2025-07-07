/***********************************************************/
// [9-1] 변수의 메모리 주소 확인
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
	int a;
    double b;
    char c;

    printf("int형 변수의 주소 : %u\n", &a);
    printf("double형 변수의 주소 : %u\n", &b);
    printf("char형 변수의 주소 : %u\n", &c);

	return 0;
}
#endif

/***********************************************************/
// [9-2] 포인터 선언과 사용
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
	int a;
    int *pa;

    pa = &a;

    printf("pa에 들어 있는 값 : %d\n", pa);

    a = 10;
    printf("포인터로 a 값 출력 : %d\n", a);

    *pa = 20; // * : 간접 참조 연산자
    printf("변수명으로 a 값 출력 : %d\n", a);

	return 0;
}
#endif

/***********************************************************/
// [9-3] 포인터를 사용한 두 정수의 합과 평균 계산
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


    // 1. pa, pb, pt, pg를 초기화.
    pa = &a, pb = &b, pt = &total, pg = &avg;
    // total에 a+b대입
    *pt = *pa + *pb;
    *pg = (double)*pt / 2;
    printf("두 정수의 값 : %d, %d\n", *pa, *pb);
    printf("두 정수의 총합 : %d\n", *pt);
    printf("두 정수의 평균 : %.1lf\n", *pg);
    

	return 0;
}
#endif

/***********************************************************/
// [9-4] 포인터에 const 사용
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
    const int num = 10; // const 붙은 변수는 선언과 동시에 초기화!!!
    int a = 10, b = 20;
    const int *pa = &a;

    printf("a의 값 : %d\n", *pa);

    pa = &b; // pa가 b의 주소를 가리킨다!!
    printf("b의 값 : %d\n", *pa);

    pa = &a;
    a = 7;
    printf("a의 값 : %d\n", *pa);
    
    // *pa = 77; // const로 포인터 설정 시 간접 참조 불가!!
    // printf("a의 값 : %d\n", *pa);

    return 0;
}
#endif

/***********************************************************/
// [9-5] 주소와 포인터의 크기
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
    char c;
    int a;
    double b;

    // 포인터는 반드시 변수와 데이터 자료형 일치
    char *pc = &c;
    int *pa = &a;
    double *pb = &b;

    // 주소의 크기
    printf("a주소 : %d, b주소 : %d, c주소 : %d\n", sizeof(&a), sizeof(&b), sizeof(&c));
    // 포인터의 크기
    printf("a포인터 : %d, b포인터 : %d, c포인터 : %d\n", sizeof(a), sizeof(b), sizeof(c));
    // 포인터가 가르키는 변수의 크기
    printf("a값 : %d, b값 : %d, c값 : %d\n", sizeof(*pa), sizeof(*pb), sizeof(*pc));

    return 0;
}
#endif

/***********************************************************/
// [9-6] 허용되지 않은 포인터의 대입
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
    int a = 10;
    int *pa = &a;
    
    double *pd;

    // pa는 a를 가르키는 int형 포인터
    // pd는 double형을 가르킬 수 있는 포인터

    // //주의) 형 변환처럼 사용 시 주소 범위 확인필요
    // pd = pa; //a의 주소를 가르킬 수 있게 pd에 대입
    // printf("%lf\n", *pd);

    int *pb;
    pb = pa;
    printf("%d\n", *pa);
    printf("%d\n", *pb);

	return 0;
}
#endif

/***********************************************************/
// [9-7] 포인터를 사용한 두 변수의 값 교환
/***********************************************************/

#if 0
#include <stdio.h>

void swap(int *pa, int *pb){
    int temp;

    //두 값을 치환후 출력;
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
// [9-8, 9] 다른 함수의 변수 사용하기
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
// [9-도전] 타이틀
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
	// 세 개의 정수 입력
    int max, mid, min;
    // 10 20 30
    scanf("%d %d %d", &max, &mid, &min);

    // 값 3개 넘길 시 가장 큰 값을 max
    // 중간 값을 mid
    // 가장 작은 값을 min으로 바꾸는 함수
    descending(&max, &mid, &min);

    printf("%d %d %d\n", max, mid, min); // 30 20 10 출력


	return 0;
}

#endif