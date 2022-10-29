#include"s21_string.h"

//  2
int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
    const unsigned char *src1 = str1, *src2 = str2;
    int res = 0;
    for (s21_size_t i = 0; i < n; i++) {
        if (src1[i] != src2[i]) {
            res = src1[i] - src2[i];
            break;
        }
    }
    return res;
}
