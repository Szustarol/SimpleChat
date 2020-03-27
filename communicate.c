#include "communicate.h"
#include "SERVER/serverloop.h"
#include <stdio.h>

void server_incomingSignal(const int signal){
    switch(signal){
        case SIGUSR1:
            server_shouldHost = 1;
            break;
        case SIGUSR2:
            server_shouldQuit = 1;
            break;
        case SIGTERM:
            server_shouldQuit = 1;
            server_shouldTerminate = 1;
            break;
        default:
            puts("Received unspecified signal");
    }
}