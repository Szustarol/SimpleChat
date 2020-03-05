#include "windowsetup.h"

GtkWidget * setupMainWindow(const char * windowName, int * argc, char *** argv){
	gtk_init(argc, argv);

	GtkWidget * mainWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);

	gtk_widget_set_size_request(GTK_WIDGET(mainWindow), 400, 200);

	g_signal_connect(mainWindow, "destroy", G_CALLBACK(gtk_main_quit), NULL);

	gtk_window_set_title(GTK_WINDOW(mainWindow), windowName);

	GtkWidget * main_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

	gtk_container_add(GTK_CONTAINER(mainWindow), main_vbox);

	GtkWidget * menubar;
	menubar = gtk_menu_bar_new();

	GtkWidget * inputLabel = gtk_label_new("Input message: ");

	GtkWidget * quit_item, *nickname_item, *connect_item, *disconnect_item;

	GtkWidget * mainArea = gtk_text_view_new();
	GtkWidget * mainAreaFrame = gtk_frame_new(NULL);
	GtkWidget * mainAreaWindow = gtk_scrolled_window_new(NULL, NULL);

	GtkWidget * inputArea = gtk_entry_new();
	GtkWidget * inputAreaFrame = gtk_frame_new(NULL);
	GtkWidget * inputAreaBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);

	gtk_text_view_set_editable(GTK_TEXT_VIEW(mainArea), FALSE);
	gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(mainArea), GTK_WRAP_WORD);
	gtk_container_set_border_width(GTK_CONTAINER(mainAreaWindow), 20);

	gtk_container_add(GTK_CONTAINER(mainAreaWindow), mainAreaFrame);
	gtk_container_add(GTK_CONTAINER(mainAreaFrame), mainArea);


	gtk_container_set_border_width(GTK_CONTAINER(inputAreaBox), GTK_WRAP_WORD);

	gtk_container_add(GTK_CONTAINER(inputAreaFrame), inputArea);
	gtk_box_pack_start(GTK_BOX(inputAreaBox), inputLabel, FALSE, FALSE, 20);
	gtk_box_pack_start(GTK_BOX(inputAreaBox), inputAreaFrame, TRUE, TRUE, 20);

	GtkWidget ** menu_items []= {&quit_item, &nickname_item, &connect_item, &disconnect_item};
	char * menu_names []= {"Quit", "Nickname", "Connect", "Disconnect"};

	GtkWidget * infoLabel = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(infoLabel), "<span color='red'>Loading...</span>");
	gtk_label_set_xalign(GTK_LABEL(infoLabel), 0.1);

	for(unsigned i = 0; i < sizeof(menu_names)/sizeof(menu_names[0]); i++){
		*menu_items[i] = gtk_menu_item_new_with_label(menu_names[i]);
		gtk_menu_shell_append(GTK_MENU_SHELL(menubar), *menu_items[i]);
	}

	gtk_widget_set_sensitive(disconnect_item, FALSE);

	gtk_box_pack_start(GTK_BOX(main_vbox), menubar, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(main_vbox), mainAreaWindow, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(main_vbox), inputAreaBox, FALSE, FALSE, 0);
	gtk_box_pack_end(GTK_BOX(main_vbox), infoLabel, FALSE, FALSE, 12);
	gtk_widget_show_all(mainWindow);

	return mainWindow;
}
