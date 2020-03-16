#include "clientloop.h"
#include "../communicate.h"
#include "../programdata.h"
#include "../GUI/contentupdate.h"
#include <signal.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h>

int client_sockfd = -1;

struct timeval client_wait;
fd_set client_descset;

struct sockaddr_in client_connaddr;

void client_init(){
	client_sockfd = socket(AF_INET, SOCK_STREAM, 0);

	client_connaddr.sin_family = AF_INET;
	client_connaddr.sin_port = htons(6660);
	inet_pton(AF_INET, "127.0.0.1", &(client_connaddr.sin_addr));


	client_wait.tv_sec = 0;
	client_wait.tv_usec = 50;

}

gint client_clientLoop(gpointer data){
	while(gtk_events_pending())
		gtk_main_iteration();

	if(program_shouldHost){
		program_shouldHost = FALSE;
		program_isHosting = TRUE;

		kill(program_childPID, SIGUSR1);

		inet_pton(AF_INET, "127.0.0.1", &(client_connaddr.sin_addr));
		int cnr;
		errno = 0;

		usleep(300);
		
		//try to connect 5 times
		for(int i = 0; i < 5; i++){
			cnr = connect(client_sockfd, (struct sockaddr *)&client_connaddr, sizeof(client_connaddr));
			if(cnr != 0)
				usleep(100);
			else
				break;
		}


		write(client_sockfd, "CONNECTED\n\0", strlen("CONNECTED\n\0")+1);
		setConnected(TRUE);
	}
	if(program_shouldDisconnect){
		program_shouldDisconnect = FALSE;
		if(program_isHosting)
			kill(program_childPID, SIGUSR2);

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
		kill(program_childPID, SIGTERM);
		g_source_remove(program_clientLoopIdentifier);
		//gtk_main_iteration();
		gtk_main_quit();
		return G_SOURCE_REMOVE;
	}
	if(program_connected){
		FD_ZERO(&client_descset);
		FD_SET(client_sockfd, &client_descset);

		int r = select(client_sockfd + 1, &client_descset, NULL, NULL, &client_wait);

		if(r > 0){
			char inpBuff[MSG_MAXLEN+1];
			inpBuff[MSG_MAXLEN] = 0;
			int r;
			r = read(client_sockfd, inpBuff, MSG_MAXLEN);

			if(r > 0)	
				contentAppendText(inpBuff);
		}
	}
	return G_SOURCE_CONTINUE;
}
