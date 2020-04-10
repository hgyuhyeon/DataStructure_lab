/*
 * matrix.c
 *
 *  Created on: 10 Apr 2020
 *      Author: ghh
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>

int n= -1;
int *pn = &n;
int **N = &pn;
/* NULL 포인터로의 접근을 시도해봤으나 NULL로 처리할 경우 segmentation fault 오류 발생함
   (아마도 NULL포인터로의 접근이 원인인 듯)
   그래서 메모리를 할당하거나 값을 수정하는 데 실패할 경우 -1을 반환하도록 전역변수 선언
   이중 포인터끼리는 이중 포인터끼리로만 리턴이 가능하도록 gcc가 철저했다.
*/

//2차원 행렬을 동적으로 생성하는 함수
int** create_matrix(int row, int col) {

	//배열의 세로 생성 - 가로 공간의 메모리 주소가 들어감
	int** matrix = malloc(sizeof(int*) * row);
	/* 2차원 배열의 행이 되어줄 1차원 배열 할당 */
	if (matrix == NULL) {
		printf("메모리 생성 실패!\n");
		return N;
	} //후처리 검사

	//배열의 가로 생성
	for (int i = 0; i < row; i++) {
		matrix[i] = malloc(sizeof(int) * col);
		/* 각 세로 공간별로 메모리를 할당하여 2차원 배열 생성!*/
		if (matrix == NULL) {
			printf("메모리 생성 실패!\n");
			return N;
		} //후처리 검사
	}
	return matrix; //만들어진 동적 메모리 리턴!
}

//동적 메모리 해제 함수
int free_matrix(int** matrix, int row, int col) {
	if (row <= col)
		for (int i = 0; i < row; i++)
			free(matrix[i]); //2차원 배열의 가로(열) 메모리 해제(행이 열보다 작거나 같을 때)
	else
		for (int i = 0; i < col; i++)
			free(matrix[i]); //2차원 배열의 가로(열) 메모리 해제(행이 열보다 클 때)
	free(matrix); //2차원 배열의 세로(행) 메모리 해제
	return **N; //메모리 중복 해제 방지
}

//사이즈가 row*col인 행렬 출력
void print_matrix(int** matrix, int row, int col) {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			printf("%5d ", matrix[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");
}

//주어진 행렬에 랜덤 값 집어넣기
int fill_data(int** matrix, int row, int col) {

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			matrix[i][j] = rand() % 20;
		}
	}

	if (matrix[row - 1][col - 1] >= 0 && matrix[row - 1][col - 1] < 20)
		return **matrix; //마지막 값까지 정상적으로 입력되었으면 행렬 반환
	else
		return **N; //그렇지 않으면 NULL반환
}

//주어진 행렬의 전치행렬 함수
int transpose_matrix(int** matrix, int** matrix_t, int row, int col) {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			matrix_t[j][i] = matrix[i][j];
		}
	}
	if (matrix[row - 1][col - 1] == matrix_t[col - 1][row - 1])
		return **matrix_t; //각 행렬의 마지막 수의 값이 똑같으면 전치행렬 반환
	else
		return **N;
}

//행렬 A와 B를 더하는 함수
int addition_matrix(int** matrix_a, int** matrix_b, int** matrix_sum,
	int row, int col) {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			matrix_sum[i][j] = matrix_a[i][j] + matrix_b[i][j]; //sum행렬에 A+B값을 저장
		}
	}
	return **matrix_sum;
}

//행렬 A에서 B를 빼는 함수
int subtraction_matrix(int** matrix_a, int** matrix_b, int** matrix_sub,
	int row, int col) {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			matrix_sub[i][j] = matrix_a[i][j] - matrix_b[i][j]; //sub행렬에 A-B값을 저장
		}
	}
	return **matrix_sub;
}

//행렬 A와 T를 곱하는 함수
int multiply_matrix(int** matrix_a, int** matrix_t, int** matrix_axt,
	int row, int col) {
	if (sizeof(matrix_a[row]) != sizeof(matrix_t[col])) {
		/* a의 열 개수와 t의 행 개수의 불일치 시 곱하지 않음*/
		printf("행렬곱 불가능.\n");
		return **N; //행렬곱이 불가능할 경우 NULL반환
	}

	int sum;
	if (row <= col) { //입력받은 행이 열보다 작거나 같을 때
		for (int i = 0; i < row; i++) { //AxT행렬의 행 증가, A행렬의 행 증가
			for (int j = 0; j < row; j++) { //AxT행렬의 열 증가, T행렬의 열 증가
				sum = 0;
				for (int k = 0; k < row; k++) //A행렬의 열, T행렬의 행 증가
					sum += matrix_a[i][k] * matrix_t[k][j];
				matrix_axt[i][j] = sum;
			}
		}
	}
	else if (row > col) { //입력받은 행이 열보다 클 때(k의 조건을 제외한 나머지는 전부 위 루프와 동일)
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < row; j++) {
				sum = 0;
				for (int k = 0; k < col; k++)
					/*조건을 위와 같이 row로 할 경우 k가 col 이상의 요소를 가리킬 수 있으므로
					동일한 루프를 col로 수정 */
					sum += matrix_a[i][k] * matrix_t[k][j];
				matrix_axt[i][j] = sum;
			}
		}
	}

	return **matrix_axt;
}


int main(void) {

	int row = 0, col = 0;

	printf("[----- [황규현]  [2019038071] -----]\n\n");

	//행렬 생성 & 데이터 입력
	while (1) { //행렬의 크기가 정상적으로 입력될 때까지 반복
		printf("행렬의 크기 입력(입력 형식: row col): ");
		scanf("%d %d", &row, &col);
		if (row > 0 && col > 0)
			break;
		else
			printf("행렬의 크기가 0 이하입니다. \n\n");
	}

	srand(time(NULL));

	/* 행렬 A 생성 */
	int** A = create_matrix(row, col);
	**A = fill_data(A, row, col);

	/* 행렬 B 생성 */
	int** B = create_matrix(row, col);
	**B = fill_data(B, row, col);
	//행렬 생성 & 데이터 입력 끝

	//생성된 A B 행렬 출력
	printf("\n행렬 A\n");
	print_matrix(A, row, col);
	printf("행렬 B\n");
	print_matrix(B, row, col);

	//A+B
	int** sum = create_matrix(row, col); //sum행렬 생성
	**sum = addition_matrix(A, B, sum, row, col); //연산
	printf("\nA+B\n");
	print_matrix(sum, row, col); //출력
	free_matrix(sum, row, col); //sum행렬의 메모리 해제

	//A-B
	int** sub = create_matrix(row, col); //sub행렬 생성
	**sub = subtraction_matrix(A, B, sub, row, col); //연산
	printf("A-B\n");
	print_matrix(sub, row, col); //출력
	free_matrix(sub, row, col); //sub행렬의 메모리 해제

	//make a transpose matrix T!
	int** T = create_matrix(col, row);
	**T = transpose_matrix(A, T, row, col);
	printf("행렬 T\n");
	print_matrix(T, col, row);

	//AxT
	int** AxT = create_matrix(row, row); //행렬 생성 기준: A행렬의 행 x T행렬(전치행렬)의 열
	**AxT = multiply_matrix(A, T, AxT, row, col);
	printf("A X T\n");
	print_matrix(AxT, row, row);

	//모든 동적 메모리 해제
	free_matrix(A, row, col); //A행렬 메모리 헤제
	free_matrix(B, row, col); //B행렬 메모리 해제
	free_matrix(T, row, col); //A의 전치행렬인 T행렬 메모리 해제
	free_matrix(AxT, row, col); //A와 T의 행렬곱인 AxT행렬 메모리 해제

	return 0;
}
