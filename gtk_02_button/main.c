// pkg-config --cflags --libs gtk+-2.0
// sudo apt install libcanberra-gtk-module libcanberra-gtk3-module
#include <gtk/gtk.h>


void end_program(GtkWidget *wid, gpointer ptr);

int main (int argc, char *argv[])
{
	gtk_init (&argc, &argv);
	GtkWidget *win = gtk_window_new (GTK_WINDOW_TOPLEVEL);			// Create (container) window
	GtkWidget *btn = gtk_button_new_with_label ("Close Window");	// Create button with label
	
	//Hook up event handlers
	g_signal_connect (btn, "clicked", G_CALLBACK(end_program), NULL);
	g_signal_connect (win, "delete_event", G_CALLBACK (end_program), NULL);	
	
	gtk_container_add (GTK_CONTAINER(win), btn);					// Add the button to the container - window is a descendant of container and is cast
	gtk_widget_show_all (win);										// Show container and all children
	gtk_main ();													// Main event loop
	return 0;
}

void end_program(GtkWidget *wid, gpointer ptr)
{
	gtk_main_quit();
}
