/***********************************************************/
// [18-1] 파일 열고 닫기
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
    FILE *fp;
    const char *path = "d:\\Intel_AI_Edge_Acadamy\\a.txt";
    // 상대 경로로 정할때
    // 우리가 지금 바라봤을 때 ctrl + f5
    // 컴파일 배포 > exe 기준
    const char *path2 = "..\\a.txt";

    fp = fopen(path, "r");
    if (fp == '\0')
    {
        printf("파일이 열리지 않았습니다.");
        return -1;
    }

    printf("파일이 열렸습니다.\n");
    int ch;

    while (1)
    {
        ch = fgetc(fp);
        if(ch == EOF){
            break;
        }
        putchar(ch);
    }

    fclose(fp);
    return 0;
}
#endif

/***********************************************************/
// [18-3] 파일에 문자열 쓰기
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
	FILE *fp;
    const char *path = "d:\\Intel_AI_Edge_Acadamy\\b.txt";

    fp = fopen(path, "w");
    if(fp == NULL) return 1;

    char *words = "C clear";

    while(*words != NULL) fputc(*(words++), fp);

    fputc('\n', fp);

    fclose(fp);

	return 0;
}
#endif

/***********************************************************/
// [18-3-연습] 파일 입출력
/***********************************************************/

#if 0
#include <stdio.h>
#include <string.h>

#include <stdio.h>
#include <string.h>
int main(void)
{
    FILE *fpa, *fpb, *fpc;
    const char *origin_path = "D:\\Intel_AI_Edge_Acadamy\\";
    char path_a[256] = {
        0,
    };
    char path_b[256] = {
        0,
    };
    char path_c[256] = {
        0,
    };
    strcpy(path_a, origin_path);
    strcpy(path_b, origin_path);
    strcpy(path_c, origin_path);
    strcat(path_a, "a.txt");
    strcat(path_b, "b.txt");
    strcat(path_c, "c.txt");

    fpa = fopen(path_a, "r");
    if (fpa == NULL)
        return 1;

    fpb = fopen(path_b, "r");
    if (fpb == NULL)
        return 2;

    fpc = fopen(path_c, "w");
    if (fpc == NULL)
        return 3;

    char temp[256] = {
        0,
    };
    // 1. a.txt 읽어서 temp에 담기!! // Hello World!!
    // 2. b.txt 읽어서 temp에 추가!! // Hello World!! C CLEAR!!
    // 3. temp를 c.txt에 그대로 쓰기
    char *pt = temp;
    int ch;
    while (1)
    {
        ch = fgetc(fpa);
        *pt++ = ch;
        if (ch == EOF)
            break;
    }
    pt--;

    while (1)
    {
        ch = fgetc(fpb);
        *pt++ = ch;
        if (ch == EOF)
            break;
    }
    pt--;
    *pt = '\0';

    pt = temp; // 쓰기 위해 포인터 맨 왼쪽으로 이동!!
    while (1)
    {
        fputc(*pt, fpc);
        pt++;
        if (*pt == NULL)
            break;
    }
    fputc('\n', fpc);

    printf("%s\n", temp);

    fclose(fpa);
    fclose(fpb);
    fclose(fpc);

    return 0;
}
#endif

/***********************************************************/
// [18-4, 5] 표준 입출력, stdin, stdout
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
    int ch;
    while (1)
    {
        ch = getchar();
        if (ch == EOF)
        {
            break;
        }
        putchar(ch);
    }

    while(1){
        ch = fgetc(stdin); //현재 OS와 연결된 키보드
        if(ch == EOF) break;
        fputc(ch, stdout);
    }

    return 0;
}
#endif

/***********************************************************/
// [18-6] 파일 형태와 개방 모드가 다른 경우
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
	FILE *pf;
    const char *path = "D:\\Intel_AI_Edge_Acadamy\\d.txt";

    fopen(path, "wb");
    if(pf == NULL) return 1;

    int array[10] = { 13, 10, 13, 13, 10, 26, 13, 10, 13, 10 };

    for(int i = 0; i < 10; i++){
        fputc(array[i], pf);
    
    }
    fclose(pf);

    // txt 형식으로 읽어보자
    pf = fopen(path, "r");

    int ch;
    while(1){
        ch = fgetc(pf);
        if(ch == EOF) break;
        printf("%3d", ch);
    }

    fclose(pf);
	return 0;
}
#endif

/***********************************************************/
// [18-7] a+ 모드로 파일 내용 확인하며 출력
/***********************************************************/

#if 1
#include <stdio.h>
#include <string.h>

int main(void)
{
    FILE *fp;
    const char *path = "D:\\Intel_AI_Edge_Acadamy\\music.txt";
    char str[20];

    fp = fopen(path, "a+");
    if (fp == NULL)
        return 1;

    // logic

    while (1)
    {
        printf("노래 제목 : "); // 아몬드 초콜릿
        scanf("%s", str);
        if (strcmp(str, "end") == 0)
            break;                         // end <- 프로그램 종료
        else if (strcmp(str, "list") == 0) // list <- 현재까지 저장된 모든 노래 출력!!
        {
            // 모든 정보 출력하기 전
            // fp를 맨 첫 줄
            // 맨 앞으로 이동시키자
            fseek(fp, 0, SEEK_SET);
            while (1)
            {
                // 개행(\n)가져오기 위해 +1
                fgets(str, strlen(str) + 1, fp);
                // 행 끝에 도달하면
                // feof() ->
                if (feof(fp) != 0)
                    break;
                printf("%s", str);
            }
        }
        // while(1) fputc(), -> 문장 전체를 입력, fputs() fprintf
        else
            fprintf(fp, "%s\n", str);
        // str에 들어 있는 노래 정보를
        // 맨 끝에 d.txt에 쓰자!!
    }

    fclose(fp); // 열었으면 닫자, 열었으면 닫자!!
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