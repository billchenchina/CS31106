#include "student.h"
#include "utils/csv.h"
#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <stdlib.h>
#include <ctype.h>
#include <libintl.h>
#define _(STRING) gettext(STRING)

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

int csv_read_file(FILE *f, student_t **student, int *N)
{
    free(*student);
    *student = NULL;
    char s[1000];
    int len;
    *N = 0;
    for (;;)
    {
        char name[200];
        memset(name, 0, sizeof(name));
        int j = 0;

        char *x = fgets(s, 1000, f);
        if (x == NULL)
            return 0;
        len = strlen(s);
        int stop = 1;
        for (int i = 0; i < len; ++i)
        {
            if (s[i] == ',')
            {
                stop = 0;
                break;
            }
        }
        if (stop)
        {
            return 0;
        }
        else
        {
            (*N)++;
            (*student) = realloc((void *)(*student), sizeof(student_t) * (*N));
            if ((*student) == NULL)
            {
                printf(_("Fail to realloc.\n"));
                return -1;
            }
        }

        s[len - 1] = '\0';
        len--;
        // First: name
        // Second: math
        // Third: chinese
        // Forth: english
        int ok[4];
        memset(ok, 0, sizeof(ok));
        int escape_add = 0;
        if (s[0] == '"')
        {
            escape_add = 1;
        }
        int end;
        if (escape_add)
        {
            for (int i = len - 1; i >= 0; --i)
            {
                if (s[i] == '"')
                {
                    end = i;
                    break;
                }
            }
            for (int i = 1; i < end; ++i)
            {
                if (s[i] == '"')
                {
                    name[j] = s[i + 1];
                    i += 1;
                }
                else
                {
                    name[j] = s[i];
                }
                j++;
            }
        }
        else
        {
            int i;
            for (i = 0; i < len; ++i)
            {
                if (s[i] == ',')
                    break;
                else
                    name[i] = s[i];
            }
            end = i;
        }
        while (s[end] != ',')
            end++;
        int begin;

        end++;
        begin = end;
        while (s[end] != ',')
            end++;
        int math = 0;
        for (int i = begin; i < end; ++i)
        {
            if (isdigit(s[i]))
            {
                math = math * 10 + s[i] - '0';
            }
        }

        end++;
        begin = end;
        while (s[end] != ',')
            end++;
        int chinese = 0;
        for (int i = begin; i < end; ++i)
        {
            if (isdigit(s[i]))
            {
                chinese = chinese * 10 + s[i] - '0';
            }
        }

        end++;
        begin = end;
        while (s[end] != '\n' && s[end] != '\0')
            end++;
        int english = 0;
        for (int i = begin; i < end; ++i)
        {
            if (isdigit(s[i]))
            {
                english = english * 10 + s[i] - '0';
            }
        }
        len = strlen(name);
        for (int i = 0; i < len; ++i)
            (*student)[*N - 1].name[i] = name[i];
        (*student)[*N - 1].name[len] = '\0';
        (*student)[*N - 1].math_grade = math;
        (*student)[*N - 1].chinese_grade = chinese;
        (*student)[*N - 1].english_grade = english;
    }
}