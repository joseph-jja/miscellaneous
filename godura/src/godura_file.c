#include "godura_file.h"
#include <gtk/gtkfilechooserdialog.h>

/* private functions */
static void do_set_title(GtkWidget *, gchar *, gchar *);
static gint write_out_file (widgetinfo *);

/* generic funtion to read in a file */
static void read_in_file (GtkWidget *, widgetinfo *);

/* prototype for the open file window */
static void open_file (widgetinfo *);

static char msg_buf_sn[255];

/* this launches a new window */
void new_window() {
    system("godura &");
}

/* simple function for setting the title 
 * this takes the GtkWidget that is the window
 * it takes the program name
 * then it takes the file name and puts a - in between them
 * if fname is NULL it will set the title accordingly */ 
static void do_set_title(GtkWidget *window, gchar *progname, gchar *fname) {

    gchar *title;

    /* now set the title */
    title = (gchar*) g_malloc(strlen(progname) + 4 + strlen(fname));
    strcpy(title,progname);
    if (fname != "\0") {
        strcat(title, " - ");
        strcat(title, fname);
    }
    gtk_window_set_title(GTK_WINDOW(window), title);
    g_free(title);

}

void destroy_window_event (GtkWidget *w, GdkEventAny *event, widgetinfo *textstruct)
{
    GList *l, *m; 
    gint ret = 1;
    GtkTextBuffer *buffer;

    l = gtk_container_get_children(GTK_CONTAINER(w));
    
    m = gtk_container_get_children(GTK_CONTAINER(GTK_WIDGET(l->data)));

    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(GXTEXT(g_list_nth_data(m, 1))->textarea));

    if (gtk_text_buffer_get_modified(buffer) )  { 
        ret = gxmessagebox_run(EXITMESSAGE, YES_NO_CANCEL_GXMESSAGEBOX);
        
        switch (ret) {
            case 0:
	        /* user selected Yes - save file then exit*/
		save_file( textstruct );
		break;   
            case 2:
	        /* user selected cancel- just return */
		return;
                break;   
            default:
                /* do nothing the user has selected No */
              break;   
        }
    }
    //stack_reset(textstruct);
    gtk_main_quit();
}

/* exit / destroy all */
void destroy_event (widgetinfo *textstruct)
{
    /* default is if the text widget has not changed to just open the file */
    gint ret = 1;
    GtkTextBuffer *buffer;

    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(GXTEXT(textstruct->textwidget)->textarea));

    /* text has changed so what does the user want to do ? */
    if (gtk_text_buffer_get_modified(buffer) )  {
        ret = gxmessagebox_run(EXITMESSAGE, YES_NO_CANCEL_GXMESSAGEBOX);
    
        switch (ret) {
            case 0:
	        /* user selected yes - save file then exit*/
		save_file(textstruct);
		break;   
            case 2:
	        /* user selected cancel- just return */
		return;
                break;   
            default:
                /* do nothing the user has selected no */
               break;   
        }
    }  

    stack_reset(textstruct);
    gtk_main_quit();
}

/* this is for the window that opens a file */
static void open_file (widgetinfo *textstruct) {

       textstruct->sudomodalwin = gtk_file_chooser_dialog_new("Open...", (GtkWindow*)textstruct->mainwindow, 
				     GTK_FILE_CHOOSER_ACTION_OPEN,
				      GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
				      GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
				      NULL);
				      
       gtk_window_set_position(GTK_WINDOW(textstruct->sudomodalwin),GTK_WIN_POS_CENTER_ALWAYS);
 
        if (gtk_dialog_run (GTK_DIALOG (textstruct->sudomodalwin)) == GTK_RESPONSE_ACCEPT)
        {
	 if (textstruct->filename != NULL) {
    		g_free(textstruct->filename);
    		textstruct->filename = "\0";
   	 }
	 textstruct->filename = (gchar*)g_malloc(strlen((gchar*)gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (textstruct->sudomodalwin))) + 1);
         strcpy((gchar*)textstruct->filename,(gchar*)gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (textstruct->sudomodalwin)));

	 read_in_file(NULL, textstruct);
        }
  	gtk_widget_destroy (textstruct->sudomodalwin);

}

void check_new (widgetinfo *textwidget)
{
    /* default is if the text widget has not changed to just open the file */
    gint ret = 1;
    GtkTextBuffer *buffer;

    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(GXTEXT(textwidget->textwidget)->textarea));

    /* text has changed so what does the user want to do ? */
    if (gtk_text_buffer_get_modified(buffer) ) {
        ret = gxmessagebox_run(NEWMESSAGE, YES_NO_CANCEL_GXMESSAGEBOX);
    }
    
    switch (ret) {
            case 0:
	        /* user selected yes - save file and set as new */
		save_file(textwidget);
                gxtext_set_as_new(textwidget->textwidget);
	        do_set_title(textwidget->mainwindow, PROGRAMNAME, "\0");
		if (textwidget->filename != NULL) {
                    g_free(textwidget->filename);
                    textwidget->filename = NULL;
                }
	        stack_reset(textwidget);
	        stack_init(textwidget);
                break;   
            case 1:
	        /* user selected no - don't save file and do set as new */
                gxtext_set_as_new(textwidget->textwidget);
	        do_set_title(textwidget->mainwindow, PROGRAMNAME, "\0");
                if (textwidget->filename != NULL) {
                    g_free(textwidget->filename);
                    textwidget->filename = NULL;
                }
	        stack_reset(textwidget);
	        stack_init(textwidget);
                break;   
            default:
                /* do nothing the user has canceled or selected no */
               break;   
        }
    
}

/* check to see if we should open the file or do something else  */ 
void check_open (widgetinfo *textwidget)
{
    /* default is if the text widget has not changed to just open the file */
    gint ret = 1;
    GtkTextBuffer *buffer;

    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(GXTEXT(textwidget->textwidget)->textarea));
				      
    /* text has changed so what does the user want to do ? */
    if (gtk_text_buffer_get_modified(buffer) ) {
        ret = gxmessagebox_run(OPENMESSAGE, YES_NO_CANCEL_GXMESSAGEBOX);
    }
    switch (ret) {
            case 0:
	        /* user selected yes - save file, set text as new, 
		 * and then open new file */
		save_file(textwidget);
                open_file(textwidget);
	        stack_reset(textwidget);
	        stack_init(textwidget);
                break;   
            case 1:
	        /* user selected no - set as new and open file */
                open_file(textwidget);
	        stack_reset(textwidget);
	        stack_init(textwidget);
                break;   
            default:
                /* do nothing the user has canceled or selected no */
               break;   
        }
   
}

void save_file (widgetinfo *textstruct) {

	if (textstruct->filename != NULL) {
	    if ( gxtext_write_out_ascii_file(GTK_WIDGET(textstruct->textwidget), textstruct->filename)  != 0 ) 
            {
                sprintf(msg_buf_sn, "Could not write file named (%s)\n", textstruct->filename);
		gxmessagebox_run(msg_buf_sn, OK_GXMESSAGEBOX);
	        return;
             }
             do_set_title(textstruct->mainwindow, 
	                  PROGRAMNAME, 
			  (gchar*)textstruct->filename);
	} else {
		saveas_file (textstruct) ;
	} 
}

/* this reads in a file to the text widget */
static gint write_out_file (widgetinfo *textstruct)
{
    if (  gxtext_write_out_ascii_file(GTK_WIDGET(textstruct->textwidget), textstruct->filename) != 0 ) {
        return -1;
    }
    do_set_title(textstruct->mainwindow, PROGRAMNAME, (gchar*)textstruct->filename);
    return 0;
}


void saveas_file (widgetinfo *textstruct) {

	int rc=0, x=0;
	struct stat buf;	

       textstruct->sudomodalwin = gtk_file_chooser_dialog_new("Save As...", (GtkWindow*)textstruct->mainwindow, 
				     GTK_FILE_CHOOSER_ACTION_SAVE,
				      GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
				      GTK_STOCK_SAVE, GTK_RESPONSE_ACCEPT,
				      NULL);
	gtk_window_set_position(GTK_WINDOW(textstruct->sudomodalwin),GTK_WIN_POS_CENTER_ALWAYS);

if (gtk_dialog_run (GTK_DIALOG (textstruct->sudomodalwin)) == GTK_RESPONSE_ACCEPT)
  {
    	if (textstruct->filename != NULL) {
    		g_free(textstruct->filename);
    		textstruct->filename = "\0";
   	 }
	 textstruct->filename = (gchar*)g_malloc(strlen((gchar*)gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (textstruct->sudomodalwin))) + 1);
         strcpy((gchar*)textstruct->filename,(gchar*)gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (textstruct->sudomodalwin)));

	 /* check to see if the file exists */   
    if ( stat(textstruct->filename, &buf) == 0 ) {
            rc = gxmessagebox_run(ERRORFILEEXISTS, YES_NO_CANCEL_GXMESSAGEBOX);
	    switch (rc) {
	        case 0:
		    if ( write_out_file(textstruct) != 0 ) { 
		    	sprintf(msg_buf_sn, "Could not write file %s\n", textstruct->filename);
			gxmessagebox_run(msg_buf_sn, OK_GXMESSAGEBOX);
		    }
		    break;
	        case 1:
	            saveas_file(textstruct);
	    	    break;
	        case 2:
	            return;
	        default:
	            break;	
	    }	
    } else {
        /* the file does not exist */
        if ( write_out_file( textstruct) != 0 ) { 
	    	sprintf(msg_buf_sn, "Could not write file %s\n", textstruct->filename);
		gxmessagebox_run(msg_buf_sn, OK_GXMESSAGEBOX);
	}
    }            

  }
	gtk_widget_destroy (textstruct->sudomodalwin);
}

/* this reads ina  file to the text widget */
static void read_in_file (GtkWidget *widget, widgetinfo *textstruct)
{

    gint rc=0; 

    if (widget) {
        if (textstruct->filename != NULL) {
               g_free(textstruct->filename);
               textstruct->filename = NULL;
         }
         textstruct->filename = (gchar*)g_malloc(strlen((gchar*)gtk_file_selection_get_filename(GTK_FILE_SELECTION(textstruct->sudomodalwin))) + 1);
            strcpy((gchar*)textstruct->filename,(gchar*)gtk_file_selection_get_filename(GTK_FILE_SELECTION(textstruct->sudomodalwin)));
    }

    /* set the widget as new */
    gxtext_set_as_new(textstruct->textwidget);

    rc = gxtext_read_in_ascii_file(GTK_WIDGET(textstruct->textwidget), textstruct->filename);

    if (rc == 0) {
	sprintf(msg_buf_sn, "Could not open file named (%s)\n", textstruct->filename);
	gxmessagebox_run(msg_buf_sn, OK_GXMESSAGEBOX);
        return;
    }

    stack_reset(textstruct);
    stack_init(textstruct);
 
    do_set_title(textstruct->mainwindow, PROGRAMNAME, (gchar*)textstruct->filename);
}


