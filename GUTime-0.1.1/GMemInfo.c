#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <panel-applet.h>
#include <gtk/gtklabel.h>
#include <gtk/gtkvbox.h>
#include <gtk/gtkentry.h>

/* some #defines here specific to our little applet */
#define PACKAGE "GMemInfo"
#define VERSION "0.0.4"
#define LICENSE "Licensed under the GPL" 
#define COMMENTS "A simple digital memory info applet for the GNOME panel. "
#define FILENAME "/proc/meminfo"
#define UPDATE_TIME 5000
#define ONEBITE 1
#define STATUSLEN 100
#define ERRORFILENOTFOUND "FileNot Found!"
#define TEXTFONT "Sans 10"
#define WIDTH 135
#define HEIGHT 26

const gchar *author[] = {
    "Joseph Acosta (joeja@mindspring.com)",
    NULL
};	

/* here is our function prototype for the funciton to uptdate our
 * little uptime applet */
static gint uptime_update (GtkWidget *);

/*
static void about_menu (AppletWidget *widget, gpointer data) {

	gtk_widget_show(gnome_about_new(PACKAGE,VERSION,LICENSE,
             (const gchar**)author, 
              _(COMMENTS),
              NULL));

}
*/

static gboolean GMemInfo_applet_factory(PanelApplet *applet,
                const char *iid,
                gpointer data) {
                                                                                        
    /* these are necessary for the applets */
    GtkWidget *myvbox;
    GtkWidget *widget;
    GtkWidget *memfree;
    GtkStyle  *style;

    if ( strcmp(iid, "OAFIID:GMemInfo_applet") != 0 ) {
        return FALSE;
    }
   
    /* gtk stuff to create our label and our widget */
    memfree = gtk_label_new("m+c: 0% m: 0% s: 0%");

    style = gtk_widget_get_style(memfree);    
    style->base->red = 0xffff;
    style->base->green = 0xffff;
    style->base->blue = 0xffff;
    gtk_widget_set_style(memfree, style);

    /* a vbox for out label and our entry */
    myvbox = gtk_vbox_new(FALSE,1);
    gtk_box_pack_start (GTK_BOX(myvbox), memfree, FALSE, FALSE, 0);

    gtk_container_add(GTK_CONTAINER(applet), myvbox);

    /* add our update function here */
    gtk_timeout_add(UPDATE_TIME, (GtkFunction)uptime_update, memfree);
    uptime_update(memfree);
	
/*	applet_widget_register_stock_callback(APPLET_WIDGET(applet),
	                                      "about",
	                                      GNOME_STOCK_MENU_ABOUT,
	                                      _("About"),
	                                      about_menu,
	                                      NULL);  
*/	
    //gtk_widget_set_usize(GTK_WIDGET(myvbox), WIDTH, HEIGHT);
    gtk_widget_show_all (GTK_WIDGET (applet));
    return TRUE;
}

PANEL_APPLET_BONOBO_FACTORY ("OAFIID:GMemInfo_applet_Factory",
                             PANEL_TYPE_APPLET,
                             PACKAGE,
                             "0",
                             GMemInfo_applet_factory,
                             NULL);

/* this code was taken in party form procps v1.2.7 and modified for my applet */
static gint uptime_update (GtkWidget *memfree)
{
	FILE *pFile;
	static char buf[255];
	static 	char	tlabel[255];
	float dtotal, dfree, dcache;
	int lablen = 0;

        memset(buf, '\0', sizeof(buf));
        memset(tlabel, '\0', sizeof(tlabel));
	
	if ((pFile=fopen(FILENAME, "r")) == NULL) {
	    gtk_label_set_text(GTK_LABEL(memfree), ERRORFILENOTFOUND);
            return 0;
	} else {
		// get the first line
		memset(buf, '\0', sizeof(buf));
		fgets(buf, sizeof(buf)-1,pFile);
		sscanf(buf,"MemTotal: %f",&dtotal);
		
		// get the second line
		memset(buf, '\0', sizeof(buf));
		fgets(buf, sizeof(buf)-1,pFile);
		sscanf(buf,"MemFree: %f",&dfree);

		memset(buf, '\0', sizeof(buf));
		sprintf(tlabel,"m+c: %d%% ", (int)(100*((dtotal-dfree)/dtotal)));
		lablen = strlen(tlabel);

                // cached memory need to read 2 lines
		memset(buf, '\0', sizeof(buf));
		fgets(buf, sizeof(buf)-1,pFile);
		memset(buf, '\0', sizeof(buf));
		fgets(buf, sizeof(buf)-1,pFile);
		sscanf(buf,"Cached: %f",&dcache);
		
		memset(buf, '\0', sizeof(buf));
		sprintf(tlabel+lablen,"m: %d%% ", (int)(100*((dtotal-dfree-dcache)/dtotal)));
		lablen = strlen(tlabel);

		/* look for SwapTotal next */
		memset(buf, '\0', sizeof(buf));
		fgets(buf, sizeof(buf)-1,pFile);
		while ( ! feof(pFile) ) {
			if ( memcmp(buf, "SwapTotal", 9) == 0 ) {
				sscanf(buf,"SwapTotal: %f",&dtotal);
				break;
			}
			memset(buf, '\0', sizeof(buf));
			fgets(buf, sizeof(buf)-1,pFile);
		}
		
		memset(buf, '\0', sizeof(buf));
		fgets(buf, sizeof(buf)-1,pFile);
		sscanf(buf,"SwapFree: %f",&dfree);

		sprintf(buf,"s: %d%%", (int)(100*((dtotal-dfree)/dtotal)));

		memcpy(tlabel+ lablen, buf, strlen(buf));
		gtk_label_set_text(GTK_LABEL(memfree), tlabel);
		
		fclose(pFile);
	}
        return 1;
}

