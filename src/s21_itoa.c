#include "s21_string.h"

static char *s21_posint(long long int n, long long int d, long long int len) {
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

static char *s21_negint(long long int n, long long int d, long long int len) {
    char *ptr;
    char *tmp;

    ptr = malloc(len + 2);
    if (!ptr)
        return (S21_NULL);
    tmp = ptr;
    *tmp = '-';
    tmp++;
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

static char *s21_subitoa(long long int n, int sign) {
    long long int d;
    long long int len;
    char *ptr;

    d = 1;
    len = 1;
    while (n / d >= 10) {
        d = d * 10;
        len++;
    }
    if (sign < 0) {
        ptr = s21_negint(n, d, len);
    } else {
        ptr = s21_posint(n, d, len);
    }
    return (ptr);
}

char *s21_itoa(long long int n) {
    char *ptr;
    int sign;

    sign = 1;
    if (n == -2147483648) {
        char *str = "-2147483648";  //  2147483648
        ptr = str;
        return (ptr);
    }
    if (n < 0) {
        n = -n;
        sign = -1;
    }
    ptr = s21_subitoa(n, sign);
    return (ptr);
}
