#include "windowhandlers.h"
#include "../programdata.h"

void nicknameChangeHandler(GtkWidget * widget, gpointer data){
	gtk_widget_show_all(program_nicknameDialog);
	gtk_dialog_run(GTK_DIALOG(program_nicknameDialog));
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

void disconnectHandler(GtkWidget * widget, gpointer data){
	program_shouldDisconnect = TRUE;
}

void connectHandler(GtkWidget * widget, gpointer data){
	gtk_widget_show_all(program_connectDialog);
	gtk_dialog_run(GTK_DIALOG(program_connectDialog));
	program_shouldDisconnect = TRUE;
}

void quitHandler(GtkWidget * widget, gpointer data){
	gtk_main_quit();
}
