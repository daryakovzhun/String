#include "s21_string.h"

void remove_zeros_in_precission(char* copy_str_flag, char* str_flag) {
    int i = 0;  //  убираем 0 если есть перед числом в точности например .005d
    while (str_flag[i] && (str_flag[i] == '.' || str_flag[i] == '0')) {
        i++;
    }

    s21_size_t j;
    for (j = i; j < s21_strlen(str_flag); j++) {
        copy_str_flag[j - i] = str_flag[j];
    }
    copy_str_flag[j - i] = '\0';
}

char* func_spec(char* str_flag, command *flags) {
    if (str_flag[0] == '.') {
        char* copy_str_flag = malloc(s21_strlen(str_flag));
        remove_zeros_in_precission(copy_str_flag, str_flag);

        if (s21_strcmp(copy_str_flag, "*") == 0) {
            flags->precission = -2;
        } else {
            flags->precission = s21_atoi(copy_str_flag);   // 0.00005
        }
        free(copy_str_flag);
    } else {
        char *before_del = s21_strtok(str_flag, ".");
        if (before_del != S21_NULL) {
            if (s21_strcmp(before_del, "*") == 0) {
                flags->width = -2;
            } else if (s21_strcmp(before_del, "0") == 0) {
                flags->zero = '0';
            } else {
                if (before_del[0] == '0') {
                    flags->zero = '0';
                }
                if (before_del[1] == '*') {  // before_del[1] && before_del[1] == '*'
                    flags->width = -2;
                } else {
                    flags->width = s21_atoi(before_del);
                }
            }
            char *after_del = s21_strtok(S21_NULL, ".");
            if (after_del) {
                if (s21_strcmp(after_del, "*") == 0) {
                    flags->precission = -2;
                } else {
                    flags->precission = s21_atoi(after_del);
                }
            }
        }
    }
    return str_flag;
}

char define_struct(char f_next, command* flags, const char **format) {
    char str_flag[1000];
    int k = 0;
    while (s21_strchr("cdifsugGeExXonp%", f_next) == S21_NULL) {
        if (f_next == '-') {
            flags->minus = f_next;
            f_next = *((*format)++);
            continue;
        } else if (f_next == '+') {
            flags->plus = f_next;
            f_next = *((*format)++);
            continue;
        } else if (f_next == ' ') {
            flags->space = f_next;
            f_next = *((*format)++);
            continue;
        } else if (f_next == 'l' || f_next == 'h' || f_next == 'L') {
            flags->lenght = f_next;
            f_next = *((*format)++);
            continue;
        }
        str_flag[k] = f_next;
        k++;
        f_next = *((*format)++);
    }
    str_flag[k] = '\0';

    func_spec(str_flag, flags);

    // str_flag[0] = '\0';   // !!!!!!

    return f_next;
}

void to_hex(long long int d, char* temp, char simbol) {
    char temp_res[10000];
    int i = 0;
    char remainder;

    if (d == 0) {
        temp_res[i] = '0';
        i++;
    }

    while (d > 0) {
        if (d % 16 < 10) {
            remainder = (d % 16) + '0';
        } else {
            remainder = d % 16 % 10  + simbol;
        }
        temp_res[i] = remainder;
        d /= 16;
        i++;
    }

    temp_res[i] = '\0';

    int k = 0;
    for (int j = s21_strlen(temp_res) - 1; j >= 0 ; j--, k++) {
        temp[k] = temp_res[j];
    }
    temp[k] = '\0';
}

void to_octal(long long int d, char* temp) {
    char temp_res[10000];
    int i = 0;

    if (d == 0) {
        temp_res[i] = '0';
        i++;
    }
    while (d > 0) {
        temp_res[i] = (d % 8) + '0';
        d /= 8;
        i++;
    }
    temp_res[i] = '\0';

    int k = 0;
    for (int j = s21_strlen(temp_res) - 1; j >= 0 ; j--, k++) {
        temp[k] = temp_res[j];
    }
    temp[k] = '\0';
}

void add_simbol(char* temp_result, char* simbol, int position) {
    char* temp_memory;
    temp_memory = s21_insert(temp_result, simbol, position);
    s21_strcpy(temp_result, temp_memory);
    free(temp_memory);
}

void spec_e(char* temp, double number, char* str_for_exp) {
    char *str = S21_NULL;
    //  number = round(number * pow(10,6))/pow(10,6);
    long long int exp;
    if ((int) number == 0 && (int)log10(fabs(number)) != log10(fabs(number))) {
        exp = (log10(fabs(number))) - 1;
    } else {
        exp = (log10(fabs(number)));
    }
    double res = pow(10, exp) * round(number / pow(10, exp) * pow(10, 6)) / pow(10, 6);
    if ((int) res == 0 && (int)log10(fabs(number)) != log10(fabs(number))) {
        exp = (log10(fabs(res))) - 1;
    } else {
        exp = (log10(fabs(res)));
    }

    res /= pow(10, exp);
    s21_strcat(str_for_exp, s21_itoa(exp));

    if (s21_strlen(str_for_exp) == 3 && str_for_exp[1] == '-') {
        str = s21_insert(str_for_exp, "0", 2);
    } else if (s21_strlen(str_for_exp) == 2) {
        str = s21_insert(str_for_exp, "+0", 1);
    }
    s21_ftoa(res, temp, 1);
    s21_strcat(temp, str);
    free(str);
}

void check_x_X_o(char f_next, char* temp, unsigned long int  d) {
    if (f_next == 'x') {
        to_hex(d, temp, 'a');
    } else if (f_next == 'X') {
        to_hex(d, temp, 'A');
    } else if (f_next == 'o') {
        to_octal(d, temp);
    } else if (f_next == 'u') {
        char *temp_memory;
        temp_memory = s21_itoau(d);
        s21_strcpy(temp, temp_memory);
        free(temp_memory);
    }
}

void check_star(command* flags, va_list* list_arg) {
    if (flags->width == -2) {
        flags->width =  va_arg(*list_arg, int);
    }
    if (flags->precission == -2) {
        flags->precission =  va_arg(*list_arg, int);
    }
}

void define_d_i(long int* d, va_list* list_arg, command* flags) {
    if (flags->lenght == 'l') {
        *d = va_arg(*list_arg, long int);
    } else if (flags->lenght == 'h') {
        *d = (short int) va_arg(*list_arg, int);
    } else {
        *d = va_arg(*list_arg, int);
    }
}

void define_x_X_o(unsigned long int* d, va_list* list_arg, command* flags) {
    if (flags->lenght == 'l') {
        *d = va_arg(*list_arg, unsigned long int);
    } else if (flags->lenght == 'h') {
        *d = (unsigned short int) va_arg(*list_arg, unsigned int);
    } else {
        *d = va_arg(*list_arg, unsigned int);
    }
}

void define_f(long double* float_number, va_list* list_arg, command* flags) {
    if (flags->lenght == 'L') {
        *float_number = va_arg(*list_arg, long double);
    } else {
        *float_number = va_arg(*list_arg, double);
    }
}

void find_temp_result(char* temp, char f_next, va_list* list_arg,
                      int* is_positive, long double* float_number, int count_simbol, command* flags) {
    check_star(flags, list_arg);

    char *temp_memory;
    if (f_next == 'c') {
        temp[0] = (flags->lenght == 'l') ? va_arg(*list_arg, wint_t) : va_arg(*list_arg, int);
        temp[1] = '\0';
    } else if (f_next == 's') {
        char* s = (flags->lenght == 'l') ? (char*) va_arg(*list_arg, wchar_t*) : va_arg(*list_arg, char*);
        s21_strcpy(temp, s);
    } else if (f_next == 'd' || f_next == 'i') {
        long int d;
        define_d_i(&d, list_arg, flags);
        *is_positive = (d >= 0) ? 1 : 0;
        temp_memory = s21_itoa(d);
        s21_strcpy(temp, temp_memory);
    } else if (f_next == 'f') {
        define_f(float_number, list_arg, flags);
        *is_positive = (*float_number >= 0) ? 1 : 0;
        s21_ftoa(*float_number, temp, flags->precission);
        temp[s21_strlen(temp) - 1] = (temp[s21_strlen(temp) - 1] == '.') ? '\0' : temp[s21_strlen(temp) - 1];
    } else if (f_next == '%') {
        temp[0] = '%';
        temp[1] = '\0';
    } else if (f_next == 'x' || f_next == 'X'|| f_next == 'o' || f_next == 'u') {
        unsigned long int d;
        define_x_X_o(&d, list_arg, flags);
        check_x_X_o(f_next, temp, d);
    } else if (f_next == 'n') {
        int *vptr = va_arg(*list_arg, int*);
        *vptr = count_simbol;
    } else if (f_next == 'p') {
        int *vptr = va_arg(*list_arg, int*);
        to_hex((long long int)vptr, temp, 'a');
        add_simbol(temp, "0x", 0);
    } else if (f_next == 'e' || f_next == 'E') {
        double number = va_arg(*list_arg, double);
        char str_e_or_E[10];
        str_e_or_E[0] = f_next;
        str_e_or_E[1] = '\0';
        spec_e(temp, number, str_e_or_E);
    }

     if (f_next == 'd' || f_next == 'i') {
        free(temp_memory);
    }
}


void check_str_precission(char* temp_result, int precission) {
    int len = s21_strlen(temp_result);
    if (precission <= len) {
        temp_result[precission] = '\0';
    }
}

void check_precission_or_width(char* temp_result, int p_or_w,
                            int flag_type, char* simbol) {
    int len = s21_strlen(temp_result);

    if (p_or_w == 0 && s21_strcmp(temp_result, simbol) == 0) {
        temp_result[0] = '\0';
    } else if (p_or_w > len && temp_result[0] != '-') {
        while (len != p_or_w) {
            add_simbol(temp_result, simbol, 0);
            len++;
        }
    } else if (temp_result[0] == '-' && p_or_w > len - 1) {
        while (len - flag_type != p_or_w) {
            add_simbol(temp_result, simbol, flag_type);
            len++;
        }
    }
}

char* check_struct(command flags, char* temp_result, int is_positive,
                   char f_next) {
    if (flags.precission != -1) {
        if (f_next == 's') {
            check_str_precission(temp_result, flags.precission);
        } else if (f_next == 'd' || f_next == 'i' || f_next == 'u' ||
                   f_next == 'o' || f_next == 'x' || f_next == 'X') {
            check_precission_or_width(temp_result, flags.precission, 1, "0");
        }
    }

    if (flags.width != -1 && flags.zero == '0' && flags.precission == -1) {
        check_precission_or_width(temp_result, flags.width, 0, "0");
    }

    if (flags.space == ' ' && is_positive == 1) {
        add_simbol(temp_result, " ", 0);
    }

    if (flags.plus == '+' && is_positive == 1) {
        add_simbol(temp_result, "+", 0);
    }

    if (flags.width != -1 && flags.minus != '-') {
        check_precission_or_width(temp_result, flags.width, 0, " ");
    }

    if (flags.minus == '-') {
        int len = s21_strlen(temp_result);
        if (flags.width >  len) {
            while (len != flags.width) {
                s21_strcat(temp_result, " ");
                len++;
            }
        }
    }

    return temp_result;
}

void reset_struct(command* flags) {
    flags->minus = '\0';
    flags->plus = '\0';
    flags->space = '\0';
    flags->zero = '\0';
    flags->width = -1;
    flags->precission = -1;
    flags->lenght = '\0';
}

int s21_sprintf(char *str, const char *format, ...) {
    int i = 0;
    va_list list_arg;
    va_start(list_arg, format);
    str[0] = '\0';

    while (*format != 0) {
        char next = *format++;
        if (next == '%') {
            char temp_result[10000] = "", f_next = *format++;
            int is_positive = -1;
            long double float_number;
            command flags = {0};
            flags.width = -1;
            flags.precission = -1;

            f_next = define_struct(f_next, &flags, &format);
            find_temp_result(temp_result, f_next, &list_arg, &is_positive, &float_number, i, &flags);
            char* result;
            result = check_struct(flags, temp_result, is_positive, f_next);

            s21_strcat(&str[i], result);
            i += s21_strlen(result);
            // лики проверить
            //  free(result);

            temp_result[0] = '\0';
            reset_struct(&flags);
        } else {
            *(str + i) = next;
            i++;
        }
        *(str + i) = '\0';
    }

    va_end(list_arg);
    return s21_strlen(str);  //  ???
}
