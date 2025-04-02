#ifndef _GODURA_HELP_H
#define _GODURA_HELP_H

#include "godura.h"

#ifdef  __cplusplus
extern "C" {
#endif

#define ABOUTWIN "godura by Joseph Acosta.\nThis program is an enhanced implementation of another editor of mine called Tk NotePad.\nIt is written in using GTK+ and GNOME instead of Tcl/Tk.\nIt is designed especially for specfiles, but will have many other added features.\nEnjoy!"

#define HELPWIN "Help me!"

void help_about();

void help_help();

void help_spec();

#ifdef  __cplusplus
}
#endif
#endif

