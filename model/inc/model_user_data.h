#ifndef MODEL_USER_DATA_H
#define MODEL_USER_DATA_H

#include "libmx.h"
#include "cJSON.h"
#include <stdlib.h>
#include "protocol.h"
#include "model_defines.h"

typedef enum  user_statuses {

    ONLINE,
    OFFLINE,
    NUMBER_OF_USER_STATUSES

}             e_user_statuses;

typedef enum   eras {

    STONE_AGE,
    EGYPT,
    MIDDLE_AGES,
    ENLIGHTMENT,
    MODERN_TIMES,
    NUMBER_OF_ERAS

}              e_eras;


typedef struct s_model_user_data {

    size_t          id;
    char*           about;
    e_user_statuses status;
    char*           t_number;
    char*           email;
    e_eras          era;
    size_t          money;
    size_t          avatar_id;
    char*           bought_items;

}              t_model_user_data;

t_model_user_data* new_model_user_data();
char*         to_string_model_user_data(t_model_user_data*);
t_model_user_data* from_string_model_user_data(char*);
void          free_model_user_data(t_model_user_data**);

#endif
