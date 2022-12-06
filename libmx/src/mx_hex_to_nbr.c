#include "libmx.h"

unsigned long mx_hex_to_nbr(const char *hex) {
    if (hex == NULL) return 0;
    unsigned long number = 0;
    while (*hex != '\0')
    {
        if (mx_isalpha(*hex)) {

            if (mx_islower(*hex) && *hex >= 'a' && *hex <= 'f') {
                number *= 16;
                number += *hex - 'a' + 10;
            } else if (mx_isupper(*hex) && *hex >= 'A' && *hex <= 'F') {
                number *= 16;
                number += *hex - 'A' + 10;
            } else {
                return 0;
            }

        } else if (mx_isdigit(*hex)) {
            number *= 16;
            number += *hex - '0';
        } else {
            return 0;
        }
        hex++;
    }
    return number;
}
