#include "programdata.h"

#define bool char

char program_lastnickname[64];
char program_nickname[64] = "User";
bool program_shouldSendMessage = FALSE;
bool program_connected = FALSE;
bool program_shoulReconnect = FALSE;
bool program_changedNickname = FALSE;


GtkWidget * program_nicknameDialog;
GtkWidget * program_connectDialog;

GtkWidget * program_statusLabel = NULL;
