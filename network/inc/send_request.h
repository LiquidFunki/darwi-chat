#ifndef SEND_REQUEST_H
#define SEND_REQUEST_H

#include "libmx.h"

// #if      defined(_MSC_VER) \
//         ||defined(__WIN32__) \
//         ||defined(_WIN32)\
//         ||defined(__WIN32)\
//         ||defined(WIN32)\
//         ||defined(__WINNT)\
//         ||defined(__WINNT__)\
//         ||defined(_WINNT)\
//         ||defined(WINNT)
// #include <winsock2.h>
// #include <windows.h>
// #include <Ws2tcpip.h>
// #include <sys/timeb.h>
// #elif   defined(__linux) \
//        ||defined(__linux__)\
//        ||defined(linux)\
//        ||defined(_linux)
// #include <sys/socket.h>
// #include <netinet/in.h>
// #include <netdb.h>
// #include <arpa/inet.h>
// #elif defined(__unix) \
//        ||defined(_unix) \
//        ||defined(__unix__) \
//        ||defined(unix) 
// #include <sys/socket.h>
// #include <netinet/in.h>
// #include <netdb.h>
// #include <arpa/inet.h>
//        #if      defined(__APPLE__) 
// #include <sys/socket.h>
// #include <netinet/in.h>
// #include <netdb.h>
// #include <arpa/inet.h>
//       #endif
// #else
// # error Cannot determine OS type
// #endif

//////////////////////////////

// #include <winsock2.h>
// #include <windows.h>
// #include <Ws2tcpip.h>
// #include <sys/timeb.h>


/////////////////////////////

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <pthread.h>

#include "protocol.h"


#define BUFFER_SIZE 4096
#define SEND_SIZE   5120

char* send_request(char*  request, char* ip, int port);
struct sockaddr_in* get_serv_addr();
pthread_t* get_current_thread();

void set_new_messages_socket(int socket);
void set_new_messages_thread(pthread_t* thread);
void close_connection();


#endif
