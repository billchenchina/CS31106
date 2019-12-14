#include <stdio.h>
#include <libintl.h>
#include <wchar.h>
#include <stdlib.h>
#include "student.h"
#include "menu.h"
#include "utils/input.h"

#define _(STRING) gettext(STRING)
void print_menu()
{
}

int init(student_t *student, unsigned int *N)
{
    printf(_("**Student Management system**\n"));
    printf(_("Create a new profile(0) or read from existing file(1)\n"));
    int selection = readint();
    if (selection == 0)
    {
        printf(_("Input the amount of student(s)\n"));
        (*N) = readuint();
        student = (student_t*) malloc((*N) * sizeof(student_t));
        for(unsigned int i = 0; i < (*N); ++i) {
            printf(_("Please input student %u's name\n"), i + 1);
            fgets(student[i].name, 40, stdin);
            printf(_("Please input the math score of student %u\n"), i + 1);
            student[i].math_grade = readuint();
            printf(_("Please input the chinese score of student %u\n"), i + 1);
            student[i].chinese_grade = readuint();
            printf(_("Please input the english score of student %u\n"), i + 1);
            student[i].english_grade = readuint();
        }
    }
    else if (selection == 1)
    {
    }
    else return -1;
    return 0;
}

int loop(student_t *student, int *N)
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
    return 0;
}