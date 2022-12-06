#include "libmx.h"

void *mx_memmove(void *dst, const void *src, size_t len) {

    void *buffer = malloc(len);

    mx_memcpy(buffer, src, len);
    mx_memcpy(dst, buffer, len);

    free(buffer);
    return  dst;
}
