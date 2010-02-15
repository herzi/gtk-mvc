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

#include "gtk-mvc-scroll-controller.h"

static void implement_gtk_mvc_controller (GtkMvcControllerIface* iface);

G_DEFINE_TYPE_WITH_CODE (GtkMvcScrollController, gtk_mvc_scroll_controller, GTK_MVC_TYPE_DEFAULT_CONTROLLER,
                         G_IMPLEMENT_INTERFACE (GTK_MVC_TYPE_CONTROLLER, implement_gtk_mvc_controller));

static void
gtk_mvc_scroll_controller_init (GtkMvcScrollController* self)
{}

static void
gtk_mvc_scroll_controller_class_init (GtkMvcScrollControllerClass* self_class)
{}

static gboolean
handle_button_press (GtkMvcController* controller,
                     GdkDevice       * device,
                     double            x,
                     double            y)
{
  GtkMvcView* view = gtk_mvc_controller_get_view (controller);

  if (view)
    {
#if 0
      if (gtk_mvc_view_hit_test (button_up_view, x, y))
        {
          /* FIXME: pass on */
        }
      else if (gtk_mvc_view_hit_test (button_down_view, x, y))
        {
          /* FIXME: pass on */
        }
      else
        {
          /* FIXME: handle */
        }
#endif
    }

  return FALSE;
}

static void
implement_gtk_mvc_controller (GtkMvcControllerIface* iface)
{
  iface->handle_button_press = handle_button_press;
}

/* vim:set et sw=2 cino=t0,f0,(0,{s,>2s,n-1s,^-1s,e2s: */
