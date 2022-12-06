#include "database.h"

size_t insert_data_stone(t_model_stone* model_stone) {

    // sqlite3 *db;
    
    int err_status = 0;

    // if((err_status = sqlite3_open(DB, &db)) != SQLITE_OK) {
    //     fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
    //     sqlite3_close(db);
    //     exit(1);
    // }

    char *insert_request = "INSERT INTO Stones(Path) VALUES('%s');";
    char *sql_query = NULL;
    char *err_msg = NULL;

    asprintf(&sql_query, insert_request, model_stone->path);

    if((err_status = sqlite3_exec(get_database(), sql_query, callback_print_db, 0, &err_msg)) != SQLITE_OK) {
        fprintf(stderr, "SQL_error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(get_database());
        return 0;
        // exit(1);
    }

    size_t stone_id = sqlite3_last_insert_rowid(get_database());
    // sqlite3_close(db);

    return stone_id;

}



int callback_get_stone(void *data, int argc, char **argv, char **azColName) {
    t_model_stone *stone = (t_model_stone*)data;

    if(argc != 0) {
        for(int column_index = 0; column_index < argc; column_index++) {
            if(!mx_strcmp(azColName[column_index], "Id"))
                stone->id = atoi(argv[column_index]);
            if(!mx_strcmp(azColName[column_index], "Path"))
                mx_strcpy(stone->path, argv[column_index]);
        }
    }

    return 0;
}



t_model_stone *get_stone_by_id(char *id) {


    int err_status = 0;


    char *insert_request = "SELECT * FROM Stones WHERE Id=('%i');";
    char *sql_query = NULL;
    char *err_msg = NULL;

    asprintf(&sql_query, insert_request, atoi(id));

    t_model_stone *model_stone = new_model_stone();

    if((err_status = sqlite3_exec(get_database(), sql_query, callback_get_stone, model_stone, &err_msg)) != SQLITE_OK) {
        fprintf(stderr, "SQL_error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(get_database());
        return 0;
        // exit(1);
    }


    return model_stone;

}
