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

#ifndef GTK_MVC_CONTROLLER_H
#define GTK_MVC_CONTROLLER_H

#include <gdk/gdk.h>

typedef struct _GtkMvcController      GtkMvcController;
typedef struct _GtkMvcControllerIface GtkMvcControllerIface;

#include "gtk-mvc-view.h"

G_BEGIN_DECLS

#define GTK_MVC_TYPE_CONTROLLER         (gtk_mvc_controller_get_type ())
#define GTK_MVC_CONTROLLER(i)           (G_TYPE_CHECK_INSTANCE_CAST ((i), GTK_MVC_TYPE_CONTROLLER, GtkMvcController))
#define GTK_MVC_IS_CONTROLLER(i)        (G_TYPE_CHECK_INSTANCE_TYPE ((i), GTK_MVC_TYPE_CONTROLLER))
#define GTK_MVC_CONTROLLER_GET_IFACE(i) (G_TYPE_INSTANCE_GET_INTERFACE ((i), GTK_MVC_TYPE_CONTROLLER, GtkMvcControllerIface))

GType       gtk_mvc_controller_get_type              (void);
GtkMvcView* gtk_mvc_controller_get_view              (GtkMvcController* self);
gboolean    gtk_mvc_controller_handle_button_press   (GtkMvcController* self,
                                                      GdkDevice       * device,
                                                      double            x,
                                                      double            y);
gboolean    gtk_mvc_controller_handle_button_release (GtkMvcController* self,
                                                      GdkDevice       * device,
                                                      double            x,
                                                      double            y);
void        gtk_mvc_controller_introduce_view        (GtkMvcController* self,
                                                      GtkMvcView      * view);

struct _GtkMvcControllerIface
{
  GTypeInterface  base_interface;

  /* vtable */
  GtkMvcView* (*get_view)              (GtkMvcController* controller);
  gboolean    (*handle_button_press)   (GtkMvcController* controller,
                                        GdkDevice       * device,
                                        double            x,
                                        double            y);
  gboolean    (*handle_button_release) (GtkMvcController* controller,
                                        GdkDevice       * device,
                                        double            x,
                                        double            y);
  void        (*introduce_view)        (GtkMvcController* controller,
                                        GtkMvcView      * view);
};

G_END_DECLS

#endif /* !GTK_MVC_CONTROLLER_H */

/* vim:set et sw=2 cino=t0,f0,(0,{s,>2s,n-1s,^-1s,e2s: */
