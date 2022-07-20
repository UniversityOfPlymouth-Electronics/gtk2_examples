// Use this for your build settings:
// Compile only: `pkg-config --cflags gtk+-2.0`
// Build:        `pkg-config --cflags --libs gtk+-2.0`
 
// Pre-requisites:
// sudo apt install build-essential git cppcheck libgtk2.0-dev libgtkmm-2.4-dev libgtk-3-dev libgtkmm-3.0-dev libcanberra-gtk-module libcanberra-gtk3-module

// GTK2 docs
// https://developer-old.gnome.org/gtk2/stable/
#include <gtk/gtk.h>


void end_program(GtkWidget *wid, gpointer ptr);
void count_button (GtkWidget *wid, gpointer ptr);
void copy_text (GtkWidget *wid, gpointer ptr);

int count = 0;

// Shared - so careful if multi-threaded
static GtkClipboard* clipboard;

// Text Entry 
GtkWidget* txt;

int main (int argc, char *argv[])
{
	gtk_init (&argc, &argv);
	GtkWidget *win = gtk_window_new (GTK_WINDOW_TOPLEVEL);			// Create (container) window
	GtkWidget *btn = gtk_button_new_with_label ("Close Window");	// Create button with label
	GtkWidget* lbl = gtk_label_new("My Label");
	GtkWidget* btn2 = gtk_button_new_with_label("Copy Button");
	clipboard = gtk_clipboard_get(GDK_SELECTION_CLIPBOARD);
	
	//txt = gtk_entry_new();	// GtkEntry type
	GtkObject *adj = gtk_adjustment_new (0, -10, 10, 1, 0, 0); //Default,min,max,step,dc,dc
	txt = gtk_spin_button_new (GTK_ADJUSTMENT (adj), 0, 0); // climb rate and dp
		
	//Hook up event handlers
	g_signal_connect (btn, "clicked",      G_CALLBACK(end_program), NULL);
	g_signal_connect (win, "delete_event", G_CALLBACK (end_program), NULL);	
	g_signal_connect( btn2,"clicked",      G_CALLBACK(copy_text), lbl);	//Note the parameter
	
	// Windows can only contain one child - so we need a container
	// Using a vertical box container (simple)
	
	//Create the table container - 2x2, Homogeneous
	GtkWidget *tbl = gtk_table_new(2,2,TRUE);
	
	//Fill the table (default padding, expand, fill etc..)
	gtk_table_attach_defaults( GTK_TABLE(tbl), lbl,  0, 1, 0, 1 ); //left-right,top-botom
	gtk_table_attach_defaults( GTK_TABLE(tbl), btn2, 1, 2, 0, 1 );
	gtk_table_attach_defaults( GTK_TABLE(tbl), btn,  0, 1, 1, 2 );
	gtk_table_attach_defaults( GTK_TABLE(tbl), txt,  1, 2, 1, 2 );

	gtk_container_add (GTK_CONTAINER(win), tbl);					// Add the button to the container - window is a descendant of container and is cast
	
	gtk_widget_show_all (win);										// Show container and all children
	gtk_main ();													// Main event loop
	return 0;
}

// wid is the widget that generated the signal
// ptr is the parameter (NULL in this case)
void end_program(GtkWidget *wid, gpointer ptr)
{
	gtk_main_quit();
}

// wid is the widget that generated the signal
// ptr is the parameter (a label to update in this case)
void count_button (GtkWidget *wid, gpointer ptr)
{
	char buffer[30];
	count++;
	sprintf (buffer, "Button pressed %d times", count);
	gtk_label_set_text (GTK_LABEL (ptr), buffer);
	
	// Add to clipboard
	gtk_clipboard_set_text(clipboard, buffer, strlen(buffer));
}

// Copy text from text field to the label
void copy_text (GtkWidget *wid, gpointer ptr)
{
	const char *input = gtk_entry_get_text (GTK_ENTRY (txt));
	gtk_label_set_text (GTK_LABEL (ptr), input);
}
