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

#include "gtk-mvc-default-view.h"

struct _GtkMvcDefaultViewPrivate
{
  cairo_rectangle_t  position;
};

#define PRIV(i) (((GtkMvcDefaultView*)(i))->_private)

static void implement_gtk_mvc_view (GtkMvcViewIface* iface);

G_DEFINE_TYPE_WITH_CODE (GtkMvcDefaultView, gtk_mvc_default_view, G_TYPE_INITIALLY_UNOWNED,
                         G_IMPLEMENT_INTERFACE (GTK_MVC_TYPE_VIEW, implement_gtk_mvc_view));

static void
gtk_mvc_default_view_init (GtkMvcDefaultView* self)
{
  PRIV (self) = G_TYPE_INSTANCE_GET_PRIVATE (self, GTK_MVC_TYPE_DEFAULT_VIEW, GtkMvcDefaultViewPrivate);
}

static void
gtk_mvc_default_view_class_init (GtkMvcDefaultViewClass* self_class)
{
  g_type_class_add_private (self_class, sizeof (GtkMvcDefaultViewPrivate));
}

static void
get_position (GtkMvcView       * view,
              cairo_rectangle_t* position)
{
  *position = PRIV (view)->position;
}

static void
set_position (GtkMvcView       * view,
              cairo_rectangle_t* position)
{
  PRIV (view)->position = *position;

  /* FIXME: trigger redraw */
}

static void
implement_gtk_mvc_view (GtkMvcViewIface* iface)
{
  iface->get_position = get_position;
  iface->set_position = set_position;
}

GtkMvcView*
gtk_mvc_default_view_new (void)
{
  return g_object_new (GTK_MVC_TYPE_DEFAULT_VIEW,
                       NULL);
}

/* vim:set et sw=2 cino=t0,f0,(0,{s,>2s,n-1s,^-1s,e2s: */
