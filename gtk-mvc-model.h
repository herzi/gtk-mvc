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

#ifndef GTK_MVC_MODEL_H
#define GTK_MVC_MODEL_H

#include <glib-object.h>

G_BEGIN_DECLS

typedef struct _GtkMvcModel      GtkMvcModel;
typedef struct _GtkMvcModelIface GtkMvcModelIface;

#define GTK_MVC_TYPE_MODEL         (gtk_mvc_model_get_type ())
#define GTK_MVC_MODEL(i)           (G_TYPE_CHECK_INSTANCE_CAST ((i), GTK_MVC_TYPE_MODEL, GtkMvcModel))
#define GTK_MVC_IS_MODEL(i)        (G_TYPE_CHECK_INSTANCE_TYPE ((i), GTK_MVC_TYPE_MODEL))
#define GTK_MVC_MODEL_GET_IFACE(i) (G_TYPE_INSTANCE_GET_INTERFACE ((i), GTK_MVC_TYPE_MODEL, GtkMvcModelIface))

GType gtk_mvc_model_get_type (void);

struct _GtkMvcModelIface
{
  GTypeInterface  base_interface;
};

G_END_DECLS

#endif /* !GTK_MVC_MODEL_H */

/* vim:set et sw=2 cino=t0,f0,(0,{s,>2s,n-1s,^-1s,e2s: */
