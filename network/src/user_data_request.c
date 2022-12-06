#include "user_data_request.h"

t_model_user_data* send_user_data_request(char *username) {

    cJSON* protocol = create_protocol();

    add_to_protocol_string(protocol, "ACTION", "GET_USER_DATA");

    add_to_protocol_string(protocol, "DATA", username);
    
    char* request = cJSON_Print(protocol);
    
    char* response = send_request(request, get_server_ip(), PORT);

    cJSON* response_user_data_model = cJSON_Parse(response);

    t_model_user_data *model_user_data = new_model_user_data();

    model_user_data = from_string_model_user_data(get_from_protocol_string(response_user_data_model, "DATA"));

   return model_user_data;
}

size_t send_money_request(size_t user_data_id) {

    cJSON* protocol = create_protocol();

    add_to_protocol_string(protocol, "ACTION", "GET_USER_DATA");
    add_to_protocol_string(protocol, "SUBACTION", "GET_USER_MONEY");

    add_to_protocol_number(protocol, "DATA", user_data_id);
    
    char* request = cJSON_Print(protocol);
    
    char* response = send_request(request, get_server_ip(), PORT);

    cJSON* response_money = cJSON_Parse(response);

    size_t money = get_from_protocol_number(response_money, "DATA");

   return money;
}

size_t send_money_request_by_username(char* username) {

    cJSON* protocol = create_protocol();

    add_to_protocol_string(protocol, "ACTION", "GET_USER_DATA");
    add_to_protocol_string(protocol, "SUBACTION", "GET_USER_MONEY_BY_USERNAME");

    add_to_protocol_string(protocol, "DATA", username);
    
    char* request = cJSON_Print(protocol);
    
    char* response = send_request(request, get_server_ip(), PORT);

    cJSON* response_money = cJSON_Parse(response);

    size_t money = get_from_protocol_number(response_money, "DATA");

   return money;
}

void send_set_user_about_request(char* username, char *token, char* about) {

    cJSON* protocol = create_protocol();

    add_to_protocol_string(protocol, "ACTION", "SET_USER_DATA");
    add_to_protocol_string(protocol, "SUBACTION", "SET_USER_ABOUT");

    add_to_protocol_string(protocol, "USERNAME", username);
    add_to_protocol_string(protocol, "TOKEN", token);
    add_to_protocol_string(protocol, "DATA", about);
    
    char* request = cJSON_Print(protocol);
    
    char* response = send_request(request, get_server_ip(), PORT);
    free(response);
}

void send_set_user_tnumber_request(char* username, char *token, char* t_number) {

    cJSON* protocol = create_protocol();

    add_to_protocol_string(protocol, "ACTION", "SET_USER_DATA");
    add_to_protocol_string(protocol, "SUBACTION", "SET_USER_TNUMBER");

    add_to_protocol_string(protocol, "USERNAME", username);
    add_to_protocol_string(protocol, "TOKEN", token);
    add_to_protocol_string(protocol, "DATA", t_number);
    
    char* request = cJSON_Print(protocol);
    
    char* response = send_request(request, get_server_ip(), PORT);
    free(response);
}

void send_set_user_email_request(char* username, char *token, char* email) {

    cJSON* protocol = create_protocol();

    add_to_protocol_string(protocol, "ACTION", "SET_USER_DATA");
    add_to_protocol_string(protocol, "SUBACTION", "SET_USER_EMAIL");

    add_to_protocol_string(protocol, "USERNAME", username);
    add_to_protocol_string(protocol, "TOKEN", token);
    add_to_protocol_string(protocol, "DATA", email);
    
    char* request = cJSON_Print(protocol);
    
    char* response = send_request(request, get_server_ip(), PORT);
    free(response);
}

t_model_store** send_store_request(int era) {
    t_model_store** model_store = (t_model_store**)malloc(sizeof(t_model_store*) * 6);

    cJSON* protocol = create_protocol();

    add_to_protocol_string(protocol, "ACTION", "STORE");
    add_to_protocol_string(protocol, "SUBACTION", "GET_STORE");

    add_to_protocol_number(protocol, "DATA", era);
    
    char* request = cJSON_Print(protocol);
    char* response = send_request(request, get_server_ip(), PORT);
   
    cJSON* response_store = cJSON_Parse(response);
    char* store_str = get_from_protocol_string(response_store, "DATA");
    cJSON* array_of_data = cJSON_Parse(store_str);


    int size = 6;
    if (era == 4) size = 1;

    for (int i = 0; i < size; i++) {
        cJSON* item = cJSON_GetArrayItem(array_of_data, i);
        model_store[i] = from_string_model_store(item->valuestring);
    }

   return model_store;
}

void send_buy_request(char* username, char *token, int store_item_id) {

    cJSON* protocol = create_protocol();

    add_to_protocol_string(protocol, "ACTION", "STORE");
    add_to_protocol_string(protocol, "SUBACTION", "BUY");

    add_to_protocol_string(protocol, "USERNAME", username);
    add_to_protocol_string(protocol, "TOKEN", token);
    add_to_protocol_number(protocol, "DATA", store_item_id);
    
    char* request = cJSON_Print(protocol);
    
    char* response = send_request(request, get_server_ip(), PORT);
    cJSON *bought_array = cJSON_Parse(get_from_protocol_string(cJSON_Parse(response), "DATA"));
    printf("\n\n\n THERE %s\n\n\n ", cJSON_Print(bought_array));

    free(response);
}

void send_set_user_era_request(char* username, char *token, int era) {

    cJSON* protocol = create_protocol();

    add_to_protocol_string(protocol, "ACTION", "SET_USER_DATA");
    add_to_protocol_string(protocol, "SUBACTION", "SET_USER_ERA");

    add_to_protocol_string(protocol, "USERNAME", username);
    add_to_protocol_string(protocol, "TOKEN", token);
    add_to_protocol_number(protocol, "DATA", era);
    
    char* request = cJSON_Print(protocol);
    
    char* response = send_request(request, get_server_ip(), PORT);

    free(response);
}

