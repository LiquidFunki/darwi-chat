#include "model_user.h"

t_model_user* new_model_user(char* name, char* password) {

    t_model_user* model_user = (t_model_user*)malloc(sizeof(t_model_user));
    model_user->id = 0;
    model_user->name = mx_strdup(name);
    model_user->password = mx_strdup(password);
    model_user->user_data_id = 0;

    return model_user;
}

char*         to_string_model_user(t_model_user* model_user) {

    cJSON* user = cJSON_CreateObject();

    add_to_protocol_string(user, "name", model_user->name);
    add_to_protocol_string(user, "password", model_user->password);
    add_to_protocol_number(user, "id", model_user->id);
    add_to_protocol_number(user, "user_data_id", model_user->user_data_id);

    char* user_str = cJSON_Print(user);
    cJSON_Delete(user);
    return user_str;
}

t_model_user* from_string_model_user(char* string) {

    cJSON* user = cJSON_Parse(string);
    char* name = get_from_protocol_string(user, "name");
    char* password = get_from_protocol_string(user, "password");

    t_model_user* model_user = new_model_user(name, password);

    model_user->id = get_from_protocol_number(user, "id");
    model_user->user_data_id = get_from_protocol_number(user, "user_data_id");


    cJSON_Delete(user);

    return model_user;
}

void          free_model_user(t_model_user** model_user) {
    free((*model_user)->name);
    free((*model_user)->password);
    free(*model_user);
    *model_user = NULL;
}
