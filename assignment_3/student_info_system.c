#include "student_info_system.h"

int main() {
    int input = -1;

    while (input != 0) {
        printf("=== Student Information System ===\n");
        
        printf("0. Exit\n");
        printf("1. Print student information\n");
        printf("2. Insert student information\n");
        printf("3. Delete student information\n");
        printf("Enter the number : ");
        scanf("%d", &input);
        switch (input)
        {
        case 0:
            exit(0);
            break;
        case 1:
            // print_student_info();
            break;
        case 2:
            // insert_student_info();
            break;
        case 3:
            // delete_student_info();
            break;
        default:
            break;
        }
    }
}