/***********************************************************/
// [10-1] 배열명에 정수 연산을 수행해 배열 요소 사용
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
	int array[3]; // 3칸 배열 총 12byte.

    printf("%d\n", array);
    printf("%d\n",&array[0]);
    printf("%d\n", (array + 1));

    array[0] = 10;
    *(array + 1) = 20;
    // *(array + 3) = 10; 처럼 범위를 벗어난 주소 사용 금지

    for(int i = 0; i < 3; i++){
        printf("%d번째 요소 : %d ", i, array[i]);
    }

	return 0;
}
#endif

/***********************************************************/
// [10-2] 배열명처럼 사용되는 포인터
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
	int array[3];
    int *pa = array;

    *pa = 10;
    // 20을 배열 두 번째 요소(인덱스 1)에 할당
    //1.
    //  array[1] = 20;
    
    //2.
    //  *(array + 1) = 20;
    
    //3.
    //  *(pa + 1) = 20;
    
    //4.
    //  pa++, *pa = 20;

    for(int i = 0; i < 3; i++){
        printf("%d번째 요소 : %d ", i, array[i] );
    }
    printf("\n");

    printf("배열 전체의 길이 : %d\n", sizeof(array));
    printf("포인터 하나의 길이 : %d\n", sizeof(pa));
    

	return 0;
}
#endif

/***********************************************************/
// [10-3] 포인터를 이용한 배열의 값 출력
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
    int array[3] = {10, 20, 30};
    int *pa = array;

    printf("배열의 값 : ");
    for(int i = 0; i < 3 ; i++){
        //printf("%d ", array[i]);
        
        // printf("%d ", *pa);
        // pa++;

        printf("%d ", *(pa++)); //후위 증감 연산자 사용시 주소 값을 확인하여 벗어났는지 체크
        // printf("%d ", *(++pa)); // 전위 증감 연산을 쓸경우 원하는 결과를 얻을수 없을 수 있다.
    }
    pa = array; // pa를 재사용을 할경우 다시 주소값을 할당 필요

	return 0;
}
#endif

/***********************************************************/
// [10-4] 포인터의 뺼셈과 관계 연산
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
    int array[5] = {10, 20, 30, 40, 50};
    int *pa = array;
    int *pb = array + 3;

    pa++;
    printf("pb - pa : %u\n", pb - pa);

    // 두 포인터 중
    // 더 앞에 있는 (인덱스가 작은) 요소 출력
    if(pa < pb){
        printf("%d\n", *pa);
    }
    else{
        printf("%d\n", *pb);
    }

	return 0;
}
#endif

/***********************************************************/
// [10-5] 배열을 처리하는 함수
/***********************************************************/

#if 0
#include <stdio.h>

void print_array(int *pa){
    for(int i = 0; i < 5; i++){
        printf("%d ", pa[i]);
    }
}

int main(void)
{
	int array[5] = {10, 20, 30, 40, 50};
    print_array(array);

	return 0;
}
#endif

/***********************************************************/
// [10-6] 크기가 다른 배열을 처리하는 함수
/***********************************************************/

#if 0
#include <stdio.h>

void print_array(int *pa, int size){

    for(int i = 0; i < size; i++){
        printf("%d ", pa[i]);
    }
    printf("\n");
}

int main(void)
{
	int array[5] = {10, 20, 30, 40, 50};
    int array2[7] = {10, 20, 30, 40, 50, 60, 70};

    print_array(array, 5);
    print_array(array2, 7);

	return 0;
}
#endif

/***********************************************************/
// [10-7] 배열에 값을 입력하는 함수
/***********************************************************/

#if 0
#include <stdio.h>

void input_array(int *pa, int size);
void print_array(int *pa, int size);
void find_max(int *pa, int size);

int main(void)
{
    int array[5] = {0,};
    
    input_array(array, sizeof(array) / sizeof(int));
    find_max(array, 5);
    
	return 0;
}

void input_array(int *pa, int size){
    for(int i = 0; i < size; i++){
        scanf("%d", &pa[i]);
    }
    // print_array(pa, size);
}

void print_array(int *pa, int size){
    for(int i = 0; i < size; i++){
        printf("%d ",pa[i]);
    }
    printf("\n");
}

void find_max(int *pa, int size){
    int max = pa[0];
    //30 10 40 20 50
    //10 20 30 40 50
    for(int i = 0; i < size; i++){
        if(max < pa[i]){
            max = pa[i];
        }
    }
    printf("%d\n", max);
}

#endif

/***********************************************************/
// [10-도전] 로또 번호 생성 프로그램
/***********************************************************/

#if 1
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_lotto(int *pa, int size){
    for(int i = 0; i < size; i++){
        printf("%d ", pa[i]);
    }
    printf("\n");
}

void input_lotto(int *pa, int size){
    srand(time(NULL));
        
    for(int i = 0; i < size; i++){
        pa[i] = rand() % 45 + 1;
        // printf("%d 번째 로또 번호 입력 : ", (i+1));
        // scanf("%d", &pa[i]);
    
        for(int j = 0; j < i; j++){
            if(pa[i] == pa[j]){
                printf("다시 입력하세요.\n");
                i--;
                break;
            }
        }
    }
}


int main(void)
{
    int lotto[6] = {0,};
    
    input_lotto(lotto, 6);
    print_lotto(lotto, 6);

	// 6개의 정수를 입력(1 ~ 45)
    // 해당 값이 이미 존재하면 다시 입력

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