
#include "get_file.h"

char* get_file(char* path_to_file) {
    
    char* response = mx_strnew(READ_SIZE);

    size_t file_index = 0;

    while ( true )
    {   
        cJSON* protocol = create_protocol();
        add_to_protocol_string(protocol, "ACTION", "GET FILE");
        add_to_protocol_number(protocol, "FILE INDEX", file_index);
        add_to_protocol_string(protocol, "DATA", path_to_file);
        char* request = cJSON_Print(protocol);

        response = send_request(request, get_server_ip(), PORT);
        
        // printf("%s\n", response);
        // fflush(stdout);

        cJSON* response_protocol = cJSON_Parse(response);

        if (response_protocol == NULL) {

            printf("parse error responce. get file\n");
            break;
        }

        char* action = get_from_protocol_string(response_protocol, "ACTION");

        if (action == NULL) {
            printf("parse error action. get file\n");
            break;
        }

        if (strcmp(action, "FILE END") == 0) {
            printf("file end.\n");
            break;
        }

        size_t unscreened_size = 0;
        save_file_client(response, &unscreened_size);

        file_index += unscreened_size;

        cJSON_Delete(protocol);
        free(request);
        cJSON_Delete(response_protocol);
        free(response);
    }

    // free(request);
    return "OK";
}

// TODO: файлы лежат зеркально на сервере и клиенте
char* save_file_client(char* response, size_t* unscreened_size) {


    char* path_to_file = NULL;

    cJSON* request_obj = cJSON_Parse(response);

    cJSON* path_to_file_obj = cJSON_GetObjectItemCaseSensitive(request_obj, "PATH TO FILE");
    path_to_file = path_to_file_obj->valuestring;
    FILE* file = fopen(path_to_file, "a");

    if (file == NULL) {
        char* create_file_command = "touch ";
        create_file_command = mx_strjoin(create_file_command, path_to_file);
        system(create_file_command);
        file = fopen(path_to_file, "a");
    }

    cJSON* file_data_obj = cJSON_GetObjectItemCaseSensitive(request_obj, "DATA");
    cJSON* screened_file_size_obj = cJSON_GetObjectItemCaseSensitive(request_obj, "FILE PART SIZE");


    char* file_data_unscreened = unscreen_file(file_data_obj->valuestring, screened_file_size_obj->valueint, unscreened_size);


    fwrite(file_data_unscreened, sizeof(char), *unscreened_size, file);
    fclose(file);

    cJSON_Delete(request_obj);

    return response;
}
