
#include "libmx.h"

int mx_binary_search(char **arr, int size, const char *s, int *count) {
    int middle = size / 2;
    int low = 0, high = size - 1;

    (*count) = 0;
    if (size == 0) return -1;

    while (low <= high)
    {
        middle = low + (high - low) / 2;
        (*count)++;
        if (mx_strcmp(arr[middle], s) == 0) {
            return middle;
        }
        else if (mx_strcmp(arr[middle], s) < 0) {
            low = middle + 1;
        } else {
            high = middle - 1;
        }
    }
    (*count) = 0;
    return -1;
}
