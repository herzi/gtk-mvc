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

#ifndef GTK_MVC_VIEW_H
#define GTK_MVC_VIEW_H

#include <cairo.h>
#include "gtk-mvc-primitives.h"

typedef struct _GtkMvcView      GtkMvcView;
typedef struct _GtkMvcViewIface GtkMvcViewIface;

#include "gtk-mvc-controller.h"

G_BEGIN_DECLS

#define GTK_MVC_TYPE_VIEW         (gtk_mvc_view_get_type ())
#define GTK_MVC_VIEW(i)           (G_TYPE_CHECK_INSTANCE_CAST ((i), GTK_MVC_TYPE_VIEW, GtkMvcView))
#define GTK_MVC_VIEW_IFACE(c)     (g_warning ("unimplemented"))
#define GTK_MVC_IS_VIEW(i)        (G_TYPE_CHECK_INSTANCE_TYPE ((i), GTK_MVC_TYPE_VIEW))
#define GTK_MVC_VIEW_GET_IFACE(i) (G_TYPE_INSTANCE_GET_INTERFACE ((i), GTK_MVC_TYPE_VIEW, GtkMvcViewIface))

GType             gtk_mvc_view_get_type               (void);
GtkMvcController* gtk_mvc_view_get_controller         (GtkMvcView            * self);
void              gtk_mvc_view_get_position           (GtkMvcView            * self,
                                                       cairo_rectangle_t     * position);
gboolean          gtk_mvc_view_hit_test               (GtkMvcView            * self,
                                                       double                  x,
                                                       double                  y);
void              gtk_mvc_view_paint                  (GtkMvcView            * self,
                                                       cairo_t               * context,
                                                       cairo_rectangle_t     * area,
                                                       cairo_rectangle_list_t* region);
void              gtk_mvc_view_query_size             (GtkMvcView            * self,
                                                       gtk_mvc_size_t        * size);
void              gtk_mvc_view_set_controller         (GtkMvcView            * self,
                                                       GtkMvcController      * controller);
void              gtk_mvc_view_set_default_controller (GtkMvcView            * self);
void              gtk_mvc_view_set_position           (GtkMvcView            * self,
                                                       cairo_rectangle_t     * position);

struct _GtkMvcViewIface
{
  GTypeInterface  base_interface;

  /* vtable */
  GtkMvcController* (*create_default_controller) (GtkMvcView            * self);
  GtkMvcController* (*get_controller)            (GtkMvcView            * self);
  void              (*get_position)              (GtkMvcView            * self,
                                                  cairo_rectangle_t     * position);
  gboolean          (*hit_test)                  (GtkMvcView            * self,
                                                  double                  x,
                                                  double                  y);
  void              (*paint)                     (GtkMvcView            * self,
                                                  cairo_t               * context,
                                                  cairo_rectangle_t     * area,
                                                  cairo_rectangle_list_t* region);
  void              (*query_size)                (GtkMvcView            * self,
                                                  gtk_mvc_size_t        * size);
  void              (*set_controller)            (GtkMvcView            * self,
                                                  GtkMvcController      * controller);
  void              (*set_position)              (GtkMvcView            * self,
                                                  cairo_rectangle_t     * rectangle);
};

G_END_DECLS

#endif /* !GTK_MVC_VIEW_H */

/* vim:set et sw=2 cino=t0,f0,(0,{s,>2s,n-1s,^-1s,e2s: */
