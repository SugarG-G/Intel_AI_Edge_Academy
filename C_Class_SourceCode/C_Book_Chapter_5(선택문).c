/***********************************************************/
// [5-1] if문의 기본 형식
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
    int a;
    printf("나이 입력 : ");
	scanf("%d", &a);
    if(a >= 20){
        printf("성인입니다.");
    }
	return 0;
}
#endif

/***********************************************************/
// [5-2] 공배수 출력하기
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
    int a;
    printf("정수 입력 : ");
	scanf("%d", &a);

    if(a % 3 == 0 && a % 5 == 0){
        printf("3과 5의 배수 입니다.");
    }

	return 0;
}
#endif

/***********************************************************/
// [5-3] 성인 및 미성년자 여부 판단
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
    int age;
	printf("나이 입력 : ");
    scanf("%d", &age);

    if(age >= 20){
        printf("성인 입니다.");
    }
    else{
        printf("미성년자 입니다.");
    }

	return 0;
}
#endif

/***********************************************************/
// [5-4] 홀수 짝수 여부 판단하기
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
	int a;
    printf("정수 입력 : ");
    scanf("%d", &a);
    
    if(a%2==0){
        printf("짝수입니다.");
    }
    else{
        printf("홀수입니다.");
    }

	return 0;
}
#endif

/***********************************************************/
// [5-5] 마트 계산대 프로그램
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
	int a;
    printf("개수 입력 : ");
    scanf("%d", &a);

    if(a <= 10){
        printf("%d원입니다.", a*10000);
    }
    else{
        printf("%d원입니디.", (int)((a*10000 - (a*10000)*0.1)));
    }

	return 0;
}
#endif

/***********************************************************/
// [5-6] 학점 계산 프로그램
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
	int score;
    printf("학점 입력 : ");
    scanf("%d", &score);

    if(score >= 90){
        printf("A 학점");
    }
    else if(score >= 80){
        printf("B 학점");
    }
    else if(score >= 70){
        printf("C 학점");
    }
    else{
        printf("F 학점");
    }

	return 0;
}
#endif

/***********************************************************/
// [5-7] 마트 계산 프로그램 v2
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
    int a = 0, b = 0;
    printf("개수 입력 : ");
    scanf("%d", &a);
    printf("회원 여부(회원 : 1, 비회원 : 0)");
    scanf("%d", &b);

    if(a <= 10){
        
        if(b == 1){
            printf("%d원입니디.", (int)((a*10000)*(1-0.1)));
        }
        else{
            printf("%d원입니다.", a*10000);
        }
    }
    else{
        if(b == 1){
            printf("%d원입니디.", (int)(((a*10000*(1-0.1))*(1-0.1))));
        }
        else{
            printf("%d원입니디.", (int)((a*10000*(1-0.1))));
        }
        
    }

    
	return 0;
}
#endif

/***********************************************************/
// [5-7.5] switch란?
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
    /*
	switch(상수식){
        case 값 : 
            실행문장1;
        case 값 :
            실행문장2;
    }
    */
    int month = 4;

    switch(month){
        case 4 : 
            printf("봄\n");
            break;
        case 6 :
            printf("여름\n");
            break;
    }

	return 0;
}
#endif

/***********************************************************/
// [5-8] 상금 지급 프로그램
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
	int grade;
    
    printf("등수 입력 : ");
    scanf("%d", &grade);

    switch(grade){
        case 1 :
            printf("300만원");
            break;
        case 2 :
            printf("200만원");
            break;
        case 3 :
            printf("100만원");
            break;
    }
    /*
    if(grade == 1){
        printf("300만원");
    }
    else if(grade == 2){
        printf("200만원");
    }
    else{
        printf("100만원");
    }
    */

	return 0;
}
#endif

/***********************************************************/
// [5-확인] 자판기 프로그램 v3
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
	int money, choice;
    printf("금액을 입력하세요 : ");
    scanf("%d", &money);
    printf("[1]아침햇살(700원) [2]솔의눈(1000원) [3]데자와(500원)");
    scanf("%d", &choice);
    int price;
    int money_1000;
    int money_500;
    int money_100;
    int change;
    if(choice == 1){
        price = 700;
    }
    else if(choice == 2){
        price = 1000;
    }
    else if(choice == 3){
        price = 500;
    }

    change = money - price;

    if(change < 0){
        printf("돈이 부족해요 ㅠㅠ");
        change = money;
    }
    printf("잔돈 : %d\n", change);

    money_1000 = change / 1000;
    money_500 = change % 1000 / 500;
    money_100 = change % 500 / 100;
    
    printf("천원 : %d개, 오백원 : %d개, 백원 : %d개",money_1000, money_500, money_100);
	return 0;
}
#endif

/***********************************************************/
// [5-실전] 계산기 프로그램
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{   
    int a, b;
	char c;
    
    printf("사칙연산 입력(정수) : ");
    scanf("%d %c %d", &a, &c, &b);

    if(c == '+'){
        printf("%d%c%d=%d",a,c,b,a+b);
    }
    else if(c == '-'){
        printf("%d%c%d=%d",a,c,b,a-b);
    }
    else if(c == '*'){
        printf("%d%c%d=%d",a,c,b,a*b);
    }
    else if(c == '/'){
        printf("%d%c%d=%d",a,c,b,a/b);
    }
    else{
        return -1;
    }
	return 0;
}
#endif

