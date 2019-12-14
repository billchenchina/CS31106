#include "student.h"

short get_sum_score(student_t stu)
{
    return stu.math_grade + stu.chinese_grade + stu.english_grade;
}