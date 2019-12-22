#include <stdio.h>
#include <stdlib.h>

#include <locale.h>
#include <libintl.h>
#include "student.h"
#include "menu.h"

#ifndef __linux__
#include <windows.h>
#include <MMSystem.h>
#pragma comment(lib,"winmm.lib")
#endif

#ifndef __linux__
#define clear() system("cls")
#else
#define clear() system("clear")
#endif

#define _(STRING) gettext(STRING)

int main()
{
    setlocale(LC_ALL, "");
    bindtextdomain("cs31106", "translate");
    textdomain("cs31106");
#ifndef __linux__
    mciSendString("open 1.wav",NULL,0,NULL);
    mciSendString("play 1.wav",NULL,0,NULL);
#endif
    student_t *student = NULL;
    int N;
    int ret;
    for (;;)
    {
        ret = loop(&student, &N);

        if(ret != 0)
        {
            printf(_("Unknown error\n"));
            return ret;
        } else {
            printf(_("Done. Please press Enter to continue...\n"));
            char s[100];
            fgets(s, 100, stdin);
            clear();
        }
    }
}