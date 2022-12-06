#include "libmx.h"

char *mx_nbr_to_hex(unsigned long nbr) {

    unsigned long nbr_copy = nbr;
    unsigned long length = 0;

    while (nbr_copy != 0)
    {
        length++;
        nbr_copy /= 16;
    }


    char *hex = mx_strnew(length);
    while (true)
    {
        if (nbr == 0) {
            break;
        }

        int symbol = nbr % 16;

        if (symbol < 10) {
            hex[length - 1] = '0' + symbol;
        } else {
            hex[length - 1] = 'a' + symbol - 10;
        }
        length--;
        nbr /= 16;
    }
    return hex;
}
