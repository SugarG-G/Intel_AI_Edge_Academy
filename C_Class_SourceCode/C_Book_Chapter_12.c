/***********************************************************/
// [12-1] 문자열은 문자열 배열??
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
    int array[5] = {10, 20, 30, 40, 50};
    int *pa = array;
    printf("%p\n", array);
    printf("%p\n", pa);
    
    char fruit[6] = {'a', 'p', 'p', 'l', 'e', '\0'};
    char fruit2[6] = "apple";
    printf("%s\n", fruit);
    printf("%s\n", fruit2);

    char *pc = fruit;
    char *pc2 = fruit2;

    printf("%p\n", pc);
    printf("%p\n", pc2);

	return 0;
}
#endif

/***********************************************************/
// [12-2] 포인터로 문자열 사용
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
    char drink[100] = "coke";
    char *pc = drink;
    /*
    // printf("%c\n", pc[0]);
    while(1){
        if(*pc == '\0'){
            break;
        }
        printf("%c",*(pc++));
    }
    */

    while(*pc) printf("%c",*(pc++));

	return 0;
}
#endif

/***********************************************************/
// [12-잠깐] 같은 문자열 상수???
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
    char fruit[6] = {'a', 'p', 'p', 'l', 'e', '\0'};
    char fruit2[6] = "apple";
    char fruit3[6] = "apple";

    printf("%p\n", fruit);
    printf("%p\n", fruit2);
    printf("%p\n", fruit3);

    char *pc = fruit;
    char *pc2 = fruit2;
    char *pc3 = fruit3;

    printf("%p\n", pc);
    printf("%p\n", pc2);
    printf("%p\n", pc3);

	return 0;
}
#endif

/***********************************************************/
// [12-3] scanf를 사용한 문자열 입력
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
    char str[100];
    printf("문자열 입력 : ");
    
    scanf("%s", str);
    printf("%s\n", str);

    scanf("%s", str);
    printf("%s", str);
    

    return 0;
}
#endif

/***********************************************************/
// [12-4] gets 함수로 한 줄의 문자열 입력
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
    char str[100];

    printf("문자열 입력 : ");
    gets(str); //엔터를 제외한 tap, 공백 입력 가능
    printf("%s", str);

	return 0;
}
#endif

/***********************************************************/
// [12-5] gets의 안정성 보장을 위한 fgets
/***********************************************************/

#if 0
#include <stdio.h>
#include <string.h>

int main(void)
{
    char str[100];
    printf("문자열 입력 : ");
    fgets(str, sizeof(str), stdin); //키보드로 입력 하겠다.
    printf("문자열 길이 : %d\n", strlen(str) - 1); // fgets로 입력 받을 때 문자열 길이는 -1 해주어야한다.
    
    // 문자열을 제외한 자료구조 배열에서는 배열의 요소 개수를 sizeof(배열명) / sizeof(자료형)으로 구했지만 문자열에서는 구하기 어렵다.
    printf("문자열 길이 2 : %d\n", sizeof(str) / sizeof(char)); 
    
    printf("입력한 문자열 : %s\n", str);
    
    printf("%s", str);

    
    
	return 0;
}
#endif

/***********************************************************/
// [12-6] 개행 문자로 인해 get 함수가 입력 안되는 경우
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
	int age;
    char name[20];
    
    printf("나이 입력 : ");
    scanf("%d", &age);
    
    printf("이름 입력 : ");
    // gets 함수 사용정 버퍼 초기화 필요
    // 초기화 방법 3가지 교재 p.358 참고
    // 1. getchar(); 2. scanf("%*c"); %*c : 주소 생략 후 char 읽기 3. fgetc(stdin);
    getchar();

    gets(name);

    printf("나이 : %d, 이름 : %s\n", age, name);

	return 0;
}
#endif

/***********************************************************/
// [12-7] 문자열을 출력하는 puts와 fputs함수
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
    char str[100] = "apple juice";
    
    // char str2[] = "banana";
    // char *ps = str2;
    // ㄴ char *ps = "banana";로 생략가능
    char *ps = "banana";

    //puts > 자동 줄바꿈 o
    //fputs > 자동 줄바꿈 x

    puts(str);
    puts(ps);

    fputs(str, stdout); // 모니터를 통해 표준 출력
    fputs(ps, stdout);

    return 0;
}
#endif

/***********************************************************/
// [12-직접] gets 함수 구현해보기!!
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
	int i = 0;
    char str[20]; // "apple" 입력
    char *ps = str;
    // getchar() 활용해 gets() 구현
    // getchar() > 문자 하나하나 입력

    //gets() 시작
    while(1){
        
        str[i] = getchar();
        if(str[i] == '\n'){
            str[i + 1] = '\0';
            i = 0;
            break;
        }
        i++;
    }
    //gets() 끝

    printf("%s", str); // apple 출력


    //포인터로 구현
    int ch;
    while(1){
        ch = getchar();
        *(ps++) = ch;
        if(ch == '\n'){
            break;
        }
    }
    *ps = '\0';

    printf("%s", str); // apple 출력
	return 0;
}
#endif

/***********************************************************/
// [12-8] 문자열을 대입하는 strcpy 함수
/***********************************************************/

#if 0
#include <stdio.h>
#include <string.h>

int main(void)
{
	char str[80] = "strawberry";
    printf("%s\n", str);
    // str = "banana"; // 오류
    /*
    str[0] = 'b';
    str[1] = 'a';
    str[2] = 'n';
    str[3] = 'a';
    str[4] = 'n';
    str[5] = 'a';
    str[6] = '\0';
    
    printf("%s\n", str);
    printf("%c\n", str[8]);
    */

    strcpy(str, "banana"); // strcpy(복사할곳, 내용);
    printf("%s\n", str);

    char *ps = str;
    ps = "kiwi";
    printf("%s\n", ps); // 포인터로 내용 변경시 다른 포인터로 변환.
    printf("%s\n", str);

	return 0;
}
#endif

/***********************************************************/
// [12-9] n개의 문자열을 복사하는 strncpy()
/***********************************************************/

#if 0
#include <stdio.h>
#include <string.h>

int main(void)
{
    char str[90] = "strawberry";

    strncpy(str,"mango", 5);
    printf("%s\n", str);

    char *ps = "chocolate";

    strncpy(str, ps, 5);
    printf("%s\n", str);

    char str2[90] = "melon_top_100";
    strncpy(str, str2, 5);
    printf("%s\n", str);
    
	return 0;
}
#endif

/***********************************************************/
// [12-8-직접구현] strcpy()
/***********************************************************/

#if 0
#include <stdio.h>

//d : destination s : source
char *my_strcpy(char *pd, char *ps){
    char *po;
    po = pd;

    while(*ps){
        *(po++) = *(ps++);
        // if(*ps == '\0'){
        //     break;
        // }
    }
    *po = '\0';

    return po;
}

int main(void)
{
    char str[90] = "strawberry";
    printf("바꾸기 전 문자열 : %s\n", str);

    //배열을 다룰 때 크기를 넣는 이유
    // ㄴ> 다른 함수에서 원래 배열의 크기를 못 보기 때문
    //문자열 배열 -> 다른 함수에서 문자열 크기 볼 수 있을 까요? 가능
    //널 문자까지 개수를 세면 -> 문자열의 크기
    my_strcpy(str, "mango");
    printf("바뀐 후 문자열 : %s\n", str); // mango;
	
	return 0;
}
#endif

/***********************************************************/
// [12-10] 문자열을 연결하는 strcat() 
/***********************************************************/

#if 0
#include <stdio.h>
#include <string.h> //strcat()

int main(void)
{
    // straw + berry
    // python, Jave
    // str1 + str2 가능
    char str[90] = "straw";
    
    strcat(str,"berry");
    printf("%s\n", str);

    char *pi = " ice-cream";
    strcat(str, pi);
    printf("%s\n", str);

    char str2[90] = "cake dessert yogurt";
    strncat(str, str2, 4);
    printf("%s\n", str);

	return 0;
}
#endif

/***********************************************************/
// [12-10-직접 구현] my_strcat() 만들기
/***********************************************************/

#if 0
#include <stdio.h>
// #include <string.h>

char *my_strcat(char *pd, char *ps){
    char *pc;
    pc = pd;

    while(*pc != 0) *(pc++);
    while(*ps != 0) *(pc++) = *(ps++);
    
    *pc = '\0';
    return pc;
}

int main(void)
{
    char str[80] = "straw";

	my_strcat(str, "berry");
    printf("%s\n", str);
	return 0;
}
#endif

/***********************************************************/
// [12-11] 문자열 길이 strlen()
/***********************************************************/

#if 0
#include <stdio.h>
#include <string.h> //strlen()

int main(void)
{
    char str1[90], str2[90];

    printf("두 과일 입력(과일1 과일2) : ");
    scanf("%s %s", str1, str2);

    printf("첫 번째 과일 : %s\n", str1);
    printf("두 번째 과일 : %s\n", str2);
	
    if(strlen(str1) > strlen(str2)){
        printf("%s 이름이 더 깁니다.\n", str1);
    }
    else printf("%s 이름이 더 깁니다.\n", str2);
    

	return 0;
}
#endif

/***********************************************************/
// [12-11-직접] my_strlen() 만들기
/***********************************************************/

#if 0
#include <stdio.h>
#include <string.h>

int my_strlen(char *str){
    int count = 0;
    while(*str != 0){
        *(str++);
        count++;
    }
    // printf("%d\n", count);
    return count;
}

int main(void)
{
	char str1[90], str2[90];

    printf("두 과일 입력(과일1 과일2) : ");
    scanf("%s %s", str1, str2);

    printf("첫 번째 과일 : %s\n", str1);
    printf("두 번째 과일 : %s\n", str2);
	
    if(my_strlen(str1) > my_strlen(str2)){
        printf("%s 이름이 더 깁니다.\n", str1);
    }
    else printf("%s 이름이 더 깁니다.\n", str2);
	return 0;
}
#endif

/***********************************************************/
// [12-12] 함수를 사용한 문자열 비교 strcmp()
/***********************************************************/

#if 0
#include <stdio.h>
#include <string.h> //strcmp()

int main(void)
{
	//strcmp(문자열1 , 문자열2)
    //각 문자열 앞에서부터 아스키코드 값을 비교
    //모두 같으면 0
    //두 번째 아스키 값이 크면 -1
    //첫 번째 아스키 값이 크면 1

    char str1[90] = "peach";
    char str2[90] = "pear";
    int result = strncmp(str1, str2, 3);
    int result = strcmp(str1, str2);
    
    switch(result){
        case 1 : 
            printf("%s이 사전에 나중에 나옵니다.", str1); 
            break;
        case -1 :
            printf("%s이 사전에 나중에 나옵니다.", str2); 
            break;
        case 0 :
            printf("문자열이 동일합니다.");
            break;
        default :
            printf("잘못 입력하셨습니다.");
            break;
    }

	return 0;
}
#endif

/***********************************************************/
// [12-12-직접구현] 나만의 my_strcmp() 만들기
/***********************************************************/

#if 0
#include <stdio.h>
#include <string.h>

int my_strcmp(char *str1, char *str2){
    
    // 문자열 하나씩 이동하면서 비교
    // 각 문자를 비교하였을 때,
    // str1의 문자 아스키 값이 크면 1
    // str2의 문자 아스키 값이 크면 -1
    // 전부 같으면 0을 반환!!

    char *ps1 = str1;
    char *ps2 = str2;

    while((*ps1 == *ps2) && ((*ps1 != '\0') && (*ps2 != '\0'))){
        ps1++;
        ps2++;
    }
    if (*ps1 > *ps2) return 1;
    else if(*ps1 < *ps2) return -1;
    else return 0;
}

int main(void)
{
    //모두 소문자만 비교

    char str1[90] = "pear";
    char str2[90] = "peach";
    // int result = strncmp(str1, str2, 3);
    int result = my_strcmp(str1, str2);
    
    switch(result){
        case 1 : 
            printf("%s이 사전에 나중에 나옵니다.", str1); 
            break;
        case -1 :
            printf("%s이 사전에 나중에 나옵니다.", str2); 
            break;
        case 0 :
            printf("문자열이 동일합니다.");
            break;
        default :
            printf("잘못 입력하셨습니다.");
            break;
    }

	return 0;
}
#endif

/***********************************************************/
// [12-추가] 문자 개수 찾기
/***********************************************************/

#if 0
#include <stdio.h>
#include <string.h>

int find_char(char *str, char c){
    int count = 0;

    while(*str){
        if(*(str++) == c){
            count++;
        } 
    }

    return count;
}

int main(void)
{
    printf("%d\n", find_char("Hello", 'H'));
	
	return 0;
}
#endif

/***********************************************************/
// [12-도전] 단어 정렬 프로그램
/***********************************************************/

#if 1
#include <stdio.h>
#include <string.h>

int main(void)
{
    // 문자열 하나씩 이동하면서 비교
    // 각 문자를 비교하였을 때,
    // str1 < str2 -> -1
    // str1 > str2 -> 1
    // str1 == str2 -> 0

	char str1[100] = "kiwi";
    char str2[100] = "banana";
    char str3[100] = "grape";
    int result = 0;

    // scanf("%s %s %s", str1, str2, str3);
    // a b c d e f g h i j k l m n o p q r s t u v w x y z
    result = strcmp(str1, str2);
    printf("%d\n", result);
    result = strcmp(str2, str3);
    printf("%d\n", result);
    
    

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