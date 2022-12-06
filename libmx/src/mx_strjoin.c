#include "libmx.h"

char *mx_strjoin(char const *s1, char const *s2) {
    if (s1 == NULL && s2 == NULL) return NULL;
    else if (s1 != NULL && s2 == NULL) {
        return mx_strdup(s1);
    } else if (s2 != NULL && s1 == NULL) {
        return mx_strdup(s2);
    } else {
        int len = mx_strlen(s1) + mx_strlen(s2);
        char *result = mx_strnew(len);
        mx_strcat(result, s1);
        return mx_strcat(result, s2);
    }
}
