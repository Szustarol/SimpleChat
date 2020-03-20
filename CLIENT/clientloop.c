#include "clientloop.h"
#include "../communicate.h"
#include "../programdata.h"
#include "../GUI/contentupdate.h"
#include <signal.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h>

#define UNUSED(x) (void)(x)

int client_sockfd = -1;

struct timeval client_wait;
fd_set client_descset;

struct sockaddr_in client_connaddr;

void client_init(void){
	client_sockfd = socket(AF_INET, SOCK_STREAM, 0);

	client_connaddr.sin_family = AF_INET;
	client_connaddr.sin_port = htons(6660);
	inet_pton(AF_INET, "127.0.0.1", &(client_connaddr.sin_addr));


	client_wait.tv_sec = 0;
	client_wait.tv_usec = 50;

	program_inputBuffer[0] = 0x0;
}

gint client_clientLoop(gpointer data){
	UNUSED(data);
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


		write(client_sockfd, "Server online.\n\0", strlen("Server online.\n\0")+1);
		setConnected(TRUE);
	}
	if(program_shouldDisconnect){

		char buffer[64+40];

		buffer[64+39] = 0x0;

		snprintf(buffer, 64+40, "[%s]: %s\n", program_nickname, "has left the server.");

		write(client_sockfd, buffer, strlen(buffer));

		program_shouldDisconnect = FALSE;
		if(program_isHosting){
			program_isHosting = FALSE;
			kill(program_childPID, SIGUSR2);
		}

		char inpBuff[MSG_MAXLEN+1];
		inpBuff[MSG_MAXLEN] = 0x0;
		usleep(150);
		FD_ZERO(&client_descset);
		FD_SET(client_sockfd, &client_descset);

		client_wait.tv_usec = 700;
		memset(inpBuff, 0x0, MSG_MAXLEN);

		while(select(client_sockfd+1, &client_descset, NULL, NULL, &client_wait) > 0){
			usleep(100);
			read(client_sockfd, inpBuff, MSG_MAXLEN);

			contentAppendText(inpBuff);
			FD_ZERO(&client_descset);
			FD_SET(client_sockfd, &client_descset);
			usleep(300);
		}

		client_wait.tv_usec = 50;

		close(client_sockfd);

		client_sockfd = socket(AF_INET, SOCK_STREAM, 0);

		setConnected(FALSE);
	}
	if(program_changedNickname){
		updateStatusLabel(0);
		program_changedNickname = FALSE;
		if(program_connected){
			char nickchgbuf[64+64+40];
			snprintf(nickchgbuf, 64+64+40, "%s has changed nickname to %s.\n", program_lastnickname, program_nickname);
			write(client_sockfd, nickchgbuf, strlen(nickchgbuf));
		}
	}
	if(program_shouldConnect){
		program_shouldConnect = FALSE;

		program_connectionDataToNumeric(&client_connaddr);

		int cnr;
		//try to connect 5 times
		for(int i = 0; i < 5; i++){
			cnr = connect(client_sockfd, (struct sockaddr *)&client_connaddr, sizeof(client_connaddr));
			if(cnr != 0)
				usleep(100);
			else
				break;
		}

		char connBuff[64+30];
		snprintf(connBuff, 64+30, "%s has connected to the server.\n", program_nickname);

		write(client_sockfd, connBuff, strlen(connBuff));
		if(cnr == 0)
			setConnected(TRUE);
		else
			contentAppendText("Connection failure\n");
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

			if(r > 0){
				inpBuff[r] = 0x0;
				contentAppendText(inpBuff);
			}

			if(strcmp(inpBuff, "Server is closing.\n") == 0){
				close(client_sockfd);
				setConnected(FALSE);
			}

		}
	}
	if(program_connected && program_inputBuffer[0] != 0){ //data is to be sent
		char nicknamebuff[70];
		snprintf(nicknamebuff, 70, "[%s]: ", program_nickname);
		write(client_sockfd, nicknamebuff, strlen(nicknamebuff));
		write(client_sockfd, program_inputBuffer, strlen(program_inputBuffer));
		program_inputBuffer[0] = 0x0;
	}
	else if(program_inputBuffer[0] != 0)
		program_inputBuffer[0] = 0;
	return G_SOURCE_CONTINUE;
}
