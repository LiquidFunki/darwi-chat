
#include "libmx.h"

void mx_printint(int n) {

    char reverse_number[15];
    int number_length = 0;

    if (n < 0) {
        mx_printchar('-');
        if (n != -2147483648)
            n = -n;
        else {
            mx_printchar('2');
            mx_printchar('1');
            mx_printchar('4');
            mx_printchar('7');
            mx_printchar('4');
            mx_printchar('8');
            mx_printchar('3');
            mx_printchar('6');
            mx_printchar('4');
            mx_printchar('8');
            return;
        }
    } else if (n == 0) {
        mx_printchar('0');
        return;
    }

    while (n != 0)
    {
        reverse_number[number_length++] = (n % 10) + '0';
        n /= 10;
    }
    
    number_length--;

    for (; number_length >= 0; number_length--) {
        mx_printchar(reverse_number[number_length]);
    }
}
