/***********************************************************/
// [8-1] �迭�� ����� ���
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
	int num; //������ ����
    num = 10;//������ �Ҵ� (�����̸� �ʱ�ȭ)
    num = 20;//������ ���Ҵ�
    printf("%d\n", num); //������ ���

    int array[5]; //�迭�� ����
    array[0] = 10; // �迭����� �Ҵ�
    array[1] = 20; 
    //�迭��Ұ� �ʱ�ȭ �Ǿ� ���� �ʴٸ� ��� �� ������ ���� ��µȴ�.

    printf("%d %d\n",array[0], array[1]);
    // printf("%d %d %d\n", array[2], array[3], array[4]);

	return 0;
}
#endif

/***********************************************************/
// [8-2] �迭�� ����� ���
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
	int array[5] = {8, 4, 99, 6, 7};

    printf("array�� ����ִ� Ȧ���� ");
    for(int i = 0; i < 5; i++){
        if(array[i] % 2 == 1){
            printf("%d ", array[i]);
        }
    }
    printf("�̴�\n");
	return 0;
}
#endif

/***********************************************************/
// [8-3] sizeof �����ڸ� ����� �迭
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
    int arr[5];
    int num;
    int result = 0;
	for(int i = 0; i < 5; i++){
        printf("%d���� ������ �Է��ϼ��� : ", i+1);
        scanf("%d", &num);
        arr[i] = num;
        result += arr[i];
    }

    printf("���� : %d��, ", result);
    printf("��� : %d��", result/(sizeof(arr) / sizeof(int)));

	return 0;
}
#endif

/***********************************************************/
// [8-4] char �� �迭�� ����� �ʱ�ȭ
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
    //�迭�� ���ڿ��� �����Ұ�� null (\0)�� ������ ũ�⸦ �������ٰ�
	int array[5] = { 1, 2, 3, 4, 5};
    char fruit[6] = {'a', 'p', 'p', 'l', 'e'};
    char fruit2[6] = "apple";

    char my_name[10];
    my_name[0] = 'c';
    my_name[1] = 'h';
    my_name[2] = 'i';
    my_name[3] = '\0';

    printf("%s", my_name);
    /*
    for(int i = 0 ; i < 5; i++){
        printf("%c", fruit[i]);
    }
    printf("\n");
    printf("%s", fruit2);
    */
    
	return 0;
}
#endif

/***********************************************************/
// [8-5] ���ڿ��� �����ϴ� strcpy �Լ�
/***********************************************************/

#if 0
#include <stdio.h>
#include <string.h>

int main(void)
{
    char fruit[100] = "apple";
    printf("���� ���� : %s\n", fruit);
    
    //strcpy(���� ���ڿ�, ���ο� ���ڿ�);
    strcpy(fruit, "banana");
    printf("���ο� ���� : %s\n", fruit);


    char cat_name[100] = "�̸��� �����ּ��� : ";
    char new_name[100];
    
    printf("%s", cat_name);
    scanf("%s", new_name);
    strcpy(cat_name, new_name);
    printf("%s", cat_name);
	return 0;
}
#endif

/***********************************************************/
// [8-6] gets(), puts() ������� �Է¹ޱ�
/***********************************************************/

#if 0
#include <stdio.h>
#include <string.h>

int main(void)
{
    char inputs[100];

    printf("������ ���� �޴� �Է� : ");
    gets(inputs);

    puts(inputs);

	return 0;
}
#endif

/***********************************************************/
// [8-����] ��ҹ��� ��ȯ ���α׷�
/***********************************************************/

#if 0
#include <stdio.h>
#include <string.h>

int main(void)
{
	char str[100];
    int count = 0;
    printf("���� �Է� : ");
    gets(str);

    for(int i = 0 ; i < sizeof(str) / sizeof(char); i++){
        if(str[i] <= 90 && str[i] >= 65){
            str[i] += 32;
            count++;
        }
    }
    printf("�ٲ� ���� : %s\n", str);
    printf("�ٲ� ���� �� : %d\n", count);

    char test[100] = "HELLO WORLD";
    printf("%s", strlwr(test));

	return 0;
}
#endif

/***********************************************************/
// [8-0] ����
/***********************************************************/

#if 1
#include <stdio.h>

int main(void)
{
    // ���� -> Ž���� �ս��� �ϱ� ����
    int array[6] = {1, 13, 21, 7, 31, 28};

    // 1. ���� ����
    //  cycle 1
    /*
    if(array[0] > array[1]){
        int temp;
        temp = array[0];
        array[0] = array[1];
        array[1] = temp;
    }
    if(array[1] > array[2]){
        int temp;
        temp = array[1];
        array[1] = array[2];
        array[2] = temp;
    }
    */
    /*
    for (int i = 0; i < 5; i++)
    {
        if (array[i] > array[i + 1])
        {
            int temp;
            temp = array[i];
            array[i] = array[i + 1];
            array[i + 1] = temp;
        }
    }
    
    for (int i = 0; i < 4; i++)
    {
        if (array[i] > array[i + 1])
        {
            int temp;
            temp = array[i];
            array[i] = array[i + 1];
            array[i + 1] = temp;
        }
    }
    */
    
    for (int j = 5; j > 0; j--)
    {
        for (int i = 0; i < j; i++)
        {
            if (array[i] > array[i + 1])
            {
                int temp;
                temp = array[i];
                array[i] = array[i + 1];
                array[i + 1] = temp;
            }
        }
    }

    for (int i = 0; i < 6; i++)
    {
        printf("%d ", array[i]);
    }

    return 0;
}
#endif