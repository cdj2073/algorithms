#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int size;
int multiplication;
int subtraction;
int addition;

int **create_matrix(int n){
	int **A = (int **)malloc(sizeof(int *) * n);
	for (int i = 0; i < n; i++)
		A[i] = (int *)malloc(sizeof(int) * n);
	return A;
}

void free_matrix(int **A, int n){
	for (int i = 0; i < n; i++){
		free(A[i]);
		A[i] = NULL;
	}
	free(A);
	A = NULL;
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

void print_matrix(int **A, int n){
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++)
			printf("%d\t", A[i][j]);
		printf("\n");
	}
	printf("\n");
}

int **add_matrix(int **A, int **B, int n){
	int **C = create_matrix(n);

	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			C[i][j] = A[i][j] + B[i][j];
			addition++;
		}
	}
	return C;
}

int **sub_matrix(int **A, int **B, int n){
	int **C = create_matrix(n);

	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			C[i][j] = A[i][j] - B[i][j];
			subtraction++;
		}
	}
	return C;
}

int **standard_algorithm(int **A, int **B, int n){
	int **C = create_matrix(n);

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
	return C;
}

int **divide_and_conquer_algorithm(int **A, int **B, int n){
	int **C = create_matrix(n);

	if (n == 1){
		C[0][0] = A[0][0] * B[0][0];
		multiplication++;
		return C;
	}
	else{
		int **A11 = create_matrix(n / 2);
		int **A12 = create_matrix(n / 2);
		int **A21 = create_matrix(n / 2);
		int **A22 = create_matrix(n / 2);
		int **B11 = create_matrix(n / 2);
		int **B12 = create_matrix(n / 2);
		int **B21 = create_matrix(n / 2);
		int **B22 = create_matrix(n / 2);

		for (int i = 0; i < n / 2; i++){
			for (int j = 0; j < n / 2; j++){
				A11[i][j] = A[i][j];
				A12[i][j] = A[i][n / 2 + j];
				A21[i][j] = A[n / 2 + i][j];
				A22[i][j] = A[n / 2 + i][n / 2 + j];
				B11[i][j] = B[i][j];
				B12[i][j] = B[i][n / 2 + j];
				B21[i][j] = B[n / 2 + i][j];
				B22[i][j] = B[n / 2 + i][n / 2 + j];
			}
		}

/*
//  	memory leak??????
		int **P1 = divide_and_conquer_algorithm(A11, B11, n / 2);
		int **P2 = divide_and_conquer_algorithm(A12, B21, n / 2);
		int **P3 = divide_and_conquer_algorithm(A11, B12, n / 2);
		int **P4 = divide_and_conquer_algorithm(A12, B22, n / 2);
		int **P5 = divide_and_conquer_algorithm(A21, B11, n / 2);
		int **P6 = divide_and_conquer_algorithm(A22, B21, n / 2);
		int **P7 = divide_and_conquer_algorithm(A21, B12, n / 2);
		int **P8 = divide_and_conquer_algorithm(A22, B22, n / 2);

		int **C11 = add_matrix(P1, P2, n / 2);
		int **C12 = add_matrix(P3, P4, n / 2);
		int **C21 = add_matrix(P5, P6, n / 2);
		int **C22 = add_matrix(P7, P8, n / 2);
*/

		int **C11 = add_matrix(divide_and_conquer_algorithm(A11, B11, n / 2), divide_and_conquer_algorithm(A12, B21, n / 2), n / 2);
		int **C12 = add_matrix(divide_and_conquer_algorithm(A11, B12, n / 2), divide_and_conquer_algorithm(A12, B22, n / 2), n / 2);
		int **C21 = add_matrix(divide_and_conquer_algorithm(A21, B11, n / 2), divide_and_conquer_algorithm(A22, B21, n / 2), n / 2);
		int **C22 = add_matrix(divide_and_conquer_algorithm(A21, B12, n / 2), divide_and_conquer_algorithm(A22, B22, n / 2), n / 2);

		for (int i = 0; i < n / 2; i++){
			for (int j = 0; j < n / 2; j++){
				C[i][j] = C11[i][j];
				C[i][n / 2 + j] = C12[i][j];
				C[n / 2 + i][j] = C21[i][j];
				C[n / 2 + i][n / 2 + j] = C22[i][j];
			}
		}

		if (n > 2){
			printf("Partial matrix of C\n");
			printf("C11\n");
			print_matrix(C11, n / 2);
			printf("C12\n");
			print_matrix(C12, n / 2);
			printf("C21\n");
			print_matrix(C21, n / 2);
			printf("C22\n");
			print_matrix(C22, n / 2);
		}

		free_matrix(A11, n / 2);
		free_matrix(A12, n / 2);
		free_matrix(A21, n / 2);
		free_matrix(A22, n / 2);
		free_matrix(B11, n / 2);
		free_matrix(B12, n / 2);
		free_matrix(B21, n / 2);
		free_matrix(B22, n / 2);
		free_matrix(C11, n / 2);
		free_matrix(C12, n / 2);
		free_matrix(C21, n / 2);
		free_matrix(C22, n / 2);

/*
		free_matrix(P1, n / 2);
		free_matrix(P2, n / 2);
		free_matrix(P3, n / 2);
		free_matrix(P4, n / 2);
		free_matrix(P5, n / 2);
		free_matrix(P6, n / 2);
		free_matrix(P7, n / 2);
		free_matrix(P8, n / 2);
*/

		return C;
	}
}


int **strassen_algorithm(int **A, int **B, int n){
	int **C = create_matrix(n);

	if (n == 1){
		C[0][0] = A[0][0] * B[0][0];
		multiplication++;
		return C;
	}
	else{
		int **A11 = create_matrix(n / 2);
		int **A12 = create_matrix(n / 2);
		int **A21 = create_matrix(n / 2);
		int **A22 = create_matrix(n / 2);
		int **B11 = create_matrix(n / 2);
		int **B12 = create_matrix(n / 2);
		int **B21 = create_matrix(n / 2);
		int **B22 = create_matrix(n / 2);

		for (int i = 0; i < n / 2; i++){
			for (int j = 0; j < n / 2; j++){
				A11[i][j] = A[i][j];
				A12[i][j] = A[i][n / 2 + j];
				A21[i][j] = A[n / 2 + i][j];
				A22[i][j] = A[n / 2 + i][n / 2 + j];
				B11[i][j] = B[i][j];
				B12[i][j] = B[i][n / 2 + j];
				B21[i][j] = B[n / 2 + i][j];
				B22[i][j] = B[n / 2 + i][n / 2 + j];
			}
		}

		int **P1 = strassen_algorithm(A11, sub_matrix(B12, B22, n / 2), n / 2);
		int **P2 = strassen_algorithm(add_matrix(A11, A12, n / 2), B22, n / 2);
		int **P3 = strassen_algorithm(add_matrix(A21, A22, n / 2), B11, n / 2);
		int **P4 = strassen_algorithm(A22, sub_matrix(B21, B11, n / 2), n / 2);
		int **P5 = strassen_algorithm(add_matrix(A11, A22, n / 2), add_matrix(B11, B22, n / 2), n / 2);
		int **P6 = strassen_algorithm(sub_matrix(A12, A22, n / 2), add_matrix(B21, B22, n / 2), n / 2);
		int **P7 = strassen_algorithm(sub_matrix(A11, A21, n / 2), add_matrix(B11, B12, n / 2), n / 2);

		int **C11 = add_matrix(P5, sub_matrix(P4, sub_matrix(P2, P6, n / 2), n / 2), n / 2);
		int **C12 = add_matrix(P1, P2, n / 2);
		int **C21 = add_matrix(P3, P4, n / 2);
		int **C22 = add_matrix(P5, sub_matrix(P1, add_matrix(P3, P7, n / 2), n / 2), n / 2);

		for (int i = 0; i < n / 2; i++){
			for (int j = 0; j < n / 2; j++){
				C[i][j] = C11[i][j];
				C[i][n / 2 + j] = C12[i][j];
				C[n / 2 + i][j] = C21[i][j];
				C[n / 2 + i][n / 2 + j] = C22[i][j];
			}
		}

		if (n > 2){
			printf("Partial matrix of C\n");
			printf("C11\n");
			print_matrix(C11, n / 2);
			printf("C12\n");
			print_matrix(C12, n / 2);
			printf("C21\n");
			print_matrix(C21, n / 2);
			printf("C22\n");
			print_matrix(C22, n / 2);
		}


		free_matrix(A11, n / 2);
		free_matrix(A12, n / 2);
		free_matrix(A21, n / 2);
		free_matrix(A22, n / 2);
		free_matrix(B11, n / 2);
		free_matrix(B12, n / 2);
		free_matrix(B21, n / 2);
		free_matrix(B22, n / 2);
		free_matrix(C11, n / 2);
		free_matrix(C12, n / 2);
		free_matrix(C21, n / 2);
		free_matrix(C22, n / 2);

		free_matrix(P1, n / 2);
		free_matrix(P2, n / 2);
		free_matrix(P3, n / 2);
		free_matrix(P4, n / 2);
		free_matrix(P5, n / 2);
		free_matrix(P6, n / 2);
		free_matrix(P7, n / 2);

		return C;
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
	printf("\n");
}

int main(){
	int **A, **B, **C1, **C2, **C3;

	// 4x4 matrix
	size = 4;
	printf("===== 4x4 matrix =====\n");
	A = create_matrix(size);
	B = create_matrix(size);

	rand_fill(A, B, size);

	multiplication = 0;
	subtraction = 0;
	addition = 0;
	printf("===== standard algorithm =====\n");
	C1 = standard_algorithm(A, B, size);
	print_result(A, B, C1, size);

	multiplication = 0;
	subtraction = 0;
	addition = 0;
	printf("===== divide-and-conquer algorithm =====\n");
	C2 = divide_and_conquer_algorithm(A, B, size);
	print_result(A, B, C2, size);

	multiplication = 0;
	subtraction = 0;
	addition = 0;
	printf("===== strassen algorithm =====\n");
	C3 = strassen_algorithm(A, B, size);
	print_result(A, B, C3, size);

	free_matrix(A, size);
	free_matrix(B, size);
	free_matrix(C1, size);
	free_matrix(C2, size);
	free_matrix(C3, size);


	// 8x8 matrix
	size = 8;
	printf("===== 8x8 matrix =====\n");
	A = create_matrix(size);
	B = create_matrix(size);

	rand_fill(A, B, size);

	multiplication = 0;
	subtraction = 0;
	addition = 0;
	printf("===== standard algorithm =====\n");
	C1 = standard_algorithm(A, B, size);
	print_result(A, B, C1, size);

	multiplication = 0;
	subtraction = 0;
	addition = 0;
	printf("===== divide-and-conquer algorithm =====\n");
	C2 = divide_and_conquer_algorithm(A, B, size);
	print_result(A, B, C2, size);

	multiplication = 0;
	subtraction = 0;
	addition = 0;
	printf("===== strassen algorithm =====\n");
	C3 = strassen_algorithm(A, B, size);
	print_result(A, B, C3, size);

	free_matrix(A, size);
	free_matrix(B, size);
	free_matrix(C1, size);
	free_matrix(C2, size);
	free_matrix(C3, size);
}
