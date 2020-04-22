#include <stdio.h>

int main()
{
	int i;
	int *ptr;
	int **dptr;


	printf("[----[황규현][2019038071]----]\n\n");

	i=1234;

	printf("[Checking values before ptr = &i]\n");
	printf("value of i == %d\n",i); //변수 i의 값
	printf("address of i == %p\n", &i); //변수 i의 주소값
	printf("value of ptr == %p\n", ptr); //포인터 변수 ptr의 값
	printf("address of ptr == %p\n", &ptr); //포인터 변수 ptr의 주소값

	ptr = &i; //ptr is now holding the address of i

	printf("\n[Checking values after ptr = &i]\n");
	printf("value of i == %d\n",i);
	printf("address of i == %p\n", &i);
	printf("value of ptr == %p\n", ptr);
	printf("address of ptr == %p\n", &ptr); //주소값이 변수 i의 주소값과 동일해짐
	printf("value of *ptr == %d\n", *ptr); //값이 변수 i와 동일해짐

	dptr=&ptr; //dptr is now holding the address of ptr

	printf("\n[checking values after dptr = &ptr]\n");
	printf("value of i == %d\n", i);
	printf("address of i == %p\n", &i);
	printf("value of ptr == %p\n", ptr);
	printf("address of ptr == %p\n", &ptr);
	printf("value of *ptr == %d\n", *ptr);
	printf("value of dptr == %p\n", dptr); //포인터가 가리키는 주소값의 값(포인터 변수에는 주소가 저장됨ㅈ)
	printf("address of dptr == %p\n", &dptr); //주소값이 변수 i와 동일해짐
	printf("value of *dptr == %p\n", *dptr); //값이 변수 i의 주소가 됐음 - 포인터가 가리키는 주소값의 값
	printf("value of **dptr %d\n", **dptr); //값이 변수 i와 동일해짐

	*ptr = 7777; // changing the value of *ptr

	printf("\n[after *ptr = 7777] \n");
	printf("value of i == %d\n", i);
	printf("value of *ptr == %d\n", *ptr);
	printf("value of **dptr == %d\n", **dptr);
	/* 포인터의 값을 바꾸는 것만으로도 변수값과 변수들을 가리키는 포인터들의 값이 변한다. */

	**dptr = 8888; // changing the value of **dptr

	printf("\n[after **dptr = 8888] \n");
	printf("value of i == %d\n", i);
	printf("value of *ptr == %d\n", *ptr);
	printf("value of **dptr == %d\n", **dptr);
	/* 이중 포인터의 값을 바꾸는 것만으로도 변수값과 변수들을 가리키는 포인터들의 값이 변한다. */

	return 0;
}
