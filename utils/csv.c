#include "csv.h"
#include <string.h>
#include <stdlib.h>

char *csv_escape(char *ori)
{
    int len = strlen(ori);
    int escape_add = 0;
    for (int i = 0; i < len; ++i)
    {
        if (ori[i] == '"' || ori[i] == ',')
        {
            escape_add++;
        }
    }
    char *ret = NULL;
    if(escape_add == 0) {
        ret = malloc(sizeof(char) * (len + 1));
    }
    else
    {
        
        ret = malloc(sizeof(char) * (1 // first double quote
        + len                          // length of the string
        + escape_add                   // escape double quote
        + 1                            // final double quote
        + 1));                         // '\0'
    }
    
    int j = 0;
    if(escape_add != 0) {
        ret[j] = '"';
        j++;
    }
    for (int i = 0; i < len; ++i, ++j)
    {
        if (ori[i] == '\r' || ori[i] == '\n' ||
            ori[i] == '"' || ori[i] == ',')
        {
            ret[j] = '"';
            j++;
        }
        ret[j] = ori[i];
    }
    if(escape_add != 0) {
        ret[j] = '"';
        j++;
    }
    ret[j] = '\0';
    return ret;
}
