#include "model_stone.h"

t_model_stone* new_model_stone() {

    t_model_stone* model_stone = (t_model_stone*)malloc(sizeof(model_stone));

    model_stone->id = 0;
    model_stone->path = mx_strnew(BUFFER_SIZE);

    return model_stone;
}

char*         to_string_model_stone(t_model_stone* model_stone) {

    cJSON* stone = cJSON_CreateObject();

    add_to_protocol_number(stone, "id", model_stone->id);
    add_to_protocol_string(stone, "path", model_stone->path);

    char* stone_str = cJSON_Print(stone);

    cJSON_Delete(stone);

    return stone_str;
}

t_model_stone* from_string_model_stone(char* json) {

    cJSON* stone = cJSON_Parse(json);

    t_model_stone* model_stone = new_model_stone();

    model_stone->id = get_from_protocol_number(stone, "id");

    char* path = get_from_protocol_string(stone, "path");

    strcpy(model_stone->path, path);

    cJSON_Delete(stone);

    return model_stone;
}

void          free_model_stone(t_model_stone** model_stone) {

    free((*model_stone)->path);
    free(*model_stone);

    *model_stone = NULL;
}
