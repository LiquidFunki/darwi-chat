#include "libmx.h"

void *mx_memccpy(void *__restrict__ dst, const void *__restrict__ src, int c, size_t n) {
    unsigned char uc_c = (unsigned char)c;

    unsigned char *uc_dst = (unsigned char *)dst;
    unsigned char *uc_src = (unsigned char *)src;

    for (size_t i = 0; i < n; i++) {
        uc_dst[i] = uc_src[i];
        if (uc_c == uc_src[i]) {
            return (void *)(uc_dst + i + 1);
        }
    }

    return NULL;
}
