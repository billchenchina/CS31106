#include <stdio.h>
#include <locale.h>
#include <libintl.h>
#include "student.h"
#include "menu.h"
#define _(STRING) gettext(STRING)

int main()
{
    setlocale(LC_ALL, "");
    bindtextdomain("CS31106", "translate");
    textdomain("CS31106");
    student_t *student = NULL;
    unsigned int N;
    for (;;)
    {
        if (loop(student, &N) != 0)
            break;
    }
}