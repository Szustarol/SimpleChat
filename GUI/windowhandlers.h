#ifndef WINDOWHANDLERS_H
#define WINDOWHANDLERS_H

#include <gtk/gtk.h>

void nicknameChangeHandler(GtkWidget * widget, gpointer data);
void nicknameChangeDoneHandler(GtkWidget * widget, gint response_id, gpointer data);
void disconnectHandler(GtkWidget * widget, gpointer data);
void hostHandler(GtkWidget * widget, gpointer data);
void connectHandler(GtkWidget * widget, gpointer data);
void connectionDoneHandler(GtkWidget * widget, gint response_id, gpointer data);
void quitHandler(GtkWidget * widget, gpointer data);
void numberOnlyInsertionHandler(GtkEntry * widget, const gchar * text, gint length, gint * position, gpointer data);
void textEnteredHandler(GtkWidget * widget, gpointer data);

#endif
