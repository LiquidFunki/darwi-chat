#include "libmx.h"

char *mx_file_to_str(const char *filename) {
    int file = open(filename, O_RDONLY);

    if (errno) {
        close(file);
        return NULL;
    }


    char c;
    char *result = mx_strnew(0);
    while (read(file, &c, 1))
    {
        char buff[2];
        buff[0] = c;
        buff[1] = '\0';
        char *garbage = result;
        result = mx_strjoin(result, buff);
        free(garbage);
    }
    
    close(file);
    return result;
}
