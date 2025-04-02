/* 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gxtext.h"
#include <gtk/gtkscrolledwindow.h>
#include <gtk/gtklabel.h>
#include <gtk/gtktable.h>
#include <gtk/gtktextiter.h>

#define GXTEXT_BUFLEN 1024

static void gxtext_class_init          (GxtextClass *klass);
static void gxtext_init                (Gxtext      *xxx);

static void ismodified(GtkTextBuffer *, GtkWidget *);
static void lineposition (GtkTextBuffer *, GtkWidget *);
static void textlineposition (GtkTextView *, GtkMovementStep , gint, gboolean, GtkWidget *);

GType gxtext_get_type () {

  static GType xxx_type = 0;

  if (!xxx_type)
    {
      static const GTypeInfo xxx_info =
      {
	sizeof (GxtextClass),
	NULL,
                NULL,
	(GClassInitFunc) gxtext_class_init,
                NULL,
	NULL,
                sizeof (Gxtext),
	0,
	(GInstanceInitFunc) gxtext_init,
      };
      xxx_type = g_type_register_static (GTK_TYPE_VBOX, "Gxtext", &xxx_info, 0);
    }
  return xxx_type;
}

static void gxtext_class_init (GxtextClass *class) {

  GtkObjectClass *object_class;

  object_class = (GtkObjectClass*) class;

  class->gxtext = NULL;
}

static void gxtext_init (Gxtext *xxx) {     

    xxx->scrolled_win = 0;
    xxx->textvbox = 0;
    xxx->textarea = 0;
    xxx->linenumber = 0;
    xxx->modified = 0;
}

GtkWidget *gxtext_new () {

    Gxtext *xxx;

    xxx = gtk_type_new(gxtext_get_type());

    xxx->textvbox = gtk_vbox_new(FALSE, 0);

    /* first lets create the scrolled region that the text area will go into */
    xxx->scrolled_win = gtk_scrolled_window_new (NULL, NULL);
    gtk_container_set_border_width (GTK_CONTAINER (xxx->scrolled_win), 2);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (xxx->scrolled_win),
                               GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

    gtk_box_pack_start(GTK_BOX(xxx->textvbox), xxx->scrolled_win,TRUE, TRUE,0);

    gtk_container_add (GTK_CONTAINER (xxx), xxx->textvbox);
    gtk_widget_show (xxx->scrolled_win);
    gtk_widget_show(xxx->textvbox);

    /* now create the new gtk2.0 text widget 
     * this is a whole lot of work so that is 
     * why I am making this custom widget*/
    xxx->textarea = gtk_text_view_new ();

    gtk_widget_show(xxx->textarea);
			
    /* here is the container packing */
    gtk_container_add (GTK_CONTAINER(xxx->scrolled_win), xxx->textarea);

    /* set editable duh */
    gtk_text_view_set_editable(GTK_TEXT_VIEW(xxx->textarea), TRUE);
	 
    /* turn off word wrap */
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(xxx->textarea), GTK_WRAP_NONE); 

  return GTK_WIDGET (xxx);
}

GtkWidget* gxtext_new_with_lin_col() {
    
    GtkWidget *table;
    GtkWidget *maintext = gxtext_new();
    GtkTextBuffer *buffer;
    			
    GXTEXT(maintext)->linenumber = gtk_label_new("Line: 1, Column: 0");
    GXTEXT(maintext)->modified = gtk_label_new("           ");
    table = (GtkWidget*)gtk_table_new(1,4, TRUE);
    
    gtk_table_attach_defaults(GTK_TABLE(table) , GXTEXT(maintext)->linenumber, 0,1,0,1);
    gtk_table_attach_defaults(GTK_TABLE(table) , GXTEXT(maintext)->modified, 2,3,0,1);
    
    gtk_box_pack_start(GTK_BOX(GXTEXT(maintext)->textvbox), table,FALSE,FALSE,0);

    gtk_widget_show(table);
    gtk_widget_show(GXTEXT(maintext)->linenumber);  
    gtk_widget_show(GXTEXT(maintext)->modified);  

    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(GXTEXT(maintext)->textarea));

    g_signal_connect(buffer, "changed",
                        (GtkSignalFunc)lineposition, GXTEXT(maintext)->linenumber);  

    g_signal_connect_after(buffer, "changed",
                        (GtkSignalFunc)ismodified, GXTEXT(maintext)->modified);  


    g_signal_connect_after(GXTEXT(maintext)->textarea, "move_cursor",
                        (GtkSignalFunc)textlineposition, GXTEXT(maintext)->linenumber);  

    return GTK_WIDGET (maintext);         

}

void gxtext_destroy(GtkWidget *gxtext) {

    gtk_widget_destroy(gxtext);
}

/* it seems that when I called g_signal_connect it missed the gpointer data */
static void textlineposition (GtkTextView *view, GtkMovementStep move, gint arg2, gboolean arg3, GtkWidget *widget) {

    GtkTextBuffer *buf;

    buf = gtk_text_view_get_buffer(GTK_TEXT_VIEW(view));

    /* now call this funciton with the buffer and label */
    lineposition(buf, widget);
}

static void ismodified (GtkTextBuffer *buf, GtkWidget *widget) {

    gtk_label_set_label(GTK_LABEL(widget), "Modified...");     
}

static void lineposition (GtkTextBuffer *buf, GtkWidget *widget) {
    
    GtkTextIter iter;
    gint x, y;
    GtkTextMark *mark;
    gchar *string;

    string = (gchar*)g_malloc(GXTEXT_BUFLEN+1);
    if (string == NULL) {
        return ;
    }
        
    /* get the insert mark of the buffer -> this is where the cursor is */
    mark = gtk_text_buffer_get_insert(buf);
    
    /* now get the iter at the insert mark */
    gtk_text_buffer_get_iter_at_mark(buf, & iter, mark);

    /* now get the line number from the iter */
    y = gtk_text_iter_get_line( & iter );
    
    /* since the iter gives us a 0 based system we add 1 always */
    y++; 
 
    /* now get the column number from the iter */
    /* zero based */
    x = gtk_text_iter_get_line_offset( & iter) ;
    
    memset(string, '\0', GXTEXT_BUFLEN+1);
    sprintf(string, "Line: %d Column: %d ", y, x);
    
    gtk_label_set_label(GTK_LABEL(widget), string);        

    g_free(string);      
}

/* this reads in a  file to the text widget */
gint gxtext_read_in_ascii_file(GtkWidget *gxtext, gchar *filename)
{

    FILE *pFile; 
    GtkTextIter start, iter, end;
    GtkTextMark *mark;
    GtkTextBuffer *buf;

    buf = gtk_text_view_get_buffer(GTK_TEXT_VIEW(GXTEXT(gxtext)->textarea));
    
    gtk_text_buffer_get_start_iter(buf, &start);
    
    gtk_text_buffer_place_cursor (buf, &start);
     
    if ((pFile=fopen(filename, "r")) == NULL) 
    {
         /* return 0 on failure */
         return 0; 
    } else {
        gchar *buffer;
	gint buflen;
	buffer = (gchar*)g_malloc(GXTEXT_BUFLEN+1); 
	
	while (!feof(pFile)) 
	{
	     buflen = fread(buffer, sizeof(char), GXTEXT_BUFLEN, pFile);

	     if (buflen <= 0) {
		   break;
	     }

	     /* get the insertion cursor - should be start */
	     mark = gtk_text_buffer_get_insert(buf);
	          
    	     /* now get the iter at the insert mark */
                    gtk_text_buffer_get_iter_at_mark(buf, &iter, mark);
					      
	     /* now insert the data */
	     gtk_text_buffer_insert(buf, &iter, buffer, buflen);
            }
            g_free(buffer);
            fclose(pFile);
    }

    gtk_text_buffer_get_bounds(buf, &start, & end);

    /* move the cursor back to the beginning of the text */
    gtk_text_buffer_place_cursor (buf, &start);

    /* we set this to false as it really has not been modified */
    gtk_text_buffer_set_modified(buf, FALSE);

    gtk_label_set_label(GTK_LABEL(GXTEXT(gxtext)->modified), "           ");     

    return 1;
}

gint gxtext_write_out_ascii_file (GtkWidget *gxtext, gchar *filename)
{
	
    FILE *pFile;
    gchar *outchars; 
    GtkTextIter start, end;
    GtkTextBuffer *buffer;
    
    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(GXTEXT(gxtext)->textarea));
    
    gtk_text_buffer_get_bounds(buffer, &start, &end);
    	       	
    if ((pFile=fopen(filename, "w")) == NULL) {
        return -1; 
    } else {
        
	/* get the charcters at this iter */
	outchars = gtk_text_iter_get_slice(&start,&end);
	fwrite(outchars, 1, strlen(outchars), pFile);
	fclose(pFile);
	free(outchars);
    }
     /* we set this to false as it really has not been modified */
    gtk_text_buffer_set_modified(buffer, FALSE);
    gtk_label_set_label(GTK_LABEL(GXTEXT(gxtext)->modified), "           ");     
    return 0;	
} 

void gxtext_select_all(GtkWidget *gxtext)
{
    GtkTextIter start, end;
    GtkTextMark *mark;
    GtkTextBuffer *buffer;
    
    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(GXTEXT(gxtext)->textarea));
    
    /* get the widget bounds start and end */
    gtk_text_buffer_get_bounds(buffer, &start, &end);

    /* move the cursor to the start of the widget */
    gtk_text_buffer_place_cursor(buffer, &start);

    /* now get the insert mark which should be at the beginning */
    mark = gtk_text_buffer_get_insert(buffer);
 
    /* now move the mark to the end and this will select the text */
    gtk_text_buffer_move_mark(buffer, mark, &end);
}

void gxtext_delete_text(GtkWidget *gxtext) {

    GtkTextBuffer *buffer;
    
    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(GXTEXT(gxtext)->textarea));

     gtk_text_buffer_delete_selection(buffer, TRUE, TRUE);
     gtk_text_buffer_set_modified(buffer, TRUE);
}

void gxtext_cut_text(GtkWidget *gxtext) {

    /* what is cut? but copy to the clipboard 
     * and then delete the text */
    gxtext_copy_text(gxtext);
    gxtext_delete_text(gxtext);
}

void gxtext_copy_text(GtkWidget *gxtext) {

    GtkTextIter start, end;
    gchar *sel;
    GtkClipboard *clip;
    GtkTextMark *mark; 
    GtkTextBuffer *buffer;
    
    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(GXTEXT(gxtext)->textarea));
    
    gtk_text_buffer_get_selection_bounds(buffer, & start, & end);

    clip = gtk_clipboard_get(GDK_SELECTION_CLIPBOARD);

    /* lets get the selection in the buffer */				
    sel = gtk_text_buffer_get_text(buffer, & start, & end , TRUE);				

    if (sel == NULL) { 
        return ; 
    }

    gtk_clipboard_set_text(clip, sel, strlen(sel));

    gtk_text_buffer_copy_clipboard(buffer, clip);

    gtk_text_buffer_place_cursor(buffer, &start);

    mark = gtk_text_buffer_get_insert(buffer);

    gtk_text_buffer_move_mark(buffer, mark, &end);

    gtk_text_buffer_set_modified(buffer, FALSE);

}

void gxtext_paste_text(GtkWidget *gxtext) {
    GtkTextIter pos; 
    GtkTextMark *mark; 
    GtkClipboard *clip;
    gchar *data; 
    GtkTextBuffer *buffer;
    
    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(GXTEXT(gxtext)->textarea));

    /* in case there is selected text delete it first */    
    gxtext_delete_text(gxtext);

    clip = gtk_clipboard_get(GDK_SELECTION_CLIPBOARD);

    mark = gtk_text_buffer_get_insert(buffer);

    gtk_text_buffer_get_iter_at_mark(buffer, &pos, mark);
    
    data = gtk_clipboard_wait_for_text(clip);

    if (data == NULL) {
        return;
    }

    gtk_text_buffer_insert(buffer, & pos, data, strlen(data));

    //gtk_text_buffer_paste_clipboard(buffer, clip, &pos, TRUE);
				    
    gtk_text_buffer_set_modified(buffer, TRUE);
}

void gxtext_set_as_new(GtkWidget *gxtext)
{
    GtkTextIter start, end;
    GtkTextBuffer *buffer;
    
    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(GXTEXT(gxtext)->textarea));

    gtk_text_buffer_get_bounds(buffer, &start, &end);

    gtk_text_buffer_delete(buffer, &start, &end);

     /* we set this to false as it really has not been modified */
    gtk_text_buffer_set_modified(buffer, FALSE);
    gtk_label_set_label(GTK_LABEL(GXTEXT(gxtext)->modified), "           ");     
}

