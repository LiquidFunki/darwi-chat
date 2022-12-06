#ifndef MODEL_MESSAGE_H
#define MODEL_MESSAGE_H

#include "libmx.h"
#include "protocol.h"
#include "string.h"
#include "stdlib.h"
#include "model_defines.h"

typedef enum   message_data_types {

    MESSAGE_TEXT,
    MESSAGE_FILE,
    MESSAGE_STONE,
    NUMBER_OF_MESSAGE_TYPES

}             e_message_data_types;

typedef enum  message_status {

    MESSAGE_SENT,
    MESSAGE_RECEIVED,
    MESSAGE_READ,
    MESSAGE_EDITED

}             e_message_status;

typedef struct s_model_message {

    size_t               id;
    char*               from_user;
    char*               to_user;
    e_message_data_types data_type;
    char*                data;
    char*                date;
    e_message_status     status;
    char*               forward_from;

}              t_model_message;

t_model_message* new_model_message();
char*         to_string_model_message(t_model_message*);
t_model_message* from_string_model_message(char*);
void          free_model_message(t_model_message**);

#endif
