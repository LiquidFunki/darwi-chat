#include "libmx.h"

int mx_count_substr(const char *str, const char *sub) {

    if (str == NULL || sub == NULL) return -1;

    int result = 0;
    if (sub[0] == '\0') return result;
    while (1) {
        str = mx_strstr(str, sub);
        if (str) {
            result++;
            if (*str != '\0')  {
                str++;
            }
            else
                break;
        } else 
            break;
    }
    return result;
}
