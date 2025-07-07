/***********************************************************/
// [17-1] 구조체 선언 및 사용
/***********************************************************/

#if 0
#include <stdio.h>
#pragma pack(3); // 바이트 얼라이어먼트 1로 설정

struct contact
{

    // 멤버 선언
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
    printf("e1의 크기 : %d\n", sizeof(e1));


    struct contact person_1;
    struct contact person_2;
    

    person_1.name = "윤치영";
    person_1.age = 19;
    person_1.mbti = "ENTP";

    person_2.name = "아이유";
    person_2.age = 33;
    person_2.mbti = "ISTP";

    printf("이름 : %s, 나이 : %d세, MBIT : %s\n", person_1.name, person_1.age, person_1.mbti);
    printf("이름 : %s, 나이 : %d세, MBIT : %s\n", person_2.name, person_2.age, person_2.mbti);

    struct student s1;
    printf("s1의 크기 : %d\n", sizeof(s1));

    

    return 0;
}
#endif

/***********************************************************/
// [17-2] 멤버의 자료형
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
    strcpy(p1.name,"윤치영");
    p1.age = 19;
    p1.height = 2000;

    printf("자기소게 : ");
    char temp[100];
    gets(p1.info);
    p1.info = (char *)malloc(strlen(temp) + 1);
    strcpy(p1.info, temp);
    p1.st.grade = 4.5;
    p1.st.id = 2025;
    
    printf("이름 : %s, 나이 : %d, 키 : %.1lfcm\n", p1.name, p1.age, p1.height);
    printf("자기소게 : %s", p1.info);
    printf("학번 : %d, 학점 : %.1lf", p1.st.id, p1.st.grade);
    
    free(temp);

	return 0;
}
#endif

/***********************************************************/
// [17-3] 최고 학점의 학생 데이터 출력
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
    struct student s1 = {315, "홍길동", 2.4},
                   s2 = {316, "임꺽정", 3.7},
                   s3 = {317, "심청이", 4.5};

    // s1, s2, s3의 학점을 탐색하면서
    // 가장 높은 학점을 가지고 있는 사람의
    // 다음과 같이 학번, 이름, 학점을 출력
    // 학번 : ???, 이름 : ???, 학점 : ???

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
        case 0 : printf("학번 : %d, 이름 : %s, 학점 : %.1lf", s1.id, s1.name, s1.grade); break;
        case 1 : printf("학번 : %d, 이름 : %s, 학점 : %.1lf", s2.id, s2.name, s2.grade); break;
        case 2 : printf("학번 : %d, 이름 : %s, 학점 : %.1lf", s3.id, s3.name, s3.grade); break;
    }
    printf("\n");
    //가장 높은 구조체 > max
    //구조체는 결국 자료형(사용자 정의된)
    //구조체는 대입 연산자를 사용 가능
    struct student max = s1;

    if(s2.grade > max.grade) max = s2;
    if(s3.grade > max.grade) max = s3;

    printf("학번 : %d, 이름 : %s, 학점 : %.1lf", max.id, max.name, max.grade);

    return 0;
}
#endif

/***********************************************************/
// [17-6] 구조체 포인터와 간접 멤버 접근 연산자
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

    printf("국어 : %d, 영어 : %d, 수학 : %d", s1.kor, (*ps).eng, ps->math); // -> : 간접 멤버 접근 연산자.

	return 0;
}
#endif

/***********************************************************/
// [17-7] 구조체 배열
/***********************************************************/

#if 0
#include <stdio.h>

struct student
{
    int id;        // 학번
    char name[20]; // 이름
    double grade;  // 학점
};

void print_list(struct student *lp, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("학번 : %d, 이름 : %s, 학점 : %.1lf\n", lp[i].id, (*(lp + i)).name, (lp+i) -> grade);
    }
}

int main(void)
{
    struct student students[3] = {
        {315, "홍길동", 2.4},
        {316, "임꺽정", 3.7},
        {317, "심청이", 4.5}};

    // 3명의 정보를 3행으로 출력
    //  학번 이름 학점
    //  for(int i = 0; i < 3; i++){
    //      printf("학번 : %d, 이름 : %s, 학점 : %.1lf\n", students[i].id, students[i].name, students[i].grade);
    //  }

    print_list(students, 3);

        return 0;
}
#endif

/***********************************************************/
// [17-9] 자기 참조 구조체
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
    //list : Linked List (연결 리스트)
    struct list a = {10, }, b = {20, }, c = {30, };
    
    // 처음 값을 가리키기 위한 주소
    struct list *head = &a;

    a.next = &b;
    b.next = &c;

    printf("a : %d, a가 가리키는 주소 : %u\n", a.num, a.next);
    printf("a : %d, b가 가리키는 주소 : %u\n", b.num, b.next);
    printf("a : %d, c가 가리키는 주소 : %u\n", c.num, c.next);
    printf("\n");
    printf("a : %d, a가 가리키는 주소 : %u\n", a.num, a.next);
    printf("b : %d, b가 가리키는 주소 : %u\n", a.next->num, a.next->next);
    printf("c : %d, c가 가리키는 주소 : %u\n", a.next->next->num, a.next->next->next);

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
// [17-10] 공용체 union
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
    // 패킷을 통해 타 디바이스에서
    // data를 전송하고자 한다.
    // 2개의 data가 오는데
    // 1. 정수형 습도
    // 2. 정수형 기온

    // 예) 84,17.1,85,17.2,86,17.3

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
// [17-11] 열거형
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
    // 영화 예매 프로그램
    int menu;
    printf("[1]없음 [2]조조 [3]통신사 할인\n");
    printf("할인 권종을 선택하세요 : ");
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

    printf("결제 금액 : %d원", ticket_pirce);

    return 0;
}
#endif

/***********************************************************/
// [17-12] tpyedef 사용한 자료형 재정의
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
    // 구조체를 재정의하면
    // 대문자로 시작하자!!
    Student s1 = {315, 3.7};
    Profile p1 = {"아이유", 17};

    int a = 10;
    t b = 20;

    printf("%d %d", a, b);

    return 0;
}
#endif

/***********************************************************/
// [0-0] 타이틀
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
	
	return 0;
}
#endif

/***********************************************************/
// [0-0] 타이틀
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
	
	return 0;
}
#endif

/***********************************************************/
// [0-0] 타이틀
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
	
	return 0;
}
#endif

/***********************************************************/
// [0-0] 타이틀
/***********************************************************/

#if 0
#include <stdio.h>

int main(void)
{
	
	return 0;
}
#endif