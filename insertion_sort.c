#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100

int count;

void insertion_sort(int arr[], int n){
	int i, j, key;
	count = 0;
	for (i = 1; i < n; i++){
		key = arr[i];
		for (j = i - 1; j >= 0; j--){
			count++;
			if (arr[j] > key)
				arr[j + 1] = arr[j];
			else
				break;
		}
		arr[j + 1] = key;
	}
}

void print_arr(int arr[], int size){
	for (int i = 0; i < size; i++)
		printf("%d ", arr[i]);
	printf("\n\n");
}

void sorted_arr(int A[]){
	for (int i = 0; i < SIZE; i++)
		A[i] = i + 1;
}

void reversely_sorted_arr(int A[]){
	for (int i = 0; i < SIZE; i++)
		A[i] = SIZE - i;
}

void test(int A[]){
	printf("before : ");
	print_arr(A, SIZE);

	insertion_sort(A, SIZE);

	printf("after : ");
	print_arr(A, SIZE);

	printf("The number of comparisons : %d\n\n", count);
}

int main(){
	int A[SIZE];
	
	printf("===== test1 =====\n");
	srand(time(NULL));
	for (int i = 0; i < SIZE; i++){
		A[i] = rand()%1000;
		for (int j = 0; j < i; j++){
			if (A[i] == A[j]){
				i--;
				break;
			}
		}
	}
	test(A);

	printf("===== test2 =====\n");
	sorted_arr(A);
	test(A);

	printf("===== test3 =====\n");
	reversely_sorted_arr(A);
	test(A);
}
