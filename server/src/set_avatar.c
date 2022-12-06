#include "set_avatar.h"

char* set_avatar(cJSON* request) {    
    printf("set avatar. move avatar to folder. set in db\n");

    char* path_to_file = get_from_protocol_string(request, "PATH TO FILE");

    char* full_path_to_file = mx_strjoin("./server/resources/tmp/", path_to_file);

    t_model_resource* model_resource = new_model_resource();
    strcpy(model_resource->path, full_path_to_file);
    strcpy(model_resource->name, "avatar");
    fflush(stdout);
    size_t avatar_id = insert_data_resource(model_resource);


    char* username = get_from_protocol_string(request, "USERNAME");

    
    update_user_avatar(username, (int)avatar_id);

    cJSON* response = create_protocol();
    add_to_protocol_string(response, "STATUS", "OK");
    char* response_str = cJSON_Print(response);

    cJSON_Delete(response);

    return response_str;

}