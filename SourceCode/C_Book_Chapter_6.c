/***********************************************************/
// [6-1]자릿수 계산 프로그램
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
	int digits = 0;
    int num;
    printf("정수 입력 : ");
    scanf("%d", &num);

    //보통 반복 횟수가 정해져 있지 않을 때 while 사용
    //보통 반복 횟수가 정해져 있을 때 for 사용
    while(num != 0){
        digits++;
        num = num / 10;
    }

    printf("%d자리 정수입니다.", digits);

	return 0;
}
#endif

/***********************************************************/
// [6-2] 10보다 작은 값 입력 프로그램
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
    int a;
    printf("정수 입력 : ");
    scanf("%d", &a);
    while(a < 10){
        printf("정수 입력 : ");
        scanf("%d", &a);
    }
    printf("종료되었습니다.");

	return 0;
}
#endif

/***********************************************************/
// [6-3] 누적합 출력 프로그램
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
	int num, sum = 0;
    printf("정수 입력 : ");
    scanf("%d", &num);

    while(num != -1){
        sum += num;
        printf("누적 결과 : %d\n", sum);
        printf("정수 입력 : ");
        scanf("%d", &num);
    }
    printf("종료되었습니다.");

	return 0;
}
#endif

/***********************************************************/
// [6-4] for문 연습
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
    /*
    for(초기식; 조건식; 증감식){
        실행문장;
    }
    */
    // 1 ~ 10까지 출력

    for (int i = 1; i <= 10; i++)
    {
        printf("%d ", i);
    }
    printf("\n");

    // 27 ~ 57까지 출력

    for (int i = 27; i <= 57; i++)
    {
        printf("%d ", i);
    }
    printf("\n");

    // 96 ~ 53까지 역순 출력
    for (int i = 96; i >= 53; i--)
    {
        printf("%d ", i);
    }
    printf("\n");

    // 1 ~ 100까지 중 3의 배수만 출력
    // 1 ~ 100까지 중 3의 배수이면서 5의 배수만 출략
    // 1 ~ 100까지 중 3의 배수이면서 5의 배수인 수를 제외하고 출력
    for (int i = 1; i <= 100; i++)
    {
        if (i % 3 == 0 && i % 5 == 0)
        {
            continue;
        }
        printf("%d ", i);
    }

    return 0;
}
#endif

/***********************************************************/
// [6-5] 배수 출력하기
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
    int a;
    printf("자연수를 입력하세요 : ");
    scanf("%d", &a);

    for (int i = 1; i <= 10; i++)
    {
        printf("%d ", a * i);
    }

    return 0;
}
#endif

/***********************************************************/
// [6-6] 구구단 출력하기
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
	for(int i = 1; i <= 9; i++){
        printf("%d x %d = %d\n",2, i, 2*i);
    }
	return 0;
}
#endif

/***********************************************************/
// [6-7] 약수 출력하기
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
    int number;
	printf("정수를 입력해주세요 : ");
    scanf("%d", &number);

    for(int i = 1; i <= number / 2; i++){
        if(32%i == 0){
            printf("%d ", i);
        }
    }
    printf("%d", number);

	return 0;
}
#endif

/***********************************************************/
// [6-권장] 권장 규칙
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
	//초기식 조건식 증감식은 알기 쉽게 한다.
    for(int i = 7; i <= 16; i++){
        printf("%d", i - 6);
    }
	return 0;
}
#endif

/***********************************************************/
// [6-유지보수] 누적합 do ~ while
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
    int sum = 0;
    int num;
    do{
        
        printf("정수 입력 : ");
        scanf("%d", &num);

        printf("누적 합계 : %d\n", sum += num);
    }
    while(num != -1);

	return 0;
}
#endif
/***********************************************************/
// [6-많이써요] 무한반복문
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
    int num, sum = 0;

    while(1){
        printf("정수 입력 : ");
        scanf("%d", &num);
        if(num == -1){
            break;
        }

        sum += num;

        printf("누적 합계 : %d\n", num);
    }

	return 0;
}
#endif

/***********************************************************/
// [6-8] 다이어트 관리 프로그램
/***********************************************************/

#if 0

#include <stdio.h>

int main(void)
{
	int current_weight = 0, goal_weight = 0;
    int week_weight = 0, loss_weight = 0;
    int week = 0;

    printf("현재 몸무게 : ");
    scanf("%d", &current_weight);
    printf("목표 몸무게 : ");
    scanf("%d", &goal_weight);
    
    while(1){
        week++;
        printf("%d주차 감량 몸무게 : ", week);
        scanf("%d", &loss_weight);
        current_weight -= loss_weight;
        if(goal_weight >= current_weight){
            printf("%dkg 달성!!", current_weight);
            break;
        }
    }
    printf("축하합니다.");

	return 0;
}
#endif

/***********************************************************/
// [6-9] 로그인 프로그램
/***********************************************************/

#if 0
#include <stdio.h>
#include <string.h>

int main(void)
{
    // 시간 나시면 해보셔요!!
    // 기본 자료형
    // 정수형 : short, int, long, long long
    // 실수형 : float, double, long double
    // 문자형 : char
    // 관계 연산 (비교 연산)
    // 크니? 작니? 같니?

    char fruit[20] = "banana";
    char fruit2[20] = "banana";
    if (fruit == fruit2) // 기본 자료형이 아니기 때문에 비교 불가
    {
        printf("같습니다");
    }
    // <string.h> 안에 strcmp()
    // 0 : 두 문자열이 같다

    printf("%d", strcmp(fruit, fruit2));

    char login_id[20] = "nayeho";
    char login_pw[20] = "1234";

    while (1)
    {
        char id[20], pw[20];
        printf("ID : ");
        scanf("%s", id);
        printf("PW : ");
        scanf("%s", pw);

        if (!strcmp(id, login_id) && !strcmp(pw, login_pw) == 1)
        {
            printf("로그인 성공");
            break;
        }
        else
        {
            printf("로그인 실패");
        }
    }
    return 0;
}
#endif

/***********************************************************/
// [6-10] up-down 프로그램
/***********************************************************/

#if 0
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    srand(time(NULL));

    int random_number = rand() % 100 + 1;
    int a;
    // printf("%d",random_number);
    while(1){
        printf("정수 입력 : ");
        scanf("%d", &a);

        if(a < random_number){
            printf("입력한 숫자보다 큽니다.\n");
        }
        else if(a > random_number){
            printf("입력한 숫자보다 작습니다.\n");
        }
        else if (a == random_number){
            printf("정답\n");
            break;
        }
    }

	// printf("%d\n", rand() % 100 + 1);
    // printf("%d\n", rand() % 100 + 1);

	return 0;
}
#endif

/***********************************************************/
// [6-11] 별찍기 기초
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
	for(int i = 0; i < 5; i++){
        for(int j = 0 ; j < 5; j++){
            printf("*");
        }
        printf("\n");
    }
	return 0;
}
#endif

/***********************************************************/
// [6-12] 구구단 프로그램
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
	for(int i = 2; i <= 9; i++){
        for(int j = 1; j <= 9; j++){
            printf("%d x %d = %d\n", i, j, i * j);
        }
    }
	return 0;
}
#endif

/***********************************************************/
// [6-13] 별찍기 응용 1
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
	for(int j = 0; j < 5; j++){
        for(int i = 0; i <= j; i++){
            printf("*");
        }
        printf("\n");
    }
	return 0;
}
#endif

/***********************************************************/
// [6-14] 별찍기 응용 2
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
    for (int j = 0; j < 5; j++)
    {
        for (int i = j; i < 5; i++)
        {
            printf(" ");
        }
        for (int k = 0; k <= j; k++)
        {
            printf("*");
        }
        printf("\n");
    }

    return 0;
}
#endif

/***********************************************************/
// [6-15] 별찍기 응용 5
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
    for (int j = 1; j <= 5; j++)
    {
        for (int i = 1; i <= j - 1; i++)
        {
            printf(" ");
        }
        for (int i = 1; i <= 6 - j; i++)
        {
            printf("*");
        }
        printf("\n");
    }
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