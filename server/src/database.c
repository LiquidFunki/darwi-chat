#include "database.h"

static sqlite3* database = NULL;

sqlite3* get_database() {
    return database;
} 

char* table_names[] = {
    "Users",
    "UsersData",
    "Messages",
    "Resources",
    "Stones",
    NULL
};

char* tables_init[] = {

    "CREATE TABLE IF NOT EXISTS Users (Id INTEGER PRIMARY KEY AUTOINCREMENT, Username TEXT, Password TEXT, UserData INTEGER) ;",
    "CREATE TABLE IF NOT EXISTS UsersData (Id INTEGER PRIMARY KEY AUTOINCREMENT, About TEXT, Status INTEGER, TNumber CHAR, Email TEXT, Era INTEGER, Money INTEGER, LastUpdate CHAR, AvatarId Integer, Bought TEXT) ;",
    "CREATE TABLE IF NOT EXISTS Messages (Id INTEGER PRIMARY KEY AUTOINCREMENT, FromUser TEXT, ToUser TEXT, Type INTEGER, Data TEXT, Date CHAR, Status INTEGER, ForwardFrom TEXT);",
    "CREATE TABLE IF NOT EXISTS Resources (Id INTEGER PRIMARY KEY AUTOINCREMENT, Path TEXT, Name TEXT) ;",
    "CREATE TABLE IF NOT EXISTS Stones (Id INTEGER PRIMARY KEY AUTOINCREMENT, Path TEXT) ;",
    "CREATE TABLE IF NOT EXISTS Store (Id INTEGER PRIMARY KEY AUTOINCREMENT, Name TEXT UNIQUE, Path TEXT, Price INTEGER, Era INTEGER) ;",
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

    database = db;

    char *err_msg = NULL;

    for (int table_index = 0; tables_init[table_index] != NULL; table_index++) {
        if((err_status = sqlite3_exec(db, tables_init[table_index], 0, 0, &err_msg)) != SQLITE_OK) {
            fprintf(stderr, "SQL_error: %s\n", err_msg);
            sqlite3_free(err_msg);
            sqlite3_close(db);
            exit(1);
        }
    }
    t_model_resource *default_avatar = new_model_resource();
    default_avatar->id = 1;
    mx_strcpy(default_avatar->name, "horse.jpeg");
    mx_strcpy(default_avatar->path, "./server/resources/images/avatars/horse.jpeg");

    if(strcmp(get_resource_by_id(1)->path, default_avatar->path))
        insert_data_resource(default_avatar);

    fill_database_store();

    // sqlite3_close(db);
}

void init_User_table() {
    // sqlite3 *db;
    
    int err_status = 0;

    // if((err_status = sqlite3_open(DB, &db)) != SQLITE_OK) {
    //     fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
    //     sqlite3_close(db);
    //     exit(1);
    // }    

    char *init_request = "CREATE TABLE IF NOT EXISTS Users (Id INTEGER PRIMARY KEY AUTOINCREMENT, Username TEXT, Password TEXT) ;";
                         
    char *err_msg = NULL;

    if((err_status = sqlite3_exec(get_database(), init_request, 0, 0, &err_msg)) != SQLITE_OK) {
        fprintf(stderr, "SQL_error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(get_database());
        exit(1);
    }

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


