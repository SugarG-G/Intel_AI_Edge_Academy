/***********************************************************/
// [5-1] if���� �⺻ ����
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
    int a;
    printf("���� �Է� : ");
	scanf("%d", &a);
    if(a >= 20){
        printf("�����Դϴ�.");
    }
	return 0;
}
#endif

/***********************************************************/
// [5-2] ����� ����ϱ�
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
    int a;
    printf("���� �Է� : ");
	scanf("%d", &a);

    if(a % 3 == 0 && a % 5 == 0){
        printf("3�� 5�� ��� �Դϴ�.");
    }

	return 0;
}
#endif

/***********************************************************/
// [5-3] ���� �� �̼����� ���� �Ǵ�
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
    int age;
	printf("���� �Է� : ");
    scanf("%d", &age);

    if(age >= 20){
        printf("���� �Դϴ�.");
    }
    else{
        printf("�̼����� �Դϴ�.");
    }

	return 0;
}
#endif

/***********************************************************/
// [5-4] Ȧ�� ¦�� ���� �Ǵ��ϱ�
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
	int a;
    printf("���� �Է� : ");
    scanf("%d", &a);
    
    if(a%2==0){
        printf("¦���Դϴ�.");
    }
    else{
        printf("Ȧ���Դϴ�.");
    }

	return 0;
}
#endif

/***********************************************************/
// [5-5] ��Ʈ ���� ���α׷�
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
	int a;
    printf("���� �Է� : ");
    scanf("%d", &a);

    if(a <= 10){
        printf("%d���Դϴ�.", a*10000);
    }
    else{
        printf("%d���Դϵ�.", (int)((a*10000 - (a*10000)*0.1)));
    }

	return 0;
}
#endif

/***********************************************************/
// [5-6] ���� ��� ���α׷�
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
	int score;
    printf("���� �Է� : ");
    scanf("%d", &score);

    if(score >= 90){
        printf("A ����");
    }
    else if(score >= 80){
        printf("B ����");
    }
    else if(score >= 70){
        printf("C ����");
    }
    else{
        printf("F ����");
    }

	return 0;
}
#endif

/***********************************************************/
// [5-7] ��Ʈ ��� ���α׷� v2
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
    int a = 0, b = 0;
    printf("���� �Է� : ");
    scanf("%d", &a);
    printf("ȸ�� ����(ȸ�� : 1, ��ȸ�� : 0)");
    scanf("%d", &b);

    if(a <= 10){
        
        if(b == 1){
            printf("%d���Դϵ�.", (int)((a*10000)*(1-0.1)));
        }
        else{
            printf("%d���Դϴ�.", a*10000);
        }
    }
    else{
        if(b == 1){
            printf("%d���Դϵ�.", (int)(((a*10000*(1-0.1))*(1-0.1))));
        }
        else{
            printf("%d���Դϵ�.", (int)((a*10000*(1-0.1))));
        }
        
    }

    
	return 0;
}
#endif

/***********************************************************/
// [5-7.5] switch��?
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
    /*
	switch(�����){
        case �� : 
            ���๮��1;
        case �� :
            ���๮��2;
    }
    */
    int month = 4;

    switch(month){
        case 4 : 
            printf("��\n");
            break;
        case 6 :
            printf("����\n");
            break;
    }

	return 0;
}
#endif

/***********************************************************/
// [5-8] ��� ���� ���α׷�
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
	int grade;
    
    printf("��� �Է� : ");
    scanf("%d", &grade);

    switch(grade){
        case 1 :
            printf("300����");
            break;
        case 2 :
            printf("200����");
            break;
        case 3 :
            printf("100����");
            break;
    }
    /*
    if(grade == 1){
        printf("300����");
    }
    else if(grade == 2){
        printf("200����");
    }
    else{
        printf("100����");
    }
    */

	return 0;
}
#endif

/***********************************************************/
// [5-Ȯ��] ���Ǳ� ���α׷� v3
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
	int money, choice;
    printf("�ݾ��� �Է��ϼ��� : ");
    scanf("%d", &money);
    printf("[1]��ħ�޻�(700��) [2]���Ǵ�(1000��) [3]���ڿ�(500��)");
    scanf("%d", &choice);
    int price;
    int money_1000;
    int money_500;
    int money_100;
    int change;
    if(choice == 1){
        price = 700;
    }
    else if(choice == 2){
        price = 1000;
    }
    else if(choice == 3){
        price = 500;
    }

    change = money - price;

    if(change < 0){
        printf("���� �����ؿ� �Ф�");
        change = money;
    }
    printf("�ܵ� : %d\n", change);

    money_1000 = change / 1000;
    money_500 = change % 1000 / 500;
    money_100 = change % 500 / 100;
    
    printf("õ�� : %d��, ����� : %d��, ��� : %d��",money_1000, money_500, money_100);
	return 0;
}
#endif

/***********************************************************/
// [5-����] ���� ���α׷�
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{   
    int a, b;
	char c;
    
    printf("��Ģ���� �Է�(����) : ");
    scanf("%d %c %d", &a, &c, &b);

    if(c == '+'){
        printf("%d%c%d=%d",a,c,b,a+b);
    }
    else if(c == '-'){
        printf("%d%c%d=%d",a,c,b,a-b);
    }
    else if(c == '*'){
        printf("%d%c%d=%d",a,c,b,a*b);
    }
    else if(c == '/'){
        printf("%d%c%d=%d",a,c,b,a/b);
    }
    else{
        return -1;
    }
	return 0;
}
#endif

