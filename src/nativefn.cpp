#include <stdarg.h>
#include <stdio.h>
#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <string.h>

extern "C"
{
    void print(char* str, ...)
    {
        va_list args;
        va_start(args, str);
        vprintf(str, args);
        va_end(args);
    }

    void println(char* str, ...)
    {
        char* aux_str;
        va_list args;
        va_start(args, str);
        aux_str = (char*) malloc(strlen(str)+2);
        strcpy(aux_str, str);
        strcat(aux_str, "\n");
        vprintf(aux_str, args);
        va_end(args);
    }

}
