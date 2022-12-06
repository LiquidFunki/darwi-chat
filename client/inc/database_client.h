#ifndef DATABASE_CLIENT_H
#define DATABASE_CLIENT_H

#include <sqlite3.h>
#include <libmx.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#include "model_user.h"
#include "model_user_data.h"
#include "model_message.h"
#include "model_resource.h"
#include "model_stone.h"

#include "controller_send_message.h"

#include "user_data.h"

typedef struct s_db_array_data {

    void* array;
    bool  first;
    int   size;
    int   capacity;

}              t_db_array_data;

void init_tables();

#define DB "db_client.sqlite"

int callback_print_db(void *not_used, int argc, char **argv, char **azColName);
int callback_count(void *not_used, int argc, char **argv, char **azColName);
bool is_user(char *username, char *password);
bool is_new_user(char *username);

t_db_array_data* create_db_array_data();

// User Table
size_t insert_data_user(char *username, char *password);
bool is_verified_user(char* username, char* token);
t_model_user* get_user_by_name(char* username);

// User Data Table
size_t insert_data_user_data(t_model_user_data* model_user_data);

// Message Table
size_t insert_data_message(t_model_message* model_message); 
t_model_message** get_all_messages_from_chat(char *from_user, int *size);

int callback_get_user_chats(void *data, int argc, char **argv, char **azColName);
char** get_all_user_chats(char *current_user, int *count);
void update_message(t_model_message* new_data);


// Resource Table
size_t insert_data_resource(t_model_resource* model_resource);
t_model_resource *get_resource_by_id(char *id);
int callback_get_resource(void *data, int argc, char **argv, char **azColName);


// Stones Table
size_t insert_data_stone(t_model_stone* model_stone);
t_model_stone *get_stone_by_id(char *id);
int callback_get_stone(void *data, int argc, char **argv, char **azColName);
t_model_message *get_stone_message_from_chat(char *from_user, int *size);

int callback_get_message(void *data, int argc, char **argv, char **azColName);
t_model_message* get_message_by_id(size_t msg_id);

#endif
