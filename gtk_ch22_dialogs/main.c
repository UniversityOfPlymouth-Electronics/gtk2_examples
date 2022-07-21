// Use this for your build settings:
// Compile only: `pkg-config --cflags gtk+-2.0`
// Build:        `pkg-config --cflags --libs gtk+-2.0`

// Pre-requisites:
// sudo apt install build-essential git cppcheck libgtk2.0-dev libgtkmm-2.4-dev libgtk-3-dev libgtkmm-3.0-dev libcanberra-gtk-module libcanberra-gtk3-module

// GTK2 docs
// https://developer-old.gnome.org/gtk2/stable/
#include <gtk/gtk.h>
void end_program (GtkWidget *wid, gpointer ptr);
void open_dlg (GtkWidget *wid, gpointer ptr);

int main (int argc, char *argv[])
{
	gtk_init (&argc, &argv);
	
	GtkWidget *win = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	GtkWidget *btn = gtk_button_new_with_label ("Close window");
	
	g_signal_connect (btn, "clicked", G_CALLBACK (open_dlg), win);
	g_signal_connect (win, "delete_event", G_CALLBACK (end_program), NULL);

	//Add to top of the window using a vbox
	GtkWidget *vbox = gtk_vbox_new (FALSE, 5);
	gtk_box_pack_start (GTK_BOX (vbox), btn, TRUE, TRUE, 0);
	gtk_container_add (GTK_CONTAINER (win), vbox);
		
	gtk_widget_show_all (win);
	gtk_main ();
	
	return 0;
}

void end_program (GtkWidget *wid, gpointer ptr)
{
	gtk_main_quit ();
}

void open_dlg (GtkWidget *wid, gpointer ptr)
{
	//Essentially a window with a vbox
	GtkWidget *dlg = gtk_dialog_new_with_buttons (
		"My dialog",
		GTK_WINDOW (ptr), 
		GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
		"Cancel", 0, 
		"OK", 1, 
		NULL);
	
	//Add label to vbox top container (bottom is the action area for the buttons)
	GtkWidget *lbl = gtk_label_new ("A question for the user");
	gtk_container_add (GTK_CONTAINER (gtk_dialog_get_content_area (GTK_DIALOG (dlg))),lbl);
	gtk_widget_show (lbl);
		
	int result = gtk_dialog_run (GTK_DIALOG (dlg));
	gtk_widget_destroy (dlg);
	printf ("Return code = %d\n", result);
}

