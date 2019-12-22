#include <stdio.h>
#include <locale.h>
#include <libintl.h>
#include "student.h"
#include "menu.h"

#ifndef __linux__
#include <windows.h>
#include <MMSystem.h>
#pragma comment(lib,"winmm.lib")
#endif


#define _(STRING) gettext(STRING)

int main()
{
    setlocale(LC_ALL, "");
    bindtextdomain("CS31106", "translate");
    textdomain("CS31106");
#ifndef __linux__
    mciSendString("open 1.wav",NULL,0,NULL);
    mciSendString("play 1.wav",NULL,0,NULL);
#endif
    student_t *student = NULL;
    unsigned int N;
    int ret;
    for (;;)
    {
        ret = loop(&student, &N);
        if(ret != 0)
        {
            printf(_("Unknown error\n"));
            return ret;
        }
    }
}