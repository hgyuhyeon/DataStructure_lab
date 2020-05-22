/*
 * Binary Search Tree #2
 *
 * Data Structures
 *
 * Department of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>



typedef struct node {
	int key;
	struct node* left;
	struct node* right;
} Node;

/* for stack */
#define MAX_STACK_SIZE		20
Node* stack[MAX_STACK_SIZE];
int top = -1;

Node* pop();
void push(Node* aNode);

/* for queue */
#define MAX_QUEUE_SIZE		20
Node* queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

Node* deQueue();
void enQueue(Node* aNode);


int initializeBST(Node** h);

/* functions that you have to implement */
void recursiveInorder(Node* ptr);	  /* recursive inorder traversal */
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */
void levelOrder(Node* ptr);	          /* level order traversal */
int insert(Node* head, int key);      /* insert a node to the tree */
int deleteNode(Node* head, int key);  /* delete the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


void printStack();



int main()
{
	char command;
	int key;
	Node* head = NULL;

	do {
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf("                [-----[황규현][2019038071]-----]                \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(head, key);
			break;

		case 'r': case 'R':
			recursiveInorder(head->left);
			break;
		case 't': case 'T':
			iterativeInorder(head->left);
			break;

		case 'l': case 'L':
			levelOrder(head->left);
			break;

		case 'p': case 'P':
			printStack();
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if (*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;

	top = -1;

	front = rear = -1;

	return 1;
}



void recursiveInorder(Node* ptr)
{
	if (ptr) {
		recursiveInorder(ptr->left);
		printf(" [%d] ", ptr->key);
		recursiveInorder(ptr->right);
	}
}

/**
 * textbook: p 224
 */
void iterativeInorder(Node* node)
{
	while (1) {
		for (; node; node = node->left)
			push(node); //스택 삽입
		node = pop(); //스택 제거
		if (node == NULL)
			break; //스택이 비어있으면 종료
		printf("%d ", node->key);
		node = node->right;
	}
}

/**
 * textbook: p 225
 */
void levelOrder(Node* ptr)
{
	if (ptr == NULL) {
		printf("Empty Tree.\n");
	}
	enQueue(ptr); //루트노드 삽입
	while (1) {
		ptr = deQueue();
		if (ptr != NULL) {
			printf("%d ", ptr->key);
			if (ptr->left)
				enQueue(ptr->left);
			if (ptr->right)
				enQueue(ptr->right);
		}
		else
			break;
	}
}


int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	if (head->left == NULL) {
		head->left = newNode;
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left;

	Node* parentNode = NULL;
	while (ptr != NULL) {

		/* if there is a node for the key, then just return */
		if (ptr->key == key) return 1;

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr;

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if (ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	/* linking the new node to the parent */
	if (parentNode->key > key)
		parentNode->left = newNode;
	else
		parentNode->right = newNode;
	return 1;
}


int deleteNode(Node* head, int key)
{
	if (head == NULL) { //트리가 생성되지 않았다면
		printf("Need to initialize.\n");
		return -1;
	}

	if (head->left == NULL) { //루트노드가 없으면
		printf("Nothing to delete.\n");
		return 0; //함수 종료
	}

	/* p = 제거할 노드, prev = 제거할 노드의 부모 노드 */
	Node* p = head->left, * prev = head;

	while (p != NULL) { //p가 마지막으로 내려올 때까지
		if (p->key > key) { //key가 노드에 있는 값보다 작으면
			prev = p; //prev도 1레벨 이동
			p = p->left; //왼쪽 자식 노드로 이동
		}
		else if (p->key < key) { //key가 노드에 있는 값보다 크면
			prev = p; //prev도 1레벨 이동
			p = p ->right; //오른쪽 자식 노드로 이동
		}
		else { //key와 노드의 값이 같으면? == 지울 값을 찾았다면?

			 /* 해당 노드가 자식 노드를 갖고있다면 */
			if ((p->left != NULL) || (p->right != NULL)) {
				//1. 양쪽 자식 노드가 있을 때
				if ((p->left != NULL) && p->right != NULL) {
					/* pp = 타겟 노드의 오른쪽 자식 노드들을 가리키는 포인터 생성
					 * prev = pp의 이전 노드를 가리키도록 함.*/
					Node* pp = p->right;
					prev = p;
					while (pp->left != NULL) {//최소값이 나올 때까지
						prev = pp;
						pp = pp->left; //왼쪽으로 내려간다
					}
					p->key = pp->key; //최소값을 타겟노드로 복사
					if (prev == p)
						prev->right = NULL; //예외처리 - 하위 노드가 2단계 이상이 아닐 때
					else
						prev->left = NULL; //최소값을 갖던 리프노드를 NULL로 변경
					free(pp); //원래 최소였던 리프노드 삭제
				}
				//2. 왼쪽 자식 노드가 있을 때
				else if (p->right == NULL) {
					//제거할 노드가 부모 노드의 왼쪽 자식 노드일 때
					if (prev->left == p)
						prev->left = p->left; //부모 노드의 왼쪽 노드와 해당 노드의 왼쪽 자식 노드 연결
					//제거할 노드가 부모 노드의 오른쪽 자식 노드일 때
					else if (prev->right == p)
						prev->right = p->left; //부모 노드의 오른쪽 노드와 해당 노드의 왼쪽 자식 노드 연결
					
					free(p); //해당 노드 삭제
				}
				//3. 오른쪽 자식 노드가 있을 때
				else if (p->left == NULL) {
					//제거할 노드가 부모 노드의 왼쪽 자식 노드일 때
					if (prev->left == p)
						prev->left = p->right; //부모 노드의 왼쪽 노드와 해당 노드의 오른쪽 자식 노드 연결
					//제거할 노드가 부모 노드의 오른쪽 자식 노드일 때
					else if (prev->right == p)
						prev->right = p->right; //부모 노드의 오른쪽 노드와 해당 노드의 오른쪽 자식 노드 연결
					
					free(p); //해당 노드 삭제
				}
				return 0;
			}

			//4. 자식 노드가 없을 때
			if (prev->left == p) { //부모 노드의 왼쪽 자식 노드를 삭제한다면
				prev->left = NULL; //부모 노드의 왼쪽 노드를 비우고
				free(p); //해당 노드 삭제
			}
			else if (prev->right == p) { //부모 노드의 오른쪽 자식 노드를 삭제한다면
				prev->right = NULL; //부모 노드의 오른쪽 노드를 비우고
				free(p); //해당 자식 노드 삭제
			}
			return 0;
		}
	}
	printf("There is no %d to delete.\n", key);
	//해당 key값을 찾지 못한 것이므로 삭제 불가능.
	return 0;
}


void freeNode(Node* ptr)
{
	if (ptr) {
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}

int freeBST(Node* head)
{

	if (head->left == head)
	{
		free(head);
		return 1;
	}

	Node* p = head->left;

	freeNode(p);

	free(head);
	return 1;
}



Node* pop()
{
	Node* x;
	if (top == -1)
		return '\0'; //스택이 이미 비어있을 땐 NULL문자 반환
	else {
		x = stack[top--];
	}
	return x; //끝부분이 한 칸 줄어들은 스택 반환
}

void push(Node* aNode)
{
	stack[++top] = aNode; //스택에 해당 노드 값 추가
}



Node* deQueue()
{
	if (front == rear) //큐가 비어있으면
		return '\0'; //NULL 반환
	else {
		front = (front + 1) % MAX_QUEUE_SIZE; //front의 값을 1 증가(3일 땐 0으로)
		return queue[front];
	}
}

void enQueue(Node* aNode)
{
	rear = (rear + 1) % MAX_QUEUE_SIZE; //rear의 값을 1 증가(3일 땐 0으로)
	if (front == rear) { //큐가 꽉 차있으면
		printf(" Full Queue \n"); //꽉 찼다고 출력하고 들어온 값은 넣지 않음
		rear = (rear - 1) % MAX_QUEUE_SIZE; //rear의 값을 원래대로 돌려주기
	}
	else
		queue[rear] = aNode; //증가된 rear가 위치한 자리에 문자 넣기
}

void printStack() {
	printf("Stack : ");
	for (int i = 0; i < MAX_STACK_SIZE; i++)
		printf("%d  ", stack[i]->key);

	printf("\n");

}
