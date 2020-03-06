#ifndef WINDOWHANDLERS_H
#define WINDOWHANDLERS_H

#include <gtk/gtk.h>

void nicknameChangeHandler(GtkWidget * widget, gpointer data);
void nicknameChangeDoneHandler(GtkWidget * widget, gint response_id, gpointer data);
void disconnectHandler(GtkWidget * widget, gpointer data);
void connectHandler(GtkWidget * widget, gpointer data);
void quitHandler(GtkWidget * widget, gpointer data);

#endif
