#ifndef _GODURA_FILE_H
#define _GODURA_FILE_H

#include "godura.h"
#include "godura_undo_redo.h"
#include "gxmessagebox.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

#define ERRORFILENOTFOUND_W "Could not find or open the file named \"%s\"!"
#define ERRORFILEEXISTS_W "File named \"%s\" already exists. Do you wish to overwrite?"
#define ERRORFILENOTFOUND "Could not find or open the file named !"
#define ERRORFILEEXISTS "File named already exists. Do you wish to overwrite?"

#define OPENMESSAGE "The contents of this file may have changed!\nSelect Yes to save your changes,\nSelect No to to Open a file,\n and Cancel to cancel this operation."
#define MESSAGE "The contents of this file may have changed!\nSelect Yes to save your changes,\nSelect No to exit,\n and Cancel to cancel to cancel this operation."
#define OPENERROR "Error!"
#define NEWMESSAGE "The contents of this file may have changed!\nSelect Yes to save your changes,\nSelect No to create a new message,\n and Cancel to cancel this operation."
#define EXITMESSAGE "The contents of this file may have changed!\nSelect Yes to save your changes,\nSelect No to exit,\n and Cancel to cancel this operation."

#ifdef  __cplusplus
extern "C" {
#endif

/* save as prototype */
void saveas_file (widgetinfo *);

/* save function protoyppe */
void save_file (widgetinfo *);

/* for new files */
void check_new(widgetinfo *);

/* this is the prototype for the destroy event */
void check_change (widgetinfo *);

/* this is for the open function */
void check_open (widgetinfo *);

/* this launches a new window */
void new_window();

/* open a url */
//void Global Software Resources();

#ifdef  __cplusplus
}
#endif

#endif /* _GXPAD_FILE_H */ 
