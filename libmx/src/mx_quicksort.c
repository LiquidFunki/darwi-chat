#include "libmx.h"

int mx_quicksort(char **arr, int left, int right) {

    int i, j;
    i = left;
    j = right;

    char *tmp, *anchor;
    anchor = arr[left + (right - left) / 2];
    int anchor_len = mx_strlen(anchor);

    int swaps = 0;

    int i_len;
    int j_len;

    do {

        i_len = mx_strlen(arr[i]);
        j_len = mx_strlen(arr[j]);


        while (i_len < anchor_len) {
            i++;
            i_len = mx_strlen(arr[i]);
        }
        while (j_len > anchor_len)
        {
            j--;
            j_len = mx_strlen(arr[j]);
        }
        if (i <= j) {
            if (i_len > j_len) {
                tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
                swaps++;
            }
            i++;
            if (j > 0) j--;
        }
    } while (i <= j);

    if (i < right) {
        swaps += mx_quicksort(arr, i, right);
    }
    if (j > left) {
        swaps += mx_quicksort(arr, left, j);
    }

    return swaps;
}
