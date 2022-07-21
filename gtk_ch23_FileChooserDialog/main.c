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

static void file_selected (GtkFileChooserButton *btn, gpointer ptr);
static void save_file (GtkWidget *btn, gpointer ptr);

int main (int argc, char *argv[])
{
	gtk_init (&argc, &argv);
	
	// Window and button
	GtkWidget *win = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	GtkWidget *btn = gtk_button_new_with_label ("Close window");
	
	// Hook up signals
	g_signal_connect (btn, "clicked",      G_CALLBACK (end_program),NULL);
	g_signal_connect (win, "delete_event", G_CALLBACK (end_program),NULL);
	
	// Add vbox
	GtkWidget *vbox = gtk_vbox_new (FALSE, 5);
	gtk_container_add (GTK_CONTAINER (win), vbox);
	
	// File chooser button (weird I know)
	// See also GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER
	GtkWidget *fc_btn = gtk_file_chooser_button_new ("Select file",	GTK_FILE_CHOOSER_ACTION_OPEN);
	g_signal_connect (fc_btn, "file-set",G_CALLBACK (file_selected), NULL);
	
	//Dialog for save
	GtkWidget *save_btn = gtk_button_new_with_label ("Select file");
	g_signal_connect (save_btn, "clicked", G_CALLBACK (save_file), win);	
		
	gtk_box_pack_start (GTK_BOX (vbox), fc_btn,   TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (vbox), save_btn, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (vbox), btn,      TRUE, TRUE, 0);
	gtk_widget_show_all (win);
	gtk_main();
	
	return 0;
}

static void file_selected (GtkFileChooserButton *btn, gpointer ptr)
{
	printf ("%s selected\n", gtk_file_chooser_get_filename(GTK_FILE_CHOOSER (btn)));
}

static void save_file (GtkWidget *btn, gpointer ptr)
{
	GtkWidget *sch = gtk_file_chooser_dialog_new ("Save file", GTK_WINDOW (ptr), GTK_FILE_CHOOSER_ACTION_SAVE,"Cancel", 0, "OK", 1, NULL);
	if (gtk_dialog_run (GTK_DIALOG (sch)) == 1)
	{
		printf ("%s selected\n", gtk_file_chooser_get_filename(GTK_FILE_CHOOSER (sch)));
	}
	gtk_widget_destroy (sch);
}
