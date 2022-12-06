#include "controller_sign_in.h"

int controller_sign_in(char* user_name, char* password) {

    t_model_user* user = new_model_user(user_name, password);
    int exit_status;
    cJSON* response = send_sign_in_request(user);
    // if(send_sign_in_request(user)){
    //     exit_status = 0;
    // }else {
    //     exit_status = 1;
    // }

    char* status = get_from_protocol_string(response, "STATUS");

    if (status != NULL && strcmp(status, "SUCCESS") == 0) {
        exit_status = 0;
        char* token = get_from_protocol_string(response, "TOKEN");
        generate_cookies(user_name, token);
    } else {
        exit_status = 1;
    }
    cJSON_Delete(response);
    free_model_user(&user);
    return exit_status;
}

void controller_view_user_era(GtkWidget **sign_in_info, t_current_window_info *current_window_info) {

    controller_get_messages();

    t_model_user_data * user_data = send_user_data_request((char *)gtk_entry_get_text(sign_in_info[0]));

    if(user_data->era == STONE_AGE){

        view_stone_age_page(current_window_info );

    } else if (user_data->era == EGYPT){

        view_egypt(current_window_info);

    } else if (user_data->era == MIDDLE_AGES){

        // TODO: add view MIDDLE_AGES era

    } else if (user_data->era == ENLIGHTMENT){
        view_enlightenment_era(current_window_info);

    }else if (user_data->era == MODERN_TIMES){

        view_modern_era(current_window_info);
        
    }

}

