#ifndef SERVERLOOP_H
#define SERVERLOOP_H

#include "../programdata.h"
#include <signal.h>
#include <sys/socket.h>
#include <netinet/in.h>

pthread_mutex_t clientsmutex;
int _Atomic server_clientCount;
char _Atomic terminate_clients;

static const int MAX_CONNECTIONS = 40;

typedef struct{
    struct sockaddr_in addr;
    int connfd;
}client_addr;

client_addr * clients[40];

char server_initialised;
char server_shouldQuit;
char server_shouldHost;
char server_shouldTerminate;

int server_connfd;
int server_listenfd;
struct sockaddr_in server_addr;
struct sockaddr_in incoming_addr;

struct timeval server_wait;
fd_set server_descset;

void server_serverInit();
void server_serverLoop();
void server_serverCleanup();
void server_sendAll(char * message);
void * server_parseClient(void * clientStruct);

#endif
