#include "godura_search.h"
#include <gxtext.h>

#define FORWARD  1
#define REVERSE   0

int go_replace(GtkWidget *, widgetinfo *);

void replace_all_text(GtkWidget *, widgetinfo *);

int go_find(GtkWidget *, widgetinfo *);

static gboolean search_line(GtkWidget *, char *, gint, gboolean);

void find_next_text(widgetinfo *textstruct, gpointer data) {

    if ((textstruct->searchterm != NULL) && (strlen(textstruct->searchterm) > 0)) {
        go_find (NULL, textstruct);
    } else {
        find_text(textstruct, data);
    }
} 

/* this is the callback function for the Find menu option */
void find_text(widgetinfo *textstruct, gpointer data) {
       Gxsearch *dialogwin;

       dialogwin = (Gxsearch*)gxsearch_new(FIND);

       gtk_toggle_button_set_active(
                        GTK_TOGGLE_BUTTON(GTK_TOGGLE_BUTTON(GXSEARCH(dialogwin)->checkbox)),
                         textstruct->matchcase); 

       gxsearch_set_match_case(dialogwin, textstruct->matchcase);

       gxsearch_set_search_dir(dialogwin, textstruct->searchdir);

       gxsearch_set_find_string(dialogwin, textstruct->searchterm);

       gtk_signal_connect(GTK_OBJECT(dialogwin->button[0]),
                        "clicked",(GtkSignalFunc)go_find,
                        textstruct);

       gtk_signal_connect_object(GTK_OBJECT(dialogwin->button[0]),
                        "clicked",(GtkSignalFunc)gtk_widget_destroy,
                        GTK_OBJECT(dialogwin));

       gtk_signal_connect_object(GTK_OBJECT(dialogwin->button[3]),
                        "clicked",(GtkSignalFunc)gtk_widget_destroy,
                        GTK_OBJECT(dialogwin));

       gtk_widget_show(GTK_WIDGET(dialogwin));
}

/* callback for the replace */
void replace_text(widgetinfo *textstruct, gpointer data) {
       Gxsearch *dialogwin;

       dialogwin = (Gxsearch*)gxsearch_new(REPLACE);

       gtk_toggle_button_set_active(
                        GTK_TOGGLE_BUTTON(GTK_TOGGLE_BUTTON(GXSEARCH(dialogwin)->checkbox)),
                         textstruct->matchcase); 

       gxsearch_set_search_dir(dialogwin, textstruct->searchdir);

       gxsearch_set_find_string(dialogwin, textstruct->searchterm);
       
       gxsearch_set_replace_string(dialogwin, textstruct->replaceterm);
       
       gtk_signal_connect(GTK_OBJECT(dialogwin->button[0]),
                        "clicked",(GtkSignalFunc)go_find,
                        textstruct);

       gtk_signal_connect_object(GTK_OBJECT(dialogwin->button[0]),
                        "clicked",(GtkSignalFunc)gtk_widget_destroy,
                        GTK_OBJECT(dialogwin));

       gtk_signal_connect(GTK_OBJECT(dialogwin->button[1]),
                        "clicked",(GtkSignalFunc)go_replace,
                        textstruct);

       gtk_signal_connect_object(GTK_OBJECT(dialogwin->button[1]),
                        "clicked",(GtkSignalFunc)gtk_widget_destroy,
                        GTK_OBJECT(dialogwin));

       gtk_signal_connect(GTK_OBJECT(dialogwin->button[2]),
                        "clicked",(GtkSignalFunc)replace_all_text,
                        textstruct);

       gtk_signal_connect_object(GTK_OBJECT(dialogwin->button[2]),
                        "clicked",(GtkSignalFunc)gtk_widget_destroy,
                        GTK_OBJECT(dialogwin));

       gtk_signal_connect_object(GTK_OBJECT(dialogwin->button[3]),
                        "clicked",(GtkSignalFunc)gtk_widget_destroy,
                        GTK_OBJECT(dialogwin));

       gtk_widget_show(GTK_WIDGET(dialogwin));
}

/* this is the replace function that is called from the hitting replace button */
int go_replace(GtkWidget *widget, widgetinfo *textwidget) {

    int rc = 0, len;
    GtkTextMark *insertpt;
    gchar *replacestr;
    GtkTextBuffer *buffer;

    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(GXTEXT(textwidget->textwidget)->textarea));
    
    /* find the text that we are goind to replace */
    rc = go_find (widget, textwidget);
    if (rc == TRUE) {
         gxtext_delete_text(textwidget->textwidget);

         replacestr = gxsearch_get_replace_string( GXSEARCH(gtk_widget_get_toplevel(widget)));

        if (replacestr != NULL) {
            len = strlen(replacestr);

            if (textwidget->replaceterm != NULL) {
                g_free(textwidget->replaceterm);
            }
            textwidget->replaceterm = (gchar*)g_malloc(len+1);
            if (textwidget->replaceterm != NULL) {
                memset(textwidget->replaceterm, '\0', len+1);
                memcpy(textwidget->replaceterm, replacestr, len);
            }

             /* must get the insert before we can set text at it as it may have changed */
             insertpt = gtk_text_buffer_get_insert(buffer) ;
         
             gtk_text_buffer_insert_at_cursor(buffer, replacestr, len);

            return TRUE;
        }                                                   
    }

    return FALSE;
}

void replace_all_text(GtkWidget *widget, widgetinfo *textwidget) {

    gint rc;

    rc = go_replace(widget, textwidget);
    while (rc == TRUE ) {
        rc = go_replace(widget, textwidget);
    }
}

static gboolean search_line(GtkWidget *gxtext, char *string, gint direction, gboolean matchcase) {

    GtkTextIter  currentpsn;
    GtkTextIter  toindex;
    GtkTextMark  *insertpt;
    GtkTextBuffer  *buffer;
    gint ipsnincr, ichars, iline, ilensearchstr, istart, iend;
    gchar *linedata;

    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(GXTEXT(gxtext)->textarea));

     /* get the insert mark of the buffer -> this is where the cursor is */
    insertpt = gtk_text_buffer_get_insert(buffer);

    /* now get the iter at the insert mark */
    gtk_text_buffer_get_iter_at_mark(buffer,  & currentpsn, insertpt);
    
    /* now get the line number from the iter */
    iline = gtk_text_iter_get_line( & currentpsn );

    ilensearchstr = strlen(string);

    if (direction == FORWARD) {
        /* now get the number of character in this line */
        ichars = gtk_text_iter_get_chars_in_line(& currentpsn);

        /* the above gives us the index at the end including null or eol */	
	/* this gets us to 0, 1 or eol minus the \n */
        ichars = (ichars < 0) ? 0 : ichars ;
        ichars = (ichars == 0) ? ichars : ichars - 1;
   
        /* get the iter at the end of the line */
        gtk_text_buffer_get_iter_at_line_index(buffer, & toindex, iline, ichars);

        ipsnincr = 1;

        /* here we get a line of data from our start point */
	linedata = gtk_text_buffer_get_text(buffer, &currentpsn, &toindex, FALSE);

        if (linedata == NULL) { 
            return FALSE;
        }
        
        istart = 0;
        iend = strlen(linedata);

    } else {

        ichars = 0;

        /* get the iter at the start of the line */
        gtk_text_buffer_get_iter_at_line_index(buffer, & toindex, iline, ichars);

        ipsnincr = -1;

        /* here we get a line of data from our start point */
	linedata = gtk_text_buffer_get_text(buffer, & toindex, &currentpsn, TRUE);

        if (linedata == NULL) { 
            return FALSE;
        }

        istart = strlen(linedata) - ilensearchstr;
        iend = 0; 

    }

    /* at this point istart is either 0 or the length of the data - the length of the string 
     * if istart = iend then we have no data and should not be here
     * or if either is less than 0 we should not continue */
    if ((istart == iend) || (istart <0) || (iend <0)) {
        return FALSE;
    }

    while ( ( (istart <= iend )  && (ipsnincr == 1) )  
             || ((ipsnincr == -1) && (istart >= (iend - ilensearchstr)))  ) {
 
        if ( ( (matchcase == FALSE) && (strncasecmp(string,linedata+istart, ilensearchstr) == 0) )
              || ( (matchcase == TRUE) && (strncmp(string,linedata+istart, ilensearchstr) == 0) ) ) {
            gint here;
 
            here = gtk_text_iter_get_offset( &currentpsn);
            if (direction == FORWARD) {
                gtk_text_iter_set_offset(&currentpsn, istart+here);
            } else {
                gtk_text_iter_set_line_offset(&currentpsn, istart);
            }

            gtk_text_buffer_place_cursor(buffer, &currentpsn);

            insertpt = gtk_text_buffer_get_insert(buffer);

            here = gtk_text_iter_get_offset( &currentpsn);

            gtk_text_iter_set_offset(&currentpsn, here+ilensearchstr);

            gtk_text_buffer_move_mark(buffer, insertpt, &currentpsn);

            /* this is for search up so that we are at the beginning of the word */
            if (direction == REVERSE) {

                gtk_text_buffer_place_cursor(buffer, &currentpsn);

                gtk_text_iter_set_offset(&currentpsn, here);

                gtk_text_buffer_move_mark(buffer, insertpt, &currentpsn);
            }

            return TRUE;
        }

        istart+=ipsnincr;
    }
    /* set the iter to end of the line as we found nothing */
    gtk_text_iter_set_line_offset(&currentpsn, ichars);
    gtk_text_buffer_place_cursor(buffer, &currentpsn);
    return FALSE;
}


/* this searches through the text widget and higlights text when there is a match */
int go_find (GtkWidget *widget, widgetinfo *textstruct) {
    gint len, rc, icurline, ipsnincr, iend, ibegofline;
    gchar *searchstr;
    GtkTextIter curpos, start, end;
    GtkTextMark *insertpt;
    GtkTextBuffer *buffer;

    if (widget != NULL) {
        /* get the search term from the search widget */
        searchstr = gxsearch_get_find_string( GXSEARCH(gtk_widget_get_toplevel(widget))) ;

        textstruct->searchdir = gxsearch_get_search_dir(GXSEARCH(gtk_widget_get_toplevel(widget)));

        textstruct->matchcase = gxsearch_get_match_case(GXSEARCH(gtk_widget_get_toplevel(widget)));

    } else {
        len = strlen(textstruct->searchterm);
        searchstr = (gchar*) g_malloc(len+1);
        if (searchstr == NULL) {
            return 0;
        }
        memset(searchstr, '\0', len+1);
        memcpy(searchstr, textstruct->searchterm, len);
    }

    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(GXTEXT(textstruct->textwidget)->textarea));

    /* make sure it is not null */
    if ((searchstr != NULL) && (strlen(searchstr) > 0)) {

        /* now set len to its length */
        len = strlen(searchstr);     

        if (textstruct->searchterm != NULL) {
            g_free(textstruct->searchterm);
        }
        textstruct->searchterm = (gchar*)g_malloc(len+1);
        if (textstruct->searchterm != NULL) {
            memset(textstruct->searchterm, '\0', len+1);
            memcpy(textstruct->searchterm, searchstr, len);
        }

        /* get the insert mark of the buffer -> this is where the cursor is */
        insertpt =gtk_text_buffer_get_insert(buffer) ;

        /* now get the iter at the insert mark */
        gtk_text_buffer_get_iter_at_mark(buffer,  & curpos, insertpt);
    
        /* now get the line number from the iter */
        icurline = gtk_text_iter_get_line( & curpos );

        gtk_text_buffer_get_bounds(buffer, &start, &end);

        /* here we need to find if we are going forward or back 
         * and then go up or down line index */
        if ( textstruct->searchdir == FORWARD ) { 
            ipsnincr = 1;
            
            /* now get the line number from the iter */
            iend = gtk_text_iter_get_line( & end );            
        } else {
            ipsnincr = -1;
            
            /* now get the line number from the iter */
            iend = gtk_text_iter_get_line( & start );            
        }        
        
        /* this next function searches through a line of text */
        rc = search_line(textstruct->textwidget, textstruct->searchterm, textstruct->searchdir, textstruct->matchcase);
        if (rc == TRUE ) {
            return TRUE;
        }

        while (rc != TRUE ) {
            icurline += ipsnincr;
        
            if ( textstruct->searchdir == FORWARD ) { 
                ibegofline = 0;
                if (icurline > iend) { 
                    break;   /* break out of while loop to set cursor to right position */
                } 
                gtk_text_iter_set_line(&curpos, icurline);
            } else {
                if (icurline < iend) { 
                    break;   /* break out of while loop to set cursor to right position */
                } 
                gtk_text_iter_set_line(&curpos, icurline);
                
                /* now get the number of character in this line */
                ibegofline = gtk_text_iter_get_chars_in_line(& curpos);

                /* the above gives us the index at the end including null or eol */	
        	/* this gets us to 0, 1 or eol minus the \n */
                ibegofline = (ibegofline < 0) ? 0 : ibegofline ;
                ibegofline = (ibegofline == 0) ? ibegofline : ibegofline - 1;
            }

            /* set the iter to ibegofline of the line as we found nothing */
            gtk_text_iter_set_line_offset(&curpos, ibegofline); 
            gtk_text_buffer_place_cursor(buffer, &curpos);

            insertpt =gtk_text_buffer_get_insert(buffer) ;

            gtk_text_view_scroll_mark_onscreen(GTK_TEXT_VIEW(GXTEXT(textstruct->textwidget)->textarea), insertpt);

            rc = search_line(textstruct->textwidget, textstruct->searchterm, textstruct->searchdir, textstruct->matchcase);
            if (rc == TRUE ) { 
                return TRUE;
            }
           
        }
    }
    /* need to add a message here */
    if ( textstruct->searchdir == FORWARD ) { 
        gtk_text_iter_set_line(&curpos, 0);
    } else {
        iend = gtk_text_iter_get_line( & end ); 
        gtk_text_iter_set_line(&curpos, iend);
    }
    gtk_text_buffer_place_cursor(buffer, &curpos);

    insertpt =gtk_text_buffer_get_insert(buffer) ;

    gtk_text_view_scroll_mark_onscreen(GTK_TEXT_VIEW(GXTEXT(textstruct->textwidget)->textarea), insertpt);

    return 0;
}




