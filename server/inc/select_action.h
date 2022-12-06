#ifndef SELECT_ACTION_H
#define SELECT_ACTION_H

#include "cJSON.h"
#include "sign.h"
#include "set_avatar.h"
#include "file_for_write.h"
#include "send_file_server.h"
#include "messages_server.h"
#include "quiz_server.h"
#include "user_data_actions.h"

int select_action(char* request, char* response);

#endif
