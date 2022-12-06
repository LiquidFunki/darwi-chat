#include "set_avatar_request.h"

char* send_set_avatar_request(char* path_to_file, char* username, char* token) {

    cJSON* protocol = create_protocol();

    cJSON* action_value = cJSON_CreateString("SET AVATAR");

    add_to_protocol(protocol, "ACTION", action_value);
    add_to_protocol_string(protocol, "USERNAME", username);
    add_to_protocol_string(protocol, "TOKEN", token);

    char* after_file_request = cJSON_Print(protocol);

    cJSON_Delete(protocol);

    char* response = send_file(path_to_file, after_file_request, get_server_ip(), PORT);

    return response;
}
