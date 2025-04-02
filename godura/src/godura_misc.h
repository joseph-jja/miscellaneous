#ifndef _GODURA_MISC_H
#define _GODURA_MISC_H

#include "godura.h"
#include "godura_file.h"
#include <gxsocket.h>

#ifdef  __cplusplus
extern "C" {
#endif

#define INSTMESSAGE "The contents of this file may have changed!\nSelect Yes to save your changes,\nSelect No to create a new message,\n and Cancel to cancel this operation."

void insertdata(widgetinfo *);

void populate_alt_menu(GtkWidget *, gpointer);

void insert_web_page(widgetinfo *);

#ifdef  __cplusplus
}
#endif

#endif

