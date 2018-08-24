#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include "gxsocket.h"

#include <gtk/gtktextiter.h>
#include <gtk/gtktextmark.h>

/* local function declarations */
static void gxsocket_class_init (GxsocketClass *);
static void gxsocket_init (Gxsocket *);

/* socket specific functions */
static int initTCPSocket(char *url, int port);
static void closeTCPSocket(int sock);

/* http specific functions */
static int writeHTTPHeader(int handle, char *data);
static void sendHTTPHeaders(int handle, gchar *server, int port, gchar *url);
static int getReturnStatusCode(gchar *data);
static int isChunked(gchar *data);
static char *httpReadline(int handle);
static char *httpReadchunk(int handle, int csize);

// misc
static int hexToDecimal(char *hex) ; 
static void writeToTextBuffer(GtkTextBuffer *textBuffer, GtkTextIter iter, GtkTextMark *mark, gchar *data, int dlen);

static char *CRLF = "\r\n";
static char *SEPARATOR_CRLF = "\r\n\r\n";

static int debug_sockets = FALSE;

/* standard gtk widget function take from the documentation */
GType gxsocket_get_type () {

    static GType xxx_type = 0;
    if (!xxx_type) {
        static const GTypeInfo xxx_info =
        { 
            sizeof(GxsocketClass),
            NULL,
            NULL,
            (GClassInitFunc)gxsocket_class_init,
            NULL,
            NULL,
            sizeof(Gxsocket),
            0,
            (GInstanceInitFunc) gxsocket_init,
        };
        xxx_type = g_type_register_static (GTK_TYPE_WINDOW, "Gxsocket", &xxx_info, 0);
    }
    return xxx_type;
}

static void gxsocket_class_init (GxsocketClass *class) {
    GtkObjectClass *object_class;
   
    object_class = (GtkObjectClass*) class;
   
    class->gxsocket = NULL;
}

static void gxsocket_init (Gxsocket *xxx) {

    xxx->proto_label = 0;
    xxx->proto_entry = 0;
    xxx->server_label = 0;
    xxx->server_entry = 0;
    xxx->port_label = 0;
    xxx->port_entry = 0;
    xxx->url_label = 0;
    xxx->url_entry = 0;
    xxx->button[0] = 0;
    xxx->button[1] = 0;
    xxx->textBuffer = 0;
}

/* here is the meat of the widget */
/* this is the base constructor for this klass */
GtkWidget* gxsocket_new() {

    Gxsocket *message;
    GtkWidget *table;

    message = gtk_type_new(gxsocket_get_type());

    /* rows, cols, homogenous */
    table = (GtkWidget*)gtk_table_new(4, 8, FALSE);

    gtk_container_add (GTK_CONTAINER(message), table);

    /* this is the protocol */
    message->proto_label = gtk_label_new("Protocol");
    message->proto_entry = gtk_entry_new_with_max_length(5);
    gtk_entry_set_width_chars(GTK_ENTRY(message->proto_entry), 5);
    gtk_entry_set_text(GTK_ENTRY(message->proto_entry), "http");   
    gtk_entry_set_editable(GTK_ENTRY(message->proto_entry), FALSE);   

    /* this is the server */
    message->server_label = gtk_label_new("Server");
    message->server_entry = gtk_entry_new_with_max_length(40);
    gtk_entry_set_width_chars(GTK_ENTRY(message->server_entry), 25);

    /* this is the port */
    message->port_label = gtk_label_new("Port");
    message->port_entry = gtk_entry_new_with_max_length(6);
    gtk_entry_set_width_chars(GTK_ENTRY(message->port_entry), 6);
    gtk_entry_set_text(GTK_ENTRY(message->port_entry), "80");   

    /* this is the url */
    message->url_label = gtk_label_new("URL");
    message->url_entry = gtk_entry_new_with_max_length(100);
    gtk_entry_set_width_chars(GTK_ENTRY(message->url_entry), 40);

    gtk_table_attach_defaults(GTK_TABLE(table),message->proto_label,0,1,0,1);
    gtk_table_attach_defaults(GTK_TABLE(table),message->proto_entry,1,2,0,1);
    gtk_table_attach_defaults(GTK_TABLE(table),message->server_label,2,3,0,1);
    gtk_table_attach_defaults(GTK_TABLE(table),message->server_entry,3,5,0,1);
    gtk_table_attach_defaults(GTK_TABLE(table),message->port_label,5,6,0,1);
    gtk_table_attach_defaults(GTK_TABLE(table),message->port_entry,6,7,0,1);
    gtk_table_attach_defaults(GTK_TABLE(table),message->url_label,0,1,1,2);
    gtk_table_attach_defaults(GTK_TABLE(table),message->url_entry,1,7,1,2);

    gtk_widget_show(message->proto_label);
    gtk_widget_show(message->proto_entry);
    gtk_widget_show(message->server_label);
    gtk_widget_show(message->server_entry);
    gtk_widget_show(message->port_label);
    gtk_widget_show(message->port_entry);
    gtk_widget_show(message->url_label);
    gtk_widget_show(message->url_entry);

    message->button[0] = (GtkWidget*)gtk_button_new_with_label("Open");
    gtk_table_attach_defaults(GTK_TABLE(table),message->button[0],5,6,2,3);
    gtk_widget_show(message->button[0]);

    message->button[1] = gtk_button_new_with_label("Cancel");
    gtk_table_attach_defaults(GTK_TABLE(table),message->button[1],6,7,2,3);
    gtk_widget_show(message->button[1]);

    gtk_widget_show(table);

    gtk_window_set_position(GTK_WINDOW(message),GTK_WIN_POS_CENTER);
    gtk_window_set_modal(GTK_WINDOW(message),TRUE);
    gtk_window_set_policy(GTK_WINDOW(message),FALSE, FALSE, FALSE);

    return GTK_WIDGET (message);
}

/////////////////////////////////////////////////////////////////////////////////////////////
// socket specific functions start
/////////////////////////////////////////////////////////////////////////////////////////////
// given a server and port this will make a tcp connection
static int initTCPSocket(gchar *servername, int port) {

    int sock;
    struct sockaddr_in host;
    struct hostent *server;
    int len = 0;

    /* create a tcp socket */
    sock = socket(AF_INET, SOCK_STREAM, 0);
        if ( sock < 0 ) {
            perror("ERROR: Could not open socket!\n");
        }
    if ( debug_sockets ) { g_printf("Got socket  %d.\n", sock); }

        server = gethostbyname(servername);
        if ( server == NULL ) {
            perror("ERROR: Could not get host or host not found!\n");
        }
    if ( debug_sockets ) { g_printf("Got server  %s.\n", servername); }
     
        bzero((char *) &host, sizeof(host));
        host.sin_family = AF_INET;
        bcopy((char *)server->h_addr, (char *)&host.sin_addr.s_addr, server->h_length);
        host.sin_port = htons(port);

    if ( debug_sockets ) { g_printf("About to connect.\n"); }
        // now connect
        if ( connect(sock, (struct sockaddr *)&host, sizeof(host)) < 0 ) {
            g_printf("ERROR: Could not connect to remote host (%s) @ port (%d)!\n", server, port);
            perror("ERROR: Could not connect to remote host @ port!\n");
        }

        return sock;
}

// given a socket handle this will close the tcp connection
static void closeTCPSocket(int sock) {
    close(sock);
}
/////////////////////////////////////////////////////////////////////////////////////////////
// socket specific functions end
/////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////
// http specific functions start
/////////////////////////////////////////////////////////////////////////////////////////////
// main entry point to load a url into a text buffer
void gxsocket_load_URL(Gxsocket *gxsocket) {

        gchar *server, *port, *url, *proto;
        gchar *data;
        int rc = 0, status = 0;
        GtkTextBuffer *textBuffer;
        GtkTextIter start, iter, end;
        GtkTextMark *mark;
        int chunkedData = FALSE;
        int chunkReadLen = 0;
        int includeHeaders = TRUE;

        server = (gchar*)gtk_entry_get_text(GTK_ENTRY(gxsocket->server_entry));
        port = (gchar*)gtk_entry_get_text(GTK_ENTRY(gxsocket->port_entry));
        url = (gchar*)gtk_entry_get_text(GTK_ENTRY(gxsocket->url_entry));

        textBuffer = (GtkTextBuffer*)gxsocket->textBuffer;

        if ( server == NULL || port == NULL ) {
            perror("Server or port not specified.\n");
            return;
        }

        if ( url == NULL ) {
            perror("URL not specified.\n");
            return;
        }

        if ( strlen(url) > 2048 ) {
            perror("URL length is too long.\n");
            return;
        }

        int handle = initTCPSocket((char*)server, atoi(port));
        if ( debug_sockets ) { g_printf("Connection server %s at port %s with url %si.\n", server, port, url); }

        if ( handle <= 0 ) {
            perror("Could not connect to host %s at port %d.\n");
        } else {
            // set the insertion cursor
            gtk_text_buffer_get_start_iter(textBuffer, &start);
            gtk_text_buffer_place_cursor (textBuffer, &start);

            // write to server
            sendHTTPHeaders(handle, server, atoi(port), url);

            // read first line from server and check the http status in the result
            data =  httpReadline(handle);
            status = getReturnStatusCode(data);
            if ( status == -1 || status < 200 || status >= 300 ) {
                // need to get another url :( .. replace with switch?
              g_printf("Status code = %d\n", status);
            }

            // process headers
            while ( data != NULL && memcmp(data, CRLF, 2) != 0 ) {
                if ( debug_sockets ) { g_printf("Headers = %d  %s", strlen(data), data); }
                if ( ! chunkedData ) { chunkedData = isChunked(data); }
                if ( includeHeaders ) {
                    writeToTextBuffer(textBuffer, iter, mark, data, strlen(data) );
                }
                data = NULL;
                free(data);
                data = httpReadline(handle);
            }

            // if we want to include the headers in the result then we add in the LF too 
            if (includeHeaders ) { 
                writeToTextBuffer(textBuffer, iter, mark, data, strlen(data) );
            }

            // read the first line of data, from the headers we know it is or is not chunked
            data = httpReadline(handle);
            if ( chunkedData && data != NULL ) {
                chunkReadLen = hexToDecimal(data);
                if ( debug_sockets ) { g_printf("Chunked data %d.\n",  hexToDecimal(data)); }
                free(data);
                data = httpReadchunk(handle, chunkReadLen);  // read the next chunk
                if ( debug_sockets ) { g_printf("Chunked data %d and got %d.\n",  chunkReadLen, strlen(data)); }
            }

            // process body
            while ( data != NULL ) {
                if ( debug_sockets ) { g_printf("Got characters %s.\n", data); }
                // insert text, free data, read next line
                writeToTextBuffer(textBuffer, iter, mark,  data, strlen(data) );
                free(data);
                data = httpReadline(handle);
                // if we are chunking data filter out the CRLF from here
                if ( chunkedData && data != NULL ) {
                    // the filter, if all we have is CRLF then we need the next line which tells us the chunk size
                    if ( strlen(data) == 2 && memcmp(data, CRLF, 2) == 0 ) {
                        free(data);
                        data = httpReadline(handle);
                    } 
                    chunkReadLen = hexToDecimal(data);
                    if ( debug_sockets ) { g_printf("What do we have? %d and got %d %s\n",  chunkReadLen, strlen(data), data);  }
                    if ( chunkReadLen > 0 ) {
                        free(data);
                        data = httpReadchunk(handle, chunkReadLen);  // read the next chunk
                    } else {
                        // during chunking the only time we have 0 is at the end
                        free(data);
                        break;
                    }
                }
            }
            closeTCPSocket(handle);
        }
}

// try to read in until we get the chunk data size specified
static char *httpReadchunk(int handle, int csize) {

    char *result;
    int rc = 0, trc =0;

    result = malloc(csize+1);
    if ( result == NULL ) {
        return NULL;
    }
    memset(result, '\0', csize+1);  
    rc = read(handle, result, csize);
    if ( rc == 0 ) { 
        perror("ERROR: Could not read data!");
    }
    while ( rc < csize || rc <= 0 ) {
       rc += read(handle, result+rc, csize-rc);
    }
    return result;
}

// read in a line of data one character at a time
static char *httpReadline(int handle) {

    int i =0, csize = 2048, multiplier = 1, rc;
    char *result;
    char *altdata;

    result = malloc(csize+1);
    if ( result == NULL ) {
        return NULL;
    }
    memset(result, '\0', csize+1);
    // try to read a line
    while ( read(handle, &result[i], 1) > 0 ) {
        if ( result[i] == '\n' ) {
            if ( ( i+1 ) < ( csize *multiplier ) ) {
                result[i+1] = '\0'; // should be null but just in case
            }
            // CFLF we only want the LF
            if ( i > 2 && result[i-1] == '\r' ) {
                result[i] = '\0';
                result[i-1] = '\n';
            }
            break;
        }
        if ( i >= ( csize *multiplier ) ) {
            // same as realloc
            altdata = strdup(result);
            if ( altdata == NULL ) { perror("ERROR: Could not get memory."); }
            free(result);
            multiplier +=1;
            result = malloc(csize * multiplier + 1);
            if ( result == NULL ) { perror("ERROR: Could not get memory."); }
            memset(result, '\0', csize*multiplier+1);
            memcpy(result, altdata, strlen(altdata));
        } 
        i+=1;
    } 
    if ( strlen(result) == 0 ) {
        return NULL;
    }
    return result;
}

// look for http header that tells us it is chunked data
static int isChunked(gchar *data) {

  if ( memcmp(data, "Transfer-Encoding: chunked", strlen("Transfer-Encoding: chunked") ) == 0 ) {
      return TRUE;
  }
  return FALSE;
}

// get the http status code from the http header
static int getReturnStatusCode(gchar *data) {

    gchar status[5]; // code of 100 to 500's only 3 chararcters really
    int i=0, dlen =0;
    int start = -1;

    memset(status, '\0', sizeof(status));

    if ( data == NULL ) { return -1; }
    if ( memcmp(data, "HTTP", 4) != 0 ) { return -1; }
    dlen = strlen(data);
    while ( i < dlen ) {
      if ( data[i] == ' ' && start >0 ){
          memcpy(status, data+start+1, i-start);
          if ( debug_sockets ) { g_printf("Got %s\n", status); }
          break;
      }
      if ( data[i] == ' ' && start == -1 ){
            start = i;
      }
      i+=1;
    }
    if ( status != NULL ) {
        return atoi(status);
    }

    return -1;
}

// this sends all the headers
// this makes it simplier to add more headers
static void sendHTTPHeaders(int handle, gchar *server, int port, gchar *url) {

    gchar buffer[2048 + 20];  // max size of a url

    // write to server
    memset(buffer, '\0', sizeof(buffer));

    sprintf(buffer, "GET %s HTTP/1.1\n", url);
    writeHTTPHeader(handle, buffer);

    if ( port == 80 || port == 443 ) {
        sprintf(buffer, "Host: %s\n", server);
    } else {
        sprintf(buffer, "Host: %s:port\n", server, port);
    }
    writeHTTPHeader(handle, buffer);

    sprintf(buffer, "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\n");
    writeHTTPHeader(handle, buffer);

    sprintf(buffer, "Accept-Charset: ISO-8859-1,utf-8;q=0.7,*;q=0.7\n");
    writeHTTPHeader(handle, buffer);

    writeHTTPHeader(handle, "\n");
}

// requires null terminated string
static int writeHTTPHeader(int handle, char *data) {

    int rc = 0;

    if ( strlen(data) > 0 ) {
        rc =  write(handle, data, strlen(data));
        if ( debug_sockets ) { g_printf("Wrote characters %d.\n", rc); }
        if ( rc <= 0 ) {
            perror("ERROR: Zero bytes written to socket!");
        }
    }
    return rc;

}

/////////////////////////////////////////////////////////////////////////////////////////////
// http specific functions end
/////////////////////////////////////////////////////////////////////////////////////////////

// conver the hex code to decimal when you have chunked encoding
static int hexToDecimal(char *hex) {

    int hlen = 0, i = 0, result = 0, multiplier = 1;
    char buf[2];

    if ( hex == NULL ) { return result; }

    hlen = strlen(hex);
    i = hlen -1;
    if ( hex[i] == '\n' ) { i -=1; }
    while ( i >= 0 ) { 
        if ( hex[i] == 'a' ) {
            result += ( multiplier * 10);
        } else if ( hex[i] == 'b' ) {
            result += ( multiplier * 11);
        } else if ( hex[i] == 'c' ) {
            result += ( multiplier * 12);
        } else if ( hex[i] == 'd' ) {
            result += ( multiplier * 13);
        } else if ( hex[i] == 'e' ) {
            result += ( multiplier * 14);
        } else if ( hex[i] == 'f' ) {
            result += ( multiplier * 15);
        } else { 
           sprintf(buf, "%c", hex[i]);
           result += ( multiplier * atoi(buf) );
        }
        multiplier *= 16;
        i-=1;
    }
    return result;
}

// because we do this in a few places we add these 3 lines here for shortening of code elsewhere
static void writeToTextBuffer(GtkTextBuffer *textBuffer, GtkTextIter iter, GtkTextMark *mark, gchar *data, int dlen) {

    mark = gtk_text_buffer_get_insert(textBuffer);
    gtk_text_buffer_get_iter_at_mark(textBuffer, &iter, mark);
    gtk_text_buffer_insert(textBuffer, &iter, data, dlen );
}
