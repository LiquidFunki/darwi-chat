#include "database_client.h"


size_t insert_data_resource(t_model_resource* model_resource) {

    sqlite3 *db;
    
    int err_status = 0;

    if((err_status = sqlite3_open(DB, &db)) != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }

    char *insert_request = "INSERT INTO Resources(Id, Path, Name) VALUES('%i', '%s', '%s');";
    char *sql_query = NULL;
    char *err_msg = NULL;

    asprintf(&sql_query, insert_request, model_resource->id, model_resource->path, model_resource->name);

    if((err_status = sqlite3_exec(db, sql_query, callback_print_db, 0, &err_msg)) != SQLITE_OK) {
        fprintf(stderr, "SQL_error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return 0;
        // exit(1);
    }

    size_t resource_id = sqlite3_last_insert_rowid(db);
    sqlite3_close(db);

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


t_model_resource *get_resource_by_id(char *id) {

    sqlite3 *db;
    
    int err_status = 0;

    if((err_status = sqlite3_open(DB, &db)) != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }

    char *insert_request = "SELECT * FROM Resources WHERE Id=('%i');";
    char *sql_query = NULL;
    char *err_msg = NULL;

    asprintf(&sql_query, insert_request, atoi(id));

    t_model_resource *model_resource = new_model_resource();

    if((err_status = sqlite3_exec(db, sql_query, callback_get_resource, model_resource, &err_msg)) != SQLITE_OK) {
        fprintf(stderr, "SQL_error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return 0;
        // exit(1);
    }

    sqlite3_close(db);

    return model_resource;

}