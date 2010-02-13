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

#include "gtk-mvc-button-view.h"

static void implement_gtk_mvc_view (GtkMvcViewIface* iface);

G_DEFINE_TYPE_WITH_CODE (GtkMvcButtonView, gtk_mvc_button_view, GTK_MVC_TYPE_DEFAULT_VIEW,
                         G_IMPLEMENT_INTERFACE (GTK_MVC_TYPE_VIEW, implement_gtk_mvc_view));

static void
gtk_mvc_button_view_init (GtkMvcButtonView* self)
{}

static void
gtk_mvc_button_view_class_init (GtkMvcButtonViewClass* self_class)
{}

static void
paint (GtkMvcView            * view,
       cairo_t               * context,
       cairo_rectangle_t     * area,
       cairo_rectangle_list_t* region)
{
  cairo_rectangle_t  position;

  gtk_mvc_view_get_position (view, &position);
  cairo_set_line_width (context, 1.0);
  cairo_rectangle (context,
                   0.5, 0.5,
                   position.width - 1.0, position.height - 1.0);
  cairo_set_source_rgb (context,
                        1.0 / 0xff * 0x20,
                        1.0 / 0xff * 0x4a,
                        1.0 / 0xff * 0x87);
  cairo_fill_preserve (context);
  cairo_set_source_rgb (context,
                        1.0 / 0xff * 0x72,
                        1.0 / 0xff * 0x9f,
                        1.0 / 0xff * 0xcf);
  cairo_stroke (context);
}

static void
implement_gtk_mvc_view (GtkMvcViewIface* iface)
{
  iface->paint = paint;
}

GtkMvcView*
gtk_mvc_button_view_new (void)
{
  return g_object_new (GTK_MVC_TYPE_BUTTON_VIEW,
                       NULL);
}

/* vim:set et sw=2 cino=t0,f0,(0,{s,>2s,n-1s,^-1s,e2s: */
