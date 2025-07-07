/***********************************************************/
// [11-1] 대문자를 소문자로 변경
/***********************************************************/

#if 0
#include <stdio.h>

char lowercase(char ch){
    if('A' < ch && ch < 'Z'){
        return ch + ('a' - 'A');
    }
    else{
        return ch;
    }
}

int main(void)
{
    printf("%c\n", lowercase('H'));
	
	return 0;
}
#endif

/***********************************************************/
// [11-2] 공백이나 제어 문자의 입력
/***********************************************************/

#if 0
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
    // char ch1, ch2;

    // scanf("%c %c", &ch1, &ch2);
    // printf("[%d %d]", ch1, ch2);

    while(1){
        char ch;

        scanf("%c", &ch);
        
        if(ch == 10){
            break;
        }
        
        printf("%c", ch);
    }
    
	return 0;
}
#endif

/***********************************************************/
// [11-3] getchar, putchar
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
	int ch;

    while(1){
        ch = getchar();
        if(ch == 10){
            break;
        }
        putchar(ch);
    }
    
    // printf("입력한 문자 : ");
    // putchar(ch);

	return 0;
}
#endif

/***********************************************************/
// [11-3-가] scanf에 공백
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
    char ch;
	for(int i = 0; i < 5; i++){
        scanf(" %c", &ch); //%앞에 공백 삽입 시 > 화이트 스페이스 무시!!
        printf("%c", ch);
    }

	return 0;
}
#endif

/***********************************************************/
// [11-4] 버퍼를 사용한 문자 입력
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
    while(1){
        char ch;
        scanf("%c", &ch);
        if(ch == 10){
            break;
        }
        printf("%c", ch);
    }

	return 0;
}
#endif

/***********************************************************/
// [11-5] 입력 문자의 아스키 코드를 출력하는 프로그램
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
    int result;
    char ch;

    while(1){
        result = scanf("%c", &ch);
        if(result == EOF) break;
        printf("%d ", ch);
    }
	
	return 0;
}
#endif

/***********************************************************/
// [11-6] getchar 함수를 사용한 문자열 입력
/***********************************************************/

#if 0
#include <stdio.h>

void my_getchar(char *str, int size){
    //Hello World!! -> Hello (\0)
    //chocobanana -> chocob
    for(int i = 0; i < size - 1; i++){
        str[i] = getchar();
        if(str[i] == '\n'){
            str[i + 1] = '\0';
            break;
        }
    }
    str[size] = '\0';
}

int main(void)
{
    char str[7];
    my_getchar(str, 7);
	printf("입력한 문자열 : %s\n", str);

	return 0;
}
#endif

/***********************************************************/
// [11-7] 버퍼 초기화
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
    int num;
    int grade;
    // scanf()와 getchar()는 버퍼를 공유한다.
    printf("학번 입력 : ");
    scanf("%d", &num);
    printf("학점 입력 : ");
    
    //입력 버퍼 사용 시 주의사항
    //잘 모르겠으면 버퍼를 초기화 하자
    getchar();

    grade = getchar();
    
    printf("학번 : %d, 학점 : %c", num, grade);
	
	return 0;
}
#endif

/***********************************************************/
// [11-도전] 길이가 가장 긴 단어 찾기
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
    int ch, max = 0, len;
    while(1){
        
        ch = getchar(); // 전체 입력의 종료를 판단.
        if(ch == -1) break;

        len = 0;

        while(1){
            if(ch == '\n'){
                break;
            }
            ch = getchar();
            len++;
        }
        if(max < len){
            max = len;
        }
    }
    printf("%d", max);
}
#endif