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

#include "gtk-mvc-view.h"

GType
gtk_mvc_view_get_type (void)
{
  static GType type = 0;

  if (g_once_init_enter (&type))
    {
      GTypeInfo  info = {
              sizeof (GtkMvcViewIface),
              NULL, NULL,
              NULL, NULL, NULL,
              0, 0, NULL,
              NULL
      };
      GType registered = g_type_register_static (G_TYPE_INTERFACE,
                                                 G_STRINGIFY (GtkMvcView),
                                                 &info,
                                                 0);
      g_once_init_leave (&type, registered);
    }

  return type;
}

void
gtk_mvc_view_get_position (GtkMvcView       * self,
                           cairo_rectangle_t* position)
{
  GtkMvcViewIface* iface;

  g_return_if_fail (GTK_MVC_IS_VIEW (self));
  g_return_if_fail (position);

  iface = GTK_MVC_VIEW_GET_IFACE (self);
  if (!iface->get_position)
    {
      g_warning ("%s(%s): the type %s doesn't implement GtkMvcViewIface->get_position()",
                 G_STRFUNC, G_STRLOC,
                 G_OBJECT_TYPE_NAME (self));
    }
  else
    {
      iface->get_position (self, position);
    }
}

void
gtk_mvc_view_paint (GtkMvcView            * self,
                    cairo_t               * context,
                    cairo_rectangle_t     * area,
                    cairo_rectangle_list_t* region)
{
  GtkMvcViewIface* iface;

  g_return_if_fail (GTK_MVC_IS_VIEW (self));
  g_return_if_fail (area);
  g_return_if_fail (region->status == CAIRO_STATUS_SUCCESS);

  iface = GTK_MVC_VIEW_GET_IFACE (self);
  if (!iface->paint)
    {
      g_warning ("%s(%s): the type %s doesn't implement GtkMvcViewIface->paint()",
                 G_STRFUNC, G_STRLOC,
                 G_OBJECT_TYPE_NAME (self));
    }
  else if (cairo_status (context) == CAIRO_STATUS_SUCCESS)
    {
      cairo_save (context);
      iface->paint (self, context, area, region);
      cairo_restore (context);
    }
}

void
gtk_mvc_view_query_size (GtkMvcView    * self,
                         gtk_mvc_size_t* size)
{
  GtkMvcViewIface* iface;

  g_return_if_fail (GTK_MVC_IS_VIEW (self));
  g_return_if_fail (size);

  iface = GTK_MVC_VIEW_GET_IFACE (self);
  if (!iface->query_size)
    {
      g_warning ("%s(%s): the type %s doesn't implement GtkMvcViewIface->query_size()",
                 G_STRFUNC, G_STRLOC,
                 G_OBJECT_TYPE_NAME (self));
    }
  else
    {
      iface->query_size (self, size);
    }
}

void
gtk_mvc_view_set_position (GtkMvcView       * self,
                           cairo_rectangle_t* position)
{
  GtkMvcViewIface* iface;

  g_return_if_fail (GTK_MVC_IS_VIEW (self));
  g_return_if_fail (position);

  iface = GTK_MVC_VIEW_GET_IFACE (self);

  if (!iface->set_position)
    {
      g_warning ("%s(%s): the type %s doesn't implement GtkMvcViewIface->set_position()",
                 G_STRFUNC, G_STRLOC,
                 G_OBJECT_TYPE_NAME (self));
    }
  else
    {
      iface->set_position (self, position);
    }
}

/* vim:set et sw=2 cino=t0,f0,(0,{s,>2s,n-1s,^-1s,e2s: */
