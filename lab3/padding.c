/*
 * padding.c
 *
 *  Created on: 3 Apr 2020
 *      Author: ghh
 */
#include <stdio.h>

struct student {
	char lastName[13]; //13 bytes
	int studentID; //4 bytes
	short grade; //2 bytes
}; //total 19 bytes

int main(void){

	printf("[-----[황규현] [2019038071]-----]\n");

	printf("size of student = %ld\n", sizeof(struct student));
	/* 24바이트 출력 - 왜?
	  컴파일러는 padding 이라는 것을 함 - 실제 메모리의 크기에 관계없이 4바이트 단위로 측정
	  원래 구조체의 크기 = 13+4+2=19 bytes
	  padding한 구조체의 크기 = 13(+3)+4+2(+2) = 19(+5) = 24 */
    
	printf("size of int = %ld\n", sizeof(int));
	/* 4바이트 출력 - int 자료형의 크기 */
  
	printf("size of short = %ld\n", sizeof(short));
	/* 2바이트 출력 - short 자료형의 크기*/

	return 0;
}
