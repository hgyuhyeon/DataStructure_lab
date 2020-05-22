/*
 * Binary Search Tree #1
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

int initializeBST(Node** h);

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


int main()
{
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */

	do {
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf("                [-----[황규현][2019038071]-----]                \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Node                  = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
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
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if (ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key); //루트노드를 보냄
			if (ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
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
	return 1;
}


void inorderTraversal(Node* ptr)
{
	if (ptr != NULL) {
		inorderTraversal(ptr->left); //일단 가장 왼쪽 노드부터 방문
		printf("%d ", ptr->key); //해당 노드 값을 출력하고
		inorderTraversal(ptr->right); //그 노드의 오른쪽 노드 방문
		/* 오른쪽 노드에서도 왼쪽 노드가 있으면 그 오른쪽 노드의 왼쪽 노드부터 방문함 */
	}
}


void preorderTraversal(Node* ptr)
{
	if (ptr != NULL) {
		printf("%d ", ptr->key); //노드의 값을 먼저 출력한다(루트부터 아래로 내려오겠지?)
		preorderTraversal(ptr->left); //왼쪽 노드를 방문한다
		preorderTraversal(ptr->right); //왼쪽 노드가 없으면 오른쪽 노드 방문
	}
}


void postorderTraversal(Node* ptr)
{
	if (ptr != NULL) {
		postorderTraversal(ptr->left); //일단 왼쪽 끝으로 내려간다
		postorderTraversal(ptr->right); //더 내려갈 왼쪽 끝이 없으면 오른쪽으로 간다
		/* 있으면 더 내려가고, 없으면 호출 종료하고 되돌아옴 */
		printf("%d ", ptr->key); //노드값을 출력한다
	}
}


int insert(Node* head, int key)
{
	if (head == NULL) { //트리가 생성되지 않았다면
		printf("Need to initialize.\n");
		return -1;
	}

	Node* temp = (Node*)malloc(sizeof(Node)); //노드 생성
	temp->key = key;
	temp->left = NULL;
	temp->right = NULL;

	Node* p = head->left, * prev = NULL; //노드 서치용 포인터
	while (p != NULL) { //리프노드로 내려올 때까지
		prev = p; //prev를 1레벨 이동
		if (p->key > temp->key) { //key가 노드에 있는 값보다 작으면
			p = p->left; //왼쪽 자식 노드로 이동
		}
		else if (p->key < temp->key) { //key가 노드에 있는 값보다 크면
			p = p->right; //오른쪽 자식 노드로 이동
		}
		else { //key와 노드의 값이 같으면?
			printf("Same node is already exist.\n");
			return 0;
		}
	}

	if (prev == NULL) { //루트노드가 없으면 
		head->left = temp; //루트 노드를 만들어준다
		return 0;
	}

	/* 현재 prev의 위치 -> 리프 노드 */
	if (prev->key > temp->key) //노드보다 새 key값이 작으면 
		prev->left = temp; //왼쪽 자식 노드로 연결
	else //새 key값이 크면
		prev->right = temp; //오른쪽 자식 노드로 연결
	return 0;
}


int deleteLeafNode(Node* head, int key)
{
	if (head == NULL) { //트리가 생성되지 않았다면
		printf("Need to initialize.\n");
		return -1;
	}

	if (head->left == NULL) { //루트노드가 없으면
		printf("Nothing to delete.\n");
		return 0; //함수 종료
	}

	Node* p = head->left, * prev = head; //노드 서치용 포인터
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
			if ((p->left != NULL) || (p->right != NULL)) { //해당 노드가 자식 노드를 갖고있다면
				printf("Cannot delete: Nodes exist,\n"); //자식 노드가 있어서 못 지움
				return -1;
			}

			if (prev->left == p) { //부모 노드의 왼쪽 자식 노드를 삭제한다면
				prev->left = NULL; //부모 노드의 왼쪽 노드를 비우고
				free(p); //해당 자식 노드 삭제
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


Node* searchRecursive(Node* ptr, int key)
{
	if (ptr != NULL) {
		if (ptr->key > key) //노드값이 key값보다 크다면
			ptr = searchRecursive(ptr->left, key); //왼쪽 자식 노드로 이동
		else if (ptr->key < key) //노드값이 key값보다 작다면
			ptr = searchRecursive(ptr->right, key); //오른쪽 자식 노드로 이동

		if (ptr == NULL) //검색결과가 없으면
			return NULL; //NULL반환

		if (ptr->key == key) //key값을 찾으면
			return ptr; //해당 노드 반환
	}
	return NULL; //결과가 없으면 NULL 반환(재귀의 끝)
}


Node* searchIterative(Node* head, int key)
{
	Node* p = head->left; //노드 search용 포인터 p
	while (p != NULL) {
		if (p->key == key) //key값을 찾으면
			return p; //p가 가리키는 노드 반환
		else if (p->key > key) //노드값이 key값보다 크다면
			p = p->left; //p는 p의 왼쪽 자식 노드를 가리킴
		else //노드값이 key값보다 작다면
			p = p->right; //p는 p의 오른쪽 자식 노드를 가리킴
	}
	return NULL; //결과가 없으므로 NULL반환
}


int freeBST(Node* head)
{
	/* 후위 순회 이용 */
	if (head != NULL) {
		freeBST(head->left); //왼쪽 노드 순회
		if (head->right == head) {
			/* 헤드노드의 특징 상 head->right가 스스로를 가리킴 */
			free(head); //헤드노드를 해제하고
			return 0; //함수를 종료한다
		}
		freeBST(head->right); //오른쪽 노드 순회

		free(head); //헤드 노드를 제외한 모든 타겟 노드를 삭제한다
	}
	
	return 0;
}
