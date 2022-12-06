#include "sign.h"

bool sign_up(char* request, char *response) {

    bool result = false;

    cJSON* request_obj = cJSON_Parse(request);

    cJSON* user_json = cJSON_GetObjectItemCaseSensitive(request_obj, "DATA");
    char* user_str = user_json->valuestring;

    t_model_user* user = from_string_model_user(user_str);
    char* encrypted_password = encrypt_pswd(user->password);
    free(user->password);
    // user->password = encrypt_pswd(user->password);
    user->password = encrypted_password;
    cJSON *sign_up_status = create_protocol();
    // add to db
    if (is_new_user(user->name)) {
        insert_data_user(user->name, user->password);
        result = true;
        add_to_protocol_string(sign_up_status, "STATUS", "SUCCESS");
    } else {
        result = false;
        add_to_protocol_string(sign_up_status, "STATUS", "ERORR");
    }
    strcpy(response, cJSON_Print(sign_up_status));




    printf("User: id: %i, username: %s password: %s\n", user->id, user->name, user->password);
    fflush(stdout);
    
    cJSON_Delete(sign_up_status);
    cJSON_Delete(request_obj);
    // cJSON_Delete(user_json);
    free_model_user(&user);

    return result;
}

bool sign_in(char* request, char *response) {
    bool result = false;


    cJSON* request_obj = cJSON_Parse(request);
    if(request_obj == NULL){
        perror("parse error sign in");
    }

    cJSON* user_json = cJSON_GetObjectItemCaseSensitive(request_obj, "DATA");
    if(request_obj == NULL){
        perror("get obj error sign in");
    }
    char* user_str = user_json->valuestring;

    t_model_user* user = from_string_model_user(user_str);
    user->password = encrypt_pswd(user->password);
    // TODO: use hash
    char* token = user->password;

    cJSON *sign_in_status = create_protocol();

    // check user in db
        // perror("THERE");

    if (is_user(user->name, user->password)) {
        add_to_protocol_string(sign_in_status, "STATUS", "SUCCESS");
        add_to_protocol_string(sign_in_status, "TOKEN", token);
        result = true;
    } else {
        result = false;
        add_to_protocol_string(sign_in_status, "STATUS", "ERROR");
    }

    strcpy(response, cJSON_Print(sign_in_status));


    printf("User: id: %i, username: %s password: %s\n", user->id, user->name, user->password);

    cJSON_Delete(request_obj);
    cJSON_Delete(sign_in_status);
    // cJSON_Delete(user_json);
    free_model_user(&user);

    return result;

}

