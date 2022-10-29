#include "s21_string.h"

//  12
char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
    char* start = dest;
    for (s21_size_t i = 0; *src && i < n; i++, dest++, src++)
        *dest = *src;
    *dest = '\0';
    return start;
}
