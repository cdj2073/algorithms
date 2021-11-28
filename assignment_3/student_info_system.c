#include "student_info_system.h"

int main() {
    int input = -1;
    srand(time(NULL));
    init_system();

    while (input != 0) {
        int id;
        printf("=== Student Information System ===\n");
        
        printf("0. Exit\n");
        printf("1. Print student information\n");
        printf("2. Insert student information\n");
        printf("3. Delete student information\n");
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
            char course_code[7];
            int year, semester, credits;
            float grade;
            printf("Please enter the course code");
            break;
        case 3:
            // delete_student_info();
            break;
        default:
            printf("\n!!! Wrong number! Please enter the number (0 ~ 3) !!!\n");
            break;
        }
    }
}