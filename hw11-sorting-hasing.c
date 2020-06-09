/*
 * hw11-sorting.c
 *
 *  Created on: May 22, 2019
 *
 *  Homework 11: Sorting & Hashing
 *  Department of Computer Science at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE			13	/* prime number */
#define MAX_HASH_TABLE_SIZE 	MAX_ARRAY_SIZE

/* 필요에 따라 함수 추가 가능 */
int initialize(int **a);
int freeArray(int *a);
void printArray(int *a);

int selectionSort(int *a);
int insertionSort(int *a);
int bubbleSort(int *a);
int shellSort(int *a);
/* recursive function으로 구현 */
int quickSort(int *a, int n);


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a에대 한 hash table을 만든다. */
int hashing(int *a, int **ht);

/* hash table에서 key를 찾아 hash table의 index return */
int search(int *ht, int key);


int main()
{
	char command;
	int *array = NULL;
	int *hashtable = NULL;
	int key = -1;
	int index = -1;

	srand(time(NULL));

	do{
		printf("----------------------------------------------------------------\n");
		printf("                        Sorting & Hashing                       \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize       = z           Quit             = q\n");
		printf(" Selection Sort   = s           Insertion Sort   = i\n");
		printf(" Bubble Sort      = b           Shell Sort       = l\n");
		printf(" Quick Sort       = k           Print Array      = p\n");
		printf(" Hashing          = h           Search(for Hash) = e\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&array);
			break;
		case 'q': case 'Q':
			freeArray(array);
			break;
		case 's': case 'S':
			selectionSort(array);
			break;
		case 'i': case 'I':
			insertionSort(array);
			break;
		case 'b': case 'B':
			bubbleSort(array);
			break;
		case 'l': case 'L':
			shellSort(array);
			break;
		case 'k': case 'K':
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			quickSort(array, MAX_ARRAY_SIZE);
			printf("----------------------------------------------------------------\n");
			printArray(array);

			break;

		case 'h': case 'H':
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			hashing(array, &hashtable);
			printArray(hashtable);
			break;

		case 'e': case 'E':
			printf("Your Key = ");
			scanf("%d", &key);
			printArray(hashtable);
			index = search(hashtable, key);
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
			break;

		case 'p': case 'P':
			printArray(array);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initialize(int** a)
{
	int *temp = NULL;

	/* array가 NULL인 경우 메모리 할당 */
	if(*a == NULL) {
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*a = temp;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else
		temp = *a; //NULL이 아니면 temp포인터는 생성되어있는 기존의 array 메모리를 가리킴

	/* 랜덤값을 배열의 값으로 저장 */
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE;

	return 0;
}

int freeArray(int *a)
{
	if(a != NULL) //array에 메모리가 있으면 해제
		free(a);
	return 0;
}

void printArray(int *a)
{
	if (a == NULL) {
		printf("nothing to print.\n");
		return;
	}
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("a[%02d] ", i);
	printf("\n");
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("%5d ", a[i]);
	printf("\n");
}

int selectionSort(int *a)
{
	int min; //최소값
	int minindex; //최소값이 저장된 인덱스
	int i, j; //for

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for (i = 0; i < MAX_ARRAY_SIZE; i++) //배열의 첫 번째 원소부터 체크(순차 탐색)
	{
		minindex = i; //첫 번째 인덱스 저장
		min = a[i]; //첫 번째 값
		for(j = i+1; j < MAX_ARRAY_SIZE; j++) //배열의 두 번째 원소부터 비교
		{
			if (min > a[j]) //새로운 최소값을 찾으면
			{
				min = a[j];
				minindex = j; 
			} //최소값 수정
		}
		a[minindex] = a[i]; //최소값 인덱스의 값를 기준값(체크할 값)으로 수정하고
		a[i] = min; //기준값은 최소값으로 수정한다 (swap)
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);
	return 0;
}

int insertionSort(int *a)
{
	int i, j, t;

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for(i = 1; i < MAX_ARRAY_SIZE; i++) //i-1번 탐색
	{
		t = a[i]; //해당 값을 t라는 매개변수에 저장하고
		j = i; //i보다 앞에 있는 원소를 탐색한다
		while (a[j-1] > t && j > 0) 
			/* j가 0보다 크면서 a[i]보다 앞 원소의 값이 a[i]보다 클 때
			   즉, a[i]보다 앞에 큰 값이 있을 때 */
		{
			a[j] = a[j-1]; //해당 값을 한 칸씩 뒤로 밀고
			j--; //다음 앞 원소로 넘어간다
		}
		a[j] = t; //나머지 t보다 큰 원소들이 전부 빠지고 비어있는 a[j]자리에 기존의 a[i]값을 넣는다.
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int bubbleSort(int *a)
{
	int i, j, t;

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for(i = 0; i < MAX_ARRAY_SIZE; i++) //배열의 모든 원소 탐색
	{
		for (j = 1; j < MAX_ARRAY_SIZE; j++) //배열의 모든 원소 탐색
		{
			if (a[j-1] > a[j]) //기준값(j)보다 앞의 값이 더 크다면
			{
				t = a[j-1];
				a[j-1] = a[j];
				a[j] = t;
			} //두 값을 swap한다
		} //1회 종료될 때마다 a[j]앞에 있는 값들끼리 정렬됨
	} //이걸 배열의 마지막 원소까지 반복한다.

	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int shellSort(int *a)
{
	int i, j, k, h, v;

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2) //h(=간격)가 0이 될 때까지 2로 나눈다
	{
		for (i = 0; i < h; i++) //배열의 인덱스를 하나씩 체크하며
		{
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h) 
			{ //인덱스 + 간격을 시작으로 j값이 배열 크기를 넘어갈 때까지 간격만큼 더해준다
				v = a[j]; //배열의 해당값을 v(매개변수)에 저장
				k = j; //해당값의 인덱스를 k에 저장
				while (k > h-1 && a[k-h] > v)
				{ //k가 간격을 유지하면서 배열 내 v값(a[j])이 들어갈 위치를 찾음
					a[k] = a[k-h]; //동일한 간격에 있는 값들을 1칸씩 뒤로 밀음
					k -= h; //간격만큼 점프
				}
				a[k] = v; //미리 저장해둔 v를 해당 자리에 insert
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int quickSort(int *a, int n) //처음 호출 시 n = MAX_ARRAY_SIZE
{
	int v, t;
	int i, j;

	if (n > 1) //리스트의 숫자가 1 이상일때
	{
		v = a[n-1]; //배열의 가장 오른쪽
		i = -1; //가장 왼쪽
		j = n - 1; //가장 오른쪽

		while(1) //v보다 작거나 큰 수를 
		{
			while(a[++i] < v);
			while(a[--j] > v); 
			//i와 j를 v에 가까워지도록 숫자를 증가시키면서 v보다 작은지, 큰 지 체크한다

			if (i >= j) break; //i보다 j의 값이 크면 중지(모든 리스트 체크)
			t = a[i];
			a[i] = a[j];
			a[j] = t; //상단의 while 조건에 맞지 않는 원소들끼리는 swap
		}
		t = a[i];
		a[i] = a[n-1];
		a[n-1] = t; 
		/* 기존 v자리에 있던 원소는 마지막으로 지정된 t자리에 swap한다. 
		   그 자리가 해당 v원소의 자리기 때문이다. */

		quickSort(a, i); //v원소의 왼쪽 리스트끼리 정렬하는 순환 함수 호출
		quickSort(a+i+1, n-i-1); //v원소의 오른쪽 리스트끼리 정렬하는 순환 함수 
	}


	return 0;
}

int hashCode(int key) { //해시 함수
   return key % MAX_HASH_TABLE_SIZE; //제산 함수를 사용한다
}

int hashing(int *a, int **ht)
{
	int *hashtable = NULL; //해시 테이블 생성

	/* hash table이 NULL인 경우 메모리 할당 */
	if(*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else {
		hashtable = *ht;	/* hash table이 NULL이 아닌경우, table 재활용, reset to -1 */
	} //해시 테이블 생성

	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		hashtable[i] = -1; //해시 테이블의 값 초기화

	/*
	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		printf("hashtable[%d] = %d\n", i, hashtable[i]); //각 해시테이블의 초기값 print
	*/

	int key = -1;
	int hashcode = -1;
	int index = -1;
	for (int i = 0; i < MAX_ARRAY_SIZE; i++) //배열의 모든 원소 해싱
	{
		key = a[i]; //key에 배열의 원래 값을 넣고 
		hashcode = hashCode(key); //hashCode함수를 이용하여 버킷 주소를 얻는다
		/*
		printf("key = %d, hashcode = %d, hashtable[%d]=%d\n", key, hashcode, hashcode, hashtable[hashcode]);
		*/ //원래 값, 버킷 주소, 해시테이블의 해당 버킷 주소 디버깅
		if (hashtable[hashcode] == -1) //테이블의 버킷이 비어있으면
		{
			hashtable[hashcode] = key; //해당 자리에 값을 넣고
		} else 	{ //버킷에 값이 존재하면

			index = hashcode; //index 변수에 값을 일시적으로 넣고 

			while(hashtable[index] != -1) //해당 자리가 비워질 때까지
			{
				index = (++index) % MAX_HASH_TABLE_SIZE;
				/*
				printf("index = %d\n", index); //바뀔 때마다 index 값 디버깅
				*/
			} //index의 값을 제산 함수 형태를 이용하여 수정한다(선형 조사법 형태)
			hashtable[index] = key; //테이블의 빈 자리에 해당 값 저장
		}
	}

	return 0;
}

int search(int *ht, int key)
{
	int index = hashCode(key); //해당 key의 해시값을 index에 넣고

	if(ht[index] == key) //만약 테이블의 버킷위치와 값이 같으면
		return index; //바로 리턴하고 함수 종료

	while(ht[++index] != key) //그렇지 않을 때(저장된 위치를 찾아야 할 때)
	{
		index = index % MAX_HASH_TABLE_SIZE; //선형 조사 방식을 이용하여 인덱스 값 증가
	}
	return index; //while문이 종료되면 값을 찾은것이므로 
}
