#ifndef _GODURA_H
#define _GODURA_H

#ifdef  __cplusplus
extern "C" {
#endif

#include <gtk/gtk.h>
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

#include <gxtext.h>

/* this file contains all the common stuff 
 * in particular the main structure that is used 
 * by almost all functions.
 * This should be included by all godura C files.  */

#define BUFFLEN                    1024
#define ONEBITE                     1

#define PROGRAM                  "godura" 
#define PROGRAMNAME         "Godura"
#define COPYRIGHT                "Licensed under the GPL"
#define AUTHOR                     "Joseph Acosta (joeja@mindspring.com)"
#define VERSION                    "0.6.1"

#define TEXTFONT "Sans 10"

#define SPECFONT "-*-times-medium-r-*-*-*-100-*-*-*-*-*-*"

/* the structure widgetinfo contains pointers to the 
        1) undo stack list
	2) undo stack index
	3) main window, 
	4) the textwidget, 
	5) a pointer to a modal window, 
	6) the filename,
	7) the search term that was last searched 
	8) the replace term that was last replaced
        9) the variable for matching case 
        10) the search direction
 */

typedef struct {
        GList *undo_redo;
        guint undo_redo_idx;
        GtkWidget *mainwindow;
        GtkWidget *textwidget;  /* this is our gxtext widget */
        GtkWidget *sudomodalwin;
        gchar *filename;
        gchar *searchterm;
        gchar *replaceterm;
        gboolean matchcase;
        gboolean searchdir;
} widgetinfo;

/* these are the prototypes for the destroy event */
void destroy_event (widgetinfo *);     // called from file menu
void destroy_window_event (GtkWidget *,GdkEventAny *event, widgetinfo *);              // called by killing window


#ifdef  __cplusplus
}
#endif

#endif

