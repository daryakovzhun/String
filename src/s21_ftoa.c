#include"s21_string.h"

void s21_ftoa(long double n, char* str, int precission) {
    if (precission == -1) { precission = 6; }
    unsigned long int coefficient = pow(10, precission);
    long double check = roundl(n * coefficient);
    n = check / coefficient;

    char pre_res[1000], reverse[1000];
    int negative = 0, i = 0;
    if (n < 0) {
        n *= -1;
        negative = 1;
    }
    long int first = (long int)n;
    long double pre_second = (n + 1) - (long double)first + 1 / coefficient;
    long double second2 = (pre_second * coefficient);
    unsigned long int second =  roundl(second2);

    do {
        str[i] = (char)((first % 10) + '0');
        first = first / 10;
        i++;
    } while (first > 0);

    for (int j = 0; j < i; j++)
        pre_res[j] = str[i - j - 1];

    pre_res[i] = '.';
    pre_res[i + 1] = '\0';
    i = 0;

    while (second > 0) {
        str[i] = (char)((second % 10) + '0');
        second = second / 10;
        i++;
    }

    if (first == 0) {
        str[i - 1] = '\0';
    } else {
        str[i] = '\0';;
    }

    int j = 0, len = s21_strlen(str);
    for (j = 0; j < len; j++)
        reverse[j] = str[len - j - 1];
    reverse[j] = '\0';

    s21_strcat(pre_res, reverse);

    if (negative) {
        char* temp_memory = s21_insert(pre_res, "-", 0);
        s21_strcpy(str, temp_memory);
        free(temp_memory);
    } else {
        s21_strcpy(str, pre_res);
    }
}
