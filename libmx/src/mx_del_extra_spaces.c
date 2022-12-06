#include "libmx.h"

char *mx_del_extra_spaces(const char *str) {
    if (str == NULL) return NULL;
    char *trimed = mx_strtrim(str);
    int len = mx_strlen(trimed);
    int without_spaces_len =  len;
    int is_space = 0;
    for (int i = 0; i < len; i++){
        if ( mx_isspace(trimed[i]) ) {
            if (is_space == 0) {
                is_space = 1;
            } else {
                without_spaces_len--;
            }
        } else {
            is_space = 0;
        }
    }

    char *result = mx_strnew(without_spaces_len);
    int result_index = 0;
    for (int i = 0; i < len; i++) {
        if ( mx_isspace(trimed[i]) ) {
            if ( is_space == 0 ) {
                result[result_index] = ' ';
                result_index++;
                is_space = 1;
            }
        } else {
            result[result_index] = trimed[i];
            result_index++;
            is_space = 0;
        }
    }
    mx_strdel(&trimed);
    return result;
}
