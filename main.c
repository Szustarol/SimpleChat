#include <gtk/gtk.h>
#include "GUI/windowsetup.h"

int main(int argc, char *argv[]) {
	setupMainWindow("SimpleChat", &argc, &argv, 1);
	gtk_main();
	return 0;
}
