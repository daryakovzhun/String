#include "s21_string.h"

//  8
char* s21_strchr(const char *str, int c) {
    char *p = S21_NULL;
    int i = 0;
    while (str[i] && str[i] != c) ++i;
    if (c == str[i])
        p = (char*)(str + i);
    return p;
}
