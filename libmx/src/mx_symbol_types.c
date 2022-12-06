#include "libmx.h"

bool mx_isalpha(int c) {
    return ( c >= 'a' &&  c <= 'z' ) || ( c >= 'A' && c <= 'Z' );
}

bool mx_isdigit(int c) {
    return (c >= '0' && c <= '9');
}

bool mx_islower(int c) {
    bool result = (c >= 'a' && c <= 'z');
    return result;
}

bool mx_isupper(int c) {
    bool result = (c >= 'A' && c <= 'Z');
    return result;
}

bool mx_isspace(char c) {
    bool result = false;
    for (int i = '\t'; i <= '\r' && !result; i++) {
        result = (c == i);
    }
    result |= (c == ' ');
    return result;
}
