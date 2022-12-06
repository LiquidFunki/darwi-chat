#include "libmx.h"

void mx_del_strarr(char ***arr) {
    char **_arr = *arr;
    int i = 0;
    while ( _arr[i] != NULL)
    {
        mx_strdel( (_arr + i) );
        i++;
    }
    free(_arr);
    *arr = NULL;
}
