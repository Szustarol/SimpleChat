#ifndef SERVERLOOP_H
#define SERVERLOOP_H

#include <signal.h>

char server_shouldQuit;
char server_shouldHost;

void server_serverLoop();

#endif
