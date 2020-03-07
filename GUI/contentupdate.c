#include "contentupdate.h"
#include "../programdata.h"

void updateStatusLabel(char connected){
	char buffer[128];
	static char * con = "Connected";
	static char * dcon = "Disconnected";
	char * src;
	if(connected) src = con;
	else src = dcon;
	sprintf(buffer, "<span color='green'>Nickname: %s, %s</span>", program_nickname, src);
	gtk_label_set_markup(GTK_LABEL(program_statusLabel), buffer);
}
