#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Grade
#define A_PLUS 4.5
#define A 4.0
#define B_PLUS 3.5
#define B 3.0
#define C_PLUS 2.5
#define C 2.0
#define D_PLUS 1.5
#define D 1.0
#define F 0

#define GRADUATION 140

typedef enum Semester { SPRING, FALL }Semester;
typedef enum Color { RED, BLACK } Color;

// courses - linked list
typedef struct course_info {
	struct course_info *next;
	
	int course_id;
	int year;
	Semester semester;
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

    int key;
    struct student_info *student_info;
} RBNode;

typedef struct RBTree {
	RBNode *root;
	RBNode *nil;

    // total students
    int total_students;
    float avg_GPA;
    float avg_credits;
} RBTree;

RBTree *Tree;
RBNode *NIL;

void init_system();
void print_student_info(int student_id);
void insert_student_info(int student_id, int course_id, int year, Semester semester, int credits, float grade);
void delete_student_info(int student_id, int course_id, int year, Semester semester);

// courses
course_info *search_course_info(course_info *lst, int course_id, int year, Semester semester);
void insert_course_info(course_info *lst, int course_id, int year, Semester semester, int credits, float grade);
void delete_course_info(course_info *lst, int course_id, int year, Semester semester);
void print_course_info(course_info *lst);
int num_course(course_info *lst, int year, Semester semester);

// RB Tree
RBTree *rb_create_tree();
RBNode *rb_create_node(int key);
RBNode *rb_search(RBNode *x, int key);
void rb_insert(RBTree *T, RBNode *z);
void rb_delete(RBTree *T, RBNode *z);
void rb_print_tree(RBTree *T);
void rb_free_node(RBNode *z);
void free_tree(RBNode *z);
