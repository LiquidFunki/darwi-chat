#ifndef SET_AVATAR_REQUEST_H
#define SET_AVATAR_REQUEST_H

#include "libmx.h"
#include "protocol.h"
#include "send_request.h"
#include "protocol.h"
#include "send_file.h"

char* send_set_avatar_request(char* path_to_file, char* username, char* token);


#endif
