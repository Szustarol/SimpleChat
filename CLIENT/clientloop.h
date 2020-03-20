#ifndef CLIENTLOOP_H
#define CLIENTLOOP_H
#include <gtk/gtk.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/select.h>

int client_sockfd;

struct sockaddr_in client_connaddr;


gint client_clientLoop(gpointer data);
void client_init(void);

struct timeval client_wait;
fd_set client_descset;

#endif
