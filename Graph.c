#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTEX 20

/* 그래프 구현 방식 - 인접 리스트 */


/* 그래프의 정점 노드 */
typedef struct Vertex {
	int num;
	struct Vertex* link;
} Vertex;

/* 그래프의 정점에 대한 헤드 노드 */
typedef struct VertexHead {
	Vertex* head;
} VertexHead;

/* 각 헤드 노드를 가리키는 그래프 인접 리스트 */
typedef struct Graph {
	VertexHead* vlist;
} Graph;

/* Array for DFS  */
Vertex* visited[MAX_VERTEX];
int top = -1;
Vertex* pop();
void push(Vertex* vtex);


/* Queue for BFS */
Vertex* queue[MAX_VERTEX];
int front = -1;
int rear = -1;
Vertex* deQueue();
void enQueue(Vertex* vtex);



/* Functions */
Graph* createGraph(Graph* g); /* empty graph creation */
int destroyGraph(Graph* g); /* deallocating all allocated memory */
int insertVertex(Graph* g, int v); /* vertex insertion */
void deleteVertex(Graph* g, int v); /* vertex deletion */
int insertEdge(Graph* g, int u, int v); /* new edge creation between two vertices */
void deleteEdge(Graph* g, int u, int v); /* edge removal */
void depthFS(Vertex* head); /* depth firt search using stack */
void breadthFS(Graph* g); /* breadth first search using queue */
void printGraph(Graph* g); /* printing graph with vertices and edges */


int main()
{
	char command;
	int key, u, v;
	Graph* g = NULL;

	do {
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                    Term Project - Graph                        \n");
		printf("----------------------------------------------------------------\n");
		printf("                [-----[황규현][2019038071]-----]                \n");
		printf("----------------------------------------------------------------\n");
		printf(" Create Graph         = c                                       \n");
		printf(" Insert Vertex        = v      Delete Vertex                = r \n");
		printf(" insert edge          = e      Delete Edge                  = s \n");
		printf(" DFS(depthFS)         = d      BFS(breadthFS)               = b \n");
		printf(" print Graph          = p      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'c': case 'C':
			g = createGraph(g);
			break;
		case 'q': case 'Q':
			destroyGraph(g);
			break;
		case 'p': case 'P':
			printGraph(g);
			break;
		case 'v': case 'V':
			printf("Your Key = ");
			scanf("%d", &key);
			insertVertex(g, key);
			break;
		case 'r': case 'R':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteVertex(g, key);
			break;
		case 'e': case 'E':
			printf("Your Key = ");
			scanf("%d %d", &u, &v);
			insertEdge(g, u, v);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d %d", &u, &v);
			deleteEdge(g, u, v);
			break;
		case 'd': case 'D':
			depthFS(g->vlist->head);
			break;
		case 'b': case 'B':
			breadthFS(g);
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}

/* 그래프 생성 */
Graph* createGraph(Graph* g) {

	if (g != NULL)
		destroyGraph(g);
	g = (Graph*)malloc(sizeof(Graph));
	g->vlist = (VertexHead *)malloc(sizeof(VertexHead) * MAX_VERTEX); //헤드노드 생성
	for (int i = 0; i < MAX_VERTEX; i++)
		(g->vlist + i)->head = NULL; //첫 번째 정점 NULL
	
	return g;
}

/* 그래프에 연결된 간선들 전부 삭제 */
void freenode(Vertex* adhead) {
	if (adhead != NULL) //adhead->link!=NULL
		freenode(adhead->link);
	free(adhead);
}

/* 그래프 삭제 */
int destroyGraph(Graph* g) {
	VertexHead* gp = g->vlist;
	for (int i = 0; i < MAX_VERTEX; i++)
		if ((gp + i)->head != NULL)
			freenode((gp + i)->head);
	free(gp);
	g->vlist = NULL;
	free(g);
	return 0;
}

/* 정점 추가 */
int insertVertex(Graph* g, int v) {
	// 그래프 g에 정점 v 삽입
	int vv = v - 1; //양의 정수화
	VertexHead* adj = g->vlist;
	if ((adj + vv)->head == NULL) {
		Vertex* node = (Vertex*)malloc(sizeof(Vertex));
		node->num = NULL;
		node->link = NULL;
		(adj + vv)->head = node;
		return 1;
	}
	printf("최대 정점 개수를 초과했습니다.\n");
	return 0;
}


 /* 정점 삭제 */
void deleteVertex(Graph* g, int v) {
	// 그래프 g에 정점 v 삭제
	VertexHead* adj = g->vlist;
	if ((adj + v)->head != NULL) {
		freenode((adj + v)->head);
		(adj + v)->head = NULL;
		return;
	}
	printf("해당하는 정점이 없습니다.\n");
	return;

}

/* 간선 생성 */
int insertEdge(Graph* g, int u, int v) {
	VertexHead* adj = g->vlist;
	int uu = u - 1, vv = v - 1; //vertex를 양의 정수만으로 표현하기 위함

	// u, v중 하나의 vertex라도 존재하지 않을 때
	if (((adj + uu)->head == NULL) || ((adj + vv)->head == NULL)) {
		printf("[%d], [%d] vertexs not exist.\n", u, v);
		return -1;
	}

	// 간선의 방향: u->v
	Vertex* node = (Vertex*)malloc(sizeof(Vertex));
	node->num = vv;
	node->link = (adj + uu)->head;
	(adj + uu)->head = node;
	return 0;
}

/* 간선 삭제 */
void deleteEdge(Graph* g, int u, int v) {
	VertexHead* adj = g->vlist;
	Vertex* p = (adj + u)->head, * prev = (adj + u);

	// u, v중 하나의 vertex라도 존재하지 않을 때
	if (((adj + u)->head == NULL) || ((adj + v)->head == NULL)) {
		printf("[%d], [%d] vertexs not exist.\n", u, v);
		return;
	}

	// 간선의 방향: u->v
	while (p->link != NULL) { //p!=NULL ?s
		if (p->num == v) {
			prev->link = p->link;
			free(p);
			return;
		}
		prev = p;
		p = p->link;
	}
	printf("no edge exist: (%d, %d)", u, v);
}

/* DFS using stack */
void depthFS(Vertex* node) {
	
}

/* BFS using queue */
void breadthFS(Graph* g) {
	Vertex* p = g->vlist->head;
	if (g->vlist == NULL) {
		printf("Empty Graph.\n");
	}
	enQueue(p); //루트노드 삽입
	while (1) {
		p = deQueue();
		if (p != NULL) {
			printf("%d ", (p->num) + 1);
			if (p->link != NULL)
				enQueue(p->link);
		}
		else
			break;
	}

}

/* 그래프 출력 */
void printGraph(Graph* g) {
	VertexHead* gp = g->vlist;
	Vertex* p = g->vlist->head;

	if (gp == NULL) {
		printf("Nothing to print.\n");
		return;
	}

	for (int i = 0; i < MAX_VERTEX; i++) {
		p = (gp + i)->head;

		if (p != NULL) {
			printf("vertex [%d]", i + 1);
			while (p->link != NULL) {
				printf(" -> %d", (p->num) + 1);
				p = p->link;
			}
			printf("\n");
		}
	}
}


///for stack
int isEmpty() {

}
/* 스택에서 꺼내기 */
Vertex* pop() {
	Vertex* x;
	if (top == -1)
		return '\0'; //스택이 이미 비어있을 땐 null문자 반환
	else {
		x = visited[top--];
	}
	return x; //끝부분이 한 칸 줄어들은 스택 반환
}
/* 스택에 추가하기 */
void push(Vertex* vtex) {
	visited[++top] = vtex; //스택에 해당 노드 값 추가
}
///


/// for queue
/* 큐에서 꺼내기 */
Vertex* deQueue() {
	if (front == rear) //큐가 비어있으면
		return '\0'; //NULL 반환
	else {
		front = (front + 1) % MAX_VERTEX; //front의 값을 1 증가(3일 땐 0으로)
		return queue[front];
	}
}
/* 큐에 넣기 */
void enQueue(Vertex* vtex) {
	rear = (rear + 1) % MAX_VERTEX; //rear의 값을 1 증가(3일 땐 0으로)
	if (front == rear) { //큐가 꽉 차있으면
		printf(" Full Queue \n"); //꽉 찼다고 출력하고 들어온 값은 넣지 않음
		rear = (rear - 1) % MAX_VERTEX; //rear의 값을 원래대로 돌려주기
	}
	else
		queue[rear] = vtex; //증가된 rear가 위치한 자리에 문자 넣기
}
///

/* 평가 주안점
	(a) 프로그램이 논리적이고 체계적인가?
	(b) Coding이 군더더기 없이 깔끔한가?
	(c) 잘못된 입력 등에 안정적으로 동작하는가?
	(d) 코드에 충분한 주석이 있어 설명이 잘 되어 있는가?
	(e) 도전적인가? 의미있는 추가함수 구현의 경우 난이도에 따라 전체 총점의 10%이내에서
	가산점 부여
	(f) 보고서의 완성도는 좋은가?
*/

//http://blog.naver.com/PostView.nhn?blogId=kdhkdh0407&logNo=120194479868
//한양대 굇수의 예제 구현
