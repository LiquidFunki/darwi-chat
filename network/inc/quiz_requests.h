#ifndef QUIZ_REQUESTS_H
#define QUIZ_REQUESTS_H

#include "libmx.h"
#include "cJSON.h"
#include "protocol.h"
#include "send_request.h"

cJSON* get_question_request(cJSON* cookies);
cJSON* check_answer_request(cJSON* cookies, char* selected_answer);

#endif
