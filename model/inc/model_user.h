#ifndef MODEL_USER_H
#define MODEL_USER_H

#include <string.h>
#include "libmx.h"
#include "cJSON.h"

#include "protocol.h"
#include "model_defines.h"

typedef struct s_model_user {

    size_t id;
    char* name;
    char* password;
    size_t user_data_id;
}              t_model_user;


t_model_user* new_model_user(char* name, char* password);
char*         to_string_model_user(t_model_user*);
t_model_user* from_string_model_user(char*);
void          free_model_user(t_model_user**);


#endif
