#include "communicate.h"
#include "SERVER/serverloop.h"

void server_incomingSignal(const int signal){
    if(signal == SIGUSR1)
        server_shouldHost = 1;
    else if(signal == SIGUSR2)
        server_shouldQuit = 1;
    else if(signal == SIGTERM){
        server_shouldQuit = 1;
        server_shouldTerminate = 1;
    }
}