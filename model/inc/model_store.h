#ifndef MODEL_STORE_H
#define MODEL_STORE_H

#include "libmx.h"
#include "protocol.h"
#include <string.h>
#include <stdlib.h>
#include "model_user_data.h"
#include "model_defines.h"

typedef struct s_model_store {

    size_t id;
    char *name;
    char *path;
    size_t price;
    e_eras era;

}              t_model_store;

t_model_store* new_model_store();
char* to_string_model_store(t_model_store* model_store);
t_model_store* from_string_model_store(char* json);
void free_model_store(t_model_store**);

#endif
