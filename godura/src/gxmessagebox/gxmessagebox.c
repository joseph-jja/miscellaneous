#include "gxmessagebox.h"
#include <assert.h>
#include <gtk/gtkbox.h>

static gint run_ok_dialog(const gchar* message);
static gint run_ync_dialog(const gchar *message); 

static void gxmessagebox_class_init          (GxmessageboxClass *klass);
static void gxmessagebox_init                (Gxmessagebox      *xxx);

GType gxmessagebox_get_type () {

  static GType xxx_type = 0;

  if (!xxx_type) {
      static const GTypeInfo xxx_info =
      {
	sizeof (GxmessageboxClass),
	NULL,
                NULL,
	(GClassInitFunc) gxmessagebox_class_init,
                NULL,
	NULL,
                sizeof (Gxmessagebox),
	0,
	(GInstanceInitFunc) gxmessagebox_init,
      };
      xxx_type = g_type_register_static (GTK_TYPE_WINDOW, "Gxmessagebox", &xxx_info, 0);
    }

  return xxx_type;
}

static void gxmessagebox_class_init (GxmessageboxClass *class)
{
  GtkObjectClass *object_class;

  object_class = (GtkObjectClass*) class;

  class->gxmessagebox = NULL;
}

static void gxmessagebox_init (Gxmessagebox *xxx)
{     
    xxx->dialog = 0;
    xxx->label = 0;
}

GtkWidget *gxmessagebox_new () {
   Gxmessagebox *xxx;
    xxx = gtk_type_new(gxmessagebox_get_type());

    xxx->dialog = (GtkDialog*)gtk_dialog_new();
    xxx->label = gtk_label_new(" ");

    gtk_box_pack_start(GTK_BOX(GTK_DIALOG(xxx->dialog)->vbox),xxx->label, FALSE, FALSE, 0);
    gtk_widget_show(xxx->label);
 
  return GTK_WIDGET (xxx);
}


gint gxmessagebox_run(const gchar* message, int type) {

     if ( type == YES_NO_CANCEL_GXMESSAGEBOX ) {
        return run_ync_dialog(message);
     } else if ( type == OK_GXMESSAGEBOX ) { 
        return run_ok_dialog(message);
     } else {
        assert("boom!");
    }
    return -1;
}

/* generic funciton that we use to bring up a ys no cancel dialog box */
static gint run_ync_dialog(const gchar *messagestring)
{
    GtkWidget *yncdialog;
    gint result;

    yncdialog = gxmessagebox_new();

    gtk_label_set_text(GTK_LABEL(GXMESSAGEBOX(yncdialog)->label), messagestring);
    
    gtk_dialog_add_button(GTK_DIALOG(GXMESSAGEBOX(yncdialog)->dialog), "Yes", 0);

    gtk_dialog_add_button(GTK_DIALOG(GXMESSAGEBOX(yncdialog)->dialog), "No", 1);

    gtk_dialog_add_button(GTK_DIALOG(GXMESSAGEBOX(yncdialog)->dialog), "Cancel", 2);

    gtk_window_set_position(GTK_WINDOW(GXMESSAGEBOX(yncdialog)->dialog),GTK_WIN_POS_CENTER_ALWAYS);

    result = gtk_dialog_run(GTK_DIALOG(GXMESSAGEBOX(yncdialog)->dialog));

    /* now destroy the dialog box */
    gtk_widget_destroy(GTK_WIDGET(GXMESSAGEBOX(yncdialog)->dialog));

    return result;
}


/* generic funciton that we use to bring up a ys no cancel dialog box */
static gint run_ok_dialog(const gchar *messagestring)
{
   GtkWidget *okdialog;
   gint result;

    okdialog = gxmessagebox_new();

    gtk_label_set_text(GTK_LABEL(GXMESSAGEBOX(okdialog)->label), messagestring);

    gtk_dialog_add_button(GTK_DIALOG(GXMESSAGEBOX(okdialog)->dialog), "Ok", 0);

    gtk_window_set_position(GTK_WINDOW(GXMESSAGEBOX(okdialog)->dialog),GTK_WIN_POS_CENTER_ALWAYS);

    result = gtk_dialog_run(GTK_DIALOG(GXMESSAGEBOX(okdialog)->dialog));

    /* now destroy the dialog box */
    gtk_widget_destroy(GTK_WIDGET(GXMESSAGEBOX(okdialog)->dialog));

    return result;
}


