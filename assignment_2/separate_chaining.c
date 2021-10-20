#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
    int key;
    struct Node *next;
} Node;

typedef struct List {
    Node *head;
    int len;
} List;

int m;

int hash(int key) {
    return key % m;
}

void insert(List *table, int key) {
    int h_k = hash(key);

    Node *tmp = table[h_k].head;
    Node *newNode = (Node *)malloc(sizeof(Node));

    newNode->key = key;
    newNode->next = NULL;

    while (tmp->next)
        tmp = tmp->next;
    tmp->next = newNode;

    table[h_k].len++;
}

void print_list(Node *head){
	Node *curNode = head->next;

	while (curNode){
		printf("%d ", curNode->key);
		curNode = curNode->next;
	}
    printf("\n");
}

void print_table(List *table) {
    int shortest = m;
    int longest = 0;
    int avg = 0;
    for (int i = 0; i < m; i++){
        printf("BUCKET[%d]\n", i);
        print_list(table[i].head);
        int len = table[i].len;
        if (len < shortest)
            shortest = len;
        if (len > longest)
            longest = len;
        avg += len;
    }
    avg /= m;
    printf("The shortest length of the chains is %d\n", shortest);
    printf("The longest length of the chains is %d\n", longest);
    printf("The average length of the chains is %d\n", avg);
}

List *init_table(int m) {
    List *table = (List *)malloc(sizeof(List) * m);
    for (int i = 0; i < m; i++) {
        table[i].head = (Node *)malloc(sizeof(Node));
        table[i].len = 0;
    }
    return table;
}

int main(){
    int keys[50];

    srand(time(NULL));
    for (int i = 0; i < 50; i++) {
        keys[i] = rand()%1000;
        for (int j = 0; j < i; j++) {
            if (keys[i] == keys[j]) {
                i--;
                break;
            }
        }
    }

    // h(k) = k mod 7
    m = 7;
    printf("===== h(k) = k mod %d ===== \n", m);
    List *hash_table1 = init_table(m);

    for (int i = 0; i < 50; i++) {
        insert(hash_table1, keys[i]);
    }
    print_table(hash_table1);
    printf("\n\n");
    
    // h(k) = k mod 11
    m = 11;
    printf("===== h(k) = k mod %d ===== \n", m);
    List *hash_table2 = init_table(m);

    for (int i = 0; i < 50; i++) {
        insert(hash_table2, keys[i]);
    }
    print_table(hash_table2);
    printf("\n\n");

    // h(k) = k mod 12
    m = 12;
    printf("===== h(k) = k mod %d ===== \n", m);
    List *hash_table3 = init_table(m);

    for (int i = 0; i < 50; i++) {
        insert(hash_table3, keys[i]);
    }
    print_table(hash_table3);

    return 0;
}