#include "libmx.h"

int mx_count_words(const char *str, char delimiter) {
    if (str == NULL) return -1;
    int result = 0, is_in_word = 0;
    while (*str != '\0')
    {
        if (*str == delimiter) {
            is_in_word = 0;
        } else if (!is_in_word) {
            is_in_word = 1;
            result++;
        }
        str++;
    }
    return result;
}
