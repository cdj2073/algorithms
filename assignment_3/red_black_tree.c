#include "student_info_system.h"

// RB Tree functions
RBTree *rb_create_tree() {
    RBTree *T = (RBTree *)malloc(sizeof(RBTree));
    NIL = (RBNode *)malloc(sizeof(RBNode));
    NIL->color = BLACK;
    T->nil = NIL;
    T->root = T->nil;

    return T;
}

RBNode *rb_create_node(int key) {
	RBNode *z = (RBNode *)malloc(sizeof(RBNode));
	z->key = key;
	z->color = RED;
	z->p = NIL;
	z->left = NIL;
	z->right = NIL;
	
	return z;
}

RBNode *rb_search(RBNode *x, int key) {
    if (x == NIL || key == x->key)
            return x;
    if (key < x->key)
        return rb_search(x->left, key);
    else
        return rb_search(x->right, key);
}

void left_rotate(RBTree *T, RBNode *x) {
	RBNode *y = x->right;
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

void right_rotate(RBTree *T, RBNode *x) {
	RBNode *y = x->left;
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

void rb_insert_fixup(RBTree *T, RBNode *z) {
	while (z != T->root && z->p->color == RED) {
		if (z->p == z->p->p->left) {
			RBNode *y = z->p->p->right;
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
			RBNode *y = z->p->p->left;
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

void rb_insert(RBTree *T, RBNode *z) {
    if (rb_search(T->root, z->key) != T->nil){
        printf("Key %d is already in the tree!\n", z->key);
        free(z);
        return;
    }

    // for total student's gpa
    float total_gpa = T->avg_GPA * T->total_students + z->student_info->GPA;
    T->total_students++;
    T->avg_GPA = total_gpa / T->total_students;

	RBNode *x = T->root;
    RBNode *y = T->nil;

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

RBNode *tree_successor(RBNode *x) {
    if (x->right != NIL) {
        x = x->right;
        while (x->left != NIL)
            x = x->left;
        return x;
    }
    else {
        RBNode *y = x->p;
        while (y != NIL && x == y->right) {
            x = y;
            y = y->p;
        }
        return y;
    }
}

void free_rbnode(RBNode *z) {
    free(z->student_info);
    free(z);
}

void free_tree(RBNode *z) {
	if (z != NIL) {
		free_tree(z->left);
		free_tree(z->right);
		free_rbnode(z);
	}
}

void rb_delete_fixup(RBTree *T, RBNode *x) {
    while (x != T->root && x->color == BLACK) {
        if (x == x->p->left) {
            RBNode *w = x->p->right;
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
            RBNode *w = x->p->left;
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

void rb_delete(RBTree *T, RBNode *z) {
    if (z == T->nil) {
        printf("Key %d is not in the tree!\n", z->key);
        return;
    }

    RBNode *x, *y;
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

    free_rbnode(y);
}

void rb_print_node(RBNode *node, int depth) {
	if (node != NIL) {
		rb_print_node(node->right, depth + 1);

		for (int i = 0; i < depth; i++)
			printf("\t");
        char color = (node->color == RED) ? 'R' : 'B';
		printf("%d [%c]\n", node->key, color);
		
		rb_print_node(node->left, depth + 1);
	}
	else {
		for (int i = 0; i < depth; i++)
			printf("\t");
		printf("NIL\n");
	}
}

void rb_print_tree(RBTree *T) {
	rb_print_node(T->root, 0);
    printf("\n");
}