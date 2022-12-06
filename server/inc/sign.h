#ifndef SIGN_UP_H
#define SIGN_UP_H

#include "libmx.h"
#include "cJSON.h"
#include "model.h"
#include "database.h"
#include "protocol.h"
#include "encrypt.h"

bool sign_up(char* request, char *response);
bool sign_in(char* request, char *response);

#endif
