/*
 * ap1.c
 *
 *  Created on: 3 Apr 2020
 *      Author: ghh
 */
#include <stdio.h>
#include <stdlib.h>

int main(void){
	int list[5];
	int *plist[5]={NULL,};

	plist[0]=(int*)malloc(sizeof(int)); //plist[0]에 4바이트의 메모리 할당

	list[0]=1;
	list[1]=100;

	*plist[0]=200;

	printf("[-----[황규현] [2019038071]-----]\n\n");

	printf("value of list[0] = %d\n",list[0]); //list[0]의 값
	printf("address of list[0] = %p\n",&list[0]); //list[0]의 주소
	printf("value of list = %p\n",list); //list의 값
	printf("address of list (&list) = %p\n",&list); //list의 주소
	/* list의 주소는 list[0]과 동일*/
  
	printf("-------------------------------------\n\n");
	printf("value of list[1] = %d\n",list[1]); //list[1]의 값
	printf("address of list[1] = %p\n",&list[1]); //list[1]의 주소
	printf("value of *(list+1) = %d\n",*(list+1)); // =list[1]의 값
	printf("address of list+1 = %p\n",list+1); // =list[1]의 주소
	/* list[1]의 주소 = list[0]의 주소 + 4byte */

	printf("-------------------------------------\n\n");
	printf("value of *plist[0] = %d\n",*plist[0]); //
	printf("&plist[0] = %p\n",&plist[0]);
	printf("&plist = %p\n",&plist);
	printf("plist = %p\n",plist);
	/* plist[0]이 가리키는 메모리의 첫 번째 요소 값(200)과 포인터 배열 plist의 주소.
	   배열의 주소는 배열의 첫 번째 요소의 주소와 같다. */

	printf("plist[0] = %p\n",plist[0]);
	/* plist[0]에 할당받은 동적 메모리의 주소. 즉 plist[0]이 가리키는 메모리의 주소 */
	printf("plist[1] = %p\n",plist[1]);
	printf("plist[2] = %p\n",plist[2]);
	printf("plist[3] = %p\n",plist[3]);
	printf("plist[4] = %p\n",plist[4]);
	/* 할당받은 메모리가 없으므로 nil*/
  
	free(plist[0]);
	return 0;
}

