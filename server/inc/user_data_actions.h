#ifndef USER_DATA_ACTIONS_H
#define USER_DATA_ACTIONS_H

#include "cJSON.h"
#include "libmx.h"
#include "string.h"
#include "protocol.h"
#include "database.h"
#include "file_for_write.h"


bool get_user_data(char *request, char *response);
bool get_user_data_money(char *request, char *response);
bool set_user_about_subaction(char *request, char *response);
bool set_user_tnumber_subaction(char *request, char *response);
bool set_user_email_subaction(char *request, char *response);
void get_store_subaction(char *request, char *response);
bool buy_subaction(char *request, char *response);
bool get_user_data_money(char *request, char *response);
bool get_user_data_money_by_username(char *request, char *response);
bool set_user_era_subaction(char *request, char *response);

#endif

