#include "libmx.h"

char *mx_strcat(char *restrict s1, const char *restrict s2) {
    for (int i = mx_strlen(s1); ; i++, s2++) {
        *(s1 + i) = *s2;
        if (*s2 == '\0') break;
    }
    return s1;
}
