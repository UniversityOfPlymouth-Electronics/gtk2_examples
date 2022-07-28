// Use this for your build settings:
// Compile only: `pkg-config --cflags gtk+-2.0`
// Build:        `pkg-config --cflags --libs gtk+-2.0`

// Pre-requisites:
// sudo apt install build-essential git cppcheck libgtk2.0-dev libgtkmm-2.4-dev libgtk-3-dev libgtkmm-3.0-dev libcanberra-gtk-module libcanberra-gtk3-module

// GTK2 docs
// https://developer-old.gnome.org/gtk2/stable/

// For gtk3, you need glade 
// For gtk2, you need glade-3, which is no longer in Ubuntu (arghhh)

#include <gtk/gtk.h>

void end_program(GtkWidget *wid, gpointer ptr);

int main (int argc, char *argv[])
{
    gtk_init (&argc, &argv);
    GtkBuilder *builder = gtk_builder_new ();
    gtk_builder_add_from_file (builder, "mylayout.glade", NULL);
    GtkWidget *win = (GtkWidget *) gtk_builder_get_object (builder,"window1");
    GtkWidget *btn = (GtkWidget *) gtk_builder_get_object (builder,"button1");
    g_signal_connect(btn, "clicked", G_CALLBACK(end_program), NULL);
    
    gtk_widget_show_all (win);
    gtk_main ();
    return 0;
}

void end_program(GtkWidget *wid, gpointer ptr)
{
	gtk_main_quit();
}
