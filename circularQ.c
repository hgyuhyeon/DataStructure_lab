/*
 * circularQ.c
 *
 *  Created on: 17 Apr 2020
 *      Author: ghh
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4

typedef char element; //char 자료형 -> element로 이름 달리하기
typedef struct {
	element queue[MAX_QUEUE_SIZE]; //큐!
	int front, rear; //큐의 시작과 끝
}QueueType;


QueueType *createQueue();
int freeQueue(QueueType *cQ);
int isEmpty(QueueType *cQ);
int isFull(QueueType *cQ);
void enQueue(QueueType *cQ, element item);
void deQueue(QueueType *cQ, element* item);
void printQ(QueueType *cQ);
void debugQ(QueueType *cQ);

element getElement();


int main(void)
{
	QueueType *cQ = createQueue(); //큐 만들기
	element data; //인서트할 데이터를 받을 element형 변수

	char command;

	do{
		printf("\n-----------------------------------------------------\n");
		printf("------------------[황규현][2019038071]-----------------\n");
		printf("------------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'i': case 'I':
			data = getElement(); //element 얻어서
			enQueue(cQ, data); //queue에 인서트
			break;
		case 'd': case 'D':
			deQueue(cQ, &data); 
      /* 최근 data의 주소를 인수로 줌
      -> 첫 번째 queue가 이곳을 가리키면서 첫 번째와 마지막 데이터가 연결됨
      -> 원형 큐의 역할을 함 */
			break;
		case 'p': case 'P':
			printQ(cQ); //queue 출력
			break;
		case 'b': case 'B':
			debugQ(cQ); //queue의 상태 출력
			break;
		case 'q': case 'Q':
			freeQueue(cQ);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); 


	return 1;
}


QueueType *createQueue()
{
	QueueType *cQ;
	cQ = (QueueType *)malloc(sizeof(QueueType)); //동적 큐 배열 생성
	cQ->front = 0;
	cQ->rear = 0; //front와 rear를 각각 0으로 지정
	return cQ;
}

int freeQueue(QueueType *cQ)
{
	free(cQ);
	return 1;
}

element getElement()
{
	element item;
	printf("Input element = ");
	scanf(" %c", &item);
	return item; //element 문자 얻어서 반환함
}


/* 큐가 비어있는지 점검 */
int isEmpty(QueueType *cQ)
{
	if(cQ->front==cQ->rear) //front와 rear의 값이 같으면 -> 큐가 꽉 차있으면
		return 1;
	else
		return 0;
}

/* 큐가 꽉 차있는지 점검 */
int isFull(QueueType *cQ)
{
	if(cQ->front==cQ->rear) front와 rear의 값이 같으면 -> 큐가 비어있으면
		return 1;
	else
		return 0;
}
//결국 front==rear일 땐 큐가 꽉 차있거나 비어있거나 둘 중 하나의 상태를 나타냄.

/* 큐에 문자를 큐의 맨 뒤에 추가하기 */
void enQueue(QueueType *cQ, element item)
{
	cQ->rear = (cQ->rear+1)%MAX_QUEUE_SIZE; //rear의 값을 1 증가(3일 땐 0으로)
	if(isFull(cQ)==1){ //큐가 꽉 차있으면
		printf(" Full Queue \n"); //꽉 찼다고 출력하고 들어온 값은 넣지 않음
		cQ->rear = (cQ->rear-1)%MAX_QUEUE_SIZE; //rear의 값을 원래대로 돌려주기
	}
	else
		cQ->queue[cQ->rear]=item; //증가된 rear가 위치한 자리에 문자 넣기
}

/* 큐에 추가된 문자 중 맨 앞에 있는 문자 삭제하기 */
void deQueue(QueueType *cQ, element *item)
{
	if(isEmpty(cQ)==1) //큐가 비어있으면
			printf(" Empty Queue \n"); //비어있다고 출력, 값은 지우지 않음(지울 수 없음)
	else{
		cQ->front = (cQ->front+1)%MAX_QUEUE_SIZE; //front의 값을 1 증가(3일 땐 0으로)
		element itemm = *item; // item이 가리키는 값(문자)를 itemm변수에 이동
		cQ->queue[cQ->front] = itemm; //itemm의 문자를 front에 
	}
}


void printQ(QueueType *cQ)
{
	int i, first, last;

	first = (cQ->front + 1)%MAX_QUEUE_SIZE; //큐의 첫 번째 출력 시작점 지정
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE; //큐의 출력 마지막점 지정

	printf("Circular Queue : [");

	i = first;
	while(i != last){
		printf("%3c", cQ->queue[i]); //큐에 저장된 문자 출력
		i = (i+1)%MAX_QUEUE_SIZE; //1칸씩 앞으로 이동 

	}
	printf(" ]\n");
}


void debugQ(QueueType *cQ)
{

	printf("\n---DEBUG\n");
	for(int i = 0; i < MAX_QUEUE_SIZE; i++)
	{
		if(i == cQ->front) {
			printf("  [%d] = front\n", i); 
      /* i가 front의 값과 같은 상태일 때는 front의 위치이므로 큐 대신 front 출력 */
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]); // 나머지 상태에서는 큐에 들어있는 값 출력

	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear); //front와 rear의 상태 출력
}
