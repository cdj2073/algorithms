#include "student_info_system.h"

float get_random_grade() {
    float grade = rand()%10 / 2.0;
    if (grade <= 2.5)
        grade = rand()%10 / 2.0;
    while (grade == 0.5)
        grade = rand()%10 / 2.0;
    return grade;
}

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
        if (course_num < 3) {
            if (semester == SPRING)
                semester = FALL;
            else {
                semester = SPRING;
                year++;
            }
            continue;
        }
        
        // for check duplicate course id (per semester)
        int *courses_id = (int *)malloc(sizeof(int) * course_num);
        for (int i = 0; i < course_num; i++) {
            if (total_credits == GRADUATION)
                break;
            courses_id[i] = rand()%9999 + 1;
            for (int j = 0; j < i; j++) {
                if (courses_id[j] == courses_id[i]) {
                    i--;
                    break;
                }
            }
            
            int credits = rand()%5 + 1;
            if (credits > 3)
                credits = 3;
            if (total_credits > GRADUATION - 3)
                credits = GRADUATION - total_credits;
            float grade = get_random_grade();
            insert_course_info(head, courses_id[i], year, semester, credits, grade);
            gpa += grade * credits;
            total_credits += credits;
        }
        free(courses_id);
        /*
        if (semester == SPRING)
            semester = FALL;
        else {
            semester = SPRING;
            year++;
        }
        */
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
    
    int students_id[150];
    int dup = 0, i = 0;
    // randomly generate 100 students
    for (i = 0; i < 100; i++) {
        int enter_year = 2012 + rand()%10; // 2012 ~ 2021
        if (enter_year < 2018)
            enter_year += rand()%5;
        students_id[i] = enter_year * 1000000 + 310000 + rand()%10000;
        for (int j = 0; j < i; j++) {
            if (students_id[i] == students_id[j]) { // duplicate student id
                i--;
                dup = 1;
                break;
            }
        }
        if (dup)
            dup = 0;
        else
            init_student(students_id[i]);
    }
    // initial condition : avg credit hours (70 +- 5)
    while (Tree->avg_credits > 75) {
        students_id[i] = 2021310000 + rand()%10000;
        for (int j = 0; j < i; j++) {
            if (students_id[i] == students_id[j]) {
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
    printf("|   GPA : %.2f\n", student->student_info->GPA);
    printf("|   Credits (Remaining Credits) : %d(%d)\n", student->student_info->credits, 140 - student->student_info->credits);
    printf("|\n");
    // courses print
    print_course_info(student->student_info->courses_head);
    printf("===== Total students : %d, GPA : %.2f, avg credits : %.2f =====\n\n", Tree->total_students, Tree->avg_GPA, Tree->avg_credits);
}

void insert_student_info(int student_id, int course_id, int year, Semester semester, int credits, float grade) {
    RBNode *student = rb_search(Tree->root, student_id);
    if (student == NIL) {
        student = rb_create_node(student_id);
        student->student_info = (student_info *)malloc(sizeof(student_info));
        student->student_info->student_id = student_id;
        student->student_info->GPA = 0;
        student->student_info->credits = 0;
        student->student_info->courses_head = (course_info *)malloc(sizeof(course_info));
    }
    // insert course info
    insert_course_info(student->student_info->courses_head, course_id, year, semester, credits, grade);
    // calculate gpa and credits
    float student_gpa = student->student_info->GPA * student->student_info->credits;
    int student_credits = student->student_info->credits;
    student_credits += credits;
    student_gpa += grade * credits;
    student_gpa /= credits;
    student->student_info->GPA = student_gpa;
    student->student_info->credits = student_credits;
    
    rb_insert(Tree, student);
    print_student_info(student_id);
}

void delete_student_info(int student_id, int course_id, int year, Semester semester) {
    if (course_id == 0) {
        printf("Delete student (%d)\n", student_id);
        print_student_info(student_id);
        rb_delete(Tree, rb_search(Tree->root, student_id));
        return;
    }
    student_info *student = rb_search(Tree->root, student_id)->student_info;
    course_info *course = search_course_info(student->courses_head, course_id, year, semester);
    if (!course) {
        printf("Student (%d) doesn't take the course (SWE%d)\n", student_id, course_id);
        print_student_info(student_id);
    }
    else {
        delete_course_info(student->courses_head, course_id, year, semester);
        printf("Delete course SWE%d\n", course_id);
        print_student_info(student_id);
    }
}