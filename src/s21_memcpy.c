#include "s21_string.h"

//  3
void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
    const char* f_pointer = (const char*) src;
    char* t_pointer = (char*) dest;
    for (s21_size_t i = 0; i < n; ++i) {
        *(t_pointer++) = *(f_pointer++);
    }
    return dest;
}
