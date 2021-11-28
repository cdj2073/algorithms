#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Grade
#define A_PLUS 4.5;
#define A 4.0;
#define B_PLUS 3.5;
#define B 3.0;
#define C_PLUS 2.5;
#define C 2.0;
#define D_PLUS 1.5;
#define D 1.0;
#define F 0;

enum Semester { SPRING, FALL };
enum Color { RED, BLACK };

// data 채워넣기
// courses - linked list
typedef struct course_info {
	struct course *prev;
	struct course *next;
	
	int course_id;       // key
	char course_code[7];
	int year;
	int semester;
	int credits;
    float grade;
} course_info;

typedef struct student_info {
    int student_id;
    float GPA;
    int credits;
    struct course_info *courses_head;
} student_info;

typedef struct RBNode {
	enum Color color;
	struct RBNode *p;
	struct RBNode *left;
	struct RBNode *right;

    // student info
    int key;
    struct student_info *student_info;
    //int student_id;
    //float total_GPA;
    //int credits;    // 취득 학점
//    int remaining_credits;   // 잔여 학점
    //struct courses *courses_head;
} RBNode;

typedef struct RBTree {
	RBNode *root;
	RBNode *nil;

    // total students
    int total_students;
    float avg_GPA;
} RBTree;

RBTree *Tree;
RBNode *NIL;

// RB Tree
RBTree *rb_create_tree();
RBNode *rb_create_node(int key);
RBNode *rb_search(RBNode *x, int key);
void rb_insert(RBTree *T, RBNode *z);
void rb_delete(RBTree *T, RBNode *z);
void rb_print_tree(RBTree *T);
void free_tree(RBNode *z);
