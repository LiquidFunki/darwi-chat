#include "send_request.h"
#include "pthread.h"
#include "encrypt.h"

static int sock_fd = 0;
static int new_messages_socket = 0;
pthread_t* new_messages_thread = NULL;
static char* request = NULL;
static struct sockaddr_in* serv_addr;
// static char* response = NULL;

void set_new_messages_socket(int socket) {
    new_messages_socket = socket;
}

void set_new_messages_thread(pthread_t* thread) {
    new_messages_thread = thread;
}

void close_connection() {

    cJSON* protocol = create_protocol();

    
    add_to_protocol_string(protocol, "ACTION", "CLOSE CONNECTION");
    char* request = cJSON_Print(protocol);

    char* response = send_request(request, get_server_ip(), PORT);
    free(response);

    close(sock_fd);
    if (new_messages_thread) {
        pthread_cancel(*new_messages_thread);
    }
    close(new_messages_socket);
    sock_fd = 0;
    new_messages_socket = 0;
    new_messages_thread = NULL;
}

struct sockaddr_in* get_serv_addr() {
    return serv_addr;
}

char* read_response(int sock_fd) {

    char* response = mx_strnew(READ_SIZE);
    int read_size = 0;

    while ( (read_size = read(sock_fd, response, READ_SIZE - 1)) > 0 )
    {
        // response[read_size - 1] = '\0';
    }
    
    return response;
}

void* connect_to_server(char* ip, int port) {
    
    serv_addr = malloc(sizeof(struct sockaddr_in));
    
    memset(serv_addr, '0', sizeof(*serv_addr));

    if((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Error : Could not create socket \n");
        return NULL;
    }


    serv_addr->sin_family = AF_INET;
    serv_addr->sin_port   = htons(port);

    if(inet_pton(AF_INET, ip, &(serv_addr->sin_addr)) <= 0)
    {
        printf("\n inet_pton error occured\n");
        return NULL;
    }

    if (connect(sock_fd, (struct sockaddr *)serv_addr, sizeof(*serv_addr)) < 0) {
        printf("\n Error : Connect Failed \n");
        return NULL;
    }
    return "OK";
}

typedef struct s_request_response {
    char* request;
    char* response;
}              t_request_response;

void* request_thread(void* arg) {

    t_request_response* request_response = (t_request_response*)arg;

    // char *buffer = encrypt_pswd(request_response->request);


    send(sock_fd, request_response->request, strlen(request_response->request), 0);
    // free(request_response->request);
    // char* response = read_response(sock_fd);
    recv(sock_fd, request_response->response, READ_SIZE, 0);

    pthread_exit(NULL);
}

static pthread_t thread;

pthread_t* get_current_thread() {
    return &thread;
}

char* send_request(char*  request_str, char* ip, int port) {

    if (request == NULL) {
        request = mx_strnew(READ_SIZE);
    }

    // printf("%s", request);

    // int sock_fd = 0;
    if (sock_fd == 0) {
        connect_to_server(ip, port);
    }

    int request_len = strlen(request_str);
    strcpy(request, request_str);

    request[request_len++] = '\r';
    request[request_len++] = '\n';

    char* response = mx_strnew(READ_SIZE);


    t_request_response* request_response = (t_request_response*)malloc(sizeof(t_request_response));
    request_response->request = request;
    request_response->response = response;

    // pthread_t thread;
    pthread_create(&thread, NULL, request_thread, request_response);
    pthread_join(thread, NULL);

    memset(request, request_len, '\0');
    // printf("response: %s\n", response);

    // sendto(sock_fd, request, strlen(request), 0, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    // send(sock_fd, request, strlen(request), 0);
    // free(request);
    // char* response = mx_strnew(READ_SIZE);
    // // char* response = read_response(sock_fd);
    // recv(sock_fd, response, READ_SIZE, 0);
    // char* response = NULL;


    return response;
}
