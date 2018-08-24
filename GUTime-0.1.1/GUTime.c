#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <panel-applet.h>
#include <gtk/gtklabel.h>
#include <gtk/gtkvbox.h>	

/* some #defines here specific to our little applet */
#define PACKAGE "GUTime"
#define VERSION "0.0.4"
#define LICENSE "Licensed under the GPL" 
#define COMMENTS "A simple uptime applet for the GNOME panel. "
#define FILENAME "/proc/uptime"
#define UPDATE_TIME 30000
#define ONEBITE 1
#define STATUSLEN 100
#define ERRORFILENOTFOUND "FileNot Found!"
#define TEXTFONT "-adobe-courier-medium-r-normal-*-*-120-*-*-m-*-*-*"
#define WIDTH 80
#define HEIGHT 28

static gint uptime_update (GtkWidget *widget);

const gchar *author[] = {
    "Joseph Acosta (joeja@mindspring.com)",
    NULL
};	

static gboolean GUTime_applet_factory(PanelApplet *applet, 
		const char *iid, 
		gpointer data) {
	
	GtkWidget *label;
    	GtkWidget *myvbox;

        if ( strcmp(iid, "OAFIID:GUTime_applet") != 0 ) {
		return FALSE;
	}

        label = gtk_label_new(" ");

	/* a vbox for out label and our entry */
    	myvbox = gtk_vbox_new(FALSE,1);

    	/* again some more gtk stuff for a label and widget */
    	gtk_box_pack_start (GTK_BOX(myvbox), label, FALSE, FALSE, 0);
	//gtk_widget_set_usize(GTK_WIDGET(myvbox), WIDTH, HEIGHT);

    	gtk_container_add (GTK_CONTAINER(applet), myvbox);

	gtk_widget_show_all (GTK_WIDGET (applet));

	uptime_update (label); 

	gtk_timeout_add(UPDATE_TIME, (GtkFunction)uptime_update, label);

	return TRUE;
}

PANEL_APPLET_BONOBO_FACTORY ("OAFIID:GUTime_applet_Factory",
                             PANEL_TYPE_APPLET,
                             PACKAGE,
                             "0",
			     GUTime_applet_factory,
                             NULL);
			     
/* this code was taken in part form procps v1.2.7 and modified for my applet */
static gint uptime_update (GtkWidget *widget)
{
	FILE 		*pFile;
	static char 	buf[128];
	char 		buffer[STATUSLEN+1]; 
	float 		uptime_secs, 
			idle_secs;
	int 		upminutes, 
			uphours, 
			updays,
			uptime_sec_i;
		
 	sprintf(buf, "%s", " ");
	if ((pFile=fopen(FILENAME, "r")) == NULL) {
		gtk_label_set_text(GTK_LABEL(widget), ERRORFILENOTFOUND);
                return 0;
	} else {
		/* initialize data */
		memset(buf, '\0', sizeof(buf));
		memset(buffer, '\0', sizeof(buffer));

		/* get the data in */
		fread(buffer, 1, STATUSLEN, pFile);
		sscanf(buffer," %f %f ",&uptime_secs, &idle_secs);
		fclose(pFile);

	        /* convert uptime_secs to int */
	        uptime_sec_i = (int)uptime_secs;

	   	/* get days min, hrs */
		updays = uptime_sec_i / (60*60*24);
		upminutes = uptime_sec_i/ 60;
  		uphours = upminutes / 60;

		if ( updays < 0 ) {
			updays = 0;
		}
		if ( uphours < 0 ) {
			uphours = 0;
		} else if ( uphours > 24 ) {
			uphours = uphours % 24;
		}
		if ( upminutes < 0 ) {
			upminutes = 0;
		} else if ( upminutes > 60 ) {
			upminutes = upminutes % 60;
		}

		if ( updays > 0 ) {
			sprintf(buf, "%d d %d h %d m", updays, uphours, upminutes);
		} else {
			sprintf(buf, "%d h %d m", uphours, upminutes);
		}
		
		gtk_label_set_text(GTK_LABEL(widget), buf);
	}
        return 1;
}


