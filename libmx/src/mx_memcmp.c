#include "libmx.h"

int mx_memcmp(const void *s1, const void *s2, size_t n) {
    unsigned char * uc_s1 = (unsigned char *)s1;
    unsigned char * uc_s2 = (unsigned char *)s2;

    for (size_t i = 0; i < n; i++) {
        if (uc_s1[i] != uc_s2[i]) return uc_s1 - uc_s2;
    }

    return 0;
}
