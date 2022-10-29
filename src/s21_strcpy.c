#include "s21_string.h"

//  11
char* s21_strcpy(char *dest, const char *src) {
    char *start = dest;
    for (; *src; dest++, src++)
        *dest = *src;
    *dest = '\0';
    return start;
}
