#ifndef MESSAGES_REQUESTS
#define MESSAGES_REQUESTS

#include "send_request.h"
#include "send_file.h"
#include "model_message.h"
#include "cJSON.h"
#include "get_file.h"
#include "get_file.h"


char* send_message(t_model_message* model_message, cJSON* protocol);
cJSON* get_all_my_messages(cJSON* cookies);
cJSON* get_my_new_messages(cJSON* cookies);

bool send_start_chat_request(char *username);
char *get_start_chat_status(char *response);
char* create_start_char_request(char *username, char* status);

#endif
