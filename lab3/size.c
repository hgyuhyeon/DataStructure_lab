/*
 * size.c
 *
 *  Created on: 3 Apr 2020
 *      Author: ghh
 */
#include <stdio.h>
#include <stdlib.h>

int main(void){
	int **x; //이중 포인터 변수 선언

	printf("[-----[황규현] [2019038071]-----]\n");
	printf("sizeof(x) = %lu\n",sizeof(x)); //포인터 변수의 크기(주소를 저장) - 8바이트
	printf("sizeof(*x) = %lu\n",sizeof(*x)); //포인터 변수의 크기(주소를 저장) - 8바이트
	printf("sizeof(**x) = %lu\n",sizeof(**x)); //포인터 변수가 가리키는 값의 크기(integer 값을 저장) - 4

	return 0;
}
