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

#ifndef GTK_MVC_ADAPTOR_H
#define GTK_MVC_ADAPTOR_H

#include <gtk/gtk.h>
#include "gtk-mvc-view.h"

G_BEGIN_DECLS

typedef struct _GtkMvcAdaptor        GtkMvcAdaptor;
typedef struct _GtkMvcAdaptorClass   GtkMvcAdaptorClass;
typedef struct _GtkMvcAdaptorPrivate GtkMvcAdaptorPrivate;

#define GTK_MVC_TYPE_ADAPTOR         (gtk_mvc_adaptor_get_type ())
#define GTK_MVC_ADAPTOR(i)           (G_TYPE_CHECK_INSTANCE_CAST ((i), GTK_MVC_TYPE_ADAPTOR, GtkMvcAdaptor))
#define GTK_MVC_ADAPTOR_CLASS(c)     (G_TYPE_CHECK_CLASS_CAST ((c), GTK_MVC_TYPE_ADAPTOR, GtkMvcAdaptorClass))
#define GTK_MVC_IS_ADAPTOR(i)        (G_TYPE_CHECK_INSTANCE_TYPE ((i), GTK_MVC_TYPE_ADAPTOR))
#define GTK_MVC_IS_ADAPTOR_CLASS(c)  (G_TYPE_CHECK_CLASS_TYPE ((c), GTK_MVC_TYPE_ADAPTOR))
#define GTK_MVC_ADAPTOR_GET_CLASS(i) (G_TYPE_INSTANCE_GET_CLASS ((i), GTK_MVC_TYPE_ADAPTOR, GtkMvcAdaptorClass))

GType      gtk_mvc_adaptor_get_type (void);
GtkWidget* gtk_mvc_adaptor_new      (GtkMvcView* view);

struct _GtkMvcAdaptor
{
  GtkLabel              base_instance;
  GtkMvcAdaptorPrivate* _private;
};

struct _GtkMvcAdaptorClass
{
  GtkLabelClass         base_class;
};

G_END_DECLS

#endif /* !GTK_MVC_ADAPTOR_H */

/* vim:set et sw=2 cino=t0,f0,(0,{s,>2s,n-1s,^-1s,e2s: */
