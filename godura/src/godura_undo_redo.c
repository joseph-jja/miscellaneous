#include "godura_undo_redo.h"
#include <stdlib.h>

static void check_index(widgetinfo *);
static void stack_flush(widgetinfo *, guint, guint);

void delete_stack_push(GtkTextBuffer *buf, GtkTextIter *start, GtkTextIter *end, widgetinfo *winstruct) {

    /* declare the structure that holds
    * the info to insert or delete the data */
    UNDO_STACK *undostk;

    undostk = g_malloc(sizeof(UNDO_STACK));
    if ( undostk == NULL) {
        exit (-9);
    }

    undostk->pos = gtk_text_iter_get_offset(start);
    undostk->datalen = gtk_text_iter_get_offset(end) - undostk->pos;

    undostk->data = gtk_text_buffer_get_text(buf, start, end, TRUE);

    undostk->type ='d';

    check_index(winstruct);

    winstruct->undo_redo = g_list_append(winstruct->undo_redo, undostk);
}

void insert_stack_push(GtkTextBuffer *buf, GtkTextIter *pos, gchar *data, gint len, widgetinfo *winstruct) {

    /* declare the structure that holds
    * the info to insert or delete the data */
    UNDO_STACK *undostk;
   
    undostk = g_malloc(sizeof(UNDO_STACK));
    if ( undostk == NULL) {
        exit (-9);
    }

    undostk->data = (gchar*)g_malloc(len+1);
    if ( undostk->data == NULL) {
        free(undostk);
        exit (-9);
    }
    memset(undostk->data, '\0', len+1);
    memcpy(undostk->data,data, len);
   
    undostk->datalen = len;
    undostk->pos = gtk_text_iter_get_offset(pos);

    undostk->type ='i';

    check_index(winstruct);

    winstruct->undo_redo = g_list_append(winstruct->undo_redo, undostk);
}

void stack_push(GtkTextBuffer *buf, widgetinfo *winstruct) {
    GtkTextIter next, pos;
    GtkTextMark *mark;
    UNDO_STACK *the_stack;
    guint index=0;

    winstruct->undo_redo_idx++;
    index = g_list_length(winstruct->undo_redo);

    if (winstruct->undo_redo_idx >= index) {
        winstruct->undo_redo_idx--;
        return;
    }

    the_stack = (UNDO_STACK*)g_list_nth_data(winstruct->undo_redo, winstruct->undo_redo_idx);
   
    if (the_stack != NULL) {

        mark = gtk_text_buffer_get_insert(buf);

        gtk_text_buffer_get_iter_at_mark(buf, &pos, mark);

        /* this handles the insert stuff now */
        if ( the_stack->type == 'd' ) {

          gtk_text_buffer_get_iter_at_mark(buf, &next, mark);

          gtk_text_iter_set_offset( & pos, the_stack->pos);

          gtk_text_iter_set_offset( & next, the_stack->pos+the_stack->datalen);     

          g_signal_handler_block(buf, deleteid);
          gtk_text_buffer_delete(buf, &pos, &next);
          g_signal_handler_unblock(buf, deleteid);

        } else if ( the_stack->type == 'i' ) {
          gtk_text_iter_set_offset( & pos, the_stack->pos);

          g_signal_handler_block(buf, insertid);
          gtk_text_buffer_insert(buf,&pos, the_stack->data, the_stack->datalen);         
          g_signal_handler_unblock(buf, insertid);
        }
    }
}

void stack_pop(GtkTextBuffer *buf, widgetinfo *winstruct) {

    GtkTextIter next, pos;
    GtkTextMark *mark;
    UNDO_STACK *the_stack;

    if (winstruct->undo_redo_idx <=0) {
        return;
    }

    the_stack = (UNDO_STACK*)g_list_nth_data(winstruct->undo_redo, winstruct->undo_redo_idx);
   
    if (the_stack != NULL) {

        mark = gtk_text_buffer_get_insert(buf);

        gtk_text_buffer_get_iter_at_mark(buf, &pos, mark);

        /* this handles the insert stuff now */
        if ( the_stack->type == 'i' ) {

          gtk_text_buffer_get_iter_at_mark(buf, &next, mark);

          gtk_text_iter_set_offset( & pos, the_stack->pos);

          gtk_text_iter_set_offset( & next, the_stack->pos+the_stack->datalen);     

          g_signal_handler_block(buf, deleteid);
          gtk_text_buffer_delete(buf, &pos, &next);
          g_signal_handler_unblock(buf, deleteid);

        } else if ( the_stack->type == 'd' ) {
          gtk_text_iter_set_offset( & pos, the_stack->pos);

          g_signal_handler_block(buf, insertid);
          gtk_text_buffer_insert(buf,&pos, the_stack->data, the_stack->datalen);         
          g_signal_handler_unblock(buf, insertid);
        }

        winstruct->undo_redo_idx--;
    }
}

static void stack_flush(widgetinfo *winstruct, guint start, guint end) {
    guint i;
    UNDO_STACK *the_stack;

    for (i=start; i<end; i++) {
        the_stack = (UNDO_STACK*)g_list_nth_data(winstruct->undo_redo, i);   
        if (the_stack != NULL) {
            winstruct->undo_redo = g_list_remove(winstruct->undo_redo, the_stack);
            g_free(the_stack->data);
            g_free(the_stack);
        }
    }
}

void stack_reset(widgetinfo *winstruct) {
    guint index=0;

    index = g_list_length(winstruct->undo_redo);

    /* safe keeping we delete all the elements */
    stack_flush(winstruct, 0, index);

    if ( winstruct->undo_redo_idx > 0 ) {
        winstruct->undo_redo_idx = 0;
        g_list_free(winstruct->undo_redo);
    }

}

void stack_init(widgetinfo *winstruct) {
   
    winstruct->undo_redo_idx = 0;
    winstruct->undo_redo = g_list_alloc();
}

static void check_index(widgetinfo *winstruct) {

    guint index=0;

    index = g_list_length(winstruct->undo_redo);

    if (index-1 > winstruct->undo_redo_idx) {

      stack_flush(winstruct, winstruct->undo_redo_idx, index);

    }       
    winstruct->undo_redo_idx++;
}
