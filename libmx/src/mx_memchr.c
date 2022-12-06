#include "libmx.h"

void *mx_memchr(const void *s, int c, size_t n) {
    unsigned char * uc_s = (unsigned char *)s;
    unsigned char uc_c = (unsigned char)c;

    for (size_t i = 0; i < n; i++) {
        if (uc_s[i] == uc_c)
        {
            return (void *)(uc_s + i);
        }
        
    }

    return NULL;
}
