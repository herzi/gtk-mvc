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

#ifndef GTK_MVC_DEFAULT_CONTROLLER_H
#define GTK_MVC_DEFAULT_CONTROLLER_H

#include "gtk-mvc-controller.h"

G_BEGIN_DECLS

typedef struct _GtkMvcDefaultController        GtkMvcDefaultController;
typedef struct _GtkMvcDefaultControllerClass   GtkMvcDefaultControllerClass;
typedef struct _GtkMvcDefaultControllerPrivate GtkMvcDefaultControllerPrivate;

#define GTK_MVC_TYPE_DEFAULT_CONTROLLER         (gtk_mvc_default_controller_get_type ())

GType gtk_mvc_default_controller_get_type (void);

struct _GtkMvcDefaultController
{
  GObject                         base_instance;
  GtkMvcDefaultControllerPrivate* _private;
};

struct _GtkMvcDefaultControllerClass
{
  GObjectClass                    base_class;
};

G_END_DECLS

#endif /* !GTK_MVC_DEFAULT_CONTROLLER_H */

/* vim:set et sw=2 cino=t0,f0,(0,{s,>2s,n-1s,^-1s,e2s: */
