#include "libmx.h"

char *mx_strstr(const char *haystack, const char *needle) {

    if (*needle == '\0') return (char *)haystack;
    while (1)
    {
        haystack = mx_strchr(haystack, needle[0]);
        if (haystack && mx_strncmp(haystack, needle, mx_strlen(needle)) == 0) {
            return (char *)haystack;
        }
        if (*haystack == '\0') break;
        haystack++;
    }
    
    return NULL;
}
