#include "database.h"

size_t insert_data_resource(t_model_resource* model_resource) {

    // sqlite3 *db;
    
    int err_status = 0;

    // if((err_status = sqlite3_open(DB, &db)) != SQLITE_OK) {
    //     fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
    //     sqlite3_close(db);
    //     exit(1);
    // }

    char *insert_request = "INSERT INTO Resources(Path, Name) VALUES('%s', '%s');";
    char *sql_query = NULL;
    char *err_msg = NULL;

    asprintf(&sql_query, insert_request, model_resource->path, model_resource->name);

    if((err_status = sqlite3_exec(get_database(), sql_query, callback_print_db, 0, &err_msg)) != SQLITE_OK) {
        fprintf(stderr, "SQL_error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(get_database());
        return 0;
        // exit(1);
    }

    size_t resource_id = sqlite3_last_insert_rowid(get_database());
    // sqlite3_close(db);

    return resource_id;

}



int callback_get_resource(void *data, int argc, char **argv, char **azColName) {
    t_model_resource *resource = (t_model_resource*)data;

    if(argc != 0) {
        for(int column_index = 0; column_index < argc; column_index++) {
            if(!mx_strcmp(azColName[column_index], "Id"))
                resource->id = atoi(argv[column_index]);
            if(!mx_strcmp(azColName[column_index], "Path"))
                mx_strcpy(resource->path, argv[column_index]);
            if(!mx_strcmp(azColName[column_index], "Name"))
                mx_strcpy(resource->name, argv[column_index]);
        }
    }

    return 0;
}


t_model_resource *get_resource_by_id(size_t id) {

    
    int err_status = 0;

    char *insert_request = "SELECT * FROM Resources WHERE Id=('%i');";
    char *sql_query = NULL;
    char *err_msg = NULL;

    asprintf(&sql_query, insert_request, id);

    t_model_resource *model_resource = new_model_resource();
    model_resource->id = id;
    if((err_status = sqlite3_exec(get_database(), sql_query, callback_get_resource, model_resource, &err_msg)) != SQLITE_OK) {
        fprintf(stderr, "SQL_error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(get_database());
        return 0;
        // exit(1);
    }

    return model_resource;

}


int callback_get_user_avatar_id(void *data, int argc, char **argv, char **azColName) {
    size_t *id = (size_t*)data;

    if(argc != 0) {
        printf("AVATAR_ID: %s", argv[0]);
        *id = atoi(argv[0]);
    }

    return 0;
}

size_t get_user_avatar_id(char *username) {

    int err_status = 0;

    char *insert_request = "SELECT AvatarId FROM UsersData WHERE Id=('%i');";
    char *sql_query = NULL;
    char *err_msg = NULL;

    asprintf(&sql_query, insert_request, get_user_data_id(username));

    size_t id;

     if((err_status = sqlite3_exec(get_database(), sql_query, callback_get_user_avatar_id, &id, &err_msg)) != SQLITE_OK) {
        fprintf(stderr, "SQL_error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(get_database());
        return 0;
        // exit(1);
    }

    return id;
}