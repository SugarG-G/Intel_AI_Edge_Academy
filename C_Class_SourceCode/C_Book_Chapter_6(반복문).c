/***********************************************************/
// [6-1]�ڸ��� ��� ���α׷�
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
	int digits = 0;
    int num;
    printf("���� �Է� : ");
    scanf("%d", &num);

    //���� �ݺ� Ƚ���� ������ ���� ���� �� while ���
    //���� �ݺ� Ƚ���� ������ ���� �� for ���
    while(num != 0){
        digits++;
        num = num / 10;
    }

    printf("%d�ڸ� �����Դϴ�.", digits);

	return 0;
}
#endif

/***********************************************************/
// [6-2] 10���� ���� �� �Է� ���α׷�
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
    int a;
    printf("���� �Է� : ");
    scanf("%d", &a);
    while(a < 10){
        printf("���� �Է� : ");
        scanf("%d", &a);
    }
    printf("����Ǿ����ϴ�.");

	return 0;
}
#endif

/***********************************************************/
// [6-3] ������ ��� ���α׷�
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
	int num, sum = 0;
    printf("���� �Է� : ");
    scanf("%d", &num);

    while(num != -1){
        sum += num;
        printf("���� ��� : %d\n", sum);
        printf("���� �Է� : ");
        scanf("%d", &num);
    }
    printf("����Ǿ����ϴ�.");

	return 0;
}
#endif

/***********************************************************/
// [6-4] for�� ����
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
    /*
    for(�ʱ��; ���ǽ�; ������){
        ���๮��;
    }
    */
    // 1 ~ 10���� ���

    for (int i = 1; i <= 10; i++)
    {
        printf("%d ", i);
    }
    printf("\n");

    // 27 ~ 57���� ���

    for (int i = 27; i <= 57; i++)
    {
        printf("%d ", i);
    }
    printf("\n");

    // 96 ~ 53���� ���� ���
    for (int i = 96; i >= 53; i--)
    {
        printf("%d ", i);
    }
    printf("\n");

    // 1 ~ 100���� �� 3�� ����� ���
    // 1 ~ 100���� �� 3�� ����̸鼭 5�� ����� �ⷫ
    // 1 ~ 100���� �� 3�� ����̸鼭 5�� ����� ���� �����ϰ� ���
    for (int i = 1; i <= 100; i++)
    {
        if (i % 3 == 0 && i % 5 == 0)
        {
            continue;
        }
        printf("%d ", i);
    }

    return 0;
}
#endif

/***********************************************************/
// [6-5] ��� ����ϱ�
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
    int a;
    printf("�ڿ����� �Է��ϼ��� : ");
    scanf("%d", &a);

    for (int i = 1; i <= 10; i++)
    {
        printf("%d ", a * i);
    }

    return 0;
}
#endif

/***********************************************************/
// [6-6] ������ ����ϱ�
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
	for(int i = 1; i <= 9; i++){
        printf("%d x %d = %d\n",2, i, 2*i);
    }
	return 0;
}
#endif

/***********************************************************/
// [6-7] ��� ����ϱ�
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
    int number;
	printf("������ �Է����ּ��� : ");
    scanf("%d", &number);

    for(int i = 1; i <= number / 2; i++){
        if(32%i == 0){
            printf("%d ", i);
        }
    }
    printf("%d", number);

	return 0;
}
#endif

/***********************************************************/
// [6-����] ���� ��Ģ
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
	//�ʱ�� ���ǽ� �������� �˱� ���� �Ѵ�.
    for(int i = 7; i <= 16; i++){
        printf("%d", i - 6);
    }
	return 0;
}
#endif

/***********************************************************/
// [6-��������] ������ do ~ while
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
    int sum = 0;
    int num;
    do{
        
        printf("���� �Է� : ");
        scanf("%d", &num);

        printf("���� �հ� : %d\n", sum += num);
    }
    while(num != -1);

	return 0;
}
#endif
/***********************************************************/
// [6-���̽��] ���ѹݺ���
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
    int num, sum = 0;

    while(1){
        printf("���� �Է� : ");
        scanf("%d", &num);
        if(num == -1){
            break;
        }

        sum += num;

        printf("���� �հ� : %d\n", num);
    }

	return 0;
}
#endif

/***********************************************************/
// [6-8] ���̾�Ʈ ���� ���α׷�
/***********************************************************/

#if 0

#include <stdio.h>

int main(void)
{
	int current_weight = 0, goal_weight = 0;
    int week_weight = 0, loss_weight = 0;
    int week = 0;

    printf("���� ������ : ");
    scanf("%d", &current_weight);
    printf("��ǥ ������ : ");
    scanf("%d", &goal_weight);
    
    while(1){
        week++;
        printf("%d���� ���� ������ : ", week);
        scanf("%d", &loss_weight);
        current_weight -= loss_weight;
        if(goal_weight >= current_weight){
            printf("%dkg �޼�!!", current_weight);
            break;
        }
    }
    printf("�����մϴ�.");

	return 0;
}
#endif

/***********************************************************/
// [6-9] �α��� ���α׷�
/***********************************************************/

#if 0
#include <stdio.h>
#include <string.h>

int main(void)
{
    // �ð� ���ø� �غ��ſ�!!
    // �⺻ �ڷ���
    // ������ : short, int, long, long long
    // �Ǽ��� : float, double, long double
    // ������ : char
    // ���� ���� (�� ����)
    // ũ��? �۴�? ����?

    char fruit[20] = "banana";
    char fruit2[20] = "banana";
    if (fruit == fruit2) // �⺻ �ڷ����� �ƴϱ� ������ �� �Ұ�
    {
        printf("�����ϴ�");
    }
    // <string.h> �ȿ� strcmp()
    // 0 : �� ���ڿ��� ����

    printf("%d", strcmp(fruit, fruit2));

    char login_id[20] = "nayeho";
    char login_pw[20] = "1234";

    while (1)
    {
        char id[20], pw[20];
        printf("ID : ");
        scanf("%s", id);
        printf("PW : ");
        scanf("%s", pw);

        if (!strcmp(id, login_id) && !strcmp(pw, login_pw) == 1)
        {
            printf("�α��� ����");
            break;
        }
        else
        {
            printf("�α��� ����");
        }
    }
    return 0;
}
#endif

/***********************************************************/
// [6-10] up-down ���α׷�
/***********************************************************/

#if 0
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    srand(time(NULL));

    int random_number = rand() % 100 + 1;
    int a;
    // printf("%d",random_number);
    while(1){
        printf("���� �Է� : ");
        scanf("%d", &a);

        if(a < random_number){
            printf("�Է��� ���ں��� Ů�ϴ�.\n");
        }
        else if(a > random_number){
            printf("�Է��� ���ں��� �۽��ϴ�.\n");
        }
        else if (a == random_number){
            printf("����\n");
            break;
        }
    }

	// printf("%d\n", rand() % 100 + 1);
    // printf("%d\n", rand() % 100 + 1);

	return 0;
}
#endif

/***********************************************************/
// [6-11] ����� ����
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
	for(int i = 0; i < 5; i++){
        for(int j = 0 ; j < 5; j++){
            printf("*");
        }
        printf("\n");
    }
	return 0;
}
#endif

/***********************************************************/
// [6-12] ������ ���α׷�
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
	for(int i = 2; i <= 9; i++){
        for(int j = 1; j <= 9; j++){
            printf("%d x %d = %d\n", i, j, i * j);
        }
    }
	return 0;
}
#endif

/***********************************************************/
// [6-13] ����� ���� 1
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
	for(int j = 0; j < 5; j++){
        for(int i = 0; i <= j; i++){
            printf("*");
        }
        printf("\n");
    }
	return 0;
}
#endif

/***********************************************************/
// [6-14] ����� ���� 2
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
    for (int j = 0; j < 5; j++)
    {
        for (int i = j; i < 5; i++)
        {
            printf(" ");
        }
        for (int k = 0; k <= j; k++)
        {
            printf("*");
        }
        printf("\n");
    }

    return 0;
}
#endif

/***********************************************************/
// [6-15] ����� ���� 5
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
    for (int j = 1; j <= 5; j++)
    {
        for (int i = 1; i <= j - 1; i++)
        {
            printf(" ");
        }
        for (int i = 1; i <= 6 - j; i++)
        {
            printf("*");
        }
        printf("\n");
    }
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