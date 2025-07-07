/***********************************************************/
// [17-1] ����ü ���� �� ���
/***********************************************************/

#if 0
#include <stdio.h>
#pragma pack(3); // ����Ʈ ����̾��Ʈ 1�� ����

struct contact
{

    // ��� ����
    char *name;
    int age;
    char *mbti;
};

struct student
{
    char ch1;
    short num;
    char ch2;
    int score;
    double grade;
    char ch3;
};

struct exam{
    char c1;
    int num;
};

int main(void)
{
    struct exam e1;
    printf("e1�� ũ�� : %d\n", sizeof(e1));


    struct contact person_1;
    struct contact person_2;
    

    person_1.name = "��ġ��";
    person_1.age = 19;
    person_1.mbti = "ENTP";

    person_2.name = "������";
    person_2.age = 33;
    person_2.mbti = "ISTP";

    printf("�̸� : %s, ���� : %d��, MBIT : %s\n", person_1.name, person_1.age, person_1.mbti);
    printf("�̸� : %s, ���� : %d��, MBIT : %s\n", person_2.name, person_2.age, person_2.mbti);

    struct student s1;
    printf("s1�� ũ�� : %d\n", sizeof(s1));

    

    return 0;
}
#endif

/***********************************************************/
// [17-2] ����� �ڷ���
/***********************************************************/

#if 0
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct student{
    int id;
    double grade;
};

struct profile{
    char name[20];
    int age;
    double height;
    char *info;

    struct student st;
};

int main(void)
{
	struct profile p1;
    strcpy(p1.name,"��ġ��");
    p1.age = 19;
    p1.height = 2000;

    printf("�ڱ�Ұ� : ");
    char temp[100];
    gets(p1.info);
    p1.info = (char *)malloc(strlen(temp) + 1);
    strcpy(p1.info, temp);
    p1.st.grade = 4.5;
    p1.st.id = 2025;
    
    printf("�̸� : %s, ���� : %d, Ű : %.1lfcm\n", p1.name, p1.age, p1.height);
    printf("�ڱ�Ұ� : %s", p1.info);
    printf("�й� : %d, ���� : %.1lf", p1.st.id, p1.st.grade);
    
    free(temp);

	return 0;
}
#endif

/***********************************************************/
// [17-3] �ְ� ������ �л� ������ ���
/***********************************************************/

#if 0
#include <stdio.h>

struct student
{
    int id;
    char name[20];
    double grade;
};

int main(void)
{
    struct student s1 = {315, "ȫ�浿", 2.4},
                   s2 = {316, "�Ӳ���", 3.7},
                   s3 = {317, "��û��", 4.5};

    // s1, s2, s3�� ������ Ž���ϸ鼭
    // ���� ���� ������ ������ �ִ� �����
    // ������ ���� �й�, �̸�, ������ ���
    // �й� : ???, �̸� : ???, ���� : ???

    double max_grade = s1.grade;
    int max_index = 0;

    if(max_grade < s2.grade){
        max_grade = s2.grade;
        max_index = 1;
    }
    if(max_grade < s3.grade){
        max_grade = s3.grade;
        max_index = 2;
    }

    switch (max_index){
        case 0 : printf("�й� : %d, �̸� : %s, ���� : %.1lf", s1.id, s1.name, s1.grade); break;
        case 1 : printf("�й� : %d, �̸� : %s, ���� : %.1lf", s2.id, s2.name, s2.grade); break;
        case 2 : printf("�й� : %d, �̸� : %s, ���� : %.1lf", s3.id, s3.name, s3.grade); break;
    }
    printf("\n");
    //���� ���� ����ü > max
    //����ü�� �ᱹ �ڷ���(����� ���ǵ�)
    //����ü�� ���� �����ڸ� ��� ����
    struct student max = s1;

    if(s2.grade > max.grade) max = s2;
    if(s3.grade > max.grade) max = s3;

    printf("�й� : %d, �̸� : %s, ���� : %.1lf", max.id, max.name, max.grade);

    return 0;
}
#endif

/***********************************************************/
// [17-6] ����ü �����Ϳ� ���� ��� ���� ������
/***********************************************************/

#if 0
#include <stdio.h>

struct score{
    int kor;
    int eng;
    int math;
};

int main(void)
{
	struct score s1 = {70, 80, 90};
    struct score *ps = &s1;

    printf("���� : %d, ���� : %d, ���� : %d", s1.kor, (*ps).eng, ps->math); // -> : ���� ��� ���� ������.

	return 0;
}
#endif

/***********************************************************/
// [17-7] ����ü �迭
/***********************************************************/

#if 0
#include <stdio.h>

struct student
{
    int id;        // �й�
    char name[20]; // �̸�
    double grade;  // ����
};

void print_list(struct student *lp, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("�й� : %d, �̸� : %s, ���� : %.1lf\n", lp[i].id, (*(lp + i)).name, (lp+i) -> grade);
    }
}

int main(void)
{
    struct student students[3] = {
        {315, "ȫ�浿", 2.4},
        {316, "�Ӳ���", 3.7},
        {317, "��û��", 4.5}};

    // 3���� ������ 3������ ���
    //  �й� �̸� ����
    //  for(int i = 0; i < 3; i++){
    //      printf("�й� : %d, �̸� : %s, ���� : %.1lf\n", students[i].id, students[i].name, students[i].grade);
    //  }

    print_list(students, 3);

        return 0;
}
#endif

/***********************************************************/
// [17-9] �ڱ� ���� ����ü
/***********************************************************/

#if 0
#include <stdio.h>

struct list
{
    int num;
    struct list *next;
};


int main(void)
{
    //list : Linked List (���� ����Ʈ)
    struct list a = {10, }, b = {20, }, c = {30, };
    
    // ó�� ���� ����Ű�� ���� �ּ�
    struct list *head = &a;

    a.next = &b;
    b.next = &c;

    printf("a : %d, a�� ����Ű�� �ּ� : %u\n", a.num, a.next);
    printf("a : %d, b�� ����Ű�� �ּ� : %u\n", b.num, b.next);
    printf("a : %d, c�� ����Ű�� �ּ� : %u\n", c.num, c.next);
    printf("\n");
    printf("a : %d, a�� ����Ű�� �ּ� : %u\n", a.num, a.next);
    printf("b : %d, b�� ����Ű�� �ּ� : %u\n", a.next->num, a.next->next);
    printf("c : %d, c�� ����Ű�� �ּ� : %u\n", a.next->next->num, a.next->next->next);

    printf("list all : ");
    struct list *current = head;
    // printf("%d ", current->num);
    // current = current->next;
    // printf("%d ", current->num);
    // current = current->next;
    // printf("%d ", current->num);

    while (1)
    {
        printf("%d ", current->num);
        current = current->next;
    }
    
	
	return 0;
}
#endif

/***********************************************************/
// [17-10] ����ü union
/***********************************************************/

#if 0
#include <stdio.h>

union data
{
    int i;
    double d;
} weather_data;

int main(void)
{
    // ��Ŷ�� ���� Ÿ ����̽�����
    // data�� �����ϰ��� �Ѵ�.
    // 2���� data�� ���µ�
    // 1. ������ ����
    // 2. ������ ���

    // ��) 84,17.1,85,17.2,86,17.3

    char *str = "84";
    int count = 1;
    if (count % 2 == 1)
    {
        weather_data.i = 84;
        count++;
    }
    else
    {
        weather_data.d = 17.1;
        count++;
    }
    return 0;
}
#endif

/***********************************************************/
// [17-11] ������
/***********************************************************/

#if 0
#include <stdio.h>

enum discount
{
    NOMAL,
    EARLY = 4000,
    TELECOM = 2000
};

int main(void)
{
    // ��ȭ ���� ���α׷�
    int menu;
    printf("[1]���� [2]���� [3]��Ż� ����\n");
    printf("���� ������ �����ϼ��� : ");
    scanf("%d", &menu);

    int ticket_pirce = 14000;

    switch (menu)
    {
        case 1:
            ticket_pirce - NOMAL;
            break;

        case 2:
            ticket_pirce -= EARLY;
            break;

        case 3:
            ticket_pirce -= TELECOM;
            break;

        default:
            break;
    }

    printf("���� �ݾ� : %d��", ticket_pirce);

    return 0;
}
#endif

/***********************************************************/
// [17-12] tpyedef ����� �ڷ��� ������
/***********************************************************/

#if 0
#include <stdio.h>

typedef signed int t;

struct student
{
    int num;
    double grade;
};

typedef struct student Student;

typedef struct
{
    char name[20];
    int age;
} Profile;

int main(void)
{
    // ����ü�� �������ϸ�
    // �빮�ڷ� ��������!!
    Student s1 = {315, 3.7};
    Profile p1 = {"������", 17};

    int a = 10;
    t b = 20;

    printf("%d %d", a, b);

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