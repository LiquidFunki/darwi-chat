#include "server.h"

typedef struct s_user_connection {

    int read_fd;
    int write_fd;

}              t_user_connection;

static int active_users_number = 0;

t_user_connection active_users[50];

char* read_request(int conn_fd, char* request, int* read_number) {

    size_t buff_size = READ_SIZE;
    

    errno = 0;
    while ( (*read_number = read(conn_fd, request, buff_size - 1)) > 0 )
    {   
        // bzero(request, BUFFER_SIZE);
        request[*read_number - 1] = '\0';
        request[*read_number - 2] = '\0';
        // printf("there we go %i\n", *read_number);
        // fflush(stdout);

        // read_number = read(conn_fd, request, buff_size);
        break;
    }
    *read_number = *read_number - 2;
    if (*read_number < 500) {
        printf("request:\n%s\n", request);
    } else {
        printf("request too big\n");
    }

    return request;
}

static cJSON* new_message_sockets = NULL;
static cJSON* user_sockets        = NULL;
static int new_message_sockets_int[100];
static int new_message_sockets_int_count = 0;

int get_new_message_socket_of(char* username) {

    return get_from_protocol_number(new_message_sockets, username);

}

bool socket_in_new_message_sockets(int socket) {
    for (int i = 0; i < new_message_sockets_int_count; i++) {
        if  (new_message_sockets_int[i] == socket) {
            // printf("%s\n", "Socket for write new messages");
            return true;
        };
    }
    
    return false;
}

void add_new_message_socket(char* username, int socket) {

    if (new_message_sockets == NULL)
        new_message_sockets = cJSON_CreateObject();


    if (cJSON_GetObjectItem(new_message_sockets, username)) {
        cJSON_DeleteItemFromObject(new_message_sockets, username);
    }
    add_to_protocol_number(new_message_sockets, username, socket);
    
    new_message_sockets_int[new_message_sockets_int_count++] = socket;

}


void* handle_request(void* data) {
    int conn_fd = *((int*)data);
    char* request = calloc(READ_SIZE, sizeof(char));
    char* response_buffer = calloc(READ_SIZE, sizeof(char));
    int read_number = 0;
    size_t response_buffer_length = 0;
    printf("main connection: %i\n", conn_fd);
    // 
    while (1) {
        // read_request(conn_fd, request, &read_number);
        // if (!socket_in_new_message_sockets(conn_fd)) {
        int read_number = recv(conn_fd, request, 14336, 0);
        if (read_number) {
            // select_action(request, response_buffer);
            // char* buffer = decrypt_pswd(request);

            // printf("buffer: %s\n", request); fflush(stdout);

            cJSON* request_obj = cJSON_Parse(request);
            char* action = get_from_protocol_string(request_obj, "ACTION");
            char* username = get_from_protocol_string(request_obj, "FROM");
            if (action != NULL && username != NULL && strcmp(action, "ADD NEW MESSAGES SOCKET") == 0) {
                
                printf("there we go\n");
                fflush(stdout);
                add_new_message_socket(username, conn_fd);
                strcpy(response_buffer, "200 OK\r\n\r\n");
                send(conn_fd, response_buffer, 10, 0);
                break;
            }

            if (read_number < 500) {
                printf(request);
            } else {
                printf("request is too long\n");
            }
            select_action(request, response_buffer);
            // printf("response_buffer:\n %s\n", response_buffer);

            if (username && action && strcmp(action, "SIGN IN") == 0) {
                printf("there we go add to user tables\n");
                fflush(stdout);
                cJSON* response = cJSON_Parse(response_buffer); 
                char* status = get_from_protocol_string(response, "STATUS");

                char* conn_fd_str = NULL;
                if (strcmp(status, "SUCCESS")) {
                    conn_fd_str = mx_itoa(conn_fd);
                    add_to_protocol_string(user_sockets, conn_fd_str, username);
                }
                if (conn_fd_str)
                    free(conn_fd_str);
            }

            if (action && (strcmp(action, "CLOSE CONNECTION") == 0)) {
                
                printf("there we go but dont want\n");
                printf("socket is closed\n");
                char* conn_fd_str = mx_itoa(conn_fd);

                char* username = get_from_protocol_string(user_sockets, conn_fd_str);
                // check on null
                int new_message_user_socket = get_from_protocol_number(new_message_sockets, username);
                cJSON_DeleteItemFromObject(new_message_sockets, username);
                close(new_message_user_socket);
                cJSON_DeleteItemFromObject(user_sockets, conn_fd_str);

                free(conn_fd_str);
                break;
            }

            if (strlen(response_buffer) == 0)
                strcpy(response_buffer, "200 OK\r\n\r\n");

            response_buffer_length = strlen(response_buffer);
            // write(conn_fd, response_buffer, response_buffer_length);
            cJSON_Delete(request_obj);
            send(conn_fd, response_buffer, response_buffer_length, 0);
            

            
            // sendto(conn_fd, response_buffer, strlen(response_buffer), 0, (struct sockaddr *)&client, sizeof(client_addres));

            // close(conn_fd);
            // free(buffer);
            memset(response_buffer, '\0', response_buffer_length);
            memset(request, '\0', read_number);
        }
            // usleep(100);
        // } else {
            // printf("there we go\n");
            // fflush(stdout);
            // break;
        // }
        sleep(1);
        
    }
    // close(conn_fd);
    pthread_exit(NULL);
}

void create_user_thread(int conn_fd) {
    // запустить поток с conn_fd и циклом
    pthread_t user_thread;

    int* p_conn_fd = (int*)malloc(sizeof(int));
    *p_conn_fd = conn_fd;
    
    pthread_create(&user_thread, NULL, handle_request, p_conn_fd);

}

void run_server() {

    // init_tables();

    int listen_fd = 0, conn_fd = 0;
    struct sockaddr_in serv_addr;

    user_sockets = cJSON_CreateObject();

    // char* response_buffer = mx_strnew(READ_SIZE);

    memset(&serv_addr, '0', sizeof(serv_addr));


    listen_fd = socket(AF_INET, SOCK_STREAM, 0);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(S_PORT);

    bind(listen_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    if (listen(listen_fd, MAX_CONNECTIONS)) {
        perror("Error: ");
    } else {
        printf("Listening\n");
    }

    printf("server runned\n");

    // char* request = mx_strnew(14336);

    while (1)
    {
        struct sockaddr_in client;
        memset(&client, 0, sizeof(struct sockaddr));
        socklen_t client_len = (socklen_t)sizeof client;
        char client_addres[BUFFER_SIZE + 1];

        conn_fd = accept(listen_fd, (struct sockaddr*)&client, &client_len);

        // add thread

        // inet_ntop(AF_INET, &client, client_addres, BUFFER_SIZE);
        // int read_number = 0;
        // read_request(conn_fd, request, &read_number);
        
        // select_action(request, response_buffer);

        // if (strlen(response_buffer) == 0)
        //     strcpy(response_buffer, "200 OK\r\n\r\n");
        // // send(conn_fd, response_buffer, strlen(response_buffer), 0); 
        // size_t response_buffer_length = strlen(response_buffer);
        // write(conn_fd, response_buffer, response_buffer_length);
        // // sendto(conn_fd, response_buffer, strlen(response_buffer), 0, (struct sockaddr *)&client, sizeof(client_addres));

        // close(conn_fd);
        // memset(response_buffer, '\0', response_buffer_length);
        // memset(request, '\0', read_number);
        // sleep(1);
        create_user_thread(conn_fd);
    }
    

}
