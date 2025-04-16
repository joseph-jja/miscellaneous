#include "godura.h"
#include "godura_undo_redo.h"
#include "godura_edit.h"
#include "godura_file.h"
#include "godura_help.h"
#include "godura_search.h"
#include "godura_misc.h"
#include "godura_prefs.h"

#define EDIT_MENU 1


static GtkItemFactoryEntry menu_items[] = {
  {"/_File", NULL, NULL, 0, "<Branch>"},
  {"/File/_New", NULL, check_new, 0, NULL},
  {"/File/_Open", "<Control>O", check_open, 0, NULL},
  {"/File/Open _Url", NULL, insert_web_page, 0, NULL},
  {"/File/_Save", "<Control>S", save_file, 1, NULL},
  {"/File/Save _As", "<Control>A", saveas_file, 0, NULL},
  {"/File/sep1", NULL, NULL, 0, "<Separator>"},
  {"/File/New _Window", NULL, new_window, 0, NULL},
/*	{ "/File/Print Se_tup", NULL, NULL, 0, NULL },
	{ "/File/_Print", NULL, NULL, 0, NULL },   */
  {"/File/sep2", NULL, NULL, 0, "<Separator>"},
/*	{ "/File/Send e-mail", NULL, NULL, 0, NULL },
	{ "/File/sep2", NULL, NULL, 0, "<Separator>" },*/
  {"/File/E_xit", NULL, destroy_event, 0, NULL},
  {"/_Edit", NULL, NULL, 0, "<Branch>"},
  {"/Edit/_Undo", "<Control>Z", undo_last, 0, NULL},
  {"/Edit/_Redo", "<Control>Y", redo_last, 0, NULL},
  {"/Edit/sep1", NULL, NULL, 0, "<Separator>"},
  {"/Edit/Cu_t", "<Control>X", cut_text, 0, NULL},
  {"/Edit/_Copy", "<Control>C", copy_text, 0, NULL},
  {"/Edit/_Paste", "<Control>V", paste_text, 0, NULL},
  {"/Edit/D_elete", NULL, delete_text, 0, NULL},
  {"/Edit/sep2", NULL, NULL, 0, "<Separator>"},
  {"/Edit/Select _All", NULL, select_text, 0, NULL},
  {"/Edit/Time _Date", NULL, get_current_time, 0, NULL},
  {"/Edit/sep3", NULL, NULL, 0, "<Separator>"},
  {"/Edit/Word _wrap", NULL, wrap_text, 0, "<ToggleItem>"},
  {"/_Search", NULL, NULL, 0, "<Branch>"},
  {"/Search/_Find", "<Control>F", find_text, 0, NULL},
  {"/Search/F_ind Next", "F3", find_next_text, 0, NULL},
  {"/Search/_Replace", "<Control>R", replace_text, 0, NULL},
  {"/_Preferences", NULL, NULL, 0, "<Branch>"},
  {"/Preferences/Fo_nt", NULL, change_font, 0, NULL},
  {"/_RPM Tool", NULL, NULL, 0, "<Branch>"},
  {"/RPM Tool/_Spec File Template", NULL, insertdata, 0, NULL},
  {"/_Help", NULL, NULL, 0, "<LastBranch>"},
  {"/Help/_About", NULL, help_about, 0, NULL},
  {"/Help/_Help", NULL, help_help, 0, NULL},
};

void
get_menu_items (GtkWidget * window, GtkWidget ** menubar, widgetinfo * textstruct) {

  GtkItemFactory *item_factory;
  GtkAccelGroup *accel_group;
  gint nmenu_items = sizeof (menu_items) / sizeof (menu_items[0]);

  accel_group = gtk_accel_group_new();

  item_factory = gtk_item_factory_new (GTK_TYPE_MENU_BAR, "<main>", accel_group);

  gtk_item_factory_create_items (item_factory, nmenu_items, menu_items, textstruct);

  gtk_window_add_accel_group (GTK_WINDOW (window), accel_group);

  if (menubar) {
    *menubar = gtk_item_factory_get_widget (item_factory, "<main>");
  }

}

int main (int argc, char *argv[]) {
	
  GtkWidget *maincontain, *menubar, *menu;
  PangoFontDescription *font_desc;
  GList *list;
  GtkTextBuffer *buffer;
  guint sig_id = 0;

  /* this is all the info stored in a struct for now */
  widgetinfo *wintextstruc;

  /* setup the main window */
  gtk_init (&argc, &argv);

  if ( (wintextstruc = (widgetinfo *) g_malloc (sizeof (widgetinfo) + 1)) == NULL) {
      exit (-1);
   }

  /* initialize the entire structure to null... */
  memset (wintextstruc, '\0', sizeof (widgetinfo) + 1);

  /* initialize the search direction */
  wintextstruc->searchdir = DOWN;

  /* initialize the match case */
  wintextstruc->matchcase = UNCHECKED;

  stack_init (wintextstruc);

  wintextstruc->mainwindow = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_policy (GTK_WINDOW (wintextstruc->mainwindow), TRUE, TRUE, TRUE);

  /* set up the containers */
  maincontain = gtk_vbox_new (FALSE, 1);
  gtk_widget_show (maincontain);

  /* add the main container to the main window */
  gtk_container_add (GTK_CONTAINER (wintextstruc->mainwindow), maincontain);

  /* some more window things here */
  gtk_widget_set_usize (wintextstruc->mainwindow, 650, 400);
  gtk_window_set_title (GTK_WINDOW (wintextstruc->mainwindow), PROGRAMNAME);

  /* set up the menu using the item factory */
  get_menu_items (wintextstruc->mainwindow, &menubar, wintextstruc);

  /* create our text widget */
  wintextstruc->textwidget = gxtext_new_with_lin_col ();

  gtk_widget_show (GTK_WIDGET (wintextstruc->textwidget));

  /* now set the font */
  font_desc = pango_font_description_from_string (TEXTFONT);
  gtk_widget_modify_font (GTK_WIDGET(GXTEXT (wintextstruc->textwidget)->textarea), font_desc);

  /* now get the right menu to pass 
   * get the list containing the edit menu */
  list = GTK_MENU_BAR (menubar)->menu_shell.children;
  menu = (GtkWidget *)GTK_MENU(GTK_MENU_ITEM (g_list_nth_data (list, EDIT_MENU))->submenu);

  // fixe me to set the font
  //g_list_foreach(list, (GFunc)gtk_widget_modify_font,  font_desc);

  pango_font_description_free (font_desc);
  
  /* add popup menu */
  sig_id = g_signal_lookup("button_press_event", gtk_text_view_get_type ());
  //g_print("Signal = %d \n", sig_id);
  //gtk_signal_emit_stop_by_name((GtkObject*)(GXTEXT(wintextstruc->textwidget)->textarea), "button_press_event");
  //      g_signal_connect_after(GXTEXT(wintextstruc->textwidget)->textarea, "populate_popup",
  //            (GtkSignalFunc)populate_alt_menu, menu);

  /* here is the packing */
  gtk_box_pack_start (GTK_BOX (maincontain), menubar, FALSE, FALSE, 0);
  gtk_box_pack_start (GTK_BOX (maincontain), wintextstruc->textwidget, TRUE, TRUE, 0);

  gtk_widget_show (menubar);
  gtk_widget_show (wintextstruc->mainwindow);


  buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW
			      (GXTEXT (wintextstruc->textwidget)->textarea));

  insertid = g_signal_connect (buffer, "insert_text",
			       (GtkSignalFunc) insert_stack_push,
			       wintextstruc);
  deleteid =
    g_signal_connect (buffer, "delete_range",
		      (GtkSignalFunc) delete_stack_push, wintextstruc);

  g_signal_connect ((GtkObject*)wintextstruc->mainwindow, "delete_event",
		    GTK_SIGNAL_FUNC (destroy_window_event), wintextstruc);

  if (argv[1] != NULL)
    {
      /* here we create a new string for holding 
       * the title .. can you say hack */
      wintextstruc->filename = (gchar *) g_malloc (strlen (argv[1]) + 1);
      if (wintextstruc->filename == NULL)
	{
	  return -1;
	}
      strcpy (wintextstruc->filename, (gchar *) argv[1]);
      gxtext_read_in_ascii_file (GTK_WIDGET (wintextstruc->textwidget),
				 wintextstruc->filename);
    }

  gtk_main ();

  /* not sure if any of this is needed */
  g_free (wintextstruc->filename);

  g_list_free (list);

  g_free (wintextstruc);

  return 0;

}
