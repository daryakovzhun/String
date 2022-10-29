#include "s21_string.h"

//  6
char* s21_strcat(char *dest, const char *src) {
    char* begin = dest;
    while (*dest)
        dest++;

    while (*src) {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
    return begin;
}
