/*
 *  doubly circular linked list
 *
 *  Data Structures
 *
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */
#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

/* 함수 리스트 */
int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);

int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);

void printList(listNode* h);



int main()
{
	char command;
	int key;
	listNode* headnode = NULL;

	do {
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
		printf("----------------------------------------------------------------\n");
		printf("                [-----[황규현][2019038071]-----]                \n");
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


int initialize(listNode** h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if (*h != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode*)malloc(sizeof(listNode)); //첫 번째 노드 생성
	(*h)->rlink = *h; //rlink와
	(*h)->llink = *h; //llink 모두 자기자신을 가리켜두기
	(*h)->key = -9999; //key에는 임의의 값 넣어두기
	return 1;
}

/* 메모리 해제 */
int freeList(listNode* h) {

	listNode* p = h; //리스트 search용 포인터 생성
	while (1) {
		if (p->rlink == h) { //마지막 노드의 메모리 해제를 위한 예외처리
			free(p);
			break;
		}
		p = p->rlink; //p는 다음 노드로 이동
		free(p->llink); //p의 이전 노드 메모리 해제
	}

	return 0;
}



void printList(listNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if (h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink; //헤드노드(key==-9999) 패스

	while (p != NULL && p != h) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}
	printf("  items = %d\n", i);


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0;
	p = h->rlink;
	while (p != NULL && p != h) {
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}

}



/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(listNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //key를 저장할 노드 생성
	node->key = key; //key 저장

	node->rlink = h; //새 노드의 오른쪽 링크는 헤드노드 연결
	node->llink = h->llink; //새 노드의 왼쪽 링크는 기존 헤드노드의 왼쪽 링크 연결
	h->llink->rlink = node; //기존 마지막노드의 오른쪽 링크는 새 노드로 연결
	h->llink = node; //헤드노드의 왼쪽 링크는 새 노드로 지정

	return 1;
}


/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) {

	if (h->rlink == h) { //리스트가 비어있을 때
	printf("Nothing to delete.\n"); //지울 게 없음을 표시
	return 0; //함수 종료
	}

	if (h->rlink->rlink == h) { //리스트 속 노드가 1개일 때
		free(h->rlink); //해당 노드 해제
		h->rlink = h; //리스트를 비워주고
		return 1; //끝
	}

	listNode* p = h->llink; //p가 지울 메모리 가리킴
	h->llink = h->llink->llink; //마지막 메모리로는 그 이전 메모리 가리킴
	h->llink->rlink = h; //마지막 메모리가 된 h->llink 메모리의 다음 메모리는 h
	free(p); //메모리 지워주기

	return 1;
}


/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //노드 1개 생성
	node->key = key; //노드의 key부분에 key를 저장.

	node->rlink = h->rlink; //노드의 오른쪽 링크는 기존에 있던 첫 번째 노드를 가리킴
	h->rlink->llink = node; //기존 노드의 왼쪽 링크는 새로 만든 노드를 가리킴
	node->llink = h; //노드의 왼쪽 링크는 헤드노드를 가리킴
	h->rlink = node; //헤드 노드의 오른쪽 링크는 새로 만든 노드를 가리킴

	return 1;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) {

	if (h->rlink == h) { //리스트가 비어있을 때
	printf("Nothing to delete.\n"); //지울 게 없음을 표시
	return 0; //함수 종료
	}

	listNode* p = h->rlink; //p를 생성해서 p가 첫 번째 노드(h->rlink)를 가리킴
	
	if (p->rlink == h) { //리스트 속 노드가 1개라면
		h->rlink = h;
		h->llink = h; //리스트를 비워주고
	}
	else {//리스트 속 노드가 2개 이상이라면
		p->rlink->llink = h; //두 번째 노드의 왼쪽 링크는 h를 가리키도록 하고
		h->rlink = p->rlink; //h의 다음 노드가 두 번째 노드(p->rlink(==h->rlink->rlink))를 가리키도록 한 다음에
	}
	free(p); //p에 있는 메모리를 해제한다.

	return 1;

}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h) {

	listNode* p = h->rlink, * temp = h;
	/* p: 리스트를 search하는 포인터
	 * temp: 노드의 순서를 바꿀 때 매개하는 포인터 */
	if (p->rlink == h) { //리스트가 비어있으면
		printf("Noting to invert.\n"); //리스트가 없다고 출력하고
		return -1; //종료
	}

	while (p->key >= 0) { //p가 리스트 한 바퀴를 도는 동안
		temp = p; //p에 있던 값을 temp로 옮김(temp의 한 칸 전진)
		p = p->rlink; //p에 있던 값을 p->link로 옮김(p의 한 칸 전진)
		temp->rlink = temp->llink;
		temp->llink = p;
		/* temp->rlink는 앞 노드를 가리킴(앞 노드<-타겟 노드->뒤 노드)
		 * temp->llink는 p노드를 가리킴(앞 노드<-타겟 노드->뒤 노드)
		 * temp = 타겟 노드, p = 뒤 노드의 역할을 함 */
	}

	h->llink = p->rlink;
	h->rlink = temp;

	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(listNode* h, int key) {

	if (h == NULL) { //헤더값이 없으면
		printf("Cannot insert.\n"); //노드 삽입 불가
		return -1;
	}

	listNode* node = (listNode*)malloc(sizeof(listNode)); //key를 저장할 노드 생성
	node->key = key;
	listNode* p = h->rlink; //리스트 search용 포인터 생성

	//예외사항
	if ((p == h)||((p->rlink == h)&&(p->key > node->key))) { //리스트가 비어있을 때
		//node->rlink = h; //노드의 오른쪽 링크와
		//node->llink = h; //노드의 왼쪽 링크는 헤드 노드를 가리킴
		//h->rlink = node; //헤드 노드는 새로 만든 노드를 가리킴
		insertFirst(h, key);
		free(node);
		return 0;
	}

	while (p->key >= 0) { //리스트가 한 바퀴 돌아가는 동안
		if (p->key > node->key) { //노드의 삽입 위치를 찾았다면
			/* 해당 노드가 리스트의 두 번째 이후의 항목으로 들어간다면
			 * 목적: p가 가리키는 노드 앞에 새 노드를 삽입해야 함 */
			node->rlink = p; //새로 생성한 노드의 오른쪽 링크는 뒤 노드(p)를 가리킴
			node->llink = p->llink; //새 노드의 왼쪽 링크는 앞 노드(p->llink)를 가리킴
			p->llink->rlink = node; //앞 노드의 오른쪽 링크는 새로 생성한 노드를 가리킴
			p->llink = node; //뒤 노드의 왼쪽 링크는 새로 생성한 노드를 가리킴

			return 0; //탐색 종료
		}
		p = p->rlink; //p는 p다음 노드로 이동(노드 1칸 이동)
	}
	/* 여기까지 왔다면 key보다 앞의 값이 없는 것이므로
	 * 리스트의 마지막에 노드를 추가한다. */

	insertLast(h, key);
	free(node); //insertNode에 할당된 메모리 해제

	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) {

	listNode* p = h->rlink; //리스트 search용 포인터 생성

	//예외사항
	if (p == h) { //리스트가 비어있을 때
		printf("Empty list.\n");
		return 0;
	}

	while (p->key >= 0) {
		/* p를 생성해서 key를 찾을때까지 빙글빙글 돌아간다.
		   조건: p가 key를 가리키고 있어야 함 */
		if (p->key == key) { //key를 찾으면?
			if (p == h) { //첫 번째 노드를 삭제한다면
				if (p->rlink == p) { //리스트 노드 개수가 1개일 때
					h->rlink = h; //리스트를 비워준 후
					free(p); //p 해제
					return 0;
				}
				h = p->rlink; //h가 두 번째 노드(p->rlink)를 가리키도록 한 다음에
				p->rlink->llink = h; //두 번째 노드의 왼쪽 링크는 h를 가리키도록 하고
				free(p); //p에 있는 메모리를 해제한다.
				return 0;
			} 
			/* 노드가 2개 이상인 리스트에서 key 찾아 삭제 */
			if (p->rlink == h) { //마지막 노드를 삭제하는 경우라면
				p->llink->rlink = h; //마지막 노드의 이전 노드(p->llink)를 마지막 노드(rlink == h)로 만들고
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
	printf("There is no '%d' to delete.\n", key); //key가 없으면? key가 없다고 출력하고 아무런 작업도 하지 x
	return 0;
}
