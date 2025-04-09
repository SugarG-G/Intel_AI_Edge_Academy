/***********************************************************/
// [3-0] 변수를 사용하는 이유
/***********************************************************/
#if 0
#include <stdio.h>

int main(){
    // 15 > 20, 5 > 6 매번 값을 변경 해야함
    printf("%d + %d = %d\n", 20, 6, 20 + 6);
    printf("%d - %d = %d\n", 20, 6, 20 - 6);
    printf("%d * %d = %d\n", 20, 6, 20 * 6);
    printf("%d / %d = %d\n", 20, 6, 20 / 6);
    
    return 0;
}
#endif

/***********************************************************/
// [3-1] 변수의 선언과 사용
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
	int a;  
    a = 10;
    
    // 1. 정수형 변수 b와 c를 선언(int로)
    // 2. 실수형 변수 da 선언 (double로)
    // 3. 문자형 변수 ch 선언 (char로)
    // 4. a에 들어 있는 값으로 b를 초기화
    // 5. a에 들어 있는 값에 20을 더해 c를 초기화
    // 6. da를 3.5로 초기화
    // 7. ch를 'A'로 초기화
    // 모든 변수 출력!!

    int b, c;
    double da;
    char ch;

    b = a;
    c = a + 20;
    da = 3.5;
    ch = 'A';

    printf("%d %d %d %.1lf %c", a, b, c, da, ch);

	return 0;
}
#endif

/***********************************************************/
// [3-2] char형 변수의 사용
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
	char ch1 = 'A';
    char ch2 = 65;

    printf("문자 %c의 아스키 코드 값 : %d\n", ch1, ch2);
    printf("아스키 코드 값이 %d인 문자 : %c\n",ch1, ch2);

	return 0;
}
#endif

/***********************************************************/
// [3-3] 여러가지 정수형 변수
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
	short sh =32767;
    int in = 2147483647;
    long ln = 2147483647;
    long long lln = 123451234512345;

    printf("short형 변수 출력 : %d\n", sh);
    printf("int형 변수 출력 : %d\n", in);
    printf("long형 변수 출력 : %ld\n", ln);
    printf("long long형 변수 출력 : %lld\n", lln); //long long 형은 lld로 출력


    short menu = 10000;
    int lotto = 2000000000;
    long people = 50000000;
    long long world_people = 7000000000;

    printf("short형 변수 출력 : %d\n", menu);
    printf("int형 변수 출력 : %d\n", lotto);
    printf("long형 변수 출력 : %ld\n", people);
    printf("long long형 변수 출력 : %lld\n", world_people); //long long 형은 lld로 출력



	return 0;
}
#endif

/***********************************************************/
// [3-4] unsigned를 잘못 사용한 경우
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
	unsigned int a;

    a = 4294967295;
    printf("%d\n", a);
    printf("%u\n", a); //unsinged 출력은 %u로 한다.
    
    a = -1;
    printf("%u\n", a);

	return 0;
}
#endif

/***********************************************************/
// [3-5] 유효 숫자 확인
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
    //선언과 동시에 초기화 가능!!
    float ft = 1.234567890123456789;
    double db = 1.234567890123456789;

    printf("%.20f\n", ft);
    printf("%.20lf\n", db);

    long double ldb = 1.234567890123456789;

    printf("%.20llf\n", ldb);

    return 0;
}
#endif

/***********************************************************/
// [3-6] char 배열에 문자열 저장
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
    // 배열 : []로 사용
    // 반드시 크기가 할당!!
    // char 변수명[크기] -> 문자열 (string)
    // 문자열은 C언어에서 구분하기 위해
    // 끝에 널 문자('\0') 이 들어간다!!

    // 기본 자료형   
    // 정수형 : short, int, long, long long
    // 실수형 : float, double, long double
    // 문자형 : char
    char fruit[20] = "strawberry";

    printf("딸기 : %s\n", fruit);
    printf("딸기잼 : %s %s\n", fruit, "jam");

	return 0;
}
#endif

/***********************************************************/
// [3-7] char 배열의 문자열 복사
/***********************************************************/

#if 0
#include <stdio.h>
#include <string.h> //문자열 관련 기능을 포함하고있다.
//strcpy()를 사용
// #define _CRT_SECURE_NO_WARNINGS;

int main(void)
{
	char fruit[20] = "banana";
    strcpy(fruit, "choco"); //fruit 문자열에 "choco" 문자를 복사해 덮어쓰기함
    
    printf("%s\n", fruit);

	return 0;
}
#endif

/***********************************************************/
// [3-8] const를 사용한 변수
/***********************************************************/

#if 1
#include <stdio.h>

int main(void)
{
	int income = 0;
    double tax;
    const double tax_rate = 0.065;

    income = 400;
    tax = income * tax_rate;
    
    printf("세금은 : %.1lf입니다.\n", tax);
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