/*
 * p2-1.c
 *
 *  Created on: 3 Apr 2020
 *      Author: ghh
 */
#include <stdio.h>
#define MAX_SIZE 100

float input[MAX_SIZE],answer;
int i;

float sum(float list[], int n){
	/* input의 주소값 -> list에 복사
	   input의 주소와 list의 값은 동일함.
	   list가 input을 가리키고 있는 모양새 */

	//리스트의 주소 확인
	printf("value of list = %p\n",list);
	printf("address of list = %p\n\n",&list);
	/* input과 list의 주소가 다름 - 둘은 다른 곳에 존재!*/

	int i;
	float tempsum=0;
	for(i=0;i<n;i++)
		tempsum+=list[i];

	return tempsum;
}
int main(void){
	printf("[-----[황규현] [2019038071]-----]\n");
	for(i=0;i<MAX_SIZE;i++)
		input[i]=i;

	//배열의 주소 보기
	printf("address of input = %p\n",input);

	answer = sum(input, MAX_SIZE);
	/* answer에 sum함수의 리턴값
	   즉, list의 값을 모두 합한 tempsum이 들어감
	   배열 input의 값을 list에 복사했기 때문에 모두 더한 값은 input의 sum과 동일함 */
	printf("The sum is: %f\n", answer);

	return 0;
}
