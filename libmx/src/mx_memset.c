#include "libmx.h"

void *mx_memset(void *b, int c, size_t len) {
    unsigned char uc_c = (unsigned char)c;
    unsigned char *uc_b = (unsigned char *)b;
    for (size_t i = 0; i < len; i++) {
        uc_b[i] = uc_c;
    }
    return b;
}
