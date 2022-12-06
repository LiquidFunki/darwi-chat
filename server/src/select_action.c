#include "select_action.h"

int select_action(char* request, char* response) {

    // *response = NULL;


    cJSON* request_obj = cJSON_Parse(request);

    if (request_obj == NULL) {
        printf("parse error\n");
        return 1;
    }

    cJSON* action_obj = cJSON_GetObjectItemCaseSensitive(request_obj, "ACTION");
    if (action_obj == NULL) {
        printf("action obj error\n");
        return 1;
    }
    char* action = action_obj->valuestring;

    if ( strcmp(action, "SIGN UP") == 0 ) {

        sign_up(request, response);

    }

    else if ( strcmp(action, "SIGN IN") == 0 ) {

        sign_in(request, response);

    } else if ( strcmp(action, "SET AVATAR") == 0 ) {
        
        char* response_buff = set_avatar(request_obj);
        strcpy(response, response_buff);
        free(response_buff);
    
    } else if ( strcmp(action, "GET FILE FOR WRITE") == 0 ) {

        file_for_write(response);
    
    } else if ( strcmp(action, "SAVE FILE") == 0 ) {

        save_file(request, response);
    
    } else if ( strcmp(action, "FILE END") == 0 ) {

        file_end(request, response);

    } else if (strcmp(action, "GET FILE") == 0) {
        
        char* response_buff = send_file_server(request);
        strcpy(response, response_buff);
        free(response_buff);

    } else if (strcmp(action, "SEND MSG") == 0) {
        
        char* response_buff = add_message(request_obj);
        strcpy(response, response_buff);
        free(response_buff);
             
    } else if (strcmp(action, "GET MSGS") == 0) {

        char* response_buff = get_messages(request_obj);
        strcpy(response, response_buff);
        free(response_buff);

    } else if ( strcmp(action, "QUIZ" ) == 0 ) {

        // subaction: get question, check answer
        char* response_buff = quiz_server(request_obj);
        strcpy(response, response_buff);
        free(response_buff);

    } else if ( strcmp(action, "START_CHAT" ) == 0 ) {

        start_chat(request, response);

    } else if ( strcmp(action, "GET_AVATAR" ) == 0) {

        get_avatar(request, response);

    } else if ( strcmp(action, "GET_RESOURCE" ) == 0) {

        get_resource(request, response);

    } else if ( strcmp(action, "GET_STONE" ) == 0) {

        get_stone(request, response);

    } else if ( strcmp(action, "GET_USER_DATA" ) == 0) {
        char *subaction = get_from_protocol_string(request_obj, "SUBACTION");

        if (!subaction)
            get_user_data(request, response);
        else if (strcmp(subaction, "GET_USER_MONEY") == 0) 
            get_user_data_money(request, response);
        else if (strcmp(subaction, "GET_USER_MONEY_BY_USERNAME") == 0) 
            get_user_data_money_by_username(request, response);
    } else if (strcmp(action, "SET_USER_DATA") == 0) {
        char *subaction = get_from_protocol_string(request_obj, "SUBACTION");
        
        if (strcmp(subaction, "SET_USER_ABOUT") == 0) 
            set_user_about_subaction(request, response);
        else if (strcmp(subaction, "SET_USER_TNUMBER") == 0) 
            set_user_tnumber_subaction(request, response);
        else if (strcmp(subaction, "SET_USER_EMAIL") == 0) 
            set_user_email_subaction(request, response);
        else if (strcmp(subaction, "SET_USER_ERA") == 0) 
            set_user_era_subaction(request, response);
    } else if (strcmp(action, "STORE") == 0) {
        char *subaction = get_from_protocol_string(request_obj, "SUBACTION");
        
        if (strcmp(subaction, "GET_STORE") == 0) 
            get_store_subaction(request, response);
        else if (strcmp(subaction, "BUY") == 0) 
            buy_subaction(request, response);
    }

    cJSON_Delete(request_obj);

    return 0;
}
