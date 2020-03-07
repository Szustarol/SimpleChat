#ifndef PROGRAMDATA_H
#define PROGRAMDATA_H
#include <gtk/gtk.h>

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

extern address_package program_connection;
extern char program_nickname[64];
extern char program_lastnickname[64];
extern bool program_shouldSendMessage;
extern bool program_shouldConnect;
extern bool program_shouldDisconnect;
extern bool program_shouldHost;
extern bool program_connected;
extern bool program_changedNickname;
extern GtkWidget * program_statusLabel;
extern GtkWidget * program_nicknameDialog;
extern GtkWidget * program_connectDialog;


#endif
