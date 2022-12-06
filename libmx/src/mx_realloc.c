#include "libmx.h"

void *mx_realloc(void *ptr, size_t size) {

//    size_t m_size = malloc_size(ptr); // swap to uncoment
     size_t m_size = size;

   
    
    if (size <= 0 && ptr) {
        free(ptr);
        return NULL;
    }

    void *buffer = NULL;

    if (ptr == NULL) return malloc(size);

    if (size < m_size) {
        buffer = malloc(m_size);
        size = m_size;
    } else {
        buffer = malloc(size);
    }

    mx_memcpy(buffer, ptr, size);
    free(ptr);
    return buffer;
}
