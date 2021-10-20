#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100

int sorted[SIZE];
int count;

void merge(int arr[], int left, int mid, int right){
	int i = left;
	int j = mid + 1;
	int k = left;

	while (i <= mid && j <= right){
		if (arr[i] >= arr[j]){
			sorted[k++] = arr[i++];
		}
		else{
			sorted[k++] = arr[j++];
		}
		count++;
	}
	if (i > mid){
		while (j <= right)
			sorted[k++] = arr[j++];
	}
	else{
		while (i <= mid)
			sorted[k++] = arr[i++];
	}
	for (int t = left; t <= right; t++)
		arr[t] = sorted[t];
}

void merge_sort(int arr[], int left, int right){
	int mid;

	if (left < right){
		mid = (left + right) / 2;
		merge_sort(arr, left, mid);
		merge_sort(arr, mid + 1, right);
		merge(arr, left, mid, right);
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

	merge_sort(A, 0, SIZE - 1);

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

	count = 0;
	printf("===== test2 =====\n");
	sorted_arr(A);
	test(A);

	count = 0;
	printf("===== test3 =====\n");
	reversely_sorted_arr(A);
	test(A);
}
