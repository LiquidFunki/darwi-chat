#ifndef CONTROLLER_SIGN_UP_H
#define CONTROLLER_SIGN_UP_H

#include "libmx.h"
#include "model_user.h"
#include "sign_requests.h"
#include "user_data_request.h"
#include "encrypt.h"


int controller_sign_up(char* user_name, char* password);

#endif
