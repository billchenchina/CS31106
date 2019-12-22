#include <stdio.h>
#include <string.h>
#include <libintl.h>
#include <stdlib.h>

#include "student.h"
#include "menu.h"
#include "utils/input.h"

#define _(STRING) gettext(STRING)
void print_menu()
{
    printf(_("**Student Management system**\n"));
    printf(_("%d. Calculate total and average score of every course\n"), 1);
    printf(_("%d. Calculate total and average score of every student\n"), 2);
    printf(_("%d. Sort in descending order by total score of every student\n"), 3);
    printf(_("%d. Sort in ascending order by total score of every student\n"), 4);
    printf(_("%d. Sort in ascending order by number\n"), 5);
    printf(_("%d. Sort in dictionary order by name\n"), 6);
    printf(_("%d. Search by number\n"), 7);
    printf(_("%d. Search by name\n"), 8);
    printf(_("%d. Statistic analysis for every course\n"), 9);
    printf(_("%d. List record\n"), 10);
    printf(_("%d. Write to a file\n"), 11);
    printf(_("%d. Read from a file\n"), 12);
    printf(_("%d. Exit\n"), 0);
    printf(_("Please enter your choice:\n"));
    return;
}

int init(student_t **student, unsigned int *N)
{
    printf(_("**Student Management system**\n"));
    printf(_("Create a new profile(0) or read from existing file(1)\n"));
    int selection = readint();
    if (selection == 0)
    {
        printf(_("Input the amount of student(s)\n"));
        (*N) = readuint();
        (*student) = (student_t *)malloc((*N) * sizeof(student_t));
        for (unsigned int i = 0; i < (*N); ++i)
        {
            printf(_("Please input student %u's name\n"), i + 1);
            fgets((*student)[i].name, 40, stdin);
            (*student)[i].name[strlen((*student)[i].name) - 1] = '\0';
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
        if (choice < 0 || choice > 12)
        {
            printf(_("You have input a wrong choice, Choice is expected from 0 to 12\nPlease input again.\n"));
            return -1;
        }
        int ret = 0;
        switch (choice)
        {
        case 0:
            return program_exit(*student);
            break;
        // Write to a file
        case 11:
            return write_to_file(*student, *N);
            break;
            // Read from a file
            //         case 12:

            // break;
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
        return 0;
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
        printf(_("Fail to open file %s"), s);
        return -1;
    }
    return csv_write_file(f, student, N);
}

int read_from_file(student_t *student, int *N)
{
    char s[100];
    for (;;)
    {
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
            break;
        }
        printf(_("Input invalid. Please try again.\n"));
    }
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
    printf(_("Not implemented.\n"));
    FILE *f = fopen(s, "r");
}