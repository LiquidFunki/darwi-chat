#include "database.h"

size_t insert_data_store(t_model_store* model_store) {
    
    int err_status = 0;

    char *insert_request = "INSERT INTO Store (Path, Name, Price, Era) VALUES('%s', '%s', '%zu', '%zu');";
    char *sql_query = NULL;
    char *err_msg = NULL;

    asprintf(&sql_query, insert_request, model_store->path, model_store->name, model_store->price, model_store->era);

    if((err_status = sqlite3_exec(get_database(), sql_query, callback_print_db, 0, &err_msg)) != SQLITE_OK) {
        fprintf(stderr, "SQL_error: %s\n", err_msg);
        sqlite3_free(err_msg);
        // sqlite3_close(get_database());
        return 0;
        // exit(1);
    }

    size_t store_item_id = sqlite3_last_insert_rowid(get_database());

    return store_item_id;

}


int callback_get_store(void *data, int argc, char **argv, char **azColName) {
    cJSON* store = (cJSON*)data;
    cJSON* store_item  = cJSON_CreateObject();

    add_to_protocol_number(store_item, "id", atol(argv[0]));
    add_to_protocol_string(store_item, "name", argv[1]);
    add_to_protocol_string(store_item, "path", argv[2]);
    add_to_protocol_number(store_item, "price", atol(argv[3]));
    add_to_protocol_number(store_item, "era", atol(argv[4]));

    char* store_item_str = cJSON_Print(store_item);
    cJSON* store_item_str_json = cJSON_CreateString(store_item_str);

    free(store_item_str);

    cJSON_AddItemToArray(store, store_item_str_json);
    return 0;
    
    // t_model_store *store = (t_model_store*)data;

    // if(argc != 0) {
    //     for(int column_index = 0; column_index < argc; column_index++) {
    //         if(!mx_strcmp(azColName[column_index], "Id"))
    //             store->id = atoi(argv[column_index]);
    //         if(!mx_strcmp(azColName[column_index], "Path"))
    //             mx_strcpy(store->path, argv[column_index]);
    //         if(!mx_strcmp(azColName[column_index], "Name"))
    //             mx_strcpy(store->name, argv[column_index]);
    //         if(!mx_strcmp(azColName[column_index], "Price"))
    //             store->price = atoi(argv[column_index]);
    //         if(!mx_strcmp(azColName[column_index], "Era"))
    //             store->era = atoi(argv[column_index]);
    //     }
    // }

    // return 0;
}


cJSON* get_store_by_era(int era) {
    int err_status = 0;
    // int id = 0;
    // if (strcmp(era, "EGYPT") == 0)
    //     id = 1;
    // if (strcmp(era, "MIDDLE_AGES") == 0)
    //     id = 2;
    // if (strcmp(era, "ENLIGHTMENT") == 0)
    //     id = 3;
    // if (strcmp(era, "MODERN_TIMES") == 0)
    //     id = 4;

    char *select_request = "SELECT * FROM Store WHERE Era = '%i';";
    char *sql_query = NULL;
    char *err = NULL;

    asprintf(&sql_query, select_request, era);

    cJSON* store = cJSON_CreateArray();

    if((err_status = sqlite3_exec(get_database(), sql_query, callback_get_store, store, &err)) != SQLITE_OK) {
        fprintf(stderr, "SQL_error: %s\n", err);
        sqlite3_free(err);
        sqlite3_close(get_database());
        // return 0;
        // exit(1);
    }

    return store;

}

void fill_database_store() {
    t_model_store *next_era_for_stone_age = new_model_store();
    strcpy(next_era_for_stone_age->name, "next era for stone age");
    strcpy(next_era_for_stone_age->path, "./client/resources/static/images/store/1.png");
    next_era_for_stone_age->price = 70;
    next_era_for_stone_age->era = 0;
    size_t next_era_for_stone_age_int = insert_data_store(next_era_for_stone_age);

    t_model_store *clear_stone = new_model_store();
    strcpy(clear_stone->name, "clear stone");
    strcpy(clear_stone->path, "./client/resources/static/images/store/2.png");
    clear_stone->price = 7;
    clear_stone->era = 0;
    size_t clear_stone_int = insert_data_store(clear_stone);

    t_model_store *rock1 = new_model_store();
    strcpy(rock1->name, "rock1");
    strcpy(rock1->path, "./client/resources/static/images/store/3.png");
    rock1->price = 15;
    rock1->era = 0;
    size_t rock1_int = insert_data_store(rock1);

    t_model_store *rock2 = new_model_store();
    strcpy(rock2->name, "rock2");
    strcpy(rock2->path, "./client/resources/static/images/store/4.png");
    rock2->price = 15;
    rock2->era = 0;
    size_t rock2_int = insert_data_store(rock2);

    t_model_store *rock3 = new_model_store();
    strcpy(rock3->name, "rock3");
    strcpy(rock3->path, "./client/resources/static/images/store/5.png");
    rock3->price = 15;
    rock3->era = 0;
    size_t rock3_int = insert_data_store(rock3);

    t_model_store *rock4 = new_model_store();
    strcpy(rock4->name, "rock4");
    strcpy(rock4->path, "./client/resources/static/images/store/6.png");
    rock4->price = 15;
    rock4->era = 0;
    size_t rock4_int = insert_data_store(rock4);

    ///////////////////////////////////////////////////

    t_model_store *next_era_for_egypt = new_model_store();
    strcpy(next_era_for_egypt->name, "next era for egypt");
    strcpy(next_era_for_egypt->path, "./client/resources/static/images/store/7.png");
    next_era_for_egypt->price = 80;
    next_era_for_egypt->era = 1;
    size_t next_era_for_egypt_int = insert_data_store(next_era_for_egypt);

    t_model_store *new_words_5 = new_model_store();
    strcpy(new_words_5->name, "5 new words");
    strcpy(new_words_5->path, "./client/resources/static/images/store/8.png");
    new_words_5->price = 10;
    new_words_5->era = 1;
    size_t new_words_5_int = insert_data_store(new_words_5);

    t_model_store *new_words_10 = new_model_store();
    strcpy(new_words_10->name, "10 new words");
    strcpy(new_words_10->path, "./client/resources/static/images/store/9.png");
    new_words_10->price = 18;
    new_words_10->era = 1;
    size_t new_words_10_int = insert_data_store(new_words_10);

    t_model_store *new_words_15 = new_model_store();
    strcpy(new_words_15->name, "15 new words");
    strcpy(new_words_15->path, "./client/resources/static/images/store/10.png");
    new_words_15->price = 26;
    new_words_15->era = 1;
    size_t new_words_15_int = insert_data_store(new_words_15);

    t_model_store *new_words_20 = new_model_store();
    strcpy(new_words_20->name, "20 new words");
    strcpy(new_words_20->path, "./client/resources/static/images/store/11.png");
    new_words_20->price = 35;
    new_words_20->era = 1;
    size_t new_words_20_int = insert_data_store(new_words_20);

    t_model_store *new_words_50 = new_model_store();
    strcpy(new_words_50->name, "50 new words");
    strcpy(new_words_50->path, "./client/resources/static/images/store/12.png");
    new_words_50->price = 70;
    new_words_50->era = 1;
    size_t new_words_50_int = insert_data_store(new_words_50);

    ///////////////////////////////////////////////////

    t_model_store *next_era_for_middle_ages = new_model_store();
    strcpy(next_era_for_middle_ages->name, "next era for middle ages");
    strcpy(next_era_for_middle_ages->path, "./client/resources/static/images/store/13.png");
    next_era_for_middle_ages->price = 90;
    next_era_for_middle_ages->era = 2;
    size_t next_era_for_middle_ages_int = insert_data_store(next_era_for_middle_ages);

    t_model_store *color1 = new_model_store();
    strcpy(color1->name, "color1");
    strcpy(color1->path, "./client/resources/static/images/store/14.png");
    color1->price = 20;
    color1->era = 2;
    size_t color1_int = insert_data_store(color1);

    t_model_store *color2 = new_model_store();
    strcpy(color2->name, "color2");
    strcpy(color2->path, "./client/resources/static/images/store/15.png");
    color2->price = 20;
    color2->era = 2;
    size_t color2_int = insert_data_store(color2);

    t_model_store *color3 = new_model_store();
    strcpy(color3->name, "color3");
    strcpy(color3->path, "./client/resources/static/images/store/16.png");
    color3->price = 20;
    color3->era = 2;
    size_t color3_int = insert_data_store(color3);

    t_model_store *middle_ages_background1 = new_model_store();
    strcpy(middle_ages_background1->name, "middle ages background1");
    strcpy(middle_ages_background1->path, "./client/resources/static/images/store/17.png");
    middle_ages_background1->price = 40;
    middle_ages_background1->era = 2;
    size_t middle_ages_background1_int = insert_data_store(middle_ages_background1);

    t_model_store *middle_ages_background2 = new_model_store();
    strcpy(middle_ages_background2->name, "middle ages background2");
    strcpy(middle_ages_background2->path, "./client/resources/static/images/store/18.png");
    middle_ages_background2->price = 40;
    middle_ages_background2->era = 2;
    size_t middle_ages_background2_int = insert_data_store(middle_ages_background2);

    ///////////////////////////////////////////////////

    t_model_store *next_era_for_enlightment = new_model_store();
    strcpy(next_era_for_enlightment->name, "next era for enlightment");
    strcpy(next_era_for_enlightment->path, "./client/resources/static/images/store/19.png");
    next_era_for_enlightment->price = 100;
    next_era_for_enlightment->era = 3;
    size_t nnext_era_for_enlightment_int = insert_data_store(next_era_for_enlightment);

    t_model_store *send_files_unlock = new_model_store();
    strcpy(send_files_unlock->name, "unlock sending files");
    strcpy(send_files_unlock->path, "./client/resources/static/images/store/20.png");
    send_files_unlock->price = 90;
    send_files_unlock->era = 3;
    size_t send_files_unlock_int = insert_data_store(send_files_unlock);
    
    t_model_store *no_mistakes = new_model_store();
    strcpy(no_mistakes->name, "educate");
    strcpy(no_mistakes->path, "./client/resources/static/images/store/21.png");
    no_mistakes->price = 75;
    no_mistakes->era = 3;
    size_t no_mistakes_int = insert_data_store(no_mistakes);
    
    t_model_store *enlightment_background1 = new_model_store();
    strcpy(enlightment_background1->name, "enlightment background1");
    strcpy(enlightment_background1->path, "./client/resources/static/images/store/22.png");
    enlightment_background1->price = 40;
    enlightment_background1->era = 3;
    size_t enlightment_background1_int = insert_data_store(enlightment_background1);

    t_model_store *enlightment_background2 = new_model_store();
    strcpy(enlightment_background2->name, "enlightment background2");
    strcpy(enlightment_background2->path, "./client/resources/static/images/store/23.png");
    enlightment_background2->price = 40;
    enlightment_background2->era = 3;
    size_t enlightment_background2_int = insert_data_store(enlightment_background2);

    t_model_store *enlightment_background3 = new_model_store();
    strcpy(enlightment_background3->name, "enlightment background3");
    strcpy(enlightment_background3->path, "./client/resources/static/images/store/24.png");
    enlightment_background3->price = 40;
    enlightment_background3->era = 3;
    size_t enlightment_background3_int = insert_data_store(enlightment_background3);

    ///////////////////////////////////////////////////

    t_model_store *prize = new_model_store();
    strcpy(prize->name, "gift");
    strcpy(prize->path, "./client/resources/static/images/store/25.png");
    prize->price = 238;
    prize->era = 4;
    size_t prize_int = insert_data_store(prize);
}

int buy_store_item(char* username, int store_item_id) {
    printf("\n\n\nSTORE ITEM ID %i\n\n\n", store_item_id);
    int price = get_store_item_price(store_item_id);
    
    int update = update_user_money(username, -price);
    printf("\n\n\nPRICE %i\n\n\n", -price);
    if (update == 1)
        return 1;
    
    return 0;
}

 int get_store_item_price(int store_item_id) {
    size_t price = 0;
    int err_status = 0;

    char *select_request = "SELECT Price FROM Store WHERE Id='%zu';";
    char *sql_query = NULL;
    char *err_msg = NULL;

    asprintf(&sql_query, select_request, store_item_id);

    if((err_status = sqlite3_exec(get_database(), sql_query, callback_get_user_size_t, &price, &err_msg)) != SQLITE_OK) {
        fprintf(stderr, "SQL_error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(get_database());
        return 0;
        // exit(1);
    }

    return price;
}

char* get_bought_items(char* username) {
    char* bought = mx_strnew(BUFSIZ);
    int err_status = 0;
    size_t user_data_id = get_user_data_id(username);

    char *select_request = "SELECT Bought FROM UsersData WHERE Id='%zu';";
    char *sql_query = NULL;
    char *err_msg = NULL;

    asprintf(&sql_query, select_request, user_data_id);

    if((err_status = sqlite3_exec(get_database(), sql_query, callback_get_user_str, bought, &err_msg)) != SQLITE_OK) {
        fprintf(stderr, "SQL_error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(get_database());
        return 0;
        // exit(1);
    }
    if (!bought)
        strcpy(bought, "[]");

    return bought;
}

int update_bought_items(char* username, char* bought) {
    int err_status = 0;
    size_t user_data_id = get_user_data_id(username);

    char *update_request = "UPDATE UsersData SET Bought = '%s' WHERE Id = '%zu';";
    char *sql_query = NULL;
    char *err_msg = NULL;
    asprintf(&sql_query, update_request, bought, user_data_id);

    if((err_status = sqlite3_exec(get_database(), sql_query, callback_print_db, NULL, &err_msg)) != SQLITE_OK) {
        fprintf(stderr, "SQL_error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(get_database());
        return 1;
        // exit(1);
    }

    return 0;
}
