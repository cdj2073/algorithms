#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int size;
int multiplication;
int subtraction;
int addition;

void standard_algorithm(int **A, int **B, int **C, int n){
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			C[i][j] = 0;
			for (int k = 0; k < n; k++){
				C[i][j] += A[i][k] * B[k][j];
				multiplication++;
				addition++;
			}
		}
	}
}

void print_matrix(int **A, int n){
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++)
			printf("%d ", A[i][j]);
		printf("\n");
	}
}

void print_result(int **A, int **B, int **C, int n){
	printf("matrix A : \n");
	print_matrix(A, n);
	printf("matrix B : \n");
	print_matrix(B, n);
	printf("matrix C = A x B : \n");
	print_matrix(C, n);

	printf("The number of multiplication : %d\n", multiplication);
	printf("The number of subtraction : %d\n", subtraction);
	printf("The number of addition : %d\n", addition);
}

void init(int **A, int n){
	A = (int **)malloc(sizeof(int *) * n);
	for (int i = 0; i < n; i++)
		A[i] = (int *)malloc(sizeof(int) * n);
	printf("init finish\n");
}

void rand_fill(int **A, int n){
	srand(time(NULL));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			A[i][j] = rand()%1000;
}

int main(){
	int **A, **B, **C;

	init(A, size);
	init(B, size);
	init(C, size);
	// 4x4 matrix
	size = 4;
	rand_fill(A, size);	// rand()%1000
	rand_fill(B, size);

	printf("helloo==================\n");
	print_matrix(A, size);

	multiplication = 0;
	subtraction = 0;
	addition = 0;
	printf("===== standard algorithm =====\n");
	standard_algorithm(A, B, C, size);
	print_result(A, B, C, size);
//	printf("The number of multiplication : %d\n", multiplication);
//	printf("The number of subtraction : %d\n", subtraction);
//	printf("The number of addition : %d\n", addition);

}
