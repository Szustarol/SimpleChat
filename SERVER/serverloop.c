#include "serverloop.h"
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>

pthread_mutex_t clientsmutex = PTHREAD_MUTEX_INITIALIZER;

char server_shouldQuit = 0;
char server_shouldHost = 0;
char server_initialised = 0;
char server_shouldTerminate = 0;
int _Atomic server_clientCount = 0;
char _Atomic terminate_clients = 0;
int server_connfd = -1;
int server_listenfd = -1;
struct sockaddr_in server_addr;
struct sockaddr_in incoming_addr;
struct timeval server_wait = {.tv_sec = 0, .tv_usec = 400};
fd_set server_descset;

void server_serverInit(){
	memset(clients, 0x0, sizeof(client_addr*)*MAX_CONNECTIONS);
	server_initialised = 1;
	server_listenfd = socket(AF_INET, SOCK_STREAM, 0);

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(194);
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	bind(server_listenfd, (struct sockaddr*)&server_addr, sizeof(server_addr));

	listen(server_listenfd, 10);

	server_clientCount = 0;
}

void server_sendAll(char * message){
	pthread_mutex_lock(&clientsmutex);
	pthread_mutex_unlock(&clientsmutex);
	int messagelen = strlen(message);
	for(int i = 0; i < MAX_CONNECTIONS; i++){
		//try writing three times
		int byteswritten = write(clients[i]->connfd, message, messagelen);
		if(byteswritten == messagelen)
			continue;
		byteswritten += write(clients[i]->connfd, message+byteswritten, messagelen-byteswritten);
		if(byteswritten == messagelen)
			continue;
		byteswritten += write(clients[i]->connfd, message+byteswritten, messagelen-byteswritten);
		
	}
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
		if(clients[i] == client)
			free(clients[i]);
	pthread_mutex_unlock(&clientsmutex);
	server_clientCount--;

	pthread_detach(pthread_self());
	return NULL;
}

void server_serverLoop(){
	while(server_shouldTerminate == 0){
		if(server_shouldHost){
			server_shouldHost = 0;
			server_serverInit();
			server_initialised = 1;
		}
		if(server_initialised && !server_shouldQuit){
			FD_ZERO(&server_descset);
			FD_SET(server_listenfd, &server_descset);

			int r = select(server_listenfd + 1, &server_descset, NULL, NULL, &server_wait);

			if(r > 0){
				socklen_t client_len = sizeof(incoming_addr);

				server_connfd = accept(server_listenfd, (struct sockaddr*)&incoming_addr, &client_len);

				if(server_clientCount+1 >= MAX_CONNECTIONS){
					close(server_connfd);
				}

				client_addr * c = (client_addr*)malloc(sizeof(client_addr));
				c->addr = incoming_addr;
				c->connfd = server_connfd;
					
				for(int i = 0; i < MAX_CONNECTIONS; i++){
					if(clients[i] == 0x0){
						clients[i] = c;
						break;
					}
				}

				pthread_t threadid;

				server_clientCount++;
				pthread_create(&threadid, NULL, &server_parseClient, (void*)c);
			}
		}

		if(server_initialised && server_shouldQuit){
			close(server_listenfd);
			server_serverCleanup();
		}

	}
}

void server_serverCleanup(){
	for(int i = 0; i < MAX_CONNECTIONS; i++){
		if(clients[i] != 0x0)
			free(clients[i]);
	}
}
