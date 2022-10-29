#include"s21_string.h"

void *s21_to_upper(const char *str) {
    char *buff = malloc((s21_strlen(str) + 1) * sizeof(char));
    if (buff != S21_NULL) {
        s21_size_t count = 0;
        while (str[count] != '\0') {
            if (str[count] >= 'a' && str[count] <= 'z') {
                buff[count] = str[count] - ' ';
            } else {
                buff[count] = str[count];
            }
            count++;
        }
        buff[s21_strlen(str)] = '\0';
    }
    return buff;
}
