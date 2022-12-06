#ifndef MESSAGES_SERVER_H
#define MESSAGES_SERVER_H

#include "cJSON.h"
#include "libmx.h"
#include "string.h"
#include "model_message.h"
#include "protocol.h"
#include "database.h"
#include "file_for_write.h"
#include "server.h"
#include "wrong_messages.h"



char* add_message(cJSON* request);
char* get_messages(cJSON* request);
bool start_chat(char *request, char *response);

bool get_avatar(char *request, char *response);
bool get_resource(char *request, char *response);
bool get_user_data_money(char *request, char *response);
bool get_stone(char *request, char *response);


#endif
