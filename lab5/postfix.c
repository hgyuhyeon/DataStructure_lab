/*
 * postfix.c
 *
 *	Created on: 17 Apr 2020
 *      Author: ghh
 *  2020 Data Structures, Homework #5
 *  Department of Computer Science at Chungbuk National University
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_STACK_SIZE 10
#define MAX_EXPRESSION_SIZE 20

 /* stack 내에서 우선순위, lparen = 0 가장 낮음 */
typedef enum {
	lparen = 0,  /* ( 왼쪽 소괄호  - 가장 낮음(순서 4) */
	rparen = 9,  /* ) 오른쪽 소괄호 - 가장 높음(순서 1)*/
	times = 7,   /* * 곱하기 연산자 (순서 2)*/
	divide = 6,  /* / 나누기 연산자 (순서 2)*/
	plus = 5,    /* + 더하기 연산자 (순서 3)*/
	minus = 4,   /* - 빼기 연산자 (순서 3)*/
	operand = 1 /* 피연산자 */
} precedence;

//infix->postfix->evaluation 순으로 계산

char infixExp[MAX_EXPRESSION_SIZE];   	/* infix expression을 저장하는 배열 */
char postfixExp[MAX_EXPRESSION_SIZE];	/* postfix로 변경된 문자열을 저장하는 배열 */
char postfixStack[MAX_STACK_SIZE];	/* postfix로 변환을 위해 필요한 스택 */
int evalStack[MAX_STACK_SIZE];		/* 계산을 위해 필요한 스택 */

int postfixStackTop = -1;  /* postfixStack의 첫 번째 */
int evalStackTop = -1;	   /* evalStack의 첫 번째 */

int evalResult = 0;	   /* 계산 결과를 저장 */

void postfixPush(char x) //스택에 문자 추가
{
	postfixStack[++postfixStackTop] = x;
}

char postfixPop() //스택에서 문자 빼내기
{
	char x;
	if (postfixStackTop == -1)
		return '\0'; //스택이 이미 비어있을 땐 NULL문자 반환
	else {
		x = postfixStack[postfixStackTop--];
	}
	return x; //끝부분이 한 칸 줄어들은 스택 반환
}


void evalPush(int x) //evluation에 문자 집어넣기
{
	evalStack[++evalStackTop] = x;
}

int evalPop() //evaluation에서 문자 빼내기
{
	if (evalStackTop == -1)
		return -1; //스택이 이미 비어있을 땐 -1 반환
	else
		return evalStack[evalStackTop--]; //끝부분이 한 칸 줄어들은 스택 반환
}


/*
 * infix expression을 입력받는다.
 * infixExp에는 입력된 값을 저장한다.
 */
void getInfix()
{
	printf("Type the expression >>> ");
	scanf("%s", infixExp);
}

//토큰을 찾아 해당 연산자와 피연산자 구별
precedence getToken(char symbol)
{
	switch (symbol) {
	case '(': return lparen;
	case ')': return rparen;
	case '+': return plus;
	case '-': return minus;
	case '/': return divide;
	case '*': return times;
	default: return operand;
	}

}

//우선순위에 따라 스택에 넣고 빼기
precedence getPriority(char x)
{
	return getToken(x);
}

/**
 * 문자 하나를 전달받아, postfixExp에 추가
 */
void charCat(char* c)
{
	if (postfixExp == '\0') //문자열이 비어있을 땐
		strncpy(postfixExp, c, 1); //문자 붙여넣기
	else
		strncat(postfixExp, c, 1); //이미 생성된 문자열 뒤에 문자 붙여넣기
}

/*
 * infixExp의 문자를 하나식 읽어가면서 stack을 이용하여 postfix로 변경한다.
 * 변경된 postfix는 postfixExp에 저장된다.
 */
void toPostfix()
{
	/* infixExp의 문자 하나씩을 읽기위한 포인터 */
	char *exp = infixExp;

	char x;
	/* 문자하나를 임시로 저장하기 위한 변수 */

	/* exp를 증가시켜가면서, 문자를 읽고 postfix로 변경 */
	while (*exp != '\0') //infixExp의 입력된 끝부분까지
	{
		x = *exp; //포인터가 가리키는 infixExp의 문자를 저장
		char px = getToken(x); //x의 우선순위를 구해 리턴

		if (px == operand) { //x가 피연산자일 때
			charCat(&x); //postfixExp에 저장
		}
		else if (px == rparen) { //연산자가 오른쪽 괄호이면
			while (postfixStack[postfixStackTop] != '(') { //왼쪽 괄호를 만나기 전까지
				charCat(&postfixStack[postfixStackTop]); //연산자를 옮기고
				postfixPop(); //스택을 지운다
			}
			postfixPop(); //왼쪽 괄호를 지운다
		}
		else if ((postfixStackTop == -1) && (px != operand)||(px==lparen)) {
			//연산자이면서 스택이 비거나, 연산자가 왼쪽 괄호이면
			postfixPush(x); //스택에 넣는다
		}
		else if ((postfixStackTop != -1) && (px <= getPriority(postfixStack[postfixStackTop]))) {
			/* 스택이 비어있지 않으면서 스택의 연산자와 우선순위가 같거나
			스택에 들어있는 연산자의 우선순위가 더 크면 */
			charCat(&postfixStack[postfixStackTop]); //스택의 연산자를 Exp에 저장
			postfixPop(); //스택의 연산자 제거
			postfixPush(x); //현재의 연산자를 스택에 추가
		}
		else if ((postfixStackTop != -1) && (px > getPriority(postfixStack[postfixStackTop]))) {
      // 스택이 비어있지 않으면서 스택에 들어있는 연산자의 우선순위보다 작으면
			postfixPush(x); //현재의 연산자를 스택에 추가
		}
		++exp; //exp가 다음 값을 가리키도록 함
	}

  //Exp에 들어가지 못한 남은 연산자들은
	while (postfixStackTop != -1) { //스택이 비어있을 때까지
		charCat(&postfixStack[postfixStackTop]); //스택에 남은 연산자를 Exp에 옮기고
		postfixPop(); //스택 지우기
	}

	x = '\0';
	charCat(&x); //마지막엔 NULL문자를 추가!
}

void debug()
{
	printf("\n---DEBUG\n");
	printf("infixExp =  %s\n", infixExp);
	printf("postExp =  %s\n", postfixExp);
	printf("eval result = %d\n", evalResult);

	printf("postfixStack : ");
	for (int i = 0; i < MAX_STACK_SIZE; i++)
		printf("%c  ", postfixStack[i]);

	printf("\n");

}

void reset()
{
	infixExp[0] = '\0';
	postfixExp[0] = '\0';

	for (int i = 0; i < MAX_STACK_SIZE; i++)
		postfixStack[i] = '\0';

	postfixStackTop = -1;
	evalStackTop = -1;
	evalResult = 0;
}

void evaluation()
{
	/* postfixExp, evalStack을 이용한 계산 */
	int i = 0;
	int ix, iy; //char형 문자 변수를 계산식으로 변환해 줄 int형 변수들
	char x, y; //문자를 받아와 줄 char형 변수들

	while (postfixExp[i] != '\0') {
		if (getToken(postfixExp[i]) == 1) { //피연산자일때
			evalPush(postfixExp[i]); // 스택에 숫자 저장
		}
		else {
			if (evalResult == 0) { //결괏값이 0일 때
				x = evalStack[evalStackTop]; //스택에 저장된 값(1) 가져오기
				evalPop(); //방금 불러온 값이 저장된 스택 1칸 삭제
				ix = (int)x - 48; //아스키코드 0은 48.
			}
			else {
				ix = evalResult; //result에 저장된 값(1) 가져오기
        /* evalResult의 값에 따라 나눈 이유: 중간 계산결과가 10을 넘을 수 있기 때문. */
			}
			y = evalStack[evalStackTop]; //저장된 값(2) 불러오기
			evalPop(); //불러온 값이 저장된 스택 삭제
			iy = (int)y - 48; //char형 문자를 int형 숫자로 변환
			switch (postfixExp[i]) {
			case '+':
				evalResult = iy + ix;
				break;
			case '-':
				if (evalResult == 0)
					evalResult = iy - ix; //나중에 불러온 값 - 먼저 불러온 값
				else
					evalResult = ix - iy; //미리 저장된 값 - 새로 불러온 값
				break;
			case '*':
				evalResult = iy * ix;
				break;
			case '/':
				if (evalResult == 0)
					evalResult = iy / ix; //나중에 불러온 값 / 먼저 불러온 값
				else
					evalResult = ix / iy; //미리 저장된 값 / 새로 불러온 값
          /* '-', '/' 연산자에서 evalResult값에 따라 연산 순서가 나뉜 이유
             evalResult가 0일 땐 최근 순서대로 값을 2개 불러오므로
             나중에 불러온 값이 더 먼저 저장된 값이지만
             0이 아닐 땐 evalResult의 값과 새로 불러온 값 하나와 연산하게 되어
             evalResult의 값이 먼저 저장되었기 때문이다.
          */
				break;
			default:
				break;
			} //switch문 끝
		} //if문 끝
		i++;
	} //while문 끝
}


int main()
{
	char command;

	do {
		printf("----------------------------------------------------------------\n");
		printf("-----------------------[황규현][2019038071]----------------------\n");
		printf("----------------------------------------------------------------\n");
		printf("               Infix to Postfix, then Evaluation               \n");
		printf("----------------------------------------------------------------\n");
		printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'i': case 'I':
			getInfix(); //수식 입력
			break;
		case 'p': case 'P':
			toPostfix();
			break;
		case 'e': case 'E':
			evaluation(); //변환 결과 출력
			break;
		case 'd': case 'D':
			debug(); //디버그, 각 변수의 상태 확인
			break;
		case 'r': case 'R':
			reset(); //초기화
			break;
		case 'q': case 'Q':
			break; //프로그램 종료
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 0;

}
