#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 20

enum Color { RED, BLACK };

typedef struct Node {
	int key;
	enum Color color;
	struct Node *p;
	struct Node *left;
	struct Node *right;
} Node;

Node *NIL;

Node *create_node(int k) {
	Node *z = (Node *)malloc(sizeof(Node));
	z->key = k;
	z->color = RED;
	z->p = NIL;
	z->left = NIL;
	z->right = NIL;
	
	return z;
}

void left_rotate(Node **root, Node *x) {
	Node *y = x->right;
	x->right = y->left;
	if (y->left != NIL)
		y->left->p = x;
	y->p = x->p;
	if (x->p == NIL) 
		root = &y;
	else if (x == x->p->left)
		x->p->left = y;
	else
		x->p->right = y;
	y->left = x;
	x->p = y;
}

void right_rotate(Node **root, Node *x) {
	Node *y = x->left;
	x->left = y->right;
	if (y->right != NIL)
		y->right->p = x;
	y->p = x->p;
	if (x->p == NIL)
		root = &y;
	else if (x == x->p->right)
		x->p->right = y;
	else
		x->p->left = y;
	y->right = x;
	x->p = y;
}
void print_node(Node *node, int depth) {
	char color;
	if (node->color == RED)
		color = 'R';
	else
		color = 'B';

	if (node != NIL) {
		print_node(node->left, depth + 1);

		for (int i = 0; i < depth; i++)
			printf("\t");
		printf("%d [%c]\n", node->key, color);
		
		print_node(node->right, depth + 1);
	}
	else {
		for (int i = 0; i < depth; i++)
			printf("\t");
		printf("nil\n");
	}
}

void print_bst(Node **root) {
	print_node(*root, 0);
}
void rb_insert_fixup(Node **root, Node *z) {
	Node *y;

	while (z != (*root) && z->p->color == RED) {
		if (z->p == z->p->p->left) {
			y = z->p->p->right;
			if (y->color == RED) {
				z->p->color = BLACK;
				y->color = BLACK;
				z->p->p->color = RED;
				z = z->p->p;
			}
			else {
				if (z == z->p->right) {
					z = z->p;
					left_rotate(root, z);
					}
				z->p->color = BLACK;
				z->p->p->color = RED;
				right_rotate(root, z->p->p);
			}
		}
		else {
			y = z->p->p->left;
			if (y->color == RED) {
				z->p->color = BLACK;
				y->color = BLACK;
				z->p->p->color = RED;
				z = z->p->p;
			}
			else {
				if (z == z->p->left) {
					z = z->p;
					right_rotate(root, z);
				}
				z->p->color = BLACK;
				z->p->p->color = RED;
				left_rotate(root, z->p->p);
			}
		}
	}
	(*root)->color = BLACK;
}


// count
int count = 0;
void rb_insert(Node **root, int k) {
	// key가 tree에 있을때는 삽입 x
	Node *y = NIL;
	Node *x = *root;
	Node *z = create_node(k);

	while (x != NIL) {
		y = x;
		if (z->key < x->key)
			x = x->left;
		else
			x = x->right;
	}
	z->p = y;
	if (y == NIL)
	{
		*root = z;
		count++;
		printf("%d insert root %d\n",count, (*root)->key);
	}
	else if (z->key < y->key)
	{
		y->left = z;
		count++;
		printf("%d insert left(%d) %d\n",count,y->key, z->key);
	}
	else
	{
		y->right = z;
		count++;
		printf("%d insert right(%d) %d\n",count,y->key, z->key);
	}

	rb_insert_fixup(root, z);
	print_bst(root);
	printf("========================================\n");
}
/*
void print_node(Node *node, int depth) {
	char color;
	if (node->color == RED)
		color = 'R';
	else
		color = 'B';

	if (node != NIL) {
		print_node(node->left, depth + 1);

		for (int i = 0; i < depth; i++)
			printf("\t");
		printf("%d [%c]\n", node->key, color);
		
		print_node(node->right, depth + 1);
	}
	else {
		for (int i = 0; i < depth; i++)
			printf("\t");
		printf("nil\n");
	}
}

void print_bst(Node **root) {
	print_node(*root, 0);
}
*/
int main() {
	int A[SIZE];
	srand(time(NULL));
	for (int i = 0; i < SIZE; i++) {
		A[i] = rand()%60;
		for (int j = 0; j < i; j++) {
			if (A[i] == A[j]) {
				i--;
				break;
			}
		}
	}

	printf("A : ");
	for (int i = 0; i < SIZE; i++)
		printf("%d ", A[i]);
	printf("\n\n");

	Node *root = (Node *)malloc(sizeof(Node));
	NIL = (Node *)malloc(sizeof(Node));
	NIL->color = BLACK;
	root = NIL;

	for (int i = 0; i < SIZE; i++)
		rb_insert(&root, A[i]);
	
	print_bst(&root);
	return 0;
}
