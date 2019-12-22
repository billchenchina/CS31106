#include <stdio.h>
#include <string.h>
#include <libintl.h>
#include <stdlib.h>

#include "student.h"
#include "menu.h"
#include "utils/input.h"

#ifndef __linux__
#define clear() system("cls")
#else
#define clear() system("clear")
#endif

#define _(STRING) gettext(STRING)
void print_menu()
{
    printf(_(" =====================Student Grade Management System V6.0==========================\n"));
    printf(_(" |              %d.Input record                                                     |\n"), 1);
    printf(_(" |              %d.Calculate total and average score of every course                |\n"), 2);
    printf(_(" |              %d.Calculate total and average score of every student               |\n"), 3);
    printf(_(" |              %d.Sort in descending order by total score of every student         |\n"), 4);
    printf(_(" |              %d.Sort in ascending order by total score of every student          |\n"), 5);
    printf(_(" |              %d.Sort in ascending order by number                                |\n"), 6);
    printf(_(" |              %d.Sort in dictionary order by name                                 |\n"), 7);
    printf(_(" |              %d.Search by number                                                 |\n"), 8);
    printf(_(" |              %d.Search by name                                                   |\n"), 9);
    printf(_(" |              %d.Statistic analysis for every course                             |\n"), 10);
    printf(_(" |              %d.List record                                                     |\n"), 11);
    printf(_(" |              %d.Write to a file                                                 |\n"), 12);
    printf(_(" |              %d.Read from a file                                                |\n"), 13);
    printf(_(" |              %d.Exit                                                             |\n"), 0);
    printf(_(" ==========================  Please enter a number   ===============================\n"));
    return;
}

int init(student_t **student, int *N)
{
    printf(_("**Student Management system**\n"));
    printf(_("Create a new profile(0) or read from existing file(1)\n"));
    if (*student)
    {
        free(*student);
        *student = NULL;
    }
    int selection = readint();
    clear();
    if (selection == 0)
    {
        printf(_("Input the amount of student(s)\n"));
        (*N) = readuint();
        (*student) = (student_t *)malloc((*N) * sizeof(student_t));
        if(*student == NULL) {
            return -1;
        }
        for (int i = 0; i < (*N); ++i)
        {
            printf(_("Please input student %u's name\n"), i + 1);
            fgets((*student)[i].name, 40, stdin);
            (*student)[i].name[strlen((*student)[i].name) - 1] = '\0';
            printf(_("Please input student %u's id\n"), i + 1);
            (*student)[i].id = readuint();
            printf(_("Please input the math score of student %u\n"), i + 1);
            (*student)[i].math_grade = readuint();
            printf(_("Please input the chinese score of student %u\n"), i + 1);
            (*student)[i].chinese_grade = readuint();
            printf(_("Please input the english score of student %u\n"), i + 1);
            (*student)[i].english_grade = readuint();
        }
        printf(_("Initialize complete.\n"));
    }
    else if (selection == 1)
    {
        read_from_file(student, N);
    }
    else
        return -1;
    return 0;
}

int loop(student_t **student, int *N)
{
    static int inited = 0;
    if (inited == 0)
    {
        int ret;
        do
        {
            ret = init(student, N);
        } while (ret != 0);

        inited = 1;
    }
    else
    {
        print_menu();
        int choice = readint();
        if (choice < 0 || choice > 13)
        {
            printf(_("You have input a wrong choice, Choice is expected from 0 to 12\nPlease input again.\n"));
            return -1;
        }
        clear();

        switch (choice)
        {
        case 0:
            return program_exit(*student);
        // Input record
        case 1:
            return input_record(student, N);
        case 2:
            return calculate_by_course(*student, *N);
        case 3:
            return calculate_by_student(*student, *N);
        case 4:
            return sort_by_grade_desc(*student, *N);
            break;
        case 5:
            return sort_by_grade_asc(*student, *N);
            break;
        case 6:
            return sort_by_id(*student, *N);
        case 7:
            return sort_by_name(*student, *N);
        case 8:
            return search_by_number(*student, *N);
        case 9:
            return search_by_name(*student, *N);
        case 10:
            return stats(*student, *N);
        case 11:
            list_record(*student, *N);
            break;
        // Write to a file
        case 12:
            return write_to_file(*student, *N);
            break;
            // Read from a file
        case 13:
        {
            char s[100];
            printf(_("Doing so will clear all current data, confirm to proceed?(y/N)\n"));
            fgets(s, 100, stdin);
            int len = strlen(s);
            if (s[len - 1] == '\n')
            {
                s[len - 1] = '\0';
                len--;
            }
            if (len == 1 && (s[0] == 'y' || s[0] == 'Y'))
            {
                return read_from_file(student, N);
                break;
            }
        }
        break;
        default:
            printf(_("Not implemented.\n"));
            break;
        }
    }
    return 0;
}

int program_exit(student_t *student)
{

    printf(_("Sure to exit?(Press Y to confirm exit.)\n"));
    char s[200];
    fgets(s, 200, stdin);
    if (s[0] == 'Y' || s[0] == 'y')
    {
        printf(_("Cleaning up memory...\n"));
        if (student != NULL)
            free(student);
        printf(_("Exiting!\n"));
        exit(EXIT_SUCCESS);
    }
    else
    {
        printf(_("Not exiting.\n"));
        return 0;
    }
}

int write_to_file(student_t *student, int N)
{
    char s[100];
    for (;;)
    {
        printf(_("Please input a location to save.\nThe file name should ends with .csv:\n"));
        fgets(s, 100, stdin);
        int len = strlen(s);
        if (s[len - 1] == '\n')
        {
            s[len - 1] = '\0';
            len--;
        }
        if (len < 4 || s[len - 4] != '.' || s[len - 3] != 'c' ||
            s[len - 2] != 's' || s[len - 1] != 'v')
        {
            printf(_("Input invalid. Please try again.\n"));
            continue;
        }
        break;
    }
    FILE *f = fopen(s, "w");
    if (f == NULL)
    {
        printf(_("Fail to open file %s\n"), s);
        return -1;
    }
    return csv_write_file(f, student, N);
}

int read_from_file(student_t **student, int *N)
{
    char s[100];
    for (;;)
    {
        printf(_("Please input a location to your file.\nThe file name should ends with .csv:\n"));
        fgets(s, 100, stdin);
        int len = strlen(s);
        if (s[len - 1] == '\n')
        {
            s[len - 1] = '\0';
            len--;
        }
        if (len < 4 || s[len - 4] != '.' || s[len - 3] != 'c' ||
            s[len - 2] != 's' || s[len - 1] != 'v')
        {
            printf(_("Input invalid. Please try again.\n"));
            continue;
        }
        break;
    }
    clear();
    FILE *f = fopen(s, "r");
    if (f == NULL)
    {
        printf(_("Couldn't open file %s\n"), s);
        return -1;
    }
    return csv_read_file(f, student, N);
}

void list_record(student_t *student, int N)
{
    for (int i = 0; i < N; ++i)
    {
        printf(_("Student %d: %s\n"), student[i].id, student[i].name);
        printf(_("Math: %d\tChinese: %d\tEnglish: %d\t\n"),
               student[i].math_grade,
               student[i].chinese_grade,
               student[i].english_grade);
    }
    return;
}

int input_record(student_t **student, int *N)
{
    return init(student, N);
}
int calculate_by_course(student_t *student, int N)
{
    int total_math = 0;
    int total_chinese = 0;
    int total_english = 0;
    for (int i = 0; i < N; ++i)
    {
        total_math += student[i].math_grade;
        total_chinese += student[i].chinese_grade;
        total_english += student[i].english_grade;
    }
    printf(_("\tMath\tChinese\tEnglish\n"));
    printf(_("Total\t%d\t%d\t%d\n"),
           total_math,
           total_chinese,
           total_english);
    printf(_("Average\t%.1f\t%.1f\t%.1f\n"),
           1.0 * total_math / N,
           1.0 * total_chinese / N,
           1.0 * total_english / N);
    return 0;
}
int calculate_by_student(student_t *student, int N)
{
    printf(_("Name\t\tAverage\tTotal\n"));
    for (int i = 0; i < N; ++i)
    {
        printf(_("%s\t\t%.1f\t%d\n"),
               student[i].name,
               1.0 * (student[i].math_grade + student[i].chinese_grade + student[i].english_grade) / 3,
               student[i].math_grade + student[i].chinese_grade + student[i].english_grade);
    }
    return 0;
}

int sort_by_grade_desc(student_t *student, int N)
{
    qsort(student, N, sizeof(student_t), cmp_by_grade_desc);
    list_record(student, N);
    return 0;
}

int sort_by_grade_asc(student_t *student, int N)
{
    qsort(student, N, sizeof(student_t), cmp_by_grade_desc);
    list_record(student, N);
    return 0;
}
int sort_by_id(student_t *student, int N)
{
    qsort(student, N, sizeof(student_t), cmp_by_id);
    list_record(student, N);
    return 0;
}

int sort_by_name(student_t *student, int N)
{
    qsort(student, N, sizeof(student_t), cmp_by_name);
    list_record(student, N);
    return 0;
}
int cmp_by_grade_desc(const void *s1, const void *s2)
{
    student_t *a1 = (student_t *)s1;
    student_t *a2 = (student_t *)s2;
    return a1->math_grade + a1->chinese_grade + a1->english_grade -
           a2->math_grade + a2->chinese_grade + a2->english_grade;
}
int cmp_by_grade_asc(const void *s1, const void *s2)
{
    student_t *a1 = (student_t *)s1;
    student_t *a2 = (student_t *)s2;
    return a2->math_grade + a2->chinese_grade + a2->english_grade -
           a1->math_grade + a1->chinese_grade + a1->english_grade;
}
int cmp_by_id(const void *s1, const void *s2)
{
    student_t *a1 = (student_t *)s1;
    student_t *a2 = (student_t *)s2;
    return a1->id - a2->id;
}
int cmp_by_name(const void *s1, const void *s2)
{
    student_t *a1 = (student_t *)s1;
    student_t *a2 = (student_t *)s2;
    return strcmp(a1->name, a2->name);
}
int search_by_number(student_t *student, int N)
{
    printf(_("Please input the student's number:\n"));
    int id;
    id = readuint();
    sort_by_grade_asc(student, N);
    for (int i = 0; i < N; ++i)
    {
        if (student[i].id == id)
        {
            printf(_("Student %s's rank is %d\n"),
                   student[i].name, i + 1);
            printf(_("\tMath: %d\n\tChinese: %d\n\tEnglish: %d\n"),
                   student[i].math_grade,
                   student[i].chinese_grade,
                   student[i].english_grade);
            printf(_("Total: %d\n"),
                   student[i].math_grade +
                       student[i].chinese_grade +
                       student[i].english_grade);
            return 0;
        }
    }
    printf(_("Couldn't find student %d"), id);
    return 0;
}
int search_by_name(student_t *student, int N)
{
    printf(_("Please input the student's name(support fuzzy search):\n"));
    char name[100];
    fgets(name, 100, stdin);
    int len = strlen(name);
    if (name[len - 1] == '\n')
    {
        name[len - 1] = '\0';
        len--;
    }
    sort_by_grade_asc(student, N);
    for (int i = 0; i < N; ++i)
    {
        if (strcmp(name, student[i].name) == 0)
        {
            printf(_("Student %s's rank is %d\n"),
                   student[i].name, i + 1);
            printf(_("\tMath: %d\n\tChinese: %d\n\tEnglish: %d\n"),
                   student[i].math_grade,
                   student[i].chinese_grade,
                   student[i].english_grade);
            printf(_("Total: %d\n"),
                   student[i].math_grade +
                       student[i].chinese_grade +
                       student[i].english_grade);
            return 0;
        }
    }
    for (int i = 0; i < N; ++i)
    {
        if (strstr(student[i].name, name) != NULL || strstr(name, student[i].name) != NULL)
        {
            printf(_("We couldn't find the exact student.\nMaybe you want %s\n"), student[i].name);
            printf(_("Student %s's rank is %d\n"),
                   student[i].name, i + 1);
            printf(_("\tMath: %d\n\tChinese: %d\n\tEnglish: %d\n"),
                   student[i].math_grade,
                   student[i].chinese_grade,
                   student[i].english_grade);
            printf(_("Total: %d\n"),
                   student[i].math_grade +
                       student[i].chinese_grade +
                       student[i].english_grade);
            return 0;
        }
    }
    printf(_("Couldn't find student %s"), name);
    return 0;
}
int stats(student_t *student, int N)
{
    {
        int a = 0, b = 0, c = 0, d = 0, f = 0;
        for (int i = 0; i < N; ++i)
        {
            if (90 <= student[i].math_grade &&
                student[i].math_grade <= 100)
                a++;
            else if (80 <= student[i].math_grade &&
                     student[i].math_grade <= 89)
                b++;
            else if (70 <= student[i].math_grade &&
                     student[i].math_grade <= 79)
                c++;
            else if (60 <= student[i].math_grade &&
                     student[i].math_grade <= 69)
                d++;
            else
                f++;
        }
        printf(_("Statistics for Math:\n"));
        if (a)
            printf(_("A(90-100): %d\t%f%%\n"), a, 100.0 * a / N);
        if (b)
            printf(_("B(80-89): %d\t%f%%\n"), b, 100.0 * b / N);
        if (c)
            printf(_("C(70-79): %d\t%f%%\n"), c, 100.0 * c / N);
        if (d)
            printf(_("D(60-69): %d\t%f%%\n"), d, 100.0 * d / N);
        if (f)
            printf(_("F(0-59): %d\t%f%%\n"), f, 100.0 * f / N);
    }
    {
        int a = 0, b = 0, c = 0, d = 0, f = 0;
        for (int i = 0; i < N; ++i)
        {
            if (90 <= student[i].chinese_grade &&
                student[i].chinese_grade <= 100)
                a++;
            else if (80 <= student[i].chinese_grade &&
                     student[i].chinese_grade <= 89)
                b++;
            else if (70 <= student[i].chinese_grade &&
                     student[i].chinese_grade <= 79)
                c++;
            else if (60 <= student[i].chinese_grade &&
                     student[i].chinese_grade <= 69)
                d++;
            else
                f++;
        }
        printf(_("Statistics for Chinese:\n"));
        if (a)
            printf(_("A(90-100): %d\t%f%%\n"), a, 100.0 * a / N);
        if (b)
            printf(_("B(80-89): %d\t%f%%\n"), b, 100.0 * b / N);
        if (c)
            printf(_("C(70-79): %d\t%f%%\n"), c, 100.0 * c / N);
        if (d)
            printf(_("D(60-69): %d\t%f%%\n"), d, 100.0 * d / N);
        if (f)
            printf(_("F(0-59): %d\t%f%%\n"), f, 100.0 * f / N);
    }

    {
        int a = 0, b = 0, c = 0, d = 0, f = 0;
        for (int i = 0; i < N; ++i)
        {
            if (90 <= student[i].english_grade &&
                student[i].english_grade <= 100)
                a++;
            else if (80 <= student[i].english_grade &&
                     student[i].english_grade <= 89)
                b++;
            else if (70 <= student[i].english_grade &&
                     student[i].english_grade <= 79)
                c++;
            else if (60 <= student[i].english_grade &&
                     student[i].english_grade <= 69)
                d++;
            else
                f++;
        }
        printf(_("Statistics for English:\n"));
        if (a)
            printf(_("A(90-100): %d\t%f%%\n"), a, 100.0 * a / N);
        if (b)
            printf(_("B(80-89): %d\t%f%%\n"), b, 100.0 * b / N);
        if (c)
            printf(_("C(70-79): %d\t%f%%\n"), c, 100.0 * c / N);
        if (d)
            printf(_("D(60-69): %d\t%f%%\n"), d, 100.0 * d / N);
        if (f)
            printf(_("F(0-59): %d\t%f%%\n"), f, 100.0 * f / N);
    }

    return 0;
}