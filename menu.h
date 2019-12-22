#ifndef _MENU_H
#define _MENU_H

// returns 0 if loop
// returns -1 if loop ends
int loop(student_t **, int *);

// returns 0 if ok
// returns -1 if input invalid
int init(student_t **student, unsigned int *N);


void print_menu();

int program_exit(student_t *student);
int write_to_file(student_t *student, int N);
int read_from_file(student_t *student, int *N);
#endif