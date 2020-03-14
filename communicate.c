#include "communicate.h"
#include "SERVER/serverloop.h"

void server_incomingSignal(const int signal){
    switch(message_type){
        case SERVER_ESTABLISH:
            server_shouldHost = 1;
            break;
        case SERVER_CLOSE:
            server_shouldQuit = 1;
            break;
        case SERVER_DESTROY:
            server_shouldQuit = 1;
            server_shouldTerminate = 1;
            break;
    }
}