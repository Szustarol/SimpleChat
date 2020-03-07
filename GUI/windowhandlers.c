#include "windowhandlers.h"
#include "../programdata.h"

void nicknameChangeHandler(GtkWidget * widget, gpointer data){
	gtk_widget_show_all(program_nicknameDialog);
	gtk_dialog_run(GTK_DIALOG(program_nicknameDialog));
}

void hostHandler(GtkWidget * widget, gpointer data){
	if(program_shouldDisconnect != TRUE)
		program_shouldHost = TRUE;
}

void nicknameChangeDoneHandler(GtkWidget * widget, gint response_id, gpointer data){
	GtkWidget * entry = data;
	if(response_id == GTK_RESPONSE_REJECT || response_id == GTK_RESPONSE_DELETE_EVENT){
		gtk_entry_set_text(GTK_ENTRY(entry), program_nickname);
	}
	else{
		const char * newname = gtk_entry_get_text(GTK_ENTRY(entry));
		if(strlen(newname) < 1)
			gtk_entry_set_text(GTK_ENTRY(entry), program_nickname);
		else{
			memcpy(program_lastnickname, program_nickname, 64*sizeof(char));
			memcpy(program_nickname, newname, 64*sizeof(char));
			program_changedNickname = TRUE;
		}
	}
	gtk_widget_hide(widget);
}

void connectionDoneHandler(GtkWidget * widget, gint response_id, gpointer data){
	program_connectionData * cdt = (program_connectionData*)data;
	if(response_id == GTK_RESPONSE_REJECT || response_id == GTK_RESPONSE_DELETE_EVENT){
		char buff[4];
		sprintf(buff, "%u", program_connection.IP1);
		gtk_entry_set_text(GTK_ENTRY(cdt->IP1), buff);
		sprintf(buff, "%u", program_connection.IP2);
		gtk_entry_set_text(GTK_ENTRY(cdt->IP2), buff);
		sprintf(buff, "%u", program_connection.IP3);
		gtk_entry_set_text(GTK_ENTRY(cdt->IP3), buff);
		sprintf(buff, "%u", program_connection.IP4);
		gtk_entry_set_text(GTK_ENTRY(cdt->IP4), buff);
	}
	else{
		program_connection.IP1 = atoi(gtk_entry_get_text(GTK_ENTRY(cdt->IP1)));
		program_connection.IP2 = atoi(gtk_entry_get_text(GTK_ENTRY(cdt->IP2)));
		program_connection.IP3 = atoi(gtk_entry_get_text(GTK_ENTRY(cdt->IP3)));
		program_connection.IP4 = atoi(gtk_entry_get_text(GTK_ENTRY(cdt->IP4)));
		program_shouldConnect = TRUE;
	}
	gtk_widget_hide(widget);
}

void disconnectHandler(GtkWidget * widget, gpointer data){
	program_shouldDisconnect = TRUE;
}

void connectHandler(GtkWidget * widget, gpointer data){
	if(program_shouldDisconnect != TRUE){
		gtk_widget_show_all(program_connectDialog);
		gtk_dialog_run(GTK_DIALOG(program_connectDialog));
	}
}

void quitHandler(GtkWidget * widget, gpointer data){
	program_shouldHalt = TRUE;
}

void numberOnlyInsertionHandler(GtkEntry * widget, const gchar * text, gint length, gint * position, gpointer data){
	char foundflag = FALSE;
	for(unsigned i = 0; i < length; i++){
		if(text[i] < '0' || text[i] > '9'){
			foundflag = TRUE;
			break;
		}
	}
	if(foundflag == FALSE){
		g_signal_handlers_block_by_func(G_OBJECT(widget), G_CALLBACK(numberOnlyInsertionHandler), data);
		gtk_editable_insert_text(GTK_EDITABLE(widget), text, length, position);
		g_signal_handlers_unblock_by_func(G_OBJECT(widget), G_CALLBACK(numberOnlyInsertionHandler), data);
	}
	g_signal_stop_emission_by_name(G_OBJECT(widget), "insert_text");
}
