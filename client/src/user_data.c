#include "user_data.h"

static cJSON* cookies = NULL;

// void generate_cookies() {


//     cookies = cJSON_CreateObject();

//     add_to_protocol_string(cookies, "USERNAME", "");
//     add_to_protocol_string(cookies, "TOKEN",    "");

// }


void generate_cookies(char *user, char *password) {


    cookies = cJSON_CreateObject();

    add_to_protocol_string(cookies, "USERNAME", user);
    add_to_protocol_string(cookies, "TOKEN",    password);

}

cJSON* get_cookies() {

    return cookies;

}