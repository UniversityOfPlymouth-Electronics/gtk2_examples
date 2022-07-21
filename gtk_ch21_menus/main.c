// Use this for your build settings:
// Compile only: `pkg-config --cflags gtk+-2.0`
// Build:        `pkg-config --cflags --libs gtk+-2.0`

// Pre-requisites:
// sudo apt install build-essential git cppcheck libgtk2.0-dev libgtkmm-2.4-dev libgtk-3-dev libgtkmm-3.0-dev libcanberra-gtk-module libcanberra-gtk3-module

// GTK2 docs
// https://developer-old.gnome.org/gtk2/stable/
#include <gtk/gtk.h>
void end_program (GtkWidget *wid, gpointer ptr);


int main (int argc, char *argv[])
{
	gtk_init (&argc, &argv);
	
	GtkWidget *win = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	GtkWidget *btn = gtk_button_new_with_label ("Close window");
	g_signal_connect (btn, "clicked", G_CALLBACK (end_program),	NULL);
	g_signal_connect (win, "delete_event", G_CALLBACK (end_program),	NULL);
	
	//Create menu bar
	GtkWidget *mbar = gtk_menu_bar_new ();
	
	//Add to top of the window using a vbox
	GtkWidget *vbox = gtk_vbox_new (FALSE, 5);
	gtk_box_pack_start (GTK_BOX (vbox), mbar, TRUE, TRUE, 0);
	gtk_container_add (GTK_CONTAINER (win), vbox);
	
	//Create menu item and add to menu shell (something that can hold menus - menu or menu bar)
	GtkWidget *file_mi = gtk_menu_item_new_with_label ("File");
	gtk_menu_shell_append (GTK_MENU_SHELL (mbar), file_mi);
	
	//Create a menu for the File menu item
	GtkWidget *f_menu = gtk_menu_new ();
	
	//Set as a submenu (nesting)
	gtk_menu_item_set_submenu (GTK_MENU_ITEM (file_mi), f_menu);
	
	//Now a menu item for the Quit operation
	GtkWidget *quit_mi = gtk_menu_item_new_with_label ("Quit");
	gtk_menu_shell_append (GTK_MENU_SHELL (f_menu), quit_mi);
	
	//Hook up the callback
	g_signal_connect (quit_mi, "activate", G_CALLBACK (end_program),NULL);
	
	//Add a button on the end
	gtk_box_pack_start (GTK_BOX (vbox), btn, TRUE, TRUE, 0);
	gtk_widget_show_all (win);
	gtk_main ();
	
	return 0;
}

void end_program (GtkWidget *wid, gpointer ptr)
{
	gtk_main_quit ();
}
