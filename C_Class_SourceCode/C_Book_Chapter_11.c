/***********************************************************/
// [11-1] �빮�ڸ� �ҹ��ڷ� ����
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
// [11-2] �����̳� ���� ������ �Է�
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
    
    // printf("�Է��� ���� : ");
    // putchar(ch);

	return 0;
}
#endif

/***********************************************************/
// [11-3-��] scanf�� ����
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
    char ch;
	for(int i = 0; i < 5; i++){
        scanf(" %c", &ch); //%�տ� ���� ���� �� > ȭ��Ʈ �����̽� ����!!
        printf("%c", ch);
    }

	return 0;
}
#endif

/***********************************************************/
// [11-4] ���۸� ����� ���� �Է�
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
// [11-5] �Է� ������ �ƽ�Ű �ڵ带 ����ϴ� ���α׷�
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
// [11-6] getchar �Լ��� ����� ���ڿ� �Է�
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
	printf("�Է��� ���ڿ� : %s\n", str);

	return 0;
}
#endif

/***********************************************************/
// [11-7] ���� �ʱ�ȭ
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
    int num;
    int grade;
    // scanf()�� getchar()�� ���۸� �����Ѵ�.
    printf("�й� �Է� : ");
    scanf("%d", &num);
    printf("���� �Է� : ");
    
    //�Է� ���� ��� �� ���ǻ���
    //�� �𸣰����� ���۸� �ʱ�ȭ ����
    getchar();

    grade = getchar();
    
    printf("�й� : %d, ���� : %c", num, grade);
	
	return 0;
}
#endif

/***********************************************************/
// [11-����] ���̰� ���� �� �ܾ� ã��
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
    int ch, max = 0, len;
    while(1){
        
        ch = getchar(); // ��ü �Է��� ���Ḧ �Ǵ�.
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