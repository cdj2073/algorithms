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
			addition--;
			for (int k = 0; k < n; k++){
				C[i][j] += A[i][k] * B[k][j];
				multiplication++;
				addition++;
			}
		}
	}
}

void divide_and_conquer_algorithm(int **A, int **B, int **C, int n){

}


void strassen_algorithm(int **A, int **B, int **C, int n){

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

int **create_matrix(int n){
	int **A = (int **)malloc(sizeof(int *) * n);
	for (int i = 0; i < n; i++)
		A[i] = (int *)malloc(sizeof(int) * n);
	return A;
}

void rand_fill(int **A, int **B, int n){
	srand(time(NULL));
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			A[i][j] = rand()%1000;
			B[i][j] = rand()%1000;
		}
	}
}

int main(){
	int **A, **B, **C;

	// 4x4 matrix
	printf("===== 4x4 matrix =====\n");
	size = 4;
	A = create_matrix(size);
	B = create_matrix(size);
	C = create_matrix(size);

	rand_fill(A, B, size);

	multiplication = 0;
	subtraction = 0;
	addition = 0;
	printf("===== standard algorithm =====\n");
	standard_algorithm(A, B, C, size);
	print_result(A, B, C, size);

	multiplication = 0;
	subtraction = 0;
	addition = 0;
	printf("===== divide-and-conquer algorithm =====\n");
	divide_and_conquer_algorithm(A, B, C, size);
	print_result(A, B, C, size);

	multiplication = 0;
	subtraction = 0;
	addition = 0;
	printf("===== strassen algorithm =====\n");
	strassen_algorithm(A, B, C, size);
	print_result(A, B, C, size);

}
