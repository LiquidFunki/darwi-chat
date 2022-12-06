#include "database_client.h"

size_t insert_data_message(t_model_message* model_message) {

    sqlite3 *db;
    
    int err_status = 0;

    if((err_status = sqlite3_open(DB, &db)) != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }

    char *insert_request = "INSERT INTO Messages(Id, FromUser, ToUser, Type, Data, Date, Status, ForwardFrom) VALUES('%i', '%s', '%s', %i, '%s', '%s', %i, '%s');";
    char *sql_query = NULL;
    char *err_msg = NULL;
    asprintf(&sql_query, insert_request, model_message->id, model_message->from_user, model_message->to_user, model_message->data_type, model_message->data, model_message->date, model_message->status, model_message->forward_from);

    if((err_status = sqlite3_exec(db, sql_query, callback_print_db, 0, &err_msg)) != SQLITE_OK) {
        fprintf(stderr, "SQL_error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return 0;
        // exit(1);
    }

    size_t message_id = sqlite3_last_insert_rowid(db);
    sqlite3_close(db);

    return message_id;

}

int callback_get_messages(void *data, int argc, char **argv, char **azColName) {
    t_db_array_data* db_array_data = (t_db_array_data*)data;

    if (db_array_data->first) {
        db_array_data->capacity = 10;
        db_array_data->array = malloc(sizeof(t_model_message*) * db_array_data->capacity);
        db_array_data->first = false;
    }

    if (db_array_data->size == db_array_data->capacity) {
        db_array_data->capacity += 10;
        db_array_data->array = realloc((t_model_message**)db_array_data->array, db_array_data->capacity *  sizeof(t_model_message*));
    }

    t_model_message** array = (t_model_message**) db_array_data->array;
    int columns_number = argc;
    array[db_array_data->size] = new_model_message();

    for (int column_index = 0; column_index < columns_number; column_index++) {

        if (strcmp(azColName[column_index], "Id") == 0) {
            array[db_array_data->size]->id = atoi(argv[column_index]);
        } else if (strcmp(azColName[column_index], "FromUser") == 0) {
            strcpy(array[db_array_data->size]->from_user, argv[column_index]);
        } else if (strcmp(azColName[column_index], "ToUser") == 0) {
            strcpy(array[db_array_data->size]->to_user, argv[column_index]);
        } else if (strcmp(azColName[column_index], "Type") == 0) {
            array[db_array_data->size]->data_type = atoi(argv[column_index]);
        } else if (strcmp(azColName[column_index], "Data") == 0) {
            strcpy(array[db_array_data->size]->data, argv[column_index]);
        } else if (strcmp(azColName[column_index], "Date") == 0) {
            strcpy(array[db_array_data->size]->date, argv[column_index]);
        } else if (strcmp(azColName[column_index], "Status") == 0) {
            array[db_array_data->size]->status = atoi(argv[column_index]);
        }else if (strcmp(azColName[column_index], "ForwardFrom") == 0) {
            strcpy(array[db_array_data->size]->forward_from, argv[column_index]);
        }

    }

    db_array_data->size++;

    return 0;
}


t_model_message *get_stone_message_from_chat(char *from_user, int *size){
    sqlite3 *db;
    
    int err_status = 0;

    if((err_status = sqlite3_open(DB, &db)) != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }

    char *sql_query = NULL;

    char *current_user = get_from_protocol_string(get_cookies(), "USERNAME");

    // char *select_request = "SELECT * FROM Messages WHERE ((((FromUser=('%s') AND ToUser=('%s')) OR (ToUser=('%s') AND FromUser=('%s'))) AND Type=('%i'))))));";
    // char *select_request = "SELECT * FROM Messages WHERE (((FromUser = '%s' AND ToUser = '%s') OR (ToUser = '%s' AND FromUser = '%s')) AND Type = '%i' AND ID = (SELECT MAX(Id) FROM Messages));";
    char *select_request = "SELECT * FROM Messages WHERE (Id IN (SELECT MAX(Id) FROM (SELECT * FROM Messages WHERE (((FromUser = '%s' AND ToUser = '%s') OR (ToUser = '%s' AND FromUser = '%s')) AND Type = '%i'))));";


    asprintf(&sql_query, select_request, from_user, current_user, from_user, current_user, 2);

    char *err_msg = NULL;

    t_db_array_data* select_result = create_db_array_data();

    if((err_status = sqlite3_exec(db, sql_query, callback_get_messages, select_result, &err_msg)) != SQLITE_OK) {
        fprintf(stderr, "SQL_error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        exit(1);
    }
    t_model_message** messages = (t_model_message**)select_result->array;

    *size = select_result->size;
    sqlite3_close(db);
    free(select_result);
    // return messages;
    if(*size == 0){
        fprintf(stderr, "\n\nNOTHING FOUND\n\n");
        return NULL;
    } else {
        fprintf(stderr, "\n\nSOMETHING FOUND %i\n\n", *size);

        return messages[*size - 1];
    }
}

t_model_message** get_all_messages_from_chat(char *from_user, int *size) {

    sqlite3 *db;
    
    int err_status = 0;

    if((err_status = sqlite3_open(DB, &db)) != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }

    char *sql_query = NULL;

    char *current_user = get_from_protocol_string(get_cookies(), "USERNAME");

    char *select_request = "SELECT * FROM Messages WHERE ((FromUser=('%s') AND ToUser=('%s')) OR (ToUser=('%s') AND FromUser=('%s')));";

    asprintf(&sql_query, select_request, from_user, current_user, from_user, current_user);

    char *err_msg = NULL;

    t_db_array_data* select_result = create_db_array_data();

    if((err_status = sqlite3_exec(db, sql_query, callback_get_messages, select_result, &err_msg)) != SQLITE_OK) {
        fprintf(stderr, "SQL_error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        exit(1);
    }
    t_model_message** messages = (t_model_message**)select_result->array;

    *size = select_result->size;
    sqlite3_close(db);
    free(select_result);
    return messages;
}



int callback_get_user_chats(void *data, int argc, char **argv, char **azColName) {
    t_db_array_data* db_array_data = (t_db_array_data*)data;

    if (db_array_data->first) {
        db_array_data->capacity = 10;
        db_array_data->array = malloc(sizeof(char *) * db_array_data->capacity);
        db_array_data->first = false;
    }

    if (db_array_data->size == db_array_data->capacity) {
        db_array_data->capacity += 10;
        db_array_data->array = realloc(db_array_data->array, db_array_data->capacity * sizeof(char*));
    }

    char** array = (char**) db_array_data->array;
    array[db_array_data->size] = mx_strdup(argv[0]);


    db_array_data->size++;

    return 0;
}


char** get_all_user_chats(char *current_user, int *count) {
    sqlite3 *db;
    
    int err_status = 0;

    if((err_status = sqlite3_open(DB, &db)) != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }

    // char *sql_query = NULL;

    // char *select_request = "SELECT DISTINCT ToUser FROM Messages WHERE FromUser=('%s');";
    char *sql_query = "SELECT ToUser From Messages UNION SELECT FromUser FROM Messages;";
    // char *select_request = "SELECT DISTINCT ToUser, FromUser From Messages";

    // asprintf(&sql_query, select_request);

    char *err_msg = NULL;

    t_db_array_data* select_result = create_db_array_data();

    if((err_status = sqlite3_exec(db, sql_query, callback_get_user_chats, select_result, &err_msg)) != SQLITE_OK) {
        fprintf(stderr, "SQL_error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        exit(1);
    }
    char** message_chats = (char**)select_result->array;
    *count = select_result->size;

    sqlite3_close(db);

    return message_chats;
}


int callback_get_message(void *data, int argc, char **argv, char **azColName) {
    t_model_message* msg = (t_model_message*)data;
    if(argc != 0) {
        for(int column_index = 0; column_index < argc; column_index++) {
            if(!strcmp(azColName[column_index], "Id"))
                msg->id = atoi(argv[column_index]);
            if(!strcmp(azColName[column_index], "FromUser")) {
                strcpy(msg->from_user, argv[column_index]);
            }
            if(!strcmp(azColName[column_index], "ToUser"))
                strcpy(msg->to_user, argv[column_index]);
            if(!strcmp(azColName[column_index], "Type"))
                msg->data_type = atoi(argv[column_index]);
            if(!strcmp(azColName[column_index], "Data"))
                strcpy(msg->data, argv[column_index]);
            if(!strcmp(azColName[column_index], "Date"))
                strcpy(msg->date, argv[column_index]);
            if(!strcmp(azColName[column_index], "Status"))
                msg->status = atoi(argv[column_index]);
            if(!strcmp(azColName[column_index], "ForwardFrom"))
                strcpy(msg->forward_from, argv[column_index]);
        }
    }    
    return 0;
}

t_model_message* get_message_by_id(size_t msg_id) {
    sqlite3 *db;
    
    int err_status = 0;

    if((err_status = sqlite3_open(DB, &db)) != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }

    char *sql_query = NULL;

    char *select_request = "SELECT * FROM Messages WHERE Id=('%zu');";

    asprintf(&sql_query, select_request, msg_id);
    char *err_msg = NULL;

    t_model_message *msg = new_model_message();
    if((err_status = sqlite3_exec(db, sql_query, callback_get_message, msg, &err_msg)) != SQLITE_OK) {
        fprintf(stderr, "SQL_error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        exit(1);
    }

    sqlite3_close(db);

    return msg;
}

void update_message(t_model_message* new_data) {

    sqlite3 *db;
    
    int err_status = 0;

    if((err_status = sqlite3_open(DB, &db)) != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }

    char *sql_query = NULL;
    char *update_request = "UPDATE Messages SET Data='%s', Status=%i WHERE Id=%i";

    asprintf(&sql_query, update_request, new_data->data, new_data->status, new_data->id); 
    
    char* err_msg = NULL;
    if((err_status = sqlite3_exec(db, sql_query, NULL, NULL, &err_msg)) != SQLITE_OK) {
        fprintf(stderr, "SQL_error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        exit(1);
    }

    sqlite3_close(db);

}

