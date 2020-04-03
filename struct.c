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
};

typedef struct {
	char lastName;
	int studentID;
	char grade;
} student2;

int Equal (student2 person1, student2 person2){

	if (person1.lastName != person2.lastName)
		return FALSE;
	if(person1.studentID != person2.studentID)
		return FALSE;
	if(person1.grade != person2.grade)
		return FALSE;

	return TRUE;

}

int main(void){


	printf("[-----[황규현] [2019038071]-----]\n\n");

	struct student1 st1 = {'A',100,'A'};

	printf("st1\n");
	printf("st1.lastName = %c\n",st1.lastName);
	printf("st1.studentID = %d\n",st1.studentID);
	printf("st1.grade = %c\n",st1.grade);

	student2 st2 = {'B',200,'B'};

	printf("\nst2\n");
	printf("st2.lastName = %c\n",st2.lastName);
	printf("st2.studentID = %d\n",st2.studentID);
	printf("st2.grade = %c\n",st2.grade);

	student2 st3;

	st3=st2;

	printf("\nst3\n");
	printf("st3.lastName = %c\n",st3.lastName);
	printf("st3.studentID = %d\n",st3.studentID);
	printf("st3.grade = %c\n",st3.grade);

	//동일성 검사
	if (Equal(st3, st2) == TRUE)
		printf("\n\n *equal* \n");
	else
		printf("\n\n *not equal* \n");

	return 0;
}
