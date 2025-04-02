#include "godura_misc.h"

static char *filetemplate = 
    "%define name\n%define version\n%define release\n%define packager\n\nSummary:\nName: %{name}\nVersion: %{version}\nRelease: %{release}\nCopyright:\nGroup:\nSource: %{name}-%{version}.tar.gz\nSource1:\nPatch:\nBuildroot: /tmp/%{name}-build\nURL:\n\n%description\n\n%prep\n\n%setup\n\n%patch\n\n%build\n\n%install\n\n%clean\n\n%files\n\n%doc\n\n%changelog\n";

void insertdata(widgetinfo *textwidget) {

       GtkTextIter start;
       Gxtext *gxtext;
       GtkTextBuffer *buffer;

       gxtext = (Gxtext*)textwidget->textwidget;

       buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(gxtext->textarea));

       check_new(textwidget);

       gtk_text_buffer_get_start_iter(buffer, &start);
	           
       gtk_text_buffer_place_cursor (buffer, &start);

       gtk_text_buffer_insert(buffer,
		        &start, filetemplate, strlen(filetemplate));

       gtk_text_buffer_set_modified(GTK_TEXT_BUFFER(buffer), FALSE);
   
       gtk_label_set_label(GTK_LABEL(GXTEXT(gxtext)->modified), "           ");     

}

void populate_alt_menu(GtkWidget *widget, gpointer data) {

//    GTK_TEXT_VIEW(widget)->popup_menu = GTK_MENU(data);

}

void insert_web_page(widgetinfo *textwidget) { 

    Gxsocket *socket;
   
    socket = (Gxsocket *)gxsocket_new();
    socket->textBuffer = (GtkWidget*)gtk_text_view_get_buffer(GTK_TEXT_VIEW(GXTEXT(textwidget->textwidget)->textarea));

    gtk_signal_connect_object(GTK_OBJECT(socket->button[0]),
                        "clicked",(GtkSignalFunc)gxsocket_load_URL,
                        GTK_OBJECT(socket));

    gtk_signal_connect_object(GTK_OBJECT(socket->button[0]),
                        "clicked",(GtkSignalFunc)gtk_widget_destroy,
                        GTK_OBJECT(socket));

    gtk_signal_connect_object(GTK_OBJECT(socket->button[1]),
                        "clicked",(GtkSignalFunc)gtk_widget_destroy,
                        GTK_OBJECT(socket));

    gtk_widget_show(GTK_WIDGET(socket));

}




