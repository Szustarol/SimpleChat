#include "programdata.h"

#define bool char

char program_lastnickname[64];
char program_nickname[64] = "User";
bool program_shouldSendMessage = FALSE;
bool program_connected = FALSE;
bool program_shouldConnect = FALSE;
bool program_changedNickname = TRUE;
bool program_shouldDisconnect = FALSE;
bool program_shouldHost = FALSE;
bool program_shouldHalt = FALSE;
bool program_isHosting = FALSE;
bool program_isServer = FALSE;
pid_t program_childPID;

int program_clientLoopIdentifier;

GtkWidget * program_nicknameDialog;
GtkWidget * program_connectDialog;

GtkWidget * program_statusLabel = NULL;

GtkWidget * program_connectItem = NULL;
GtkWidget * program_disconnectItem = NULL;
GtkWidget * program_hostItem = NULL;

address_package program_connection = {.IP1 = 192, .IP2 = 168, .IP3 = 1, .IP4 = 1};
