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

typedef struct Tree {
	Node *root;
	Node *nil;
} Tree;

Node *NIL;

Tree *create_tree() {
	Tree *T = (Tree *)malloc(sizeof(Tree));
	NIL = (Node *)malloc(sizeof(Node));
	NIL->color = BLACK;
	T->nil = NIL;
	T->root = T->nil;

	return T;
}

Node *create_node(int k) {
	Node *z = (Node *)malloc(sizeof(Node));
	z->key = k;
	z->color = RED;
	z->p = NIL;
	z->left = NIL;
	z->right = NIL;
	
	return z;
}

Node *rb_search(Node *x, int k) {
    if (x == NIL || k == x->key)
        return x;
    if (k < x->key)
        return rb_search(x->left, k);
    else
        return rb_search(x->right, k);
}

void left_rotate(Tree *T, Node *x) {
	Node *y = x->right;
	x->right = y->left;
	if (y->left != T->nil)
		y->left->p = x;
	y->p = x->p;
	if (x->p == T->nil) 
		T->root = y;
	else if (x == x->p->left)
		x->p->left = y;
	else
		x->p->right = y;
	y->left = x;
	x->p = y;
}

void right_rotate(Tree *T, Node *x) {
	Node *y = x->left;
	x->left = y->right;
	if (y->right != T->nil)
		y->right->p = x;
	y->p = x->p;
	if (x->p == T->nil)
		T->root = y;
	else if (x == x->p->right)
		x->p->right = y;
	else
		x->p->left = y;
	y->right = x;
	x->p = y;
}

void rb_insert_fixup(Tree *T, Node *z) {
	while (z != T->root && z->p->color == RED) {
		if (z->p == z->p->p->left) {
			Node *y = z->p->p->right;
			if (y->color == RED) {
				z->p->color = BLACK;
				y->color = BLACK;
				z->p->p->color = RED;
				z = z->p->p;
			}
			else {
				if (z == z->p->right) {
					z = z->p;
					left_rotate(T, z);
					}
				z->p->color = BLACK;
				z->p->p->color = RED;
				right_rotate(T, z->p->p);
			}
		}
		else {
			Node *y = z->p->p->left;
			if (y->color == RED) {
				z->p->color = BLACK;
				y->color = BLACK;
				z->p->p->color = RED;
				z = z->p->p;
			}
			else {
				if (z == z->p->left) {
					z = z->p;
					right_rotate(T, z);
				}
				z->p->color = BLACK;
				z->p->p->color = RED;
				left_rotate(T, z->p->p);
			}
		}
	}
	T->root->color = BLACK;
}


void rb_insert(Tree *T, Node *z) {
    if (rb_search(T->root, z->key) != T->nil){
        printf("Key %d is already in the tree!\n", z->key);
        free(z);
        return;
    }

	Node *x = T->root;
    Node *y = T->nil;

	while (x != T->nil) {
		y = x;
		if (z->key < x->key)
			x = x->left;
		else
			x = x->right;
	}
	z->p = y;
	if (y == T->nil)
		T->root = z;
	else if (z->key < y->key)
		y->left = z;
	else
		y->right = z;

	rb_insert_fixup(T, z);
}

Node *tree_successor(Node *x) {
    if (x->right != NIL) {
        x = x->right;
        while (x->left != NIL)
            x = x->left;
        return x;
    }
    else {
        Node *y = x->p;
        while (y != NIL && x == y->right) {
            x = y;
            y = y->p;
        }
        return y;
    }
}

void rb_delete_fixup(Tree *T, Node *x) {
    while (x != T->root && x->color == BLACK) {
        if (x == x->p->left) {
            Node *w = x->p->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->p->color = RED;
                left_rotate(T, x->p);
                w = x->p->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->p;
            }
            else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    right_rotate(T, w);
                    w = x->p->right;
                }
                w->color = x->p->color;
                x->p->color = BLACK;
                w->right->color = BLACK;
                left_rotate(T, x->p);
                x = T->root;
            }
        }
        else {
            Node *w = x->p->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->p->color = RED;
                right_rotate(T, x->p);
                w = x->p->left;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->p;
            }
            else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    left_rotate(T, w);
                    w = x->p->left;
                }
                w->color = x->p->color;
                x->p->color = BLACK;
                w->left->color = BLACK;
                right_rotate(T, x->p);
                x = T->root;
            }
        }
    }
    x->color = BLACK;
}

void rb_delete(Tree *T, Node *z) {
    if (z == T->nil) {
        printf("Key %d is not in the tree!\n", z->key);
        return;
    }

    Node *x, *y;
    if (z->left == T->nil || z->right == T->nil)
        y = z;
    else
        y = tree_successor(z);
    if (y->left != T->nil) 
        x = y->left;
    else
        x = y->right;
    x->p = y->p;
    if (y->p == T->nil)
        T->root = x;
    else if (y == y->p->left)
        y->p->left = x;
    else
        y->p->right = x;
    if (y != z) {
        z->key = y->key;
        z->color = y->color;
    }
    if (y->color == BLACK)
        rb_delete_fixup(T, x);
    free(y);
}

void print_node(Node *node, int depth) {
	if (node != NIL) {
		print_node(node->right, depth + 1);

		for (int i = 0; i < depth; i++)
			printf("\t");
        char color = (node->color == RED) ? 'R' : 'B';
		printf("%d [%c]\n", node->key, color);
		
		print_node(node->left, depth + 1);
	}
	else {
		for (int i = 0; i < depth; i++)
			printf("\t");
		printf("NIL\n");
	}
}

void print_bst(Tree *T) {
	print_node(T->root, 0);
    printf("\n");
}

void free_tree(Node *z) {
	if (z != NIL) {
		free_tree(z->left);
		free_tree(z->right);
		free(z);
	}
}

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
	printf("\n");

	Tree *T = create_tree();

    // insert keys in A and print
	for (int i = 0; i < SIZE; i++)
		rb_insert(T, create_node(A[i]));
	print_bst(T);

    // insert 33, 12, 27, 41, 25
    printf("===== RB-INSERT(T, 33) =====\n");
    rb_insert(T, create_node(33));
    print_bst(T);

    printf("===== RB-INSERT(T, 12) =====\n");
    rb_insert(T, create_node(12));
    print_bst(T);

    printf("===== RB-INSERT(T, 27) =====\n");
    rb_insert(T, create_node(27));
    print_bst(T);

    printf("===== RB-INSERT(T, 41) =====\n");
    rb_insert(T, create_node(41));
    print_bst(T);

    printf("===== RB-INSERT(T, 25) =====\n");
    rb_insert(T, create_node(25));
    print_bst(T);


    // delete 41, 27, 25, 12, 33
    printf("===== RB-DELETE(T, 41) =====\n");
    rb_delete(T, rb_search(T->root, 41));
    print_bst(T);

    printf("===== RB-DELETE(T, 27) =====\n");
    rb_delete(T, rb_search(T->root, 27));
    print_bst(T);

    printf("===== RB-DELETE(T, 25) =====\n");
    rb_delete(T, rb_search(T->root, 25));
    print_bst(T);

    printf("===== RB-DELETE(T, 12) =====\n");
    rb_delete(T, rb_search(T->root, 12));
    print_bst(T);

    printf("===== RB-DELETE(T, 33) =====\n");
    rb_delete(T, rb_search(T->root, 33));
    print_bst(T);

	return 0;
}
