#include "student_info_system.h"

// Initialize the system with random values
void init_student(int student_id) {
    int enter_year, course_id, total_credits = 0;
    float gpa = 0;

    enter_year = student_id / 1000000;

    // course information generate
    course_info *head = (course_info *)malloc(sizeof(course_info));
    int year = enter_year;
    Semester semester = SPRING;
    while (year <= 2021) {
        int course_num = rand()%8;  // the number of courses (3 ~ 7)
        if (course_num < 3)
            continue;
        
        // for check duplicate course id (per semester)
        int *courses_id = (int *)malloc(sizeof(int) * course_num);
        for (int i = 0; i < course_num; i++) {
            courses_id[i] = rand()%10000;
            for (int j = 0; j < i; j++) {
                if (courses_id[j] == courses_id[i]) {
                    i--;
                    break;
                }
            }
            
            int credits = rand()%3 + 1;
            float grade = rand()%10 / 2;
            if (grade <= 2.0)
                grade = rand()%10 / 2;
            while (grade == 0.5)
                grade = rand()%10 / 2;
            insert_course_info(head, courses_id[i], year, semester, credits, grade);
            gpa += grade * credits;
            total_credits += credits;
        }
        free(courses_id);
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
    
    int students_id[100];
    // randomly generate 100 students
    for (int i = 0; i < 100; i++) {
        int enter_year = 2011 + rand()%11; // 2011 ~ 2021
        students_id[i] = enter_year * 1000000 + 310000 + rand()%10000;
        for (int j = 0; j < i; j++) {
            if (students_id[i] == students_id[j]) { // duplicate student id
                i--;
                break;
            }
        }
        init_student(students_id[i]);
    }
}

void print_student_info(int student_id) {
    RBNode *student = rb_search(Tree->root, student_id);
    if (student == Tree->nil) {
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

void delete_student_info() {

}