/***********************************************************/
// [16-1] 동적 할당을 활용한 배열 생성
/***********************************************************/

#if 0
#include <stdio.h>
#include <stdlib.h> //동적 할당

int main(void)
{
    int n;
    printf("배열의 크기를 입력하세요 : ");
    scanf("%d", &n);
    
    //malloc : 동적 할당
    //n * sizeof(int) > n개 x 4byte 만큼 할당
    //(int *) > void 포인터를 형변환해서 사용 (malloc은 void임)
    int *array = (int *)malloc(n * sizeof(int));

    //만약 할당할 여유 공간 (메모리)가 없다면
    if(array == NULL){
        printf("메모리가 부족 합니다.");
        // return -1;
        exit(1); // 어디서든 프로그램 종료
    }

	int count = 1;

    for(int i = 0; i < n; i++){
        array[i] = count++;
    }

    for(int i = 0; i < n; i++){
        printf("%3d ", array[i]);
    }
    // 동적 할당 해제
    free(array);
    // 하지 안으면 메모리 회수가 안됨
    // 단, 해제한 이후 더 이상 array를 출력할 수 없다.

	return 0;
}
#endif

/***********************************************************/
// [16-2] 연속 할당과 재할당
/***********************************************************/

#if 0
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int n;
    printf("배열의 크기를 입력하세요 : ");
    scanf("%d", &n);

    //calloc -> 초기화까지 해줌
    int *array = (int *)calloc(n, sizeof(int));

    if(array == NULL){
        printf("메모리가 부족 합니다.");
        // return -1;
        exit(1); // 어디서든 프로그램 종료
    }

	int count = 1;

    for(int i = 0; i < n; i++){
        array[i] = count++;
    }

    for(int i = 0; i < n; i++){
        printf("%3d ", array[i]);
    }

    printf("\n");

    int m;
    printf("재조정할 배열의 크기 입력 : ");
    scanf("%d", &m);
    array = (int *)realloc(array, m * sizeof(int));

    for(int i = n; i < m; i++){
        array[i] = count++;
    }

    for(int i = 0; i < m; i++){
        printf("%3d ", array[i]);
    }

    free(array);

	return 0;
}
#endif

/***********************************************************/
// [16-4] 3개의 문자열을 저장하기 위한 동적 할당
/***********************************************************/

#if 0
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	// 3개의 문자열 입력
    // 각 문자열의 길이 모름
    char *str[3];
    char temp[46] = {0,};
    for(int i = 0; i < 3; i++){
        gets(temp);
        str[i] = (char *)malloc(strlen(temp) + 1);
        if(str[i] == NULL){
            printf("메모리 부족");
            exit(1);
        }
        strcpy(str[i], temp);
    }

    for(int i = 0; i < 3; i++){
        printf("%s ", str[i]);
    }

    for(int i = 0; i < 3; i++){
        free(str[i]);
    }

	return 0;
}
#endif

/***********************************************************/
// [16-5] 몇 개를 받아 문자열 출력
/***********************************************************/

#if 0
#include <stdio.h>
#include <stdlib.h> // malloc
#include <string.h> // strlen, strcpy

void print_array(char **str){
    for(int i = 0; *str != '\0'; i++){
        printf("%s\n", *str);
        str++;
    }
}

int main(void)
{
    //사용자가 문자열을 입력
    // 몇개 입력할지 모름
    // 최대 20개까지만..

    char *str[21];
    char temp[46] = {0};
    
    for(int i = 0; i < 20; i++){
        printf("문자열을 입력하세요 : ");
        gets(temp);
        if(strcmp(temp, "end") == 0) break;
        str[i] = (char *)malloc(strlen(temp) + 1);
        if(str[i] == NULL) exit(1);
        strcpy(str[i], temp);
    }

    print_array(str);
	
    for(int i = 0; i < 20; i++){
        if(str[i] == NULL) break;
        free(str[i]);
    }

	return 0;
}
#endif

/***********************************************************/
// [16-6] 명령 프롬프트 인자를 출력하는 프로그램
/***********************************************************/

#if 0
#include <stdio.h>
#include <stdlib.h> // atoi()

int main(int argc, char **argv)
{
    // 수정 후 Ctrl + Shift + B 빌드!!
    printf("Hello World!!\n");
    int size = atoi(argv[1]);
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < i; j++)
        {
            printf("*");
        }
        printf("\n");
    }
    /*for (int i = 0; i < argc; i++)
    {
        printf("%s\n", argv[i]);
    }*/

    return 0;
}
#endif

