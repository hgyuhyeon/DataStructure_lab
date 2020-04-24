/*
 * single linked list
 *
 *  Created on: 24 Apr 2020
 *
 *  Data Structures
 *  Department of Computer Science
 *  at Chungbuk National University
 */
#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
	int key;
	struct Node* link;
} listNode;

typedef struct Head {
	struct Node* first;
}headNode;


/* 함수 리스트 */
headNode* initialize(headNode* h);
int freeList(headNode* h);

int insertFirst(headNode* h, int key);
int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);

int deleteFirst(headNode* h);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);

int main()
{
	char command; //명령어 문자
	int key; //입력받는 정수
	headNode* headnode = NULL; //새로운 단일 연결 리스트를 가리킬 포인터

	do {
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf("              [-----[황규현][2019038071]-----]                    \n");
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
			headnode = initialize(headnode); //연결리스트 생성
			break;
		case 'p': case 'P':
			printList(headnode); //리스트
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key); //리스트 내에 존재하는 key보다 큰 수 바로 앞에 노드 추가
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key); //key와 같은 값을 갖는 첫 번째 노드를 제거
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key); //새 노드를 리스트의 마지막에 추가
			break;
		case 'e': case 'E':
			deleteLast(headnode); //리스트의 마지막 노드 제거
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key); //새 노드를 리스트의 맨 앞에 추가
			break;
		case 't': case 'T':
			deleteFirst(headnode); //리스트의 첫 번째 노드 제거
			break;
		case 'r': case 'R':
			invertList(headnode); //리스트 재배열
			break;
		case 'q': case 'Q':
			freeList(headnode); //리스트 해제
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}

headNode* initialize(headNode* h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if (h != NULL)
		freeList(h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp; //새로운 단일 연결 리스트에 대한 메모리가 생성됐음
}

int freeList(headNode* h) {
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first; //리스트의 첫 번째를 가리키는 포인터 생성

	listNode* prev = NULL; //포인터 p의 이전 노드를 가리키는 포인터 prev 생성
	while (p != NULL) { //포인터가 NULL을 가리키지 않으면
		prev = p; //prev는 p로 이동(노드 1칸 이동, 이번에 해제할 메모리)
		p = p->link; //p는 p다음 노드로 이동(노드 1칸 이동, 다음에 해제할 )
		free(prev); //prev가 가리키고 있는 노드 메모리의 해제
	}
	free(h); //마지막으로 headnode 해제
	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //노드 1개 생성
	node->key = key; //노드의 key부분에 key를 저장.

	node->link = h->first; //노드의 링크(노드 뒤 포인터)는 기존에 있던 첫 번째 노드를 가리킴
	h->first = node; //리스트의 첫 번째 포인터는 새로 만든 노드를 가리킴

	return 0;
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {

	if (h == NULL) {
		printf("inavailable to insert node.\n");
		return -1;
	}

	listNode* node = (listNode*)malloc(sizeof(listNode)); //key를 저장할 노드 생성
	node->key = key;

	if (h->first == NULL) { //리스트가 비어있을 때
		node->link = h->first; //노드의 링크(노드 뒤 포인터)는 기존에 있던 첫 번째 노드(여기서는 NULL)를 가리킴
		h->first = node; //리스트의 첫 번째 포인터는 새로 만든 노드를 가리킴
		return 0;
	}

	listNode* p = h->first, * prev = NULL; //리스트 search용 포인터 2개 생성
	while (p != NULL) { //p가 리스트의 끝까지 갈 때까지
		if (p->key > node->key) { //리스트에 있는 항목보다 노드의 항목이 작으면
			if (prev == NULL) { //해당 노드가 리스트의 첫 번째 항목으로 들어간다면
				insertFirst(h, key); //리스트의 맨 앞에 넣는 함수 호출
				free(node); //insertNode내에서 할당된 node는 해제
				return 0;
			}
			/* 해당 노드가 리스트의 두 번째 이후의 항목으로 들어간다면 */
			prev->link = node; //앞 노드의 링크는 새로 생성한 노드를 가리킴
			node->link = p; //새로 생성한 노드의 링크는 뒤 노드를 가리킴
			return 0; //탐색 종료
		}
		prev = p; //prev는 p로 이동(노드 1칸 이동)
		p = p->link; //p는 p다음 노드로 이동(노드 1칸 이동)
	}
	//여기까지 왔다면 key보다 앞의 값이 없는 것이므로 리스트의 마지막에 노드를 추가한다.
	prev->link = node; //마지막 노드의 링크가 새로 생성한 노드를 가리킴
	node->link = p; //새로 생성한 노드의 링크는 뒤 노드(NULL)를 가리킴
	return 0;
}

/**
 * list의 끝에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //key를 저장할 노드 생성
	node->key = key; //key 저장
	node->link = NULL;

	listNode* p = h->first, * prev = NULL; //리스트 search용 포인터 2개 생성
	while (p != NULL) { //p가 끝까지 갈 때까지
		prev = p; //prev는 p로 이동(노드 1칸 이동)
		p = p->link; //p는 p다음 노드로 이동(노드 1칸 이동)
		/* while문이 종료되면
		 * p가 NULL을 가리키고
		 * prev는 p 이전이므로 prev가 마지막 노드를 가리키게 된다
		 * 그럼 prev가 가리키는 자리 뒤에 노드를 추가하면 완성 */
	}

	prev->link = node; //마지막 노드의 링크가 새로 생성한 노드를 가리킴
	node->link = p; //새로 생성한 노드의 링크는 뒤 노드(NULL)를 가리킴

	return 0;
}

/*
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {
	listNode* p = h->first; //p를 생성해서 p가 첫 번째 노드를 가리키고
	h->first = p->link; //h->first가 두 번째 노드(p->next)를 가리키도록 한 다음에
	free(p); //p에 있는 메모리를 해제한다.
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {

	listNode* p = h->first, * prev = NULL; //리스트 search용 포인터 2개 생성
	while (p != NULL) {
		/* prev와 p를 생성해서 key를 찾을때까지 빙글빙글 돌아간다.
		   조건: prev는 key의 이전 노드, p가 key를 가리키고 있어야 함 */

		if (p->key == key) { //key를 찾으면?
			if (prev == NULL) //삭제하고 싶은 노드가 제일 앞에 있으면
				h->first = p->link; //list의 head가 다음 노드를 가리키도록 한 다음에
			else //타겟 노드가 제잎 앞에 있는 게 아니라면
				prev->link = p->link; //prev->next(key의 이전 노드)가 p->next(key의 다음 노드)를 가리킴
			free(p); //p가 가리키고 있는 key노드의 메모리 해제
			return 0; //바로 함수 종료
		}
		prev = p; //prev는 p로 이동(노드 1칸 이동)
		p = p->link; //p는 p다음 노드로 이동(노드 1칸 이동)
	}

	printf("There is no '%d' to delete.\n", key); //key가 없으면? key가 없다고 출력하고 아무런 작업도 하지 x
	//현재의 프로그램은 key와 같은 노드 중 첫 번째로 나오는 노드만을 삭제한다.
  //만약 key와 같은 노드가 여러개인 경우, 이 노드들을 모두 삭제하는걸까?
	//아니면 첫 번째로 나오는 key와 같은 노드를 삭제하는걸까?
	return 0;
}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {

	listNode* p = h->first, * prev = NULL, * pprev = NULL; //리스트 search용 포인터 3개 생성
	while (p != NULL) {
		/* prev와 p를 생성해서 key를 찾을때까지 빙글빙글 돌아간다.
		   조건: prev는 key의 이전 노드, p가 key를 가리키고 있어야 함 */
		if (prev == NULL) {
			/* prev가 아무 노드도 가리키지 않을 때 pprev가 어떠한 값을 가리키게 하지 않기 위해서 만든 조건 */
			prev = p; //prev는 p로 이동(노드 1칸 이동)
			p = p->link; //p는 p다음 노드로 이동(노드 1칸 이동)
			continue;
		}
		pprev = prev; //pprev는 p로 이동(노드 1칸 이동)
		prev = p; //prev는 p로 이동(노드 1칸 이동)
		p = p->link; //p는 p다음 노드로 이동(노드 1칸 이동)
	}

	/* 여기까지 진행된 후 포인터들의 상태
	 * p: NULL 가리킴
	 * prev: 삭제해야 할 마지막 노드 가리킴
	 * pprev: 마지막 노드의 이전 노드 가리킴
	 */

	if (pprev == NULL) //남은 노드가 2개 미만이라서 pprev까지 사용되지 않았을 때
	/* 이 경우 포인터들의 상태
	 * p: NULL 가리킴
	 * prev: 삭제해야 할 첫 번째이자 마지막 노드 가리킴
	 * pprev: NULL 가리킴
	 */
		h->first = NULL; //listhead가 NULL 가리키게 하고(리스트를 비워주고)
	else //남은 노드가 2개 이상일 때
		pprev->link = NULL; //pprev->link가 NULL 가리키게 하고(마지막 노드로 만들고)
	free(prev); //prev 노드의 메모리를 해제하면 끝!
	return 0;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {
	listNode* p = h->first, * prev = NULL, * temp = NULL;
	/* p: 리스트를 search하는 포인터
	 * prev: p가 가리키는 노드의 이전 노드
	 * temp: 노드의 순서를 바꿀 때 매개하는 포인터 */
	if (p == NULL) { //리스트가 비어있으면
		printf("There isn't exist any list.\n"); //리스트가 없다고 출력하고
		return -1; //종료
	}

	while (p != NULL) { //p가 리스트 끝까지 가는 동안
		prev = temp; //temp에 있던 값을 prev로 옮김 (prev의 한 칸 전진)
		temp = p; //p에 있던 값을 temp로 옮김(temp의 한 칸 전진)
		p = p->link; //p에 있던 값을 p->link로 옮김(p의 한 칸 전진)
		temp->link = prev;
		/* temp->link는 prev노드를 가리킴(앞 노드<-중간 노드->뒤 노드)
		 * prev = 앞 노드, temp = 중간 노드, p = 뒤 노드의 역할을 함 */
	}
	h->first = temp;
	//listhead가 재배치 전 마지막 노드를 가리킴 -> 재배치 후 첫 번째 노드
	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if (h == NULL || h->first == NULL) {
		/* 리스트가 initialize되어있지 않거나
		 * initialize된 리스트가 비어있을 때 */
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while (p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i);
}
