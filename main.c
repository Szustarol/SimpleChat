#include <gtk/gtk.h>
#include "GUI/windowsetup.h"
#include "programdata.h"
#include "SERVER/serverloop.h"
#include "CLIENT/clientloop.h"

int main(int argc, char *argv[]) {
	program_childPID = fork();
	if(program_childPID){
		server_serverLoop();
	}
	else{
		setupMainWindow("SimpleChat", &argc, &argv, 1);
		program_clientLoopIdentifier = g_timeout_add(0, client_clientLoop, NULL);
		gtk_main();
	}

	return 0;
}
