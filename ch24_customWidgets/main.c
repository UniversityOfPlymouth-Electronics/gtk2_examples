// Use this for your build settings:
// Compile only: `pkg-config --cflags gtk+-2.0`
// Build:        `pkg-config --cflags --libs gtk+-2.0`

// Pre-requisites:
// sudo apt install build-essential git cppcheck libgtk2.0-dev libgtkmm-2.4-dev libgtk-3-dev libgtkmm-3.0-dev libcanberra-gtk-module libcanberra-gtk3-module

// GTK2 docs
// https://developer-old.gnome.org/gtk2/stable/
#include <gtk/gtk.h>

void end_program (GtkWidget *wid, gpointer ptr)
{
	gtk_main_quit ();
}

// Also - see /usr/share/themes

int main (int argc, char *argv[])
{
	gtk_init (&argc, &argv);
	GtkWidget *win = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	GtkWidget *btn = gtk_button_new_with_label ("Close window");
	g_signal_connect (btn, "clicked", G_CALLBACK (end_program),	NULL);
	g_signal_connect (win, "delete_event", G_CALLBACK (end_program),NULL);
	
	GtkWidget *btn2 = gtk_button_new_with_label ("My _button");
	//Customise
	// See https://developer-old.gnome.org/gtk2/stable/GtkButton.html
	g_object_set (G_OBJECT (btn2), "relief", GTK_RELIEF_NONE, NULL); //Remove 3D shadow
	g_object_set (G_OBJECT (btn2), "use-underline", TRUE, NULL);     //Hold down alt to see the underline
	//---------
	
	GtkWidget *lbl = gtk_label_new ("My label");
	//Customise
	g_object_set (G_OBJECT (lbl), "angle", 45.0f, NULL);
	//---------
	
	GtkWidget *box = gtk_vbox_new (FALSE, 5);
	gtk_box_pack_start (GTK_BOX (box), btn2, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (box), btn, TRUE, TRUE, 0);
	gtk_box_pack_end (GTK_BOX (box), lbl, TRUE, TRUE, 0);
	gtk_container_add (GTK_CONTAINER (win), box);
	gtk_widget_show_all (win);
	gtk_main();
	
	return 0;
}


