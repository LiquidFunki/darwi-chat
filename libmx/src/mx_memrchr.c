#include "libmx.h"

void *mx_memrchr(const void *s, int c, size_t n) {

    unsigned char uc_c = (unsigned char)c;
    unsigned char *uc_s = (unsigned char *)s;

    for (size_t i = n; ; i--) {
        
        if (uc_s[i] == uc_c)  return (void *)(uc_s + i);
        if (i == 0) break;
    }

    return NULL;
}
