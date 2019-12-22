#ifndef _MENU_H
#define _MENU_H

// returns 0 if loop
// returns -1 if loop ends
int loop(student_t **, int *);

// returns 0 if ok
// returns -1 if input invalid
int init(student_t **student, int *N);


void print_menu();

int program_exit(student_t *student);

int input_record(student_t **, int *);

int calculate_by_course(student_t *, int);
int calculate_by_student(student_t *, int);
int sort_by_grade_desc(student_t *, int);
int sort_by_grade_asc(student_t *, int);
int sort_by_id(student_t *, int);
int sort_by_name(student_t *, int);
int search_by_number(student_t *, int);
int search_by_name(student_t *, int);
int stats(student_t *, int);

int cmp_by_grade_desc(const void *, const void *);
int cmp_by_grade_asc(const void *, const void *);
int cmp_by_id(const void *, const void *);
int cmp_by_name(const void *, const void *);

int write_to_file(student_t *student, int N);
int read_from_file(student_t **student, int *N);

void list_record(student_t *student, int N);

#endif
