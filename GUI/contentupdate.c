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

void contentAppendText(char * text){
	GtkTextIter iter;
	gtk_text_buffer_get_end_iter(GTK_TEXT_BUFFER(program_mainTextBuffer), &iter);
	gtk_text_buffer_insert(
		GTK_TEXT_BUFFER(program_mainTextBuffer),
		&iter,
		text,
		strlen(text)
	);
}

void setConnected(char connected){
	if(connected == TRUE){
		gtk_widget_set_sensitive(program_disconnectItem, TRUE);
		gtk_widget_set_sensitive(program_connectItem, FALSE);
		gtk_widget_set_sensitive(program_hostItem, FALSE);
		program_connected = TRUE;
	}
	else{
		gtk_widget_set_sensitive(program_disconnectItem, FALSE);
		gtk_widget_set_sensitive(program_connectItem, TRUE);
		gtk_widget_set_sensitive(program_hostItem, TRUE);
		program_connected = FALSE;
	}
}
