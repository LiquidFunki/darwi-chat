#ifndef MODEL_RESOURCE_H
#define MODEL_RESOURCE_H

#include "libmx.h"
#include "protocol.h"
#include <string.h>
#include <stdlib.h>
#include "model_defines.h"

typedef struct s_model_resource {

    size_t id;
    char*  path;
    char*  name;

}              t_model_resource;

t_model_resource* new_model_resource();
char*         to_string_model_resource(t_model_resource*);
t_model_resource* from_string_model_resource(char*);
void          free_model_resource(t_model_resource**);

#endif
