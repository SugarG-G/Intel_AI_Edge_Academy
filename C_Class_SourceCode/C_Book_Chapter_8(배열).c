/***********************************************************/
// [8-1] 배열의 선언과 사용
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
	int num; //변수의 선언
    num = 10;//변수의 할당 (최초이면 초기화)
    num = 20;//변수에 재할당
    printf("%d\n", num); //변수의 사용

    int array[5]; //배열의 선언
    array[0] = 10; // 배열요소의 할당
    array[1] = 20; 
    //배열요소가 초기화 되어 있지 않다면 사용 시 쓰레기 값이 출력된다.

    printf("%d %d\n",array[0], array[1]);
    // printf("%d %d %d\n", array[2], array[3], array[4]);

	return 0;
}
#endif

/***********************************************************/
// [8-2] 배열의 선언과 사용
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
	int array[5] = {8, 4, 99, 6, 7};

    printf("array에 들어있는 홀수는 ");
    for(int i = 0; i < 5; i++){
        if(array[i] % 2 == 1){
            printf("%d ", array[i]);
        }
    }
    printf("이다\n");
	return 0;
}
#endif

/***********************************************************/
// [8-3] sizeof 연산자를 사용한 배열
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
    int arr[5];
    int num;
    int result = 0;
	for(int i = 0; i < 5; i++){
        printf("%d과목 성정을 입력하세요 : ", i+1);
        scanf("%d", &num);
        arr[i] = num;
        result += arr[i];
    }

    printf("총점 : %d점, ", result);
    printf("평균 : %d점", result/(sizeof(arr) / sizeof(int)));

	return 0;
}
#endif

/***********************************************************/
// [8-4] char 형 배열의 선언과 초기화
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
    //배열에 문자열을 저장할경우 null (\0)을 포함한 크기를 지정해줄것
	int array[5] = { 1, 2, 3, 4, 5};
    char fruit[6] = {'a', 'p', 'p', 'l', 'e'};
    char fruit2[6] = "apple";

    char my_name[10];
    my_name[0] = 'c';
    my_name[1] = 'h';
    my_name[2] = 'i';
    my_name[3] = '\0';

    printf("%s", my_name);
    /*
    for(int i = 0 ; i < 5; i++){
        printf("%c", fruit[i]);
    }
    printf("\n");
    printf("%s", fruit2);
    */
    
	return 0;
}
#endif

/***********************************************************/
// [8-5] 문자열을 대입하는 strcpy 함수
/***********************************************************/

#if 0
#include <stdio.h>
#include <string.h>

int main(void)
{
    char fruit[100] = "apple";
    printf("현재 과일 : %s\n", fruit);
    
    //strcpy(이전 문자열, 새로운 문자열);
    strcpy(fruit, "banana");
    printf("새로운 과일 : %s\n", fruit);


    char cat_name[100] = "이름을 지어주세요 : ";
    char new_name[100];
    
    printf("%s", cat_name);
    scanf("%s", new_name);
    strcpy(cat_name, new_name);
    printf("%s", cat_name);
	return 0;
}
#endif

/***********************************************************/
// [8-6] gets(), puts() 띄어쓰기까지 입력받기
/***********************************************************/

#if 0
#include <stdio.h>
#include <string.h>

int main(void)
{
    char inputs[100];

    printf("내일의 점심 메뉴 입력 : ");
    gets(inputs);

    puts(inputs);

	return 0;
}
#endif

/***********************************************************/
// [8-도전] 대소문자 변환 프로그램
/***********************************************************/

#if 0
#include <stdio.h>
#include <string.h>

int main(void)
{
	char str[100];
    int count = 0;
    printf("문장 입력 : ");
    gets(str);

    for(int i = 0 ; i < sizeof(str) / sizeof(char); i++){
        if(str[i] <= 90 && str[i] >= 65){
            str[i] += 32;
            count++;
        }
    }
    printf("바뀐 문장 : %s\n", str);
    printf("바뀐 문자 수 : %d\n", count);

    char test[100] = "HELLO WORLD";
    printf("%s", strlwr(test));

	return 0;
}
#endif

/***********************************************************/
// [8-0] 정렬
/***********************************************************/

#if 1
#include <stdio.h>

int main(void)
{
    // 정렬 -> 탐색을 손쉽게 하기 위해
    int array[6] = {1, 13, 21, 7, 31, 28};

    // 1. 버블 정렬
    //  cycle 1
    /*
    if(array[0] > array[1]){
        int temp;
        temp = array[0];
        array[0] = array[1];
        array[1] = temp;
    }
    if(array[1] > array[2]){
        int temp;
        temp = array[1];
        array[1] = array[2];
        array[2] = temp;
    }
    */
    /*
    for (int i = 0; i < 5; i++)
    {
        if (array[i] > array[i + 1])
        {
            int temp;
            temp = array[i];
            array[i] = array[i + 1];
            array[i + 1] = temp;
        }
    }
    
    for (int i = 0; i < 4; i++)
    {
        if (array[i] > array[i + 1])
        {
            int temp;
            temp = array[i];
            array[i] = array[i + 1];
            array[i + 1] = temp;
        }
    }
    */
    
    for (int j = 5; j > 0; j--)
    {
        for (int i = 0; i < j; i++)
        {
            if (array[i] > array[i + 1])
            {
                int temp;
                temp = array[i];
                array[i] = array[i + 1];
                array[i + 1] = temp;
            }
        }
    }

    for (int i = 0; i < 6; i++)
    {
        printf("%d ", array[i]);
    }

    return 0;
}
#endif