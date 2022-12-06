#ifndef SIGN_UP_REQUEST_H
#define SIGN_UP_REQUEST_H


#include "model_user.h"
#include "cJSON.h"
#include "send_request.h"
#include "protocol.h"

char* create_sign_request(t_model_user* model_user, char* action);

bool send_sign_up_request(t_model_user* model_user);
cJSON* send_sign_in_request(t_model_user* model_user);

#endif
