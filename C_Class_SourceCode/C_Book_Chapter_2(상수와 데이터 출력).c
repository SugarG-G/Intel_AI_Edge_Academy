/* 
    �ۼ��� : ��ġ��
    �ۼ��� : 2025.04.08. AM 12:42:00
    ���� : 10�� 20�� ���ϴ� ���α׷�
*/
#if 0
int main() 
{
    10 + 20;

    return 0;
}
#endif

/* 
�ۼ��� : ��ġ��
�ۼ��� : 2025.04.08. AM 12:47:00
���� : ���ڿ��� ȭ�鿡 ����ϴ� ���α׷�
*/
#if 0

#include <stdio.h>

int main(){
    printf("Be Happy");
    printf("My friend");

    return 0;
}
#endif

/* 
    �ۼ��� : ��ġ��
    �ۼ��� : 2025.04.08. AM 12:53:00
    ���� : ���� ���ڸ� ����� ���
*/
#if 0
#include <stdio.h>

int main(){
    printf("Be Happy\n");
    printf("My\tfriend\n"); // \t = tep
    printf("Hello\tWorld!\n");
    printf("Goot\bd\tChance\n"); // \b = back space(Ŀ�� ��ġ�� ��ĭ ������ �̵�)
    printf("Cow\rW\a\n"); // \r = ĳ���� ����(Ŀ�� ��ġ�� �� ������ �̵�), \a = �˶�

    return 0;
}
#endif

/* 
    �ۼ��� : ��ġ��
    �ۼ��� : 2025.04.08. AM 14:09:00
    ���� : ������ �Ǽ��� ���
*/

#if 0

#include <stdio.h>

int main(){
    printf("%d\n", 10);
    printf("%lf\n", 3.4);
    printf("%.1lf\n", 3.45); // .1lf�Ҽ��� ���� ù° �ڸ����� ��� (�ݿø�)
    printf("%.10lf\n", 3.4);

    printf("%d�� %d�� ���� %d�Դϴ�.\n", 10, 20, 10 + 20);
    printf("%.lf - %.1lf = %.1lf\n", 3.4, 1.2, 3.4 - 1.2);
    printf("%.lf - %.1lf = %.1lf\n", 3.3, 1.1, 3.3 - 1.1);

    return 0;
}
#endif

/* 
    �ۼ��� : ��ġ��
    �ۼ��� : 2025.04.08. AM 14:30:00
    ���� : 3���� ������ ���� ���
*/

#if 0

#include <stdio.h>

int main(){
    printf("%d\n", 12);
    printf("%d\n", 014);
    printf("%d\n", 0xc);

    printf("%o\n", 100);
    printf("%x\n", 100);
    printf("%X\n", 100);

    return 0;
}
#endif

/* 
    �ۼ��� : ��ġ��
    �ۼ��� : 2025.04.08. AM 14:46:00
    ���� : ���ڿ� ���ڿ� �������� ���
*/

#if 0

#include <stdio.h>

int main(){
    printf("%c\n", 'A');
    printf("%s\n", "A");
    printf("%c�� %s �Դϴ�.", '1', "first");
    
    return 0;
}

#endif