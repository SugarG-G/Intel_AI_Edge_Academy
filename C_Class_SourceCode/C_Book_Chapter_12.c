/***********************************************************/
// [12-1] ���ڿ��� ���ڿ� �迭??
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
// [12-2] �����ͷ� ���ڿ� ���
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
// [12-���] ���� ���ڿ� ���???
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
// [12-3] scanf�� ����� ���ڿ� �Է�
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
    char str[100];
    printf("���ڿ� �Է� : ");
    
    scanf("%s", str);
    printf("%s\n", str);

    scanf("%s", str);
    printf("%s", str);
    

    return 0;
}
#endif

/***********************************************************/
// [12-4] gets �Լ��� �� ���� ���ڿ� �Է�
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
    char str[100];

    printf("���ڿ� �Է� : ");
    gets(str); //���͸� ������ tap, ���� �Է� ����
    printf("%s", str);

	return 0;
}
#endif

/***********************************************************/
// [12-5] gets�� ������ ������ ���� fgets
/***********************************************************/

#if 0
#include <stdio.h>
#include <string.h>

int main(void)
{
    char str[100];
    printf("���ڿ� �Է� : ");
    fgets(str, sizeof(str), stdin); //Ű����� �Է� �ϰڴ�.
    printf("���ڿ� ���� : %d\n", strlen(str) - 1); // fgets�� �Է� ���� �� ���ڿ� ���̴� -1 ���־���Ѵ�.
    
    // ���ڿ��� ������ �ڷᱸ�� �迭������ �迭�� ��� ������ sizeof(�迭��) / sizeof(�ڷ���)���� �������� ���ڿ������� ���ϱ� ��ƴ�.
    printf("���ڿ� ���� 2 : %d\n", sizeof(str) / sizeof(char)); 
    
    printf("�Է��� ���ڿ� : %s\n", str);
    
    printf("%s", str);

    
    
	return 0;
}
#endif

/***********************************************************/
// [12-6] ���� ���ڷ� ���� get �Լ��� �Է� �ȵǴ� ���
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
	int age;
    char name[20];
    
    printf("���� �Է� : ");
    scanf("%d", &age);
    
    printf("�̸� �Է� : ");
    // gets �Լ� ����� ���� �ʱ�ȭ �ʿ�
    // �ʱ�ȭ ��� 3���� ���� p.358 ����
    // 1. getchar(); 2. scanf("%*c"); %*c : �ּ� ���� �� char �б� 3. fgetc(stdin);
    getchar();

    gets(name);

    printf("���� : %d, �̸� : %s\n", age, name);

	return 0;
}
#endif

/***********************************************************/
// [12-7] ���ڿ��� ����ϴ� puts�� fputs�Լ�
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
    char str[100] = "apple juice";
    
    // char str2[] = "banana";
    // char *ps = str2;
    // �� char *ps = "banana";�� ��������
    char *ps = "banana";

    //puts > �ڵ� �ٹٲ� o
    //fputs > �ڵ� �ٹٲ� x

    puts(str);
    puts(ps);

    fputs(str, stdout); // ����͸� ���� ǥ�� ���
    fputs(ps, stdout);

    return 0;
}
#endif

/***********************************************************/
// [12-����] gets �Լ� �����غ���!!
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
	int i = 0;
    char str[20]; // "apple" �Է�
    char *ps = str;
    // getchar() Ȱ���� gets() ����
    // getchar() > ���� �ϳ��ϳ� �Է�

    //gets() ����
    while(1){
        
        str[i] = getchar();
        if(str[i] == '\n'){
            str[i + 1] = '\0';
            i = 0;
            break;
        }
        i++;
    }
    //gets() ��

    printf("%s", str); // apple ���


    //�����ͷ� ����
    int ch;
    while(1){
        ch = getchar();
        *(ps++) = ch;
        if(ch == '\n'){
            break;
        }
    }
    *ps = '\0';

    printf("%s", str); // apple ���
	return 0;
}
#endif

/***********************************************************/
// [12-8] ���ڿ��� �����ϴ� strcpy �Լ�
/***********************************************************/

#if 0
#include <stdio.h>
#include <string.h>

int main(void)
{
	char str[80] = "strawberry";
    printf("%s\n", str);
    // str = "banana"; // ����
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

    strcpy(str, "banana"); // strcpy(�����Ұ�, ����);
    printf("%s\n", str);

    char *ps = str;
    ps = "kiwi";
    printf("%s\n", ps); // �����ͷ� ���� ����� �ٸ� �����ͷ� ��ȯ.
    printf("%s\n", str);

	return 0;
}
#endif

/***********************************************************/
// [12-9] n���� ���ڿ��� �����ϴ� strncpy()
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
// [12-8-��������] strcpy()
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
    printf("�ٲٱ� �� ���ڿ� : %s\n", str);

    //�迭�� �ٷ� �� ũ�⸦ �ִ� ����
    // ��> �ٸ� �Լ����� ���� �迭�� ũ�⸦ �� ���� ����
    //���ڿ� �迭 -> �ٸ� �Լ����� ���ڿ� ũ�� �� �� ���� ���? ����
    //�� ���ڱ��� ������ ���� -> ���ڿ��� ũ��
    my_strcpy(str, "mango");
    printf("�ٲ� �� ���ڿ� : %s\n", str); // mango;
	
	return 0;
}
#endif

/***********************************************************/
// [12-10] ���ڿ��� �����ϴ� strcat() 
/***********************************************************/

#if 0
#include <stdio.h>
#include <string.h> //strcat()

int main(void)
{
    // straw + berry
    // python, Jave
    // str1 + str2 ����
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
// [12-10-���� ����] my_strcat() �����
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
// [12-11] ���ڿ� ���� strlen()
/***********************************************************/

#if 0
#include <stdio.h>
#include <string.h> //strlen()

int main(void)
{
    char str1[90], str2[90];

    printf("�� ���� �Է�(����1 ����2) : ");
    scanf("%s %s", str1, str2);

    printf("ù ��° ���� : %s\n", str1);
    printf("�� ��° ���� : %s\n", str2);
	
    if(strlen(str1) > strlen(str2)){
        printf("%s �̸��� �� ��ϴ�.\n", str1);
    }
    else printf("%s �̸��� �� ��ϴ�.\n", str2);
    

	return 0;
}
#endif

/***********************************************************/
// [12-11-����] my_strlen() �����
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

    printf("�� ���� �Է�(����1 ����2) : ");
    scanf("%s %s", str1, str2);

    printf("ù ��° ���� : %s\n", str1);
    printf("�� ��° ���� : %s\n", str2);
	
    if(my_strlen(str1) > my_strlen(str2)){
        printf("%s �̸��� �� ��ϴ�.\n", str1);
    }
    else printf("%s �̸��� �� ��ϴ�.\n", str2);
	return 0;
}
#endif

/***********************************************************/
// [12-12] �Լ��� ����� ���ڿ� �� strcmp()
/***********************************************************/

#if 0
#include <stdio.h>
#include <string.h> //strcmp()

int main(void)
{
	//strcmp(���ڿ�1 , ���ڿ�2)
    //�� ���ڿ� �տ������� �ƽ�Ű�ڵ� ���� ��
    //��� ������ 0
    //�� ��° �ƽ�Ű ���� ũ�� -1
    //ù ��° �ƽ�Ű ���� ũ�� 1

    char str1[90] = "peach";
    char str2[90] = "pear";
    int result = strncmp(str1, str2, 3);
    int result = strcmp(str1, str2);
    
    switch(result){
        case 1 : 
            printf("%s�� ������ ���߿� ���ɴϴ�.", str1); 
            break;
        case -1 :
            printf("%s�� ������ ���߿� ���ɴϴ�.", str2); 
            break;
        case 0 :
            printf("���ڿ��� �����մϴ�.");
            break;
        default :
            printf("�߸� �Է��ϼ̽��ϴ�.");
            break;
    }

	return 0;
}
#endif

/***********************************************************/
// [12-12-��������] ������ my_strcmp() �����
/***********************************************************/

#if 0
#include <stdio.h>
#include <string.h>

int my_strcmp(char *str1, char *str2){
    
    // ���ڿ� �ϳ��� �̵��ϸ鼭 ��
    // �� ���ڸ� ���Ͽ��� ��,
    // str1�� ���� �ƽ�Ű ���� ũ�� 1
    // str2�� ���� �ƽ�Ű ���� ũ�� -1
    // ���� ������ 0�� ��ȯ!!

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
    //��� �ҹ��ڸ� ��

    char str1[90] = "pear";
    char str2[90] = "peach";
    // int result = strncmp(str1, str2, 3);
    int result = my_strcmp(str1, str2);
    
    switch(result){
        case 1 : 
            printf("%s�� ������ ���߿� ���ɴϴ�.", str1); 
            break;
        case -1 :
            printf("%s�� ������ ���߿� ���ɴϴ�.", str2); 
            break;
        case 0 :
            printf("���ڿ��� �����մϴ�.");
            break;
        default :
            printf("�߸� �Է��ϼ̽��ϴ�.");
            break;
    }

	return 0;
}
#endif

/***********************************************************/
// [12-�߰�] ���� ���� ã��
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
// [12-����] �ܾ� ���� ���α׷�
/***********************************************************/

#if 1
#include <stdio.h>
#include <string.h>

int main(void)
{
    // ���ڿ� �ϳ��� �̵��ϸ鼭 ��
    // �� ���ڸ� ���Ͽ��� ��,
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