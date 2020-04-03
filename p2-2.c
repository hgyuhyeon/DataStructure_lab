/*
 * p2-2.c
 *
 *  Created on: 3 Apr 2020
 *      Author: ghh
 */
#include <stdio.h>

void print1(int *ptr, int rows){
	int i;
	printf("Address Contents\n");
	for(i=0;i<rows;i++)
		printf("%p \t  %5d\n",ptr+i,*(ptr+i));
	printf("\n");
	/* int형 배열이기 때문에 4바이트씩 주소가 이동함
	   포인터를 이용한 배열의 출력 방법의 예시 */
}

int main(void){

	printf("[-----[황규현] [2019038071]-----]\n");

	int one[]={0,1,2,3,4};
	printf("one = %p\n",one);
	printf("&one = %p\n",&one);
	printf("&one[0] = %p\n\n",&one[0]);
	/* 배열 one의 값 = 배열 one의 주소
	   배열 one의 주소 = 배열 one의 첫 번째 요소의 주소 */
	print1(&one[0],5);
	return 0;
}

