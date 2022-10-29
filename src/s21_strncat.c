#include"s21_string.h"

char *s21_strncat(char *dest, const char *src, size_t n) {
    int len_1 = s21_strlen(dest);
    s21_strncpy(dest + len_1, src, n);
    return dest;
}
