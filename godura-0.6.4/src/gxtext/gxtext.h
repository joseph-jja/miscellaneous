
/* This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */
#ifndef __GXTEXT_H__
#define __GXTEXT_H__


#include <gdk/gdk.h>
#include <gtk/gtkvbox.h>
#include <gtk/gtktextbuffer.h>
#include <gtk/gtktextview.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define GXTEXT(obj)          GTK_CHECK_CAST (obj, gxtext_get_type (), Gxtext)
#define GXTEXT_CLASS(klass)  GTK_CHECK_CLASS_CAST (klass, gxtext_get_type (), GxtextClass)
#define IS_GXTEXT(obj)       GTK_CHECK_TYPE (obj, gxtext_get_type ())


typedef struct _Gxtext       Gxtext;
typedef struct _GxtextClass  GxtextClass;

struct _Gxtext
{
  GtkVBox vbox;

  GtkWidget *scrolled_win;

  GtkWidget *textvbox;
  GtkWidget *textarea;
  
  GtkWidget *linenumber;
  GtkWidget *modified;

};

struct _GxtextClass
{
  GtkVBoxClass parent_class;

  void (* gxtext) (Gxtext *xxx);
};

GtkType        gxtext_get_type        (void);
GtkWidget*     gxtext_new             (void);

/* creates a new gxtext 
 * widget with line and column numbering*/
GtkWidget*      gxtext_new_with_lin_col(void); 

/* read in an ascii fie into the text */
/* return 0 on failure */
gint gxtext_read_in_ascii_file(GtkWidget *, gchar *);

/* write out an ascii fie from the text */
/* return 0 on failure */
gint gxtext_write_out_ascii_file (GtkWidget *, gchar *);

/* set the gxtext widget as new */
/* delete all the text and set as unmodified */
void gxtext_set_as_new(GtkWidget *);

/* select all the text in the widget */
void gxtext_select_all(GtkWidget *);

/* cut the selection from text in the widget */
void gxtext_cut_text(GtkWidget *);

/* copy the selection from text in the widget */
void gxtext_copy_text(GtkWidget *);

/* paste to text in the widget */
void gxtext_paste_text(GtkWidget *);

/* delete the selection from text in the widget */
void gxtext_delete_text(GtkWidget *);

/* destroy the text widget */
void gxtext_destroy(GtkWidget *);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __GXTEXT_H__ */

