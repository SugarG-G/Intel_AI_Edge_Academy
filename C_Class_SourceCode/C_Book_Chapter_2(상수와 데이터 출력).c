/* 
    작성자 : 윤치영
    작성일 : 2025.04.08. AM 12:42:00
    제목 : 10과 20을 더하는 프로그램
*/
#if 0
int main() 
{
    10 + 20;

    return 0;
}
#endif

/* 
작성자 : 윤치영
작성일 : 2025.04.08. AM 12:47:00
제목 : 문자열을 화면에 출력하는 프로그램
*/
#if 0

#include <stdio.h>

int main(){
    printf("Be Happy");
    printf("My friend");

    return 0;
}
#endif

/* 
    작성자 : 윤치영
    작성일 : 2025.04.08. AM 12:53:00
    제목 : 제어 문자를 사용한 출력
*/
#if 0
#include <stdio.h>

int main(){
    printf("Be Happy\n");
    printf("My\tfriend\n"); // \t = tep
    printf("Hello\tWorld!\n");
    printf("Goot\bd\tChance\n"); // \b = back space(커서 위치를 한칸 전으로 이동)
    printf("Cow\rW\a\n"); // \r = 캐리지 리턴(커서 위치를 맨 앞으로 이동), \a = 알람

    return 0;
}
#endif

/* 
    작성자 : 윤치영
    작성일 : 2025.04.08. AM 14:09:00
    제목 : 정수와 실수의 출력
*/

#if 0

#include <stdio.h>

int main(){
    printf("%d\n", 10);
    printf("%lf\n", 3.4);
    printf("%.1lf\n", 3.45); // .1lf소수점 이하 첫째 자리까지 출력 (반올림)
    printf("%.10lf\n", 3.4);

    printf("%d과 %d의 합은 %d입니다.\n", 10, 20, 10 + 20);
    printf("%.lf - %.1lf = %.1lf\n", 3.4, 1.2, 3.4 - 1.2);
    printf("%.lf - %.1lf = %.1lf\n", 3.3, 1.1, 3.3 - 1.1);

    return 0;
}
#endif

/* 
    작성자 : 윤치영
    작성일 : 2025.04.08. AM 14:30:00
    제목 : 3가지 진법의 정수 상수
*/

#if 0

#include <stdio.h>

int main(){
    printf("%d\n", 12);
    printf("%d\n", 014);
    printf("%d\n", 0xc);

    printf("%o\n", 100);
    printf("%x\n", 100);
    printf("%X\n", 100);

    return 0;
}
#endif

/* 
    작성자 : 윤치영
    작성일 : 2025.04.08. AM 14:46:00
    제목 : 문자와 문자열 데이터의 출력
*/

#if 0

#include <stdio.h>

int main(){
    printf("%c\n", 'A');
    printf("%s\n", "A");
    printf("%c은 %s 입니다.", '1', "first");
    
    return 0;
}

#endif