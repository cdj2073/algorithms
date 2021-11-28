#include "student_info_system.h"

// Initialize the system with random values
void init_system() {
    Tree = rb_create_tree();

}


void print_student_info(int student_id) {
    RBNode *student = rb_search(Tree->root, student_id);
    if (!student) {
        printf("There is no student (%d). \n", student_id);
        return;
    }
    printf("===== Student (%d) =====", student_id);
    printf("|   GPA : %f", student->student_info->GPA);
    printf("|   Credits (Remaining Credits) : %d(%d)", student->student_info->credits, 140 - student->student_info->credits);
    // courses print

    printf("===== Total students : %d, GPA : %f =====", Tree->total_students, Tree->avg_GPA);
}

void insert_student_info(int student_id, char course_code[], int year, int semester, int credits, float grade) {
    RBNode *student = rb_search(Tree->root, student_id);
    if (!student) {
        student = rb_create_node(student_id);
        student->student_info = (student_info *)malloc(sizeof(student_info));
        student->student_info->student_id = student_id;
    }
    // insert course info
    // calculate gpa
    // add credits
}