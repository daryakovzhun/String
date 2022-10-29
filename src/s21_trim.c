#include"s21_string.h"

void *s21_trim(const char *src, const char *trim_chars) {
    char *buff = S21_NULL;
    if (src != S21_NULL) {
        if (trim_chars && *trim_chars) {
            s21_size_t n = s21_strlen(src);
            char* str = malloc(s21_strlen(src) + 1);
            for (s21_size_t i = 0; i < n; i++) {
                str[i] = src[n - i - 1];
            }
            str[n] = '\0';

            s21_size_t len_s = s21_strspn(src, trim_chars);
            s21_size_t len_e = s21_strspn(str, trim_chars);
            free(str);

            if ((n || len_s || len_e)) {
                if (len_s == n) {
                    len_s = 0;
                }
                buff = (char *) malloc(sizeof(char) * (n - len_s - len_e + 1));
                if (buff != S21_NULL) {
                    s21_strncpy(buff, src + len_s, n - len_s - len_e);
                    buff[n - len_s - len_e] = '\0';
                }
            }
        } else {
            buff = s21_trim(src, " \t\n\b\v");
        }
    }

    if (s21_strcmp(src, "") == 0) {
        buff = (char *) malloc(sizeof(char) * 1);
        buff[0] = '\0';
    }
    return buff;
}




