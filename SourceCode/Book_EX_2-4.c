/* 
    작성자 : 윤치영
    작성일 : 2025.04.08. AM 14:09:00
    제목 : 정수와 실수의 출력
*/

#include <stdio.h>

int main(){
    printf("%d\n", 10);
    printf("%lf\n", 3.4);
    printf("%.1lf\n", 3.45); // .1lf소수점 이하 첫째 자리까지 출력 (반올림)
    printf("%.10lf\n", 3.4);

    printf("%d°? %d?? ???? %d??´?´?.\n", 10, 20, 10 + 20);
    printf("%.lf - %.1lf = %.1lf\n", 3.4, 1.2, 3.4 - 1.2);
    printf("%.lf - %.1lf = %.1lf\n", 3.3, 1.1, 3.3 - 1.1);

    return 0;
}