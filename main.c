#include <gtk/gtk.h>
#include "GUI/windowsetup.h"

int main(int argc, char *argv[]) {
	GtkWidget * mainWindow = setupMainWindow("SimpleChat", &argc, &argv);
	gtk_main();
	return 0;
}
