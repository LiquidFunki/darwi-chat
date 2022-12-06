#include "get_resources_request.h"

t_model_resource* send_get_avatar_request(char* username) {

    cJSON* protocol = create_protocol();

    add_to_protocol_string(protocol, "ACTION", "GET_AVATAR");

    add_to_protocol_string(protocol, "DATA", username);
    
    char* request = cJSON_Print(protocol);
    
    char* response = send_request(request, get_server_ip(), PORT);

    cJSON* response_resource_model = cJSON_Parse(response);

    t_model_resource *model_resource = new_model_resource();

    printf("%s\n", response);
    fflush(stdout);

   model_resource = from_string_model_resource(get_from_protocol_string(response_resource_model, "DATA"));

    // char *client_path = mx_replace_substr(model_resource->path, "./server", "./client");

   return model_resource;
}


t_model_resource* send_get_resource_request(char *id) {

    cJSON* protocol = create_protocol();

    add_to_protocol_string(protocol, "ACTION", "GET_RESOURCE");

    add_to_protocol_string(protocol, "DATA", id);
    
    char* request = cJSON_Print(protocol);
    
    char* response = send_request(request, get_server_ip(), PORT);

    cJSON* response_resource_model = cJSON_Parse(response);

    t_model_resource *model_resource = new_model_resource();

    printf("%s\n", response);
    fflush(stdout);

   model_resource = from_string_model_resource(get_from_protocol_string(response_resource_model, "DATA"));

    // char *client_path = mx_replace_substr(model_resource->path, "./server", "./client");

   return model_resource;
}

t_model_stone* send_get_stone_request(char *id) {

    cJSON* protocol = create_protocol();

    add_to_protocol_string(protocol, "ACTION", "GET_STONE");

    add_to_protocol_string(protocol, "DATA", id);
    
    char* request = cJSON_Print(protocol);
    fprintf(stderr, "\n\nTHERE REQUEST FOR STONE %s\n\n", request);
    char* response = send_request(request, get_server_ip(), PORT);

    cJSON* response_resource_model = cJSON_Parse(response);

    t_model_stone *model_stone = new_model_stone();

    printf("%s\n", response);
    fflush(stdout);

   model_stone = from_string_model_stone(get_from_protocol_string(response_resource_model, "DATA"));

    // char *client_path = mx_replace_substr(model_resource->path, "./server", "./client");

   return model_stone;
}
