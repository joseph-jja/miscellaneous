#include "godura_prefs.h"

void change_font(widgetinfo *textstruct) {

    GtkWidget *font_sel;
    PangoFontDescription *font_desc;
        GtkFontSelectionDialog *dlg;

    font_sel = gtk_font_selection_dialog_new("Set session font");

    if (gtk_dialog_run (GTK_DIALOG (font_sel)) == GTK_RESPONSE_OK) {
   
                dlg = (GtkFontSelectionDialog *)font_sel;   
        /* now set the font */
          font_desc = pango_font_description_from_string (gtk_font_selection_dialog_get_font_name(dlg));
          gtk_widget_modify_font (GTK_WIDGET(GXTEXT (textstruct->textwidget)->textarea), font_desc);
    }   
    gtk_widget_destroy (font_sel);
}