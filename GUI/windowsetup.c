#include "windowsetup.h"
#include "windowhandlers.h"
#include "../programdata.h"

GtkWidget * setupMainWindow(const char * windowName, int * argc, char *** argv, char setupDialogs){
	gtk_init(argc, argv);

	GtkWidget * mainWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);

	gtk_widget_set_size_request(GTK_WIDGET(mainWindow), 400, 200);

	g_signal_connect(mainWindow, "destroy", G_CALLBACK(gtk_main_quit), NULL);

	gtk_window_set_title(GTK_WINDOW(mainWindow), windowName);

	GtkWidget * main_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

	gtk_container_add(GTK_CONTAINER(mainWindow), main_vbox);

	GtkWidget * menubar;
	menubar = gtk_toolbar_new();

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

	program_statusLabel = infoLabel;

	for(unsigned i = 0; i < sizeof(menu_names)/sizeof(menu_names[0]); i++){
		*menu_items[i] = GTK_WIDGET(gtk_tool_button_new(NULL, menu_names[i]));
		gtk_toolbar_insert(GTK_TOOLBAR(menubar), GTK_TOOL_ITEM(*menu_items[i]), -1);
	}

	gtk_widget_set_sensitive(disconnect_item, FALSE);

	gtk_box_pack_start(GTK_BOX(main_vbox), menubar, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(main_vbox), mainAreaWindow, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(main_vbox), inputAreaBox, FALSE, FALSE, 0);
	gtk_box_pack_end(GTK_BOX(main_vbox), infoLabel, FALSE, FALSE, 12);
	gtk_widget_show_all(mainWindow);

	g_signal_connect(G_OBJECT(quit_item), "clicked", G_CALLBACK(quitHandler), NULL);

	if(setupDialogs != 0){
		program_nicknameDialog = setupNicknameDialog(mainWindow);
		g_signal_connect(G_OBJECT(nickname_item), "clicked", G_CALLBACK(nicknameChangeHandler), NULL);
		program_connectDialog = setupConnectDialog(mainWindow);
		g_signal_connect(G_OBJECT(connect_item), "clicked", G_CALLBACK(connectHandler), NULL);
	}

	return mainWindow;
}


GtkWidget * setupNicknameDialog(GtkWidget * parent){
	GtkWidget * dialog = gtk_dialog_new_with_buttons("Change nickname", GTK_WINDOW(parent),
	 GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
 	 "OK", GTK_RESPONSE_ACCEPT, "Cancel", GTK_RESPONSE_REJECT, NULL);

	gtk_container_set_border_width(GTK_CONTAINER(dialog), 15);

	GtkWidget * label = gtk_label_new("Change nickname:");
	GtkWidget * nickname;
	nickname  = gtk_entry_new();
	gtk_entry_set_text(GTK_ENTRY(nickname), program_nickname);
	gtk_entry_set_max_length(GTK_ENTRY(nickname), 63);
//	gtk_widget_set_margin_start(label, 10);
//	gtk_widget_set_margin_end(label, 10);
	gtk_box_pack_start(GTK_BOX(gtk_dialog_get_content_area(GTK_DIALOG(dialog))), label, TRUE, TRUE, 10);
	gtk_box_pack_start(GTK_BOX(gtk_dialog_get_content_area(GTK_DIALOG(dialog))), nickname, TRUE, TRUE, 10);
	g_signal_connect(G_OBJECT(dialog), "delete-event", G_CALLBACK(gtk_widget_hide_on_delete), NULL);
	g_signal_connect(G_OBJECT(dialog), "response", G_CALLBACK(nicknameChangeDoneHandler), nickname);
	return dialog;
}

GtkWidget * setupConnectDialog(GtkWidget * parent){
	GtkWidget * dialog = gtk_dialog_new_with_buttons("Connect to a server", GTK_WINDOW(parent),
	 GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
 	 "Connect", GTK_RESPONSE_ACCEPT, "Cancel", GTK_RESPONSE_REJECT, NULL);

	gtk_container_set_border_width(GTK_CONTAINER(dialog), 15);
	GtkWidget * label = gtk_label_new("IP Address:");

	static program_connectionData cdt;

	cdt.IP1 = gtk_entry_new(); gtk_entry_set_text(GTK_ENTRY(cdt.IP1), "192");
	cdt.IP2 = gtk_entry_new(); gtk_entry_set_text(GTK_ENTRY(cdt.IP2), "168");
	cdt.IP3 = gtk_entry_new(); gtk_entry_set_text(GTK_ENTRY(cdt.IP3), "1");
	cdt.IP4 = gtk_entry_new(); gtk_entry_set_text(GTK_ENTRY(cdt.IP4), "1");

	gtk_box_pack_start(GTK_BOX(gtk_dialog_get_content_area(GTK_DIALOG(dialog))), label, TRUE, TRUE, 10);

	g_signal_connect(G_OBJECT(dialog), "delete-event", G_CALLBACK(gtk_widget_hide_on_delete), NULL);

	return dialog;
}
