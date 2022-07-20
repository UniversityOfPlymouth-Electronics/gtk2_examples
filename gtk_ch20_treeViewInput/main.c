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

// Callback for when a row is selected
void row_selected (GtkWidget *wid, gpointer ptr)
{
	GtkTreeSelection *sel;
	GtkTreeModel *model;
	GtkTreeIter iter;
	char *option;
	
	//Which rows are highlighted?
	sel = gtk_tree_view_get_selection (GTK_TREE_VIEW (wid));
	//Get the model (ListStore) and iterator (selected row)
	if (gtk_tree_selection_get_selected (sel, &model, &iter))
	{
		gtk_tree_model_get (model, &iter, 0, &option, -1);	//Col 0, write data to addres of option
		printf ("The selected row contains the text %s\n", option);
	}
}

int main (int argc, char *argv[])
{
	gtk_init (&argc, &argv);
	
	GtkWidget *win = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	GtkWidget *btn = gtk_button_new_with_label ("Close window");
	g_signal_connect (btn, "clicked", G_CALLBACK (end_program),NULL);
	g_signal_connect (win, "delete_event", G_CALLBACK (end_program),NULL);
	
	int pos = 0;
	
	// Create list store - 2 cols: string and a pixel buffer
	GtkListStore *ls = gtk_list_store_new (2, G_TYPE_STRING,GDK_TYPE_PIXBUF);
	
	// Create GdkPixbuf - in this case an icon from the current theme
	GdkPixbuf *icon  = gtk_icon_theme_load_icon (gtk_icon_theme_get_default (), "dialog-ok-apply", 32, 0, NULL);
	
	// Add three rows to the list store: Col 0 is a string; Col 1 is an image
	gtk_list_store_insert_with_values (ls, NULL, pos++, 0,"Option 1", 1, icon, -1);
	gtk_list_store_insert_with_values (ls, NULL, pos++, 0,"Option 2", 1, icon, -1);
	gtk_list_store_insert_with_values (ls, NULL, pos++, 0,"Option 3", 1, icon, -1);
	
	// Create a tree view using the liststore as the model
	GtkWidget *tv = gtk_tree_view_new_with_model (GTK_TREE_MODEL (ls));
	
	// Now both renderers
	GtkCellRenderer *prend = gtk_cell_renderer_pixbuf_new ();
	GtkCellRenderer *trend = gtk_cell_renderer_text_new ();
	
	// Insert columns into the tree view: -1 is to the right; title; renderer; renderer args:
	// - set the ‘pixbuf’ attribute of the pixbuf renderer to the model data in column 1
	// - set the ‘text’ attribute of the text renderer to the model data in column 0
	gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (tv), -1, "Icon", prend, "pixbuf", 1, NULL);
	gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (tv), -1, "Option", trend, "text", 0, NULL);
	
	// Call-backs
	g_signal_connect (tv, "cursor-changed", G_CALLBACK(row_selected), NULL);
	
	// Table view
	GtkWidget *tbl = gtk_table_new (2, 2, FALSE);
	gtk_table_attach_defaults (GTK_TABLE (tbl), tv, 0, 2, 0, 1);
	gtk_table_attach_defaults (GTK_TABLE (tbl), btn, 0, 1, 1, 2);
	
	gtk_container_add (GTK_CONTAINER (win), tbl);
	gtk_widget_show_all (win);
	gtk_main ();
	
	return 0;
}
