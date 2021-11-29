#include "student_info_system.h"

int main() {
    int input = -1;
    srand(time(NULL));
    init_system();
    printf("*** System Initialized ***\n");
    while (input != 0) {
        int id;
        printf("==================================\n");
        printf("=== Student Information System ===\n");
        
        printf("0. Exit\n");
        printf("1. Print student information\n");
        printf("2. Insert student information\n");
        printf("3. Delete student information\n");
        printf("4. Print all students (RB Tree)\n\n");
        printf("Enter the number : ");
        scanf("%d", &input);
        printf("\n");
        switch (input)
        {
        case 0:
            exit(0);
            break;
        case 1:
            // print_student_info();
            printf("Please enter the student ID : ");
            scanf("%d", &id);
            print_student_info(id);
            break;
        case 2:
            // insert_student_info();
            printf("Please enter the student ID : ");
            scanf("%d", &id);
            RBNode *student = rb_search(Tree->root, id);
            if (student != NIL) {
                if (student->student_info->credits == GRADUATION) {
                    printf("Student (%d) has already graduated.\n", id);
                    print_student_info(id);
                    break;
                }
            }

            int course_id;
            int year, credits;
            Semester semester;
            float grade;

            // get course information
            printf("Please enter the course ID (int xxxx) : ");
            scanf("%d", &course_id);
            
            printf("Please enter the year of that course : ");
            scanf("%d", &year);
            while (year > 2021 || year < id / 1000000) {
                printf("Please enter again (%d ~ %d) : ", id / 1000000, year);
                scanf("%d", &year);
            }
            printf("Please enter the semester of that course (Spring : 0, Fall : 1) : ");
            scanf("%d", (int *)&semester);
            while (semester != 0 && semester != 1) {
                printf("Please enter again (Spring : 0, Fall : 1) : ");
                scanf("%d", (int *)&semester);
            }
            if (student != NIL && search_course_info(student->student_info->courses_head, course_id, year, semester)) {
                printf("\nAlready inserted courses\n");
                print_student_info(id);
                break;
            }
            
            printf("Please enter the credits of that course (1 ~ 3) : ");
            scanf("%d", &credits);
            while (credits < 1 || credits > 3) {
                printf("Please enter again (1 ~ 3) : ");
                scanf("%d", &credits);
            }
            printf("Please enter the grade of that course\n");
            printf(" 4.5(A+)  4.0(A)  3.5(B+)  3.0(B)  2.5(C+)  2.0(C)  1.5(D+)  1.0(D)  0(F) : ");
            scanf("%f", &grade);
            while (grade != 4.5 && grade != 4.0 && grade != 3.5 && grade != 3.0 && grade != 2.5 && grade != 2.0 && grade != 1.5 && grade != 1.0 && grade != 0) {
                printf("Please enter again (4.5(A+)  4.0(A)  3.5(B+)  3.0(B)  2.5(C+)  2.0(C)  1.5(D+)  1.0(D)  0(F) : ");
                scanf("%f", &grade);
            }
            insert_student_info(id, course_id, year, semester, credits, grade);
            break;
        case 3:
            // delete_student_info();
            printf("Please enter the student ID : ");
            scanf("%d", &id);
            if (rb_search(Tree->root, id) == NIL) {
                rb_print_tree(Tree);
                printf("\nThere is no student (%d)\n", id);
                break;
            }
            int del_id;
            printf("If you want to delete student, enter 0\n");
            printf("If you want to delete course from the student, enter course ID (int xxxx)\n");
            printf("Enter the number : ");
            scanf("%d", &del_id);
            delete_student_info(id, del_id);
            break;
        case 4:
            printf("===== Total students =====\n");
            rb_print_tree(Tree);
            break;
        default:
            printf("\n!!! Wrong number! Please enter the number (0 ~ 3) !!!\n");
            break;
        }
        printf("\n\n");
    }
    free_tree(Tree->root);
    free(NIL);
    free(Tree);
    Tree = NULL;
    printf("bbbbbbbbbbbbbbbbbb\n");
}