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

#include "gtk-mvc-default-controller.h"

struct _GtkMvcDefaultControllerPrivate
{
  GtkMvcView* view;
};

#define PRIV(i) (((GtkMvcDefaultController*)(i))->_private)

static void implement_gtk_mvc_controller (GtkMvcControllerIface* iface);

G_DEFINE_TYPE_WITH_CODE (GtkMvcDefaultController, gtk_mvc_default_controller, G_TYPE_INITIALLY_UNOWNED,
                         G_IMPLEMENT_INTERFACE (GTK_MVC_TYPE_CONTROLLER, implement_gtk_mvc_controller));

static void
gtk_mvc_default_controller_init (GtkMvcDefaultController* self)
{
  PRIV (self) = G_TYPE_INSTANCE_GET_PRIVATE (self, GTK_MVC_TYPE_DEFAULT_CONTROLLER, GtkMvcDefaultControllerPrivate);
}

static void
gtk_mvc_default_controller_class_init (GtkMvcDefaultControllerClass* self_class)
{
  g_type_class_add_private (self_class, sizeof (GtkMvcDefaultControllerPrivate));
}

static GtkMvcView*
get_view (GtkMvcController* controller)
{
  return PRIV (controller)->view;
}

static gboolean
handle_button_press (GtkMvcController* controller,
                     GdkDevice       * device,
                     double            x,
                     double            y)
{
  return FALSE;
}

static void
detach_view (gpointer  data,
             GObject * old_location)
{
  PRIV (data)->view = NULL;
}

static void
introduce_view (GtkMvcController* controller,
                GtkMvcView      * view)
{
  if (PRIV (controller)->view == view)
    {
      /* FIXME: test this */
      return;
    }

  if (PRIV (controller)->view)
    {
      g_object_weak_unref (G_OBJECT (PRIV (controller)->view),
                           detach_view,
                           controller);
      PRIV (controller)->view = NULL;
    }

  if (view)
    {
      PRIV (controller)->view = view;
      g_object_weak_ref (G_OBJECT (view), detach_view, controller);
    }
}

static void
implement_gtk_mvc_controller (GtkMvcControllerIface* iface)
{
  iface->get_view            = get_view;
  iface->handle_button_press = handle_button_press;
  iface->introduce_view      = introduce_view;
}

/* vim:set et sw=2 cino=t0,f0,(0,{s,>2s,n-1s,^-1s,e2s: */
