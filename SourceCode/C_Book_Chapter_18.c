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

#if 1
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
// [0-0] 타이틀
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
	
	return 0;
}
#endif