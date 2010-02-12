/* This file is part of herzi's playground
 *
 * Copyright (C) 2010  Sven Herzberg
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation; either version 2.1 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
 * USA
 */

#ifndef GTK_MVC_SCROLL_VIEW_H
#define GTK_MVC_SCROLL_VIEW_H

#include <gtk/gtk.h>
#include "gtk-mvc-view.h"

G_BEGIN_DECLS

typedef struct _GtkMvcScrollView        GtkMvcScrollView;
typedef struct _GtkMvcScrollViewClass   GtkMvcScrollViewClass;
typedef struct _GtkMvcScrollViewPrivate GtkMvcScrollViewPrivate;

#define GTK_MVC_TYPE_SCROLL_VIEW         (gtk_scroll_view_get_type ())
#define GTK_MVC_SCROLL_VIEW(i)           (G_TYPE_CHECK_INSTANCE_CAST ((i), GTK_SCROLL_TYPE_VIEW, GtkScrollView))
#define GTK_MVC_SCROLL_VIEW_CLASS(c)     (G_TYPE_CHECK_CLASS_CAST ((c), GTK_SCROLL_TYPE_VIEW, GtkScrollViewClass))
#define GTK_MVC_IS_SCROLL_VIEW(i)        (G_TYPE_CHECK_INSTANCE_TYPE ((i), GTK_SCROLL_TYPE_VIEW))
#define GTK_MVC_IS_SCROLL_VIEW_CLASS(c)  (G_TYPE_CHECK_CLASS_TYPE ((c), GTK_SCROLL_TYPE_VIEW))
#define GTK_MVC_SCROLL_VIEW_GET_CLASS(i) (G_TYPE_INSTANCE_GET_CLASS ((i), GTK_SCROLL_TYPE_VIEW, GtkScrollViewClass))

GType       gtk_mvc_scroll_view_get_type (void);
GtkMvcView* gtk_mvc_scroll_view_new      (void);

struct _GtkMvcScrollView
{
  GtkLabel                 base_instance;
  GtkMvcScrollViewPrivate* _private;
};

struct _GtkMvcScrollViewClass
{
  GtkLabelClass            base_class;
};

G_END_DECLS

#endif /* !GTK_MVC_SCROLL_VIEW_H */

/* vim:set et sw=2 cino=t0,f0,(0,{s,>2s,n-1s,^-1s,e2s: */
