// `pkg-config --cflags --libs gtk+-2.0`
// sudo apt install build-essential cppcheck libgtk2.0-dev libcanberra-gtk-module libcanberra-gtk3-module
#include <gtk/gtk.h>


void end_program(GtkWidget *wid, gpointer ptr);
void count_button (GtkWidget *wid, gpointer ptr);
int count = 0;

int main (int argc, char *argv[])
{
	gtk_init (&argc, &argv);
	GtkWidget *win = gtk_window_new (GTK_WINDOW_TOPLEVEL);			// Create (container) window
	GtkWidget *btn = gtk_button_new_with_label ("Close Window");	// Create button with label
	GtkWidget* lbl = gtk_label_new("My Label");
	GtkWidget* btn2 = gtk_button_new_with_label("Count!");
		
	//Hook up event handlers
	g_signal_connect (btn, "clicked", G_CALLBACK(end_program), NULL);
	g_signal_connect (win, "delete_event", G_CALLBACK (end_program), NULL);	
	g_signal_connect( btn2,"clicked", G_CALLBACK(count_button), lbl);	//Note the parameter
	
	// Windows can only contain one child - so we need a container
	// Using a vertical box container (simple)
	
	//Create the box container
	GtkWidget *box = gtk_vbox_new(FALSE, 5);
	
	//Pack the box: expand and fill are both TRUE, padding 0
	gtk_box_pack_start(GTK_BOX(box), btn2, TRUE, TRUE, 16);		
	gtk_box_pack_start(GTK_BOX(box), lbl,  TRUE, TRUE, 16);
	gtk_box_pack_start(GTK_BOX(box), btn,  TRUE, TRUE, 16);
	gtk_container_add (GTK_CONTAINER(win), box);					// Add the button to the container - window is a descendant of container and is cast
	
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
}
