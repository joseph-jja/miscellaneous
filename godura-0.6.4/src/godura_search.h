#ifndef _GODURA_SEARCH_H
#define _GODURA_SEARCH_H

#include "godura.h"
#include <gxsearch.h>

#ifdef  __cplusplus
extern "C" {
#endif

void find_text(widgetinfo *, gpointer);

void find_next_text(widgetinfo *, gpointer); 

void replace_text(widgetinfo *, gpointer);

#ifdef  __cplusplus
}
#endif

#endif /* _GXPAD_SEARCH_H */
