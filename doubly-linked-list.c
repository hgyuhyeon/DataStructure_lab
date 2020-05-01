/*
 * doubly-linked-list.c
 *
 * Doubly Linked List
 *  Created on: 1 May 2020
 *
 *  Data Structures
 *  Department of Computer Science
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>
 /* 필요한 헤더파일 추가 if necessary */


typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

typedef struct Head {
	struct Node* first;
}headNode;

/* 함수 리스트 */

/* note: initialize는 이중포인터를 매개변수로 받음
		 singly-linked-list의 initialize와 차이점을 이해 할것 */
int initialize(headNode** h);

/* note: freeList는 싱글포인터를 매개변수로 받음
		- initialize와 왜 다른지 이해 할것
		 - 이중포인터를 매개변수로 받아도 해제할 수 있을 것 */
int freeList(headNode* h);

int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);
int insertFirst(headNode* h, int key);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int deleteFirst(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);


int main()
{
	char command;
	int key;
	headNode* headnode = NULL;

	do {
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
		printf("----------------------------------------------------------------\n");
		printf("              [-----[황규현][2019038071]-----]                  \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'z': case 'Z':
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}


int initialize(headNode** h) {

	if (*h != NULL)
		freeList(*h); //headNode에 메모리가 있으면 메모리 해제 먼저 하기

	/* headNode에 대한 메모리를 할당하여 리턴
	 * *h = NULL인 상태 */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	*h = temp;

	return 1;
}

int freeList(headNode* h) {

	listNode* p = h->first; //리스트 search용 포인터 생성
	while (p != NULL) {
		if (p->rlink == NULL) { //마지막 노드의 메모리 해제를 위한 예외처리
			free(p);
			break;
		}
		p = p->rlink; //p는 다음 노드로 이동
		free(p->llink); //p의 이전 노드 메모리 해제
	}
	free(h);

	return 0;
}

void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if (h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while (p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}

	printf("  items = %d\n", i);
}




/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //key를 저장할 노드 생성
	node->key = key; //key 저장

	listNode* p = h->first; //리스트 search용 포인터 생성

	//예외사항 - 리스트가 비어있을 때
	if (h->first == NULL) {
		node->rlink = NULL; //새 노드의 오른쪽은 NULL
		h->first = node; //새 노드를 첫 번째 노드로 만들고
		node->llink = h->first; //새 노드의 왼쪽은 헤드노드를 가리킴
		return 0;
	}

	while (p->rlink != NULL) { //p가 끝까지 갈 때까지
		p = p->rlink; //p는 p다음 노드로 이동(노드 1칸 이동)
		/* while문이 종료되면
		 * p가 마지막 노드를 가리키니까
		 * p->rlink 자리에 노드를 추가하면 완성임. */
	}

	node->rlink = NULL; //마지막 노드로 추가할 것이기 때문에 rlink는 NULL
	p->rlink = node; //기존 마지막 노드 뒤 오른쪽 링크에 새 노드 연결
	node->llink = p; //새 노드의 왼쪽 링크를 기존의 마지막 노드와 연결

	return 0;
}



/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {

	listNode* p = h->first; //리스트 search용 포인터 생성

	if (p->rlink == NULL) { //리스트 속 노드가 1개일 때
		h->first = NULL; //리스트를 비워주고
		free(p); //p 해제
		return 0;
	}

	while (p->rlink != NULL) { //p의 다음 노드가 NULL이 아닐때까지
		p = p->rlink; //p는 p다음 노드로 이동(노드 1칸 이동)
	}

	//이때 p = 마지막 노드
	p->llink->rlink = NULL; //마지막 노드의 이전 노드(p->llink)의 다음 노드(rlink)를 NULL로 만들고
	free(p); //마지막 노드(p)의 메모리를 해제하면 끝!

	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //노드 1개 생성
	node->key = key; //노드의 key부분에 key를 저장.

	//예외사항 - 리스트가 비어있을 때
	if (h->first == NULL) {
		node->rlink = NULL; //새 노드의 오른쪽은 NULL
		h->first = node; //새 노드를 첫 번째 노드로 만들고
		node->llink = h->first; //새 노드의 왼쪽은 헤드노드를 가리킴
		return 0;
	}

	node->rlink = h->first; //노드의 링크(노드 뒤 포인터)는 기존에 있던 첫 번째 노드를 가리킴
	node->rlink->llink = node; //기존 노드의 왼쪽 링크는 새로 만든 노드를 가리킴
	h->first = node; //첫 번째 노드로 만들고
	node->llink = h->first; //노드의 왼쪽 링크는 헤더 가리킴

	return 0;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {

	listNode* p = h->first; //p를 생성해서 p가 첫 번째 노드를 가리키고
	h->first = p->rlink; //h->first가 두 번째 노드(p->rlink)를 가리키도록 한 다음에
	if (p->rlink == NULL) { //리스트 속 노드가 1개라면
		h->first = NULL; //리스트를 비워주고
	}
	else
		p->rlink->llink = h->first; //두 번째 노드의 왼쪽 링크는 h를 가리키도록 하고
	free(p); //p에 있는 메모리를 해제한다.

	return 0;
}



/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {

	listNode* p = h->first, * prev = NULL, * temp = NULL;
	/* p: 리스트를 search하는 포인터
	 * prev: p가 가리키는 노드의 이전 노드
	 * temp: 노드의 순서를 바꿀 때 매개하는 포인터
	 * p 하나로 끝낼 수도 있겠지만 복잡해지니까 그냥 기존대로 함 */
	if (p == NULL) { //리스트가 비어있으면
		printf("There isn't exist any list.\n"); //리스트가 없다고 출력하고
		return -1; //종료
	}

	while (p != NULL) { //p가 리스트 끝까지 가는 동안
		prev = temp; //temp에 있던 값을 prev로 옮김 (prev의 한 칸 전진)
		temp = p; //p에 있던 값을 temp로 옮김(temp의 한 칸 전진)
		p = p->rlink; //p에 있던 값을 p->link로 옮김(p의 한 칸 전진)
		temp->rlink = prev;
		temp->llink = p;
		/* temp->rlink는 prev노드를 가리킴(앞 노드<-중간 노드->뒤 노드)
		 * temp->llink는 p노드를 가리킴(앞 노드<-중간 노드->뒤 노드)
		 * prev = 앞 노드, temp = 중간 노드, p = 뒤 노드의 역할을 함 */
	}
	h->first = temp;
	temp->llink = h->first;
	//listhead가 재배치 전 마지막 노드를 가리킴 -> 재배치 후 첫 번째 노드

	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {

	if (h == NULL) { //헤더값이 없으면
		printf("Unavailable to insert node.\n"); //노드 삽입 불가
		return -1;
	}

	listNode* node = (listNode*)malloc(sizeof(listNode)); //key를 저장할 노드 생성
	node->key = key;
	listNode* p = h->first; //리스트 search용 포인터 생성

	//예외사항
	if (p == NULL) { //리스트가 비어있을 때
		node->rlink = NULL; //노드의 오른쪽 링크(노드 뒤 포인터)는 NULL을 가리킴(첫 번째 노드니까)
		node->llink = h->first; //노드의 왼쪽 링크는 헤드 노드를 가리킴
		h->first = node; //헤드 노드는 새로 만든 노드를 가리킴
		return 0;
	}
	
	while (p != NULL) { //2개 이상의 노드를 가진 리스트에서 p가 리스트의 마지막 노드에 갈 때까지
		if (p->key > node->key) { //리스트에 있는 항목보다 노드의 항목이 작으면
			if (p == h->first) { //해당 노드가 리스트의 첫 번째 항목으로 들어간다면
				insertFirst(h, key); //리스트의 맨 앞에 넣는 함수 호출
				free(node); //insertNode내에서 할당된 node는 해제
				return 0;
			}
			/* 해당 노드가 리스트의 두 번째 이후의 항목으로 들어간다면
			 * 목적: p가 가리키는 노드 앞에 새 노드를 삽입해야 함 */
			node->rlink = p; //새로 생성한 노드의 오른쪽 링크는 뒤 노드(p)를 가리킴
			node->llink = p->llink; //새 노드의 왼쪽 링크는 앞 노드(p->llink)를 가리킴
			p->llink->rlink = node; //앞 노드의 오른쪽 링크는 새로 생성한 노드를 가리킴
			p->llink = node; //뒤 노드의 왼쪽 링크는 새로 생성한 노드를 가리킴

			return 0; //탐색 종료
		}
		if (p->rlink == NULL) //p의 이동을 마지막 노드에서 종료시키기 위함
			break;
		p = p->rlink; //p는 p다음 노드로 이동(노드 1칸 이동)
	}
	/* 여기까지 왔다면 key보다 앞의 값이 없는 것이므로 
	 * 리스트의 마지막에 노드를 추가한다.
	 * 현재 p상태 = 마지막 노드 */

	node->rlink = NULL; //새로 생성한 노드의 오른쪽 링크는 NULL을 가리킴
	node->llink = p; //새로 생성한 노드의 왼쪽 링크는 기존의 마지막 노드를 가리킴
	p->rlink = node; //마지막 노드의 오른쪽 링크는 새로 생성한 노드를 가리킴
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {

	listNode* p = h->first; //리스트 search용 포인터 생성

	//예외사항
	if (p == NULL) { //리스트가 비어있을 때
		printf("Empty list.\n");
		return 0;
	}


	while (p != NULL) {
		/* p를 생성해서 key를 찾을때까지 빙글빙글 돌아간다.
		   조건: p가 key를 가리키고 있어야 함 */

		if (p->key == key) { //key를 찾으면?

			if (p == h->first) { //첫 번째 노드를 삭제한다면
				if (p->rlink == NULL) { //리스트 노드 개수가 1개일 때
					h->first = NULL; //리스트를 비워준 후
					free(p); //p 해제
					return 0;
				}
				h->first = p->rlink; //h->first가 두 번째 노드(p->rlink)를 가리키도록 한 다음에
				p->rlink->llink = h->first; //두 번째 노드의 왼쪽 링크는 h를 가리키도록 하고
				free(p); //p에 있는 메모리를 해제한다.
				return 0;
			}

			/* 노드가 2개 이상인 리스트에서 key 찾아 삭제 */
			if (p->rlink == NULL) { //마지막 노드를 삭제하는 경우라면
				p->llink->rlink = NULL; //마지막 노드의 이전 노드(p->llink)의 다음 노드(rlink)를 NULL로 만들고
				free(p); //마지막 노드(p)의 메모리를 해제
				return 0;
			}
			p->rlink->llink = p->llink;
			//p->rlink(key의 다음 노드)의 llink(왼쪽 노드)는 p->llink(key의 이전 노드)를 가리킴
			p->llink->rlink = p->rlink; 
			//p->llink(key의 이전 노드)의 rlink(오른쪽 노드)는 p->rlink(key의 다음 노드)를 가리킴
			free(p); //p가 가리키고 있는 key노드의 메모리 해제
			return 0; //바로 함수 종료
		}
		p = p->rlink; //p는 p다음 노드로 이동(노드 1칸 이동)
	}

	printf("There is no '%d' to delete.\n", key); 
	//key가 없으면? key가 없다고 출력하고 아무런 작업도 하지 x

	return 1;
}
