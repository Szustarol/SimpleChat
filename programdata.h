#ifndef PROGRAMDATA_H
#define PROGRAMDATA_H
#include <gtk/gtk.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct{
	GtkWidget * IP4;
	GtkWidget * IP3;
	GtkWidget * IP2;
	GtkWidget * IP1;
}program_connectionData;

typedef struct{
	uint8_t IP4;
	uint8_t IP3;
	uint8_t IP2;
	uint8_t IP1;
}address_package;

void program_connectionDataToNumeric(void * dest);

#define BUFFER_LEN 512+64
static const int MSG_MAXLEN = 512;
static const int SERVER_PORTNUM = 6660; //IRC PORT

//program state variables
extern bool program_connected;
extern bool program_changedNickname;
extern bool program_isServer;
extern bool program_isHosting;

//program operational flags
extern bool program_shouldSendMessage;
extern bool program_shouldConnect;
extern bool program_shouldDisconnect;
extern bool program_shouldHost;
extern bool program_shouldHalt;

//cross-thread communcation data
extern int	program_clientLoopIdentifier;
extern pid_t program_childPID;


//gtk items
extern GtkWidget * program_connectItem;
extern GtkWidget * program_disconnectItem;
extern GtkWidget * program_hostItem;
extern GtkWidget * program_statusLabel;
extern GtkWidget * program_nicknameDialog;
extern GtkWidget * program_connectDialog;

//buffers
extern char program_inputBuffer[BUFFER_LEN];
extern char program_nickname[64];
extern char program_lastnickname[64];
extern address_package program_connection;
extern GtkTextBuffer * program_mainTextBuffer;

#endif
