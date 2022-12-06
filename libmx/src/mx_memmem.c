#include "libmx.h"

void *mx_memmem(const void *big, size_t big_len, const void *little, size_t little_len) {

    if (big_len < little_len || little_len == 0 || big_len == 0) return NULL;

    unsigned char *uc_big = (unsigned char *)big;
    unsigned char *uc_little = (unsigned char *)little;

    while (*uc_big)
    {
        if (mx_memcmp((void *)uc_big, (void *)uc_little, little_len) == 0) {
            return (void *)uc_big;
        }
        uc_big++;
    }
    
    return NULL;
}
