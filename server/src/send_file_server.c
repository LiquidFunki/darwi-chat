#include "send_file_server.h"

char* send_file_server(char* request) {

    cJSON* request_protocol = cJSON_Parse(request);

    char* path_to_file = get_from_protocol_string(request_protocol, "DATA");
    size_t index       = get_from_protocol_number(request_protocol, "FILE INDEX");

    

    char* full_path = mx_strjoin("./server", path_to_file);
    printf("full path: %s\n", full_path);
    FILE* file = fopen(full_path, "r");
    if (file == NULL) {
        printf("No such file. send file server\n");
    }
    fseek(file, index, SEEK_CUR);
    
    size_t read_number = 0;
    char* file_part = create_file_part_data(file, &read_number);
    
    fclose(file);
    
    cJSON* response_protocol = create_protocol();
    if (read_number != 0 && file_part != NULL) {
        index += read_number;
        add_to_protocol_string(response_protocol, "ACTION", "SAVE FILE");
        add_to_protocol_string(response_protocol, "PATH TO FILE", mx_strjoin("./client/", path_to_file));
        add_to_protocol_number(response_protocol, "FILE PART SIZE", read_number);
        add_to_protocol_number(response_protocol, "FILE INDEX", index);
        add_to_protocol_string(response_protocol, "DATA", file_part);
    } else {
        add_to_protocol_string(response_protocol, "ACTION", "FILE END");
    }
   

    char* response = cJSON_Print(response_protocol);

    free(full_path);
    cJSON_Delete(request_protocol);
    cJSON_Delete(response_protocol);
    return response;
}
