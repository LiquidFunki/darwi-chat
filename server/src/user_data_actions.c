#include "user_data_actions.h"

bool get_user_data(char *request, char *response) {
    cJSON *get_user_data_response = create_protocol();

    cJSON *request_cjson = cJSON_Parse(request);

    char *username = get_from_protocol_string(request_cjson, "DATA");
    
    size_t user_data_id = get_user_data_id(username);
    
    t_model_user_data *model_user_data = get_user_data_by_username(username);

    add_to_protocol_string(get_user_data_response, "DATA", to_string_model_user_data(model_user_data));

    strcpy(response, cJSON_Print(get_user_data_response));

    printf("%s\n", response);
    fflush(stdout);

    return true;
}

bool get_user_data_money(char *request, char *response) {
    cJSON *get_user_data_response = create_protocol();

    cJSON *request_cjson = cJSON_Parse(request);

    size_t user_data_id = get_from_protocol_number(request_cjson, "DATA");
    
    int money = get_user_money_by_user_data_id(user_data_id);

    add_to_protocol_number(get_user_data_response, "DATA", money);

    strcpy(response, cJSON_Print(get_user_data_response));

    printf("%s\n", response);
    fflush(stdout);

    return true;
}

bool get_user_data_money_by_username(char *request, char *response) {
    cJSON *get_user_data_response = create_protocol();

    cJSON *request_cjson = cJSON_Parse(request);

    char* username = get_from_protocol_string(request_cjson, "DATA");
    
    int money = get_user_money_by_username(username); 

    add_to_protocol_number(get_user_data_response, "DATA", money);

    strcpy(response, cJSON_Print(get_user_data_response));

    printf("%s\n", response);
    fflush(stdout);

    return true;
}

bool set_user_about_subaction(char *request, char *response) {
    cJSON *get_user_data_response = create_protocol();

    cJSON *request_cjson = cJSON_Parse(request);

    char* about = get_from_protocol_string(request_cjson, "DATA");
    char* username = get_from_protocol_string(request_cjson, "USERNAME");
    char* token = get_from_protocol_string(request_cjson, "TOKEN");

    if (is_verified_user(username, token))
        update_user_about(username, about);

    strcpy(response, cJSON_Print(get_user_data_response));

    printf("%s\n", response);
    fflush(stdout);
    
    return true;
}

bool set_user_tnumber_subaction(char *request, char *response) {
    cJSON *get_user_data_response = create_protocol();

    cJSON *request_cjson = cJSON_Parse(request);

    char* t_number = get_from_protocol_string(request_cjson, "DATA");
    char* username = get_from_protocol_string(request_cjson, "USERNAME");
    char* token = get_from_protocol_string(request_cjson, "TOKEN");

    if (is_verified_user(username, token))
        update_user_tnumber(username, t_number);

    strcpy(response, cJSON_Print(get_user_data_response));

    printf("%s\n", response);
    fflush(stdout);

    return true;
}

bool set_user_email_subaction(char *request, char *response) {
    cJSON *get_user_data_response = create_protocol();

    cJSON *request_cjson = cJSON_Parse(request);

    char* email = get_from_protocol_string(request_cjson, "DATA");
    char* username = get_from_protocol_string(request_cjson, "USERNAME");
    char* token = get_from_protocol_string(request_cjson, "TOKEN");

    if (is_verified_user(username, token))
        update_user_email(username, email);

    strcpy(response, cJSON_Print(get_user_data_response));

    printf("%s\n", response);
    fflush(stdout);

    return true;
}

void get_store_subaction(char *request, char *response) {
    cJSON* get_store_response = create_protocol();

    cJSON* request_cjson = cJSON_Parse(request);

    int era = get_from_protocol_number(request_cjson, "DATA");

    cJSON* store = get_store_by_era(era);
    char* store_array_str = cJSON_Print(store);

    add_to_protocol_string(get_store_response, "DATA", store_array_str);
    
    char* response_buff = cJSON_Print(get_store_response);
    strcpy(response, response_buff);
    
    free(response_buff);
    free(store_array_str);

    printf("%s\n", response);
    fflush(stdout);
}

bool buy_subaction(char *request, char *response) {
    cJSON *get_store_response = create_protocol();

    cJSON *request_cjson = cJSON_Parse(request);

    int store_item_id = get_from_protocol_number(request_cjson, "DATA");
    
    char* username = get_from_protocol_string(request_cjson, "USERNAME");
    char* token = get_from_protocol_string(request_cjson, "TOKEN");

    char* bought_current_str = get_bought_items(username);
    cJSON* bought_current_json_array = cJSON_CreateArray();
    bought_current_json_array = cJSON_Parse(bought_current_str);
    bought_current_str = cJSON_Print(bought_current_json_array);

    if (is_verified_user(username, token)){
        int bought = buy_store_item(username, store_item_id);
        if (bought == 1)
            add_to_protocol_string(get_store_response, "STATUS", "ERROR");
        else {
            add_to_protocol_string(get_store_response, "STATUS", "SUCCESS");
            cJSON* last_bought_id = cJSON_Parse(mx_itoa(store_item_id));  
            cJSON_AddItemToArray(bought_current_json_array, last_bought_id);
            free(bought_current_str);
            bought_current_str = cJSON_Print(bought_current_json_array);

            update_bought_items(username, bought_current_str);
        }    
    }

    add_to_protocol_string(get_store_response, "DATA", bought_current_str);
    
    strcpy(response, cJSON_Print(get_store_response));

    printf("%s\n", response);
    fflush(stdout);

    return true;
}

bool set_user_era_subaction(char *request, char *response) {
    cJSON *get_user_data_response = create_protocol();

    cJSON *request_cjson = cJSON_Parse(request);

    int era = get_from_protocol_number(request_cjson, "DATA");
    char* username = get_from_protocol_string(request_cjson, "USERNAME");
    char* token = get_from_protocol_string(request_cjson, "TOKEN");

    if (is_verified_user(username, token))
        update_user_era(username, era);

    strcpy(response, cJSON_Print(get_user_data_response));

    printf("%s\n", response);
    fflush(stdout);

    return true;
}
