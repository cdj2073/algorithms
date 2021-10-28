#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define M 41
#define SIZE 35

typedef struct Node {
	int key;
	int flag;
	int probes;
} Node;

Node table_linear[M];
Node table_quadratic[M];
Node table_double[M];

int hash(int key) {
    return key % M;
}

void insert_linear(int k) {
	int i = 0;
	int bucket;
	while (i < M) {
		bucket = hash(hash(k) + i);
		if (table_linear[bucket].flag == 0) {
			table_linear[bucket].flag = 1;
			table_linear[bucket].key = k;
			table_linear[bucket].probes += i;
			return;
		}
		i++;
	}
}

void insert_quadratic(int k) {
	int c1 = 1;
	int c2 = 3;
	int i = 0;
	int bucket;

	while (i < M) {
		bucket = hash(hash(k) + c1 * i + c2 * i * i);
		if (table_quadratic[bucket].flag == 0) {
			table_quadratic[bucket].flag = 1;
			table_quadratic[bucket].key = k;
			table_quadratic[bucket].probes += i;
			return;
		}
		i++;
	}
}

void insert_double(int k) {
	int h1 = hash(k);
	int h2 = 1 + (k % (M - 1));
	int i = 0;
	int bucket;

	while (i < M) {
		bucket = hash(h1 + i * h2);
		if (table_double[bucket].flag == 0) {
			table_double[bucket].flag = 1;
			table_double[bucket].key = k;
			table_double[bucket].probes += i;
			return;
		}
		i++;
	}
}

void print_table(Node *table) {
	int max = 0;
	int count = 0;
	float avg_probes = 0;

	for (int i = 0; i < M; i++) {
		printf("BUCKET[%d] : ", i);
		if (table[i].flag == 1) {
			count++;
			avg_probes += table[i].probes;
			printf("%d\n", table[i].key);
		}
		else {
			if (count > max)
				max = count;
			count = 0;
			printf("empty\n");
		}
	}
	if (count > max)
		max = count;
	avg_probes /= SIZE;

	printf("The average number of probes is %f\n", avg_probes);
	printf("The primary cluster length is %d\n\n", max);
}

int main() {
	int keys[SIZE];

	srand(time(NULL));
	for (int i = 0; i < SIZE; i++) {
		keys[i] = rand()%1000;
		for (int j = 0; j < i; j++) {
			if (keys[i] == keys[j]) {
				i--;
				break;
			}
		}
	}

	// insert keys to hash tables
	for (int i = 0; i < SIZE; i++) {
		insert_linear(keys[i]);
		insert_quadratic(keys[i]);
		insert_double(keys[i]);
	}

	// print hash tables
	printf("===== linear probing =====\n");
	print_table(table_linear);
	printf("===== quadratic probing =====\n");
	print_table(table_quadratic);
	printf("===== double probing =====\n");
	print_table(table_double);

	return 0;
}
