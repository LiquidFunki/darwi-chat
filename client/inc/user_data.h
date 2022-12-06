#ifndef USER_DATA_H
#define USER_DATA_H

#include "libmx.h"
#include "cJSON.h"
#include "protocol.h"


// void generate_cookies();
void generate_cookies(char *user, char *password);
cJSON* get_cookies();

#endif
