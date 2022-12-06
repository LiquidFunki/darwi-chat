#include "database.h"

bool is_verified_user(char* username, char* token) {


    if (username == NULL || token == NULL) return false;

    t_model_user* user = get_user_by_name(username);

    if (user == NULL) return false;
    
    if (strcmp(username, user->name) == 0 && strcmp(token, user->password) == 0)
        return true;
    
    return false;

}

int callback_get_user(void *data, int argc, char **argv, char **azColName) {

    if (argc == 0) {
        *((t_model_user**)data) = NULL;
        return 1;
    }
    else {
        *((t_model_user**)data) = new_model_user(argv[1], argv[2]);
        (*((t_model_user**)data))->id = atol(argv[0]);
        (*((t_model_user**)data))->user_data_id = atol(argv[3]);
    }

    return 0;
}


t_model_user* get_user_by_name(char* username) {

    t_model_user* model_user = NULL;

    int err_status = 0;

    // sqlite3 *db;
    
    // if((err_status = sqlite3_open(DB, &db)) != SQLITE_OK) {
    //     fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
    //     sqlite3_close(db);
    //     exit(1);
    // } 

    char *sql_query = NULL;

    char *check_request = "SELECT * FROM Users WHERE Username=('%s');";
    asprintf(&sql_query, check_request, username);
    char *err_msg = NULL;

    if((err_status = sqlite3_exec(get_database(), sql_query, callback_get_user, (void*)&model_user, &err_msg)) != SQLITE_OK) {
        fprintf(stderr, "SQL_error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(get_database());
        exit(1);
    }

    // sqlite3_close(db);

    return model_user;
}


bool is_new_user(char *username) {
    int err_status = 0;

    // sqlite3 *db;
    
    // if((err_status = sqlite3_open(DB, &db)) != SQLITE_OK) {
    //     fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
    //     sqlite3_close(db);
    //     exit(1);
    // } 

    char *sql_query = NULL;

    char *check_request = "SELECT * FROM Users WHERE Username=('%s');";

    asprintf(&sql_query, check_request, username);

    char *err_msg = NULL;
    
    int count = 0;

    if((err_status = sqlite3_exec(get_database(), sql_query, callback_count, &count, &err_msg)) != SQLITE_OK) {
        fprintf(stderr, "SQL_error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(get_database());
        exit(1);
    }

    // sqlite3_close(db);


    if(count == 0)
        return true;
    return false;
}


bool is_user(char *username, char *password) {
    // sqlite3 *db;
    
    int err_status = 0;

    // if((err_status = sqlite3_open(DB, &db)) != SQLITE_OK) {
    //     fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
    //     sqlite3_close(db);
    //     exit(1);
    // } 

    char *sql_query = NULL;

    char *check_request = "SELECT * FROM Users WHERE (Username=('%s') AND Password=('%s'));";

    asprintf(&sql_query, check_request, username, password);

    char *err_msg = NULL;
    
    int count = 0;

    if((err_status = sqlite3_exec(get_database(), sql_query, callback_count, &count, &err_msg)) != SQLITE_OK) {
        fprintf(stderr, "SQL_error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(get_database());
        exit(1);
    }

    // sqlite3_close(db);
    
    if(count == 0)
        return false;
    return true;
}

size_t insert_data_user(char *username, char *password) {
    
    //TODO: ERA !
    t_model_user_data* user_data = new_model_user_data();
    user_data->era = 1;
    size_t user_data_id = insert_data_user_data(user_data);
    free_model_user_data(&user_data);

    // sqlite3 *db;
    
    int err_status = 0;

    // if((err_status = sqlite3_open(DB, &db)) != SQLITE_OK) {
    //     fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
    //     sqlite3_close(db);
    //     exit(1);
    // }

    char *insert_request = "INSERT INTO Users(Username, Password, UserData) VALUES('%s', '%s', '%zu');";
    char *sql_query = NULL;
    char *err_msg = NULL;

    asprintf(&sql_query, insert_request, username, password, user_data_id);

    
    if((err_status = sqlite3_exec(get_database(), sql_query, callback_print_db, 0, &err_msg)) != SQLITE_OK) {
        fprintf(stderr, "SQL_error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(get_database());
        return 0;
        // exit(1);
    }

    size_t user_id = sqlite3_last_insert_rowid(get_database);

    // sqlite3_close(db);

    return user_id;
}

size_t get_user_data_id(char *username) {
    t_model_user *model_user = get_user_by_name(username);

    if (model_user == NULL) {
        return 0;
    }

    size_t user_data_id = model_user->user_data_id;
    free_model_user(&model_user);

    return user_data_id;
}

int update_username(char *username, char *new_username) {
    errno = 0;
    size_t user_data_id = get_user_data_id(username);
    
    int err_status = 0;

    if (username_is_unique(new_username)) {
        char *update_request = "UPDATE Users SET Username = '%s' WHERE Id = '%zu';";
        char *sql_query = NULL;
        char *err_msg = NULL;

        asprintf(&sql_query, update_request, new_username, user_data_id);

        if((err_status = sqlite3_exec(get_database(), sql_query, callback_print_db, 0, &err_msg)) != SQLITE_OK) {
            fprintf(stderr, "SQL_error: %s\n", err_msg);
            sqlite3_free(err_msg);
            sqlite3_close(get_database());
            return 1;
            // exit(1);
        }

        return 0;
    }

    return 1;
}

bool username_is_unique(char* username) {
    errno = 0;
    int err_status = 0;

    char *select_request = "SELECT Id FROM Users WHERE Username = '%s';";
    char *sql_query = NULL;
    char *err_msg = NULL;

    int id = -1;

    asprintf(&sql_query, select_request, username);

    if((err_status = sqlite3_exec(get_database(), sql_query, callback_get_user_str, &id, &err_msg)) != SQLITE_OK) {
        fprintf(stderr, "SQL_error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(get_database());
        return 1;
        // exit(1);
    }
    
    if (id == -1) 
        return false;

    return true;   
}
