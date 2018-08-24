#ifndef __GXSEARCH_H__
#define __GXSEARCH_H__

#include <gdk/gdk.h>
#include <gtk/gtkwidget.h>
#include <gtk/gtkentry.h>
#include <gtk/gtkwindow.h>
#include <gtk/gtkbutton.h>
#include <gtk/gtklabel.h>
#include <gtk/gtktable.h>
#include <gtk/gtkradiobutton.h>

#ifdef  __cplusplus 
extern "C" {
#endif /* __cplusplus */

#define GXSEARCH(obj)          GTK_CHECK_CAST(obj, gxsearch_get_type(), Gxsearch)
#define GXSEARCH_CLASS(klass)  GTK_CHECK_CLASS_CAST(klass, gxsearch_get_type(), GxsearchClass)
#define IS_GXSEARCH(obj)       GTK_CHECK_TYPE(obj, gxsearch_get_type())

typedef struct _Gxsearch Gxsearch;
typedef struct _GxsearchClass GxsearchClass;

/* this is for the check boxes for the diection */
enum {
    UP, 
    DOWN
};

/* this is for the check box for the match case */
enum {
    UNCHECKED, 
    CHECKED
};

/* this is to bring up eith erht find window or the replace window */
enum {
    FIND, 
    REPLACE
};

struct _Gxsearch {
    GtkWindow gxsearch;
    GtkWidget *label;
    GtkWidget *entry;
    GtkWidget *slabel;
    GtkWidget *sentry;
    GtkWidget *checkbox;
    GtkWidget *direction[2];
    GtkWidget *button[4];
};

struct _GxsearchClass {
    GtkWindowClass parent_class;
    void (* gxsearch) (Gxsearch *xxx);
};

/* wintype is the type of dialog to create */
GtkWidget*       gxsearch_new               (gint type);
GtkType            gxsearch_get_type          (void);

gchar *          gxsearch_get_find_string(Gxsearch *); 

void             gxsearch_set_find_string(Gxsearch *, gchar *); 

void             gxsearch_set_replace_string(Gxsearch *, gchar *);

gchar *          gxsearch_get_replace_string(Gxsearch *); 

void             gxsearch_set_search_string(Gxsearch *, gchar *); 

void             gxsearch_set_search_dir(Gxsearch *, gboolean); 

gboolean          gxsearch_get_search_dir(Gxsearch *); 

void             gxsearch_set_match_case(Gxsearch *, gboolean); 

gboolean          gxsearch_get_match_case(Gxsearch *); 


#ifdef  __cplusplus
}
#endif /* __cplusplus */

#endif /* _GXSEARCH_H */
