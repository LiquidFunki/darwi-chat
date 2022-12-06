#include "libmx.h"

char **mx_strsplit(char const *s, char c) {
    if (s == NULL) return NULL;
    int left_delimiter_index = 0, i = 0;
    int count_words = mx_count_words(s, c);
    char **result = (char **)malloc( (count_words + 1) * sizeof(char *));
    int result_index = 0;

    int is_left_delim = 1;
    for (; s[i] != '\0'; i++) {
        if (s[i] == c) {
            if (is_left_delim) {
                left_delimiter_index++;
            } else {
                int len = i - left_delimiter_index;
                // printf("index: %i, len: %i\n", i, len);
                result[result_index] = mx_strnew(len);
                mx_strncpy(result[result_index], s + left_delimiter_index, len);
                left_delimiter_index = i + 1;
                is_left_delim = 1;
                result_index++;
            }
        } else {
            is_left_delim = 0;
        }
    }

    if (left_delimiter_index != i) {
        int len = i - left_delimiter_index + 1;
        result[result_index] = mx_strnew(len);
        mx_strncpy(result[result_index], s + left_delimiter_index, len);
        result_index++;
    }

    result[result_index] = NULL;
    return result;
}
