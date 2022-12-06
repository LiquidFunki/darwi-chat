#include "libmx.h"

char *mx_strtrim(const char *str) {
    if (str == NULL) return NULL;
    int start_index =  0, end_index =  mx_strlen(str) - 1;
    for (; mx_isspace(str[start_index]); start_index++) {}
    for (; mx_isspace(str[end_index]); end_index--) {}
    int len = end_index - start_index + 1;
    char *trimed = mx_strnew(len);
    mx_strncpy(trimed, (str + start_index), len);
    return trimed;
}
