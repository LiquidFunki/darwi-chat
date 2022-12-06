#ifndef USER_DATA_REQUEST_H
#define USER_DATA_REQUEST_H


#include "model_user.h"
#include "cJSON.h"
#include "send_request.h"
#include "protocol.h"
#include "model_user_data.h"
#include "model_store.h"

t_model_user_data* send_user_data_request(char *username);
void send_set_user_about_request(char* username, char *token, char* about);
void send_set_user_tnumber_request(char* username, char *token, char* t_number);
void send_set_user_email_request(char* username, char *token, char* email);
t_model_store** send_store_request(int era);
void send_buy_request(char* username, char *token, int store_item_id);
size_t send_money_request(size_t user_data_id);
size_t send_money_request_by_username(char* username);
void send_set_user_era_request(char* username, char *token, int era);

#endif
