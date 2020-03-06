#ifndef PROGRAMDATA_H
#define PROGRAMDATA_H
#include <gtk/gtk.h>

#define bool char

extern char program_nickname[64];
extern char program_lastnickname[64];
extern bool program_shouldSendMessage;
extern bool program_shoulReconnect;
extern bool program_connected;
extern bool program_changedNickname;
extern GtkWidget * program_statusLabel;
extern GtkWidget * program_nicknameDialog;
extern GtkWidget * program_connectDialog;


#endif
