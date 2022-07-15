// pkg-config --cflags --libs gtk+-2.0
// sudo apt install libcanberra-gtk-module libcanberra-gtk3-module

#include <gtk/gtk.h>
int main (int argc, char *argv[])
{
	gtk_init (&argc, &argv);
	GtkWidget *win = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_widget_show (win);
	gtk_main ();
	return 0;
}
