/*
 * struct.c
 *
 *  Created on: 3 Apr 2020
 *      Author: ghh
 */

#include <stdio.h>
#include <string.h>
#define TRUE 1
#define FALSE 0

struct student1 {
	char lastName;
	int studentID;
	char grade;
}; //재정의하지 않은 구조체

typedef struct {
	char lastName;
	int studentID;
	char grade;
} student2; //재정의한 구조체

int Equal (student2 person1, student2 person2){ //동일성 검사

	if (person1.lastName != person2.lastName)
		return FALSE;
	if(person1.studentID != person2.studentID)
		return FALSE;
	if(person1.grade != person2.grade)
		return FALSE;

	return TRUE;
}
/* 각 구조체 별 항목을 일일히 비교하여아 함. strcmp(문자열) -> char(문자)로 변형 */

int main(void){


	printf("[-----[황규현] [2019038071]-----]\n\n");

	struct student1 st1 = {'A',100,'A'}; 
	/* 
		구조체임을 알 수 있는 struct의 선언이 필요 - 재정의하지 않았기 때문에
		A - 문자로 선언
	*/

	printf("st1\n");
	printf("st1.lastName = %c\n",st1.lastName);
	printf("st1.studentID = %d\n",st1.studentID);
	printf("st1.grade = %c\n",st1.grade);

	student2 st2 = {'B',200,'B'};

	printf("\nst2\n");
	printf("st2.lastName = %c\n",st2.lastName);
	printf("st2.studentID = %d\n",st2.studentID);
	printf("st2.grade = %c\n",st2.grade);
	//구조체 st1, st2의 값 출력

	student2 st3;

	st3=st2; //새로 생성한 구조체 st3에 st2의 값 옮김. - 컴파일러의 버전에 따라 불가능함

	printf("\nst3\n");
	printf("st3.lastName = %c\n",st3.lastName);
	printf("st3.studentID = %d\n",st3.studentID);
	printf("st3.grade = %c\n",st3.grade);
	//구조체 st3의 값 출력

	/*동일성 검사
	 구조체 st3에 st2의 값을 저장했는데, 이 값이 정상적으로 저장되었는지 검사한다.
	 요소 중 하나라도 저장이 안 되어있으면 FALSE를 리턴한다.
	*/
	if (Equal(st3, st2) == TRUE) //함수의 리턴값이 1(TRUE)이면
		printf("\n\n *equal* \n"); //equal 출력
	else //0 0(FALSE)이면
		printf("\n\n *not equal* \n"); // not equal 출력 

	return 0;
}
