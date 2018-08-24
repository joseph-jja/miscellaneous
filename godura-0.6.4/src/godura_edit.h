#ifndef _GODURA_EDIT_H
#define _GODURA_EDIT_H

#include "godura.h"
#include "godura_undo_redo.h"

#ifdef  __cplusplus
extern "C" {
#endif

void undo_last(widgetinfo *, gpointer);

void redo_last(widgetinfo *, gpointer);

/* cut, copy, paste, and edit menu functions 
 * these are wrapper functions for the native 
 * gtk cut, copy, and paste functions */

void paste_text(widgetinfo *, gpointer);

void cut_text(widgetinfo *, gpointer);

void copy_text(widgetinfo *, gpointer);

void delete_text(widgetinfo *, gpointer); 

void select_text(widgetinfo *, gpointer );

void get_current_time(widgetinfo *);

void wrap_text(widgetinfo *);

#ifdef  __cplusplus
}
#endif

#endif /* _GXPAD_EDIT_H */
