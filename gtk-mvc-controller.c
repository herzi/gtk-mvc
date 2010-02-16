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

#include "gtk-mvc-controller.h"

GType
gtk_mvc_controller_get_type (void)
{
  static GType type = 0;

  if (g_once_init_enter (&type))
    {
      GType registered = g_type_register_static_simple (G_TYPE_INTERFACE,
                                                        G_STRINGIFY (GtkMvcController),
                                                        sizeof (GtkMvcControllerIface),
                                                        NULL, 0,
                                                        NULL, 0);

      g_once_init_leave (&type, registered);
    }

  return type;
}

GtkMvcView*
gtk_mvc_controller_get_view (GtkMvcController* self)
{
  GtkMvcControllerIface* iface;

  g_return_if_fail (GTK_MVC_IS_CONTROLLER (self));

  iface = GTK_MVC_CONTROLLER_GET_IFACE (self);
  if (!iface->get_view)
    {
      g_warning ("%s(%s): the type %s doesn't implement GtkMvcControllerIface->get_view",
                 G_STRFUNC, G_STRLOC,
                 G_OBJECT_TYPE_NAME (self));

      return NULL;
    }

  return iface->get_view (self);
}

gboolean
gtk_mvc_controller_handle_button_press (GtkMvcController* self,
                                        GdkDevice       * device,
                                        double            x,
                                        double            y)
{
  GtkMvcControllerIface* iface;

  g_return_if_fail (GTK_MVC_IS_CONTROLLER (self));
  g_return_if_fail (GDK_IS_DEVICE (device));

  iface = GTK_MVC_CONTROLLER_GET_IFACE (self);

  if (!iface->handle_button_press)
    {
      g_warning ("%s(%s): the type %s doesn't implement GtkMvcControllerIface->handle_button_press",
                 G_STRFUNC, G_STRLOC,
                 G_OBJECT_TYPE_NAME (self));

      return FALSE;
    }

  return iface->handle_button_press (self, device, x, y);
}

gboolean
gtk_mvc_controller_handle_button_release (GtkMvcController* self,
                                          GdkDevice       * device,
                                          double            x,
                                          double            y)
{
  GtkMvcControllerIface* iface;

  g_return_if_fail (GTK_MVC_IS_CONTROLLER (self));
  g_return_if_fail (GDK_IS_DEVICE (device));

  iface = GTK_MVC_CONTROLLER_GET_IFACE (self);

  if (!iface->handle_button_release)
    {
      g_warning ("%s(%s): the type %s doesn't implement GtkMvcControllerIface->handle_button_release",
                 G_STRFUNC, G_STRLOC,
                 G_OBJECT_TYPE_NAME (self));

      return FALSE;
    }

  return iface->handle_button_release (self, device, x, y);
}

void
gtk_mvc_controller_introduce_view (GtkMvcController* self,
                                   GtkMvcView      * view)
{
  GtkMvcControllerIface* iface;

  g_return_if_fail (GTK_MVC_IS_CONTROLLER (self));
  g_return_if_fail (!view || GTK_MVC_IS_VIEW (view));

  iface = GTK_MVC_CONTROLLER_GET_IFACE (self);

  if (!iface->introduce_view)
    {
      g_warning ("%s(%s): the type %s doesn't implement GtkMvcControllerIface->introduce_view",
                 G_STRFUNC, G_STRLOC,
                 G_OBJECT_TYPE_NAME (self));
    }
  else
    {
      iface->introduce_view (self, view);
    }
}

/* vim:set et sw=2 cino=t0,f0,(0,{s,>2s,n-1s,^-1s,e2s: */
