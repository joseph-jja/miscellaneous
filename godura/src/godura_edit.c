#include "godura_edit.h"

#include <time.h>

/* this file contains the functions for the file menu 
   see gXpad.h for more details */

void undo_last(widgetinfo *textwidget, gpointer data) {

   GtkTextBuffer *buffer;
   buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(GXTEXT(textwidget->textwidget)->textarea));
   stack_pop(buffer, textwidget );

}

void redo_last(widgetinfo *textwidget, gpointer data) {

   GtkTextBuffer *buffer;
   buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(GXTEXT(textwidget->textwidget)->textarea));
   stack_push(buffer, textwidget);

}

void paste_text(widgetinfo *textstruct, gpointer data) {

    gxtext_paste_text(GTK_WIDGET(textstruct->textwidget) );

}

void cut_text(widgetinfo *textstruct, gpointer data) {

    gxtext_cut_text(GTK_WIDGET(textstruct->textwidget) );

}

void copy_text(widgetinfo *textstruct, gpointer data) {

    gxtext_copy_text(GTK_WIDGET(textstruct->textwidget) );
    
}

void delete_text(widgetinfo *textstruct, gpointer data) {

    gxtext_delete_text(GTK_WIDGET(textstruct->textwidget) );

}

void select_text(widgetinfo *textstruct, gpointer data) {

    gxtext_select_all(textstruct->textwidget);

}

void wrap_text(widgetinfo *textstruct) {

    gint mode;

    mode = gtk_text_view_get_wrap_mode(GTK_TEXT_VIEW(GXTEXT(textstruct->textwidget)->textarea)); 
    if (mode == GTK_WRAP_WORD) 
    { 
        gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(GXTEXT(textstruct->textwidget)->textarea), 
    		GTK_WRAP_NONE);
    } else {   
        gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(GXTEXT(textstruct->textwidget)->textarea), 
    		GTK_WRAP_WORD);
    }
}

void get_current_time(widgetinfo *textstruct) {
		
	gchar *mytime;
	gint nchars, curyr;
	
	struct tm *realtime;
        time_t realseconds;
        static char buf[28];  /* this should be HH:MM am/pm MM/DD/YYYY only about 18 chars are needed*/
	GtkTextMark *mark;
	GtkTextIter iter; 
	   GtkTextBuffer *buffer;

	time(&realseconds);
	realtime = localtime(&realseconds);
	
        curyr = realtime->tm_year +1900;

        memset(buf, '\0', sizeof(buf));

  	sprintf(buf, "%2d:%2d%s %d/%d/%d", realtime->tm_hour%12 ? realtime->tm_hour%12 : 12,
		realtime->tm_min, realtime->tm_hour > 11 ? "pm" : "am",
		realtime->tm_mday, realtime->tm_mday, curyr);
		
  	nchars = strlen(buf);
	mytime = (gchar*)malloc(nchars + 1);
	
	if (mytime != NULL) {
		memcpy(mytime,buf, nchars);

		/* if there is a selection we just delete it */
		delete_text(textstruct, NULL);

               buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(GXTEXT(textstruct->textwidget)->textarea));

		/* get the insert mark of the buffer -> this is where the cursor is */
                mark = gtk_text_buffer_get_insert(buffer);
    
    	        /* now get the iter at the insert mark */
                gtk_text_buffer_get_iter_at_mark(buffer, & iter, mark);

	        /* now insert the text at the iter */ 
		gtk_text_buffer_insert(buffer, & iter, mytime, nchars);

                g_free(mytime);

        gtk_text_buffer_set_modified(buffer, TRUE);

	}

}
