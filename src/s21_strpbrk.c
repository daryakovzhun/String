#include "s21_string.h"

const char* s21_strpbrk(const char* s1, const char* s2) {
    const char *res = S21_NULL;
    int s1_len = s21_strlen(s1);
    int s2_len = s21_strlen(s2);

    for (int i = 0; i < s1_len; i++) {
        int was = 0;
        for (int j = 0; j < s2_len; j++) {
            if (s1[i] == s2[j]) {
                was = 1;
                break;
            }
        }
        if (was) {
            res = s1 + i;
            break;
        }
    }
    return (char *) res;
}
