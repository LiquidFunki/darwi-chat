#include "sign_requests.h"

char *get_sign_status(char *response){
    cJSON* response_obj = cJSON_Parse(response);
    if (response_obj == NULL) {
        printf("parse error\n");
        return false;
    }

    cJSON* sign_status_obj = cJSON_GetObjectItemCaseSensitive(response_obj, "STATUS");
    if (sign_status_obj == NULL) {
        printf("sign status obj error\n");
        return false;
    }
    char* status = sign_status_obj->valuestring;
    // cJSON_Delete(response_obj);
    // cJSON_Delete(sign_status_obj);

    return status;
}

char* create_sign_request(t_model_user* model_user, char* status) {

    char* data = to_string_model_user(model_user);

    cJSON* protocol = create_protocol();
    
    cJSON* data_value = cJSON_CreateString(data);
    cJSON* action_value = cJSON_CreateString(status);

    add_to_protocol(protocol, "ACTION", action_value);
    add_to_protocol(protocol, "DATA", data_value);

    char* protocol_str = cJSON_Print(protocol);

    cJSON_Delete(protocol);

    return protocol_str;
}

bool send_sign_up_request(t_model_user* model_user) {

    char* request = create_sign_request(model_user, "SIGN UP");
    char* response = send_request(request, get_server_ip(), PORT);
    
    char* status = get_sign_status(response);

    printf("%s\n", response);

    return !strcmp(status, "SUCCESS");
}


cJSON* send_sign_in_request(t_model_user* model_user) {

    char* request = create_sign_request(model_user, "SIGN IN");
    char* response = send_request(request, get_server_ip(), PORT);

    // char* status = get_sign_status(response);
    cJSON* response_obj = cJSON_Parse(response);

    // printf("%s\n", response);

    return response_obj;
}

