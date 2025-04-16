/***********************************************************/
// [14-0] 2차원 배열 사용 이유
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
    int score1[4] = { 10, 20, 30, 40 };
    int score2[4] = { 20, 30, 40, 50 };
    int score3[4] = { 30, 40, 50, 60 };

    int total_kor = score1[0] + score2[0] + score3[0];

    int scores[3][4] = { score1, score2, score3};
    

	return 0;
}
#endif

/***********************************************************/
// [14-1] 네 과목의 총점과 평균
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
    int scores[3][4] = {
        {72, 80, 95, 60},
        {68, 98, 83, 90},
        {75, 72, 84, 90}};
    int scores_sum[3] = {
        0,
    };
    double avg;
    // 두 번째 사람의 3번째 과목 -> score[1][2]
    //  각 사람들의 총점
    for (int j = 0; j < 3; j++)
    {
        for (int i = 0; i < 4; i++)
        {
            scores_sum[j] += scores[j][i];
        }
        avg = scores_sum[j] / (double)4;
        printf("%d\n", scores_sum[j]);
        printf("%lf\n", avg);
    }
    // 총 12개의 데이터
    // [3][4] : 3행 4열
    // 7번째 데이터의 행, 열의 index는 어떻게 되는가?
    // scores[1][2]
    // 1 ~ 4 -> 열 인덱스 0
    // 5 ~ 8 -> 열 인덱스 1
    // 9 ~ 12 -> 열 인덱스 2
    // 0 ~ 3 -> 1자리
    // 4 ~ 7 -> 2자리
    // like 4진수
    // 7 - 1 / 4
    // 1번째 데이터 열 index -> 0
    // 2번째 데이터 열 index -> 1
    // 3번째 데이터 열 index -> 2
    // 4번째 데이터 열 index -> 3
    // 5번째 데이터 열 index -> 0
    // (7 - 1) % 4
    // n번째 데이터의 행 index -> (n - 1) / 열의 개수
    // n번째 데이터의 열 index -> (n - 1) % 열의 개수

    return 0;
}
#endif

/***********************************************************/
// [14-2] scanf를 통한 2차원 배열 초기화
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
    int scores[3][4];
    //입력
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 4; j++){
            scanf("%d", &scores[i][j]);
        }
    }
	
    //출력
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 4; j++){
            printf("%5d ", scores[i][j]);
        }
        printf("\n");
    }

	return 0;
}
#endif

/***********************************************************/
// [14-연습] 2차원 배열 부수기
/***********************************************************/

#if 0
#include <stdio.h>

void input_2d_array(int (*pa)[5])
{
    int count = 1;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            pa[i][j] = count++;
        }
    }
}

void input_2d_array2(int (*pa)[5])
{
    int count = 21;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            pa[i][j] = count++;
        }
    }
}

void print_2d_array(int (*pa)[5])
{
    // pointer
    // pa -> array[0]
    // pa + 1 -> array[1]
    // ((pa + 2) + 3) array[2][3]

    // 매개변수에 int pa[5][5]
    // 매개변수에 int pa[][5]
    // 매개변수에 int pa[]

    // pa는 5x5 2차원 배열
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            printf("%3d", pa[i][j]);
        }
        printf("\n");
    }
}

void print_2d_array2(int (*pa)[5])
{
    // pointer
    // pa -> array[0]
    // pa + 1 -> array[1]
    // ((pa + 2) + 3) array[2][3]

    // 매개변수에 int pa[5][5]
    // 매개변수에 int pa[][5]
    // 매개변수에 int pa[]

    // pa는 5x5 2차원 배열
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            printf("%3d", pa[j][i]);
        }
        printf("\n");
    }
}

void print_2d_array3(int (*pa)[5])
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 4; j >= 0; j--)
        {
            printf("%3d", pa[i][j]);
        }
        printf("\n");
    }
}

void print_2d_array4(int (*pa)[5])
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 4; j >= 0; j--)
        {
            printf("%3d", pa[j][i]);
        }
        printf("\n");
    }
}

void print_2d_array5(int (*pa)[5])
{
    for (int i = 4; i >= 0; i--)
    {
        for (int j = 4; j >= 0; j--)
        {
            printf("%3d", pa[j][i]);
        }
        printf("\n");
    }
}

void print_2d_array6(int (*pa)[5])
{
    for (int i = 0; i < 5; i++)
    {
        if (i % 2 == 0)
        {
            for (int j = 0; j < 5; j++)
            {
                printf("%3d", pa[i][j]);
            }
        }
        else
        {
            for (int j = 4; j >= 0; j--)
            {
                printf("%3d", pa[i][j]);
            }
        }
        printf("\n");
    }
}

int main(void)
{
    int array[5][5];

    int array2[10][3];
    // 행의 개수 : 10
    // 열의 개수 : 3
    // array2를 통해서 -> 10
    // array2 : 120byte
    // array2[0] : 12byte

    sizeof(array2);    // 120byte
    sizeof(array2[0]); // 12byte
    sizeof(int);       // 4byte

    int row = sizeof(array2) / sizeof(array2[0]);
    int column = sizeof(array2[0]) / sizeof(int);

    int count = 1;
    // input_2d_array(array);
    // print_2d_array(array);
    // printf("\n");
    input_2d_array2(array);
    // print_2d_array(array);
    printf("\n");
    // print_2d_array2(array);
    // printf("\n");
    // print_2d_array3(array);
    // printf("\n");
    // print_2d_array4(array);
    // printf("\n");
    // print_2d_array5(array);
    // printf("\n");
    print_2d_array6(array);
    return 0;
}
#endif

/***********************************************************/
// [14-3] 여러 마리의 동물을 입출력
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
    char ani[5][20];

    for(int i = 0; i < 5; i++){
        scanf("%s", ani[i]);
    }

    for(int i = 0; i < 5; i++){
        printf("%s\n", ani[i]);
    }
#endif

/***********************************************************/
// [14-4] 포인터 배열로 여러개의 문자열 출력
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{

    char *pa = "dog";
    char *pb = "cat";
    char *pc = "rabbit";
    char *pd = "elephant";
    char *pe = "hippo";

    char *pary[5] = {pa, pb, pc, pd, pe};

    for (int i = 0; i < 5; i++)
    {
        printf("%s\n", pary[i]);
    }

    char *pary2[5] = {"dog", "cat", "rabbit", "elephant", "hippo"};

    for (int i = 0; i < 5; i++)
    {
        printf("%s\n", pary2[i]);
    }

    return 0;
}
#endif

/***********************************************************/
// [14-5] 포인터 배열을 통해 int 2차원도 1차원처럼 써보자
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
    int ary1[4] = { 10, 20, 30, 40 };
    int ary2[4] = { 11, 21, 31, 41 };
    int ary3[4] = { 12, 22, 32, 42 };

    int *par[3] = {ary1, ary2, ary3};

    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 4; j++){
            printf("%3d", par[i][j]);
        }
        printf("\n");
    }

	return 0;
}
#endif

/***********************************************************/
// [14-도전] 가로 세로의 합 구하기
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{

    int array[5][6] = {
        0,
    };
    int count = 1;
    int sum = 0;
    int i = 0, j = 0;

    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 5; j++)
        {
            array[i][j] = count++;
        }
    }

    int total_row; // 행의 합 저장하는 변수

    for (i = 0; i < 5; i++)
    {
        total_row = 0;
        for (j = 0; j < 5; j++)
        {
            total_row += array[i][j];
        }
        array[i][j] = total_row;
    }

    // 2. 열의 합 구해서 대입!!
    int total_col; // 열의 합 저장하는 변수
    for (i = 0; i < 5; i++)
    {
        total_col = 0;
        for (j = 0; j < 4; j++)
        {
            total_col += array[j][i];
        }
        array[j][i] = total_col;
    }

    // 3. 모든 값 더해서 array[4][5]에 대입
    int total;

    total = 0;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 5; j++)
        {
            total += array[i][j];
        }
    }
    array[i][j] = total;

    for (i = 0; i < 5; i++)
    {
        for (j = 0; j < 6; j++)
        {
            printf("%4d", array[i][j]);
        }
        printf("\n");
    }

    return 0;
}
#endif

/***********************************************************/
// [14-백준2738] 행렬 덧셈
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
    // 3 3
    // 1 1 1
    // 2 2 2
    // 0 1 0
    // 3 3 3
    // 4 4 4
    // 5 5 100
	freopen("input.txt", "r", stdin);

    int n = 0, m = 0;

    scanf("%d %d", &n, &m);
    int array1[n][m];
    int array2[n][m];

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            scanf("%d", &array1[i][j]);
        }
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            scanf("%d", &array2[i][j]);
        }
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            printf("%d ", array1[i][j] + array2[i][j]);
        }
        printf("\n");
    }

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