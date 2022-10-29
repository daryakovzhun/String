#include"s21_string.h"

long long int s21_atoi(const char *buff) {
    char *str = s21_trim(buff, " +");
    long long int pre_result = 0, preview = 0, result = 0, zero = 1;
    int i = 0, q = 0;
    while ((str[i] >= '0' && str[i] <= '9') || (str[i] == '-' && i == 0))
        i++;
    if (str[0] == '-') {
        q = 1;
        i--;
    }
    for (int k = 1; k < i; k++)
        zero = zero * 10;
    if (q == 1)
        i++;
    for (int j = 0; j < i; j++) {
        if (str[j] >= '0' && str[j] <= '9')
            preview = ((long long int)str[j] - '0') * zero;
        pre_result += preview;
        if (str[j] != '-')
            zero /= 10;
    }
    free(str);
    if (q == 1)
        pre_result *= -1;

    if (pre_result <= 2147483647 && pre_result >= -2147483648)
        result = (long long int)pre_result;
    else if (pre_result > 2147483647)
        result = 2147483647;
    else if (pre_result < -2147483648)
        result = -2147483648;
    return result;
}
