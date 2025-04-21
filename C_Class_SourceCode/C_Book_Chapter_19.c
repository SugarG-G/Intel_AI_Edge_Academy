/***********************************************************/
// [0-0] 타이틀
/***********************************************************/
#include <stdio.h>
#include "student.h" // 절대경로 상대경로 모두 사용가능

// 매크로
#define PI 3.141592
#define UNIT "cm^2"
#define SUCCESS_PRINT printf("면적 구하기 성공 \n")

#define SUM(a, b) (a + b)
#define MUL(a, b) (a * b)

#define NAME_CAT(x, y) (x##y)

#define VER 7 //버전
#define BIT16 // 정수 표현 범위


int main(void)
{

#if VER >= 6
    printf("버전 %d입니다.\n", VER);
#endif

    int max;

#ifdef BIT16
    max = 32767;
#else
    max = 2147483647;
#endif

    printf("정수형의  최대 범위 : %d\n", max);

    //이미 만들어져 있는 매크로
    printf("컴파일 날짜 : %s\n", __DATE__);
    printf("컴파일 날짜 : %s\n", __TIME__);
    printf("파일명 : %s\n", __FILE__);
    printf("함수명 : %s\n", __FUNCTION__);
    printf("행번호 : %d\n", __LINE__);

#line 2025 "macro.c"
    printf("파일명 : %s\n", __FILE__);
    printf("행번호 : %d\n", __LINE__);

    for (int i = 1; i <= 3; i++)
    {
        int NAME_CAT(score, i);
        NAME_CAT(score, i) = i * 10;
        printf("%d\n", NAME_CAT(score, i));
    }

    int score1 = 10;
    int score2 = 20;
    int score3 = 30;

    int result = SUM(2, 5);
    printf("%d\n", result);

    int result2 = 30 / MUL(2, 5);
    printf("%d\n", result2);

    int r;
    printf("반지름을 입력하세요 : ");
    scanf("%d", &r);

    double area = PI * r * r;

    printf("원의 넓이는 %.2lf%s\n", area, UNIT);
    SUCCESS_PRINT;

    Student s1;

    s1.num = 315;
    s1.grade = 3.7;

    return 0;
}
