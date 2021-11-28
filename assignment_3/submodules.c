#include "student_info_system.h"

/*
int random_value(int range) {
    srand(time(NULL));
    return rand()%range;
}
*/

// Initialize the system with random values
void init_student() {
    int enter_year, student_id, course_id, total_credits = 0;
    
    float gpa = 0;

    enter_year = 2011 + rand()%11;
    student_id = enter_year * 1000000 + 310000 + rand()%10000;

    // course information generate
    course_info *head = (course_info *)malloc(sizeof(course_info));
    int year = enter_year;
    Semester semester = SPRING;
    while (year <= 2021) {
        int course_num = rand()%8;  // the number of courses (3 ~ 7)
        if (course_num < 3)
            continue;
        for (int i = 0; i < course_num; i++) {
            int credits = rand()%3 + 1;
            int course_id = rand()%10000;
            float grade = rand()%10 / 2;
            if (grade <= 2.0)
                grade = rand()%10 / 2;
            while (grade == 0.5)
                grade = rand()%10 / 2;
            insert_course_info(head, course_id, year, semester, credits, grade);
            gpa += grade * credits;
            total_credits += credits;
        }
        if (semester == SPRING)
            semester = FALL;
        else {
            semester = SPRING;
            year++;
        }
    }

    // create student_info
    student_info *student = (student_info *)malloc(sizeof(student_info));
    student->student_id = student_id;
    student->courses_head = head;
    student->credits = total_credits;
    student->GPA = gpa / total_credits;

    // create rbnode and insert to tree
    RBNode *newNode = rb_create_node(student_id);
    newNode->student_info = student;
    rb_insert(Tree, newNode);

    print_student_info(student_id);
}

void init_system() {
    Tree = rb_create_tree();
    
    // randomly generate 100 students
    for (int i = 0; i < 100; i++) {
        init_student();
    }

}

void print_student_info(int student_id) {
    RBNode *student = rb_search(Tree->root, student_id);
    if (!student) {
        printf("There is no student (%d).\n", student_id);
        return;
    }
    printf("===== Student (%d) =====\n", student_id);
    printf("|   GPA : %f\n", student->student_info->GPA);
    printf("|   Credits (Remaining Credits) : %d(%d)\n", student->student_info->credits, 140 - student->student_info->credits);
    // courses print
    print_course_info(student->student_info->courses_head);
    printf("===== Total students : %d, GPA : %f =====\n\n", Tree->total_students, Tree->avg_GPA);
}

void insert_student_info(int student_id, int course_id, int year, Semester semester, int credits, float grade) {
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