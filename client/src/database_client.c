#include "database_client.h"

char* table_names[] = {
    "Users",
    "UsersData",
    "Messages",
    "Resources",
    "Stones",
    NULL
};

char* tables_init[] = {

    "CREATE TABLE IF NOT EXISTS Messages (Id INTEGER PRIMARY KEY, FromUser TEXT, ToUser TEXT, Type INTEGER, Data TEXT, Date CHAR, Status INTEGER, ForwardFrom TEXT) ;",
    "CREATE TABLE IF NOT EXISTS Resources (Id INTEGER PRIMARY KEY, Path TEXT, Name TEXT) ;",
    "CREATE TABLE IF NOT EXISTS Stones (Id INTEGER PRIMARY KEY, Path TEXT) ;",
    NULL
};

void init_tables() {

    sqlite3 *db = NULL;
    int err_status = 0;

    if((err_status = sqlite3_open(DB, &db)) != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }

    char *err_msg = NULL;

    for (int table_index = 0; tables_init[table_index] != NULL; table_index++) {
        if((err_status = sqlite3_exec(db, tables_init[table_index], 0, 0, &err_msg)) != SQLITE_OK) {
            fprintf(stderr, "SQL_error: %s\n", err_msg);
            sqlite3_free(err_msg);
            sqlite3_close(db);
            exit(1);
        }
    }

    sqlite3_close(db);
}


int callback_print_db(void *not_used, int argc, char **argv, char **azColName) {
    not_used = 0;

    for(int row_idx = 0; row_idx < argc; row_idx++) {
        printf("%s = %s\n", azColName[row_idx], argv[row_idx] ? argv[row_idx] : "NULL");
        fflush(stdout);
    }
    printf("\n");

    return 0;
}

int callback_count(void *data, int argc, char **argv, char **azColName) {

    *((int*)data) = argc;

    return 0;
}

t_db_array_data* create_db_array_data() {

    t_db_array_data* db_array_data = (t_db_array_data*)malloc(sizeof(t_db_array_data));

    db_array_data->array = NULL;
    db_array_data->first = true;
    db_array_data->size  = 0;
    db_array_data->capacity = 0;

    return db_array_data;
}


