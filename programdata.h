#ifndef PROGRAMDATA_H
#define PROGRAMDATA_H
#include <gtk/gtk.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdint.h>
#define bool char

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

static const int MSG_MAXLEN = 512;

extern pid_t program_childPID;
extern bool program_isServer;
extern bool program_isHosting;
extern GtkWidget * program_connectItem;
extern GtkWidget * program_disconnectItem;
extern GtkWidget * program_hostItem;
extern int	program_clientLoopIdentifier;
extern address_package program_connection;
extern char program_nickname[64];
extern char program_lastnickname[64];
extern bool program_shouldSendMessage;
extern bool program_shouldConnect;
extern bool program_shouldDisconnect;
extern bool program_shouldHost;
extern bool program_shouldHalt;
extern bool program_connected;
extern bool program_changedNickname;
extern GtkWidget * program_statusLabel;
extern GtkWidget * program_nicknameDialog;
extern GtkWidget * program_connectDialog;
extern GtkTextBuffer * program_mainTextBuffer;


#endif
