/***********************************************************/
// [16-1] ���� �Ҵ��� Ȱ���� �迭 ����
/***********************************************************/

#if 0
#include <stdio.h>
#include <stdlib.h> //���� �Ҵ�

int main(void)
{
    int n;
    printf("�迭�� ũ�⸦ �Է��ϼ��� : ");
    scanf("%d", &n);
    
    //malloc : ���� �Ҵ�
    //n * sizeof(int) > n�� x 4byte ��ŭ �Ҵ�
    //(int *) > void �����͸� ����ȯ�ؼ� ��� (malloc�� void��)
    int *array = (int *)malloc(n * sizeof(int));

    //���� �Ҵ��� ���� ���� (�޸�)�� ���ٸ�
    if(array == NULL){
        printf("�޸𸮰� ���� �մϴ�.");
        // return -1;
        exit(1); // ��𼭵� ���α׷� ����
    }

	int count = 1;

    for(int i = 0; i < n; i++){
        array[i] = count++;
    }

    for(int i = 0; i < n; i++){
        printf("%3d ", array[i]);
    }
    // ���� �Ҵ� ����
    free(array);
    // ���� ������ �޸� ȸ���� �ȵ�
    // ��, ������ ���� �� �̻� array�� ����� �� ����.

	return 0;
}
#endif

/***********************************************************/
// [16-2] ���� �Ҵ�� ���Ҵ�
/***********************************************************/

#if 0
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int n;
    printf("�迭�� ũ�⸦ �Է��ϼ��� : ");
    scanf("%d", &n);

    //calloc -> �ʱ�ȭ���� ����
    int *array = (int *)calloc(n, sizeof(int));

    if(array == NULL){
        printf("�޸𸮰� ���� �մϴ�.");
        // return -1;
        exit(1); // ��𼭵� ���α׷� ����
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
    printf("�������� �迭�� ũ�� �Է� : ");
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
// [16-4] 3���� ���ڿ��� �����ϱ� ���� ���� �Ҵ�
/***********************************************************/

#if 0
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	// 3���� ���ڿ� �Է�
    // �� ���ڿ��� ���� ��
    char *str[3];
    char temp[46] = {0,};
    for(int i = 0; i < 3; i++){
        gets(temp);
        str[i] = (char *)malloc(strlen(temp) + 1);
        if(str[i] == NULL){
            printf("�޸� ����");
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
// [16-5] �� ���� �޾� ���ڿ� ���
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
    //����ڰ� ���ڿ��� �Է�
    // � �Է����� ��
    // �ִ� 20��������..

    char *str[21];
    char temp[46] = {0};
    
    for(int i = 0; i < 20; i++){
        printf("���ڿ��� �Է��ϼ��� : ");
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
// [16-6] ��� ������Ʈ ���ڸ� ����ϴ� ���α׷�
/***********************************************************/

#if 0
#include <stdio.h>
#include <stdlib.h> // atoi()

int main(int argc, char **argv)
{
    // ���� �� Ctrl + Shift + B ����!!
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

