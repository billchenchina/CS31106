#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "input.h"
#include "libintl.h"

#define _(STRING) gettext(STRING)

int readint()
{
    int ret, res = 0;
    for (;;)
    {
        int _readint(int *);
        ret = _readint(&res);
        if (ret == 0)
            break;
        else if (ret == -1)
        {
            printf(_("Input invailid. Please input again\n"));
        }
    }
    return res;
}

int _readint(int *res)
{
    char buffer[100];
    fgets(buffer, 100, stdin);
    int len = strlen(buffer);
    int front = 0, end = len;

    for (; front < end; front++)
    {
        if (!isspace(buffer[front]))
            break;
    }
    for (; front < end; end--)
    {
        if (!isspace(buffer[end - 1]))
            break;
    }
    if (front == end)
    {
        return -1;
    }

    int is_negative = 0;
    if (buffer[front] == '-')
    {
        is_negative = 1;
        front++;
    }
    for (int i = front; i < end; ++i)
    {
        if (!isdigit(buffer[i]))
            return -1;
    }
    for (int i = front; i < end; ++i)
    {
        (*res) = (*res) * 10 + (buffer[i] - '0');
    }
    return 0;
}

unsigned int readuint()
{
    unsigned int ret;
    do
    {
        ret = readint();
    } while (ret < 0);
    return ret;
}