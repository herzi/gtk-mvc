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

#ifndef GTK_MVC_DEFAULT_VIEW_H
#define GTK_MVC_DEFAULT_VIEW_H

#include "gtk-mvc-view.h"

G_BEGIN_DECLS

typedef struct _GtkMvcDefaultView        GtkMvcDefaultView;
typedef struct _GtkMvcDefaultViewClass   GtkMvcDefaultViewClass;
typedef struct _GtkMvcDefaultViewPrivate GtkMvcDefaultViewPrivate;

#define GTK_MVC_TYPE_DEFAULT_VIEW         (gtk_mvc_default_view_get_type ())
#define GTK_MVC_DEFAULT_VIEW(i)           (G_TYPE_CHECK_INSTANCE_CAST ((i), GTK_MVC_TYPE_DEFAULT_VIEW, GtkMvcDefaultView))
#define GTK_MVC_DEFAULT_VIEW_CLASS(c)     (G_TYPE_CHECK_CLASS_CAST ((c), GTK_MVC_TYPE_DEFAULT_VIEW, GtkMvcDefaultViewClass))
#define GTK_MVC_IS_DEFAULT_VIEW(i)        (G_TYPE_CHECK_INSTANCE_TYPE ((i), GTK_MVC_TYPE_DEFAULT_VIEW))
#define GTK_MVC_IS_DEFAULT_VIEW_CLASS(c)  (G_TYPE_CHECK_CLASS_CAST ((c), GTK_MVC_TYPE_DEFAULT_VIEW))
#define GTK_MVC_DEFAULT_VIEW_GET_CLASS(i) (G_TYPE_INSTANCE_GET_CLASS ((i), GTK_MVC_TYPE_DEFAULT_VIEW, GtkMvcDefaultViewClass))

GType       gtk_mvc_default_view_get_type (void);
GtkMvcView* gtk_mvc_default_view_new      (void);

struct _GtkMvcDefaultView
{
  GInitiallyUnowned         base_instance;
  GtkMvcDefaultViewPrivate* _private;
};

struct _GtkMvcDefaultViewClass
{
  GInitiallyUnownedClass    base_class;
};

G_END_DECLS

#endif /* !GTK_MVC_DEFAULT_VIEW_H */

/* vim:set et sw=2 cino=t0,f0,(0,{s,>2s,n-1s,^-1s,e2s: */
