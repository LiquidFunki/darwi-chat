#include "libmx.h"

int mx_get_substr_index(const char *str, const char *sub) {

    if (str == NULL || sub == NULL) return -2;
    if (*sub == '\0') return 0;

    while (str)
    {   
        int first_index = mx_get_char_index(str, sub[0]);
        if (first_index < 0) {
            break;
        } else {
            str = (str + first_index);
        }

        if (str && mx_strncmp(str, sub, mx_strlen(sub)) == 0) {
            return first_index;
        }
        str++;
    }
    
    return -1;

}
