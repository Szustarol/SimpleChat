#include <gtk/gtk.h>
#include "GUI/windowsetup.h"
#include "SERVER/serverloop.h"

int main(int argc, char *argv[]) {
	setupMainWindow("SimpleChat", &argc, &argv, 1);
	gtk_main();
	return 0;
}
