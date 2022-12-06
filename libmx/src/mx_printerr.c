#include "libmx.h"

void mx_printerr(char* text) {
    write(2, text, mx_strlen(text));
}
