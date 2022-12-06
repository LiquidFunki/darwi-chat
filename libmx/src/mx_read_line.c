#include "libmx.h"

int mx_read_line(char **lineptr, size_t buf_size, char delim, const int fd) {

    if (buf_size <= 0) return -2;

    buf_size = 1;
    char *buffer = mx_strnew(buf_size);
    char *temp = NULL, *lineptr_buff = *lineptr; 
    *lineptr = NULL;
    int bytes = 0;
    int delim_index = -1;
    int result = 0;

    while ( (bytes = read(fd, buffer, buf_size)) > 0 )
    {   
        if ((delim_index = mx_get_char_index(buffer, delim)) >= 0) {
            
            buffer[delim_index] = '\0';
            temp = *lineptr;
            *lineptr = mx_strjoin(*lineptr, buffer);
            if (temp != NULL) {
                mx_strdel(&temp);
            }
            result += mx_strlen(buffer);
            mx_strdel(&buffer);

            return result;

        }

        temp = *lineptr;
        *lineptr = mx_strjoin(*lineptr, buffer);
        if (temp != NULL) {
            mx_strdel(&temp);
        }
        result += bytes;
    }

    mx_strdel(&buffer);
    if (result == 0) {

        *lineptr = lineptr_buff;

        if (errno) {
            return -2;
        } else {
            return -1;
        }
    }
    
    return result;
}
