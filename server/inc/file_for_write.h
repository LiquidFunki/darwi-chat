#ifndef FILE_FOR_WRITE
#define FILE_FOR_WRITE

#include "libmx.h"
#include <stdio.h>
#include <string.h>
#include "cJSON.h"
#include <stdio.h>
#include "protocol.h"
// #include <io.h>
#include <sys/stat.h>
#include "select_action.h"



char* get_next_file_for_write();
char* file_for_write();
char* save_file(char* request, char* response);
char* file_end(char* request, char* response);


#endif
