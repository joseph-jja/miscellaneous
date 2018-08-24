#ifndef _GXSOCKET_H
#define _GXSOCKET_H

#include <gdk/gdk.h>
#include <gtk/gtkwidget.h>
#include <gtk/gtkentry.h>
#include <gtk/gtkwindow.h>
#include <gtk/gtkbutton.h>
#include <gtk/gtklabel.h>
#include <gtk/gtktable.h>
#include <gtk/gtktextbuffer.h>

#ifdef  __cplusplus
extern "C" {
#endif

#define GXSOCKET(obj)          GTK_CHECK_CAST(obj, gxsocket_get_type(), Gxsocket)
#define GXSOCKET_CLASS(klass)  GTK_CHECK_CLASS_CAST(klass, gxsocket_get_type(), GxsocketClass)
#define IS_GXSOCKET(obj)       GTK_CHECK_TYPE(obj, gxsocket_get_type())

typedef struct _Gxsocket Gxsocket;
typedef struct _GxsocketClass GxsocketClass;

struct _Gxsocket {
    GtkWindow gxsocket;
    GtkWidget *proto_label;
    GtkWidget *proto_entry;
    GtkWidget *server_label;
    GtkWidget *server_entry;
    GtkWidget *port_label;
    GtkWidget *port_entry;
    GtkWidget *url_label;
    GtkWidget *url_entry;
    GtkWidget *button[2];

    // resulting text buffer
    GtkWidget *textBuffer;
};

struct _GxsocketClass {
    GtkWindowClass parent_class;
    void (* gxsocket) (Gxsocket *xxx);
};

/* wintype is the type of dialog to create */
GtkWidget*       gxsocket_new               ();
GtkType            gxsocket_get_type          (void);

void          gxsocket_load_URL(Gxsocket *);

#ifdef  __cplusplus
}
#endif

#endif /* _GXSOCKET_H */ 
