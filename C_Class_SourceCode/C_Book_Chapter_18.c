/***********************************************************/
// [18-1] ���� ���� �ݱ�
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
    FILE *fp;
    const char *path = "d:\\Intel_AI_Edge_Acadamy\\a.txt";
    // ��� ��η� ���Ҷ�
    // �츮�� ���� �ٶ���� �� ctrl + f5
    // ������ ���� > exe ����
    const char *path2 = "..\\a.txt";

    fp = fopen(path, "r");
    if (fp == '\0')
    {
        printf("������ ������ �ʾҽ��ϴ�.");
        return -1;
    }

    printf("������ ���Ƚ��ϴ�.\n");
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
// [18-3] ���Ͽ� ���ڿ� ����
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
// [18-3-����] ���� �����
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
    // 1. a.txt �о temp�� ���!! // Hello World!!
    // 2. b.txt �о temp�� �߰�!! // Hello World!! C CLEAR!!
    // 3. temp�� c.txt�� �״�� ����
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

    pt = temp; // ���� ���� ������ �� �������� �̵�!!
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
// [18-4, 5] ǥ�� �����, stdin, stdout
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
        ch = fgetc(stdin); //���� OS�� ����� Ű����
        if(ch == EOF) break;
        fputc(ch, stdout);
    }

    return 0;
}
#endif

/***********************************************************/
// [18-6] ���� ���¿� ���� ��尡 �ٸ� ���
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

    // txt �������� �о��
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
// [18-7] a+ ���� ���� ���� Ȯ���ϸ� ���
/***********************************************************/

#if 0
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
        printf("�뷡 ���� : "); // �Ƹ�� ���ݸ�
        scanf("%s", str);
        if (strcmp(str, "end") == 0)
            break;                         // end <- ���α׷� ����
        else if (strcmp(str, "list") == 0) // list <- ������� ����� ��� �뷡 ���!!
        {
            // ��� ���� ����ϱ� ��
            // fp�� �� ù ��
            // �� ������ �̵���Ű��
            fseek(fp, 0, SEEK_SET);
            while (1)
            {
                // ����(\n)�������� ���� +1
                fgets(str, strlen(str) + 1, fp);
                // �� ���� �����ϸ�
                // feof() ->
                if (feof(fp) != 0)
                    break;
                printf("%s", str);
            }
        }
        // while(1) fputc(), -> ���� ��ü�� �Է�, fputs() fprintf
        else
            fprintf(fp, "%s\n", str);
        // str�� ��� �ִ� �뷡 ������
        // �� ���� d.txt�� ����!!
    }

    fclose(fp); // �������� ����, �������� ����!!
    return 0;
}
#endif

/***********************************************************/
// [18-8] ���� ���� ���ڸ� �Է��� ���ٷ� ��������
/***********************************************************/

#if 0
#include <stdio.h>
#include <string.h>

int main(void)
{
    // a : Hello World!!
    // b : C CLEAR!!
    // 2���� e�� ��������

    const char *path_a = "D:\\Intel_AI_Edge_Acadamy\\a.txt";
    const char *path_b = "D:\\Intel_AI_Edge_Acadamy\\b.txt";
    const char *path_e = "D:\\Intel_AI_Edge_Acadamy\\e.txt";

    FILE *fpa, *fpb, *fpe;

    fpa = fopen(path_a, "r");
    if(fpa == NULL) return 1;
    fpb = fopen(path_b, "r");
    if(fpb == NULL) return 2;
    fpe = fopen(path_e, "w");
    if(fpe == NULL) return 3;

    char str[80];
    char *ps;

    while(1){
        ps = fgets(str, strlen(str) + 1, fpa);
        if(ps == NULL) break;
    }
    while(1){
        ps = fgets(str, strlen(str) + 1, fpb);
        if(ps == NULL) break;
    }

    while(1){
        fputs(ps, fpe);
        if(ps == NULL) break;
    }

    fclose(fpa);
    fclose(fpb);
    fclose(fpe);
	
	return 0;
}
#endif

/***********************************************************/
// [18-9] fprintf() �پ��� �������� ��������
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
    FILE *fp, *fsp;
    const char *path = "D:\\Intel_AI_Edge_Acadamy\\girlfriend.txt";

    fp = fopen(path, "r");
    if(fp == NULL) return 1;

    char *path_score = "D:\\Intel_AI_Edge_Acadamy\\score.txt";
    fsp = fopen(path_score, "w");
    if(fsp == NULL) return 2;

    char name[20];
    int ko, en, ma;
    double avg;
    int sum;

    int result = 0;
    while(1){
        result = fscanf(fp, "%s %d %d %d", name, &ko, &en, &ma);
        if(result == EOF) break;
        sum = ko +en + ma;
        avg = sum / 3.0;

        fprintf(fsp, "%s %d %.1lf\n", name, sum, avg);
    }

    fclose(fp);
    fclose(fsp);

	return 0;
}
#endif

/***********************************************************/
// [0-0] Ÿ��Ʋ
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
	
	return 0;
}
#endif

/***********************************************************/
// [0-0] Ÿ��Ʋ
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
	
	return 0;
}
#endif

/***********************************************************/
// [0-0] Ÿ��Ʋ
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
	
	return 0;
}
#endif