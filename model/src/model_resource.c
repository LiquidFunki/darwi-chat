#include "model_resource.h"

t_model_resource* new_model_resource() {

    t_model_resource* model_resource = (t_model_resource*)malloc(sizeof(t_model_resource));

    model_resource->id = 0;
    model_resource->name = mx_strnew(BUFSIZ);
    model_resource->path = mx_strnew(BUFFER_SIZE);

    return model_resource;
}

char*         to_string_model_resource(t_model_resource* model_resource) {

    cJSON* resource = cJSON_CreateObject();

    add_to_protocol_number(resource, "id", model_resource->id);
    add_to_protocol_string(resource, "name", model_resource->name);
    add_to_protocol_string(resource, "path", model_resource->path);

    char* resource_str = cJSON_Print(resource);

    cJSON_Delete(resource);
    return resource_str;
}

t_model_resource* from_string_model_resource(char* json) {

    cJSON* resource = cJSON_Parse(json);

    t_model_resource* model_resource = new_model_resource();

    model_resource->id = get_from_protocol_number(resource, "id");
    char* name = get_from_protocol_string(resource, "name");
    char* path = get_from_protocol_string(resource, "path");

    strcpy(model_resource->name, name);
    strcpy(model_resource->path, path);

    cJSON_Delete(resource);
    return model_resource;
}

void          free_model_resource(t_model_resource** model_resource) {
    free((*model_resource)->name);
    free((*model_resource)->path);
    free(*model_resource);

    *model_resource = NULL;
}
