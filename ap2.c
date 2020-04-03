/*
 * ap2.c
 *
 *  Created on: 3 Apr 2020
 *      Author: ghh
 */
#include <stdio.h>
#include <stdlib.h>

int main(void){
	int list[5];
	int *plist[5];

	list[0]=10;
	list[1]=11;

	plist[0]=(int*)malloc(sizeof(int));

	printf("[-----[황규현] [2019038071]-----]\n\n");

	printf("list[0] = %d\n",list[0]);
	printf("address of list = %p\n",list);
	printf("address of list[0] = %p\n",&list[0]);
	printf("address of list + 0 = %p\n",list+0);
	/* list의 주소는 list[0]의 주소와 같다 */

	printf("address of list + 1 = %p\n",list+1);
	// &(list[0]+4)
	printf("address of list + 2 = %p\n",list+2);
	// &(list[0]+8)
	printf("address of list + 3 = %p\n",list+3);
	// &(list[0]+12)
	printf("address of list + 4 = %p\n",list+4);
	printf("address of list[4] = %p\n",&list[4]);
	// &(list[0]+16), =&list[4], = list+4

	return 0;
}

