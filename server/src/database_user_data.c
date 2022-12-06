#include "database.h"

size_t insert_data_user_data(t_model_user_data* model_user_data) {

    sqlite3 *db;
    
    int err_status = 0;

    if((err_status = sqlite3_open(DB, &db)) != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }
    
    char *insert_request = "INSERT INTO UsersData(About, Status, TNumber, Email, Era, Money, AvatarId, Bought) VALUES('%s', %i, '%s', '%s', '%i', '%zu', '%zu', '%s');";
    char *sql_query = NULL;
    char *err_msg = NULL;

    asprintf(&sql_query, insert_request, model_user_data->about, model_user_data->status, model_user_data->t_number, model_user_data->email, model_user_data->era, model_user_data->money, model_user_data->avatar_id, model_user_data->bought_items);

    if((err_status = sqlite3_exec(db, sql_query, callback_print_db, 0, &err_msg)) != SQLITE_OK) {
        fprintf(stderr, "SQL_error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return 0;
        // exit(1);
    }

    size_t user_data_id = sqlite3_last_insert_rowid(db);
    sqlite3_close(db);

    return user_data_id;
}

int update_user_avatar(char* username, int avatar_id) {
    errno = 0;
    size_t user_data_id = get_user_data_id(username);


    int err_status = 0;

    char *update_request = "UPDATE UsersData SET AvatarId = '%i' WHERE Id=%zu;";
    char *sql_query = NULL;
    char *err_msg = NULL;

    asprintf(&sql_query, update_request, avatar_id, user_data_id);

    if((err_status = sqlite3_exec(get_database(), sql_query, callback_print_db, 0, &err_msg)) != SQLITE_OK) {
        fprintf(stderr, "SQL_error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(get_database());
        return 1;
        // exit(1);
    }


    return 0;
}

int update_user_money(char *username, int add_money) {
    errno = 0;
    size_t user_data_id = get_user_data_id(username);
    size_t money = get_user_money_by_username(username); 
    if (add_money > 0 || (add_money < 0 && abs(add_money) <= money))
        money += add_money;
    else
        return 1;
    
    int err_status = 0;

    char *update_request = "UPDATE UsersData SET Money = '%zu' WHERE Id=%zu;";
    char *sql_query = NULL;
    char *err_msg = NULL;

    asprintf(&sql_query, update_request, money, user_data_id);

    if((err_status = sqlite3_exec(get_database(), sql_query, callback_print_db, 0, &err_msg)) != SQLITE_OK) {
        fprintf(stderr, "SQL_error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(get_database());
        return 1;
        // exit(1);
    }


    return 0;
}

size_t get_user_money_by_username(char *username) {
    size_t money = 0;
    size_t user_data_id = get_user_data_id(username);
    
    int err_status = 0;

    char *select_request = "SELECT Money FROM UsersData WHERE Id='%zu';";
    char *sql_query = NULL;
    char *err_msg = NULL;

    asprintf(&sql_query, select_request, user_data_id);

    if((err_status = sqlite3_exec(get_database(), sql_query, callback_get_user_size_t, &money, &err_msg)) != SQLITE_OK) {
        fprintf(stderr, "SQL_error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(get_database());
        return 0;
        // exit(1);
    }

    return money;
}

size_t get_user_money_by_user_data_id(size_t user_data_id) {
    size_t money = 0;
    
    int err_status = 0;

    char *select_request = "SELECT Money FROM UsersData WHERE Id='%zu';";
    char *sql_query = NULL;
    char *err_msg = NULL;

    asprintf(&sql_query, select_request, user_data_id);

    if((err_status = sqlite3_exec(get_database(), sql_query, callback_get_user_size_t, &money, &err_msg)) != SQLITE_OK) {
        fprintf(stderr, "SQL_error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(get_database());
        return 0;
        // exit(1);
    }

    return money;
}

int callback_get_user_size_t(void *data, int argc, char **argv, char **azColName) {

    if (argc == 0) {
        printf("error: callback_get_user_money: no user data with given id\n");
        fflush(stdout);
        return 1;
    }
    else {
        *((size_t *)data) = atol(argv[0]);
    }

    return 0;
}

//////////////////////////////////////////////////////////////////

int update_user_about(char *username, char *about) {
    errno = 0;
    size_t user_data_id = get_user_data_id(username);
    
    int err_status = 0;

    char *update_request = "UPDATE UsersData SET About = '%s' WHERE Id = '%zu';";
    char *sql_query = NULL;
    char *err_msg = NULL;

    asprintf(&sql_query, update_request, about, user_data_id);

    if((err_status = sqlite3_exec(get_database(), sql_query, callback_print_db, 0, &err_msg)) != SQLITE_OK) {
        fprintf(stderr, "SQL_error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(get_database());
        return 1;
        // exit(1);
    }

    return 0;
}

char *get_user_about(char *username) {
    char *about = mx_strnew(ABOUT_SIZE);
    size_t user_data_id = get_user_data_id(username);
    
    int err_status = 0;

    char *select_request = "SELECT About FROM UsersData WHERE Id='%zu';";
    char *sql_query = NULL;
    char *err_msg = NULL;

    asprintf(&sql_query, select_request, user_data_id);

    if((err_status = sqlite3_exec(get_database(), sql_query, callback_get_user_str, &about, &err_msg)) != SQLITE_OK) {
        fprintf(stderr, "SQL_error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(get_database());
        return 0;
        // exit(1);
    }

    return about;
}

int callback_get_user_str(void *data, int argc, char **argv, char **azColName) {
    char* new_data = (char*)data;
    if (argc == 0) {
        printf("error: callback_get_user_about: no user data with given id\n");
        fflush(stdout);
        return 1;
    }
    else {
        // *((char**)data) = argv[0];
        strcpy(new_data, argv[0]);
        printf("\n\nargv[0] %s\n\n", argv[0]);
        printf("\n\argc %i\n\n", argc);
    }

    return 0;
}

//////////////////////////////////////////////////////////////////

int update_user_tnumber(char *username, char *tnumber) {
    errno = 0;
    size_t user_data_id = get_user_data_id(username);
    
    int err_status = 0;

    char *update_request = "UPDATE UsersData SET TNumber = '%s' WHERE Id = '%zu';";
    char *sql_query = NULL;
    char *err_msg = NULL;

    asprintf(&sql_query, update_request, tnumber, user_data_id);

    if((err_status = sqlite3_exec(get_database(), sql_query, callback_print_db, 0, &err_msg)) != SQLITE_OK) {
        fprintf(stderr, "SQL_error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(get_database());
        return 1;
        // exit(1);
    }

    return 0;
}

char *get_user_tnumber(char *username) {
    char *tnumber = mx_strnew(T_NUMBER_SIZE);
    size_t user_data_id = get_user_data_id(username);
    
    int err_status = 0;

    char *select_request = "SELECT TNumber FROM UsersData WHERE Id='%zu';";
    char *sql_query = NULL;
    char *err_msg = NULL;

    asprintf(&sql_query, select_request, user_data_id);

    if((err_status = sqlite3_exec(get_database(), sql_query, callback_get_user_str, &tnumber, &err_msg)) != SQLITE_OK) {
        fprintf(stderr, "SQL_error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(get_database());
        return 0;
        // exit(1);
    }

    return tnumber;
}

//////////////////////////////////////////////////////////////////

int update_user_email(char *username, char *email) {
    errno = 0;
    size_t user_data_id = get_user_data_id(username);
    
    int err_status = 0;

    char *update_request = "UPDATE UsersData SET Email = '%s' WHERE Id = '%zu';";
    char *sql_query = NULL;
    char *err_msg = NULL;

    asprintf(&sql_query, update_request, email, user_data_id);

    if((err_status = sqlite3_exec(get_database(), sql_query, callback_print_db, 0, &err_msg)) != SQLITE_OK) {
        fprintf(stderr, "SQL_error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(get_database());
        return 1;
        // exit(1);
    }

    return 0;
}

char *get_user_email(char *username) {
    char *email = mx_strnew(EMAIL_SIZE);
    size_t user_data_id = get_user_data_id(username);
    
    int err_status = 0;

    char *select_request = "SELECT Email FROM UsersData WHERE Id='%zu';";
    char *sql_query = NULL;
    char *err_msg = NULL;

    asprintf(&sql_query, select_request, user_data_id);

    if((err_status = sqlite3_exec(get_database(), sql_query, callback_get_user_str, &email, &err_msg)) != SQLITE_OK) {
        fprintf(stderr, "SQL_error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(get_database());
        return 0;
        // exit(1);
    }

    return email;
}

//////////////////////////////////////////////////////////////////

t_model_user_data *get_user_data_by_username(char *username) {
    // char *email = mx_strnew(EMAIL_SIZE);
    size_t user_data_id = get_user_data_id(username);
    t_model_user_data *model_user_data = new_model_user_data();
    int err_status = 0;

    char *select_request = "SELECT * FROM UsersData WHERE Id='%zu';";
    char *sql_query = NULL;
    char *err_msg = NULL;

    asprintf(&sql_query, select_request, user_data_id);

    if((err_status = sqlite3_exec(get_database(), sql_query, callback_get_user_data, model_user_data, &err_msg)) != SQLITE_OK) {
        fprintf(stderr, "SQL_error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(get_database());
        return 0;
        // exit(1);
    }

    return model_user_data;
}

int callback_get_user_data(void *data, int argc, char **argv, char **azColName) { 
    t_model_user_data *model_user_data = (t_model_user_data *)data;

    if (argc == 0) {
        printf("error: callback_get_user_data: no user data with given id\n");
        fflush(stdout);
        return 1;
    }
    else {
        for (int column_index = 0; column_index < argc; column_index++) {
            if (!strcmp(azColName[column_index], "Id"))
                model_user_data->id = atoi(argv[column_index]);
            if (!strcmp(azColName[column_index], "About"))
                strcpy(model_user_data->about, argv[column_index]);
            if (!strcmp(azColName[column_index], "Status"))
               model_user_data->status = atoi(argv[column_index]);
            if (!strcmp(azColName[column_index], "TNumber"))
                strcpy(model_user_data->t_number, argv[column_index]);
            if (!strcmp(azColName[column_index], "Email"))
                strcpy(model_user_data->email, argv[column_index]);
            if (!strcmp(azColName[column_index], "Era"))
                model_user_data->era = atoi(argv[column_index]);
            if (!strcmp(azColName[column_index], "Money"))
                model_user_data->money = atoi(argv[column_index]);
            if (!strcmp(azColName[column_index], "Bought"))
                strcpy(model_user_data->bought_items, argv[column_index]);
        }
    }

    return 0;
}

int update_user_era(char *username, int era) {

    printf("/n/n in update /n/n");
    errno = 0;
    size_t user_data_id = get_user_data_id(username);
    
    int err_status = 0;
    
    char *update_request = "UPDATE UsersData SET Era = '%i' WHERE Id = '%zu';";
    char *sql_query = NULL;
    char *err_msg = NULL;

    asprintf(&sql_query, update_request, era, user_data_id);

    if((err_status = sqlite3_exec(get_database(), sql_query, callback_print_db, 0, &err_msg)) != SQLITE_OK) {
        fprintf(stderr, "SQL_error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(get_database());
        return 1;
        // exit(1);
    }

    printf("/n/n end update /n/n");
    return 0;
}

