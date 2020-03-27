#include "serverloop.h"
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>
#include <errno.h>

pthread_mutex_t clientsmutex = PTHREAD_MUTEX_INITIALIZER;

char volatile _Atomic server_shouldQuit = 0;
char volatile _Atomic server_shouldHost = 0;
char volatile _Atomic server_initialised = 0;
char volatile _Atomic server_shouldTerminate = 0;
int _Atomic server_clientCount = 0;
char _Atomic terminate_clients = 0;
static int server_connfd = -1;
static int server_listenfd = -1;
static struct sockaddr_in server_addr;
static struct sockaddr_in incoming_addr;
static struct timeval server_wait = {.tv_sec = 0, .tv_usec = 400};
static fd_set server_descset;

void server_serverInit(void){
	memset(clients, 0x0, sizeof(client_addr*)*MAX_CONNECTIONS);
	server_initialised = 1;
	server_listenfd = socket(AF_INET, SOCK_STREAM, 0);

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(SERVER_PORTNUM);
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	errno = 0;
	bind(server_listenfd, (struct sockaddr*)&server_addr, sizeof(server_addr));

	printf("Bind return: %d\n", errno);

	listen(server_listenfd, 10);

	printf("Listen return: %d\n", errno);

	server_clientCount = 0;
}

void server_sendAll(char * message){
	pthread_mutex_lock(&clientsmutex);
	int messagelen = strlen(message);
	for(int i = 0; i < MAX_CONNECTIONS; i++){
		//try writing three times
		if(clients[i] == 0) continue;
		int byteswritten = write(clients[i]->connfd, message, messagelen);
		if(byteswritten == messagelen)
			continue;
		byteswritten += write(clients[i]->connfd, message+byteswritten, messagelen-byteswritten);
		if(byteswritten == messagelen)
			continue;
		byteswritten += write(clients[i]->connfd, message+byteswritten, messagelen-byteswritten);
		
	}
	pthread_mutex_unlock(&clientsmutex);
}

void * server_parseClient(void * clientStruct){
	int message_len = 0;
	client_addr * client = (client_addr*)clientStruct;
	char message[MSG_MAXLEN+1];
	message[MSG_MAXLEN] = 0;

	while( terminate_clients == 0 && (message_len = read(client->connfd, message, MSG_MAXLEN)) > 0){
		message[message_len] = 0x0;
		server_sendAll(message);
	}
	
	close(client->connfd);
	pthread_mutex_lock(&clientsmutex);
	for(int i = 0; i < MAX_CONNECTIONS; i++)
		if(clients[i] == client){
			free(clients[i]);
			clients[i] = 0x0;
			break;
		}
	pthread_mutex_unlock(&clientsmutex);
	server_clientCount--;

	pthread_detach(pthread_self());
	return NULL;
}

void server_serverLoop(void){
	while(server_shouldTerminate == 0){
		if(server_shouldHost){
			server_shouldHost = 0;
			server_serverInit();
			server_initialised = 1;
		}
		if(server_initialised && !server_shouldQuit){
			int r = server_waitFd(server_listenfd);
			if(r > 0){
				puts("incoming connection");
				socklen_t client_len = sizeof(incoming_addr);

				server_connfd = accept(server_listenfd, (struct sockaddr*)&incoming_addr, &client_len);

				if(server_clientCount+1 >= MAX_CONNECTIONS){
					close(server_connfd);
				}

				client_addr * c = (client_addr*)malloc(sizeof(client_addr));
				c->addr = incoming_addr;
				c->connfd = server_connfd;
					
				pthread_mutex_lock(&clientsmutex);
				for(int i = 0; i < MAX_CONNECTIONS; i++){
					if(clients[i] == 0x0){
						clients[i] = c;
						break;
					}
				}
				pthread_mutex_unlock(&clientsmutex);

				pthread_t threadid;

				server_clientCount++;
				pthread_create(&threadid, NULL, &server_parseClient, (void*)c);
			}
		}
		if(server_initialised && server_shouldQuit){
			server_serverCleanup();
		}
		if(terminate_clients){
			if(server_clientCount == 0)
				terminate_clients = 0;
		}
	}
	//in case termiation signal is fired while loop is in progress
	if(server_initialised && server_shouldQuit){
		server_serverCleanup();
	}
	if(terminate_clients){
		if(server_clientCount == 0)
			terminate_clients = 0;
	}
}

int server_waitFd(int fd){
	FD_ZERO(&server_descset);
	FD_SET(fd, &server_descset);
	
	return select(fd + 1, &server_descset, NULL, NULL, &server_wait);
}

void server_serverCleanup(void){
	char * quitstr = "Server is closing.\n\0";
	server_sendAll(quitstr);
	usleep(100);
	server_initialised = 0;
	terminate_clients = 1;
	close(server_listenfd);
	server_shouldQuit = 0;
}
