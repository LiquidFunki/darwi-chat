#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "libmx.h"
#include "cJSON.h"
#include "string.h"
#include "time.h"
#include "stdio.h"

#define BUFSIZ 1024
#define SEND_SIZE 5120
#define BUFFER_SIZE 4096
#define READ_SIZE   14336

#define PORT 10001

cJSON* create_protocol();
cJSON* add_to_protocol(cJSON* protocol, char* key, cJSON* value);
cJSON* add_to_protocol_string(cJSON* protocol, char* key, char* value);
cJSON* add_to_protocol_number(cJSON* protocol, char* key, double value);
cJSON* add_file_to_protocol(cJSON* protocol, char* key, char* file_bytes, size_t file_size);
char*  get_file_from_protocol(cJSON* protocol, char* key, size_t* file_size);
cJSON* get_from_protocol(cJSON* protocol, char* key);
char*  get_from_protocol_string(cJSON* protocol, char* key);
double get_from_protocol_number(cJSON* protocol, char* key);
cJSON* set_in_protocol_string(cJSON* protocol, char* key, char*value);

char* screen_file(char* file_bytes, size_t file_size, size_t *screened_size);
char* unscreen_file(char* screened, size_t screened_size, size_t* file_size);

char* get_server_ip();


#endif
