#include <gtk/gtk.h>
#include <signal.h>
#include "GUI/windowsetup.h"
#include "programdata.h"
#include "SERVER/serverloop.h"
#include "CLIENT/clientloop.h"
#include "communicate.h"

int main(int argc, char *argv[]) {
	program_childPID = fork();
	if(program_childPID == 0){
		struct sigaction s;
		sigemptyset(&s.sa_mask);
		s.sa_flags = 0;
		s.sa_handler = server_incomingSignal;
		sigaction(SIGUSR1, &s, NULL);
		sigaction(SIGUSR2, &s, NULL);
		sigaction(SIGTERM, &s, NULL);
		server_serverLoop();
		server_serverCleanup();
	}
	else{
		client_init();
		setupMainWindow("SimpleChat", &argc, &argv, 1);
		program_clientLoopIdentifier = g_timeout_add(0, client_clientLoop, NULL);
		gtk_main();
	}

	return 0;
}
