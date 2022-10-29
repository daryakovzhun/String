#include"s21_string.h"

size_t s21_strspn(const char *str1, const char *str2) {
    size_t i = 0, j = 0, k = 0;
    while (str1[i] != '\0') {
        while (str2[j] != '\0') {
            if (str1[i] == str2[j]) k++;
            j++;
        }
        if (k == 0) break;
        k = 0;
        j = 0;
        i++;
    }
    return i;
}
