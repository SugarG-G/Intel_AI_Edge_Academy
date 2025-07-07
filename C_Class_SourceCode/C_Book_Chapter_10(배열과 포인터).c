/***********************************************************/
// [10-1] �迭�� ���� ������ ������ �迭 ��� ���
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
	int array[3]; // 3ĭ �迭 �� 12byte.

    printf("%d\n", array);
    printf("%d\n",&array[0]);
    printf("%d\n", (array + 1));

    array[0] = 10;
    *(array + 1) = 20;
    // *(array + 3) = 10; ó�� ������ ��� �ּ� ��� ����

    for(int i = 0; i < 3; i++){
        printf("%d��° ��� : %d ", i, array[i]);
    }

	return 0;
}
#endif

/***********************************************************/
// [10-2] �迭��ó�� ���Ǵ� ������
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
	int array[3];
    int *pa = array;

    *pa = 10;
    // 20�� �迭 �� ��° ���(�ε��� 1)�� �Ҵ�
    //1.
    //  array[1] = 20;
    
    //2.
    //  *(array + 1) = 20;
    
    //3.
    //  *(pa + 1) = 20;
    
    //4.
    //  pa++, *pa = 20;

    for(int i = 0; i < 3; i++){
        printf("%d��° ��� : %d ", i, array[i] );
    }
    printf("\n");

    printf("�迭 ��ü�� ���� : %d\n", sizeof(array));
    printf("������ �ϳ��� ���� : %d\n", sizeof(pa));
    

	return 0;
}
#endif

/***********************************************************/
// [10-3] �����͸� �̿��� �迭�� �� ���
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
    int array[3] = {10, 20, 30};
    int *pa = array;

    printf("�迭�� �� : ");
    for(int i = 0; i < 3 ; i++){
        //printf("%d ", array[i]);
        
        // printf("%d ", *pa);
        // pa++;

        printf("%d ", *(pa++)); //���� ���� ������ ���� �ּ� ���� Ȯ���Ͽ� ������� üũ
        // printf("%d ", *(++pa)); // ���� ���� ������ ����� ���ϴ� ����� ������ ���� �� �ִ�.
    }
    pa = array; // pa�� ������ �Ұ�� �ٽ� �ּҰ��� �Ҵ� �ʿ�

	return 0;
}
#endif

/***********************************************************/
// [10-4] �������� �E���� ���� ����
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
    int array[5] = {10, 20, 30, 40, 50};
    int *pa = array;
    int *pb = array + 3;

    pa++;
    printf("pb - pa : %u\n", pb - pa);

    // �� ������ ��
    // �� �տ� �ִ� (�ε����� ����) ��� ���
    if(pa < pb){
        printf("%d\n", *pa);
    }
    else{
        printf("%d\n", *pb);
    }

	return 0;
}
#endif

/***********************************************************/
// [10-5] �迭�� ó���ϴ� �Լ�
/***********************************************************/

#if 0
#include <stdio.h>

void print_array(int *pa){
    for(int i = 0; i < 5; i++){
        printf("%d ", pa[i]);
    }
}

int main(void)
{
	int array[5] = {10, 20, 30, 40, 50};
    print_array(array);

	return 0;
}
#endif

/***********************************************************/
// [10-6] ũ�Ⱑ �ٸ� �迭�� ó���ϴ� �Լ�
/***********************************************************/

#if 0
#include <stdio.h>

void print_array(int *pa, int size){

    for(int i = 0; i < size; i++){
        printf("%d ", pa[i]);
    }
    printf("\n");
}

int main(void)
{
	int array[5] = {10, 20, 30, 40, 50};
    int array2[7] = {10, 20, 30, 40, 50, 60, 70};

    print_array(array, 5);
    print_array(array2, 7);

	return 0;
}
#endif

/***********************************************************/
// [10-7] �迭�� ���� �Է��ϴ� �Լ�
/***********************************************************/

#if 0
#include <stdio.h>

void input_array(int *pa, int size);
void print_array(int *pa, int size);
void find_max(int *pa, int size);

int main(void)
{
    int array[5] = {0,};
    
    input_array(array, sizeof(array) / sizeof(int));
    find_max(array, 5);
    
	return 0;
}

void input_array(int *pa, int size){
    for(int i = 0; i < size; i++){
        scanf("%d", &pa[i]);
    }
    // print_array(pa, size);
}

void print_array(int *pa, int size){
    for(int i = 0; i < size; i++){
        printf("%d ",pa[i]);
    }
    printf("\n");
}

void find_max(int *pa, int size){
    int max = pa[0];
    //30 10 40 20 50
    //10 20 30 40 50
    for(int i = 0; i < size; i++){
        if(max < pa[i]){
            max = pa[i];
        }
    }
    printf("%d\n", max);
}

#endif

/***********************************************************/
// [10-����] �ζ� ��ȣ ���� ���α׷�
/***********************************************************/

#if 0
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_lotto(int *pa, int size){
    for(int i = 0; i < size; i++){
        printf("%d ", pa[i]);
    }
    printf("\n");
}

void input_lotto(int *pa, int size){
    srand(time(NULL));
        
    for(int i = 0; i < size; i++){
        pa[i] = rand() % 45 + 1;
        // printf("%d ��° �ζ� ��ȣ �Է� : ", (i+1));
        // scanf("%d", &pa[i]);
    
        for(int j = 0; j < i; j++){
            if(pa[i] == pa[j]){
                printf("�ٽ� �Է��ϼ���.\n");
                i--;
                break;
            }
        }
    }
}


int main(void)
{
    int lotto[6] = {0,};
    
    input_lotto(lotto, 6);
    print_lotto(lotto, 6);

	// 6���� ������ �Է�(1 ~ 45)
    // �ش� ���� �̹� �����ϸ� �ٽ� �Է�

	return 0;
}

#endif

/***********************************************************/
// [10-����] ���� �˰���
/***********************************************************/

#if 1
#include <stdio.h>

void swap(int *pa, int *pb)
{
    int temp;
    temp = *pa;
    *pa = *pb;
    *pb = temp;
}

void print_array(int *pa, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", pa[i]);
    }
    printf("\n");
}

void bubble_sort(int *pa, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            if (pa[i] > pa[j])
            {
                swap(&pa[i], &pa[j]);
            }
        }
    }
}

// ���� ������ ������ ��������
// cycle�� �ִ� ġȯ 1ȸ
void selection_sort(int *pa, int size)
{
    int max_index = 0;
    int max = pa[0];
    /*
    // 1cycle
    for(int i = 0; i < size; i++){
        if(pa[i] > max){
            max = pa[i];
            max_index = i;
        }
    }
    swap(&pa[max_index], &pa[size - 1]);

    // 2cycle
    max = pa[0];
    max_index = 0;
    for(int i = 0; i < size - 1; i++){
        if(pa[i] > max){
            max = pa[i];
            max_index = i;
        }
    }
    swap(&pa[max_index], &pa[size - 2]);
    */
    
    for (int j = 0; j < size - 1; j++)
    {
        max = pa[0];
        max_index = 0;
        for (int i = 0; i < size - j; i++)
        {
            if (pa[i] > max)
            {
                max = pa[i];
                max_index = i;
            }
        }
        swap(&pa[max_index], &pa[size - (j + 1)]);
    }
}

void binary_search(int *pa, int size, int search){
    int low_index = 0;
    int high_index = size - 1;
    int mid_index = (low_index + high_index) / 2;

    while(low_index <= high_index){
        if(pa[mid_index] > search){
            high_index = mid_index - 1;
            mid_index = (low_index + high_index) / 2;
        }
        else if(pa[mid_index] < search){
            low_index = mid_index + 1;
            mid_index = (low_index + high_index) / 2;
        }
        else{
            printf("ã���� �ϴ� %d�� index %d�� �ֽ��ϴ�.", search, mid_index);
            break;
        }
    }
}

    int main(void)
    {
        int array[10] = {1, 32, 19, 27, 23, 20, 15, 96, 25, 37};
        int size = sizeof(array) / sizeof(int);
        printf("�迭 ���� : ");
        print_array(array, size);

        bubble_sort(array, size);
        printf("���� ���� �� : ");
        print_array(array, size);

        selection_sort(array, size);
        printf("���� ���� �� : ");
        print_array(array, size);

        int search = 19;
        binary_search(array, size, search); // ã���� �ϴ� 23�� 4��° �ֽ��ϴ�.

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