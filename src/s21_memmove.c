#include "s21_string.h"

//  4
void *s21_memmove(void *dest, const void *src, s21_size_t n) {
    void * ret = dest;
    if (dest <= src || (char*)dest >= ((char*)src + n)) {
        while (n--) {
            *(char*)dest = *(char*)src;
            dest = (char*)dest + 1;
            src = (char*)src + 1;
        }
    } else {
        dest = (char*)dest + n - 1;
        src = (char*)src + n - 1;
        while (n--) {
            *(char*)dest = *(char*)src;
            dest = (char*)dest - 1;
            src = (char*)src - 1;
        }
    }
    return ret;
}
