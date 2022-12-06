#ifndef GET_FILE_H
#define GET_FILE_H

#include "libmx.h"
#include "cJSON.h"
#include <stdio.h>
#include <string.h>
#include "protocol.h"
#include "send_request.h"

char* save_file_client(char* response, size_t* unscreened_size);
char* get_file(char* path_to_file);

#endif
