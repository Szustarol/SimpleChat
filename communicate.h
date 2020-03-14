#ifndef COMMUNICATE_H
#define COMMUNICATE_H
#include "programdata.h"

typedef enum{
    SERVER_ESTABLISH,
    SERVER_CLOSE,
    SERVER_DESTROY
}server_messages;

enum client_messages{
    START_UNABLE
};

server_messages message_type;

void server_incomingSignal(const int signal);

#endif