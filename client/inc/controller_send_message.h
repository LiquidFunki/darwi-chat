#ifndef CONTROLLER_SEND_MESSAGE
#define CONTROLLER_SEND_MESSAGE

#include "model_message.h"
#include "protocol.h"
#include "user_data.h"
#include "libmx.h"
#include "string.h"
#include "messages_requests.h"
#include "get_resources_request.h"
#include "database_client.h"
#include "view_messages.h"


t_model_message *controller_send_message(char* to, e_message_data_types data_type, char* data);
 t_model_message *controller_forward_message(char* to, e_message_data_types data_type, char* data, char *forward_from);

#endif
