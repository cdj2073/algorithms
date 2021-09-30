#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100

typedef struct Node{
	int data;
	struct Node *next;
} Node;

int list_len;

void insert(Node *lst, int x){
	Node *tmp = lst;
	Node *newNode = (Node *)malloc(sizeof(Node));

	newNode->data = x;
	newNode->next = NULL;
	list_len++;

	while (tmp->next)
		tmp = tmp->next;
	tmp->next = newNode;
}

void delete(Node *lst, int x){
	int i = 0;
	Node *prevNode = lst;
	Node *curNode = lst->next;

	while (i < list_len && curNode){
		if (curNode->data == x){
			prevNode->next = curNode->next;
			free(curNode);
			curNode = prevNode->next;
			list_len--;
		}
		prevNode = prevNode->next;
		curNode = curNode->next;
		i++;
	}
}

void print(Node *lst){
	int n = 0;
	Node *curNode = lst->next;

	while (curNode){
		printf("%d ", curNode->data);
		curNode = curNode->next;
		if (n == list_len / 2)
			printf("\n");
		n++;
	}
	printf("\n\n");
}

int main(){
	int arr[SIZE];

	// fill int array randomly
	srand(time(NULL));
	for (int i = 0; i < SIZE; i++)
		arr[i] = rand()%SIZE;

	// construct the linked list
	Node *head = (Node *)malloc(sizeof(Node));
	for (int i = 0; i < SIZE; i++)
		insert(head, arr[i]);

	// randomly select an integer and delete
	int randNum = arr[rand()%100];
	printf("randomly chosen number : %d\n\n", randNum);
	printf("before deletion\n");
	print(head);
	delete(head, randNum);
	printf("after deletion\n");
	print(head);
	
	printf("=========================\n");
	// repeat two more times
	randNum = arr[rand()%100];
	printf("randomly chosen number : %d\n\n", randNum);
	printf("before deletion\n");
	print(head);
	delete(head, randNum);
	printf("after deletion\n");
	print(head);

	printf("=========================\n");
	randNum = arr[rand()%100];
	printf("randomly chosen number : %d\n\n", randNum);
	printf("before deletion\n");
	print(head);
	delete(head, randNum);
	printf("after deletion\n");
	print(head);
}
