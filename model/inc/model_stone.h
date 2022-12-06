#ifndef MODEL_STONE_H
#define MODEL_STONE_H

#include "libmx.h"
#include "protocol.h"
#include <stdlib.h>
#include <string.h>
#include "model_defines.h"

typedef struct s_model_stone {

    size_t id;
    char* path;

}              t_model_stone;

t_model_stone* new_model_stone();
char*         to_string_model_stone(t_model_stone*);
t_model_stone* from_string_model_stone(char*);
void          free_model_stone(t_model_stone**);

#endif
