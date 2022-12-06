#include "model_store.h"

t_model_store *new_model_store() {
    t_model_store *model_store = (t_model_store*)malloc(sizeof(t_model_store));

    model_store->id = 0;
    model_store->name = mx_strnew(BUFSIZ);
    model_store->path = mx_strnew(BUFFER_SIZE);
    model_store->price = 0;
    model_store->era = STONE_AGE;

    return model_store;
}

char* to_string_model_store(t_model_store* model_store) {

    cJSON* resource = cJSON_CreateObject();

    add_to_protocol_number(resource, "id", model_store->id);
    add_to_protocol_string(resource, "name", model_store->name);
    add_to_protocol_string(resource, "path", model_store->path);
    add_to_protocol_number(resource, "id", model_store->price);
    add_to_protocol_number(resource, "id", model_store->era);

    char* resource_str = cJSON_Print(resource);

    cJSON_Delete(resource);
    return resource_str;
}

t_model_store* from_string_model_store(char* json) {

    cJSON* resource = cJSON_Parse(json);

    t_model_store* model_store = new_model_store();

    model_store->id = get_from_protocol_number(resource, "id");
    char* name = get_from_protocol_string(resource, "name");
    char* path = get_from_protocol_string(resource, "path");
    model_store->price = get_from_protocol_number(resource, "price");
    model_store->era = get_from_protocol_number(resource, "era");

    strcpy(model_store->name, name);
    strcpy(model_store->path, path);

    cJSON_Delete(resource);
    return model_store;
}

void free_model_store(t_model_store** model_store) {
    free((*model_store)->name);
    free((*model_store)->path);
    free(*model_store);

    *model_store = NULL;
}
