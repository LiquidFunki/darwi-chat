#ifndef DATABASE_H
#define DATABASE_H

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
#include "model_store.h"

typedef struct s_db_array_data {

    void* array;
    bool  first;
    int   size;
    int   capacity;

}              t_db_array_data;

void init_tables();

#define DB "db.sqlite"

sqlite3* get_database();

int callback_print_db(void *not_used, int argc, char **argv, char **azColName);
void init_User_table();
int callback_count(void *not_used, int argc, char **argv, char **azColName);
bool is_user(char *username, char *password);
bool is_new_user(char *username);

t_db_array_data* create_db_array_data();

// User Table
size_t insert_data_user(char *username, char *password);
bool is_verified_user(char* username, char* token);
t_model_user* get_user_by_name(char* username);
size_t get_user_data_id(char *username);
size_t get_user_money_by_username(char *username);
size_t get_user_money_by_user_data_id(size_t user_data_id);
int update_username(char *username, char *new_username);
bool username_is_unique(char* username);

// User Data Table
size_t insert_data_user_data(t_model_user_data* model_user_data);
int update_user_money(char *username, int add_money);
int update_user_avatar(char* username, int avatar_id);
int callback_get_user_size_t(void *data, int argc, char **argv, char **azColName);
int update_user_about(char *username, char *about);
char *get_user_about(char *username);
int callback_get_user_str(void *data, int argc, char **argv, char **azColName);
int update_user_tnumber(char *username, char *tnumber);
char *get_user_tnumber(char *username);
int update_user_email(char *username, char *email);
char *get_user_email(char *username);
t_model_user_data *get_user_data_by_username(char *username);
int callback_get_user_data(void *data, int argc, char **argv, char **azColName);
int update_user_era(char *username, int era);

// Message Table
size_t insert_data_message(t_model_message* model_message);
cJSON* get_all_new_messages_of(char* username);
cJSON* get_all_messages_of(char* username);
cJSON* json_get_all_messages_of(char* username);
cJSON* json_get_new_messages_of(char* username);
int update_message_data(t_model_message* model_message);

t_model_resource *get_resource_by_id(size_t id);
int callback_get_resource(void *data, int argc, char **argv, char **azColName);

int callback_get_user_avatar_id(void *data, int argc, char **argv, char **azColName);
size_t get_user_avatar_id(char *username);

// Resource Table
size_t insert_data_resource(t_model_resource* model_resource);

// Stones Table
size_t insert_data_stone(t_model_stone* model_stone);
t_model_stone *get_stone_by_id(char *id);
int callback_get_stone(void *data, int argc, char **argv, char **azColName) ;

// Store Table
void fill_database_store();
cJSON* get_store_by_era(int era);
int callback_get_store(void *data, int argc, char **argv, char **azColName);
size_t insert_data_store(t_model_store* model_store);
int buy_store_item(char* username, int store_item_id);
int get_store_item_price(int store_item_id);
char* get_bought_items(char* username);
int update_bought_items(char* username, char* bought);

#endif
