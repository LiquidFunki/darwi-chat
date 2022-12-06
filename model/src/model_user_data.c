#include "model_user_data.h"

t_model_user_data* new_model_user_data() {

    t_model_user_data* model_user_data = (t_model_user_data*)malloc(sizeof(t_model_user_data));

    model_user_data->about =    mx_strnew(ABOUT_SIZE);
    model_user_data->email =    mx_strnew(EMAIL_SIZE);
    model_user_data->t_number = mx_strnew(T_NUMBER_SIZE);
    model_user_data->id       = 0;
    model_user_data->era      = STONE_AGE;
    model_user_data->status   = ONLINE;
    model_user_data->money    = 0;
    model_user_data->avatar_id= 1;
    model_user_data->bought_items = mx_strnew(BUFSIZ);
    strcpy(model_user_data->bought_items, "[]");
    
    return model_user_data;
}


char*         to_string_model_user_data(t_model_user_data* model_user_data) {

    cJSON* user_data = cJSON_CreateObject();

    add_to_protocol_string(user_data, "about", model_user_data->about);
    add_to_protocol_string(user_data, "email", model_user_data->email);
    add_to_protocol_string(user_data, "t_number", model_user_data->t_number);
    add_to_protocol_number(user_data, "id", model_user_data->id);
    add_to_protocol_number(user_data, "era", model_user_data->era);
    add_to_protocol_number(user_data, "status", model_user_data->status);
    add_to_protocol_number(user_data, "money", model_user_data->money);
    add_to_protocol_number(user_data, "avatar_id", model_user_data->money);
    add_to_protocol_string(user_data, "bought_items", model_user_data->bought_items);

    char* user_data_str = cJSON_Print(user_data);
    cJSON_Delete(user_data);

    return user_data_str;
}

t_model_user_data* from_string_model_user_data(char* json) {

    cJSON* user_data = cJSON_Parse(json);

    char* about    = get_from_protocol_string(user_data, "about");
    char* email    = get_from_protocol_string(user_data, "email");
    char* t_number = get_from_protocol_string(user_data, "t_number");
    char* bought_items = get_from_protocol_string(user_data, "bought_items");

    t_model_user_data* model_user_data = new_model_user_data();

    strcpy(model_user_data->about, about);
    strcpy(model_user_data->email, email);
    strcpy(model_user_data->t_number, t_number);
    strcpy(model_user_data->bought_items, bought_items);

    model_user_data->id = get_from_protocol_number(user_data, "id");
    model_user_data->era = (int)get_from_protocol_number(user_data, "era");
    model_user_data->status = (int)get_from_protocol_number(user_data, "status");
    model_user_data->money = (size_t)get_from_protocol_number(user_data, "money");
    model_user_data->avatar_id = (size_t)get_from_protocol_number(user_data, "avatar_id");

    cJSON_Delete(user_data);

    return model_user_data;
}
void          free_model_user_data(t_model_user_data** model_user_data) {

    free((*model_user_data)->about);
    free((*model_user_data)->email);
    free((*model_user_data)->t_number);

    free(*model_user_data);
    *model_user_data = NULL;
}
