#ifndef _UNDO_STACK_H
#define _UNDO_STACK_H


#include <gdk/gdk.h>
#include <gtk/gtkwidget.h>
#include <gtk/gtktextbuffer.h>
#include <string.h>
#include "godura.h"

gulong insertid;
gulong deleteid;

struct undostack {
    gchar *data;
    gchar type;
    gint datalen;
    gint pos; 
    guint signalid;
};

typedef struct undostack UNDO_STACK;

void delete_stack_push(GtkTextBuffer *, GtkTextIter *, GtkTextIter *,  widgetinfo *); 

void insert_stack_push(GtkTextBuffer *, GtkTextIter *, gchar *, gint, widgetinfo *); 

void stack_pop(GtkTextBuffer *, widgetinfo *);

void stack_push(GtkTextBuffer *, widgetinfo *);

void stack_reset(widgetinfo *);

void stack_init(widgetinfo *);

#endif 

