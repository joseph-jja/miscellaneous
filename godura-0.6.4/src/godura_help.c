#include "godura_help.h"

void help_help() {

    GtkWidget *open_dialog;
    GtkWidget *label; 
    PangoFontDescription *font_desc;

    label = gtk_label_new("Not Implemented Yet!");
    
    open_dialog = gtk_dialog_new(); 
    
    gtk_box_pack_start(GTK_BOX(GTK_DIALOG(open_dialog)->vbox),label, FALSE, FALSE, 0);
    gtk_widget_show(label); 
    
    gtk_dialog_add_button(GTK_DIALOG(open_dialog), 
    			"Ok", 0);
    
    gtk_window_set_position(GTK_WINDOW(open_dialog),GTK_WIN_POS_CENTER_ALWAYS);
 
    font_desc = pango_font_description_from_string (TEXTFONT);
    gtk_widget_modify_font (GTK_WIDGET(label), font_desc);
    pango_font_description_free (font_desc);
   
    gtk_dialog_run(GTK_DIALOG(open_dialog));

    /* now destroy the dialog box */	
    gtk_widget_destroy(open_dialog);
    
       
}

void help_about() {

    GtkWidget *open_dialog;
    GtkWidget *label; 
    PangoFontDescription *font_desc;
   
    /* add in at some point   */ 
    label = gtk_label_new(ABOUTWIN);
    
    open_dialog = gtk_dialog_new(); 
    
    gtk_box_pack_start(GTK_BOX(GTK_DIALOG(open_dialog)->vbox),label, FALSE, FALSE, 0);
    gtk_widget_show(label); 
    
    gtk_dialog_add_button(GTK_DIALOG(open_dialog), 
    			"Ok", 0);

    font_desc = pango_font_description_from_string (TEXTFONT);
    gtk_widget_modify_font (GTK_WIDGET(label), font_desc);
    pango_font_description_free (font_desc);

    gtk_window_set_position(GTK_WINDOW(open_dialog),GTK_WIN_POS_CENTER_ALWAYS);
    
    gtk_dialog_run(GTK_DIALOG(open_dialog));

    /* now destroy the dialog box */	
    gtk_widget_destroy(open_dialog);
    
}


 
