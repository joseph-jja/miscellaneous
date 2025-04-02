#include <gxsearch.h>

#include <gtk/gtkwindow.h>

#define FINDTEXT                        "Find: "
#define REPLACETEXT                "Replace: "
#define REPLACE_ALLTEXT                "Replace ALL: "
#define MATCHCASE                  "Match Case"
#define DIRECTION_UP               "Up"
#define DIRECTION_DOWN         "Down"

/* local function declarations */
static void gxsearch_class_init (GxsearchClass *);

static void gxsearch_init (Gxsearch *);

/* standard gtk widget function take from the documentation */
GType gxsearch_get_type () {

    static GType xxx_type = 0;
    if (!xxx_type) {
        static const GTypeInfo xxx_info = 
        {  
             sizeof(GxsearchClass),
             NULL, 
             NULL,
             (GClassInitFunc)gxsearch_class_init,
             NULL,
             NULL,
             sizeof(Gxsearch),
             0,
             (GInstanceInitFunc) gxsearch_init,
        };
        xxx_type = g_type_register_static (GTK_TYPE_WINDOW, "Gxsearch", &xxx_info, 0);
    }
    return xxx_type;
}

static void gxsearch_class_init (GxsearchClass *class) {
    GtkObjectClass *object_class;
    
    object_class = (GtkObjectClass*) class;
    
    class->gxsearch = NULL;
}

static void gxsearch_init (Gxsearch *xxx) {

    xxx->label = 0;
    xxx->entry = 0;
    xxx->checkbox = 0;
    xxx->direction[0] = 0;
    xxx->direction[1] = 0;
    xxx->button[0] = 0; 
    xxx->button[1] = 0; 
    xxx->button[2] = 0; 
    xxx->button[3] = 0; 
 
}

/* here is the meat of the widget */
/* this is the base constructor for this klass */
GtkWidget* gxsearch_new(gint type) {

    Gxsearch *message;
    GtkWidget *table;

    message = gtk_type_new(gxsearch_get_type());

    table = (GtkWidget*)gtk_table_new(4, 5, FALSE);

    gtk_container_add (GTK_CONTAINER(message), table);

    /* this is the find */
    message->label = gtk_label_new(FINDTEXT);
    message->entry = gtk_entry_new_with_max_length(40);
    message->button[0] = (GtkWidget*)gtk_button_new_with_label(FINDTEXT);

    /* column left, column right, row left, row right */
    gtk_table_attach_defaults(GTK_TABLE(table),message->label,0,1,0,1);
    gtk_table_attach_defaults(GTK_TABLE(table),message->entry,1,3,0,1);
    gtk_table_attach_defaults(GTK_TABLE(table),message->button[0],3,4,0,1);

    gtk_widget_show(message->label);
    gtk_widget_show(message->entry);
    gtk_widget_show(message->button[0]);

    if (type == REPLACE) {

        /* this is the replace */
        message->slabel = gtk_label_new(REPLACETEXT);
        message->sentry = gtk_entry_new_with_max_length(40);
        message->button[1] = (GtkWidget*)gtk_button_new_with_label(REPLACETEXT);

        gtk_table_attach_defaults(GTK_TABLE(table),message->slabel,0,1,1,2);
        gtk_table_attach_defaults(GTK_TABLE(table),message->sentry,1,3,1,2);
        gtk_table_attach_defaults(GTK_TABLE(table),message->button[1],3,4,1,2);

        gtk_widget_show(message->slabel);
        gtk_widget_show(message->sentry);
        gtk_widget_show(message->button[1]);

        message->button[2] = (GtkWidget*)gtk_button_new_with_label(REPLACE_ALLTEXT);

        gtk_table_attach_defaults(GTK_TABLE(table),message->button[2],3,4,2,3);

        gtk_widget_show(message->button[2]);

    }

    message->checkbox = gtk_check_button_new_with_label(MATCHCASE);
    message->direction[0] = gtk_radio_button_new_with_label(NULL, DIRECTION_UP);
    message->direction[1] = gtk_radio_button_new_with_label(
               gtk_radio_button_group(GTK_RADIO_BUTTON(message->direction[0])), DIRECTION_DOWN);

    message->button[3] = gtk_button_new_with_label("Cancel");

    if (type == REPLACE) {
        gtk_table_attach_defaults(GTK_TABLE(table),message->checkbox,0,1,3,4);
        gtk_table_attach_defaults(GTK_TABLE(table),message->direction[0],1,2,3,4);
        gtk_table_attach_defaults(GTK_TABLE(table),message->direction[1],2,3,3,4);
        gtk_table_attach_defaults(GTK_TABLE(table),message->button[3],3,4,3,4);
    } else {
        gtk_table_attach_defaults(GTK_TABLE(table),message->checkbox,0,1,1,2);
        gtk_table_attach_defaults(GTK_TABLE(table),message->direction[0],1,2,1,2);
        gtk_table_attach_defaults(GTK_TABLE(table),message->direction[1],2,3,1,2);
        gtk_table_attach_defaults(GTK_TABLE(table),message->button[3],3,4,1,2);
    }

    gtk_widget_show(message->checkbox);
    gtk_widget_show(message->direction[0]);
    gtk_widget_show(message->direction[1]);
    gtk_widget_show(message->button[3]);

    gtk_widget_show(table);

    gtk_entry_set_text(GTK_ENTRY(message->entry),"\0");

    gtk_window_set_position(GTK_WINDOW(message),GTK_WIN_POS_CENTER);
    gtk_window_set_modal(GTK_WINDOW(message),TRUE);
    gtk_window_set_policy(GTK_WINDOW(message),FALSE, FALSE, FALSE);

    return GTK_WIDGET (message);
} 

void set_entry_term(GtkWidget *entry, gchar *value) { 
    if (value == NULL ) {
        gtk_entry_set_text(GTK_ENTRY(entry),"\0");
    } else {
        gtk_entry_set_text(GTK_ENTRY(entry),value);
    }
} 

/* set the search direction in the search widget */
void gxsearch_set_search_dir(Gxsearch *search, gboolean dir) {

    GSList *list;

     list = gtk_radio_button_group(GTK_RADIO_BUTTON(GXSEARCH(search)->direction[0])); 

    if (dir == UP ) { 
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(g_slist_nth_data(list,0)), FALSE);
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(g_slist_nth_data(list,1)), TRUE);
    } else {
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(g_slist_nth_data(list,1)), FALSE);
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(g_slist_nth_data(list,0)), TRUE);
    }

}

/* get the search direction that was set in the widget */
gboolean          gxsearch_get_search_dir(Gxsearch *search) {

    GSList *list;

     list = gtk_radio_button_group(GTK_RADIO_BUTTON(GXSEARCH(search)->direction[0])); 
    
     return ( gtk_toggle_button_get_active( GTK_TOGGLE_BUTTON(g_slist_nth_data(list,0)) )  );

} 

/* set the search direction in the search widget */
void gxsearch_set_match_case(Gxsearch *search, gboolean dir) {

    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(search->checkbox), dir);

}

/* get the search direction that was set in the widget */
gboolean          gxsearch_get_match_case(Gxsearch *search) {
   
    return gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(search->checkbox));
} 
gchar *gxsearch_get_find_string(Gxsearch *search) {
    return (gchar*)gtk_entry_get_text(GTK_ENTRY(GXSEARCH(search)->entry)); 
} 

void gxsearch_set_find_string(Gxsearch *search, gchar *findterm) {
    set_entry_term(GTK_WIDGET(GXSEARCH(search)->entry), findterm);
} 

gchar *gxsearch_get_replace_string(Gxsearch *search) { 
    return (gchar*)gtk_entry_get_text(GTK_ENTRY(GXSEARCH(search)->sentry));
}

void gxsearch_set_replace_string(Gxsearch *search, gchar *replaceterm) { 
    set_entry_term(GTK_WIDGET(GXSEARCH(search)->sentry), replaceterm);
}
