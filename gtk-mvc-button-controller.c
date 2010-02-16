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

#include "gtk-mvc-button-controller.h"

#include "gtk-mvc.h"

static void implement_gtk_mvc_controller (GtkMvcControllerIface* iface);

G_DEFINE_TYPE_WITH_CODE (GtkMvcButtonController, gtk_mvc_button_controller, GTK_MVC_TYPE_DEFAULT_CONTROLLER,
                         G_IMPLEMENT_INTERFACE (GTK_MVC_TYPE_CONTROLLER, implement_gtk_mvc_controller));

static void
gtk_mvc_button_controller_init (GtkMvcButtonController* self)
{}

static void
gtk_mvc_button_controller_class_init (GtkMvcButtonControllerClass* self_class)
{}

static gboolean
handle_button_press (GtkMvcController* controller,
                     GdkDevice       * device,
                     double            x,
                     double            y)
{
  GtkMvcView* view = gtk_mvc_controller_get_view (controller);

  /* FIXME: think about g_return_val_if_fail (hit_test())??? */
  if (view && gtk_mvc_view_hit_test (view, x, y))
    {
      GtkMvcModel* model = gtk_mvc_view_get_model (view);

      if (GTK_MVC_IS_BUTTON_MODEL (model))
        {
          gtk_mvc_button_model_set_pushed (GTK_MVC_BUTTON_MODEL (model), TRUE);

          /* FIXME: grab the pointer and wait for release */

          return TRUE;
        }
    }

  return FALSE;
}

static gboolean
handle_button_release (GtkMvcController* controller,
                       GdkDevice       * device,
                       double            x,
                       double            y)
{
  GtkMvcView* view = gtk_mvc_controller_get_view (controller);

  /* FIXME: think about g_return_val_if_fail (hit_test())??? */
  if (view && gtk_mvc_view_hit_test (view, x, y))
    {
      GtkMvcModel* model = gtk_mvc_view_get_model (view);

      if (GTK_MVC_IS_BUTTON_MODEL (model))
        {
          gtk_mvc_button_model_set_pushed (GTK_MVC_BUTTON_MODEL (model), FALSE);

          return TRUE;
        }
    }

  return FALSE;
}

static void
implement_gtk_mvc_controller (GtkMvcControllerIface* iface)
{
  iface->handle_button_press   = handle_button_press;
  iface->handle_button_release = handle_button_release;
}

GtkMvcController*
gtk_mvc_button_controller_new (void)
{
  return g_object_new (GTK_MVC_TYPE_BUTTON_CONTROLLER,
                       NULL);
}

/* vim:set et sw=2 cino=t0,f0,(0,{s,>2s,n-1s,^-1s,e2s: */
