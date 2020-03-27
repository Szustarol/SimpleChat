#include "programdata.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

bool program_connected = FALSE;
bool program_changedNickname = TRUE;
bool program_isServer = FALSE;
bool program_isHosting = FALSE;

bool program_shouldSendMessage = FALSE;
bool program_shouldConnect = FALSE;
bool program_shouldDisconnect = FALSE;
bool program_shouldHost = FALSE;
bool program_shouldHalt = FALSE;

int program_clientLoopIdentifier;
pid_t program_childPID;


GtkWidget * program_nicknameDialog;
GtkWidget * program_connectDialog;
GtkWidget * program_statusLabel = NULL;
GtkWidget * program_connectItem = NULL;
GtkWidget * program_disconnectItem = NULL;
GtkWidget * program_hostItem = NULL;


char program_inputBuffer[BUFFER_LEN];
char program_lastnickname[64];
char program_nickname[64] = "User";
GtkTextBuffer * program_mainTextBuffer = NULL;
address_package program_connection = {.IP1 = 192, .IP2 = 168, .IP3 = 1, .IP4 = 1};


void program_connectionDataToNumeric(void * dest){
    struct sockaddr_in * target = (struct sockaddr_in *)dest;
    char buffer [32];
    buffer[31] = 0x0;
    snprintf(buffer, 31, "%u.%u.%u.%u",
        program_connection.IP1,
        program_connection.IP2,
        program_connection.IP3,
        program_connection.IP4);

    puts(buffer);
    
    inet_pton(AF_INET, buffer, &(target->sin_addr));
}