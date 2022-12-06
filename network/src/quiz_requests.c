#include "quiz_requests.h"

cJSON* get_question_request(cJSON* cookies) {

    cJSON* protocol = create_protocol();

    add_to_protocol_string(protocol, "FROM", get_from_protocol_string(cookies, "USERNAME"));
    add_to_protocol_string(protocol, "TOKEN", get_from_protocol_string(cookies, "TOKEN"));
    add_to_protocol_string(protocol, "ACTION", "QUIZ");
    add_to_protocol_string(protocol, "SUBACTION", "GET QUESTION");

    char* request = cJSON_Print(protocol);

    char* response = send_request(request, get_server_ip(), PORT);

    cJSON* response_obj = cJSON_Parse(response);

    free(request);
    free(response);
    cJSON_Delete(protocol);

    return response_obj;
}

cJSON* check_answer_request(cJSON* cookies, char* selected_answer) {

    cJSON* protocol = create_protocol();

    add_to_protocol_string(protocol, "FROM", get_from_protocol_string(cookies, "USERNAME"));
    add_to_protocol_string(protocol, "TOKEN", get_from_protocol_string(cookies, "TOKEN"));
    add_to_protocol_string(protocol, "ACTION", "QUIZ");
    add_to_protocol_string(protocol, "SUBACTION", "CHECK ANSWER");
    add_to_protocol_string(protocol, "QUESTION INDEX", get_from_protocol_string(cookies, "QUESTION INDEX"));
    add_to_protocol_string(protocol, "DATA", selected_answer);

    char* request = cJSON_Print(protocol);

    char* response = send_request(request, get_server_ip(), PORT);

    cJSON* response_obj = cJSON_Parse(response);

    free(request);
    free(response);
    cJSON_Delete(protocol);

    return response_obj;

}

