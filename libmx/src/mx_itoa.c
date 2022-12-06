
#include "libmx.h"

char *mx_itoa(int number) {
    char *result = NULL;
    if (number == 0) {
        result = (char *)malloc(sizeof(char) * 2);
        result[1] = '\0';
        result[0] = '0';
        return result;
    }
    char buff[22];
    int start_index = 0;

    int is_positive = 1;
    if (number < 0) {
        is_positive = 0;
        number = -number;
        if (number == -2147483648) {
            result = mx_strnew(11);
            result[0] = '-';
            result[1] = '2';
            result[2] = '1';
            result[3] = '4';
            result[4] = '7';
            result[5] = '4';
            result[6] = '8';
            result[7] = '3';
            result[8] = '6';
            result[9] = '4';
            result[10] = '8';
            return result;
        }
    }

    
    
    while (number != 0)
    {
        buff[start_index] = number % 10 + '0';
        number /= 10;
        start_index++;
    }

    if (is_positive == 0) {
        buff[start_index] = '-';
        start_index++;
    }
    // result = (char *)malloc(sizeof(char) * (start_index + 1));
    result = mx_strnew(start_index);
    result[start_index] = '\0';
    for (int i = start_index - 1; i >= 0; i--) {
        result[start_index - i - 1] = buff[i];
    }
    return result;
}
