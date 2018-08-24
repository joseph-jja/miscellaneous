#ifndef __GXMESSAGEBOX_H__
#define __GXMESSAGEBOX_H__

#include <gdk/gdk.h>
#include <gtk/gtkwidget.h>
#include <gtk/gtkdialog.h>
#include <gtk/gtklabel.h>

#ifdef  __cplusplus 
extern "C" {
#endif /* __cplusplus */

#define GXMESSAGEBOX(obj)          GTK_CHECK_CAST(obj, gxmessagebox_get_type(), Gxmessagebox)
#define GXMESSAGEBOX_CLASS(klass)  GTK_CHECK_CLASS_CAST(klass, gxmessagebox_get_type(), GxmessageboxClass)
#define IS_GXMESSAGEBOX(obj)       GTK_CHECK_TYPE(obj, gxmessagebox_get_type())

typedef struct _Gxmessagebox Gxmessagebox;
typedef struct _GxmessageboxClass GxmessageboxClass;

enum {
    YES_NO_CANCEL_GXMESSAGEBOX, 
    OK_GXMESSAGEBOX
};

struct _Gxmessagebox {
    GtkWindow gxmessagebox;
    GtkDialog *dialog;
    GtkWidget *label;
};

struct _GxmessageboxClass {
    GtkWindowClass parent_class;
    void (* gxmessagebox) (Gxmessagebox *xxx);
};

/* wintype is the type of dialog to create */
GtkWidget*       gxmessagebox_new               (void);
GtkType            gxmessagebox_get_type          (void);

gint gxmessagebox_run(const gchar* message, int type); 

#ifdef  __cplusplus
}
#endif /* __cplusplus */

#endif /* _GXMESSAGEBOX_H */
