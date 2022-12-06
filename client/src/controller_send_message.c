#include "controller_send_message.h"

t_model_message *controller_send_message(char* to, e_message_data_types data_type, char* data) {

    if (to != NULL) {
        t_model_message* model_message = new_model_message();

        cJSON* protocol = create_protocol();
        add_to_protocol_string(protocol, "FROM", get_from_protocol_string(get_cookies(), "USERNAME"));
        add_to_protocol_string(protocol, "TOKEN", get_from_protocol_string(get_cookies(), "TOKEN"));


        strcpy(model_message->from_user, get_from_protocol_string(get_cookies(), "USERNAME"));
        strcpy(model_message->to_user, to);
        model_message->data_type = data_type;

        strcpy(model_message->data, data);

        char* response = send_message(model_message, protocol);
        
        t_model_message * model_message_tmp = from_string_model_message(get_from_protocol_string(cJSON_Parse(response), "DATA"));

        if(model_message_tmp->data_type == MESSAGE_FILE){
            t_model_resource *file_to_save = send_get_resource_request(model_message_tmp->data);
            insert_data_resource(file_to_save);
            free_model_resource(&file_to_save);
        } else if (model_message_tmp->data_type == MESSAGE_STONE){
            t_model_stone *model_stone = send_get_stone_request(model_message_tmp->data);
            insert_data_stone(model_stone);
            // request_file_if_not_exist(mx_replace_substr(model_stone->path, "./server", "./client")); // TODO: Kastyl' ?
            free_model_stone(&model_stone);
        }


        insert_data_message(model_message_tmp);


        

        return model_message_tmp;
    }
    else{
        return NULL;
    }
}

 t_model_message *controller_forward_message(char* to, e_message_data_types data_type, char* data, char *forward_from) {

    if (to != NULL) {
        t_model_message* model_message = new_model_message();

        cJSON* protocol = create_protocol();
        add_to_protocol_string(protocol, "FROM", get_from_protocol_string(get_cookies(), "USERNAME"));
        add_to_protocol_string(protocol, "TOKEN", get_from_protocol_string(get_cookies(), "TOKEN"));


        strcpy(model_message->from_user, get_from_protocol_string(get_cookies(), "USERNAME"));
        strcpy(model_message->to_user, to);
        strcpy(model_message->forward_from, forward_from);

        model_message->data_type = data_type;

        strcpy(model_message->data, data);

        char* response = send_message(model_message, protocol);
        
        t_model_message * model_message_tmp = from_string_model_message(get_from_protocol_string(cJSON_Parse(response), "DATA"));

        t_model_resource *file_to_save = send_get_resource_request(model_message_tmp->data);
        
        insert_data_resource(file_to_save);

        free_model_resource(&file_to_save);

        insert_data_message(model_message_tmp);


        

        return model_message_tmp;
    }
    else
        return NULL;
    
}