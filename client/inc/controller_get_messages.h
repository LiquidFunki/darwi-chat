#ifndef CONTROLLER_GET_MESSAGES
#define CONTROLLER_GET_MESSAGES


#include "messages_requests.h"
#include "get_resources_request.h"
#include "user_data.h"
#include "view_chat_window.h"


void controller_get_messages();
t_model_message** controller_get_new_messages(int* count);


#endif
