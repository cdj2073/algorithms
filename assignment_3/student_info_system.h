#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define

enum Color { RED, BLACK };

typedef struct RBNode {
	enum Color color;
	struct Node *p;
	struct Node *left;
	struct Node *right;

    // student info
} RBNode;

typedef struct RBTree {
	RBNode *root;
	RBNode *nil;
} RBTree;