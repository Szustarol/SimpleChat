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

char volatile _Atomic server_initialised;
char volatile _Atomic server_shouldQuit;
char volatile _Atomic server_shouldHost;
char volatile _Atomic server_shouldTerminate;

/*
These are static-defined:
int server_connfd;
int server_listenfd;
struct sockaddr_in server_addr;
struct sockaddr_in incoming_addr;

struct timeval server_wait;
fd_set server_descset;
*/

void server_serverInit(void);
void server_serverLoop(void);
void server_serverCleanup(void);
void server_sendAll(char * message);
int server_waitFd(int fd);
void * server_parseClient(void * clientStruct);

#endif
