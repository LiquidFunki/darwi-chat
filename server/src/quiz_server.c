#include "quiz_server.h"

static cJSON* questions_obj = NULL;
static int q_number = 0;

void generate_quiz() {

    char* path_to_file = "./server/resources/quiz";

    // char *file = mx_file_to_str(path_to_file);

    FILE* file  = fopen(path_to_file, "r");
    if (file == NULL) {
        printf("have not resource quiz\n");
        fflush(stdout);
        return;
    }

    fseek(file, 0, SEEK_END);
    size_t file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* file_str = mx_strnew(file_size);
    fread(file_str, sizeof(char), file_size, file);  

    printf("%s\n", file_str);
    fflush(stdout);
    char** questions = mx_strsplit(file_str, '\n');
    questions_obj = cJSON_CreateObject();
    // int q_number = 0;

    for(; questions[q_number] != NULL; q_number++) {
        cJSON* question = cJSON_CreateObject();
        char **question_info = mx_strsplit(questions[q_number], ';');

        add_to_protocol_string(question, "QUESTION", question_info[0]);
        add_to_protocol_string(question, "CORRECT_ANSWER", question_info[1]);
        add_to_protocol_string(question, "ANSWER_1", question_info[2]);
        add_to_protocol_string(question, "ANSWER_2", question_info[3]);
        add_to_protocol_string(question, "ANSWER_3", question_info[4]);

        add_to_protocol(questions_obj, mx_itoa(q_number), question);

        mx_del_strarr(&question_info);
    }
    fclose(file);
    free(file_str);
    printf("q_number: %i\n", q_number);
    fflush(stdout);
    // questions_number = q_number;

}

cJSON* get_questions() {
    if (questions_obj == NULL) generate_quiz();
    return questions_obj;
}

char* quiz_server(cJSON* request) {
    //TODO: validate user
    get_questions();

    char* username = get_from_protocol_string(request, "FROM");
    char* token = get_from_protocol_string(request, "TOKEN");

    cJSON* response = create_protocol();

    if (username == NULL || token == NULL) {
        printf("Error: Quiz server: username or token is null\n"); fflush(stdout);
    } else {

        char* subaction = get_from_protocol_string(request, "SUBACTION");

        if (subaction == NULL) {

            printf("Error: Quiz server: subaction is null\n"); fflush(stdout);

        } else {
                // printf("there we go\n");fflush(stdout);

            if (strcmp(subaction, "GET QUESTION") == 0) {
                
                int question_index = rand() % q_number;
                char* question_index_str = mx_itoa(question_index);
                cJSON* question  = get_from_protocol(questions_obj, question_index_str);


                char*  question_str = cJSON_Print(question);

                add_to_protocol_string(response, "DATA", question_str);
                add_to_protocol_string(response, "QUESTION INDEX", question_index_str);
                add_to_protocol_string(response, "STATUS", "OK");

                free(question_index_str);
                free(question_str);

            } else if (strcmp(subaction, "CHECK ANSWER") == 0) {
                
                add_to_protocol_string(response, "STATUS", "OK");
                char* answer = get_from_protocol_string(request, "DATA");
                if (answer != NULL) {
                    char*  question_index_str = get_from_protocol_string(request, "QUESTION INDEX");

                    if (question_index_str == NULL) {
                        cJSON_DeleteItemFromObject(response, "STATUS");
                        add_to_protocol_string(response, "STATUS", "ERROR");
                        printf("Error: Question index is null\n");
                    } else {
                        int question_index = atoi(question_index_str);

                        cJSON* question = get_from_protocol(questions_obj, question_index_str);

                        if (question == NULL) {
                            cJSON_DeleteItemFromObject(response, "STATUS");
                            add_to_protocol_string(response, "STATUS", "ERROR");
                            printf("Error: Question with index %s is undefined\n", question_index_str);
                        } else {
                            // if question == NULL && if question index str == NULL

                            char* correct_answer = get_from_protocol_string(question, "CORRECT_ANSWER");

                            if  (strcmp(answer, correct_answer) == 0) {
                                // update user money
                                update_user_money(username, 1);
                                add_to_protocol_string(response, "DATA", "CORRECT");
                            } else {
                                // update user  money
                                update_user_money(username, -1);
                                add_to_protocol_string(response, "DATA", "INCORRECT");
                            }
                        }
                    }

                    
                } else {
                    printf("Error: Quiz server: answer is null\n"); fflush(stdout);
                }

            } else {
                printf("Error: Quiz server: subaction is undefined\n"); fflush(stdout);
            }
        }

    }

    char* response_str = cJSON_Print(response);

    cJSON_Delete(response);

    return response_str;

}