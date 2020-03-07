#ifndef WINDOWSETUP_H
#define WINDOWSETUP_H
#include <gtk/gtk.h>

GtkWidget * setupMainWindow(const char * windowName, int * arc, char *** argv, char setupDialogs);

GtkWidget * setupNicknameDialog(GtkWidget * parent);

GtkWidget * setupConnectDialog(GtkWidget * parent);

#endif
