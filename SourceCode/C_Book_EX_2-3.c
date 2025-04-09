/* 
    작성자 : 윤치영
    작성일 : 2025.04.08. AM 12:53:00
    제목 : 제어 문자를 사용한 출력
*/

#include <stdio.h>

int main(){
    printf("Be Happy\n");
    printf("My\tfriend\n"); // \t = tep
    printf("Hello\tWorld!\n");
    printf("Goot\bd\tChance\n"); // \b = back space(커서 위치를 한칸 전으로 이동)
    printf("Cow\rW\a\n"); // \r = 캐리지 리턴(커서 위치를 맨 앞으로 이동), \a = 알람

    return 0;
}