#include "student_info_system.h"

course_info *create_course(int course_id, int year, Semester semester, int credits, int grade) {
	course_info *course = (course_info *)malloc(sizeof(course_info));
	//course->prev = NULL;
	course->next = NULL;
	
	course->course_id = course_id;
	course->year = year;
	course->semester = semester;
	course->credits = credits;
	course->grade = grade;

	return course;
}

void print_grade(float grade) {
	if (grade == A_PLUS) printf("A+");
	else if (grade == A) printf("A");
	else if (grade == B_PLUS)printf("B+");
	else if (grade == B) printf("B");
	else if (grade == C_PLUS)printf("C+");
	else if (grade == C) printf("C");
	else if (grade == D_PLUS)printf("D+");
	else if (grade == D) printf("D");
	else if (grade == F) printf("F");
	else printf("??");
}

course_info *search_course_info(course_info *lst, int course_id, int year, Semester semester) {
	course_info *tmp = lst;
	while (tmp->next) {
		if (tmp->next->course_id == course_id && tmp->next->year == year && tmp->next->semester == semester)
			return tmp->next;
		tmp = tmp->next;
	}
	return NULL;
}

int num_course(course_info *lst, int year, Semester semester) {
	course_info *tmp = lst;
	int num = 0;
	while (tmp->next && tmp->next->year > year) {
		tmp = tmp->next;
	}
	if (tmp->next->year == year && tmp->next->semester == semester) {
		while (tmp->next && tmp->next->year == year && tmp->next->semester == semester) {
			num++;
			tmp = tmp->next;
		}
		return num;
	}
	return num;
}

void insert_course_info(course_info *lst, int course_id, int year, Semester semester, int credits, float grade) {
	course_info *tmp = lst;
	course_info *new_course = (course_info *)malloc(sizeof(course_info));
	//new_course->prev = NULL;
	new_course->next = NULL;
	
	new_course->course_id = course_id;
	new_course->year = year;
	new_course->semester = semester;
	new_course->credits = credits;
	new_course->grade = grade;

	while (tmp->next && tmp->next->year > new_course->year)		
		tmp = tmp->next;
	if (tmp->next && tmp->next->year == year) {
		while (tmp->next && tmp->next->semester > new_course->semester)
		tmp = tmp->next;
	}
	new_course->next = tmp->next;
	tmp->next = new_course;
}

void delete_course_info(course_info *lst, int course_id, int year, Semester semester) {
	course_info *prevNode = lst;
	course_info *curNode = lst->next;

	while (curNode){
		if (curNode->course_id == course_id && curNode->year == year && curNode->semester == semester){
			prevNode->next = curNode->next;
			free(curNode);
			curNode = prevNode->next;
		}
		prevNode = prevNode->next;
		curNode = curNode->next;
	}
}

void print_course_info(course_info *lst) {
	int n = 0;
	course_info *curNode = lst->next;
	int year = curNode->year;
	Semester semester = curNode->semester;
	printf("|	Courses\n");

	while (curNode) {
		float gpa = 0;
		int credits = 0;
		printf("|	===== %s, %d =====\n", curNode->semester == SPRING ? "Spring" : "Fall", year);
		while (curNode && curNode->year == year && curNode->semester == semester) {
			printf("|	SWE%04d (%d)	: ", curNode->course_id, curNode->credits);
			print_grade(curNode->grade);
			printf("\n");
			gpa += curNode->grade * curNode->credits;
			credits += curNode->credits;
			curNode = curNode->next;
		}
		printf("|	===== %.2f / %d =====\n", gpa/credits, credits);
		printf("|\n");
		if (!curNode)
			return;
		year = curNode->year;
		semester = curNode->semester;
	}
}