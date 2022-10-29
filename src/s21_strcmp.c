#include "s21_string.h"

//  9
int s21_strcmp(const char *str1, const char *str2) {
    for (; str1 != S21_NULL && *str1 && *str1 == *str2; str1++, str2++) {}
    return *str1 - *str2;
}
