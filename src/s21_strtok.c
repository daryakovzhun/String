#include "s21_string.h"

//  20
char *s21_strtok(char *str, const char *delim) {
    static char *end;
    int ch;
    if (str == S21_NULL) {
        str = end;
    }
    do {
        if ((ch = *str++) == '\0') {
            return S21_NULL;
        }
    } while (s21_strchr(delim, ch));
    --str;

    end = str + s21_strcspn(str, delim);
    if (*end != '\0')
    *end++ = '\0';
    return str;
}
