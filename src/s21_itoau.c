#include "s21_string.h"

static char *s21_posint(unsigned long int n, unsigned long int d, unsigned long int len) {
    char *ptr;
    char *tmp;

    ptr = malloc(len + 1);
    if (!ptr)
        return (S21_NULL);
    tmp = ptr;
    while (d >= 1) {
        char sub;
        sub = n / d + '0';
        *tmp++ = sub;
        n = n % d;
        d = d / 10;
    }
    *tmp = '\0';
    return (ptr);
}

static char *s21_subitoa(unsigned long int n) {
    unsigned long int d;
    unsigned long int len;
    char *ptr;

    d = 1;
    len = 1;
    while (n / d >= 10) {
        d = d * 10;
        len++;
    }
    ptr = s21_posint(n, d, len);

    return (ptr);
}

char *s21_itoau(unsigned long int n) {
    char *ptr;
    ptr = s21_subitoa(n);
    return (ptr);
}
