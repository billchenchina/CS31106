#include "student.h"
#include "utils/csv.h"
#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <stdlib.h>


short get_sum_score(student_t stu)
{
    return stu.math_grade + stu.chinese_grade + stu.english_grade;
}
int csv_write_file(FILE *f, student_t *student, int N)
{
    int ret;
    for (int i = 0; i < N; ++i)
    {
        char *escaped_data = csv_escape(student[i].name);
        ret = fprintf(f, "%s,%d,%d,%d\n", escaped_data,
                      student[i].math_grade, student[i].chinese_grade,
                      student[i].english_grade);
        if (ret < 0)
            return ret;
        free(escaped_data);
    }
    ret = fclose(f);
    return ret;
}