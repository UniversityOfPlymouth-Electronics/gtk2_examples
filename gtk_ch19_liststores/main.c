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
void check_toggle (GtkWidget *wid, gpointer ptr);
void radio_toggle (GtkWidget *wid, gpointer ptr);
void combo_changed (GtkWidget *wid, gpointer ptr);

//Click count
int count = 0;

//Position in list store
int pos = 0;

// Shared - so careful if multi-threaded
static GtkClipboard* clipboard;

// Text Entry 
GtkWidget* txt;

// Checked or not
volatile int isChecked = 0;

int main (int argc, char *argv[])
{
	gtk_init (&argc, &argv);
	GtkWidget *win = gtk_window_new (GTK_WINDOW_TOPLEVEL);			// Create (container) window
	GtkWidget *btn = gtk_button_new_with_label ("Close Window");	// Create button with label
	GtkWidget* lbl = gtk_label_new("My Label");
	GtkWidget* btn2 = gtk_button_new_with_label("Copy Button");
	GtkWidget *chk = gtk_check_button_new_with_label ("My check");	// Check button
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(chk), TRUE);
	GtkWidget *rad1 = gtk_radio_button_new_with_label (NULL, "Button 1");
	GSList *group = gtk_radio_button_get_group(GTK_RADIO_BUTTON(rad1));
	GtkWidget *rad2 = gtk_radio_button_new_with_label (group, "Button 2");
	//Combo box
	/*
	GtkWidget *comb = gtk_combo_box_text_new ();
	gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (comb), "Option 1");
	gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (comb), "Option 2");
	gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (comb), "Option 3");
	gtk_combo_box_set_active (GTK_COMBO_BOX (comb), 0);	//Set default item
	*/
	
	//List Store
	GtkListStore *ls = gtk_list_store_new (1, G_TYPE_STRING); 				// 1 column, then types of each
	
	//Add entries
	gtk_list_store_insert_with_values (ls, NULL, pos++, 0,"Option 1", -1); 	//Iterator is NULL; pos is the row; column-data pairs; -1 to terminate 
	gtk_list_store_insert_with_values (ls, NULL, pos++, 0,"Option 2", -1);
	gtk_list_store_insert_with_values (ls, NULL, pos++, 0,"Option 3", -1);
	
	//Associate combo box with the list store
	GtkWidget *comb = gtk_combo_box_new_with_model (GTK_TREE_MODEL (ls));	//Data is type GtkTreeModel
	
	//Create a renderer (for text type data)
	GtkCellRenderer *rend = gtk_cell_renderer_text_new ();
	//Add the renderer to the cell layout of the combo box
	gtk_cell_layout_pack_start (GTK_CELL_LAYOUT (comb), rend, FALSE);	// Do not expand into free space
	//Set the text attribute to column 0 of the list store
	gtk_cell_layout_add_attribute (GTK_CELL_LAYOUT (comb), rend,"text", 0);
	
	
	//Clipboard
	clipboard = gtk_clipboard_get(GDK_SELECTION_CLIPBOARD);
	
	//txt = gtk_entry_new();	// GtkEntry type
	GtkObject *adj = gtk_adjustment_new (0, -10, 10, 1, 0, 0); //Default,min,max,step,dc,dc
	txt = gtk_spin_button_new (GTK_ADJUSTMENT (adj), 0, 0); // climb rate and dp
		
	//Hook up event handlers
	g_signal_connect (btn, "clicked",      G_CALLBACK(end_program), NULL);
	g_signal_connect (win, "delete_event", G_CALLBACK (end_program), NULL);	
	g_signal_connect( btn2,"clicked",      G_CALLBACK(copy_text), lbl);	//Note the parameter
	g_signal_connect( chk, "toggled",      G_CALLBACK(check_toggle), lbl);
	//g_signal_connect (comb,"changed",      G_CALLBACK(combo_changed), NULL);
	
	//radio_toggle
	g_signal_connect( rad1, "toggled",      G_CALLBACK(radio_toggle), lbl);
	g_signal_connect( rad2, "toggled",      G_CALLBACK(radio_toggle), lbl);
	
	
	// Windows can only contain one child - so we need a container
	// Using a vertical box container (simple)
	
	//Create the table container - 2x2, Homogeneous
	GtkWidget *tbl = gtk_table_new(2,2,TRUE);
	
	//Fill the table (default padding, expand, fill etc..)
	gtk_table_attach_defaults( GTK_TABLE(tbl), rad1,  0, 1, 0, 1 );
	gtk_table_attach_defaults( GTK_TABLE(tbl), comb, 1, 2, 0, 1 );
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

// Check button changed
void check_toggle (GtkWidget *wid, gpointer ptr)
{
	isChecked = gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (wid));
	printf ("The state of the button is %d\n", isChecked);
}

void radio_toggle (GtkWidget *wid, gpointer ptr)
{
	isChecked = gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (wid));
	printf ("The state of the button is %d\n", isChecked);
}

void combo_changed (GtkWidget *wid, gpointer ptr)
{
	int sel = gtk_combo_box_get_active (GTK_COMBO_BOX (wid));
	char *selected = gtk_combo_box_text_get_active_text (
	GTK_COMBO_BOX_TEXT (wid));
	printf ("The value of the combo is %d %s\n", sel, selected);
}
