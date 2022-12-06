#include "messages_requests.h"

char* send_message(t_model_message* model_message, cJSON* protocol) {

    char* message_json = to_string_model_message(model_message);

    char* response = NULL;
    char* request = NULL;

    add_to_protocol_string(protocol, "ACTION", "SEND MSG");

    if (model_message->data_type == MESSAGE_TEXT) {

        add_to_protocol_string(protocol, "DATA", message_json);
        request = cJSON_Print(protocol);
        // TODO: check request size
        
        response = send_request(request, get_server_ip(), PORT);
        free(message_json);
        free(request);
    
    } else if (model_message->data_type == MESSAGE_FILE) {

        // after file json data == model_message
        add_to_protocol_string(protocol, "DATA", message_json);
        request = cJSON_Print(protocol);

        // printf("\nTHERE REQUEST: %s\n", request);

        //TODO:
        response = send_file(model_message->data, request, get_server_ip(), PORT);


        free(message_json);
        free(request);

    } else if (model_message->data_type == MESSAGE_STONE) {
        // after file json data == model_message
        add_to_protocol_string(protocol, "DATA", message_json);
        request = cJSON_Print(protocol);

        // printf("\nTHERE REQUEST: %s\n", request);

        //TODO:
        response = send_file(model_message->data, request, get_server_ip(), PORT);


        free(message_json);
        free(request);

    }

    return response;

}

cJSON* get_my_messages(cJSON* cookies, char* subaction) {
    // create table if not exist
    // get filename with temp messages json
    // get this file
    // parse json to array
    // parse all array elements to model_messages
    // add all messages to db
    // ACTION: GET MSGS
    cJSON* protocol = create_protocol();

    char* username = get_from_protocol_string(cookies, "USERNAME");
    char* token    = get_from_protocol_string(cookies, "TOKEN");

    cJSON* messages = NULL;

    if (username == NULL || token == NULL) {
        printf("username or token is null\n"); fflush(stdout);
        cJSON_Delete(protocol);
        return messages;
    }

    add_to_protocol_string(protocol, "FROM", username);
    add_to_protocol_string(protocol, "TOKEN", token);

    add_to_protocol_string(protocol, "ACTION", "GET MSGS");
    add_to_protocol_string(protocol, "SUBACTION", subaction);

    char* request = cJSON_Print(protocol);
    char* response = send_request(request, get_server_ip(), PORT);

    free(request);

    cJSON* response_file_with_msgs = cJSON_Parse(response);
    free(response);
    char* path_to_file = get_from_protocol_string(response_file_with_msgs, "DATA");

    char* result = NULL;
    if (path_to_file)
        result = get_file(path_to_file);
    if  (result != NULL && strcmp(result, "OK") != 0) {
        printf("Error: get my messages: get file with messages\n");  fflush(stdout);
    }  else {

        // read file
        // parse to json array
        // add to db

        char* full_path_to_file = mx_strjoin("./client/", path_to_file);

        FILE* file = fopen(full_path_to_file, "r");
        fseek(file, 0, SEEK_END);
        size_t file_size = ftell(file);
        fseek(file, 0, SEEK_SET);

        char* user_messages_json_str = mx_strnew(file_size);

        fread(user_messages_json_str, sizeof(char), file_size, file);
        
        messages = cJSON_Parse(user_messages_json_str);

        printf("%s\n", cJSON_Print(messages)); fflush(stdout);

        free(full_path_to_file);
    }

    cJSON_Delete(protocol);
    cJSON_Delete(response_file_with_msgs);

    return messages;
}

cJSON* get_all_my_messages(cJSON* cookies) {
    // SUBACTION: GET ALL MSGS
    return get_my_messages(cookies, "GET ALL MSGS");
}

cJSON* get_my_new_messages(cJSON* cookies) {
    // something like get my messages
    // ACTION: GET MESSAGES
    // SUBACTION: GET NEW MSGS
    // SUBACTION: GET FILE WITH MSGS
    return get_my_messages(cookies, "GET NEW MSGS");
}


char *get_start_chat_status(char *response){
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

char* create_start_chat_request(char *username, char* status) {

    char* data = username;

    cJSON* protocol = create_protocol();
    
    cJSON* data_value = cJSON_CreateString(data);
    cJSON* action_value = cJSON_CreateString(status);

    add_to_protocol(protocol, "ACTION", action_value);
    add_to_protocol(protocol, "DATA", data_value);

    char* protocol_str = cJSON_Print(protocol);

    cJSON_Delete(protocol);

    return protocol_str;
}


bool send_start_chat_request(char *username) {
    
    char* request = create_start_chat_request(username, "START_CHAT");
    char* response = send_request(request, get_server_ip(), PORT);

    char* status = get_start_chat_status(response);

    printf("%s\n", response);

    return !strcmp(status, "SUCCESS");
}



