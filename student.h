#ifndef _STUDENT_H
#define _STUDENT_H
#include <wchar.h>
typedef struct STUDENT
{
    char name[40];
    short math_grade;
    short chinese_grade;
    short english_grade;
} student_t;

short get_sum_score(student_t stu);

#endif