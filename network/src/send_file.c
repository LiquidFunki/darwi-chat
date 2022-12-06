#include "send_file.h"

char* get_file_for_write(char* ip, int port) {

    cJSON* protocol = create_protocol();
    
    cJSON* action_value = cJSON_CreateString("GET FILE FOR WRITE");
    add_to_protocol(protocol, "ACTION", action_value);

    char* request = cJSON_Print(protocol);

    char* response = send_request(request, ip, port);
    return response;
}

char* create_file_part_data(FILE* file, size_t* read_number) {


    char* file_data = mx_strnew(BUFFER_SIZE);
    *read_number = 0;

    *read_number = fread(file_data, sizeof(char), BUFFER_SIZE - 1, file);

    if (*read_number <= 0) {
        free(file_data);
        return NULL;
    }

    printf("readed number = %zu\n", *read_number);
    
    size_t screened_size = 0;
    char* file_part = screen_file(file_data, *read_number, &screened_size);

    *read_number = screened_size;
    free(file_data);

    return file_part;
}

char* send_file(char* path_to_file, char* after_file_request, char* ip, int port) {

    char* file_for_write_response = get_file_for_write(ip, port);


    FILE* file = fopen(path_to_file, "r");
    if (file == NULL) {
        perror("Send File Error: ");
        return NULL;
    }

    char* file_part = NULL;
    size_t file_part_size = 0;

    while( (file_part = create_file_part_data(file, &file_part_size)) != NULL) {

        cJSON* protocol = create_protocol();
        
        cJSON* path_to_file_value = cJSON_CreateString(file_for_write_response);
        cJSON* action_value = cJSON_CreateString("SAVE FILE"); 
        add_to_protocol(protocol, "ACTION", action_value);
        cJSON* file_part_value = cJSON_CreateNumber(file_part_size);
        add_to_protocol(protocol, "FILE PART SIZE", file_part_value);
        add_to_protocol(protocol, "PATH TO FILE", path_to_file_value);
        cJSON* data_value = cJSON_CreateString(file_part);
        add_to_protocol(protocol, "DATA", data_value);

        char* protocol_str = cJSON_Print(protocol);
        send_request(protocol_str, ip, port);

        free(protocol_str);
        free(file_part);
        cJSON_Delete(protocol);
    }
    
    char* end_file_request = NULL;

    cJSON* path_to_file_value = cJSON_CreateString(file_for_write_response);
    cJSON* protocol = create_protocol();
    cJSON* action_value = cJSON_CreateString("FILE END");
    cJSON* data_value = cJSON_CreateString(after_file_request);


    add_to_protocol(protocol, "DATA", data_value);
    add_to_protocol(protocol, "ACTION", action_value);
    add_to_protocol(protocol, "PATH TO FILE", path_to_file_value);


    end_file_request = cJSON_Print(protocol);

    cJSON_Delete(protocol);

    char* response = send_request(end_file_request, ip, port);

    return response;
}
