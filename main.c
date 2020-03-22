#include <gtk/gtk.h>
#include <signal.h>
#include "GUI/windowsetup.h"
#include "programdata.h"
#include "SERVER/serverloop.h"
#include "CLIENT/clientloop.h"
#include "communicate.h"

/*
 the server is always running, but is not always active - when it receives SIGUSR1,
 it sets up the socket and binds it. If the user never hosts, the server does nothing.
 IF the server receives SIGUSR2, it means that the user is a host, and it want's to stop
 hosting, so the server should close the socket, but still be ready to start when asked to.
 SIGTERM is sent when the user closes the application, the server sends the quit message to 
 all the connected clients, closes all active sockets and returns.
*/

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
