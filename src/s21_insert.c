#include"s21_string.h"

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
    char *buff = S21_NULL;
    if (src != S21_NULL && str != S21_NULL && start_index <= s21_strlen(src)) {
        buff = (char *) malloc((sizeof(char) * s21_strlen(src) + s21_strlen(str) + 1));
        if (buff != S21_NULL) {
            s21_strncpy(buff, src, start_index);
            s21_strcpy(buff + start_index, str);
            s21_strcpy(buff + start_index + s21_strlen(str), src + start_index);
        }
    }
    return buff;
}
