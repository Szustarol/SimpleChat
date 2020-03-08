#include "clientloop.h"
#include "../programdata.h"
#include "../GUI/contentupdate.h"
#include <signal.h>

gint client_clientLoop(gpointer data){
	while(gtk_events_pending())
		gtk_main_iteration();

	if(program_shouldHost){
		program_shouldHost = FALSE;
		setConnected(TRUE);
	}
	if(program_shouldDisconnect){
		program_shouldDisconnect = FALSE;
		setConnected(FALSE);
	}
	if(program_changedNickname){
		updateStatusLabel(0);
		program_changedNickname = FALSE;
	}
	if(program_shouldConnect){
		program_shouldConnect = FALSE;
		setConnected(TRUE);
	}
	if(program_shouldHalt == TRUE){
		g_source_remove(program_clientLoopIdentifier);
		//gtk_main_iteration();
		gtk_main_quit();
		return G_SOURCE_REMOVE;
	}
	return G_SOURCE_CONTINUE;
}
